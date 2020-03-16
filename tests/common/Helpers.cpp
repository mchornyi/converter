#include "gtest/gtest.h"

#include "Helpers.h"
#include "task-runner/TaskRunner.h"

#include <chrono>
#include <thread>

namespace helpers
{
void
stop_task_runner( task_runner::TaskRunner& task_runner )
{
    using namespace std::chrono;

    ASSERT_TRUE( task_runner.is_running( ) );

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
}