#include "gmock/gmock.h"

#include "ConverterLame.h"

namespace
{
using namespace converter;

TEST( ConverterLameTest, DefaultConvert )
{
    ConverterLame converter_lame;
    //converter_lame.convert("lame -q0 -b128 ./res/testcase.wav ./res/testcase.mp3");
    converter_lame.convert("lame -q0 -b128 testcase.wav testcase.mp3");
}
}  // namespace