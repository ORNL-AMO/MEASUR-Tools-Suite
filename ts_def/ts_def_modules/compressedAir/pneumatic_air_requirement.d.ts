/**
 * @brief Input parameters for the single-acting piston air requirement calculation.
 *
 * @var cylinderDiameter double, inner bore diameter of the cylinder in inches.
 * @var cylinderStroke double, piston travel distance per stroke in inches.
 * @var airPressure double, operating gauge pressure at the cylinder inlet in psi.
 * @var cyclesPerMin double, number of complete cycles per minute.
 */
export interface PneumaticAirRequirementSingleActingInput {
    cylinderDiameter: number;
    cylinderStroke: number;
    airPressure: number;
    cyclesPerMin: number;
}

/**
 * @brief Input parameters for the double-acting piston air requirement calculation.
 *
 * @var cylinderDiameter double, inner bore diameter of the cylinder in inches.
 * @var cylinderStroke double, piston travel distance per stroke in inches.
 * @var pistonRodDiameter double, diameter of the piston rod in inches.
 * @var airPressure double, operating gauge pressure at the cylinder inlet in psi.
 * @var cyclesPerMin double, number of complete cycles per minute.
 */
export interface PneumaticAirRequirementDoubleActingInput {
    cylinderDiameter: number;
    cylinderStroke: number;
    pistonRodDiameter: number;
    airPressure: number;
    cyclesPerMin: number;
}

/**
 * @brief Result of a pneumatic cylinder air requirement calculation.
 *
 * @var volumeAirIntakePiston double, cylinder air intake volume per minute at cylinder conditions in cfm.
 * @var compressionRatio double, ratio of absolute working pressure to atmospheric pressure.
 * @var airRequirementPneumaticCylinder double, free-air equivalent consumption in scfm.
 */
export interface PneumaticAirRequirementResult {
    volumeAirIntakePiston: number;
    compressionRatio: number;
    airRequirementPneumaticCylinder: number;
}

/**
 * @brief Calculates the air requirement for a single-acting pneumatic cylinder.
 * @param input PneumaticAirRequirementSingleActingInput
 * @return PneumaticAirRequirementResult containing cylinder intake volume, compression ratio, and free-air requirement.
 */
export function calculatePneumaticAirRequirementSingleActing(
    input: PneumaticAirRequirementSingleActingInput
): PneumaticAirRequirementResult;

/**
 * @brief Calculates the air requirement for a double-acting pneumatic cylinder.
 * @param input PneumaticAirRequirementDoubleActingInput
 * @return PneumaticAirRequirementResult containing cylinder intake volume, compression ratio, and free-air requirement.
 */
export function calculatePneumaticAirRequirementDoubleActing(
    input: PneumaticAirRequirementDoubleActingInput
): PneumaticAirRequirementResult;

/** Factory function to load the Pneumatic Air Requirement. */
export default function PneumaticAirRequirementModule(): Promise<{
    calculatePneumaticAirRequirementSingleActing: typeof calculatePneumaticAirRequirementSingleActing;
    calculatePneumaticAirRequirementDoubleActing: typeof calculatePneumaticAirRequirementDoubleActing;
}>;

