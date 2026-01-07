#include <string>

#include <emscripten/bind.h>

#include "processHeat/AirHeatingUsingExhaust.h"
#include "processHeat/AirWaterCoolingUsingFlue.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(processHeat_class) {
    using namespace gas_composition;

    class_<AirHeatingUsingExhaust::Output>("AirHeatingUsingExhaustOutput")
        .property("hxColdAir", &AirHeatingUsingExhaust::Output::hxColdAir)
        .property("hxOutletExhaust", &AirHeatingUsingExhaust::Output::hxOutletExhaust)
        .property("energySavings", &AirHeatingUsingExhaust::Output::energySavings)
        .property("heatCapacityFlue", &AirHeatingUsingExhaust::Output::heatCapacityFlue)
        .property("heatCapacityAir", &AirHeatingUsingExhaust::Output::heatCapacityAir);

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

    class_<AirWaterCoolingUsingFlue>("AirWaterCoolingUsingFlue")
        .constructor<>()
        .function("calculate", &AirWaterCoolingUsingFlue::calculate);
}


