#pragma once

#include "IConverter.h"

#include <memory>

namespace converter
{
class ConverterLame final: public IConverter
{
public:
    ConverterLame( );
    ~ConverterLame( );

    task_runner::ErrorInfo convert( std::string argumets ) override;

    void convert( const std::string& file_in, const std::string& file_out );

private:
    struct Impl;
    std::unique_ptr< Impl > m_pimpl;
};
}  // namespace converter