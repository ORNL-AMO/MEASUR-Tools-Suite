/**
 * Fan Affinity Laws
 *
 * Calculates baseline and modified fan energy use and annual energy cost
 * savings for motor-control and flow changes.
 */

/**
 * Enumeration representing motor control type for the fan system.
 */
export enum MotorControlType {
    OnOff = 0,
    TwoSpeed = 1,
    VSD = 2,
    None = 3
}

/**
 * Enumeration representing desired-flow input mode.
 */
export enum FlowMode {
    Percent = 0,
    Volume = 1
}

/**
 * Result object returned by {@link FanAffinityLaws.calculate} and {@link FanAffinityLaws.changeFanSize}.
 *
 * @property annualEnergyBaseline double, baseline annual energy in kWh
 * @property annualEnergyNew double, modified annual energy in kWh
 * @property annualCostSavings double, annual cost savings in $
 */
export interface FanAffinityLawsOutput {
    /** Baseline annual energy, units kWh */
    annualEnergyBaseline: number;
    /** Modified annual energy, units kWh */
    annualEnergyNew: number;
    /** Annual cost savings, units $ */
    annualCostSavings: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input object for {@link FanAffinityLaws}.
 *
 * @property electricityCost double, electric usage rate in $/kWh
 * @property driveEfficiency double, Efficiency of the drive percentage (1 - 100)
 * @property motorEfficiency double, Efficiency of the motor percentage (1 - 100)
 * @property flowPercentBaseline double, Flow rate change by percent (0 - 100)
 * @property operatingHours double, Hours for which the fan system operates per year - hours (1 - 8760 hours)
 * @property motorPower double, Motor Power in kW
 * @property ratedFlow double, Flow Rate in CFM
 * @property motorControlTypeCurrent MotorControlType enum, current motor control for the fan system
 * @property motorControlTypeNew MotorControlType enum, changed motor control for the fan system
 * @property flowMode FlowMode enum, mode for flow change - by percent or by volume
 * @property desiredFlowRate double, Desired flow rate based on flow mode
 *          If flow mode is volume desired flow rate is flow volume in CFM
 *          If flow mode is percentage desired flow rate is flow percentage (0 - 100)
 */
export interface FanAffinityLawsInput {
    /** Electricity cost, units $/kWh */
    electricityCost: number;
    /** Drive efficiency, units % */
    driveEfficiency: number;
    /** Motor efficiency, units % */
    motorEfficiency: number;
    /** Baseline flow percentage, units % */
    flowPercentBaseline: number;
    /** Annual operating hours, units h */
    operatingHours: number;
    /** Motor power, units kW */
    motorPower: number;
    /** Rated flow, units CFM */
    ratedFlow: number;
    /** Current motor control type */
    motorControlTypeCurrent: MotorControlType;
    /** New motor control type */
    motorControlTypeNew: MotorControlType;
    /** Flow mode */
    flowMode: FlowMode;
    /** Desired flow rate (units depend on flow mode) */
    desiredFlowRate: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Fan affinity law calculations for annual baseline/new energy and annual cost savings.
 */
export declare class FanAffinityLaws {
    /**
     * Constructor for FanAffinityLaws. Use this constructor with input object.
     * @param input {@link FanAffinityLawsInput} struct containing all necessary input parameters for FanAffinityLaws
     */
    constructor(input: FanAffinityLawsInput);

    /**
     * Constructor for FanAffinityLaws - Use this constructor when fan size is not changing.
     * @param electricityCost double, electric usage rate in $/kWh
     * @param driveEfficiency double, Efficiency of the drive percentage (1 - 100)
     * @param motorEfficiency double, Efficiency of the motor percentage (1 - 100)
     * @param flowPercentBaseline double, Flow rate change by percent (0 - 100)
     * @param operatingHours double, Hours for which the fan system operates per year - hours (1 - 8760 hours)
     * @param motorPower double, Motor Power in kW
     * @param ratedFlow double, Flow Rate in CFM
     * @param motorControlTypeCurrent MotorControlType enum, current motor control for the fan system
     * @param motorControlTypeNew MotorControlType enum, changed motor control for the fan system
     * @param flowMode FlowMode enum, mode for flow change - by percent or by volume
     * @param desiredFlowRate double, Desired flow rate based on flow mode
     *          If flow mode is volume desired flow rate is flow volume in CFM
     *          If flow mode is percentage desired flow rate is flow percentage (0 - 100)
     */
    constructor(
        electricityCost: number,
        driveEfficiency: number,
        motorEfficiency: number,
        flowPercentBaseline: number,
        operatingHours: number,
        motorPower: number,
        ratedFlow: number,
        motorControlTypeCurrent: MotorControlType,
        motorControlTypeNew: MotorControlType,
        flowMode: FlowMode,
        desiredFlowRate: number
    );

    /**
     * Compute annual baseline and changed energy based on current and changed state of motor Control
     *      at a desired flow rate by percent or by volume.
     * @returns Output struct containing annual energy baseline and changed annual energy in kWh
     */
    calculate(): FanAffinityLawsOutput;

    /**
     * Compute annual baseline and changed energy based on current and changed state of motor Control
     *      at a desired flow rate by percent or by volume with changing fan size.
     * @param fanDiameterCurrent double, Current fan diameter in inches
     * @param fanDiameter double, Changed fan diameter in inches
     * @returns {@link FanAffinityLawsOutput} struct containing annual energy baseline and changed annual energy in kWh
     */
    changeFanSize(fanDiameterCurrent: number, fanDiameter: number): FanAffinityLawsOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type FanAffinityLawsModule = {
    MotorControlType: typeof MotorControlType;
    FlowMode: typeof FlowMode;
    FanAffinityLaws: typeof FanAffinityLaws;
    FanAffinityLawsOutput: FanAffinityLawsOutput;
    FanAffinityLawsInput: FanAffinityLawsInput;
};