#include "gtest/gtest.h"

#include "ConverterAppSimple.h"
#include "common/Helpers.h"

namespace
{
using namespace converter;
const uint32_t expected_file_size_testcase_mp3( 12538 );
const uint32_t expected_file_size_big_test_case_mp3( 1181257 );

TEST( ConverterAppSimpleTest, RunApp )
{
    const std::string working_dir( "./res/" );
    EXPECT_TRUE( ConverterAppSimple( ).run( working_dir ) );

    // Check the files and cleanup

    const std::string out_file_testcase_mp3( "./res/testcase.mp3" );
    const std::string out_file_big_test_case_mp3( "./res/big-test-case.mp3" );

    auto size = helpers::file_size( out_file_testcase_mp3 );
    EXPECT_EQ( expected_file_size_testcase_mp3, size );
    EXPECT_EQ( 0, remove( out_file_testcase_mp3.c_str( ) ) );

    size = helpers::file_size( out_file_big_test_case_mp3 );
    EXPECT_EQ( expected_file_size_big_test_case_mp3, size );
    EXPECT_EQ( 0, remove( out_file_big_test_case_mp3.c_str( ) ) );
}

TEST( ConverterAppSimpleTest, RunAppNotValidWorkingDir )
{
    const std::string working_dir( "./res1/" );
    ASSERT_FALSE( ConverterAppSimple( ).run( working_dir ) );
}
}  // namespace