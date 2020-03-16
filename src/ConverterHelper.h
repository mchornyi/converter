#pragma once

#include "ConverterTask.h"

namespace converter
{
class IConverter;

class ConverterHelper
{
public:
    static std::unique_ptr< ConverterTask > make_lame_converter_task_dafault(
        IConverter*, const std::string& file_path_in, const std::string& file_path_out );
};

}  // namespace converter