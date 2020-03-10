#ifdef CONFIG_FILE
#include CONFIG_FILE
#else
#define Converter_VERSION_MAJOR 1
#define Converter_VERSION_MINOR 0
#endif

#include "TaskBase.h"

int
main( int argc, const char* argv[] )
{
    if ( argc < 2 )
    {
        std::cout << "Converter" << std::endl
                  << "Version " << Converter_VERSION_MAJOR << "." << Converter_VERSION_MINOR
                  << std::endl;
    }

    task_runner::TaskBase obj;

    return 1;
}