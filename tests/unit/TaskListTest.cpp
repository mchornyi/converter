#include "gtest/gtest.h"

#include "task-runner/TaskBase.h"
#include "task-runner/TaskList.h"

namespace
{
using namespace task_runner;

TEST( TaskListTest, EmptyPop )
{
    TaskList task_list;

    ASSERT_EQ( 0, task_list.size( ) );

    ASSERT_EQ( nullptr, task_list.pop( ) );
}

TEST( TaskListTest, PushPopSize )
{
    TaskBase task;

    TaskList task_list;

    ASSERT_TRUE( task_list.push( &task ) );

    ASSERT_EQ( 1, task_list.size( ) );

    TaskBase* task_tmp = task_list.pop( );

    ASSERT_EQ( &task, task_tmp );
}

TEST( TaskListTest, PriorityCheck )
{
    TaskBase task_medium;
    task_medium.set_priority( Priority::Medium );
    TaskBase task_low;
    task_low.set_priority( Priority::Low );
    TaskBase task_high;
    task_high.set_priority( Priority::High );

    TaskList task_list;

    ASSERT_TRUE( task_list.push( &task_medium ) );
    ASSERT_TRUE( task_list.push( &task_low ) );
    ASSERT_TRUE( task_list.push( &task_high ) );

    ASSERT_EQ( 3, task_list.size( ) );

    ASSERT_EQ( &task_high, task_list.pop( ) );
    ASSERT_EQ( &task_medium, task_list.pop( ) );
    ASSERT_EQ( &task_low, task_list.pop( ) );
}

}  // namespace