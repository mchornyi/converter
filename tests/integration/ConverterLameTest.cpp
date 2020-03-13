#include "gmock/gmock.h"

#include "ConverterLame.h"

namespace
{
using namespace converter;

TEST( ConverterLameTest, DefaultConvert )
{
    ConverterLame converter_lame;
    converter_lame.convert("");
}
}  // namespace