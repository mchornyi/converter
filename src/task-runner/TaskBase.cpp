#include "common/Log.h"
#include "task-runner/TaskBase.h"

#include <set>

using namespace task_runner;

namespace
{
const TaskID INVALID_ID( 0 );
TaskID id_counter( INVALID_ID );

};  // namespace

struct TaskBase::Impl
{
    Impl( )
        : error( Error::None )
        , state( State::None )
        , priority( Priority::Low )
    {
        id = ++id_counter;
    }

    bool
    add_listener( ITaskListener* listener )
    {
        auto res = listeners.insert( listener );
        return res.second;
    }
    bool
    remove_listener( ITaskListener* listener )
    {
        return listeners.erase( listener ) > 0;
    }

    std::set< ITaskListener* > listeners;
    TaskID id;
    std::promise< void > promise;
    Error error;
    State state;
    Priority priority;
};

TaskBase::TaskBase( )
    : m_pimpl( new TaskBase::Impl( ) )
{
}

TaskBase::~TaskBase( )
{
}

TaskID
TaskBase::get_id( ) const
{
    return m_pimpl->id;
}

bool
TaskBase::add_listener( ITaskListener* listener )
{
    return m_pimpl->add_listener( listener );
}

bool
TaskBase::remove_listener( ITaskListener* listener )
{
    return m_pimpl->remove_listener( listener );
}

void
TaskBase::run( )
{
    run_internal( );
}

void
TaskBase::stop( )
{
    stop_internal( );
}

Error
TaskBase::get_error( ) const
{
    return m_pimpl->error;
}

void
TaskBase::set_priority( Priority value )
{
    m_pimpl->priority = value;
}

Priority
TaskBase::get_priority( ) const
{
    return m_pimpl->priority;
}

State
TaskBase::get_state( ) const
{
    return m_pimpl->state;
}

std::future< void >
TaskBase::get_future( )
{
    return m_pimpl->promise.get_future( );
}

void
TaskBase::run_internal( )
{
    LOG( "WARN: Empty implementation" );
}

void
TaskBase::stop_internal( )
{
    LOG( "WARN: Empty implementation" );
}