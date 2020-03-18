#include "ConverterApp.h"

#include "converter/ConverterHelper.h"
#include "converter/ConverterLame.h"
#include "converter/ConverterTask.h"
#include "common/Log.h"
#include "common/Utils.h"

#include "task-runner/TaskBase.h"
#include "task-runner/TaskRunner.h"

#include <iostream>

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
    const std::string wav_str( ".wav" );
    const std::string mp3_str( ".mp3" );

    const auto files = utils::list_files( working_dir );

    const auto files_wav = utils::filter_list_files( files, wav_str );

    TaskContainer tasks;

    tasks.reserve( files_wav.size( ) );

    for ( const auto& file_wav : files_wav )
    {
        std::string file_path_out = file_wav;
        auto pos = file_path_out.find( wav_str );
        if ( pos == std::string::npos )
        {
            LOG( "ERROR: Wrong file extension %s", file_path_out.c_str( ) );
            continue;
        }

        file_path_out.replace( pos, mp3_str.size( ), mp3_str );

        auto converter_task( converter::ConverterHelper::make_lame_converter_task_dafault(
            converter, file_wav, file_path_out ) );

        if ( !converter_task )
        {
            LOG( "ERROR: Cannot create conversion task for file %s", file_wav.c_str( ) );
            continue;
        }

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
{
    if ( !utils::dir_exist(working_dir) )
    {
        std::cerr << "Cannot access " << working_dir << "\n";
        return;
    }

    m_pimpl.reset( new Impl( ) );

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

bool
ConverterApp::run( )
{
    if ( !m_pimpl )
    {
        return false;
    }

    m_pimpl->tasks = make_tasks( &m_pimpl->converter_lame, m_pimpl->working_dir );

    for ( auto& task : m_pimpl->tasks )
    {
        m_pimpl->task_Runner->add_task( task.get( ) );
    }

    for ( auto& task : m_pimpl->tasks )
    {
        auto task_future = task->get_future( );
        task_future.wait( );
    }

    stop_task_runner( *m_pimpl->task_Runner.get( ) );

    return true;
}

}  // namespace converter