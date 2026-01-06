#include "steam/water_heating_using_steam.h"
#include "steamModeler/SaturatedProperties.h"
#include "steamModeler/SteamProperties.h"
#include "physics/constants.h"
namespace water_heating_using_steam {

WaterHeatingUsingSteamResults waterHeatingUsingSteam(
    double pressure_steam_in,
    double flow_steam_rate,
    double temperature_water_in,
    double pressure_water_out,
    double flow_water_rate,
    double temp_makeup_water,
    double pres_makeup_water,
    double eff_water_heater,
    double eff_boiler,
    double operating_hours
) {
    // --- Calculate steam and water properties ---
    // Get saturated steam properties at inlet pressure
    auto sat_props = SaturatedProperties(pressure_steam_in, SaturatedTemperature(pressure_steam_in).calculate()).calculate();
    const double enthalpy_steam_in  = sat_props.gasSpecificEnthalpy;    // kJ/kg
    const double enthalpy_steam_out = sat_props.liquidSpecificEnthalpy; // kJ/kg

    // Boiling point temperature of water at outlet pressure
    const double bp_temp_water_out = SaturatedTemperature(pressure_water_out).calculate(); // K

    // Enthalpy of makeup water at given pressure and temperature
    const double enthalpy_makeup_water =
        SteamProperties(pres_makeup_water, SteamProperties::ThermodynamicQuantity::TEMPERATURE, temp_makeup_water)
            .calculate()
            .specificEnthalpy;

    // --- Calculate outlet water temperature ---
    double temp_water_out = temperature_water_in +
        ((enthalpy_steam_in - enthalpy_steam_out) * flow_steam_rate) / (physics::si::kSpecificHeatWater * 1000 * flow_water_rate);

    // Safety margin for boiling point (empirical factor)
    const double temp_bp_water_out = 0.96328 * bp_temp_water_out;

    // --- Calculate heat gain rate (kJ/hr) ---
    double heat_gain_rate = (enthalpy_steam_in - enthalpy_steam_out) * flow_steam_rate;

    // --- Check for boiling point warning and adjust if necessary ---
    bool bp_temp_warning_flag = false;
    double flow_bypass_steam = 0;
    if (temp_water_out >= temp_bp_water_out) {
        // If calculated outlet water temperature exceeds safe boiling point, adjust values
        bp_temp_warning_flag = true;
        temp_water_out = temp_bp_water_out;
        // Recalculate heat gain rate for adjusted temperature
        heat_gain_rate = 1000 * physics::si::kSpecificHeatWater * (temp_water_out - temperature_water_in) * flow_water_rate;
        // Calculate bypass steam flow required to maintain safe temperature
        flow_bypass_steam = flow_steam_rate - (heat_gain_rate / (enthalpy_steam_in - enthalpy_steam_out));
    }

    // --- Package results ---
    WaterHeatingUsingSteamResults results;
    results.temp_water_out = temp_water_out;                   // K
    results.bp_temp_water_out = bp_temp_water_out;             // K
    results.bp_temp_warning_flag = bp_temp_warning_flag;       // true if boiling point exceeded
    results.flow_bypass_steam = flow_bypass_steam;             // m3/hr
    results.enthalpy_steam_in = enthalpy_steam_in;             // kJ/kg
    results.enthalpy_steam_out = enthalpy_steam_out;           // kJ/kg
    results.enthalpy_makeup_water = enthalpy_makeup_water;     // kJ/kg
    // Energy saved in domestic water heater (kJ/yr)
    results.energy_saved_dwh = heat_gain_rate * operating_hours / eff_water_heater;
    // Energy saved in boiler (kJ/yr)
    results.energy_saved_boiler = (flow_steam_rate - flow_bypass_steam) * (enthalpy_steam_out - enthalpy_makeup_water) * operating_hours / eff_boiler;
    // Water saved (m3/yr)
    results.water_saved = (flow_steam_rate - flow_bypass_steam) * operating_hours / 1000;
    // Heat gain rate (kJ/hr)
    results.heat_gain_rate = heat_gain_rate;
    return results;
}

} // namespace water_heating_using_steam
