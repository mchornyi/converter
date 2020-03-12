#include "gtest/gtest.h"

#include "common/Log.h"
#include "task-runner/TaskList.h"
#include "task-runner/TaskThread.h"

#include <chrono>
#include <thread>

namespace
{
using namespace task_runner;

TEST( TaskThreadDeathTest, NoJoin )
{
    ASSERT_DEATH(
        {
            TaskList task_list;

            TaskThread task_thread( &task_list );
        },
        TaskThread::get_death_error_msg( ) );
}

TEST( TaskThreadDeathTest, Stop )
{
    using namespace std::chrono;

    TaskList task_list;

    TaskThread task_thread( &task_list );

    ASSERT_TRUE( task_thread.is_running( ) );

    // wait for thread to start
    std::this_thread::sleep_for( milliseconds( 100 ) );

    task_thread.stop( );

    int max_iteration_count = 100;
    while ( max_iteration_count-- > 0 && task_thread.is_running( ) )
    {
        std::this_thread::sleep_for( milliseconds( 10 ) );
    }

    // This helps to avoid the blocked state
    ASSERT_FALSE( task_thread.is_running( ) )
        << "ERROR: The thread cannot stop! The crash is going to happen!";

    task_thread.join( );
}

}  // namespace