#include <steam/air_water_cooling_using_flue.h>
#include <physics/gas_composition.h>

#include "catch.hpp"

using namespace Catch;
using namespace air_water_cooling_using_flue;
using namespace gas_composition;
TEST_CASE("Calculate air water cooling using flue results", "[steam][airWaterCoolingUsingFlue]") {

    GasComposition gasFlueCond("Gas", 94.1, 3.02, 1.41, 0.01, 0.42, 0.28, 0.0, 0.0, 0.7, 0, 0.01);
    auto resHeatRecovery = airWaterCoolingUsingFlue(gasFlueCond, 116, 300, 125, 70, 60, 0.04, 60, 0);
    CHECK(resHeatRecovery.excess_air == Approx(0.2169692841));
    CHECK(resHeatRecovery.flow_flue_gas == Approx(107022.7016052115));
    CHECK(resHeatRecovery.specific_heat == Approx(0.2577908474));
    CHECK(resHeatRecovery.fraction_condensed == Approx(0.19816).epsilon(0.005));
    CHECK(resHeatRecovery.available_heat_fraction == Approx(0.8443608099));
    CHECK(resHeatRecovery.total_available_heat_fraction == Approx(0.8645004409));
    CHECK(resHeatRecovery.latent_heat_fraction == Approx(0.02014).epsilon(0.005));
    CHECK(resHeatRecovery.latent_heat_recovery == Approx(2.3362));
    CHECK(resHeatRecovery.sensible_heat_recovery == Approx(4.8281577633));
}