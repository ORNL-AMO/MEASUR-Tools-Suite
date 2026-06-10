/**
 * Motor control types for the fan system.
 */
export enum MotorControlType {
    OnOff = 0,
    TwoSpeed = 1,
    VSD = 2,
    None = 3
}

/**
 * Flow mode for desired flow input.
 */
export enum FlowMode {
    Percent = 0,
    Volume = 1
}

/**
 * Output struct for FanAffinityLaws
 * @property annualEnergyBaseline double, Baseline energy consumption in kWh
 * @property annualEnergyNew double, Energy consumption in kWh
 * @property annualCostSavings double, Cost savings in $ based on change in energy consumption and electricity cost
 */
export interface FanAffinityLawsOutput {
    annualEnergyBaseline: number;
    annualEnergyNew: number;
    annualCostSavings: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input struct for FanAffinityLaws.
 * Use this struct to create input object and then use that object to create FanAffinityLaws object.
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
    electricityCost: number;
    driveEfficiency: number;
    motorEfficiency: number;
    flowPercentBaseline: number;
    operatingHours: number;
    motorPower: number;
    ratedFlow: number;
    motorControlTypeCurrent: MotorControlType;
    motorControlTypeNew: MotorControlType;
    flowMode: FlowMode;
    desiredFlowRate: number;
}

/**
 * Fan affinity law calculations for annual baseline/new energy and annual cost savings.
 */
export declare class FanAffinityLaws {
    /**
     * Constructor for FanAffinityLaws. Use this constructor with input object.
     * @param input Input struct containing all necessary input parameters for FanAffinityLaws
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
     * @returns Output struct containing annual energy baseline and changed annual energy in kWh
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
