#include "gtest/gtest.h"

#include "TaskBase.h"

namespace 
{
    // Tests the default constructor.
    TEST(TaskBaseTest, ValidationOfGetID)
    {
        task_runner::TaskBase obj1;
        task_runner::TaskBase obj2;
        task_runner::TaskBase obj3;

        ASSERT_EQ( 1, obj1.get_id() );
        ASSERT_EQ( 2, obj2.get_id() );
        ASSERT_EQ( 3, obj3.get_id() );
    }
}