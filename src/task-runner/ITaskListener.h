#pragma once

namespace task_runner
{
class TaskBase;

class ITaskListener
{
private:
    virtual void on_completed( TaskBase* ) = 0;
};
}  // namespace task_runner