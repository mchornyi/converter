#include "gtest/gtest.h"

#include "ConverterApp.h"
#include "common/Helpers.h"

namespace
{
using namespace converter;
const uint32_t expected_file_size_testcase_mp3( 12538 );

TEST( ConverterAppTest, RunApp )
{
    ConverterApp app( "./res/" );

    app.run( );

    // Check the files and cleanup

    std::stringstream ss;
    ss << "./res/testcase"
       << ".mp3";

    const auto size = helpers::file_size( ss.str( ) );
    EXPECT_EQ( expected_file_size_testcase_mp3, size );
    EXPECT_EQ( 0, remove( ss.str( ).c_str( ) ) );
}
}  // namespace