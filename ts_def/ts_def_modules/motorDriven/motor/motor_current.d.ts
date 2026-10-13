/** Stateless supplied-FLA-normalized and raw-model motor-current calculations. */
import type { LineFrequency, MotorEfficiencyClass } from "./motorEnum";

/** Required motor nameplate and fractional-load inputs shared by both calculation paths. */
export interface MotorCurrentInput {
    /** Motor nameplate power, units hp. */
    motorRatedPower: number;
    /** Motor nameplate speed, units rpm. */
    motorRpm: number;
    /** Nominal electrical line-frequency selection. */
    lineFrequency: LineFrequency;
    /** Motor efficiency class. PREMIUM supports only 2-, 4-, or 6-pole speed/frequency selections. */
    efficiencyClass: MotorEfficiencyClass;
    /** Efficiency, dimensionless fraction. Must be positive for SPECIFIED; ignored otherwise. */
    specifiedEfficiency: number;
    /** Fraction of rated motor load, dimensionless. Values above 1.5 evaluate at 1.5; negative values extrapolate. */
    loadFactor: number;
    /** Positive motor nameplate voltage, units V. */
    ratedVoltage: number;
}

/** Plain result from supplied-FLA normalization; no delete() is required. */
export interface MotorCurrentOutput {
    /** Motor current at the selected load, normalized to supplied full-load current, units A. */
    current: number;
    /** Independently estimated full-load current from EstimateFLA, units A; not the supplied fullLoadAmps. */
    estimatedFLA: number;
}

/**
 * Calculates current using model anchors normalized to supplied full-load current.
 * Model preconditions are caller-owned and unvalidated: positive rated voltage, positive specified
 * efficiency for SPECIFIED, and 2/4/6 poles for PREMIUM. Input is not modified.
 *
 * @param input Motor nameplate and fractional-load inputs; plain object with no cleanup.
 * @param fullLoadAmps Supplied full-load current, units A. Zero produces zero current.
 * @returns Plain result containing calculated current and independently estimated FLA, both units A.
 */
export declare function calculateMotorCurrent(input: MotorCurrentInput, fullLoadAmps: number): MotorCurrentOutput;

/**
 * Calculates raw-model current for the optimal-motor path without voltage or supplied-FLA normalization.
 * Field-voltage adjustments belong to the consumer. The same unvalidated model preconditions and
 * load boundaries as calculateMotorCurrent apply. Input is not modified.
 *
 * @param input Motor nameplate and fractional-load inputs; plain object with no cleanup.
 * @returns Raw-model current at the selected load, units A.
 */
export declare function calculateOptimalMotorCurrent(input: MotorCurrentInput): number;

/** Runtime functions contributed by the motor-current binding. */
export type MotorCurrentModule = {
    calculateMotorCurrent: typeof calculateMotorCurrent;
    calculateOptimalMotorCurrent: typeof calculateOptimalMotorCurrent;
};
