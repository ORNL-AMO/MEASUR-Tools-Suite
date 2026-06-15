/**
 * Water Cooling Heat Loss calculations.
 *
 * Calculates the total heat loss due to water cooling in process heating
 * equipment. Assumes no phase change; uses sensible heat only.
 *
 */

/**
 * Calculate total heat loss due to water cooling in process heating equipment.
 *
 * Computes the heat loss removed by cooling water based on flow rate,
 * temperature difference, and a correction factor. No phase change is
 * assumed; sensible heat only.
 *
 * @param flowRate Cooling water flow rate, units gal/min
 * @param initialTemperature Initial/inlet water temperature, units degF
 * @param outletTemperature Outlet water temperature, units degF
 * @param correctionFactor Correction factor, unitless
 * @returns Total heat loss, units BTU/hr
 */
export function waterCoolingTotalHeatLoss(
    flowRate: number,
    initialTemperature: number,
    outletTemperature: number,
    correctionFactor: number
): number;

export type WaterCoolingHeatLossModule = {
    waterCoolingTotalHeatLoss: typeof waterCoolingTotalHeatLoss;
};
