/**
 * Atmosphere Heat Loss Calculator.
 *
 * Calculates the total heat loss from escaping atmospheric gas in a furnace
 * or heating system.
 */

/**
 * Calculates the total heat loss from escaping atmospheric gas.
 *
 * @param flow_rate Flow rate of gas, units SCFH (standard cubic feet per hour)
 * @param specific_heat Specific heat of gas, units BTU/SCF/degF
 * @param inlet_temperature Inlet temperature of gas, units degF
 * @param outlet_temperature Outlet temperature of gas, units degF
 * @param correction_factor Correction factor (unitless)
 * @returns Total heat loss, units BTU/hr
 */
export function atmosphereTotalHeatLoss(
    flow_rate: number,
    specific_heat: number,
    inlet_temperature: number,
    outlet_temperature: number,
    correction_factor: number
): number;

export type AtmosphereHeatLossModule = {
    atmosphereTotalHeatLoss: typeof atmosphereTotalHeatLoss;
};
