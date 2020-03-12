#include "gtest/gtest.h"

#include "task-runner/TaskRunner.h"

namespace
{
using namespace task_runner;

TEST( TaskRunnerTest, Default )
{
    TaskRunner task_runner;
}

}