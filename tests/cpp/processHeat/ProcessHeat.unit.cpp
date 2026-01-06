#include <processHeat/AirHeatingUsingExhaust.h>
#include <processHeat/AirWaterCoolingUsingFlue.h>
#include <processHeat/losses/solid_liquid_flue_gas_material.h>

#include "catch.hpp"

using namespace Catch;
using namespace gas_composition;
using namespace gas_flue_gas_material;
using namespace solid_liquid_flue_gas_material;
TEST_CASE("Estimate maximum air flow that can be heated by using exhaust gas", "[processHeat]") {
    GasComposition gas("Gas", 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    auto           res = AirHeatingUsingExhaust(gas).calculate(400, 0.358, 8, 4000, 45, 0.85, 0.60, 4000);
    CHECK(res.hxColdAir == Approx(197829.27));
    CHECK(res.hxOutletExhaust == Approx(187));
    CHECK(res.energySavings == Approx(930.96));
    CHECK(res.heatCapacityFlue == Approx(928.78));
    CHECK(res.heatCapacityAir == Approx(4464));

    GasComposition gasFlueCond("Gas", 94.1, 3.02, 1.41, 0.01, 0.42, 0.28, 0.0, 0.0, 0.7, 0, 0.01);
    auto resHeatRecovery = AirWaterCoolingUsingFlue().calculate(gasFlueCond, 116, 300, 125, 70, 60, 0.04, 60, 0);
    CHECK(resHeatRecovery.excessAir == Approx(0.2169692841));
    CHECK(resHeatRecovery.flowFlueGas == Approx(107022.7016052115));
    CHECK(resHeatRecovery.specHeat == Approx(0.2577908474));
    CHECK(resHeatRecovery.fracCondensed == Approx(0.19816).epsilon(0.005));
    CHECK(resHeatRecovery.effThermal == Approx(0.8443608099));
    CHECK(resHeatRecovery.effThermalLH == Approx(0.8645004409));
    CHECK(resHeatRecovery.effLH == Approx(0.02014).epsilon(0.005));
    CHECK(resHeatRecovery.heatRecovery == Approx(2.3362));
    CHECK(resHeatRecovery.sensibleHeatRecovery == Approx(4.8281577633));
}

TEST_CASE("Air Heating Using Exhaust Solid Liquid Flue Gas", "[processHeat]") {

    double fuelHeatingValue =
        solid_liquid_flue_gas_material::calculateHeatingValueFuel(75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5);
    auto res = AirHeatingUsingExhaust(fuelHeatingValue).calculate(400, 0.358, 8, 4000, 45, 0.85, 0.60, 4000);
    CHECK(res.hxColdAir == Approx(15621.25));
    CHECK(res.hxOutletExhaust == Approx(187));
    CHECK(res.energySavings == Approx(73.512));
    CHECK(res.heatCapacityFlue == Approx(73.339));
    CHECK(res.heatCapacityAir == Approx(4464));
}