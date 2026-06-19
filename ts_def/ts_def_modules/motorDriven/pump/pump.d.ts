import { Motor } from "../motor/motor";
import { Drive, LoadEstimationMethod } from "../motor/motorEnum";
import { PumpStyle, SpecificSpeed } from "../pumpFan/pumpFan";

/**
 * Pump calculations.
 *
 * Provides pump head tools and pump-system result calculators for baseline
 * and modified operating conditions.
 */

/**
 * Result object returned by head tool calculations.
 */
export declare class HeadToolOutput {
    /**
     * Constructor for HeadToolOutput
     * @param differentialElevationHead Differential elevation head, units ft.
     * @param differentialPressureHead Differential pressure head, units ft.
     * @param differentialVelocityHead Differential velocity head, units ft.
     * @param estimatedSuctionFrictionHead Estimated suction friction head, units ft.
     * @param estimatedDischargeFrictionHead Estimated discharge friction head, units ft.
     * @param pumpHead Total pump head, units ft.
     */
    constructor(
        differentialElevationHead: number,
        differentialPressureHead: number,
        differentialVelocityHead: number,
        estimatedSuctionFrictionHead: number,
        estimatedDischargeFrictionHead: number,
        pumpHead: number
    );

    /** Differential elevation head, units ft */
    differentialElevationHead: number;
    /** Differential pressure head, units ft */
    differentialPressureHead: number;
    /** Differential velocity head, units ft */
    differentialVelocityHead: number;
    /** Estimated suction friction head, units ft */
    estimatedSuctionFrictionHead: number;
    /** Estimated discharge friction head, units ft */
    estimatedDischargeFrictionHead: number;
    /** Total pump head, units ft */
    pumpHead: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Head tool model for systems with a suction tank.
 */
export declare class HeadToolSuctionTank {
    /**
     * @param specificGravity double, specific gravity, dimensionless (unitless)
     * @param flowRate double, flow rate in gpm
     * @param suctionPipeDiameter Suction pipe diameter, units ft.
     * @param suctionTankGasOverPressure double, suction tank gas over pressure in psig
     * @param suctionTankFluidSurfaceElevation double, suction tank fluid surface elevation in ft
     * @param suctionLineLossCoefficients double, suction line loss coefficients (unitless)
     * @param dischargePipeDiameter Discharge pipe diameter, units ft.
     * @param dischargeGaugePressure double, discharge gauge pressure in psig
     * @param dischargeGaugeElevation Discharge gauge elevation, units ft.
     * @param dischargeLineLossCoefficients double, discharge line loss coefficients (unitless)
     */
    constructor(
        specificGravity: number,
        flowRate: number,
        suctionPipeDiameter: number,
        suctionTankGasOverPressure: number,
        suctionTankFluidSurfaceElevation: number,
        suctionLineLossCoefficients: number,
        dischargePipeDiameter: number,
        dischargeGaugePressure: number,
        dischargeGaugeElevation: number,
        dischargeLineLossCoefficients: number
    );

    /**
     * Calculates the operating pump head
     * @returns HeadToolOutput
     */
    calculate(): HeadToolOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Head tool model for systems without a suction tank.
 */
export declare class HeadTool {
    /**
     * Constructor for HeadTool with no Suction Tank, all inputs specified
     *
     * @param specificGravity double, specific gravity, dimensionless - unitless
     * @param flowRate double, flow rate in gpm (gallons per minute)
     * @param suctionPipeDiameter double, diameter of suction pipe in feet
     * @param suctionGaugePressure double, gauge pressure of suction in psig (pounds per square inch guage)
     * @param suctionGaugeElevation double, gauge elevation of suction in feet
     * @param suctionLineLossCoefficients double, line loss coefficients of suction - unitless
     * @param dischargePipeDiameter double, diameter of discharge pipe in feet
     * @param dischargeGaugePressure double, gauge pressure of discharge in psig (pounds per square inch guage)
     * @param dischargeGaugeElevation double, gauge elevation of discharge in feet
     * @param dischargeLineLossCoefficients double, line loss coefficients of discharge - unitless
     *
     * */
    constructor(
        specificGravity: number,
        flowRate: number,
        suctionPipeDiameter: number,
        suctionGaugePressure: number,
        suctionGaugeElevation: number,
        suctionLineLossCoefficients: number,
        dischargePipeDiameter: number,
        dischargeGaugePressure: number,
        dischargeGaugeElevation: number,
        dischargeLineLossCoefficients: number
    );

    /**
     * Calculates the operating pump head
     * @returns HeadToolOutput
     */
    calculate(): HeadToolOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

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
     * @param annual_energy Annual energy, units kWh/year.
     * @param annual_cost Annual cost, units $/year.
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
    /** Annual energy, units kWh */
    annual_energy: number;
    /** Annual cost, units $ */
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
    HeadToolOutput: typeof HeadToolOutput;
    HeadToolSuctionTank: typeof HeadToolSuctionTank;
    HeadTool: typeof HeadTool;
    PumpResultInput: typeof PumpResultInput;
    PumpFieldData: typeof PumpFieldData;
    PumpResult: typeof PumpResult;
    PumpResults: typeof PumpResults;
};
