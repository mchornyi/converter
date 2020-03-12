#pragma once

#include "gmock/gmock.h"
#include "task-runner/ITaskListener.h"

namespace task_mocks
{
class MockTaskListener : public task_runner::ITaskListener
{
public:
    MOCK_METHOD( void, on_completed, (task_runner::TaskBase*), ( override ) );
};
}