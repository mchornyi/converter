#include "gtest/gtest.h"

#include "common/Helpers.h"
#include "common/Utils.h"
#include "converter/ConverterHelper.h"
#include "converter/ConverterLame.h"
#include "converter/ConverterTask.h"

#include "task-runner/TaskRunner.h"

#include <sstream>

#ifdef WIN32
const std::string g_working_dir = utils::exe_path( ) + "\\..\\res\\";
#else
const std::string g_working_dir( "./res/" );
#endif

namespace
{
using namespace converter;

const uint32_t expected_file_size_testcase_mp3( 12538 );

const std::string file_path_in = g_working_dir + "testcase.wav";
const std::string file_path_out = g_working_dir + "testcase.mp3";

TEST( ConverterLameTest, DefaultConvert )
{
    ConverterLame converter_lame;

    std::stringstream argumets;

    argumets << "lame -q4 -b160";  // good quality
    argumets << " " << file_path_in << " " << file_path_out;

    const auto convert_res = converter_lame.convert( argumets.str( ) );

    EXPECT_EQ( task_runner::ErrorInfo( ), convert_res );

    const auto size = helpers::file_size( file_path_out );
    EXPECT_EQ( expected_file_size_testcase_mp3, size );
    ASSERT_EQ( 0, remove( file_path_out.c_str( ) ) );
}

TEST( ConverterLameTest, ConvertTask )
{
    ConverterLame converter_lame;

    auto converter_task( ConverterHelper::make_lame_converter_task_dafault(
        &converter_lame, file_path_in, file_path_out ) );

    ASSERT_TRUE( converter_task );

    const bool res = converter_task->run( );

    EXPECT_TRUE( res );

    const auto size = helpers::file_size( file_path_out );
    EXPECT_EQ( expected_file_size_testcase_mp3, size );
    ASSERT_EQ( 0, remove( file_path_out.c_str( ) ) );
}

TEST( ConverterLameTest, ConvertTaskNoInputFile )
{
    const std::string file_path_in_not_valid = g_working_dir + "no-existed-file.wav";

    ConverterLame converter_lame;

    auto converter_task( ConverterHelper::make_lame_converter_task_dafault(
        &converter_lame, file_path_in_not_valid, file_path_out ) );

    ASSERT_FALSE( converter_task );
}

TEST( ConverterLameTest, TaskRunner )
{
    const u_int8_t thread_count = 2;
    const uint32_t tasks_count = 10;

    task_runner::TaskRunner task_runner( thread_count );

    ConverterLame converter_lame;

    std::vector< std::unique_ptr< ConverterTask > > converter_tasks;

    converter_tasks.reserve( tasks_count );

    for ( uint32_t i = 0; i < tasks_count; ++i )
    {
        std::stringstream ss;
        ss << g_working_dir << "testcase" << i << ".mp3";

        converter_tasks.emplace_back( ConverterHelper::make_lame_converter_task_dafault(
            &converter_lame, file_path_in, ss.str( ) ) );
    }

    // Add task to the runner
    for ( auto& task : converter_tasks )
    {
        ASSERT_TRUE( task_runner.add_task( task.get( ) ) );
    }

    // Wait each task for completion
    for ( auto& task : converter_tasks )
    {
        auto task_future = task->get_future( );
        const std::chrono::milliseconds span( 1 * 60 * 1000 );
        auto result = task_future.wait_for( span );
        EXPECT_EQ( std::future_status::ready, result );
    }

    // Check the files and cleanup
    for ( uint32_t i = 0; i < tasks_count; ++i )
    {
        std::stringstream ss;
        ss << g_working_dir << "testcase" << i << ".mp3";

        const auto size = helpers::file_size( ss.str( ) );
        EXPECT_EQ( expected_file_size_testcase_mp3, size );
        EXPECT_EQ( 0, remove( ss.str( ).c_str( ) ) );
    }

    helpers::stop_task_runner( task_runner );
}

}  // namespace