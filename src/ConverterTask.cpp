
#include "ConverterTask.h"
#include "IConverter.h"

namespace converter
{
struct ConverterTask::Impl
{
    Impl( converter::IConverter* _converter, std::string _arguments )
        : converter( _converter )
        , arguments( std::move( _arguments ) )
    {
    }
    converter::IConverter* converter;
    std::string arguments;
};

ConverterTask::ConverterTask( IConverter* converter, std::string arguments )
    : m_pimpl( new Impl( converter, std::move( arguments ) ) )
{
}

ConverterTask::~ConverterTask( )
{
}

task_runner::ErrorInfo
ConverterTask::run_internal( )
{
    if ( m_pimpl->converter == nullptr )
    {
        return {task_runner::Error::InvalidArgument, "Converter is not initialized"};
    }

    return m_pimpl->converter->convert( "" );
}

void
ConverterTask::stop_internal( )
{
}

}  // namespace converter