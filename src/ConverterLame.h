#pragma once

#include "IConverter.h"

#include <memory>

namespace converter
{
class ConverterLame : public IConverter
{
public:
    ConverterLame( );
    ~ConverterLame( );

    task_runner::ErrorInfo convert( std::string argumets ) override;

private:
    struct Impl;
    std::unique_ptr< Impl > m_pimpl;
};
}  // namespace converter