#include <vector>

#include <emscripten/bind.h>

#include "compressedAir/AirSystemCapacity.h"
#include "compressedAir/AirVelocity.h"
#include "compressedAir/DecibelsMethod.h"
#include "compressedAir/PipeData.h"

using namespace emscripten;

// airSystemCapacity
EMSCRIPTEN_BINDINGS(airSystemCapacity) {
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

    class_<AirSystemCapacity>("AirSystemCapacity")
        .constructor<PipeData, std::vector<double>>()
        .function("calculate", &AirSystemCapacity::calculate);

    class_<AirSystemCapacity::Output>("AirSystemCapacityOutput")
        .constructor<double, std::vector<double>, double, double, PipeData>()
        .property("totalPipeVolume", &AirSystemCapacity::Output::totalPipeVolume)
        .property("totalReceiverVolume", &AirSystemCapacity::Output::totalReceiverVol)
        .property("totalCapacityOfCompressedAirSystem", &AirSystemCapacity::Output::totalCapacityOfCompressedAirSystem)
        .property("receiverCapacities", &AirSystemCapacity::Output::receiverCapacities)
        .property("pipeLengths", &AirSystemCapacity::Output::pipeLengths);
}

// airVelocity
EMSCRIPTEN_BINDINGS(airVelocity) {
    class_<AirVelocity>("AirVelocity")
        .constructor<double, double, double>()
        .function("calculate", &AirVelocity::calculate);
}

// decibelsMethod
EMSCRIPTEN_BINDINGS(decibelsMethod) {
    class_<DecibelsMethod>("DecibelsMethod")
        .constructor<double, double, double, double, double, double, double, double, double, double, double>()
        .function("calculate", &DecibelsMethod::calculate);

    class_<DecibelsMethod::Output>("DecibelsMethodOutput")
        .constructor<double, double>()
        .property("leakRateEstimate", &DecibelsMethod::Output::leakRateEstimate)
        .property("annualConsumption", &DecibelsMethod::Output::annualConsumption);
}