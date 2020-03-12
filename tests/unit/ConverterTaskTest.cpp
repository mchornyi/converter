#include "gtest/gtest.h"

#include "ConverterTask.h"
#include "MockIConverter.h"

namespace
{
using namespace converter;

TEST( ConverterTask, Run )
{
    task_mocks::MockIConverter mock_i_Converter;

    EXPECT_CALL( mock_i_Converter, convert );

    ConverterTask task( &mock_i_Converter, "" );

    task.run( );
}

}  // namespace