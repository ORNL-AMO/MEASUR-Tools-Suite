/** Stateless motor power-factor calculation with loaded and near-zero-load paths. */
import type { LineFrequency, MotorEfficiencyClass } from "./motorEnum";

/** Complete required inputs; passed as a plain object without allocation or delete(). */
export interface MotorPowerFactorInput {
    /** Nominal line-frequency selection; used only when abs(loadFactor) < 0.001. */
    lineFrequency: LineFrequency;
    /** Motor speed, units rpm; used only near zero load. */
    motorRpm: number;
    /** Motor efficiency model; near-zero PREMIUM requires a 2-, 4-, or 6-pole motor. */
    efficiencyClass: MotorEfficiencyClass;
    /** Specified efficiency, dimensionless fraction; near-zero SPECIFIED uses it, other classes ignore it. */
    specifiedEfficiency: number;
    /** Motor rated shaft power, units hp. */
    motorRatedPower: number;
    /** Fraction of rated shaft load, dimensionless; abs(value) < 0.001 selects the near-zero path. */
    loadFactor: number;
    /** Motor RMS line current, units A. */
    motorCurrent: number;
    /** Operating motor efficiency, dimensionless fraction; ignored near zero load. */
    motorEfficiency: number;
    /** Supplied RMS line-to-line voltage, units V; ignored near zero load in favor of fixed 460 V. */
    ratedVoltage: number;
}

/**
 * Calculates motor power factor as the ratio of real to apparent electrical power.
 * For abs(loadFactor) < 0.001, uses modeled zero-load loss and fixed 460 V;
 * otherwise uses supplied load, operating efficiency, current and voltage.
 * All fields are required. No numerical validation, defaults or clamping are applied;
 * negative and nonfinite arithmetic results and near-zero efficiency-model errors are retained.
 * For a physically meaningful near-zero SPECIFIED model, specifiedEfficiency must be positive;
 * negative values propagate the model's error.
 *
 * @param input Complete nameplate and operating data, with per-field units documented above; not modified.
 * @returns Power factor, dimensionless fraction (normally 0-1), not percentage points.
 * The plain input and scalar result require no delete() calls.
 */
export declare function calculateMotorPowerFactor(input: MotorPowerFactorInput): number;

/** Runtime function contributed by the motor power-factor binding. */
export type MotorPowerFactorModule = {
    calculateMotorPowerFactor: typeof calculateMotorPowerFactor;
};
