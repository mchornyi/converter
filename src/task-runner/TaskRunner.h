#pragma once

#include <memory>

namespace task_runner
{
class TaskRunner final
{
public:
    TaskRunner( );
    ~TaskRunner( );

    TaskRunner( TaskRunner& ) = delete;

    TaskRunner& operator=( TaskRunner& ) = delete;

private:
    struct Impl;
    std::unique_ptr< Impl > m_pimpl;
};
}  // namespace task_runner