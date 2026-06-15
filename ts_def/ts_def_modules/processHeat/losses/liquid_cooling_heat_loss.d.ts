/**
 * Liquid Cooling Heat Loss calculations.
 *
 * Calculates the total heat loss due to liquid cooling in process heating
 * equipment. Assumes no phase change; uses sensible heat only.
 *
 */

/**
 * Calculate total heat loss due to liquid cooling in process heating equipment.
 *
 * Computes the heat loss removed by a cooling liquid based on flow rate,
 * liquid density, temperature difference, specific heat, and a correction
 * factor. No phase change is assumed; sensible heat only.
 *
 * @param flow_rate Cooling liquid flow rate, units gal/min
 * @param density Liquid density, units lb/scf
 * @param initial_temperature Initial/inlet liquid temperature, units degF
 * @param outlet_temperature Outlet liquid temperature, units degF
 * @param specific_heat Specific heat of liquid, units BTU/lb/degF
 * @param correction_factor Correction factor, unitless
 * @returns Total heat loss, units BTU/hr
 */
export function liquidCoolingTotalHeatLoss(
    flow_rate: number,
    density: number,
    initial_temperature: number,
    outlet_temperature: number,
    specific_heat: number,
    correction_factor: number
): number;

export type LiquidCoolingHeatLossModule = {
    liquidCoolingTotalHeatLoss: typeof liquidCoolingTotalHeatLoss;
};
