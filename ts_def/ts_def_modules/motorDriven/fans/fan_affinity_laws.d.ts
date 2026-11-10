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

/** Complete required fan data; a plain object requiring no delete(). */
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

/** Two-speed power factor and time shares; plain dimensionless values requiring no delete(). */
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
 * @throws For inputs outside retained validation ranges, nonfinite/zero VSD or Two-Speed baseline
 * flow, or a Two-Speed modification flow fraction outside finite [0,1]. No general volume-flow
 * cap or result clamping is applied; VSD overcapacity volume inputs retain signed savings.
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
 * @throws For nonpositive diameters or inputs rejected by calculateFanAffinityLaws.
 */
export declare function calculateFanAffinityLawsWithFanSize(
    input: FanAffinityLawsInput,
    currentDiameter: number,
    newDiameter: number
): FanAffinityLawsResult;

/**
 * Resolves a Two-Speed fan's average power factor and time at full speed, half speed, and off.
 * @param flowFraction Average flow divided by rated flow, dimensionless fraction 0-1 (not percent).
 * @returns Dimensionless power factor and time fractions summing to one; no delete().
 * @throws When flowFraction is nonfinite or outside [0,1]. Zero is valid for this helper.
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
