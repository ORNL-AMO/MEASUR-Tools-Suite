/**
 * Energy Equivalency Calculator.
 *
 * Calculates equivalent electrical or fuel-fired heat input for process
 * heating systems, enabling comparison between fuel-fired and electrically
 * heated furnaces based on their respective efficiencies.
 */

/**
 * Calculates the equivalent electrical heat input required to replace a
 * fuel-fired furnace.
 *
 * Uses the fuel-fired heat input and efficiencies to determine the
 * equivalent electrical input.
 *
 * @param fuel_fired_heat_input Fuel-fired heat input, units MMBtu/hr
 * @param fuel_fired_efficiency Fuel-fired furnace efficiency, units %
 * @param electrically_heated_efficiency Electrically heated furnace efficiency, units %
 * @returns Equivalent electrical heat input, units kW
 */
export function calculateElectricalEquivalentHeatInput(
    fuel_fired_heat_input: number,
    fuel_fired_efficiency: number,
    electrically_heated_efficiency: number
): number;

/**
 * Calculates the equivalent fuel-fired heat input required to replace an
 * electrically heated furnace.
 *
 * Uses the electrical heat input and efficiencies to determine the
 * equivalent fuel-fired input.
 *
 * @param electrical_heat_input Electrical heat input, units kW
 * @param electrically_heated_efficiency Electrically heated furnace efficiency, units %
 * @param fuel_fired_efficiency Fuel-fired furnace efficiency, units %
 * @returns Equivalent fuel-fired heat input, units MMBtu/hr
 */
export function calculateFuelFiredEquivalentHeatInput(
    electrical_heat_input: number,
    electrically_heated_efficiency: number,
    fuel_fired_efficiency: number
): number;

export type EnergyEquivalencyModule = {
    calculateElectricalEquivalentHeatInput: typeof calculateElectricalEquivalentHeatInput;
    calculateFuelFiredEquivalentHeatInput: typeof calculateFuelFiredEquivalentHeatInput;
};
