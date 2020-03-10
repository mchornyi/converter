#pragma once

#include <memory>

namespace task_runner
{
class TaskBase;

class TaskList
{
public:
    TaskList( );
    virtual ~TaskList( );

    TaskList( const TaskList& ) = delete;
    TaskList& operator=( const TaskList& ) = delete;

    bool push( TaskBase* );
    TaskBase* pop( );
    int size( ) const;

private:
    struct Impl;
    std::unique_ptr< Impl > m_pimpl;
};
}  // namespace taks_runner