#include <emscripten/bind.h>

#include "compressedAir/pipe_data.h"

using namespace emscripten;
using pipe_data::PipeData;

EMSCRIPTEN_BINDINGS(pipe_data) {
    class_<PipeData>("PipeData")
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double,
                     double, double, double, double, double, double, double, double>()
        .property("oneHalf", &PipeData::oneHalf)
        .property("threeFourths", &PipeData::threeFourths)
        .property("one", &PipeData::one)
        .property("oneAndOneFourth", &PipeData::oneAndOneFourth)
        .property("oneAndOneHalf", &PipeData::oneAndOneHalf)
        .property("two", &PipeData::two)
        .property("twoAndOneHalf", &PipeData::twoAndOneHalf)
        .property("three", &PipeData::three)
        .property("threeAndOneHalf", &PipeData::threeAndOneHalf)
        .property("four", &PipeData::four)
        .property("five", &PipeData::five)
        .property("six", &PipeData::six)
        .property("eight", &PipeData::eight)
        .property("ten", &PipeData::ten)
        .property("twelve", &PipeData::twelve)
        .property("fourteen", &PipeData::fourteen)
        .property("sixteen", &PipeData::sixteen)
        .property("eighteen", &PipeData::eighteen)
        .property("twenty", &PipeData::twenty)
        .property("twentyFour", &PipeData::twentyFour);
}
