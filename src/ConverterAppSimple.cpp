#include "ConverterAppSimple.h"

#include "ConverterLame.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <vector>

#include <dirent.h>

namespace
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

}  // namespace

namespace converter
{
ConverterAppSimple::ConverterAppSimple( )
{
}

ConverterAppSimple::~ConverterAppSimple( )
{
}

bool
ConverterAppSimple::run( std::string working_dir )
{
    struct stat info;

    if ( stat( working_dir.c_str( ), &info ) != 0 )
    {
        std::cerr << "Cannot access " << working_dir << "\n";
        return false;
    }

    const std::string wav_str( ".wav" );
    const std::string mp3_str( ".mp3" );

    const auto files = list_files( working_dir );

    const auto files_wav = filter_list_files( files, wav_str );

    // Prepare input/output files
    for ( const auto& file_wav : files_wav )
    {
        std::string file_path_out = file_wav;
        auto pos = file_path_out.find( wav_str );
        if ( pos == std::string::npos )
        {
            continue;
        }

        file_path_out.replace( pos, mp3_str.size( ), mp3_str );

        m_files_to_convert.emplace_back( std::make_pair( file_wav, file_path_out ) );
    }

    if ( m_files_to_convert.empty( ) )
    {
        return false;
    }

    // Start thread pool
    auto threads_number = std::thread::hardware_concurrency( );
    if ( threads_number <= 1 )
    {
        threads_number = 2;
    }

    std::vector< std::thread > thread_pool;
    thread_pool.reserve( threads_number );
    for ( size_t i = 0; i < threads_number; i++ )
    {
        thread_pool.push_back( std::thread( &ConverterAppSimple::poll, this ) );
    }

    // Wait for thread to finish
    for ( auto& thread : thread_pool )
    {
        thread.join( );
    }

    return true;
}

void
ConverterAppSimple::poll( )
{
    ConverterLame lame;

    while ( true )
    {
        std::pair< std::string, std::string > file_to_convert;

        {  // lock_guard scope
            std::lock_guard< std::mutex > lock( m_mtx );
            if ( m_files_to_convert.empty( ) )
            {
                break;
            }

            std::swap( file_to_convert, m_files_to_convert.back( ) );
            m_files_to_convert.pop_back( );
        }

        lame.convert( file_to_convert.first, file_to_convert.second );
    }
}

}  // namespace converter