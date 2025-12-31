#include <string>

#include <emscripten/bind.h>

#include "processHeat/AirHeatingUsingExhaust.h"
#include "processHeat/AirWaterCoolingUsingFlue.h"
#include "processHeat/WaterHeatingUsingFlue.h"
#include "processHeat/WaterHeatingUsingSteam.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(processHeat_class) {
    using namespace gas_composition;
    enum_<WaterHeatingUsingFlue::SteamCondition>("SteamConditionType")
        .value("Superheated", WaterHeatingUsingFlue::SteamCondition::Superheated)
        .value("Saturated", WaterHeatingUsingFlue::SteamCondition::Saturated);

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

    class_<WaterHeatingUsingFlue::Output>("WaterHeatingUsingFlueOutput")
        .property("flowFlueGas", &WaterHeatingUsingFlue::Output::flowFlueGas)
        .property("effBoiler", &WaterHeatingUsingFlue::Output::effBoiler)
        .property("enthalpySteam", &WaterHeatingUsingFlue::Output::enthalpySteam)
        .property("enthalpyFW", &WaterHeatingUsingFlue::Output::enthalpyFW)
        .property("flowSteam", &WaterHeatingUsingFlue::Output::flowSteam)
        .property("flowFW", &WaterHeatingUsingFlue::Output::flowFW)
        .property("specheatFG", &WaterHeatingUsingFlue::Output::specheatFG)
        .property("heatCapacityFG", &WaterHeatingUsingFlue::Output::heatCapacityFG)
        .property("specheatFW", &WaterHeatingUsingFlue::Output::specheatFW)
        .property("heatCapacityFW", &WaterHeatingUsingFlue::Output::heatCapacityFW)
        .property("heatCapacityMin", &WaterHeatingUsingFlue::Output::heatCapacityMin)
        .property("ratingHeatRecFW", &WaterHeatingUsingFlue::Output::ratingHeatRecFW)
        .property("tempFlueGasOut", &WaterHeatingUsingFlue::Output::tempFlueGasOut)
        .property("tempFWOut", &WaterHeatingUsingFlue::Output::tempFWOut)
        .property("energySavingsBoiler", &WaterHeatingUsingFlue::Output::energySavingsBoiler)
        .property("costSavingsBoiler", &WaterHeatingUsingFlue::Output::costSavingsBoiler);

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

    class_<WaterHeatingUsingFlue>("WaterHeatingUsingFlue")
        .constructor<>()
        .function("calculate", &WaterHeatingUsingFlue::calculate);

    class_<AirWaterCoolingUsingFlue>("AirWaterCoolingUsingFlue")
        .constructor<>()
        .function("calculate", &AirWaterCoolingUsingFlue::calculate);
}


