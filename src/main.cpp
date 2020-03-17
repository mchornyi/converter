#include "ConverterApp.h"

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

int
main( int argc, char* argv[] )
{
    // Check the number of parameters
    if ( argc < 2 )
    {
        std::cerr << "Usage: " << argv[ 0 ] << " folder_path" << std::endl;
        return 1;
    }

    std::string folder_path( argv[ 1 ] );

    struct stat info;

    if ( stat( folder_path.c_str( ), &info ) != 0 )
    {
        std::cerr << "Cannot access " << folder_path << "\n";
        return 1;
    }

    converter::ConverterApp app( folder_path );

    app.run( );

    return 0;
}
