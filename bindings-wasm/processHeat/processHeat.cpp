#include <string>

#include <emscripten/bind.h>

#include "processHeat/AirHeatingUsingExhaust.h"
#include "processHeat/AirWaterCoolingUsingFlue.h"
#include "processHeat/WaterHeatingUsingSteam.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(processHeat_class) {
    using namespace gas_composition;

    class_<AirHeatingUsingExhaust::Output>("AirHeatingUsingExhaustOutput")
        .property("hxColdAir", &AirHeatingUsingExhaust::Output::hxColdAir)
        .property("hxOutletExhaust", &AirHeatingUsingExhaust::Output::hxOutletExhaust)
        .property("energySavings", &AirHeatingUsingExhaust::Output::energySavings)
        .property("heatCapacityFlue", &AirHeatingUsingExhaust::Output::heatCapacityFlue)
        .property("heatCapacityAir", &AirHeatingUsingExhaust::Output::heatCapacityAir);

    class_<WaterHeatingUsingSteam::Output>("WaterHeatingUsingSteamOutput")
        .property("tempWaterOut", &WaterHeatingUsingSteam::Output::tempWaterOut)
        .property("bpTempWaterOut", &WaterHeatingUsingSteam::Output::bpTempWaterOut)
        .property("bpTempWarningFlag", &WaterHeatingUsingSteam::Output::bpTempWarningFlag)
        .property("flowByPassSteam", &WaterHeatingUsingSteam::Output::flowByPassSteam)
        .property("enthalpySteamIn", &WaterHeatingUsingSteam::Output::enthalpySteamIn)
        .property("enthalpySteamOut", &WaterHeatingUsingSteam::Output::enthalpySteamOut)
        .property("enthalpyMakeUpWater", &WaterHeatingUsingSteam::Output::enthalpyMakeUpWater)
        .property("energySavedDWH", &WaterHeatingUsingSteam::Output::energySavedDWH)
        .property("energySavedBoiler", &WaterHeatingUsingSteam::Output::energySavedBoiler)
        .property("waterSaved", &WaterHeatingUsingSteam::Output::waterSaved)
        .property("heatGainRate", &WaterHeatingUsingSteam::Output::heatGainRate);

    class_<AirWaterCoolingUsingFlue::Output>("AirWaterCoolingUsingFlueOutput")
        .property("excessAir", &AirWaterCoolingUsingFlue::Output::excessAir)
        .property("flowFlueGas", &AirWaterCoolingUsingFlue::Output::flowFlueGas)
        .property("specHeat", &AirWaterCoolingUsingFlue::Output::specHeat)
        .property("fracCondensed", &AirWaterCoolingUsingFlue::Output::fracCondensed)
        .property("effThermal", &AirWaterCoolingUsingFlue::Output::effThermal)
        .property("effThermalLH", &AirWaterCoolingUsingFlue::Output::effThermalLH)
        .property("effLH", &AirWaterCoolingUsingFlue::Output::effLH)
        .property("heatRecovery", &AirWaterCoolingUsingFlue::Output::heatRecovery)
        .property("sensibleHeatRecovery", &AirWaterCoolingUsingFlue::Output::sensibleHeatRecovery);

    class_<AirHeatingUsingExhaust>("AirHeatingUsingExhaust")
        .constructor<GasComposition>()
        .constructor<double, bool>()
        .function("calculate", &AirHeatingUsingExhaust::calculate);

    class_<WaterHeatingUsingSteam>("WaterHeatingUsingSteam")
        .constructor<>()
        .function("calculate", &WaterHeatingUsingSteam::calculate);

    class_<AirWaterCoolingUsingFlue>("AirWaterCoolingUsingFlue")
        .constructor<>()
        .function("calculate", &AirWaterCoolingUsingFlue::calculate);
}


