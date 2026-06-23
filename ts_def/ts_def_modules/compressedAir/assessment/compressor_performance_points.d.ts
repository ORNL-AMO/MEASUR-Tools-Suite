import { CompressorControl, CompressorLubricant, CompressorStage, CompressorType } from "./compressor";

/** One compressor performance point used by assessment profile calculations. */
export interface CompressorPerformancePoint {
    /** Discharge pressure, units psig. */
    dischargePressurePsig: number;
    /** True when discharge pressure should be calculated from defaults, dimensionless boolean. */
    isDefaultPressure: boolean;
    /** Airflow, units acfm. */
    airflowAcfm: number;
    /** True when airflow should be calculated from defaults, dimensionless boolean. */
    isDefaultAirflow: boolean;
    /** Package power, units kW. */
    powerKw: number;
    /** True when package power should be calculated from defaults, dimensionless boolean. */
    isDefaultPower: boolean;
}

/** Standard compressor performance-point bundle used by the assessment workflow. */
export interface CompressorPerformancePoints {
    /** Full-load point. */
    fullLoad: CompressorPerformancePoint;
    /** Maximum full-flow point. */
    maxFullFlow: CompressorPerformancePoint;
    /** VFD mid-turndown point. */
    midTurndown: CompressorPerformancePoint;
    /** VFD turndown point. */
    turndown: CompressorPerformancePoint;
    /** Unload point. */
    unloadPoint: CompressorPerformancePoint;
    /** No-load point. */
    noLoad: CompressorPerformancePoint;
    /** Blow-off point. */
    blowoff: CompressorPerformancePoint;
}

/** Nameplate and rated compressor data used to generate performance points. */
export interface CompressorNameplateData {
    /** Compressor type, dimensionless enum. */
    compressorType: CompressorType;
    /** Compressor stage arrangement, dimensionless enum. */
    stage: CompressorStage;
    /** Compressor lubricant configuration, dimensionless enum. */
    lubricant: CompressorLubricant;
    /** Rated motor size, units hp. */
    motorPowerHp: number;
    /** Rated full-load pressure, units psig. */
    fullLoadOperatingPressurePsig: number;
    /** Rated full-load capacity, units acfm. */
    fullLoadRatedCapacityAcfm: number;
    /** Rated load power, units kW. */
    ratedLoadPowerKw: number;
    /** Polytropic compressor exponent, dimensionless. */
    polytropicCompressorExponent: number;
    /** Full-load electrical current, units A. */
    fullLoadAmps: number;
    /** Full-load package input power, units kW. */
    totalPackageInputPowerKw: number;
}

/** Compressor control settings used to generate performance points. */
export interface CompressorControlsData {
    /** Compressor control strategy, dimensionless enum. */
    control: CompressorControl;
    /** Unload or turndown capacity, units percent. */
    unloadPointCapacityPct: number;
    /** Number of unload steps, dimensionless count. */
    numberOfUnloadSteps: number;
    /** True when automatic shutdown is enabled, dimensionless boolean. */
    automaticShutdown: boolean;
    /** Unload sump pressure, units psig. */
    unloadSumpPressurePsig: number;
}

/** Compressor design inputs used to generate performance points. */
export interface CompressorDesignDetails {
    /** Blowdown time, units seconds. */
    blowdownTimeSec: number;
    /** Modulating pressure range, units psig. */
    modulatingPressurePsig: number;
    /** Compressor inlet pressure, units psia. */
    inputPressurePsia: number;
    /** Design efficiency, units percent. */
    designEfficiencyPct: number;
    /** Service factor, dimensionless. */
    serviceFactor: number;
    /** Full-modulation no-load power, units percent. */
    noLoadPowerFMPercent: number;
    /** Unload no-load power, units percent. */
    noLoadPowerULPercent: number;
    /** Maximum full-flow pressure, units psig. */
    maxFullFlowPressurePsig: number;
}

/** Centrifugal compressor curve endpoints used for performance-point interpolation. */
export interface CentrifugalSpecifics {
    /** Surge airflow, units acfm. */
    surgeAirflowAcfm: number;
    /** Maximum full-load pressure, units psig. */
    maxFullLoadPressurePsig: number;
    /** Capacity at maximum full-load pressure, units acfm. */
    maxFullLoadCapacityAcfm: number;
    /** Minimum full-load pressure, units psig. */
    minFullLoadPressurePsig: number;
    /** Capacity at minimum full-load pressure, units acfm. */
    minFullLoadCapacityAcfm: number;
}

