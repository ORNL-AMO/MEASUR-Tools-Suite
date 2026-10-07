import { Motor } from "../motor/motor";
import { Drive, LoadEstimationMethod } from "../motor/motorEnum";
import { PumpStyle, SpecificSpeed } from "../pumpFan/pumpFan";

/**
 * Pump calculations.
 *
 * Provides pump-system result calculators for baseline and modified operating conditions.
 */

/**
 * Input parameters for pump result calculations.
 */
export declare class PumpResultInput {
    /**
     * @param style PumpStyle, pump style selector
     * @param pumpEfficiency double, pump efficiency, dimensionless
     * @param rpm double, pump speed in RPM
     * @param drive Drive enum, drive type
     * @param kviscosity Kinematic viscosity, units cSt.
     * @param specificGravity double, specific gravity, dimensionless
     * @param stageCount Pump stage count.
     * @param speed SpecificSpeed, pump specific speed selector
     * @param specifiedEfficiency Specified optimal efficiency, dimensionless fraction.
     */
    constructor(
        style: PumpStyle,
        pumpEfficiency: number,
        rpm: number,
        drive: Drive,
        kviscosity: number,
        specificGravity: number,
        stageCount: number,
        speed: SpecificSpeed,
        specifiedEfficiency: number
    );

    /**
     * @param style PumpStyle, pump style selector
     * @param pumpEfficiency double, pump efficiency, dimensionless
     * @param rpm double, pump speed in RPM
     * @param drive Drive enum, drive type
     * @param kviscosity Kinematic viscosity, units cSt.
     * @param specificGravity double, specific gravity, dimensionless
     * @param stageCount Pump stage count.
     * @param speed SpecificSpeed, pump specific speed selector
     * @param specifiedEfficiency Specified optimal efficiency, dimensionless fraction.
     * @param differentialPressurePsi Operating differential pressure for positive-displacement pump result calculations,
     * units psi.
     */
    constructor(
        style: PumpStyle,
        pumpEfficiency: number,
        rpm: number,
        drive: Drive,
        kviscosity: number,
        specificGravity: number,
        stageCount: number,
        speed: SpecificSpeed,
        specifiedEfficiency: number,
        differentialPressurePsi: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Field data used for pump result calculations.
 */
export declare class PumpFieldData {
    /**
     * Constructor
     * @param flowRate double, rate of flow. Units are gpm
     * @param head double, pump head measured in feet
     * @param loadEstimationMethod LoadEstimationMethod, classification of load estimation method
     * @param motorPower double, power output of the pump's motor in hp.
     * @param motorAmps double, current measured from the pump's motor in amps
     * @param voltage double, the measured bus voltage in volts
     */
    constructor(
        flowRate: number,
        head: number,
        loadEstimationMethod: LoadEstimationMethod,
        motorPower: number,
        motorAmps: number,
        voltage: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by pump result calculations.
 */
export declare class PumpResults {
    /**
     * Constructor for PumpResults
     * @param pump_efficiency Pump efficiency, dimensionless fraction.
     * @param motor_rated_power Motor rated power, units hp.
     * @param motor_shaft_power Motor shaft power, units hp.
     * @param mover_shaft_power Mover shaft power, units hp.
     * @param motor_efficiency Motor efficiency, dimensionless fraction.
     * @param motor_power_factor Motor power factor, dimensionless.
     * @param motor_current Motor current, units A.
     * @param motor_power Motor power, units kW.
     * @param annual_energy Annual energy, units MWh/year.
     * @param annual_cost Annual cost, units thousand dollars/year.
     * @param load_factor Load factor, dimensionless fraction.
     * @param drive_efficiency Drive efficiency, dimensionless fraction.
     */
    constructor(
        pump_efficiency: number,
        motor_rated_power: number,
        motor_shaft_power: number,
        mover_shaft_power: number,
        motor_efficiency: number,
        motor_power_factor: number,
        motor_current: number,
        motor_power: number,
        annual_energy: number,
        annual_cost: number,
        load_factor: number,
        drive_efficiency: number
    );

    /** Pump efficiency, dimensionless fraction. */
    pump_efficiency: number;
    /** Motor rated power, units hp */
    motor_rated_power: number;
    /** Motor shaft power, units hp */
    motor_shaft_power: number;
    /** Mover shaft power, units hp */
    mover_shaft_power: number;
    /** Motor efficiency, dimensionless fraction. */
    motor_efficiency: number;
    /** Motor power factor, dimensionless, unitless */
    motor_power_factor: number;
    /** Motor current, units A */
    motor_current: number;
    /** Motor power, units kW */
    motor_power: number;
    /** Annual energy, units MWh/year */
    annual_energy: number;
    /** Annual cost, units thousand dollars/year */
    annual_cost: number;
    /** Load factor, dimensionless fraction. */
    load_factor: number;
    /** Drive efficiency, dimensionless fraction. */
    drive_efficiency: number;
    /** Estimated full-load amps, units A */
    estimatedFLA: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates existing and modified pump-system results.
 */
export declare class PumpResult {
    /**
     * Constructor
     * @param pumpInput Pump::Input, contains all pump-related data, passed by reference
     * @param motor Motor, contains all motor-related calculations, passed by reference
     * @param fieldData FieldData, contains all field data-related calculations, passed by reference
     * @param operatingHours Annual operating hours, units hr/year.
     * @param unitCost Electricity unit cost, units $/kWh.
     */
    constructor(pumpInput: PumpResultInput, motor: Motor, fieldData: PumpFieldData, operatingHours: number, unitCost: number);

    /**
     * Calculate for existing
     * @returns PumpResults
     */
    calculateExisting(): PumpResults;

    /**
     * Calculate for modifications
     * @returns PumpResults
     */
    calculateModified(): PumpResults;

    /**
     * Gets the annual savings potential
     * @returns double, annual savings potential in $/year
     */
    getAnnualSavingsPotential(): number;

    /**
     * Gets the optimization rating
     * @returns Optimization rating, units %.
     */
    getOptimizationRating(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type PumpModule = {
    PumpResultInput: typeof PumpResultInput;
    PumpFieldData: typeof PumpFieldData;
    PumpResult: typeof PumpResult;
    PumpResults: typeof PumpResults;
};
