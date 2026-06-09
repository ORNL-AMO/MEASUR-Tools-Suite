/**
 * @brief Input parameters for the pipe sizing calculation.
 *
 * @var airflow double, volumetric free-air flow rate in cfm.
 * @var airlinePressure double, operating gauge pressure in the pipe in psig.
 * @var designVelocity double, maximum allowable compressed-air velocity in ft/s.
 * @var atmosphericPressure double, local atmospheric pressure in psia.
 */
export interface PipeSizingInput {
    airflow: number;
    airlinePressure: number;
    designVelocity: number;
    atmosphericPressure: number;
}

/**
 * @brief Result of the pipe sizing calculation.
 *
 * @var crossSectionalArea double, minimum required internal pipe area in in^2.
 * @var pipeDiameter double, minimum required internal pipe diameter in inches.
 */
export interface PipeSizingResult {
    crossSectionalArea: number;
    pipeDiameter: number;
}

/**
 * @brief Calculates the minimum pipe cross-sectional area and diameter for a compressed air system.
 * @details Converts free-air flow to compressed-air volume at operating pressure and
 *          computes the minimum circular internal diameter for the design velocity.
 * @param input PipeSizingInput
 * @return PipeSizingResult containing `crossSectionalArea` [in^2] and `pipeDiameter` [in].
 */
export function calculatePipeSize(input: PipeSizingInput): PipeSizingResult;

/** Factory function to load the Pipe Sizing. */
export default function PipeSizingModule(): Promise<{
    calculatePipeSize: typeof calculatePipeSize;
}>;