/** Input bundle for default performance-point generation. */
export interface CompressorPerformancePointInput {
    /** Nameplate and rated data. */
    nameplate: CompressorNameplateData;
    /** Control settings. */
    controls: CompressorControlsData;
    /** Design details. */
    design: CompressorDesignDetails;
    /** Centrifugal curve data. */
    centrifugal: CentrifugalSpecifics;
    /** Existing points and default flags. */
    points: CompressorPerformancePoints;
    /** Atmospheric pressure, units psia. */
    atmosphericPressurePsia: number;
}

/** Input bundle for automatic sequencer set-point adjustment. */
export interface SequencerSetPointInput {
    /** Compressor performance-point input. */
    compressor: CompressorPerformancePointInput;
    /** Sequencer target pressure, units psig. */
    targetPressurePsig: number;
    /** Sequencer pressure variance, units psig. */
    variancePsig: number;
}

/** Input bundle for system pressure reduction performance-point adjustment. */
export interface PressureReductionPointInput {
    /** Compressor performance-point input. */
    compressor: CompressorPerformancePointInput;
    /** Average system pressure reduction, units psig. */
    pressureReductionPsig: number;
}

/** Input bundle for cascading set-point performance-point adjustment. */
export interface CascadingSetPointInput {
    /** Compressor performance-point input. */
    compressor: CompressorPerformancePointInput;
    /** Adjusted full-load pressure, units psig. */
    fullLoadPressurePsig: number;
    /** Adjusted maximum full-flow pressure, units psig. */
    maxFullFlowPressurePsig: number;
}

/** @param input Input bundle with compressor nameplate, controls, design data, and default flags. */
export function generatePerformancePoints(input: CompressorPerformancePointInput): CompressorPerformancePoints;

/** @param input Automatic sequencer set-point input bundle. */
export function adjustPerformancePointsForSequencer(input: SequencerSetPointInput): CompressorPerformancePoints;

/** @param input System pressure reduction performance-point input bundle. */
export function reduceSystemPressurePerformancePoints(input: PressureReductionPointInput): CompressorPerformancePoints;

/** @param input Cascading set-point performance-point input bundle. */
export function adjustCascadingSetPointPerformancePoints(input: CascadingSetPointInput): CompressorPerformancePoints;

/**
 * @param capacityAcfm Rated capacity, units acfm.
 * @param pointPressurePsig Point discharge pressure, units psig.
 * @param ratedPressurePsig Rated discharge pressure, units psig.
 * @param atmosphericPressurePsia Atmospheric pressure, units psia.
 * @returns Pressure-adjusted airflow, units acfm.
 */
export function calculatePressureAdjustedAirflow(
    capacityAcfm: number,
    pointPressurePsig: number,
    ratedPressurePsig: number,
    atmosphericPressurePsia: number
): number;

/**
 * @param compressorType Compressor type, dimensionless enum.
 * @param inletPressurePsia Compressor inlet pressure, units psia.
 * @param pointPressurePsig Point discharge pressure, units psig.
 * @param ratedFullLoadPressurePsig Rated full-load pressure, units psig.
 * @param packagePowerKw Package power, units kW.
 * @param atmosphericPressurePsia Atmospheric pressure, units psia.
 * @returns Pressure-adjusted package power, units kW.
 */
export function calculatePressureAdjustedPower(
    compressorType: CompressorType,
    inletPressurePsia: number,
    pointPressurePsig: number,
    ratedFullLoadPressurePsig: number,
    packagePowerKw: number,
    atmosphericPressurePsia: number
): number;

/**
 * @param noLoadPowerULPercent No-load unload power, units percent.
 * @param packagePowerKw Full-load package power, units kW.
 * @param designEfficiencyPercent Design efficiency, units percent.
 * @returns No-load package power, units kW.
 */
export function calculateNoLoadPower(
    noLoadPowerULPercent: number,
    packagePowerKw: number,
    designEfficiencyPercent: number
): number;

