/**
 * Energy Input Exhaust Gas Heat Loss calculations.
 *
 * Calculates available heat, heat delivered, and exhaust gas losses for a
 * non-EAF electric furnace based on excess air, combustion air temperature,
 * exhaust gas temperature, and total heat input.
 *
 */

/**
 * Result object returned by {@link energyInputExhaustGasHeatLossCalculate}.
 *
 * @property available_heat Available heat, units % (percent)
 * @property heat_delivered Heat delivered to the furnace, units BTU/hr
 * @property exhaust_gas_losses Exhaust gas losses, units BTU/hr
 */
export interface EnergyInputExhaustGasLossesResult {
    /** Available heat percent, units % */
    available_heat: number;
    /** Heat delivered to the furnace, units BTU/hr */
    heat_delivered: number;
    /** Exhaust gas losses, units BTU/hr */
    exhaust_gas_losses: number;
}

/**
 * Calculate available heat, heat delivered, and exhaust gas losses for a
 * non-EAF electric furnace in a single call.
 *
 * @param excess_air Excess air, units % (percent)
 * @param combustion_air_temp Temperature of combustion air, units degF
 * @param exhaust_gas_temp Temperature of exhaust gas, units degF
 * @param total_heat_input Total heat input from all sources, units BTU/hr;
 *   if zero, available heat is set to 100% (default: 1)
 * @returns {@link EnergyInputExhaustGasLossesResult}
 */
export function energyInputExhaustGasHeatLossCalculate(
    excess_air: number,
    combustion_air_temp: number,
    exhaust_gas_temp: number,
    total_heat_input?: number
): EnergyInputExhaustGasLossesResult;

/**
 * Calculate available heat percentage for a non-EAF electric furnace.
 *
 * If total heat input is zero, available heat is set to 100%.
 *
 * @param excess_air Excess air, units % (percent)
 * @param combustion_air_temp Temperature of combustion air, units degF
 * @param exhaust_gas_temp Temperature of exhaust gas, units degF
 * @param total_heat_input Total heat input from all sources, units BTU/hr (default: 1)
 * @returns Available heat, units % (percent)
 */
export function energyInputAvailableHeat(
    excess_air: number,
    combustion_air_temp: number,
    exhaust_gas_temp: number,
    total_heat_input?: number
): number;

/**
 * Calculate heat delivered to a non-EAF electric furnace.
 *
 * @param available_heat Available heat, units % (percent)
 * @param total_heat_input Total heat input from all sources, units BTU/hr
 * @returns Heat delivered, units BTU/hr
 */
export function energyInputHeatDelivered(
    available_heat: number,
    total_heat_input: number
): number;

/**
 * Calculate exhaust gas losses for a non-EAF electric furnace.
 *
 * @param heat_delivered Heat delivered to the furnace, units BTU/hr
 * @param available_heat Available heat, units % (percent)
 * @returns Exhaust gas losses, units BTU/hr
 */
export function energyInputTotalHeatLoss(
    heat_delivered: number,
    available_heat: number
): number;

export type EnergyInputExhaustGasHeatLossModule = {
    energyInputExhaustGasHeatLossCalculate: typeof energyInputExhaustGasHeatLossCalculate;
    energyInputAvailableHeat: typeof energyInputAvailableHeat;
    energyInputHeatDelivered: typeof energyInputHeatDelivered;
    energyInputTotalHeatLoss: typeof energyInputTotalHeatLoss;
};
