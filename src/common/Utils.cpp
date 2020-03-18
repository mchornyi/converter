#include "Utils.h"

#if defined(_WIN32)
#include <Windows.h>
#include <io.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include <iostream>

namespace utils
{
std::vector< std::string >
list_files( const std::string& working_dir )
{
    std::vector< std::string > res;

<<<<<<< HEAD
    #if defined(_WIN32)
=======
    #ifdef WIN32
>>>>>>> WIN32 Adaptation
    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdata;
 
    std::string dir = working_dir;
    if(dir[dir.size()-1] == '\\' || dir[dir.size()-1] == '/') 
    {
        dir = dir.substr(0,dir.size()-1);
    }
 
    hFind = FindFirstFile(std::string(dir).append("\\*").c_str(), &fdata); 
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (strcmp(fdata.cFileName, ".") != 0 &&
                strcmp(fdata.cFileName, "..") != 0)
            {
                if (fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    continue;
                }
                else
                {
<<<<<<< HEAD
                    res.push_back(fdata.cFileName);
=======
					const std::string file_path = dir + "\\" + fdata.cFileName;
                    res.push_back(file_path);
					std::cout << "File to convert: " << file_path << "\n";
>>>>>>> WIN32 Adaptation
                }
            }
        }
        while (FindNextFile(hFind, &fdata) != 0);
    } else {
        std::cerr << "Can't access directory" << working_dir.c_str() << "\n";
        return {};
    }
 
    if (GetLastError() != ERROR_NO_MORE_FILES)
    {
        FindClose(hFind);
        std::cerr << "An error with reading directory: " << GetLastError() << std::endl;
    }
 
    FindClose(hFind);
    hFind = INVALID_HANDLE_VALUE;
    #else
    DIR* directory = opendir( working_dir.c_str( ) );
    if ( directory == nullptr )
    {
        std::cerr << "Can't access directory " << working_dir.c_str( ) << "\n";
        return {};
    }

    struct dirent* dir_ent;

    while ( ( dir_ent = readdir( directory ) ) != nullptr )
    {
        const std::string file_path = working_dir + "/" + dir_ent->d_name;
        res.emplace_back( file_path );
    }

    closedir( directory );
    #endif

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
<<<<<<< HEAD
    #if defined(_WIN32)
=======
    #ifdef WIN32
>>>>>>> WIN32 Adaptation
    return (_access_s( dir.c_str(), 0 ) == 0);
    #else
    struct stat info;
    return (stat( dir.c_str( ), &info ) == 0);
    #endif
}

}  // namespace utils