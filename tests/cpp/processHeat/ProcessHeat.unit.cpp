#include <processHeat/AirWaterCoolingUsingFlue.h>
#include <processHeat/losses/solid_liquid_flue_gas_material.h>

#include "catch.hpp"

using namespace Catch;
using namespace gas_composition;
TEST_CASE("Estimate maximum air flow that can be heated by using exhaust gas", "[processHeat]") {

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