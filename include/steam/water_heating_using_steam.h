
/**
 * @ingroup water_heating_using_steam_calculator
 * @file water_heating_using_steam.h
 *
 * @copybrief water_heating_using_steam
 */

/**
 * @ingroup water_heating_using_steam_calculator
 * @namespace water_heating_using_steam
 * @brief Water heating using vent steam calculations for process heating systems.
 */
namespace water_heating_using_steam {

/**
 * @ingroup water_heating_using_steam_calculator
 * @struct WaterHeatingUsingSteamResults
 * @brief Results of the water heating using steam calculation.
 * @details Contains all output values from the water heating using steam calculation.
 */
struct WaterHeatingUsingSteamResults {
    double temp_water_out = 0;         ///< Outlet water temperature @unitb{K}
    double bp_temp_water_out = 0;      ///< Boiling point temp of water out @unitb{K}
    bool bp_temp_warning_flag = false; ///< Warning if outlet water at/above boiling point
    double flow_bypass_steam = 0;      ///< Bypass steam flow @unitb{kg/hr}
    double enthalpy_steam_in = 0;      ///< Inlet steam enthalpy @unitb{kJ/kg}
    double enthalpy_steam_out = 0;     ///< Outlet steam enthalpy @unitb{kJ/kg}
    double enthalpy_makeup_water = 0;  ///< Makeup water enthalpy @unitb{kJ/kg}
    double energy_saved_dwh = 0;       ///< Energy saved in DWH @unitb{kJ/yr}
    double energy_saved_boiler = 0;    ///< Energy saved in boiler @unitb{kJ/yr}
    double water_saved = 0;            ///< Water saved @unitb{m3/yr}
    double heat_gain_rate = 0;         ///< Heat gain rate @unitb{kJ/hr}
};

/**
 * @ingroup water_heating_using_steam_calculator
 * @brief Calculates energy savings from using vent steam to heat water using a steam to liquid heat exchanger.
 * @details Uses process parameters to estimate the benefit of using vent steam for water heating and boiler operation.
 *
 * @param[in] pressure_steam_in Inlet steam pressure @unitb{MPaa}
 * @param[in] flow_steam_rate Steam flow rate @unitb{kg/hr}
 * @param[in] temperature_water_in Inlet water temperature @unitb{K}
 * @param[in] pressure_water_out Outlet water pressure @unitb{MPaa}
 * @param[in] flow_water_rate Water flow rate @unitb{m3/hr}
 * @param[in] temp_makeup_water Makeup water temperature @unitb{K}
 * @param[in] pres_makeup_water Makeup water pressure @unitb{MPaa}
 * @param[in] eff_water_heater Water heater efficiency (fraction)
 * @param[in] eff_boiler Boiler efficiency (fraction)
 * @param[in] operating_hours Operating hours @unitb{hr}
 * @return WaterHeatingUsingSteamResults struct with all calculated outputs.
 */
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
);

} // namespace water_heating_using_steam

