/**
 * Shared compressor assessment enums and result objects.
 */

/** Compressor mechanical type, dimensionless enum. */
export enum CompressorType {
    Centrifugal = 0,
    Screw = 1,
    Reciprocating = 2
}

/** Compressor control strategy, dimensionless enum. */
export enum CompressorControl {
    LoadUnload = 0,
    ModulationUnload = 1,
    BlowOff = 2,
    ModulationWithoutUnload = 3,
    StartStop = 4,
    VariableDisplacementUnload = 5,
    MultiStepUnloading = 6,
    Vfd = 7
}

/** Compressor stage arrangement, dimensionless enum. */
export enum CompressorStage {
    Single = 0,
    Two = 1,
    Multiple = 2
}

/** Compressor lubricant configuration, dimensionless enum. */
export enum CompressorLubricant {
    Injected = 0,
    Free = 1,
    None = 2
}

/** Compressor input basis, dimensionless enum. */
export enum CompressorInputBasis {
    PowerFraction = 0,
    CapacityFraction = 1,
    MeasuredPower = 2,
    MeasuredCapacity = 3,
    Electrical = 4
}

/** Standard compressor model result. */
export interface CompressorPerformanceResult {
    /** Calculated compressor package power, units kW. */
    powerKw: number;
    /** Calculated compressor airflow, units acfm. */
    airflowAcfm: number;
    /** Calculated fraction of full-load power, dimensionless. */
    powerFraction: number;
    /** Calculated fraction of full-load airflow, dimensionless. */
    airflowFraction: number;
}

/** Compressor model result for blow-off controls. */
export interface CompressorBlowOffResult {
    /** Calculated compressor package power, units kW. */
    powerKw: number;
    /** Calculated useful compressor airflow, units acfm. */
    airflowAcfm: number;
    /** Calculated fraction of full-load power, dimensionless. */
    powerFraction: number;
    /** Calculated fraction of full-load useful airflow, dimensionless. */
    airflowFraction: number;
    /** Calculated blow-off airflow, units acfm. */
    blowOffAirflowAcfm: number;
    /** Calculated fraction of full-load airflow blown off, dimensionless. */
    blowOffFraction: number;
}

export type CompressorAssessmentSharedModule = {
    CompressorType: typeof CompressorType;
    CompressorControl: typeof CompressorControl;
    CompressorStage: typeof CompressorStage;
    CompressorLubricant: typeof CompressorLubricant;
    CompressorInputBasis: typeof CompressorInputBasis;
};
