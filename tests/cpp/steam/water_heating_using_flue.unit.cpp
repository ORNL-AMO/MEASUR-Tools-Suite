#include <steam/water_heating_using_flue.h>
#include "catch.hpp"
#include "physics/gas_composition.h"

using namespace Catch;
using namespace water_heating_using_flue;
using namespace gas_composition;
TEST_CASE("Calculate water heating using flue results", "[steam]") {

    GasComposition gasFlue("Gas", 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    WaterHeatingUsingFlueResults           resFlueHeat =
        waterHeatingUsingFlue(gasFlue, 725, 0.05, 80, 0.02, 55.88, 3.45, 60, 500, 225, 0.04, 0.625, 8000,
                                          5.21, 37706, SteamCondition::Superheated, 60);
    CHECK(resFlueHeat.flue_gas_mass_flow == Approx(23658.1596137958));
    CHECK(resFlueHeat.boiler_available_heat == Approx(0.7193913738));
    CHECK(resFlueHeat.steam_specific_enthalpy == Approx(2865.339));
    CHECK(resFlueHeat.feedwater_specific_enthalpy == Approx(452.0478));
    CHECK(resFlueHeat.steam_mass_flow == Approx(15991.2762656448));
    CHECK(resFlueHeat.feedwater_mass_flow == Approx(16630.9273162706));
    CHECK(resFlueHeat.flue_gas_specific_heat == Approx(1.1319998535));
    CHECK(resFlueHeat.flue_gas_heat_capacity == Approx(26781.0332157512));
    CHECK(resFlueHeat.feedwater_specific_heat == Approx(4.2285));
    CHECK(resFlueHeat.feedwater_heat_capacity == Approx(70323.6515387818));
    CHECK(resFlueHeat.min_heat_capacity == Approx(26781.0332157512));
    CHECK(resFlueHeat.recovered_heat == Approx(4649484.9332901333));
    CHECK(resFlueHeat.flue_gas_exit_temp == Approx(484.537));
    CHECK(resFlueHeat.feedwater_exit_temp == Approx(446.4877442629));
    CHECK(resFlueHeat.annual_energy_savings == Approx(51704.6503757363));
    CHECK(resFlueHeat.annual_cost_savings == Approx(269381.2284575859));
}