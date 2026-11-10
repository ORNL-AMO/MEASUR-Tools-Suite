/** Stateless fan control and diameter-change energy calculations using delivered baseline power. */

/** Fan motor control selecting the flow-to-power relationship. */
export enum MotorControlType {
    /** Full-speed operation while on. */
    OnOff = 0,
    /** Full-speed, half-speed, and off time sharing. */
    TwoSpeed = 1,
    /** Variable-speed control using the cubic flow law. */
    VSD = 2,
    /** No speed adjustment; control factor is one. */
    None = 3
}

/** Representation of desired flow relative to the original fan. */
export enum FlowMode {
    /** Percentage of the original fan's rated flow. */
    Percent = 0,
    /** Volume flow in the same units as ratedFlow. */
    Volume = 1
}

/** Complete caller-validated fan data; a plain object requiring no delete(). */
export interface FanAffinityLawsInput {
    /** Electricity rate, units $/kWh; greater than zero. */
    electricityCost: number;
    /** Drive efficiency, units %, greater than zero and at most 100. */
    driveEfficiency: number;
    /** Motor efficiency, units %, greater than zero and at most 100. */
    motorEfficiency: number;
    /** Baseline flow as % of rated flow, units %, 0-100; finite and positive for VSD/Two-Speed. */
    flowPercentBaseline: number;
    /** Annual operating time, units h/year; greater than zero and at most 8760. */
    operatingHours: number;
    /** Delivered fan power at the baseline operating point, units kW; greater than zero. */
    motorPower: number;
    /** Rated volume flow, units CFM or any consistent flow unit (e.g. m^3/s); greater than zero. */
    ratedFlow: number;
    /** Baseline control. OnOff/None use a baseline control factor of one. */
    motorControlTypeCurrent: MotorControlType;
    /** Modified control. */
    motorControlTypeNew: MotorControlType;
    /** Desired-flow input representation. */
    flowMode: FlowMode;
    /** Desired flow: same volume-flow unit as ratedFlow in Volume mode, or units % (0-100) in Percent mode. */
    desiredFlowRate: number;
}

/** Annual electrical energy and signed savings; a plain object requiring no delete(). */
export interface FanAffinityLawsResult {
    /** Baseline electrical energy, units kWh/year. */
    annualEnergyBaseline: number;
    /** Modified electrical energy, units kWh/year. */
    annualEnergyNew: number;
    /** Signed savings, units $/year; negative means increased cost. */
    annualCostSavings: number;
}

/** Two-speed power factor and time shares for caller-supplied flow in [0,1]; plain values requiring no delete(). */
export interface FanAffinityLawsTimeFactorResult {
    /** Average power divided by full-speed power, dimensionless fraction 0-1. */
    factor: number;
    /** Time at full speed, dimensionless fraction 0-1. */
    timeAbove50Percent: number;
    /** Time at half speed, dimensionless fraction 0-1. */
    timeAt50Percent: number;
    /** Time off, dimensionless fraction 0-1. */
    timeAt0Percent: number;
}

/**
 * Calculates annual energy and savings without changing fan diameter.
 * Normalizes delivered baseline power to full-speed power before applying modified control.
 * @param input Complete fan data; units documented per member. Percentages use 0-100 values.
 * @returns Annual electrical energy in kWh/year and signed savings in $/year; no delete().
 * Desktop/callers own all input validation. No input checks, defaults, or clamping are applied;
 * invalid inputs can produce nonphysical values, infinity, or NaN.
 */
export declare function calculateFanAffinityLaws(input: FanAffinityLawsInput): FanAffinityLawsResult;

/**
 * Calculates annual energy and savings with a fan diameter change.
 * Rated flow scales with diameter cubed; full-speed power scales with diameter to the fifth power.
 * VSD and Two-Speed both use desired flow divided by the resized fan's rated flow.
 * @param input Complete fan data; desired flow remains referenced to the original rated flow.
 * @param currentDiameter Original fan diameter, units in; greater than zero.
 * @param newDiameter Modified fan diameter, units in; greater than zero.
 * @returns Annual electrical energy in kWh/year and signed savings in $/year; no delete().
 * Desktop/callers own diameter and input validation. No input checks, defaults, or clamping
 * are applied; invalid inputs can produce nonphysical values, infinity, or NaN.
 */
export declare function calculateFanAffinityLawsWithFanSize(
    input: FanAffinityLawsInput,
    currentDiameter: number,
    newDiameter: number
): FanAffinityLawsResult;

/**
 * Resolves a Two-Speed fan's average power factor and time at full speed, half speed, and off.
 * @param flowFraction Average flow divided by rated flow, dimensionless fraction 0-1 (not percent).
 * @returns Dimensionless power factor and time shares; for caller-supplied flow in [0,1],
 * shares are in [0,1] and sum to one. No delete().
 * Desktop/callers own the input domain. No input checks or clamping are applied.
 * Out-of-range flow can yield negative time shares; nonfinite arithmetic is propagated.
 * Zero is valid for this helper, but cannot normalize positive baseline power.
 */
export declare function get50PercentTimeFactor(flowFraction: number): FanAffinityLawsTimeFactorResult;

/** Runtime functions and enums contributed by the fan-affinity-laws binding. */
export type FanAffinityLawsModule = {
    MotorControlType: typeof MotorControlType;
    FlowMode: typeof FlowMode;
    calculateFanAffinityLaws: typeof calculateFanAffinityLaws;
    calculateFanAffinityLawsWithFanSize: typeof calculateFanAffinityLawsWithFanSize;
    get50PercentTimeFactor: typeof get50PercentTimeFactor;
};
