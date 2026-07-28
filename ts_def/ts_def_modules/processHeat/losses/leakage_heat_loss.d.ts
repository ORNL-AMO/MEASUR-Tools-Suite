/**
 * Leakage Heat Loss calculations.
 *
 * Calculates the total energy loss from hot gas leakages in process heating
 * furnaces. Should only be used when the furnace is operating at a positive
 * pressure. Computes heat loss from gases leaving the furnace via openings
 * other than the flue.
 *
 */

/**
 * Calculate total heat loss from hot gas leakage.
 *
 * Computes the heat loss caused by gases leaking from the furnace through
 * openings other than the flue. Use only when the furnace operates at
 * positive pressure.
 *
 * @param draft_pressure Furnace draft pressure, units inch H2O (inch water column)
 * @param opening_area Opening area, units sqft
 * @param leakage_gas_temperature Temperature of leaking gases, units degF
 * @param ambient_temperature Ambient temperature, units degF
 * @param coefficient_discharge Coefficient of discharge (flow coefficient), unitless
 * @param specific_gravity specific gravity, dimensionless, unitless
 * @param correction_factor Correction factor, unitless
 * @returns Total heat loss, units BTU/hr
 */
export function leakageTotalHeatLoss(
    draft_pressure: number,
    opening_area: number,
    leakage_gas_temperature: number,
    ambient_temperature: number,
    coefficient_discharge: number,
    specific_gravity: number,
    correction_factor: number
): number;

export type LeakageHeatLossModule = {
    leakageTotalHeatLoss: typeof leakageTotalHeatLoss;
};
