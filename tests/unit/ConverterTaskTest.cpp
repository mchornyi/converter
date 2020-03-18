#include "gtest/gtest.h"

#include "converter/ConverterTask.h"
#include "converter/ConverterHelper.h"

#include "common/Helpers.h"
#include "task-runner/TaskRunner.h"

#include "MockIConverter.h"
#include "MockTaskBaseListener.h"
namespace
{
using namespace converter;

TEST( ConverterTask, Run )
{
    task_mocks::MockIConverter mock_i_Converter;

    EXPECT_CALL( mock_i_Converter, convert );

    auto task( ConverterHelper::make_converter_task_default( &mock_i_Converter ) );

    ASSERT_TRUE( task );

    task->run( );

    ASSERT_EQ( task_runner::State::Completed, task->get_state( ) );

    const auto error_info = task->get_error( );
    ASSERT_EQ( task_runner::Error::None, error_info.error );
    ASSERT_EQ( std::string( "" ), error_info.msg );
}

TEST( ConverterTask, RunTaskRunnerAndCheckTaskState )
{
    task_mocks::MockIConverter mock_i_Converter;

    EXPECT_CALL( mock_i_Converter, convert );

    auto task( ConverterHelper::make_converter_task_default( &mock_i_Converter ) );

    ASSERT_TRUE( task );

    auto task_future = task->get_future( );

    task_mocks::MockTaskListener mock_task_listener;

    EXPECT_CALL( mock_task_listener, on_completed );

    ASSERT_TRUE( task->add_listener( &mock_task_listener ) );

    task_runner::TaskRunner task_runner;

    ASSERT_TRUE( task_runner.add_task( task.get( ) ) );

    const std::chrono::milliseconds span( 300 );
    auto result = task_future.wait_for( span );

    ASSERT_EQ( std::future_status::ready, result ) << "Time out error!";

    auto error_code = task_future.get( );

    ASSERT_EQ( 0, error_code );

    helpers::stop_task_runner( task_runner );
}

}  // namespace