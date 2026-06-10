/**
 * Input parameters for the estimate method compressed air leak calculation.
 *
 * @property operatingTime double, annual system operating time in hours.
 * @property leakRateEstimate double, estimated leak rate from visual/audible assessment in scfm.
 */
export interface EstimateMethodInput {
    operatingTime: number;
    leakRateEstimate: number;
}

/**
 * Result of the estimate method leak annual consumption calculation.
 *
 * @property annualConsumption double, estimated annual air loss from the leak in kscf.
 */
export interface EstimateMethodResult {
    annualConsumption: number;
}

/**
 * Estimates annual compressed air consumption from a leak using the estimate method.
 * @details Annual consumption is calculated from leak rate estimate and annual operating time.
 * @note Leak rate estimate must be in scfm and operating time in hours per year.
 * @param input Input for estimate method calculation.
 * @returns EstimateMethodResult containing `annualConsumption` [kscf].
 */
export function calculateEstimateMethod(input: EstimateMethodInput): EstimateMethodResult;

export type EstimateMethodModule = {
    calculateEstimateMethod: typeof calculateEstimateMethod;
    EstimateMethodInput: EstimateMethodInput;
    EstimateMethodResult: EstimateMethodResult;
};
