#pragma once

#include <string>

namespace converter
{
class IConverter
{
protected:
    virtual ~IConverter( ) = default;

public:
    virtual task_runner::ErrorInfo convert( std::string argumets ) = 0;
};
}  // namespace converter