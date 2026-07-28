/**
 * Gas Cooling Heat Loss calculations.
 *
 * Calculates the total heat loss due to gas (including air) cooling in process
 * heating equipment. Assumes no phase change; uses sensible heat only.
 *
 */

/**
 * Calculate total heat loss due to gas (including air) cooling in process heating equipment.
 *
 * Computes the heat loss removed by a cooling gas based on flow rate,
 * temperature difference, specific heat, correction factor, and gas density.
 * No phase change is assumed; sensible heat only.
 *
 * @param flow_rate Gas volumetric flow rate, units scf/min
 * @param initial_temperature Inlet temperature of gas, units degF
 * @param final_temperature Outlet temperature of gas, units degF
 * @param specific_heat Specific heat of gas, units BTU/scf/degF
 * @param correction_factor Correction factor (unitless)
 * @param gas_density Gas density, units lb/scf
 * @returns Total heat loss, units BTU/hr
 */
export function gasCoolingTotalHeatLoss(
    flow_rate: number,
    initial_temperature: number,
    final_temperature: number,
    specific_heat: number,
    correction_factor: number,
    gas_density: number
): number;

export type GasCoolingHeatLossModule = {
    gasCoolingTotalHeatLoss: typeof gasCoolingTotalHeatLoss;
};
