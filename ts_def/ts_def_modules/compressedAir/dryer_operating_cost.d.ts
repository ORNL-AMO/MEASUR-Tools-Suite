/** Supported compressed-air dryer types. */
export enum DryerType {
    Heatless = 0,
    HeatedExternally = 1,
    BlowerPurgeWithSweep = 2,
    BlowerPurgeWithoutSweep = 3,
    HeatOfCompressionHC = 4,
    HeatOfCompressionSP = 5,
    Refrigerated = 6
}

/** Selects whether purge airflow is supplied as capacity percent or direct flow. */
export enum PurgeInputMode {
    PercentOfDryerCapacity = 0,
    DirectFlow = 1
}

/** Complete, frontend-validated inputs for the dryer operating-cost calculation. */
export interface DryerOperatingCostInput {
    /** Dryer configuration to evaluate. */
    dryerType: DryerType;
    /** Inlet airflow, in standard cubic feet per minute (SCFM). */
    flowRate: number;
    /** Inlet gauge pressure, in pounds per square inch gauge (psig). */
    pressure: number;
    /** Inlet temperature, in degrees Fahrenheit. */
    temperature: number;
    /** Annual dryer operating time, in hours per year. */
    annualOperatingHours: number;
    /** Electricity rate, in dollars per kilowatt-hour. */
    costOfElectricity: number;
    /** Compressed-air rate, in dollars per 1,000 standard cubic feet. */
    costOfCompressedAir: number;
    /** Cooling-water rate, in dollars per 1,000 gallons. */
    costOfCoolingWater: number;
    /** Manual heater load, in kilowatts; zero selects automatic sizing. */
    heaterPower: number;
    /** Heater operating time per 24 hours, in hours. */
    heatingHoursPerDay: number;
    /** Purge airflow as dryer-capacity percentage points. */
    purgeRate: number;
    /** Direct purge airflow, in SCFM. */
    purgeFlowRate: number;
    /** Design desiccant capacity, in percentage points. */
    designDDCPercentage: number;
    /** Regeneration half-cycle length, in hours. */
    regenerationCycleLength: number;
    /** Manual motor size, in horsepower; zero selects automatic sizing. */
    motorPower: number;
    /** Active purge input representation. */
    purgeInputMode: PurgeInputMode;
}

/** Resolved annual dryer operating-cost results. */
export interface DryerOperatingCostResult {
    /** Water removed, in pounds per hour. */
    waterRemoved: number;
    /** Total annual operating cost, in dollars per year. */
    totalCostPerYear: number;
    /** Heater load used by the calculation, in kilowatts. */
    heaterPower: number;
    /** Heater operating time per 24 hours, in hours. */
    heatingHoursPerDay: number;
    /** Effective purge airflow, in dryer-capacity percentage points. */
    purgeRate: number;
    /** Design desiccant capacity, in percentage points. */
    designDDCPercentage: number;
    /** Purge airflow used by the calculation, in SCFM. */
    purgeFlowRate: number;
    /** Motor power used by the calculation, in horsepower. */
    motorPower: number;
    /** Regeneration half-cycle length, in hours. */
    regenerationCycleLength: number;
}

/** Calculates annual operating cost for supported desiccant and refrigerated dryers. */
export declare function calculateDryerOperatingCost(
    input: DryerOperatingCostInput
): DryerOperatingCostResult;

/** Runtime exports contributed by the dryer operating-cost binding. */
export type DryerOperatingCostModule = {
    DryerType: typeof DryerType;
    PurgeInputMode: typeof PurgeInputMode;
    calculateDryerOperatingCost: typeof calculateDryerOperatingCost;
};
