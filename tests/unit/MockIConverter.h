#pragma once

#include "gmock/gmock.h"
#include "converter/IConverter.h"

namespace task_mocks
{
class MockIConverter : public converter::IConverter
{
public:
    MOCK_METHOD( task_runner::ErrorInfo, convert, ( std::string ), ( override ) );
};
}  // namespace task_mocks