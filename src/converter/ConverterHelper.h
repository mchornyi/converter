#pragma once

#include <memory>
#include <string>

namespace converter
{
class IConverter;
class ConverterTask;

class ConverterHelper
{
public:
    static std::unique_ptr< ConverterTask > make_converter_task_default( IConverter* );

    static std::unique_ptr< ConverterTask > make_lame_converter_task_dafault(
        IConverter*, const std::string& file_path_in, const std::string& file_path_out );
};

}  // namespace converter