/**
 * @param noLoadPowerFMPercent Full-modulation no-load power, units percent.
 * @param fullLoadPowerKw Full-load package power, units kW.
 * @returns No-load package power without unloading, units kW.
 */
export function calculateNoLoadPowerWithoutUnloading(
    noLoadPowerFMPercent: number,
    fullLoadPowerKw: number
): number;

/**
 * @param noLoadPowerFMPercent Full-modulation no-load power, units percent.
 * @param unloadPointCapacityPercent Unload point capacity, units percent.
 * @param exponent Modulation curve exponent, dimensionless.
 * @param maxFullFlowPowerKw Maximum full-flow power, units kW.
 * @returns Unload point package power, units kW.
 */
export function calculateUnloadPointPower(
    noLoadPowerFMPercent: number,
    unloadPointCapacityPercent: number,
    exponent: number,
    maxFullFlowPowerKw: number
): number;

/**
 * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
 * @param unloadPointCapacityPercent Unload point capacity, units percent.
 * @returns Unload point airflow, units acfm.
 */
export function calculateUnloadPointAirflow(
    fullLoadAirflowAcfm: number,
    unloadPointCapacityPercent: number
): number;

/**
 * @param maxFullFlowPressurePsig Maximum full-flow pressure, units psig.
 * @param modulatingPressureRangePsig Modulating pressure range, units psig.
 * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
 * @param unloadPointAirflowAcfm Unload point airflow, units acfm.
 * @returns Unload point discharge pressure, units psig.
 */
export function calculateUnloadPointDischargePressure(
    maxFullFlowPressurePsig: number,
    modulatingPressureRangePsig: number,
    fullLoadAirflowAcfm: number,
    unloadPointAirflowAcfm: number
): number;

/**
 * @param centrifugal Centrifugal compressor curve endpoints.
 * @param dischargePressurePsig Discharge pressure, units psig.
 * @returns Interpolated centrifugal unload airflow, units acfm.
 */
export function calculateCentrifugalUnloadPointAirflow(
    centrifugal: CentrifugalSpecifics,
    dischargePressurePsig: number
): number;

/**
 * @param totalPackageInputPowerKw Full-load package input power, units kW.
 * @param fullLoadRatedCapacityAcfm Rated full-load capacity, units acfm.
 * @returns Rated specific power, units kW/100 acfm.
 */
export function calculateRatedSpecificPower(
    totalPackageInputPowerKw: number,
    fullLoadRatedCapacityAcfm: number
): number;

/**
 * @param ratedSpecificPower Rated specific power, units kW/100 acfm.
 * @param fullLoadOperatingPressurePsig Rated full-load pressure, units psig.
 * @returns Rated isentropic efficiency, units percent.
 */
export function calculateRatedIsentropicEfficiency(
    ratedSpecificPower: number,
    fullLoadOperatingPressurePsig: number
): number;

export type CompressorPerformancePointsModule = {
    generatePerformancePoints: typeof generatePerformancePoints;
    adjustPerformancePointsForSequencer: typeof adjustPerformancePointsForSequencer;
    reduceSystemPressurePerformancePoints: typeof reduceSystemPressurePerformancePoints;
    adjustCascadingSetPointPerformancePoints: typeof adjustCascadingSetPointPerformancePoints;
    calculatePressureAdjustedAirflow: typeof calculatePressureAdjustedAirflow;
    calculatePressureAdjustedPower: typeof calculatePressureAdjustedPower;
    calculateNoLoadPower: typeof calculateNoLoadPower;
    calculateNoLoadPowerWithoutUnloading: typeof calculateNoLoadPowerWithoutUnloading;
    calculateUnloadPointPower: typeof calculateUnloadPointPower;
    calculateUnloadPointAirflow: typeof calculateUnloadPointAirflow;
    calculateUnloadPointDischargePressure: typeof calculateUnloadPointDischargePressure;
    calculateCentrifugalUnloadPointAirflow: typeof calculateCentrifugalUnloadPointAirflow;
    calculateRatedSpecificPower: typeof calculateRatedSpecificPower;
    calculateRatedIsentropicEfficiency: typeof calculateRatedIsentropicEfficiency;
};
