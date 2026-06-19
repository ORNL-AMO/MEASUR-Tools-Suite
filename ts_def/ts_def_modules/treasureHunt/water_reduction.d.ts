/**
 * Water Reduction calculations.
 *
 * Provides a function-based API for estimating annual water use and cost savings
 * for water reduction measures identified during an energy treasure hunt or water efficiency
 * assessment. Supports four measurement methods: metered flow, volume meter, bucket, and other.
 */

// ---------------------------------------------------------------------------
// Enumerations
// ---------------------------------------------------------------------------

import { WaterReductionInputV } from "../binding/registered_vectors";

/**
 * Selects the measurement method used to determine water use for a single measure.
 *
 * - `Metered` - uses an instantaneous flow meter reading
 * - `Volume`  - uses initial/final totalizing meter readings over a timed interval
 * - `Bucket`  - uses the time required to fill a container of known volume
 * - `Other`   - uses a directly supplied annual consumption value
 */
export enum WaterReductionMeasurementMethod {
    Metered = 0,
    Volume  = 1,
    Bucket  = 2,
    Other   = 3,
}

// ---------------------------------------------------------------------------
// Measurement method data value objects
// ---------------------------------------------------------------------------

/**
 * Input data for the metered flow measurement method.
 *
 * Used when water use is measured with a continuous flow meter. The meter reading
 * is combined with operating hours to calculate annual water use.
 *
 * @property meterReading number, instantaneous flow rate from the meter, units gal/min
 */
export interface MeteredFlowMethodData {
    /** Instantaneous flow rate from the meter, units gal/min */
    meterReading: number;
}

/**
 * Input data for the volume meter measurement method.
 *
 * Used when water use is measured by recording initial and final readings of a totalizing
 * water meter over a timed interval. The change in reading divided by elapsed time gives
 * the average flow rate.
 *
 * @property finalMeterReading number, final meter reading at end of interval, units gal
 * @property initialMeterReading number, initial meter reading at start of interval, units gal
 * @property elapsedTime number, duration of measurement interval, units min
 */
export interface VolumeMeterMethodData {
    /** Final meter reading at end of measurement interval, units gal */
    finalMeterReading: number;
    /** Initial meter reading at start of measurement interval, units gal */
    initialMeterReading: number;
    /** Duration of the measurement interval, units min */
    elapsedTime: number;
}

/**
 * Input data for the bucket measurement method.
 *
 * Used when water use is measured by timing how long it takes to fill a container of known
 * volume. The bucket volume divided by the fill time gives the flow rate.
 *
 * @property bucketVolume number, volume of the bucket used for measurement, units gal
 * @property bucketFillTime number, time required to fill the bucket, units s
 */
export interface BucketMethodData {
    /** Volume of the bucket used for the measurement, units gal */
    bucketVolume: number;
    /** Time required to fill the bucket, units s */
    bucketFillTime: number;
}

/**
 * Input data for the other (direct consumption) measurement method.
 *
 * Used when annual water consumption is known directly from a report, bill, or other source
 * without requiring a flow-rate conversion.
 *
 * @property consumption number, annual water consumption, units gal/year
 */
export interface WaterOtherMethodData {
    /** Annual water consumption, units gal/year */
    consumption: number;
}

// ---------------------------------------------------------------------------
// Main input / output value objects
// ---------------------------------------------------------------------------

/**
 * Input data for a single water reduction measure.
 *
 * Aggregates all parameters needed to evaluate one measure. The active measurement method
 * is selected via {@link WaterReductionMeasurementMethod}; only the corresponding method data
 * struct is used in the calculation.
 *
 * @property hoursPerYear number, annual operating hours, units hr/year, units hours/year
 * @property waterCost number, water cost rate, units $/gal
 * @property measurementMethod {@link WaterReductionMeasurementMethod}, measurement method to apply
 * @property meteredFlowMethodData {@link MeteredFlowMethodData}, data for metered flow method
 * @property volumeMeterMethodData {@link VolumeMeterMethodData}, data for volume meter method
 * @property bucketMethodData {@link BucketMethodData}, data for bucket method
 * @property otherMethodData {@link WaterOtherMethodData}, data for other method
 */
