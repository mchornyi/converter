#include "Utils.h"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace utils
{
std::vector< std::string >
list_files( const std::string& working_dir )
{
    std::vector< std::string > res;

    DIR* directory = opendir( working_dir.c_str( ) );
    if ( directory == nullptr )
    {
        return {};
    }

    struct dirent* dir_ent;

    while ( ( dir_ent = readdir( directory ) ) != nullptr )
    {
        const std::string file_path = working_dir + "/" + dir_ent->d_name;
        res.emplace_back( file_path );
    }

    closedir( directory );

    return res;
}

std::vector< std::string >
filter_list_files( const std::vector< std::string >& files, const std::string& filter )
{
    std::vector< std::string > res;
    for ( const auto& item : files )
    {
        const auto pos = item.find( filter );

        if ( pos != std::string::npos && ( ( item.size( ) - pos ) == 4 ) )
        {
            res.emplace_back( item );
        }
    }

    return res;
}

bool
dir_exist( const std::string& dir )
{
    struct stat info;
    return (stat( dir.c_str( ), &info ) == 0);
}

}  // namespace utils