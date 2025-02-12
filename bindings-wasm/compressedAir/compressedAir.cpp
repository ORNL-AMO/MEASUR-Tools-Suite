#include "compressedAir/AirSystemCapacity.h"
#include "compressedAir/AirVelocity.h"
#include "compressedAir/BagMethod.h"
#include "compressedAir/DecibelsMethod.h"
#include "compressedAir/EstimateMethod.h"
#include "compressedAir/OperatingCost.h"
#include "compressedAir/OrificeMethod.h"
#include "compressedAir/PipeData.h"
#include "compressedAir/PipeSizing.h"
#include "compressedAir/PneumaticAirRequirement.h"
#include "compressedAir/PneumaticValve.h"
#include "compressedAir/ReceiverTank.h"
#include <vector>

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(compressedAir_enums)
{
    enum_<ReceiverTank::Method>("ReceiverTankMethod")
        .value("General", ReceiverTank::Method::General)
        .value("DedicatedStorage", ReceiverTank::Method::DedicatedStorage)
        .value("MeteredStorage", ReceiverTank::Method::MeteredStorage)
        .value("BridgingCompressorReactionDelay", ReceiverTank::Method::BridgingCompressorReactionDelay);

    enum_<PneumaticAirRequirement::PistonType>("PistonType")
        .value("SingleActing", PneumaticAirRequirement::PistonType::SingleActing)
        .value("DoubleActing", PneumaticAirRequirement::PistonType::DoubleActing);
}

// pneumaticAirRequirement
EMSCRIPTEN_BINDINGS(pneumaticAirRequirement)
{
    class_<PneumaticAirRequirement>("PneumaticAirRequirement")
        .constructor()
        .constructor<PneumaticAirRequirement::PistonType, double, double, double, double>()
        .constructor<PneumaticAirRequirement::PistonType, double, double, double, double, double>()
        .function("calculate", &PneumaticAirRequirement::calculate);

    class_<PneumaticAirRequirement::Output>("PneumaticAirRequirementOutput")
        .constructor<double, double, double>()
        .property("volumeAirIntakePiston", &PneumaticAirRequirement::Output::volumeAirIntakePiston)
        .property("compressionRatio", &PneumaticAirRequirement::Output::compressionRatio)
        .property("airRequirementPneumaticCylinder", &PneumaticAirRequirement::Output::airRequirementPneumaticCylinder);
}

// usableAirCapacity
// receiverTank
EMSCRIPTEN_BINDINGS(receiverTank)
{
    class_<ReceiverTank>("ReceiverTank")
        .constructor()
        .constructor<ReceiverTank::Method, double, double, double>()
        .constructor<ReceiverTank::Method, double, double, double, double, double>()
        .constructor<ReceiverTank::Method, double, double, double, double, double, double>()
        .function("calculateSize", &ReceiverTank::calculateSize)
        .function("calculateUsableCapacity", &ReceiverTank::calculateUsableCapacity);
}

// operatingCost
EMSCRIPTEN_BINDINGS(operatingCost)
{
    class_<OperatingCost>("OperatingCost")
        .constructor<double, double, double, double, double, double, double>()
        .function("calculate", &OperatingCost::calculate);

    class_<OperatingCost::Output>("OperatingCostOutput")
        .constructor<double, double, double, double>()
        .property("runTimeUnloaded", &OperatingCost::Output::runTimeUnloaded)
        .property("costForLoaded", &OperatingCost::Output::costForLoaded)
        .property("costForUnloaded", &OperatingCost::Output::costForUnloaded)
        .property("totalAnnualCost", &OperatingCost::Output::totalAnnualCost);
}

// airSystemCapacity
EMSCRIPTEN_BINDINGS(airSystemCapacity)
{
    class_<PipeData>("PipeData")
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double>()
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
EMSCRIPTEN_BINDINGS(airVelocity)
{
    class_<AirVelocity>("AirVelocity")
        .constructor<double, double, double>()
        .function("calculate", &AirVelocity::calculate);
}

// pipeSizing
EMSCRIPTEN_BINDINGS(pipeSizing)
{
    class_<PipeSizing>("PipeSizing")
        .constructor<double, double, double, double>()
        .function("calculate", &PipeSizing::calculate);

    class_<PipeSizing::Output>("PipeSizingOutput")
        .constructor<double, double>()
        .property("crossSectionalArea", &PipeSizing::Output::crossSectionalArea)
        .property("pipeDiameter", &PipeSizing::Output::pipeDiameter);
}

// pneumaticValve
EMSCRIPTEN_BINDINGS(pneumaticValve)
{
    class_<PneumaticValve>("PneumaticValve")
        .constructor<double, double>()
        .constructor<double, double, double>()
        .function("calculate", &PneumaticValve::calculate);
}

// bagMethod
EMSCRIPTEN_BINDINGS(bagMethod)
{
    class_<BagMethod>("BagMethod")
        .constructor<double, double, double, double, double>()
        .function("calculate", &BagMethod::calculate);

    class_<BagMethod::Output>("BagMethodOutput")
        .constructor<double, double>()
        .property("flowRate", &BagMethod::Output::flowRate)
        .property("annualConsumption", &BagMethod::Output::annualConsumption);
}

// estimateMethod
EMSCRIPTEN_BINDINGS(estimateMethod)
{
    class_<EstimateMethod>("EstimateMethod")
        .constructor<double, double>()
        .function("calculate", &EstimateMethod::calculate);

    class_<EstimateMethod::Output>("EstimateMethodOutput")
        .constructor<double>()
        .property("annualConsumption", &EstimateMethod::Output::annualConsumption);
}

// decibelsMethod
EMSCRIPTEN_BINDINGS(decibelsMethod)
{
    class_<DecibelsMethod>("DecibelsMethod")
        .constructor<double, double, double, double, double, double, double, double, double, double, double>()
        .function("calculate", &DecibelsMethod::calculate);

    class_<DecibelsMethod::Output>("DecibelsMethodOutput")
        .constructor<double, double>()
        .property("leakRateEstimate", &DecibelsMethod::Output::leakRateEstimate)
        .property("annualConsumption", &DecibelsMethod::Output::annualConsumption);
}

// orificeMethod
EMSCRIPTEN_BINDINGS(orificeMethod)
{
    class_<OrificeMethod>("OrificeMethod")
        .constructor<double, double, double, double, double, double, double>()
        .function("calculate", &OrificeMethod::calculate);

    class_<OrificeMethod::Output>("OrificeMethodOutput")
        .constructor<double, double, double, double, double, double, double>()
        .property("standardDensity", &OrificeMethod::Output::standardDensity)
        .property("sonicDensity", &OrificeMethod::Output::sonicDensity)
        .property("leakVelocity", &OrificeMethod::Output::leakVelocity)
        .property("leakRateLBMmin", &OrificeMethod::Output::leakRateLBMmin)
        .property("leakRateScfm", &OrificeMethod::Output::leakRateScfm)
        .property("leakRateEstimate", &OrificeMethod::Output::leakRateEstimate)
        .property("annualConsumption", &OrificeMethod::Output::annualConsumption);
}