export interface WaterReductionInput {
    /** annual operating hours, units hr/year, units hours/year */
    hoursPerYear: number;
    /** Water cost rate, units $/gal */
    waterCost: number;
    /** Measurement method to apply */
    measurementMethod: WaterReductionMeasurementMethod;
    /** Data for the metered flow method */
    meteredFlowMethodData: MeteredFlowMethodData;
    /** Data for the volume meter method */
    volumeMeterMethodData: VolumeMeterMethodData;
    /** Data for the bucket method */
    bucketMethodData: BucketMethodData;
    /** Data for the other method */
    otherMethodData: WaterOtherMethodData;
}

/**
 * Result object returned by {@link waterReduction} and method-specific helper functions.
 *
 * Contains the accumulated annual water use and annual water cost across all measures passed
 * to {@link waterReduction}, or the individual result from a single-method helper function.
 *
 * @property waterUse number, annual water use, units gal/year
 * @property waterCost number, annual water cost, units $/year
 */
export interface WaterReductionOutput {
    /** Annual water use, units gal/year */
    waterUse: number;
    /** Annual water cost, units $/year */
    waterCost: number;
}

// ---------------------------------------------------------------------------
// Calculator functions
// ---------------------------------------------------------------------------

/**
 * Calculate total annual water use and cost for a collection of water reduction measures.
 *
 * Iterates over `input_vec`, dispatches each measure to the appropriate single-method helper
 * (metered flow, volume meter, bucket, or other), and accumulates the results.
 *
 * @param input_vec Vector of {@link WaterReductionInput} structs, one per measure.
 * @returns {@link WaterReductionOutput} with summed annual water use (gal/year)
 *   and annual water cost ($/year) across all measures.
 */
export function waterReduction(input_vec: WaterReductionInputV): WaterReductionOutput;

/**
 * Calculate annual water use and cost using the metered flow method.
 *
 * Multiplies meter reading by 60 (gal/min to gal/hr) and annual operating hours, units hr/year to obtain annual
 * water use, then calculates cost using water cost rate.
 *
 * @param data {@link MeteredFlowMethodData} with meter reading, units gal/min.
 * @param operating_hours annual operating hours, units hr/year, units hours/year.
 * @param water_cost Water cost rate, units $/gal.
 * @returns {@link WaterReductionOutput} with annual water use and annual water cost.
 */
export function meteredFlowReduction(
    data: MeteredFlowMethodData,
    operating_hours: number,
    water_cost: number
): WaterReductionOutput;

/**
 * Calculate annual water use and cost using the volume meter method.
 *
 * Computes average flow from change in meter reading over elapsed time, then scales to annual use.
 *
 * @param data {@link VolumeMeterMethodData} with initial/final meter readings (gal) and elapsed time (min).
 * @param operating_hours annual operating hours, units hr/year, units hours/year.
 * @param water_cost Water cost rate, units $/gal.
 * @returns {@link WaterReductionOutput} with annual water use and annual water cost.
 */
export function volumeMeterReduction(
    data: VolumeMeterMethodData,
    operating_hours: number,
    water_cost: number
): WaterReductionOutput;

/**
 * Calculate annual water use and cost using the bucket measurement method.
 *
 * Computes flow rate from bucket volume and fill time, then scales to annual use.
 *
 * @param data {@link BucketMethodData} with bucket volume (gal) and fill time (s).
 * @param operating_hours annual operating hours, units hr/year, units hours/year.
 * @param water_cost Water cost rate, units $/gal.
 * @returns {@link WaterReductionOutput} with annual water use and annual water cost.
 */
export function bucketReduction(
    data: BucketMethodData,
    operating_hours: number,
    water_cost: number
): WaterReductionOutput;

/**
 * Calculate annual water use and cost using a directly supplied consumption value.
 *
 * Uses the consumption field directly as annual water use without flow-rate conversion.
 *
 * @param data {@link WaterOtherMethodData} with annual water consumption, units gal/year.
 * @param water_cost Water cost rate, units $/gal.
 * @returns {@link WaterReductionOutput} with annual water use and annual water cost.
 */
export function otherReduction(
    data: WaterOtherMethodData,
    water_cost: number
): WaterReductionOutput;

export type WaterReductionModule = {
    WaterReductionMeasurementMethod: typeof WaterReductionMeasurementMethod;
    waterReduction: typeof waterReduction;
    meteredFlowReduction: typeof meteredFlowReduction;
    volumeMeterReduction: typeof volumeMeterReduction;
    bucketReduction: typeof bucketReduction;
    otherReduction: typeof otherReduction;
};
