#include "vector"

#include "treasureHunt/ElectricityReduction.h"
#include "treasureHunt/NaturalGasReduction.h"
#include "treasureHunt/CompressedAirReduction.h"
#include "treasureHunt/CompressedAirPressureReduction.h"
#include "treasureHunt/WaterReduction.h"
#include "treasureHunt/SteamReduction.h"
#include "treasureHunt/InsulatedPipeReduction.h"
#include "treasureHunt/InsulatedTankReduction.h"
#include "steamModeler/SteamProperties.h"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(electricityReduction_class)
{
    class_<MultimeterData>("MultimeterData")
        .constructor<int, double, double, double>();

    class_<NameplateData>("NameplateData")
        .constructor<double, bool, double, double, double, double>();

    class_<PowerMeterData>("PowerMeterData")
        .constructor<double>();

    class_<OtherMethodData>("OtherMethodData")
        .constructor<double>();

    class_<ElectricityReductionInput>("ElectricityReductionInput")
        .constructor<int, double, int, MultimeterData, NameplateData, PowerMeterData, OtherMethodData, int>();

    register_vector<ElectricityReductionInput>("ElectricityReductionInputV");

    class_<ElectricityReduction::Output>("ElectricityReductionOutput")
        .property("energyUse", &ElectricityReduction::Output::energyUse)
        .property("energyCost", &ElectricityReduction::Output::energyCost)
        .property("power", &ElectricityReduction::Output::power);

    class_<ElectricityReduction>("ElectricityReduction")
        .constructor<std::vector<ElectricityReductionInput>>()
        .function("calculate", &ElectricityReduction::calculate);
}

