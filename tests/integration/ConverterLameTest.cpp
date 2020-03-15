#include "gmock/gmock.h"

#include "ConverterLame.h"

#include <fstream>
#include <sstream>

namespace
{
using namespace converter;

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
    EXPECT_EQ( 12538, size );
    ASSERT_EQ( 0, remove( file_path_out.c_str( ) ) );
}
}  // namespace