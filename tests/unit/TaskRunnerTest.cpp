#include "gtest/gtest.h"

#include "MockTaskBaseListener.h"
#include "Helpers.h"
#include "task-runner/TaskBase.h"
#include "task-runner/TaskRunner.h"
#include "task-runner/TaskThread.h"

#include <chrono>
#include <thread>

namespace
{
using namespace task_runner;

TEST( TaskRunnerDeathTest, NoJoin )
{
    ASSERT_DEATH( { TaskRunner task_runner; }, TaskThread::get_death_error_msg( ) );
}

TEST( TaskRunnerTest, Stop )
{
    using namespace std::chrono;

    TaskRunner task_runner( 2 );

    // wait for thread to start
    const std::chrono::milliseconds span( 100 );
    std::this_thread::sleep_for( span );

    helpers::stop_task_runner( task_runner );
}

TEST( TaskRunnerTest, AddTask )
{
    TaskBase task;

    TaskRunner task_runner;

    ASSERT_TRUE( task_runner.add_task( &task ) );
    ASSERT_FALSE( task_runner.add_task( nullptr ) );

    helpers::stop_task_runner( task_runner );
}

TEST( TaskRunnerTest, CheckTaskState )
{
    TaskBase task;

    auto task_future = task.get_future( );

    task_mocks::MockTaskListener mock_task_listener;

    EXPECT_CALL( mock_task_listener, on_completed );

    ASSERT_TRUE( task.add_listener( &mock_task_listener ) );

    TaskRunner task_runner;

    ASSERT_TRUE( task_runner.add_task( &task ) );

    ASSERT_FALSE( task_runner.add_task( nullptr ) );

    const std::chrono::milliseconds span( 300 );
    auto result = task_future.wait_for( span );

    ASSERT_EQ( std::future_status::ready, result ) << "Time out error!";

    auto error_code = task_future.get( );

    ASSERT_EQ( 0, error_code );

    helpers::stop_task_runner( task_runner );
}

}  // namespace