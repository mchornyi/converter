#include "gtest/gtest.h"

#include "common/Log.h"

namespace
{
TEST( LogTest, LogMessageValidation )
{
    std::string expected_message( "ConverterMessageTestMessage" );
    std::string expected_line_number( ":13" );
    std::string expected_function( "func:TestBody" );

    std::string actual = FORMAT_LOG( "ConverterMessageTestMessage" );

    ASSERT_NE( std::string::npos, actual.find( expected_message ) );
    ASSERT_NE( std::string::npos, actual.find( expected_line_number ) );
    ASSERT_NE( std::string::npos, actual.find( expected_function ) );
}
}  // namespace