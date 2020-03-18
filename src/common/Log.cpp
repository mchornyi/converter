#include "Log.h"

#include "common/common.h"

#include <stdarg.h>
#include <iomanip>
#include <sstream>
#include <thread>
#include <iostream>

namespace logger
{
void
log_message( const char* file, const char* function, int line, const char* format, ... )
{
    char buffer[ 256 ];
    va_list args;
    va_start( args, format );
    vsprintf_s( buffer, format, args );
    va_end( args );

    std::cout << format_message( file, function, line, buffer );
}

std::string
format_message( const char* file, const char* function, int line, const char* message )
{
    std::time_t log_time = std::time( nullptr );
    std::tm log_time_local = *std::localtime( &log_time );

    auto thread_id = std::this_thread::get_id( );

    std::string str_file( file );
    const std::string project_src("converter/");
    str_file = str_file.substr( str_file.find( project_src ) );

    std::stringstream ss;

    ss << "[" << std::put_time( &log_time_local, "%F %T" ) << "]"
       << "[tid:" << thread_id << "]"
       << "[..." << str_file << ":" << line << "(" << function << ")] " << message << "\n";

    return ss.str( );
}
}  // namespace logger