#pragma once

#include <memory>

namespace task_runner
{
class TaskList;

class TaskThread final
{
public:
    TaskThread( TaskList* );
    ~TaskThread( );

    TaskThread( TaskThread& ) = delete;

    TaskThread& operator=( TaskThread& ) = delete;

    void stop( );

    void join( );

    bool is_running( ) const;

    static const char* get_death_error_msg( );

private:
    void poll( );

private:
    struct Impl;
    std::unique_ptr< Impl > m_pimpl;
};
}  // namespace task_runner