#include "gtest/gtest.h"

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
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

    task_runner.stop( );

    int max_iteration_count = 100;
    while ( max_iteration_count-- > 0 && task_runner.is_running( ) )
    {
        std::this_thread::sleep_for( milliseconds( 10 ) );
    }

    // This helps to avoid the blocked state
    ASSERT_FALSE( task_runner.is_running( ) )
        << "ERROR: The TaskRunner cannot stop! The crash is going to happen!";

    task_runner.join( );
}

}  // namespace