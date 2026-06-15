/**
 * Exhaust Gas Heat Loss calculations for Electric Arc Furnace (EAF).
 *
 * Calculates the total heat loss due to exhaust gases leaving an Electric Arc
 * Furnace, based on gas temperature, composition, flow rate, and dust loading.
 *
 */

/**
 * Calculate total heat loss due to exhaust gases in an Electric Arc Furnace (EAF).
 *
 * Computes the heat loss caused by exhaust gases leaving the EAF based on
 * gas temperature, composition (CO, H2, combustible gases), volume flow rate,
 * and dust loading.
 *
 * @param off_gas_temp Temperature of exhaust gases before mixing with outside air, units degF
 * @param co_percent Percent of CO in exhaust gas, units %
 * @param h2_percent Percent of H2 in exhaust gas, units %
 * @param combustible_gases_percent Average percent of combustible gases in exhaust, units %
 * @param volume_flow_rate Total volume of exhaust gases, units scf/min
 * @param dust_loading Dust loading for exhaust gases, units lb/scf
 * @returns Total heat loss, units BTU/hr
 */
export function exhaustGasEAFTotalHeatLoss(
    off_gas_temp: number,
    co_percent: number,
    h2_percent: number,
    combustible_gases_percent: number,
    volume_flow_rate: number,
    dust_loading: number
): number;

export type ExhaustGasHeatLossElectricArcFurnaceModule = {
    exhaustGasEAFTotalHeatLoss: typeof exhaustGasEAFTotalHeatLoss;
};
