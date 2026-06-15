/**
 * Air Heating Using Exhaust Calculator.
 *
 * Estimates heat recovery from exhaust gas used to preheat combustion air
 * in process heating systems. Supports both gaseous fuels (via GasCompositions)
 * and solid/liquid fuels (via SolidLiquidFlueGasMaterial).
 */

import type { GasCompositions } from '../physics/gas_compositions';
import type { SolidLiquidFlueGasMaterial } from '../databases/default_data';

export type { GasCompositions, SolidLiquidFlueGasMaterial };

/**
 * Results of the air heating using exhaust calculation.
 *
 * @property hxColdAir Heat recovered by cold air, units BTU/hr
 * @property hxOutletExhaust Outlet exhaust temperature after heat exchange, units degF
 * @property energySavings Annual energy savings, units MMBtu/yr
 * @property heatCapacityFlue Heat capacity of flue gas
 * @property heatCapacityAir Heat capacity of air
 */
export interface AirHeatingUsingExhaustResults {
    /** Heat recovered by cold air, units BTU/hr */
    hxColdAir: number;
    /** Outlet exhaust temperature after heat exchange, units degF */
    hxOutletExhaust: number;
    /** Annual energy savings, units MMBtu/yr */
    energySavings: number;
    /** Heat capacity of flue gas */
    heatCapacityFlue: number;
    /** Heat capacity of air */
    heatCapacityAir: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates air heating using exhaust for gaseous fuels.
 *
 * Uses gas composition to determine fuel heating value and stoichiometric
 * air, then estimates heat recovery from exhaust to preheat combustion air.
 *
 * @param gas_composition {@link GasCompositions} object with fuel properties
 * @param flue_temperature Flue gas temperature, units degF
 * @param excess_air Excess air as fraction (e.g. 0.09 for 9%)
 * @param fire_rate Firing rate, units MMBtu/hr
 * @param airflow Air flow, units scfm
 * @param inlet_temperature Inlet air temperature, units degF
 * @param heater_efficiency Heater efficiency as fraction
 * @param hx_efficiency Heat exchanger efficiency as fraction
 * @param operating_hours Annual operating hours, units hr
 * @returns {@link AirHeatingUsingExhaustResults} with all calculated outputs
 */
export function airHeatingUsingExhaustWithGasComposition(
    gas_composition: GasCompositions,
    flue_temperature: number,
    excess_air: number,
    fire_rate: number,
    airflow: number,
    inlet_temperature: number,
    heater_efficiency: number,
    hx_efficiency: number,
    operating_hours: number
): AirHeatingUsingExhaustResults;

/**
 * Calculates air heating using exhaust for solid/liquid fuels.
 *
 * Uses the provided SolidLiquidFlueGasMaterial to determine fuel heating
 * value and stoichiometric air, then estimates heat recovery from exhaust
 * to preheat combustion air.
 *
 * @param material {@link SolidLiquidFlueGasMaterial} object with fuel composition and properties
 * @param flue_temperature Flue gas temperature, units degF
 * @param excess_air Excess air as fraction (e.g. 0.09 for 9%)
 * @param fire_rate Firing rate, units MMBtu/hr
 * @param airflow Air flow, units scfm
 * @param inlet_temperature Inlet air temperature, units degF
 * @param heater_efficiency Heater efficiency as fraction
 * @param hx_efficiency Heat exchanger efficiency as fraction
 * @param operating_hours Annual operating hours, units hr
 * @returns {@link AirHeatingUsingExhaustResults} with all calculated outputs
 */
export function airHeatingUsingExhaustWithSolidLiquidFlueGasMaterial(
    material: SolidLiquidFlueGasMaterial,
    flue_temperature: number,
    excess_air: number,
    fire_rate: number,
    airflow: number,
    inlet_temperature: number,
    heater_efficiency: number,
    hx_efficiency: number,
    operating_hours: number
): AirHeatingUsingExhaustResults;

export type AirHeatingUsingExhaustModule = {
    AirHeatingUsingExhaustResults: AirHeatingUsingExhaustResults;
    airHeatingUsingExhaustWithGasComposition: typeof airHeatingUsingExhaustWithGasComposition;
    airHeatingUsingExhaustWithSolidLiquidFlueGasMaterial: typeof airHeatingUsingExhaustWithSolidLiquidFlueGasMaterial;
};