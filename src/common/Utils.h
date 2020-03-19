#pragma once

#include <string>
#include <vector>

namespace utils
{
#ifdef WIN32
std::string exe_path( );
#endif

std::vector< std::string > list_files( const std::string& working_dir );

std::vector< std::string > filter_list_files( const std::vector< std::string >& files,
                                              const std::string& filter );

bool dir_exist( const std::string& dir );

}  // namespace utils
