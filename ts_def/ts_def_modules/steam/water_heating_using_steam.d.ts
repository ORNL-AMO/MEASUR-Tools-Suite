/**
 * Water Heating Using Steam calculations.
 *
 * Calculates energy savings from using vent steam to heat water via a
 * steam-to-liquid heat exchanger. Estimates savings for both the domestic
 * water heater (DWH) and the boiler, as well as water saved.
 */

/**
 * Result object returned by {@link waterHeatingUsingSteam}.
 *
 * @property tempWaterOut Outlet water temperature, units K
 * @property bpTempWaterOut Boiling point temperature of outlet water, units K
 * @property bpTempWarningFlag Warning flag - true if outlet water is at or above boiling point
 * @property flowByPassSteam Bypass steam flow, units kg/hr
 * @property enthalpySteamIn Inlet steam enthalpy, units kJ/kg
 * @property enthalpySteamOut Outlet steam enthalpy, units kJ/kg
 * @property enthalpyMakeUpWater Makeup water enthalpy, units kJ/kg
 * @property energySavedDWH Energy saved in domestic water heater, units kJ/yr
 * @property energySavedBoiler Energy saved in boiler, units kJ/yr
 * @property waterSaved Water saved, units m3/yr
 * @property heatGainRate Heat gain rate, units kJ/hr
 */
export interface WaterHeatingUsingSteamOutput {
    /** Outlet water temperature, units K */
    tempWaterOut: number;
    /** Boiling point temperature of outlet water, units K */
    bpTempWaterOut: number;
    /** Warning flag - true if outlet water is at or above boiling point */
    bpTempWarningFlag: boolean;
    /** Bypass steam flow, units kg/hr */
    flowByPassSteam: number;
    /** Inlet steam enthalpy, units kJ/kg */
    enthalpySteamIn: number;
    /** Outlet steam enthalpy, units kJ/kg */
    enthalpySteamOut: number;
    /** Makeup water enthalpy, units kJ/kg */
    enthalpyMakeUpWater: number;
    /** Energy saved in domestic water heater, units kJ/yr */
    energySavedDWH: number;
    /** Energy saved in boiler, units kJ/yr */
    energySavedBoiler: number;
    /** Water saved, units m3/yr */
    waterSaved: number;
    /** Heat gain rate, units kJ/hr */
    heatGainRate: number;
}

/**
 * Calculate energy savings from using vent steam to heat water via a
 * steam-to-liquid heat exchanger.
 *
 * Uses process parameters to estimate the benefit of using vent steam for
 * water heating and boiler operation.
 *
 * @param pressure_steam_in Inlet steam pressure, units MPaa
 * @param flow_steam_rate Steam flow rate, units kg/hr
 * @param temperature_water_in Inlet water temperature, units K
 * @param pressure_water_out Outlet water pressure, units MPaa
 * @param flow_water_rate Water flow rate, units m3/hr
 * @param temp_makeup_water Makeup water temperature, units K
 * @param pres_makeup_water Makeup water pressure, units MPaa
 * @param eff_water_heater Water heater efficiency, fraction
 * @param eff_boiler Boiler efficiency, fraction
 * @param operating_hours Operating hours, units hr
 * @returns {@link WaterHeatingUsingSteamOutput}
 */
export function waterHeatingUsingSteam(
    pressure_steam_in: number,
    flow_steam_rate: number,
    temperature_water_in: number,
    pressure_water_out: number,
    flow_water_rate: number,
    temp_makeup_water: number,
    pres_makeup_water: number,
    eff_water_heater: number,
    eff_boiler: number,
    operating_hours: number
): WaterHeatingUsingSteamOutput;

export type WaterHeatingUsingSteamModule = {
    waterHeatingUsingSteam: typeof waterHeatingUsingSteam;
};
