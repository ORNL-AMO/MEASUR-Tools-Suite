import type { LineFrequency, MotorEfficiencyClass } from "./motorEnum";

/** Inputs for the stateless estimated full-load-current calculation. */
export interface EstimateFLAInput {
    /** Rated motor power, units hp. */
    motorRatedPower: number;
    /** Motor nameplate speed, units rpm. */
    motorRpm: number;
    /** Nominal electrical line-frequency selection. */
    lineFrequency: LineFrequency;
    /** Motor efficiency classification. */
    efficiencyClass: MotorEfficiencyClass;
    /** Specified motor efficiency, dimensionless fraction. Used only for the specified class. */
    specifiedEfficiency: number;
    /** Motor nameplate voltage, units V. */
    ratedVoltage: number;
}

/**
 * Retained partial-load current anchors, units A, in fixed load order:
 * 0%, 25%, 50%, 75%, 100%, and 125%.
 */
export type EstimateFLAPartialLoadCurrents = [
    zeroPercent: number,
    twentyFivePercent: number,
    fiftyPercent: number,
    seventyFivePercent: number,
    oneHundredPercent: number,
    oneHundredTwentyFivePercent: number
];

/** Results from the stateless estimated full-load-current calculation. */
export interface EstimateFLAOutput {
    /** Estimated full-load current, units A. */
    estimatedFLA: number;
    /**
     * Retained coefficient-curve current anchors, units A.
     * These are not voltage- or specified-efficiency-adjusted; see {@link estimatedFLA} for that adjusted value.
     */
    partialLoadCurrents: EstimateFLAPartialLoadCurrents;
}

/**
 * Estimates a motor's full-load current and retained partial-load current anchors.
 *
 * @param input Motor nameplate and efficiency-class inputs.
 * @returns Estimated full-load current and six current anchors.
 */
export declare function calculateEstimateFLA(input: EstimateFLAInput): EstimateFLAOutput;

/** Runtime exports contributed by the estimated-full-load-current binding. */
export type EstimateFLAModule = {
    calculateEstimateFLA: typeof calculateEstimateFLA;
};