EMSCRIPTEN_BINDINGS(naturalGasReduction_class)
{
    class_<FlowMeterMethodData>("FlowMeterMethodData")
        .constructor<double>();

    class_<NaturalGasOtherMethodData>("NaturalGasOtherMethodData")
        .constructor<double>();

    class_<AirMassFlowMeasuredData>("AirMassFlowMeasuredData")
        .constructor<double, double>();

    class_<AirMassFlowNameplateData>("AirMassFlowNameplateData")
        .constructor<double>();

    class_<AirMassFlowData>("AirMassFlowData")
        .constructor<bool, AirMassFlowMeasuredData, AirMassFlowNameplateData, double, double, double>();

    class_<WaterMassFlowData>("WaterMassFlowData")
        .constructor<double, double, double, double>();

    class_<NaturalGasReductionInput>("NaturalGasReductionInput")
        .constructor<int, double, int, FlowMeterMethodData, NaturalGasOtherMethodData, AirMassFlowData, WaterMassFlowData, int>();

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

EMSCRIPTEN_BINDINGS(compressedAirReduction_class)
{
    class_<CompressedAirFlowMeterMethodData>("CompressedAirFlowMeterMethodData")
        .constructor<double>();

    class_<BagMethodData>("BagMethodData")
        .constructor<double, double, double>();

    class_<PressureMethodData>("PressureMethodData")
        .constructor<int, int, double>();

    class_<CompressedAirOtherMethodData>("CompressedAirOtherMethodData")
        .constructor<double>();

    class_<CompressorElectricityData>("CompressorElectricityData")
        .constructor<double, double>();

    class_<CompressedAirReductionInput>("CompressedAirReductionInput")
        .constructor<int, int, double, int, CompressedAirFlowMeterMethodData, BagMethodData, PressureMethodData,
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

EMSCRIPTEN_BINDINGS(compressedAirPressureReduction_class)
{
    class_<CompressedAirPressureReductionInput>("CompressedAirPressureReductionInput")
        .constructor<bool, int, double, double, double, double, double, double>();

    register_vector<CompressedAirPressureReductionInput>("CompressedAirPressureReductionInputV");

    class_<CompressedAirPressureReduction::Output>("CompressedAirPressureReductionOutput")
        .property("energyUse", &CompressedAirPressureReduction::Output::energyUse)
        .property("energyCost", &CompressedAirPressureReduction::Output::energyCost);

    class_<CompressedAirPressureReduction>("CompressedAirPressureReduction")
        .constructor<std::vector<CompressedAirPressureReductionInput>>()
        .function("calculate", &CompressedAirPressureReduction::calculate);
}

EMSCRIPTEN_BINDINGS(waterReduction_class)
{
    class_<MeteredFlowMethodData>("MeteredFlowMethodData")
        .constructor<double>();

    class_<VolumeMeterMethodData>("VolumeMeterMethodData")
        .constructor<double, double, double>();

    class_<BucketMethodData>("BucketMethodData")
        .constructor<double, double>();

    class_<WaterOtherMethodData>("WaterOtherMethodData")
        .constructor<double>();

    class_<WaterReductionInput>("WaterReductionInput")
        .constructor<int, double, int, MeteredFlowMethodData, VolumeMeterMethodData, BucketMethodData, WaterOtherMethodData>();

    register_vector<WaterReductionInput>("WaterReductionInputV");

    class_<WaterReduction::Output>("WaterReductionOutput")
        .property("waterUse", &WaterReduction::Output::waterUse)
        .property("waterCost", &WaterReduction::Output::waterCost)
        .property("annualWaterSavings", &WaterReduction::Output::annualWaterSavings)
        .property("costSavings", &WaterReduction::Output::costSavings);

    class_<WaterReduction>("WaterReduction")
        .constructor<std::vector<WaterReductionInput>>()
        .function("calculate", &WaterReduction::calculate);
}

EMSCRIPTEN_BINDINGS(steamReduction_class)
{
    class_<SteamFlowMeterMethodData>("SteamFlowMeterMethodData")
        .constructor<double>();

    class_<SteamMassFlowNameplateData>("SteamMassFlowNameplateData")
        .constructor<double>();

    class_<SteamMassFlowMeasuredData>("SteamMassFlowMeasuredData")
        .constructor<double, double>();

    class_<SteamMassFlowMethodData>("SteamMassFlowMethodData")
        .constructor<bool, SteamMassFlowMeasuredData, SteamMassFlowNameplateData, double, double>();

    class_<SteamOffsheetMethodData>("SteamOffsheetMethodData")
        .constructor<double>();

    class_<SteamReductionInput>("SteamReductionInput")
        .constructor<int, int, double, int, double, double,
        SteamFlowMeterMethodData, SteamMassFlowMethodData, SteamMassFlowMethodData, SteamOffsheetMethodData, int,
        double, SteamProperties::ThermodynamicQuantity, double, double>();

    register_vector<SteamReductionInput>("SteamReductionInputV");

    class_<SteamReduction::Output>("SteamReductionOutput")
        .property("steamUse", &SteamReduction::Output::steamUse)
        .property("energyUse", &SteamReduction::Output::energyUse)
        .property("energyCost", &SteamReduction::Output::energyCost);

    class_<SteamReduction>("SteamReduction")
        .constructor<std::vector<SteamReductionInput>>()
        .function("calculate", &SteamReduction::calculate);
}

EMSCRIPTEN_BINDINGS(insulatedPipeReduction_class)
{
    class_<InsulatedPipeInput>("InsulatedPipeInput")
        .constructor<int, double, double, double, double, double, double, double, double, double, double, std::vector<double>, std::vector<double>>();

    class_<InsulatedPipeOutput>("InsulatedPipeOutput")
        .function("getHeatLength", &InsulatedPipeOutput::getHeatLength)
        .function("getAnnualHeatLoss", &InsulatedPipeOutput::getAnnualHeatLoss);

    class_<InsulatedPipeReduction>("InsulatedPipeReduction")
        .constructor<InsulatedPipeInput>()
        .function("calculate", &InsulatedPipeReduction::calculate);
}

EMSCRIPTEN_BINDINGS(insulatedTankReduction_class)
{
    class_<InsulatedTankInput>("InsulatedTankInput")
        .constructor<int, double, double, double, double, double, double, double, double, double, double, double, double>();

    class_<InsulatedTankOutput>("InsulatedTankOutput")
        .function("getHeatLoss", &InsulatedTankOutput::getHeatLoss)
        .function("getAnnualHeatLoss", &InsulatedTankOutput::getAnnualHeatLoss);

    class_<InsulatedTankReduction>("InsulatedTankReduction")
        .constructor<InsulatedTankInput>()
        .function("calculate", &InsulatedTankReduction::calculate);
}