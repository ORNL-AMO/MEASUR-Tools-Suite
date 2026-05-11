#include <emscripten/bind.h>

#include "steamModeler/SteamProperties.h"
#include "treasureHunt/CompressedAirReduction.h"
#include "treasureHunt/InsulatedPipeReduction.h"
#include "treasureHunt/InsulatedTankReduction.h"
#include "treasureHunt/NaturalGasReduction.h"
#include "treasureHunt/SteamReduction.h"
#include "vector"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(naturalGasReduction_class) {
    class_<FlowMeterMethodData>("FlowMeterMethodData").constructor<double>();

    class_<NaturalGasOtherMethodData>("NaturalGasOtherMethodData").constructor<double>();

    class_<AirMassFlowMeasuredData>("AirMassFlowMeasuredData").constructor<double, double>();

    class_<AirMassFlowNameplateData>("AirMassFlowNameplateData").constructor<double>();

    class_<AirMassFlowData>("AirMassFlowData")
        .constructor<bool, AirMassFlowMeasuredData, AirMassFlowNameplateData, double, double, double>();

    class_<WaterMassFlowData>("WaterMassFlowData").constructor<double, double, double, double>();

    class_<NaturalGasReductionInput>("NaturalGasReductionInput")
        .constructor<int, double, int, FlowMeterMethodData, NaturalGasOtherMethodData, AirMassFlowData,
                     WaterMassFlowData, int>();

    register_vector<NaturalGasReductionInput>("NaturalGasReductionInputV");

    class_<NaturalGasReduction::Output>("NaturalGasReductionOutput")
        .property("energyUse", &NaturalGasReduction::Output::energyUse)
        .property("energyCost", &NaturalGasReduction::Output::energyCost)
        .property("heatFlow", &NaturalGasReduction::Output::heatFlow)
        .property("totalFlow", &NaturalGasReduction::Output::totalFlow);

    class_<NaturalGasReduction>("NaturalGasReduction")
        .constructor<std::vector<NaturalGasReductionInput>>()
        .function("calculate", &NaturalGasReduction::calculate);
}

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

EMSCRIPTEN_BINDINGS(steamReduction_class) {
    class_<SteamFlowMeterMethodData>("SteamFlowMeterMethodData").constructor<double>();

    class_<SteamMassFlowNameplateData>("SteamMassFlowNameplateData").constructor<double>();

    class_<SteamMassFlowMeasuredData>("SteamMassFlowMeasuredData").constructor<double, double>();

    class_<SteamMassFlowMethodData>("SteamMassFlowMethodData")
        .constructor<bool, SteamMassFlowMeasuredData, SteamMassFlowNameplateData, double, double>();

    class_<SteamOffsheetMethodData>("SteamOffsheetMethodData").constructor<double>();

    class_<SteamReductionInput>("SteamReductionInput")
        .constructor<int, int, double, int, double, double, SteamFlowMeterMethodData, SteamMassFlowMethodData,
                     SteamMassFlowMethodData, SteamOffsheetMethodData, int, double,
                     SteamProperties::ThermodynamicQuantity, double, double>();

    register_vector<SteamReductionInput>("SteamReductionInputV");

    class_<SteamReduction::Output>("SteamReductionOutput")
        .property("steamUse", &SteamReduction::Output::steamUse)
        .property("energyUse", &SteamReduction::Output::energyUse)
        .property("energyCost", &SteamReduction::Output::energyCost);

    class_<SteamReduction>("SteamReduction")
        .constructor<std::vector<SteamReductionInput>>()
        .function("calculate", &SteamReduction::calculate);
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
