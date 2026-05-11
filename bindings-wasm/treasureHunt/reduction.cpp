#include <emscripten/bind.h>

#include "treasureHunt/CompressedAirReduction.h"
#include "treasureHunt/InsulatedPipeReduction.h"
#include "treasureHunt/InsulatedTankReduction.h"
#include "vector"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(compressedAirReduction_class) {
    class_<CompressedAirFlowMeterMethodData>("CompressedAirFlowMeterMethodData").constructor<double>();

    class_<BagMethodData>("BagMethodData").constructor<double, double, double>(); // legacy only

    class_<PressureMethodData>("PressureMethodData").constructor<int, int, double>();

    class_<CompressedAirOtherMethodData>("CompressedAirOtherMethodData").constructor<double>();

    class_<CompressorElectricityData>("CompressorElectricityData").constructor<double, double>();

    class_<CompressedAirReductionInput>("CompressedAirReductionInput")
        .constructor<int, int, double, int, CompressedAirFlowMeterMethodData, BagMethod, PressureMethodData,
                     CompressedAirOtherMethodData, CompressorElectricityData, int>();

    register_vector<CompressedAirReductionInput>("CompressedAirReductionInputV");

    class_<CompressedAirReduction::Output>("CompressedAirReductionOutput")
        .property("energyUse", &CompressedAirReduction::Output::energyUse)
        .property("energyCost", &CompressedAirReduction::Output::energyCost)
        .property("flowRate", &CompressedAirReduction::Output::flowRate)
        .property("singleNozzleFlowRate", &CompressedAirReduction::Output::singleNozzleFlowRate)
        .property("consumption", &CompressedAirReduction::Output::consumption);

    class_<CompressedAirReduction>("CompressedAirReduction")
        .constructor<std::vector<CompressedAirReductionInput>>()
        .function("calculate", &CompressedAirReduction::calculate);
}

EMSCRIPTEN_BINDINGS(insulatedPipeReduction_class) {
    class_<InsulatedPipeInput>("InsulatedPipeInput")
        .constructor<int, double, double, double, double, double, double, double, double, double, double,
                     std::vector<double>, std::vector<double>>();

    class_<InsulatedPipeOutput>("InsulatedPipeOutput")
        .function("getHeatLength", &InsulatedPipeOutput::getHeatLength)
        .function("getAnnualHeatLoss", &InsulatedPipeOutput::getAnnualHeatLoss);

    class_<InsulatedPipeReduction>("InsulatedPipeReduction")
        .constructor<InsulatedPipeInput>()
        .function("calculate", &InsulatedPipeReduction::calculate);
}

EMSCRIPTEN_BINDINGS(insulatedTankReduction_class) {
    class_<InsulatedTankInput>("InsulatedTankInput")
        .constructor<int, double, double, double, double, double, double, double, double, double, double, double,
                     double>();

    class_<InsulatedTankOutput>("InsulatedTankOutput")
        .function("getHeatLoss", &InsulatedTankOutput::getHeatLoss)
        .function("getAnnualHeatLoss", &InsulatedTankOutput::getAnnualHeatLoss);

    class_<InsulatedTankReduction>("InsulatedTankReduction")
        .constructor<InsulatedTankInput>()
        .function("calculate", &InsulatedTankReduction::calculate);
}
