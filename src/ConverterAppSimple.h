#pragma once
#include <string>
#include <utility>
#include <vector>
#include <mutex>	

namespace converter
{
class ConverterAppSimple final
{
public:
    ConverterAppSimple( );

    ~ConverterAppSimple( );

    bool run( std::string working_dir );

private:
    void poll( );

private:
    std::vector< std::pair< std::string, std::string > > m_files_to_convert;
    std::mutex m_mtx;
};
}  // namespace converter