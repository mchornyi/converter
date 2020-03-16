#include "gmock/gmock.h"

#include "ConverterHelper.h"
#include "ConverterLame.h"
#include "ConverterTask.h"
#include "common/Helpers.h"

#include "task-runner/TaskRunner.h"

#include <fstream>
#include <sstream>

namespace
{
using namespace converter;

const uint32_t expected_file_size_testcase_mp3( 12538 );

long long
file_size( const std::string& file_path )
{
    std::ifstream is( file_path, std::ifstream::binary );

    is.seekg( 0, is.end );

    const auto length = is.tellg( );

    is.close( );

    return length;
}

TEST( ConverterLameTest, DefaultConvert )
{
    ConverterLame converter_lame;

    const std::string file_path_in( "./res/testcase.wav" );
    const std::string file_path_out( "./res/testcase.mp3" );

    std::stringstream argumets;

    argumets << "lame -q4 -b160";  // good quality
    argumets << " " << file_path_in << " " << file_path_out;

    const auto convert_res = converter_lame.convert( argumets.str( ) );

    EXPECT_EQ( task_runner::ErrorInfo( ), convert_res );

    const auto size = file_size( file_path_out );
    EXPECT_EQ( expected_file_size_testcase_mp3, size );
    ASSERT_EQ( 0, remove( file_path_out.c_str( ) ) );
}

TEST( ConverterLameTest, ConvertTask )
{
    const std::string file_path_in( "./res/testcase.wav" );
    const std::string file_path_out( "./res/testcase.mp3" );

    ConverterLame converter_lame;

    auto converter_task( ConverterHelper::make_lame_converter_task_dafault(
        &converter_lame, file_path_in, file_path_out ) );

    ASSERT_TRUE( converter_task );

    const bool res = converter_task->run( );

    EXPECT_TRUE( res );

    const auto size = file_size( file_path_out );
    EXPECT_EQ( expected_file_size_testcase_mp3, size );
    ASSERT_EQ( 0, remove( file_path_out.c_str( ) ) );
}

TEST( ConverterLameTest, ConvertTaskNoInputFile )
{
    const std::string file_path_in( "./res/testcase1.wav" );
    const std::string file_path_out( "./res/testcase.mp3" );

    ConverterLame converter_lame;

    auto converter_task( ConverterHelper::make_lame_converter_task_dafault(
        &converter_lame, file_path_in, file_path_out ) );

    ASSERT_FALSE( converter_task );
}

TEST( ConverterLameTest, TaskRunner )
{
    const u_int8_t thread_count = 8;
    const uint32_t tasks_count = 100;

    task_runner::TaskRunner task_runner( thread_count );

    const std::string file_path_in( "./res/testcase.wav" );

    ConverterLame converter_lame;

    std::vector< std::unique_ptr< ConverterTask > > converter_tasks;

    converter_tasks.reserve( tasks_count );

    for ( uint32_t i = 0; i < tasks_count; ++i )
    {
        std::stringstream ss;
        ss << "./res/testcase" << i << ".mp3";

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
        ss << "./res/testcase" << i << ".mp3";

        const auto size = file_size( ss.str( ) );
        EXPECT_EQ( expected_file_size_testcase_mp3, size );
        EXPECT_EQ( 0, remove( ss.str( ).c_str( ) ) );
    }

    helpers::stop_task_runner( task_runner );
}

}  // namespace