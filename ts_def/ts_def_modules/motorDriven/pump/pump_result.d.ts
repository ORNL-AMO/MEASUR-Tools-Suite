import { Drive, LineFrequency, LoadEstimationMethod, MotorEfficiencyClass } from "../motor/motorEnum";
import { PumpStyle } from "../pumpFan/pumpFan";

/** Equipment, hydraulic duty, and operating data shared by pump-result calculations. */
export interface PumpResultSystemInput {
    /** Pump hydraulic-power model selector. */
    pumpStyle: PumpStyle;
    /** Motor-to-pump drive type. */
    drive: Drive;
    /** Specified drive efficiency, dimensionless fraction; used only for a specified drive. */
    specifiedDriveEfficiency: number;
    /** Pumped-fluid specific gravity, dimensionless. */
    specificGravity: number;
    /** Pump flow rate, units gpm. */
    flowRate: number;
    /** Pump head, units ft; ignored for a positive-displacement pump. */
    head: number;
    /** Positive-displacement pressure rise, units psi; ignored for other pump styles. */
    differentialPressure: number;
    /** Motor nameplate power, units hp. */
    motorRatedPower: number;
    /** Motor nameplate speed, units RPM. */
    motorRatedSpeed: number;
    /** Electrical line-frequency selector. */
    lineFrequency: LineFrequency;
    /** Motor efficiency-class selector. */
    motorEfficiencyClass: MotorEfficiencyClass;
    /** Specified motor efficiency, dimensionless fraction; used only for the specified class. */
    specifiedMotorEfficiency: number;
    /** Motor nameplate voltage, units V. */
    motorRatedVoltage: number;
    /** Measured or expected operating voltage, units V. */
    operatingVoltage: number;
    /** Annual operating time, units hr/year. */
    operatingHours: number;
    /** Electricity rate, units $/kWh. */
    unitCost: number;
}

/** Shared system data and measurements used to calculate an existing pump result. */
export interface ExistingPumpResultInput {
    /** Equipment, hydraulic duty, and operating data shared by both calculation paths. */
    system: PumpResultSystemInput;
    /** Motor nameplate full-load current, units A. */
    motorFullLoadAmps: number;
    /** Selects measured motor power or measured motor current as the load-estimation basis. */
    loadEstimationMethod: LoadEstimationMethod;
    /** Measured three-phase motor input power, units kW. */
    measuredMotorPower: number;
    /** Measured motor current, units A. */
    measuredMotorCurrent: number;
}

/** Shared system data and proposed efficiency used to calculate a modified pump result. */
export interface ModifiedPumpResultInput {
    /** Equipment, hydraulic duty, and operating data shared by both calculation paths. */
    system: PumpResultSystemInput;
    /** Proposed pump efficiency, dimensionless fraction. */
    pumpEfficiency: number;
}

/** Motor, drive, pump, energy, and cost results for one operating condition. */
export interface PumpResultOutput {
    /** Pump hydraulic efficiency, dimensionless fraction. */
    pumpEfficiency: number;
    /** Motor nameplate power, units hp. */
    motorRatedPower: number;
    /** Motor shaft output power, units hp. */
    motorShaftPower: number;
    /** Pump shaft input power, units hp. */
    moverShaftPower: number;
    /** Motor efficiency, dimensionless fraction. */
    motorEfficiency: number;
    /** Motor power factor, dimensionless. */
    motorPowerFactor: number;
    /** Motor current, units A. */
    motorCurrent: number;
    /** Motor electrical input power, units kW. */
    motorPower: number;
    /** Annual electrical energy use, units MWh/year. */
    annualEnergy: number;
    /** Annual electricity cost, units thousand dollars/year. */
    annualCost: number;
    /** Motor load factor, dimensionless fraction. */
    loadFactor: number;
    /** Drive efficiency, dimensionless fraction. */
    driveEfficiency: number;
    /** Estimated motor full-load current, units A; zero for modified results. */
    estimatedFullLoadAmps: number;
}

/** Calculates existing pump-system results from measured motor data. */
export declare function calculateExistingPumpResult(input: ExistingPumpResultInput): PumpResultOutput;

/** Calculates modified pump-system results for a proposed pump efficiency. */
export declare function calculateModifiedPumpResult(input: ModifiedPumpResultInput): PumpResultOutput;

/** Runtime exports contributed by the pump-result binding. */
export type PumpResultModule = {
    calculateExistingPumpResult: typeof calculateExistingPumpResult;
    calculateModifiedPumpResult: typeof calculateModifiedPumpResult;
};
