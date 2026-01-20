#include <string>
#include <emscripten/bind.h>
#include "steam/water_heating_using_steam.h"

using namespace emscripten;
using namespace water_heating_using_steam;

EMSCRIPTEN_BINDINGS(water_heating_using_steam_class) {
	value_object<WaterHeatingUsingSteamResults>("WaterHeatingUsingSteamOutput")
        .field("tempWaterOut", &WaterHeatingUsingSteamResults::temp_water_out)
        .field("bpTempWaterOut", &WaterHeatingUsingSteamResults::bp_temp_water_out)
        .field("bpTempWarningFlag", &WaterHeatingUsingSteamResults::bp_temp_warning_flag)
        .field("flowByPassSteam", &WaterHeatingUsingSteamResults::flow_bypass_steam)
        .field("enthalpySteamIn", &WaterHeatingUsingSteamResults::enthalpy_steam_in)
        .field("enthalpySteamOut", &WaterHeatingUsingSteamResults::enthalpy_steam_out)
        .field("enthalpyMakeUpWater", &WaterHeatingUsingSteamResults::enthalpy_makeup_water)
        .field("energySavedDWH", &WaterHeatingUsingSteamResults::energy_saved_dwh)
        .field("energySavedBoiler", &WaterHeatingUsingSteamResults::energy_saved_boiler)
        .field("waterSaved", &WaterHeatingUsingSteamResults::water_saved)
        .field("heatGainRate", &WaterHeatingUsingSteamResults::heat_gain_rate);

    // Parameters for waterHeatingUsingSteam:
    //   pressure_steam_in (Inlet steam pressure, MPaa)
    //   flow_steam_rate (Steam flow rate, kg/hr)
    //   temperature_water_in (Inlet water temperature, K)
    //   pressure_water_out (Outlet water pressure, MPaa)
    //   flow_water_rate (Water flow rate, m3/hr)
    //   temp_makeup_water (Makeup water temperature, K)
    //   pres_makeup_water (Makeup water pressure, MPaa)
    //   eff_water_heater (Water heater efficiency, fraction)
    //   eff_boiler (Boiler efficiency, fraction)
    //   operating_hours (Operating hours, hr)
	function("waterHeatingUsingSteam", &waterHeatingUsingSteam);
}
