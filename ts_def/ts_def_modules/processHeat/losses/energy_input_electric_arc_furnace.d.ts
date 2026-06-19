/**
 * Energy Input calculations for Electric Arc Furnace (EAF).
 *
 * Calculates the total chemical energy input and total heat delivered for
 * an Electric Arc Furnace from natural gas, coal/carbon injection, electrodes,
 * other fuels, and electric power input.
 *
 */

/**
 * Calculate total chemical energy input for an Electric Arc Furnace (EAF).
 *
 * Computes the total chemical energy input from natural gas, coal/carbon
 * injection, electrodes, and other fuels.
 *
 * @param natural_gas_heat_input Total heat input from natural gas, units MMBtu/hr
 * @param coal_carbon_injection Mass of coal/carbon injection, units lb/hr
 * @param coal_heating_value Heating value of coal/carbon, units BTU/lb
 * @param electrode_use Electrode use, units lb/hr
 * @param electrode_heating_value Electrode heating value, units BTU/lb
 * @param other_fuels Heat supplied from other sources, units MMBtu/hr
 * @returns Total chemical energy input, units BTU/hr
 */
export function energyInputEAFTotalChemicalEnergyInput(
    natural_gas_heat_input: number,
    coal_carbon_injection: number,
    coal_heating_value: number,
    electrode_use: number,
    electrode_heating_value: number,
    other_fuels: number
): number;

/**
 * Calculate total heat delivered to the Electric Arc Furnace (EAF).
 *
 * Computes the total heat delivered to the EAF, including electric power supplied.
 *
 * @param total_chemical_energy_input Total chemical energy input, units BTU/hr
 * @param electricity_input Total electric power supplied, units kWh/hr
 * @returns Total heat delivered to EAF, units BTU/hr
 */
export function energyInputEAFTotalHeatDelivered(
    total_chemical_energy_input: number,
    electricity_input: number
): number;

export type EnergyInputElectricArcFurnaceModule = {
    energyInputEAFTotalChemicalEnergyInput: typeof energyInputEAFTotalChemicalEnergyInput;
    energyInputEAFTotalHeatDelivered: typeof energyInputEAFTotalHeatDelivered;
};
