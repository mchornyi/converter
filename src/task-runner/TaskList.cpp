#include "task-runner/TaskBase.h"
#include "task-runner/TaskList.h"

#include <mutex>
#include <set>

namespace task_runner
{
auto task_compare = []( const TaskBase* lhs, const TaskBase* rhs ) -> bool {
    if ( lhs == nullptr || rhs == nullptr )
    {
        return false;
    }

    if ( lhs->get_priority( ) < rhs->get_priority( ) )
    {
        return true;
    }

    if ( lhs->get_priority( ) == rhs->get_priority( ) )
    {
        return lhs < rhs;
    }

    return false;
};

struct TaskList::Impl
{
    Impl( )
        : tasks_list( task_compare )
    {
    }

    bool
    push( TaskBase* task )
    {
        if ( task == nullptr )
        {
            return false;
        }

        if ( task->get_state( ) != State::None )
        {
            return false;
        }

        const std::lock_guard< std::mutex > lock( mtx );

        auto result = tasks_list.insert( task );

        task->set_state( State::Queued );

        return result.second;
    }

    TaskBase*
    pop( )
    {
        const std::lock_guard< std::mutex > lock( mtx );

        if ( tasks_list.empty( ) )
        {
            return nullptr;
        }

        auto it = tasks_list.end( );

        --it;

        TaskBase* task = *it;

        task->set_state( State::None );

        tasks_list.erase( it );

        return task;
    }

    int
    size( ) const
    {
        const std::lock_guard< std::mutex > lock( mtx );
        return tasks_list.size( );
    }

    mutable std::mutex mtx;
    std::set< TaskBase*, decltype( task_compare ) > tasks_list;
};

TaskList::TaskList( )
    : m_pimpl( new Impl( ) )
{
}

TaskList::~TaskList( )
{
}

bool
TaskList::push( TaskBase* task )
{
    return m_pimpl->push( task );
}

TaskBase*
TaskList::pop( )
{
    return m_pimpl->pop( );
}

int
TaskList::size( ) const
{
    return m_pimpl->size( );
}

}  // namespace task_runner