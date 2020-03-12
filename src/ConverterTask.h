#pragma once

#include "task-runner/TaskBase.h"

namespace converter
{
class IConverter;

class ConverterTask final : public task_runner::TaskBase
{
public:
    ConverterTask( converter::IConverter* converter, std::string arguments );

    ~ConverterTask( );

private:
    virtual task_runner::ErrorInfo run_internal( ) override;

    virtual void stop_internal( ) override;

private:
    struct Impl;
    std::unique_ptr< Impl > m_pimpl;
};
}  // namespace converter