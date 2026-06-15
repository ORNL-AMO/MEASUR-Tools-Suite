/**
 * Gas Flue Gas Material calculations.
 *
 * Calculates process heat properties and total heat loss for flue gas
 * from a fuel gas mixture with given combustion conditions.
 *
 */

import type { GasCompositions } from '../../physics/gas_compositions';

/**
 * Result object returned by {@link gasFlueGasMaterialProcessHeatProperties}.
 *
 * @property stoichAir Stoichiometric air required for complete combustion, units SCF air/SCF fuel
 * @property excessAir Percent excess air (e.g. 9 for 9%), unitless
 * @property availableHeat Available heat from combustion, units BTU/hr
 * @property specificHeat Specific heat of the gas, units BTU/hr/degF
 * @property density Total mass generated (density field), units lb/hr
 * @property flueGasO2 Oxygen in flue gas, units %
 */
export interface ProcessHeatProperties {
    /** Stoichiometric air required for complete combustion, units SCF air/SCF fuel */
    stoichAir: number;
    /** Percent excess air (e.g. 9 for 9%), unitless */
    excessAir: number;
    /** Available heat from combustion, units BTU/hr */
    availableHeat: number;
    /** Specific heat of the gas, units BTU/hr/degF */
    specificHeat: number;
    /** Total mass generated, units lb/hr */
    density: number;
    /** Oxygen in flue gas, units % */
    flueGasO2: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculate total heat loss for flue gas from a fuel gas mixture.
 *
 * @param flue_gas_temperature Furnace flue gas temperature, units degF
 * @param excess_air_percentage Percent excess air (e.g. 9 for 9%), units %
 * @param combustion_air_temperature Combustion air temperature, units degF
 * @param compositions {@link GasCompositions} instance representing the fuel gas mixture
 * @param fuel_temperature Temperature of fuel, units degF
 * @returns Total heat loss, units BTU/hr
 */
export function gasFlueGasMaterialTotalHeatLoss(
    flue_gas_temperature: number,
    excess_air_percentage: number,
    combustion_air_temperature: number,
    compositions: GasCompositions,
    fuel_temperature: number
): number;

/**
 * Calculate process heat properties for a fuel gas mixture and operating conditions.
 *
 * @param compositions {@link GasCompositions} instance representing the fuel gas mixture
 * @param flue_gas_temp Flue gas temperature, units degF
 * @param flue_gas_o2 Oxygen percentage in flue gas, units %
 * @param comb_air_temp Combustion air temperature, units degF
 * @param fuel_temp Fuel temperature, units degF
 * @param ambient_air_temp Ambient air temperature, units degF (default: 60)
 * @param comb_air_moisture Combustion air moisture, units % (default: 0)
 * @param excess_air Excess air percentage, units % (default: 0)
 * @returns {@link ProcessHeatProperties}
 */
export function gasFlueGasMaterialProcessHeatProperties(
    compositions: GasCompositions,
    flue_gas_temp: number,
    flue_gas_o2: number,
    comb_air_temp: number,
    fuel_temp: number,
    ambient_air_temp?: number,
    comb_air_moisture?: number,
    excess_air?: number
): ProcessHeatProperties;

export type GasFlueGasMaterialModule = {
    ProcessHeatProperties: ProcessHeatProperties;
    gasFlueGasMaterialTotalHeatLoss: typeof gasFlueGasMaterialTotalHeatLoss;
    gasFlueGasMaterialProcessHeatProperties: typeof gasFlueGasMaterialProcessHeatProperties;
};