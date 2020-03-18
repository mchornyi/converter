#pragma once

#include <string>

namespace logger
{
std::string format_message( const char* file, const char* function, int line, const char* message );
void log_message( const char* file, const char* function, int line, const char* format, ... );
}  // namespace logger

#define FORMAT_LOG( msg ) logger::format_message( __FILE__, __FUNCTION__, __LINE__, msg )
#define LOG( msg, ... ) logger::log_message( __FILE__, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__ )