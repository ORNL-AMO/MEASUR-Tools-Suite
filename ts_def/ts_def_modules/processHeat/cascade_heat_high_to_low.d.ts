/**
 * Cascade Heat High-to-Low Calculator.
 *
 * Calculates energy and cost savings from cascading waste heat from a
 * high-temperature primary process to supply heat to a low-temperature
 * secondary process using exhaust gas heat recovery.
 *
 * @see cascade_heat_high_to_low_calculator
 */

import type { GasCompositions } from '../physics/gas_compositions';

export type { GasCompositions };

/**
 * Results of the cascade heat high-to-low calculation.
 *
 * @property priFlueVolume Primary flue gas volume, units SCF/hr
 * @property hxEnergyRate Heat exchanger energy rate, units MMBtu/hr
 * @property eqEnergySupply Equivalent energy supply, units MMBtu/hr
 * @property effOpHours Effective operating hours, units hr/yr
 * @property energySavings Total energy savings, units MMBtu/yr
 * @property costSavings Total cost savings, units USD/yr
 * @property hourlySavings Hourly energy savings, units MMBtu/hr
 * @property priExcessAir Primary excess air, fraction
 * @property priAvailableHeat Primary available heat, fraction
 * @property secExcessAir Secondary excess air, fraction
 * @property secAvailableHeat Secondary available heat, fraction
 */
export interface CascadeHeatHighToLowOutput {
    /** Primary flue gas volume, units SCF/hr */
    priFlueVolume: number;
    /** Heat exchanger energy rate, units MMBtu/hr */
    hxEnergyRate: number;
    /** Equivalent energy supply, units MMBtu/hr */
    eqEnergySupply: number;
    /** Effective operating hours, units hr/yr */
    effOpHours: number;
    /** Total energy savings, units MMBtu/yr */
    energySavings: number;
    /** Total cost savings, units USD/yr */
    costSavings: number;
    /** Hourly energy savings, units MMBtu/hr */
    hourlySavings: number;
    /** Primary excess air, fraction */
    priExcessAir: number;
    /** Primary available heat, fraction */
    priAvailableHeat: number;
    /** Secondary excess air, fraction */
    secExcessAir: number;
    /** Secondary available heat, fraction */
    secAvailableHeat: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates energy and cost savings from cascading heat from a high-temperature
 * to a low-temperature process.
 *
 * Uses flue gas properties and process parameters to estimate the benefit of
 * using waste heat from a primary (high-temp) process to supply heat to a
 * secondary (low-temp) process.
 *
 * @param gas_compositions {@link GasCompositions} fuel gas composition for flue gas calculations
 * @param fuel_hv Fuel heating value, units BTU/SCF
 * @param fuel_cost Fuel cost, units USD/MMBtu
 * @param pri_firing_rate Primary process firing rate, units MMBtu/hr
 * @param pri_exhaust_temp Primary process exhaust temperature, units degF
 * @param pri_exhaust_o2 Primary process exhaust O2, fraction
 * @param pri_comb_air_temp Primary process combustion air temperature, units degF
 * @param pri_op_hours Primary process operating hours, units hr/yr
 * @param sec_firing_rate Secondary process firing rate, units MMBtu/hr
 * @param sec_exhaust_temp Secondary process exhaust temperature, units degF
 * @param sec_exhaust_o2 Secondary process exhaust O2, fraction
 * @param sec_comb_air_temp Secondary process combustion air temperature, units degF
 * @param sec_op_hours Secondary process operating hours, units hr/yr
 * @param fuel_temp_f Fuel temperature, units degF (default: 60)
 * @param ambient_air_temp_f Ambient air temperature, units degF (default: 60)
 * @param comb_air_moisture_perc Combustion air moisture, units % (default: 0)
 * @returns {@link CascadeHeatHighToLowOutput} with all calculated outputs
 */
export function calculateCascadeHeatHighToLow(
    gas_compositions: GasCompositions,
    fuel_hv: number,
    fuel_cost: number,
    pri_firing_rate: number,
    pri_exhaust_temp: number,
    pri_exhaust_o2: number,
    pri_comb_air_temp: number,
    pri_op_hours: number,
    sec_firing_rate: number,
    sec_exhaust_temp: number,
    sec_exhaust_o2: number,
    sec_comb_air_temp: number,
    sec_op_hours: number,
    fuel_temp_f?: number,
    ambient_air_temp_f?: number,
    comb_air_moisture_perc?: number
): CascadeHeatHighToLowOutput;

export type CascadeHeatHighToLowModule = {
    CascadeHeatHighToLowOutput: CascadeHeatHighToLowOutput;
    calculateCascadeHeatHighToLow: typeof calculateCascadeHeatHighToLow;
};
