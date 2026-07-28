/**
 * Leak Survey - Estimate Method
 *
 * Estimates annual compressed air loss from an estimated leak flow rate and
 * annual operating time.
 */

/**
 * Input parameters for the estimate method compressed air leak calculation.
 *
 * @property operatingTime double, annual system operating time in hours.
 * @property leakRateEstimate double, estimated leak rate from visual/audible assessment in scfm.
 */
export interface EstimateMethodInput {
    /** annual system operating time in hours. */
    operatingTime: number;
    /** estimated leak rate from visual/audible assessment units scfm. */
    leakRateEstimate: number;
}

/**
 * Result of the estimate method leak annual consumption calculation.
 *
 * @property annualConsumption double, estimated annual air loss from the leak in kscf.
 */
export interface EstimateMethodResult {
    /** estimated annual air loss from the leak units kscf. */
    annualConsumption: number;
}

/**
 * Estimates annual compressed air consumption from a leak using the estimate method.
 * @details Annual consumption is calculated from leak rate estimate and annual operating time.
 * @note Leak rate estimate must be in scfm and operating time in hours per year.
 * @param input {@link EstimateMethodInput} for estimate method calculation.
 * @returns {@link EstimateMethodResult} containing `annualConsumption` [kscf].
 */
export function calculateEstimateMethod(input: EstimateMethodInput): EstimateMethodResult;

export type EstimateMethodModule = {
    calculateEstimateMethod: typeof calculateEstimateMethod;
};
