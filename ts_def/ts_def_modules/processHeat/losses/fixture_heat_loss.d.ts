/**
 * Fixture Heat Loss calculations.
 *
 * Calculates the total heat loss from fixtures, trays, conveyor belts, and
 * similar equipment that enter the furnace at lower temperatures and are
 * heated to the furnace temperature. Assumes no melting or phase change of
 * the fixture material.
 *
 */

/**
 * Calculate total heat loss from fixtures, trays, or conveyors.
 *
 * Computes the heat loss caused by fixtures, trays, conveyor belts, and
 * similar equipment that enter the furnace at lower temperatures and are
 * heated to the furnace temperature. No melting or phase change is assumed.
 *
 * @param specific_heat Specific heat of fixture material, units BTU/lb/degF
 * @param feed_rate Feed rate of fixture material, units lb/hr
 * @param initial_temperature Initial temperature of fixture, units degF
 * @param final_temperature Final temperature of fixture, units degF
 * @param correction_factor Correction factor (unitless)
 * @returns Total heat loss, units BTU/hr
 */
export function fixtureTotalHeatLoss(
    specific_heat: number,
    feed_rate: number,
    initial_temperature: number,
    final_temperature: number,
    correction_factor: number
): number;

export type FixtureHeatLossModule = {
    fixtureTotalHeatLoss: typeof fixtureTotalHeatLoss;
};
