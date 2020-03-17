#ifdef CONFIG_FILE
#include CONFIG_FILE
#else
#define Converter_VERSION_MAJOR 1
#define Converter_VERSION_MINOR 0
#endif

#include "ConverterApp.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <string>

int
main( int argc, const char* argv[] )
{
    if ( argc < 2 )
    {
        std::cout << "Converter" << std::endl
                  << "Version " << Converter_VERSION_MAJOR << "." << Converter_VERSION_MINOR
                  << std::endl;
        
        std::cout << "Usage: " << argv[ 0 ] << " folder_path" << std::endl;
        
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