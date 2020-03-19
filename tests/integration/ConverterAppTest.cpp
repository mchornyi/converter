#include "gtest/gtest.h"

#include "ConverterApp.h"
#include "common/Helpers.h"
#include "common/Utils.h"

#ifdef WIN32
const std::string g_working_dir = utils::exe_path( ) + "\\..\\res\\";
#else
const std::string g_working_dir( "./res/" );
#endif
namespace
{
using namespace converter;
const uint32_t expected_file_size_testcase_mp3( 12538 );
const uint32_t expected_file_size_big_test_case_mp3( 1181257 );

TEST( ConverterAppTest, RunApp )
{
    ConverterApp app( g_working_dir );

    EXPECT_TRUE( app.run( ) );

    // Check the files and cleanup

    const std::string out_file_testcase_mp3 = g_working_dir + "testcase.mp3";
    const std::string out_file_big_test_case_mp3 = g_working_dir + "big-test-case.mp3";

    auto size = helpers::file_size( out_file_testcase_mp3 );
    EXPECT_EQ( expected_file_size_testcase_mp3, size );
    EXPECT_EQ( 0, remove( out_file_testcase_mp3.c_str( ) ) );

    size = helpers::file_size( out_file_big_test_case_mp3 );
    EXPECT_EQ( expected_file_size_big_test_case_mp3, size );
    EXPECT_EQ( 0, remove( out_file_big_test_case_mp3.c_str( ) ) );
}

TEST( ConverterAppTest, RunAppNotValidWorkingDir )
{
    const std::string working_dir( "./res1/" );
    ConverterApp app( working_dir );

    ASSERT_FALSE( app.run( ) );
}
}  // namespace