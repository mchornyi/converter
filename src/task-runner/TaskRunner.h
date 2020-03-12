#pragma once

#include <memory>

namespace task_runner
{
class TaskRunner final
{
public:
    explicit TaskRunner( u_int8_t thread_count = 1 );
    ~TaskRunner( );

    TaskRunner( TaskRunner& ) = delete;

    TaskRunner& operator=( TaskRunner& ) = delete;

    void join();

    void stop();

    bool is_running() const;

private:
    struct Impl;
    std::unique_ptr< Impl > m_pimpl;
};
}  // namespace task_runner