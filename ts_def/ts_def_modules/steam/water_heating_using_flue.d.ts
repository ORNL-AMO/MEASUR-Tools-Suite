/**
 * Water Heating Using Flue Gas calculations.
 *
 * Calculates energy and cost savings from using flue gas (waste) heat to
 * preheat boiler feed water using a non-condensing heat exchanger. Uses
 * fuel gas composition and process parameters to estimate the benefit.
 */

import type { GasCompositions } from '../physics/gas_compositions';

export type { GasCompositions };

/**
 * Steam condition type for water heating using flue gas calculations.
 */
export enum SteamConditionType {
    Superheated = 0,
    Saturated = 1,
}

/**
 * Result object returned by {@link waterHeatingUsingFlue}.
 *
 * @property flowFlueGas Flue gas mass flow, units kg/hr
 * @property effBoiler Boiler available heat, fraction
 * @property enthalpySteam Steam specific enthalpy, units kJ/kg
 * @property enthalpyFW Feedwater specific enthalpy, units kJ/kg
 * @property flowSteam Steam mass flow, units kg/hr
 * @property flowFW Feedwater mass flow, units kg/hr
 * @property specheatFG Flue gas specific heat, units kJ/(kg.K)
 * @property heatCapacityFG Flue gas heat capacity, units kJ/(hr.K)
 * @property specheatFW Feedwater specific heat, units kJ/(kg.K)
 * @property heatCapacityFW Feedwater heat capacity, units kJ/(hr.K)
 * @property heatCapacityMin Minimum heat capacity, units kJ/(hr.K)
 * @property ratingHeatRecFW Recovered heat, units kJ/hr
 * @property tempFlueGasOut Flue gas exit temperature, units K
 * @property tempFWOut Feedwater exit temperature, units K
 * @property energySavingsBoiler Annual energy savings, units GJ/yr
 * @property costSavingsBoiler Annual cost savings, units $/yr
 */
export interface WaterHeatingUsingFlueOutput {
    /** Flue gas mass flow, units kg/hr */
    flowFlueGas: number;
    /** Boiler available heat, fraction */
    effBoiler: number;
    /** Steam specific enthalpy, units kJ/kg */
    enthalpySteam: number;
    /** Feedwater specific enthalpy, units kJ/kg */
    enthalpyFW: number;
    /** Steam mass flow, units kg/hr */
    flowSteam: number;
    /** Feedwater mass flow, units kg/hr */
    flowFW: number;
    /** Flue gas specific heat, units kJ/(kg.K) */
    specheatFG: number;
    /** Flue gas heat capacity, units kJ/(hr.K) */
    heatCapacityFG: number;
    /** Feedwater specific heat, units kJ/(kg.K) */
    specheatFW: number;
    /** Feedwater heat capacity, units kJ/(hr.K) */
    heatCapacityFW: number;
    /** Minimum heat capacity, units kJ/(hr.K) */
    heatCapacityMin: number;
    /** Recovered heat, units kJ/hr */
    ratingHeatRecFW: number;
    /** Flue gas exit temperature, units K */
    tempFlueGasOut: number;
    /** Feedwater exit temperature, units K */
    tempFWOut: number;
    /** Annual energy savings, units GJ/yr */
    energySavingsBoiler: number;
    /** Annual cost savings, units $/yr */
    costSavingsBoiler: number;
}

/**
 * Calculate energy and cost savings from using flue gas heat to preheat
 * boiler feed water using a non-condensing heat exchanger.
 *
 * @param gas_compositions {@link GasCompositions} fuel gas composition for flue gas calculations
 * @param temp_flue_gas_f Flue gas temperature, units degF
 * @param perc_o2 Oxygen percentage in flue gas, fraction
 * @param temp_comb_air_f Combustion air temperature, units degF
 * @param moist_comb_air Combustion air moisture, fraction
 * @param rating_boiler Boiler rating, units GJ/hr
 * @param pr_steam Steam pressure, units MPa
 * @param temp_ambient_air_f Ambient air temperature, units degF
 * @param temp_steam_f Steam temperature, units degF
 * @param temp_fw Feedwater temperature, units degF
 * @param perc_blow_down Blowdown percentage, fraction
 * @param eff_hx Heat exchanger efficiency, fraction
 * @param op_hours Operating hours, units hr
 * @param cost_fuel Fuel cost, units $/GJ
 * @param hhv_fuel Fuel higher heating value, units kJ/Nm3
 * @param cond_steam {@link SteamConditionType} Superheated or Saturated (default: Superheated)
 * @param fuel_temp_f Fuel temperature, units degF (default: 60)
 * @returns {@link WaterHeatingUsingFlueOutput}
 */
export function waterHeatingUsingFlue(
    gas_compositions: GasCompositions,
    temp_flue_gas_f: number,
    perc_o2: number,
    temp_comb_air_f: number,
    moist_comb_air: number,
    rating_boiler: number,
    pr_steam: number,
    temp_ambient_air_f: number,
    temp_steam_f: number,
    temp_fw: number,
    perc_blow_down: number,
    eff_hx: number,
    op_hours: number,
    cost_fuel: number,
    hhv_fuel: number,
    cond_steam?: SteamConditionType,
    fuel_temp_f?: number
): WaterHeatingUsingFlueOutput;

export type WaterHeatingUsingFlueModule = {
    SteamConditionType: typeof SteamConditionType;
    waterHeatingUsingFlue: typeof waterHeatingUsingFlue;
};
