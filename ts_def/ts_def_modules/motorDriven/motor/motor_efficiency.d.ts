import type { LineFrequency, MotorEfficiencyClass } from "./motorEnum";

/** Inputs for the stateless motor-efficiency calculation. */
export interface MotorEfficiencyInput {
    /** Nominal electrical line-frequency selection. */
    lineFrequency: LineFrequency;
    /** Measured motor speed, units rpm. */
    motorRpm: number;
    /** Motor efficiency classification. */
    efficiencyClass: MotorEfficiencyClass;
    /** Rated motor power, units hp. */
    motorRatedPower: number;
    /** Operating load, dimensionless fraction. */
    loadFactor: number;
    /**
     * Specified motor efficiency, dimensionless fraction.
     * Required and nonnegative for the specified class; ignored for other classes.
     */
    specifiedEfficiency: number;
}

/**
 * Estimates motor efficiency at the requested load.
 *
 * @param input Motor characteristics and operating load.
 * @returns Estimated motor efficiency, dimensionless fraction.
 */
export declare function calculateMotorEfficiency(input: MotorEfficiencyInput): number;

/** Runtime exports contributed by the motor-efficiency binding. */
export type MotorEfficiencyModule = {
    calculateMotorEfficiency: typeof calculateMotorEfficiency;
};
