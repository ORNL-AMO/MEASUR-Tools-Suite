/**
 * Slag/Other Material Heat Loss calculations.
 *
 * Calculates the total heat loss caused by heating slag or other combustion
 * byproducts within the furnace. Assumes the majority of slag is silicon and
 * that specific heat does not change with temperature. For glass structures
 * in slag, output may change significantly.
 *
 */

/**
 * Calculate total heat loss for slag or other material losses.
 *
 * Computes the heat loss caused by heating slag or other combustion
 * byproducts within the furnace. Assumes majority of slag is silicon and
 * specific heat does not vary with temperature.
 *
 * @param weight Weight discharged, units lb
 * @param inlet_temperature Inlet temperature of charged materials, units degF
 * @param outlet_temperature Outlet temperature, units degF
 * @param specific_heat Specific heat of material, units BTU/lb/degF
 * @param correction_factor Correction factor, unitless
 * @returns Total heat loss, units BTU
 */
export function slagOtherMaterialTotalHeatLoss(
    weight: number,
    inlet_temperature: number,
    outlet_temperature: number,
    specific_heat: number,
    correction_factor: number
): number;

export type SlagOtherMaterialHeatLossModule = {
    slagOtherMaterialTotalHeatLoss: typeof slagOtherMaterialTotalHeatLoss;
};
