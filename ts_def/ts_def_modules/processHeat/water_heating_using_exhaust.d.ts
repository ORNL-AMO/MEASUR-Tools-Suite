/**
 * Water Heating Using Exhaust calculations.
 *
 * Calculates recovered heat, hot water flow, refrigeration tons,
 * chiller capacity, and electrical energy.
 */

/**
 * Result object returned by {@link waterHeatingUsingExhaust}.
 *
 * @property recoveredHeat double, recovered heat in Btu/hr
 * @property hotWaterFlow double, hot water flow in gal/hr
 * @property tonsRefrigeration double, tons of refrigeration in tons
 * @property capacityChiller double, chiller capacity in tons
 * @property electricalEnergy double, electrical energy in Btu/hr
 */
export interface WaterHeatingUsingExhaustOutput {
    /** Recovered heat, units Btu/hr */
    recoveredHeat: number;
    /** Hot water flow, units gal/hr */
    hotWaterFlow: number;
    /** Tons of refrigeration, units ton */
    tonsRefrigeration: number;
    /** Chiller capacity, units ton */
    capacityChiller: number;
    /** Electrical energy, units Btu/hr */
    electricalEnergy: number;
}

/**
 * Calculate energy savings from using exhaust gas heat to drive an absorption chiller.
 *
 * @param available_heat Fraction of available heat (percentage as fraction)
 * @param heat_input Heat input in Btu/hr
 * @param hx_efficiency Heat exchanger efficiency (fraction)
 * @param chiller_in_temperature Chiller inlet temperature in degF
 * @param chiller_out_temperature Chiller outlet temperature in degF
 * @param cop_chiller Coefficient of performance for chiller (fraction)
 * @param chiller_efficiency Chiller efficiency (fraction)
 * @param cop_compressor Coefficient of performance for compressor (fraction)
 * @returns {@link WaterHeatingUsingExhaustOutput}
 */
export function waterHeatingUsingExhaust(
    available_heat: number,
    heat_input: number,
    hx_efficiency: number,
    chiller_in_temperature: number,
    chiller_out_temperature: number,
    cop_chiller: number,
    chiller_efficiency: number,
    cop_compressor: number
): WaterHeatingUsingExhaustOutput;

export type WaterHeatingUsingExhaustModule = {
    waterHeatingUsingExhaust: typeof waterHeatingUsingExhaust;
};
