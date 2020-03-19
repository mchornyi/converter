#include "ConverterLame.h"

#include <iostream>
#include <sstream>
#include <vector>

#include "frontend/console.h"
#include "frontend/main.h"

namespace converter
{
struct ConverterLame::Impl
{
};

ConverterLame::ConverterLame( )
{
}

ConverterLame::~ConverterLame( )
{
}

task_runner::ErrorInfo
ConverterLame::convert( std::string argumets )
{
    task_runner::ErrorInfo result;

    std::vector< char* > args;
    std::istringstream iss( argumets );

    std::string item;
    while ( iss >> item )
    {
        char* arg = new char[ item.size( ) + 1 ];
        copy( item.begin( ), item.end( ), arg );
        arg[ item.size( ) ] = '\0';
        args.push_back( arg );
    }
    args.push_back( 0 );

    //
    lame_t gf;
    gf = lame_init( );  // initialize libmp3lame
    if ( NULL == gf )
    {
        result = {task_runner::Error::FatalLameInit, "Fatal error during initialization\n"};
    }
    else
    {
        frontend_open_console( );
        std::cout << "Run Lame with the following arguments: " << argumets << "\n";
        lame_main( gf, args.size( ) - 1, args.data( ) );
        lame_close( gf );
        frontend_close_console( );
    }
    //

    for ( size_t i = 0; i < args.size( ); i++ )
    {
        delete[] args[ i ];
    }

    return result;
}

void
ConverterLame::convert( const std::string& file_path_in, const std::string& file_path_out )
{
    std::stringstream argumets;

    argumets << "lame -q4 -b160";  // good quality
    argumets << " " << file_path_in << " " << file_path_out;

    convert( argumets.str( ) );
}

}  // namespace converter