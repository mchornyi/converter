#ifdef CONFIG_FILE
#include CONFIG_FILE
#else
#define Converter_VERSION_MAJOR 1
#define Converter_VERSION_MINOR 0
#endif

//#include "ConverterApp.h"
#include "ConverterAppSimple.h"
#include "common/Utils.h"

#include <iostream>

int
main( int argc, const char* argv[] )
{
    if ( argc < 2 )
    {
        std::cout << "Converter" << std::endl
                  << "Version " << Converter_VERSION_MAJOR << "." << Converter_VERSION_MINOR
                  << std::endl;

        std::cout << "Usage: " << argv[ 0 ] << " directory_path" << std::endl;

        return 1;
    }

    std::string directory_path( argv[ 1 ] );

    // converter::ConverterApp app( directory_path );
    // app.run( );

    converter::ConverterAppSimple( ).run( directory_path );

    return 0;
}