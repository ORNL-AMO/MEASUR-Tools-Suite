#include "processHeat/cascade_heat_high_to_low.h"
#include "processHeat/losses/gas_flue_gas_material.h"
#include "catch.hpp"

using namespace Catch;
using namespace cascade_heat_high_to_low;
TEST_CASE("Calculate results for cascade heat high to low", "[Process Heating][CascadeHeatHighToLow]") {

    gas_composition::GasComposition gasCH("Gas", 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    CascadeHeatHighToLowResults     resCascadeHeatHighToLow = calculateCascadeHeatHighToLow(
        gasCH, 1020, 5.00, 12.0, 1475, 0.07, 80, 8000, 9.50, 225, 17.5, 80, 7000, 60, 60, 0);
    CHECK(resCascadeHeatHighToLow.pri_flue_volume == Approx(175123.0293326335));
    CHECK(resCascadeHeatHighToLow.hx_energy_rate == Approx(4.2341865845));
    CHECK(resCascadeHeatHighToLow.eq_energy_supply == Approx(4.7235204084));
    CHECK(resCascadeHeatHighToLow.eff_op_hours == Approx(7000));
    CHECK(resCascadeHeatHighToLow.energy_savings == Approx(33064.6428585547));
    CHECK(resCascadeHeatHighToLow.cost_savings == Approx(165323.2142927737));
    CHECK(resCascadeHeatHighToLow.hourly_savings == Approx(4.7235204084));
    CHECK(resCascadeHeatHighToLow.pri_excess_air == Approx(0.4519750365));
    CHECK(resCascadeHeatHighToLow.pri_available_heat == Approx(0.4724916999));
    CHECK(resCascadeHeatHighToLow.sec_excess_air == Approx(-1.05775222));
    CHECK(resCascadeHeatHighToLow.sec_available_heat == Approx(0.8964).epsilon(0.005));
}
