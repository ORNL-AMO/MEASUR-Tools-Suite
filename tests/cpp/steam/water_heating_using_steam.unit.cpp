#include <steam/water_heating_using_steam.h>

#include "catch.hpp"

using namespace Catch;
using namespace water_heating_using_steam;
TEST_CASE("Calculate water heating using steam results 1", "[steam]") {
    WaterHeatingUsingSteamResults resSteamEnergy =
        waterHeatingUsingSteam(0.1565, 340.2, 285.93, 0.5150, 2.7255, 285.93, 0.2048, 0.72, 0.8, 7000);
    CHECK(resSteamEnergy.temp_water_out == Approx(352.304));
    CHECK(resSteamEnergy.bp_temp_water_out == Approx(426.1));
    CHECK(resSteamEnergy.enthalpy_steam_in == Approx(2695.04));
    CHECK(resSteamEnergy.enthalpy_steam_out == Approx(472.5));
    CHECK(resSteamEnergy.enthalpy_makeup_water == Approx(53.876));
    CHECK(resSteamEnergy.energy_saved_dwh == Approx(7351062329.1926));
    CHECK(resSteamEnergy.energy_saved_boiler == Approx(1246124501.2457));
    CHECK(resSteamEnergy.water_saved == Approx(2381.4));
    CHECK(resSteamEnergy.heat_gain_rate == Approx(756109.2681));
}

TEST_CASE("Calculate water heating using steam results 2", "[steam]") {
    WaterHeatingUsingSteamResults resSteamEnergy =
        waterHeatingUsingSteam(0.1703, 226.79, 285.93, 0.2737, 0.6814, 285.93, 0.2048, 0.7, 0.7, 8000);
    CHECK(resSteamEnergy.temp_water_out == Approx(388.75));
    CHECK(resSteamEnergy.bp_temp_water_out == Approx(403.57));
    CHECK(resSteamEnergy.enthalpy_steam_in == Approx(2698.89));
    CHECK(resSteamEnergy.enthalpy_steam_out == Approx(483.41));
    CHECK(resSteamEnergy.enthalpy_makeup_water == Approx(53.876));
    CHECK(resSteamEnergy.flow_bypass_steam == Approx(94.61));
    CHECK(resSteamEnergy.energy_saved_dwh == Approx(3346757808.4035));
    CHECK(resSteamEnergy.energy_saved_boiler == Approx(648872153.14));
    CHECK(resSteamEnergy.water_saved == Approx(1057.44));
    CHECK(resSteamEnergy.heat_gain_rate == Approx(292841.3082));
}