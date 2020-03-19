#include "common/Log.h"
#include "task-runner/TaskList.h"
#include "task-runner/TaskRunner.h"
#include "task-runner/TaskThread.h"

#include <vector>

namespace task_runner
{
struct TaskRunner::Impl
{
    TaskList task_list;
    std::vector< std::unique_ptr< TaskThread > > thread_pool;
};

TaskRunner::TaskRunner( u_int8_t thread_count /*= 1*/ )
    : m_pimpl( new Impl( ) )
{
    m_pimpl->thread_pool.reserve( thread_count );

    for ( u_int8_t i = 0; i < thread_count; ++i )
    {
        m_pimpl->thread_pool.emplace_back(
            std::unique_ptr< TaskThread >( new TaskThread( &m_pimpl->task_list ) ) );
    }
}

TaskRunner::~TaskRunner( )
{
    if ( is_running( ) )
    {
        LOG( "ERROR: The TaskRunner is still runnig!" );
    }
}

void
TaskRunner::join( )
{
    for ( auto& thread : m_pimpl->thread_pool )
    {
        thread->join( );
    }
}

void
TaskRunner::stop( )
{
    for ( auto& thread : m_pimpl->thread_pool )
    {
        thread->stop( );
    }
}

bool
TaskRunner::is_running( ) const
{
    for ( auto& thread : m_pimpl->thread_pool )
    {
        if ( thread->is_running( ) )
        {
            return true;
        }
    }

    return false;
}

bool
TaskRunner::add_task( TaskBase* task )
{
    return m_pimpl->task_list.push( task );
}

}  // namespace task_runner