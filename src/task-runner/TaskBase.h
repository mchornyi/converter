#pragma once

#include "common/common.h"

#include <future>
#include <memory>

namespace task_runner
{
class ITaskListener;
using TaskID = uint32_t;

enum class Error : int32_t
{
    None,
    InvalidArgument
};

struct ErrorInfo
{
    ErrorInfo( )
        : error( Error::None )
    {
    }

    ErrorInfo( Error _error, std::string _msg )
        : error( _error )
        , msg( std::move( _msg ) )

    {
    }

    Error error;
    std::string msg;
};

enum class State : int32_t
{
    None,
    Running,
    Queued,
    Completed
};

enum class Priority : int32_t
{
    Low,
    Medium,
    High
};

class TaskBase
{
    friend class TaskList;

public:
    TaskBase( );
    TaskBase( const TaskBase& ) = delete;
    TaskBase& operator=( const TaskBase& ) = delete;
    virtual ~TaskBase( );

    bool add_listener( ITaskListener* );
    bool remove_listener( ITaskListener* );

    TaskID get_id( ) const;

    bool run( );

    void stop( );

    ErrorInfo get_error( ) const;

    Priority get_priority( ) const;

    void set_priority( Priority );

    State get_state( ) const;

    std::future< int > get_future( );

private:
    void set_state( State );

    virtual ErrorInfo run_internal( );

    virtual void stop_internal( );

private:
    struct Impl;
    std::unique_ptr< Impl > m_pimpl;
};
}  // namespace task_runner
