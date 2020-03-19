#include "common/Log.h"
#include "task-runner/ITaskListener.h"
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
        : state( State::None )
        , priority( Priority::Low )
    {
        id = ++id_counter;
    }

    bool
    add_listener( ITaskListener* listener )
    {
        if ( listener == nullptr )
        {
            return false;
        }

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
    std::promise< int > promise;
    ErrorInfo errorInfo;
    State state;
    Priority priority;
    std::mutex run_mtx;
};

TaskBase::TaskBase( )
    : m_pimpl( new Impl( ) )
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

bool
TaskBase::run( )
{
    std::lock_guard<std::mutex> lock(m_pimpl->run_mtx);

    const State currnet_state = get_state( );
    if ( currnet_state != State::None )
    {
        LOG( "WARN: The task id=%d state is %d", get_id( ), currnet_state );
        return false;
    }

    set_state( State::Running );

    m_pimpl->errorInfo = run_internal( );

    set_state( State::Completed );

    m_pimpl->promise.set_value( m_pimpl->errorInfo.error == Error::None ? 0 : 1 );

    return true;
}

void
TaskBase::stop( )
{
    stop_internal( );
}

ErrorInfo
TaskBase::get_error( ) const
{
    return m_pimpl->errorInfo;
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

void
TaskBase::set_state( State value )
{
    if ( m_pimpl->state == value )
    {
        return;
    }

    m_pimpl->state = value;

    if ( m_pimpl->state == State::Completed )
    {
        for ( auto* listener : m_pimpl->listeners )
        {
            listener->on_completed( this );
        }
    }
}

std::future< int >
TaskBase::get_future( )
{
    return m_pimpl->promise.get_future( );
}

ErrorInfo
TaskBase::run_internal( )
{
    LOG( "WARN: Empty implementation" );
    return ErrorInfo( );
}

void
TaskBase::stop_internal( )
{
    LOG( "WARN: Empty implementation" );
}