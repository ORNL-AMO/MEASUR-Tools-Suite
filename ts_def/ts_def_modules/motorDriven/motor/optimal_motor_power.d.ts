/** Stateless electrical operating-point estimation for a supplied motor shaft-power requirement. */
import type { LineFrequency, MotorEfficiencyClass } from "./motorEnum";

/** Complete required motor and operating data; plain object without allocation or delete(). */
export interface OptimalMotorPowerInput {
    /** Nameplate shaft power, units hp. */
    motorRatedPower: number;
    /** Nameplate speed, units rpm. */
    motorRpm: number;
    /** Nominal electrical line-frequency selection. */
    lineFrequency: LineFrequency;
    /** Efficiency model; PREMIUM current model supports only 2/4/6 poles. */
    efficiencyClass: MotorEfficiencyClass;
    /** Efficiency, dimensionless fraction; used for SPECIFIED only. */
    specifiedEfficiency: number;
    /** Nameplate line-to-line voltage, units V. */
    ratedVoltage: number;
    /** Operating line-to-line voltage, units V. */
    fieldVoltage: number;
    /** Required mechanical motor shaft output, units hp. */
    optimalMotorShaftPower: number;
}

/** Plain estimated electrical operating point; no delete() calls are required. */
export interface OptimalMotorPowerResult {
    /** Real electrical input, units kW. */
    power: number;
    /** Mechanical-output to real-input efficiency, dimensionless fraction. */
    efficiency: number;
    /** Operating line current, units A. */
    current: number;
    /** Real-to-apparent electrical power ratio, dimensionless fraction. */
    powerFactor: number;
    /** Interpolated fraction of rated shaft load, dimensionless. */
    loadFactor: number;
}

/**
 * Estimates electrical demand for a supplied shaft requirement, without selecting motor size.
 * Retains the empirical 1% load search, interpolation and voltage corrections. Search stops
 * on strict shaft-power exceedance or load greater than 1.5; results may extrapolate beyond
 * that range. All eight fields are required. No numerical validation, defaults or clamping
 * are applied; degenerate inputs retain nonfinite arithmetic and dependency errors.
 * For meaningful results supply positive rated power/voltages and a positive specified
 * efficiency fraction for SPECIFIED, subject to the underlying motor model's limits.
 * @param input Complete motor and operating data, with units documented per field; not modified.
 * @returns Plain result with electrical kW, current in A, and dimensionless fractions.
 * Neither the input nor result requires delete().
 */
export declare function calculateOptimalMotorPower(input: OptimalMotorPowerInput): OptimalMotorPowerResult;

/** Runtime function contributed by the optimal motor-power binding. */
export type OptimalMotorPowerModule = {
    calculateOptimalMotorPower: typeof calculateOptimalMotorPower;
};
