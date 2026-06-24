import type {
    CompressorProfileCompressorV,
    CompressorProfileRowV,
    CompressorProfileTotalV,
    CompressorRuntimeStateV,
    CompressorTrimSelectionV
} from "../../binding/registered_vectors";
import {
    CompressorControl,
    CompressorInputBasis,
    CompressorLubricant,
    CompressorStage,
    CompressorType
} from "./compressor";
import { CompressorPerformancePoints } from "./compressor_performance_points";

/** Multi-compressor system allocation strategy, dimensionless enum. */
export enum CompressorSystemControlMode {
    Cascading = 0,
    IsentropicEfficiency = 1,
    LoadSharing = 2,
    TargetPressureSequencer = 3,
    BaseTrim = 4
}

/** Compressor definition used by system-profile calculations. */
export interface CompressorProfileCompressor {
    /** Stable compressor identifier. */
    compressorId: string;
    /** Compressor type, dimensionless enum. */
    compressorType: CompressorType;
    /** Control strategy, dimensionless enum. */
    control: CompressorControl;
    /** Compressor stage arrangement, dimensionless enum. */
    stage: CompressorStage;
    /** Lubricant type, dimensionless enum. */
    lubricant: CompressorLubricant;
    /** True when automatic shutdown is enabled, dimensionless boolean. */
    automaticShutdown: boolean;
    /** Compressor performance points used by interval calculations. */
    performancePoints: CompressorPerformancePoints;
    /** Blowdown time, units seconds. */
    blowdownTimeSec: number;
    /** Unload sump pressure, units psig. */
    unloadSumpPressurePsig: number;
    /** Explicit unload capacity, units percent; pass zero to derive from performance points. */
    unloadPointCapacityPct: number;
    /** Modulation floor fraction, dimensionless. */
    noLoadPowerFractionForModulation: number;
    /** Modulating pressure range, units psig. */
    modulatingPressurePsig: number;
}

/** One compressor interval row in an assessment system profile. */
export interface CompressorProfileRow {
    /** Stable compressor identifier. */
    compressorId: string;
    /** Stable day-type identifier. */
    dayTypeId: string;
    /** Interval start time, units hours. */
    timeIntervalHr: number;
    /** Compressor operating order; zero means off, dimensionless count. */
    operatingOrder: number;
    /** Compressor package power, units kW. */
    powerKw: number;
    /** Compressor airflow, units acfm. */
    airflowAcfm: number;
    /** Fraction of full-load compressor power, dimensionless. */
    powerFraction: number;
    /** Fraction of full-load compressor airflow, dimensionless. */
    airflowFraction: number;
    /** Fraction of total system full-load power, dimensionless. */
    systemPowerFraction: number;
    /** Fraction of total system full-load airflow, dimensionless. */
    systemAirflowFraction: number;
    /** Electrical power factor, dimensionless. */
    powerFactor: number;
    /** Electrical current, units A. */
    amps: number;
    /** Electrical voltage, units V. */
    volts: number;
}

/** Total system demand row used by profile reallocation. */
export interface CompressorProfileTotal {
    /** Stable day-type identifier. */
    dayTypeId: string;
    /** Interval start time, units hours. */
    timeIntervalHr: number;
    /** Total system airflow, units acfm. */
    airflowAcfm: number;
    /** Total compressor power, units kW. */
    powerKw: number;
    /** Total power including auxiliary power, units kW. */
    totalPowerKw: number;
    /** Fraction of total system full-load airflow, dimensionless. */
    airflowFraction: number;
    /** Fraction of total system full-load power, dimensionless. */
    powerFraction: number;
    /** Auxiliary equipment power, units kW. */
    auxiliaryPowerKw: number;
}

/** Optional reduce-runtime on/off state for one compressor interval. */
export interface CompressorRuntimeState {
    /** Stable compressor identifier. */
    compressorId: string;
    /** Stable day-type identifier. */
    dayTypeId: string;
    /** Interval start time, units hours. */
    timeIntervalHr: number;
    /** True when the compressor is available to run, dimensionless boolean. */
    isCompressorOn: boolean;
    /** True when automatic shutdown should be applied, dimensionless boolean. */
    automaticShutdownTimer: boolean;
}

/** Optional base-trim compressor selection for one day type. */
export interface CompressorTrimSelection {
    /** Stable day-type identifier. */
    dayTypeId: string;
    /** Selected trim compressor identifier. */
    compressorId: string;
}

/** Shared options for profile calculations. */
export interface CompressorProfileOptions {
    /** Day type to calculate. */
    dayTypeId: string;
    /** Profile input basis, dimensionless enum. */
    inputBasis: CompressorInputBasis;
    /** System allocation mode, dimensionless enum. */
    controlMode: CompressorSystemControlMode;
    /** Atmospheric pressure, units psia. */
    atmosphericPressurePsia: number;
    /** Existing air storage, units ft3. */
    totalAirStorageFt3: number;
    /** Added receiver volume, units ft3. */
    additionalReceiverVolumeFt3: number;
    /** True when zero-flow capacity inputs may shut down compressors, dimensionless boolean. */
    canShutdown: boolean;
}

