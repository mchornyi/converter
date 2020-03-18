#include "common/Log.h"
#include "task-runner/TaskBase.h"
#include "task-runner/TaskList.h"
#include "task-runner/TaskThread.h"

#include <atomic>
#include <thread>
#include <iostream>

namespace task_runner
{
const char*
TaskThread::get_death_error_msg( )
{
    static const char* death_error_msg = "ERROR: The thread is still working\n";
    return death_error_msg;
}

struct TaskThread::Impl
{
    Impl( )
        : task_list( nullptr )
        , is_enabled( true )
    {
    }

    TaskList* task_list;
    std::thread task_thread;
    std::atomic_bool is_enabled;
};

TaskThread::TaskThread( TaskList* task_list )
    : m_pimpl( new Impl( ) )
{
    m_pimpl->task_list = task_list;

    m_pimpl->task_thread = std::thread( &TaskThread::poll, this );
}

TaskThread::~TaskThread( )
{
    if ( is_running( ) )
    {
        std::cout << get_death_error_msg( ) << std::endl;
    }
}

void
TaskThread::poll( )
{
    const std::chrono::milliseconds span( 200 );

    LOG( "INFO: The thread is enabled" );

    while ( m_pimpl->is_enabled.load( std::memory_order::memory_order_relaxed ) )
    {
        auto task = m_pimpl->task_list->pop( );

        if ( task )
        {
            task->run( );
        }

        std::this_thread::sleep_for( span );

        std::this_thread::yield( );
    }
}

void
TaskThread::stop( )
{
    m_pimpl->is_enabled.store( false, std::memory_order::memory_order_relaxed );
}

void
TaskThread::join( )
{
    m_pimpl->task_thread.join( );
}

bool
TaskThread::is_running( ) const
{
    return m_pimpl->is_enabled.load( std::memory_order::memory_order_relaxed )
           && m_pimpl->task_thread.joinable( );
}

}  // namespace task_runner