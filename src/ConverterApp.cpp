#include "ConverterApp.h"

#include "ConverterHelper.h"
#include "ConverterLame.h"
#include "ConverterTask.h"
#include "common/Log.h"
#include "task-runner/TaskBase.h"
#include "task-runner/TaskRunner.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <vector>

using TaskContainer = std::vector< std::unique_ptr< task_runner::TaskBase > >;

namespace
{
void
stop_task_runner( task_runner::TaskRunner& task_runner )
{
    using namespace std::chrono;

    if ( !task_runner.is_running( ) )
    {
        LOG( "Error: !task_runner.is_running( )" );
        return;
    }

    task_runner.stop( );

    int max_iteration_count = 100;
    while ( max_iteration_count-- > 0 && task_runner.is_running( ) )
    {
        std::this_thread::sleep_for( milliseconds( 10 ) );
    }

    // This helps to avoid the blocked state
    if ( task_runner.is_running( ) )
    {
        LOG( "ERROR: The TaskRunner cannot stop! The crash is going to happen!" );
        return;
    }

    task_runner.join( );
}

TaskContainer
make_tasks( converter::IConverter* converter, const std::string& working_dir )
{
    struct stat info;

    if ( stat( working_dir.c_str( ), &info ) != 0 )
    {
        std::cerr << "Cannot access " << working_dir << "\n";
        return {};
    }

    // TODO: Read the folder
    TaskContainer tasks;

    int files_number = 0;

    tasks.reserve( files_number );

    std::string file_path_in;
    std::string file_path_out;

    auto converter_task( converter::ConverterHelper::make_lame_converter_task_dafault(
        converter, file_path_in, file_path_out ) );

    if ( converter_task )
    {
        tasks.emplace_back( std::move( converter_task ) );
    }

    return tasks;
}

}  // namespace

namespace converter
{
struct ConverterApp::Impl
{
    std::string working_dir;

    std::unique_ptr< task_runner::TaskRunner > task_Runner;
    TaskContainer tasks;
    ConverterLame converter_lame;
};

ConverterApp::ConverterApp( std::string working_dir )
    : m_pimpl( new Impl( ) )
{
    m_pimpl->working_dir = std::move( working_dir );

    auto threads_number = std::thread::hardware_concurrency( );
    if ( threads_number <= 1 )
    {
        threads_number = 2;
    }

    m_pimpl->task_Runner.reset( new task_runner::TaskRunner( threads_number ) );
}

ConverterApp::~ConverterApp( )
{
}

void
ConverterApp::run( )
{
    for ( auto& task : m_pimpl->tasks )
    {
        m_pimpl->task_Runner->add_task( task.get( ) );
    }

    m_pimpl->tasks = make_tasks( &m_pimpl->converter_lame, m_pimpl->working_dir );

    for ( auto& task : m_pimpl->tasks )
    {
        auto task_future = task->get_future( );
        // const std::chrono::milliseconds span( 1 * 60 * 1000 );
        // auto result = task_future.wait_for( span );
        task_future.wait( );
    }

    stop_task_runner( *m_pimpl->task_Runner.get( ) );
}

}  // namespace converter