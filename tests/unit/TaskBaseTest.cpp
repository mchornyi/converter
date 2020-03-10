#include "gtest/gtest.h"

#include "task-runner/ITaskListener.h"
#include "task-runner/TaskBase.h"

namespace
{
using namespace task_runner;
// Tests the default constructor.
TEST( TaskBaseTest, GetID )
{
    TaskBase task1;
    TaskBase task2;
    TaskBase task3;

    ASSERT_EQ( 1, task1.get_id( ) );
    ASSERT_EQ( 2, task2.get_id( ) );
    ASSERT_EQ( 3, task3.get_id( ) );
}

TEST( TaskBaseTest, ListenerAddRemove )
{
    class FakeListener : public ITaskListener
    {
    public:
        FakeListener( )
        {
        }

    private:
        void
        on_completed( TaskBase* ) override
        {
        }
    };

    TaskBase task;
    FakeListener fake_listener;
    FakeListener fake_listener2;

    ASSERT_TRUE( task.add_listener( &fake_listener ) );
    ASSERT_TRUE( task.remove_listener( &fake_listener ) );

    ASSERT_FALSE( task.remove_listener( &fake_listener2 ) );
}

TEST( TaskBaseTest, GetErrorNone )
{
    TaskBase task;

    ASSERT_EQ( Error::None, task.get_error( ) );
}

TEST( TaskBaseTest, GetPriority )
{
    TaskBase task;

    ASSERT_EQ( Priority::Low, task.get_priority( ) );
}

TEST( TaskBaseTest, GetState )
{
    TaskBase task;

    ASSERT_EQ( State::None, task.get_state( ) );
}

}  // namespace