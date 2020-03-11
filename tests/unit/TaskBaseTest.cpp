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

    ASSERT_EQ( Error::None, task.get_error( ).error );
    ASSERT_EQ( std::string( ), task.get_error( ).msg );
}

TEST( TaskBaseTest, GetPriority )
{
    TaskBase task;

    ASSERT_EQ( Priority::Low, task.get_priority( ) );
}

TEST( TaskBaseTest, SetPriority )
{
    TaskBase task;
    task.set_priority( Priority::Medium );

    ASSERT_EQ( Priority::Medium, task.get_priority( ) );
}

TEST( TaskBaseTest, GetState )
{
    TaskBase task;

    ASSERT_EQ( State::None, task.get_state( ) );
}

TEST( TaskBaseTest, GetStateAfterRunCommand )
{
    TaskBase task;

    ASSERT_EQ( State::None, task.get_state( ) );

    task.run();

    ASSERT_EQ( State::Completed, task.get_state( ) );
}

TEST( TaskBaseTest, GetFutureTimeOutError )
{
    TaskBase task;

    std::future< int > task_future = task.get_future( );

    const std::chrono::milliseconds span( 100 );

    auto result = task_future.wait_for( span );

    ASSERT_NE( std::future_status::ready, result );
}

TEST( TaskBaseTest, GetFutureSuccess )
{
    TaskBase task;

    std::future< int > task_future = task.get_future( );

    const std::chrono::milliseconds span( 100 );

    std::thread task_thread( [&task] {
        const std::chrono::milliseconds span( 10 );
        std::this_thread::sleep_for( span );
        task.run( );
    } );

    auto result = task_future.wait_for( span );

    task_thread.join( );

    ASSERT_EQ( std::future_status::ready, result ) << "Time out error!";

    auto error_code = task_future.get( );

    ASSERT_EQ( 0, error_code );
}

TEST( TaskBaseTest, AddRemoveListener )
{
    TaskBase task;

    class FakeListener : public ITaskListener
    {
        virtual void
        on_completed( TaskBase* ) override
        {
        }

    } fake_listener;

    ASSERT_EQ( true, task.add_listener( &fake_listener ) );
    ASSERT_NE( true, task.add_listener( &fake_listener ) );

    ASSERT_EQ( true, task.remove_listener( &fake_listener ) );
    ASSERT_NE( true, task.remove_listener( &fake_listener ) );
}

}  // namespace