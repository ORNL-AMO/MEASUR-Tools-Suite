/**
 * Pneumatic Air Requirement
 *
 * Calculates compressed air requirements for single-acting and double-acting
 * pneumatic cylinders.
 */

/**
 * Input parameters for the single-acting piston air requirement calculation.
 *
 * @property cylinderDiameter double, inner bore diameter of the cylinder in inches.
 * @property cylinderStroke double, piston travel distance per stroke in inches.
 * @property airPressure double, operating gauge pressure at the cylinder inlet in psi.
 * @property cyclesPerMin double, number of complete cycles per minute.
 */
export interface PneumaticAirRequirementSingleActingInput {
    /** inner bore diameter of the cylinder in inches. */
    cylinderDiameter: number;
    /** piston travel distance per stroke in inches. */
    cylinderStroke: number;
    /** operating gauge pressure at the cylinder inlet units psi. */
    airPressure: number;
    /** Number of complete cycles per minute, units cycles/min. */
    cyclesPerMin: number;
}

/**
 * Input parameters for the double-acting piston air requirement calculation.
 *
 * @property cylinderDiameter double, inner bore diameter of the cylinder in inches.
 * @property cylinderStroke double, piston travel distance per stroke in inches.
 * @property pistonRodDiameter double, diameter of the piston rod in inches.
 * @property airPressure double, operating gauge pressure at the cylinder inlet in psi.
 * @property cyclesPerMin double, number of complete cycles per minute.
 */
export interface PneumaticAirRequirementDoubleActingInput {
    /** inner bore diameter of the cylinder in inches. */
    cylinderDiameter: number;
    /** piston travel distance per stroke in inches. */
    cylinderStroke: number;
    /** diameter of the piston rod in inches. */
    pistonRodDiameter: number;
    /** operating gauge pressure at the cylinder inlet units psi. */
    airPressure: number;
    /** Number of complete cycles per minute, units cycles/min. */
    cyclesPerMin: number;
}

/**
 * Result of a pneumatic cylinder air requirement calculation.
 *
 * @property volumeAirIntakePiston double, cylinder air intake volume per minute at cylinder conditions in cfm.
 * @property compressionRatio double, ratio of absolute working pressure to atmospheric pressure.
 * @property airRequirementPneumaticCylinder double, free-air equivalent consumption in scfm.
 */
export interface PneumaticAirRequirementResult {
    /** cylinder air intake volume per minute at cylinder conditions units cfm. */
    volumeAirIntakePiston: number;
    /** Ratio of absolute working pressure to atmospheric pressure, dimensionless. */
    compressionRatio: number;
    /** free-air equivalent consumption units scfm. */
    airRequirementPneumaticCylinder: number;
}

/**
 * Calculates the air requirement for a single-acting pneumatic cylinder.
 * @param input {@link PneumaticAirRequirementSingleActingInput}
 * @returns {@link PneumaticAirRequirementResult} containing cylinder intake volume, compression ratio, and free-air requirement.
 */
export function calculatePneumaticAirRequirementSingleActing(
    input: PneumaticAirRequirementSingleActingInput
): PneumaticAirRequirementResult;

/**
 * Calculates the air requirement for a double-acting pneumatic cylinder.
 * @param input {@link PneumaticAirRequirementDoubleActingInput}
 * @returns {@link PneumaticAirRequirementResult} containing cylinder intake volume, compression ratio, and free-air requirement.
 */
export function calculatePneumaticAirRequirementDoubleActing(
    input: PneumaticAirRequirementDoubleActingInput
): PneumaticAirRequirementResult;

export type PneumaticAirRequirementModule = {
    calculatePneumaticAirRequirementSingleActing: typeof calculatePneumaticAirRequirementSingleActing;
    calculatePneumaticAirRequirementDoubleActing: typeof calculatePneumaticAirRequirementDoubleActing;
};
