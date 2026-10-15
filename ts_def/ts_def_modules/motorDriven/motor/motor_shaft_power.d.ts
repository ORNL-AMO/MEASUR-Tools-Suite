/** Stateless motor shaft-power and operating-point estimation from measured electrical power or current. */
import type { LineFrequency, LoadEstimationMethod, MotorEfficiencyClass } from "./motorEnum";

/** Complete required inputs, passed as a plain object without allocation or delete(). */
export interface MotorShaftPowerInput {
    /** Nameplate shaft power, units hp. */
    motorRatedPower: number;
    /** Measured real electrical input, units kW; ignored in CURRENT mode. */
    motorMeasuredPower: number;
    /** Nameplate speed, units rpm. */
    motorRpm: number;
    /** Nominal electrical line-frequency selection. */
    lineFrequency: LineFrequency;
    /** Efficiency model; current-model PREMIUM supports only 2/4/6 poles. */
    efficiencyClass: MotorEfficiencyClass;
    /** Efficiency, dimensionless fraction; used for SPECIFIED only. */
    specifiedEfficiency: number;
    /** Nameplate line-to-line voltage, units V. */
    ratedVoltage: number;
    /** Supplied full-load current, units A; zero does not select an estimated value. */
    fullLoadAmps: number;
    /** Measured operating line-to-line voltage, units V. */
    fieldVoltage: number;
    /** POWER selects measured kW; otherwise uses measured current. */
    loadEstimationMethod: LoadEstimationMethod;
    /** Measured line current, units A; ignored in POWER mode. */
    fieldCurrent: number;
}

/** Plain operating-point result; no delete() calls are required. */
export interface MotorShaftPowerResult {
    /** Mechanical motor output, units hp. */
    shaftPower: number;
    /** Operating line current, units A. */
    current: number;
    /** Real-to-apparent electrical power ratio, dimensionless fraction. */
    powerFactor: number;
    /** Mechanical-output to real-input efficiency, dimensionless fraction. */
    efficiency: number;
    /** Real electrical input, units kW. */
    power: number;
    /** Independently estimated full-load current, units A; distinct from supplied FLA. */
    estimatedFLA: number;
    /** Interpolated fraction of rated shaft load, dimensionless; not clamped to the search range. */
    loadFactor: number;
}

/**
 * Estimates shaft power using the retained empirical 1% load search and voltage corrections.
 * POWER preserves measured electrical kW; CURRENT preserves measured line A. Search stops on
 * strict measurement exceedance or load greater than 1.5; interpolation can extrapolate beyond
 * that range. All eleven fields are required, including the inactive measurement.
 * No numerical validation, defaults, fallback FLA or result clamping are applied. Degenerate
 * inputs retain nonfinite results and dependency errors. For meaningful results supply positive
 * rated power, voltages and FLA, and a positive specified-efficiency fraction for SPECIFIED.
 *
 * @param input Complete motor and operating data, with units documented per field; not modified.
 * @returns Plain result: shaft hp, electrical kW, current/estimated FLA in A, and dimensionless fractions.
 * Neither the input nor result requires delete().
 */
export declare function calculateMotorShaftPower(input: MotorShaftPowerInput): MotorShaftPowerResult;

/** Runtime function contributed by the motor shaft-power binding. */
export type MotorShaftPowerModule = {
    calculateMotorShaftPower: typeof calculateMotorShaftPower;
};
