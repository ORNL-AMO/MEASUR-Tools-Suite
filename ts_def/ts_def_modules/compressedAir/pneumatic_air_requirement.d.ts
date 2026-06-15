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
    cylinderDiameter: number;
    cylinderStroke: number;
    airPressure: number;
    cyclesPerMin: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
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
    cylinderDiameter: number;
    cylinderStroke: number;
    pistonRodDiameter: number;
    airPressure: number;
    cyclesPerMin: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result of a pneumatic cylinder air requirement calculation.
 *
 * @property volumeAirIntakePiston double, cylinder air intake volume per minute at cylinder conditions in cfm.
 * @property compressionRatio double, ratio of absolute working pressure to atmospheric pressure.
 * @property airRequirementPneumaticCylinder double, free-air equivalent consumption in scfm.
 */
export interface PneumaticAirRequirementResult {
    volumeAirIntakePiston: number;
    compressionRatio: number;
    airRequirementPneumaticCylinder: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
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
    PneumaticAirRequirementSingleActingInput: PneumaticAirRequirementSingleActingInput;
    PneumaticAirRequirementDoubleActingInput: PneumaticAirRequirementDoubleActingInput;
    PneumaticAirRequirementResult: PneumaticAirRequirementResult;
};