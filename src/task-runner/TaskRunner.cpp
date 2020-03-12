#include "task-runner/TaskRunner.h"

namespace task_runner
{
struct TaskRunner::Impl
{
};

TaskRunner::TaskRunner( )
    : m_pimpl( new Impl( ) )
{
}

TaskRunner::~TaskRunner( )
{
}
}  // namespace task_runner