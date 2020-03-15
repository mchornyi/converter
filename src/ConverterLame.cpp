#include "ConverterLame.h"

#include <vector>
#include <sstream>

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
    gf = lame_init( ); // initialize libmp3lame
    if ( NULL == gf )
    {
        result = {task_runner::Error::FatalLameInit, "Fatal error during initialization\n"};
    }
    else
    {
        lame_main( gf, args.size( ) - 1, args.data( ) );
        lame_close( gf );
    }
    //

    for ( size_t i = 0; i < args.size( ); i++ )
    {
        delete[] args[ i ];
    }

    return result;
}

}  // namespace converter