/** Savings input for one day type. */
export interface CompressorProfileSavingsInput {
    /** Stable day-type identifier. */
    dayTypeId: string;
    /** Electricity cost, units dollars/kWh. */
    electricityCostPerKwh: number;
    /** Profile interval duration, units hours. */
    intervalHours: number;
    /** Annual operating days, units days/year. */
    operatingDays: number;
    /** Added auxiliary energy, units kWh/year. */
    auxiliaryEnergyKwh: number;
    /** Implementation cost, units dollars. */
    implementationCost: number;
    /** Salvage value, units dollars. */
    salvageValue: number;
}

/** Energy, cost, savings, and payback result for one day type. */
export interface CompressorProfileSavingsResult {
    /** Baseline annual energy, units kWh/year. */
    baselineEnergyKwh: number;
    /** Baseline annual cost, units dollars/year. */
    baselineCost: number;
    /** Adjusted annual energy, units kWh/year. */
    adjustedEnergyKwh: number;
    /** Adjusted annual cost, units dollars/year. */
    adjustedCost: number;
    /** Annual energy savings, units kWh/year. */
    energySavingsKwh: number;
    /** Annual cost savings, units dollars/year. */
    costSavings: number;
    /** Cost savings fraction expressed as a percentage, units percent. */
    percentSavings: number;
    /** Implementation cost, units dollars. */
    implementationCost: number;
    /** Salvage value, units dollars. */
    salvageValue: number;
    /** Simple payback, units months. */
    paybackMonths: number;
}

/**
 * @param compressors Vector of compressor definitions.
 * @param profileRows Vector of user-entered compressor profile rows.
 * @param options Shared profile options.
 * @returns Vector of calculated compressor profile rows; call `delete()` on the returned vector.
 */
export function calculateBaselineProfile(
    compressors: CompressorProfileCompressorV,
    profileRows: CompressorProfileRowV,
    options: CompressorProfileOptions
): CompressorProfileRowV;

/**
 * @param compressors Vector of compressor definitions.
 * @param profileRows Vector of calculated compressor profile rows.
 * @returns Vector of system total rows; call `delete()` on the returned vector.
 */
export function calculateProfileTotals(
    compressors: CompressorProfileCompressorV,
    profileRows: CompressorProfileRowV
): CompressorProfileTotalV;

/**
 * @param compressors Vector of compressor definitions.
 * @param previousProfileRows Vector of prior compressor profile rows used for order context.
 * @param demandRows Vector of total system demand rows.
 * @param options Shared profile options.
 * @param runtimeStates Optional vector of on/off states for reduce-runtime cases.
 * @param trimSelections Optional vector of base-trim selections.
 * @returns Vector of reallocated compressor profile rows; call `delete()` on the returned vector.
 */
export function reallocateProfileFlow(
    compressors: CompressorProfileCompressorV,
    previousProfileRows: CompressorProfileRowV,
    demandRows: CompressorProfileTotalV,
    options: CompressorProfileOptions,
    runtimeStates: CompressorRuntimeStateV,
    trimSelections: CompressorTrimSelectionV
): CompressorProfileRowV;

/**
 * @param baselineRows Vector of baseline compressor profile rows.
 * @param adjustedRows Vector of adjusted compressor profile rows.
 * @param input Savings input for one day type.
 * @returns Energy, cost, savings, and payback result for the supplied day type.
 */
export function calculateProfileSavings(
    baselineRows: CompressorProfileRowV,
    adjustedRows: CompressorProfileRowV,
    input: CompressorProfileSavingsInput
): CompressorProfileSavingsResult;

/**
 * @param compressor Compressor definition.
 * @param inputBasis Profile input basis, dimensionless enum.
 * @param inputValue Input value in the units implied by `inputBasis`.
 * @param options Shared profile options.
 * @param powerFactor Electrical power factor, dimensionless.
 * @param amps Electrical current, units A.
 * @param volts Electrical voltage, units V.
 * @returns Calculated compressor profile row.
 */
export function calculateCompressorProfileRow(
    compressor: CompressorProfileCompressor,
    inputBasis: CompressorInputBasis,
    inputValue: number,
    options: CompressorProfileOptions,
    powerFactor: number,
    amps: number,
    volts: number
): CompressorProfileRow;

/**
 * @param useAirflowAcfm Baseline use airflow, units acfm.
 * @param adjustedFullLoadPressurePsig Adjusted full-load pressure, units psig.
 * @param altitudePressurePsia Site altitude pressure, units psia.
 * @param originalFullLoadPressurePsig Original full-load pressure, units psig.
 * @param atmosphericPressurePsia Atmospheric reference pressure, units psia.
 * @returns Pressure-reduced airflow, units acfm.
 */
export function calculatePressureReducedAirflow(
    useAirflowAcfm: number,
    adjustedFullLoadPressurePsig: number,
    altitudePressurePsia: number,
    originalFullLoadPressurePsig: number,
    atmosphericPressurePsia: number
): number;

export type CompressorSystemProfileModule = {
    CompressorSystemControlMode: typeof CompressorSystemControlMode;
    calculateBaselineProfile: typeof calculateBaselineProfile;
    calculateProfileTotals: typeof calculateProfileTotals;
    reallocateProfileFlow: typeof reallocateProfileFlow;
    calculateProfileSavings: typeof calculateProfileSavings;
    calculateCompressorProfileRow: typeof calculateCompressorProfileRow;
    calculatePressureReducedAirflow: typeof calculatePressureReducedAirflow;
};
