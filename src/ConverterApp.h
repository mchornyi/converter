#pragma once

#include <string>
#include <memory>

namespace converter
{
class ConverterApp final
{
public:
    ConverterApp( std::string path_folder );
    ~ConverterApp( );

    bool run();

private:
    struct Impl;
    std::unique_ptr< Impl > m_pimpl;
};
}  // namespace converter