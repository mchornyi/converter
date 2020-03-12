#include "gtest/gtest.h"

#include "common/Log.h"
#include "task-runner/TaskBase.h"
#include "task-runner/TaskList.h"
#include "task-runner/TaskThread.h"

#include <chrono>
#include <thread>

namespace
{
using namespace task_runner;

void
stop_thread( TaskThread& thread )
{
    using namespace std::chrono;

    ASSERT_TRUE( thread.is_running( ) );

    thread.stop( );

    int max_iteration_count = 100;
    while ( max_iteration_count-- > 0 && thread.is_running( ) )
    {
        std::this_thread::sleep_for( milliseconds( 10 ) );
    }

    // This helps to avoid the blocked state
    ASSERT_FALSE( thread.is_running( ) )
        << "ERROR: The thread cannot stop! The crash is going to happen!";

    thread.join( );
}

TEST( TaskThreadDeathTest, NoJoin )
{
    ASSERT_DEATH(
        {
            TaskList task_list;

            TaskThread task_thread( &task_list );
        },
        TaskThread::get_death_error_msg( ) );
}

TEST( TaskThreadTest, Stop )
{
    TaskList task_list;

    TaskThread task_thread( &task_list );

    ASSERT_TRUE( task_thread.is_running( ) );

    // wait for thread to start
    const std::chrono::milliseconds span( 100 );
    std::this_thread::sleep_for( span );

    stop_thread( task_thread );
}

TEST( TaskThreadTest, RunTask )
{
    TaskBase task_base;

    auto task_future = task_base.get_future( );

    TaskList task_list;

    TaskThread task_thread( &task_list );

    ASSERT_TRUE( task_thread.is_running( ) );

    // wait for thread to start
    const std::chrono::milliseconds span( 100 );
    std::this_thread::sleep_for( span );

    task_list.push( &task_base );

    const std::chrono::milliseconds span_future( 300 );
    task_future.wait_for( span_future );

    EXPECT_EQ( State::Completed, task_base.get_state( ) ) << "ERROR: The task is not completed!";

    stop_thread( task_thread );
}

}  // namespace