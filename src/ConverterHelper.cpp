#include "ConverterHelper.h"

#include "common/Log.h"

#include <fstream>
#include <sstream>

namespace
{
bool
file_exists( const std::string& file_path )
{
    if ( file_path.empty( ) )
    {
        return false;
    }

    std::ifstream f( file_path.c_str( ) );
    return f.good( );
}
}  // namespace

namespace converter
{
std::unique_ptr< ConverterTask >
ConverterHelper::make_converter_task_dafault( IConverter* converter,
                                              const std::string& file_path_in,
                                              const std::string& file_path_out )
{
    if ( converter == nullptr || !file_exists( file_path_in ) )
    {
        LOG( "converter == nullptr || !file_exists( file_path_in )" );
        return {};
    }

    std::stringstream argumets;

    argumets << "lame -q4 -b160";  // good quality
    argumets << " " << file_path_in << " " << file_path_out;

    return std::unique_ptr< ConverterTask >( new ConverterTask( converter, argumets.str( ) ) );
}

}  // namespace converter