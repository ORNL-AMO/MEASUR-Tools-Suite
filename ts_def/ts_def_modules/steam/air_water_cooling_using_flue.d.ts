/**
 * Air/Water Cooling Using Flue Gas calculations.
 *
 * Calculates heat recovery, available heat, and latent heat effects for
 * a condensing heat exchanger using flue gas from a fuel-fired process.
 * Supports both sensible and latent heat recovery estimation.
 */

import type { GasCompositions } from '../physics/gas_compositions';

export type { GasCompositions };

/**
 * Result object returned by {@link airWaterCoolingUsingFlue}.
 *
 * @property excessAir Excess air fraction, unitless
 * @property flowFlueGas Flue gas flow, units lb/hr
 * @property specHeat Specific heat, units BTU/lb/degF
 * @property fracCondensed Fraction of water vapor condensed, unitless
 * @property effThermal Fraction of heat available (sensible only), unitless
 * @property effThermalLH Fraction of heat available (sensible + latent), unitless
 * @property effLH Fraction of heat available due to latent heat, unitless
 * @property heatRecovery Latent heat recovered, units MMBtu/hr
 * @property sensibleHeatRecovery Sensible heat recovered, units MMBtu/hr
 */
export interface AirWaterCoolingUsingFlueOutput {
    /** Excess air fraction, unitless */
    excessAir: number;
    /** Flue gas flow, units lb/hr */
    flowFlueGas: number;
    /** Specific heat, units BTU/lb/degF */
    specHeat: number;
    /** Fraction of water vapor condensed, unitless */
    fracCondensed: number;
    /** Fraction of heat available (sensible only), unitless */
    effThermal: number;
    /** Fraction of heat available (sensible + latent), unitless */
    effThermalLH: number;
    /** Fraction of heat available due to latent heat, unitless */
    effLH: number;
    /** Latent heat recovered, units MMBtu/hr */
    heatRecovery: number;
    /** Sensible heat recovered, units MMBtu/hr */
    sensibleHeatRecovery: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculate heat recovery using flue gas through a condensing heat exchanger.
 *
 * Uses gas composition and process parameters to estimate heat recovery,
 * available heat fraction, and latent heat effects.
 *
 * @param gas_compositions {@link GasCompositions} object with fuel properties
 * @param heat_input Heat input, units MMBtu/hr
 * @param temp_flue_gas_in Flue gas inlet temperature, units degF
 * @param temp_flue_gas_out Flue gas outlet temperature, units degF
 * @param temp_comb_air Combustion air temperature, units degF
 * @param fuel_temp Fuel temperature, units degF
 * @param perc_o2 Percent O2 in flue gas, fraction
 * @param ambient_air_temp Ambient air temperature, units degF (default: 60)
 * @param moist_comb_air Moisture in combustion air, fraction (default: 0)
 * @returns {@link AirWaterCoolingUsingFlueOutput}
 */
export function airWaterCoolingUsingFlue(
    gas_compositions: GasCompositions,
    heat_input: number,
    temp_flue_gas_in: number,
    temp_flue_gas_out: number,
    temp_comb_air: number,
    fuel_temp: number,
    perc_o2: number,
    ambient_air_temp?: number,
    moist_comb_air?: number
): AirWaterCoolingUsingFlueOutput;

export type AirWaterCoolingUsingFlueModule = {
    AirWaterCoolingUsingFlueOutput: AirWaterCoolingUsingFlueOutput;
    airWaterCoolingUsingFlue: typeof airWaterCoolingUsingFlue;
};
