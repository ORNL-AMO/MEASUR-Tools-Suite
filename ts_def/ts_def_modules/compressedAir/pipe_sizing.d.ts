/**
 * Compressed Air Pipe Sizing
 *
 * Calculates minimum cross-sectional area and diameter for compressed air
 * piping at a target design velocity.
 */

/**
 * Input parameters for the pipe sizing calculation.
 *
 * @property airflow double, volumetric free-air flow rate in cfm.
 * @property airlinePressure double, operating gauge pressure in the pipe in psig.
 * @property designVelocity double, maximum allowable compressed-air velocity in ft/s.
 * @property atmosphericPressure double, local atmospheric pressure in psia.
 */
export interface PipeSizingInput {
    airflow: number;
    airlinePressure: number;
    designVelocity: number;
    atmosphericPressure: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result of the pipe sizing calculation.
 *
 * @property crossSectionalArea double, minimum required internal pipe area in in^2.
 * @property pipeDiameter double, minimum required internal pipe diameter in inches.
 */
export interface PipeSizingResult {
    crossSectionalArea: number;
    pipeDiameter: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates the minimum pipe cross-sectional area and diameter for a compressed air system.
 * @details Converts free-air flow to compressed-air volume at operating pressure and
 *          computes the minimum circular internal diameter for the design velocity.
 * @param input {@link PipeSizingInput}
 * @returns {@link PipeSizingResult} containing `crossSectionalArea` [in^2] and `pipeDiameter` [in].
 */
export function calculatePipeSize(input: PipeSizingInput): PipeSizingResult;

export type PipeSizingModule = {
    calculatePipeSize: typeof calculatePipeSize;
    PipeSizingInput: PipeSizingInput;
    PipeSizingResult: PipeSizingResult;
};