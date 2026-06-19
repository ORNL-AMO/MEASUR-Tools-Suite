/**
 * Compressed Air Reduction calculations.
 *
 * Provides a function-based API for estimating annual compressed air consumption,
 * energy use, and cost savings for compressed air reduction measures. Supports four
 * measurement methods: flow meter, bag method, orifice/pressure method, and other.
 * Two utility types are supported: compressed air (cost per unit volume) and
 * electricity (cost per kilowatt-hour, derived via compressor specific power).
 */

import { CompressorElectricityData } from "../compressedAir/compressed_air_utils";
import { CompressedAirReductionInputV } from "../binding/registered_vectors";

// ---------------------------------------------------------------------------
// Enumerations
// ---------------------------------------------------------------------------

/**
 * Selects the measurement method used to determine compressed air consumption for a single measure.
 *
 * - `FlowMeter` - reads flow rate directly from an installed flow meter
 * - `Bag`       - estimates flow rate by timing how long it takes to fill a known-volume bag
 * - `Pressure`  - calculates flow rate from nozzle type and supply pressure
 * - `Other`     - uses a directly supplied annual consumption value
 */
export enum CompressedAirMeasurementMethod {
    FlowMeter = 0,
    Bag       = 1,
    Pressure  = 2,
    Other     = 3,
}

/**
 * Selects the utility type used to compute annual energy cost.
 *
 * - `CompressedAir` - cost based on air consumption, units $/scf
 * - `Electricity`   - cost based on compressor electricity draw, units $/kWh
 */
export enum CompressedAirUtilityType {
    CompressedAir = 0,
    Electricity   = 1,
}

// ---------------------------------------------------------------------------
// Measurement method data value objects
// ---------------------------------------------------------------------------

/**
 * Input data for the flow meter measurement method.
 *
 * Used when compressed air flow is measured directly by an installed flow meter.
 * The meter reading is the instantaneous flow rate; annual consumption is derived by
 * multiplying by annual operating time and the units multiplier.
 *
 * @property meterReading number, instantaneous flow rate from the installed meter, units scfm
 */
export interface FlowMeterMethodData {
    /** Instantaneous flow rate from the installed meter, units scfm (scf/min) */
    meterReading: number;
}

/**
 * Input data for the bag measurement method.
 *
 * The bag method estimates compressed air flow rate by measuring how long it takes to
 * fill a known-volume bag. The bag volume divided by the fill time (converted to minutes)
 * gives the flow rate in scfm.
 *
 * @property bagFillTime number, time to fill the bag with compressed air, units seconds
 * @property bagVolume number, internal volume of the bag, units scf
 */
export interface BagMethodData {
    /** Time to fill the bag with compressed air, units seconds */
    bagFillTime: number;
    /** Internal volume of the bag, units scf */
    bagVolume: number;
}

/**
 * Input data for the orifice/pressure measurement method.
 *
 * Used when compressed air flow rate is estimated from the nozzle type and supply pressure
 * using a quadratic equation with pre-calibrated nozzle coefficients. Thirteen nozzle types
 * are supported (indices 0-12). The units multiplier from the outer input is not applied in
 * this method.
 *
 * @property nozzleType number, nozzle type index (0-12) used to select lookup table coefficients
 * @property numberOfNozzles number, number of nozzles in the system
 * @property supplyPressure number, compressed air supply pressure, units psi
 */
export interface PressureMethodData {
    /** Nozzle type index used to select lookup table coefficients, unitless enum value 0-12. */
    nozzleType: number;
    /** Number of nozzles in the system */
    numberOfNozzles: number;
    /** Compressed air supply pressure, units psi */
    supplyPressure: number;
}

/**
 * Input data for the other (direct consumption) measurement method.
 *
 * Used when the annual compressed air consumption is already known from utility records,
 * an audit report, or another source, and no flow-rate measurement is available.
 *
 * @property consumption number, annual compressed air consumption, units scf/year
 */
export interface OtherMethodData {
    /** Annual compressed air consumption, units scf/year */
    consumption: number;
}

// ---------------------------------------------------------------------------
// Main input / output value objects
// ---------------------------------------------------------------------------

/**
 * Input data for a single compressed air reduction measure.
 *
 * Aggregates all parameters needed to evaluate one measure. The active measurement
 * method is selected via {@link CompressedAirMeasurementMethod}; only the corresponding
 * method data struct is used in the calculation. The `units` field is a quantity multiplier
 * (e.g., number of identical leak points or equipment pieces). Note: `units` is not applied
 * by the pressure method.
 *
 * @property hoursPerYear number, annual operating hours, units hr/year, units hours/year
 * @property utilityType {@link CompressedAirUtilityType}, utility type for cost calculation
 * @property utilityCost number, utility cost rate, units $/unit
 * @property measurementMethod {@link CompressedAirMeasurementMethod}, measurement method to apply
 * @property flowMeterMethodData {@link FlowMeterMethodData}, data for the flow meter method
 * @property bagMethodData {@link BagMethodData}, data for the bag method
 * @property pressureMethodData {@link PressureMethodData}, data for the orifice/pressure method
 * @property otherMethodData {@link OtherMethodData}, data for the other method
 * @property compressorElectricityData {@link CompressorElectricityData}, data for the electricity utility calculation
 * @property units number, quantity multiplier (not applied to pressure method)
 */
export interface CompressedAirReductionInput {
    /** annual operating hours, units hr/year, units hours/year */
    hoursPerYear: number;
    /** Utility type for cost calculation */
    utilityType: CompressedAirUtilityType;
    /** Utility cost rate, units $/unit */
    utilityCost: number;
    /** Measurement method to apply */
    measurementMethod: CompressedAirMeasurementMethod;
    /** Data for the flow meter method */
    flowMeterMethodData: FlowMeterMethodData;
    /** Data for the bag method */
    bagMethodData: BagMethodData;
    /** Data for the orifice/pressure method */
    pressureMethodData: PressureMethodData;
    /** Data for the other method */
    otherMethodData: OtherMethodData;
    /** Data for the electricity utility calculation */
    compressorElectricityData: CompressorElectricityData;
    /** Quantity multiplier, count of identical measures; not applied to pressure method. */
    units: number;
}

/**
 * Result object returned by {@link compressedAirReduction} and method-specific helper functions.
 *
 * Contains the accumulated annual energy use, annual energy cost, total flow rate,
 * per-nozzle flow rate (pressure method only), and total consumption across all measures.
 *
 * @property energyUse number, annual electrical energy use, units kWh/year
 * @property energyCost number, annual energy cost, units $/year
 * @property flowRate number, total compressed air flow rate, units scf/min
 * @property singleNozzleFlowRate number, flow rate per individual nozzle (pressure method only), units scf/min
 * @property consumption number, annual compressed air consumption, units scf/year
 */
export interface CompressedAirReductionOutput {
    /** Annual electrical energy use, units kWh/year */
    energyUse: number;
    /** Annual energy cost, units $/year */
    energyCost: number;
    /** Total compressed air flow rate, units scf/min */
    flowRate: number;
    /** Flow rate per individual nozzle (pressure method only), units scf/min */
    singleNozzleFlowRate: number;
    /** Annual compressed air consumption, units scf/year */
    consumption: number;
}

// ---------------------------------------------------------------------------
// Calculator functions
// ---------------------------------------------------------------------------

/**
 * Calculate total annual compressed air consumption, energy use, and cost for a collection of measures.
 *
 * Iterates over `input_vec`, dispatches each measure to the appropriate single-method helper
 * (flow meter, bag, pressure, or other), applies the utility-type cost calculation, and
 * accumulates the results.
 *
 * @param input_vec Vector of {@link CompressedAirReductionInput} structs, one per measure.
 * @returns {@link CompressedAirReductionOutput} with summed annual energy use (kWh/year),
 *   annual energy cost ($/year), total flow rate (scf/min), single-nozzle flow rate (scf/min),
 *   and total consumption (scf/year).
 */
export function compressedAirReduction(input_vec: CompressedAirReductionInputV): CompressedAirReductionOutput;

/**
 * Calculate annual compressed air consumption and flow rate using the flow meter method.
 *
 * Computes annual consumption as the product of the meter reading, annual operating hours, units hr/year,
 * units multiplier, and a factor of 60 to convert from per-minute to per-hour.
 * Energy use and energy cost are zero; call {@link compressedAirReduction} for a full result.
 *
 * @param data {@link FlowMeterMethodData} with the flow meter reading, units scf/min.
 * @param hours_per_year annual operating hours, units hr/year, units hours/year.
 * @param units Quantity multiplier, count of identical measures.
 * @returns {@link CompressedAirReductionOutput} with flow rate and consumption populated;
 *   energy use and energy cost are zero.
 */
export function flowMeterReduction(
    data: FlowMeterMethodData,
    hours_per_year: number,
    units: number
): CompressedAirReductionOutput;

/**
 * Calculate annual compressed air consumption and flow rate using the bag method.
 *
 * Flow rate is derived from the bag volume and fill time. Annual consumption is computed
 * from the flow rate, annual operating hours, units hr/year, and both quantity multipliers (bags and units).
 * Energy use and energy cost are zero; call {@link compressedAirReduction} for a full result.
 *
 * @param data {@link BagMethodData} with bag geometry, fill time, and number of bags.
 * @param hours_per_year annual operating hours, units hr/year, units hours/year.
 * @param units Outer quantity multiplier, count of identical leak points or equipment pieces.
 * @returns {@link CompressedAirReductionOutput} with flow rate and consumption populated;
 *   energy use and energy cost are zero.
 */
export function bagMethodReduction(
    data: BagMethodData,
    hours_per_year: number,
    units: number
): CompressedAirReductionOutput;

/**
 * Calculate annual compressed air consumption and flow rate using the orifice/pressure method.
 *
 * Single-nozzle flow rate is computed from a quadratic function of supply pressure using
 * pre-calibrated coefficients for the selected nozzle type. Total flow rate scales with the
 * number of nozzles. The outer units multiplier is not applied in this method.
 * Energy use and energy cost are zero; call {@link compressedAirReduction} for a full result.
 *
 * @param data {@link PressureMethodData} with nozzle type, number of nozzles, and
 *   supply pressure, units psi.
 * @param hours_per_year annual operating hours, units hr/year, units hours/year.
 * @returns {@link CompressedAirReductionOutput} with flow rates and consumption populated;
 *   energy use and energy cost are zero.
 */
export function pressureMethodReduction(
    data: PressureMethodData,
    hours_per_year: number
): CompressedAirReductionOutput;

/**
 * Returns a partial result with consumption set from a directly supplied value.
 *
 * No flow-rate or energy calculation is performed. The supplied consumption value is used
 * directly as the annual compressed air consumption.
 * Energy use, energy cost, and flow rate are zero; call {@link compressedAirReduction} for a full result.
 *
 * @param data {@link OtherMethodData} with the annual consumption, units scf/year.
 * @returns {@link CompressedAirReductionOutput} with consumption populated; all other fields are zero.
 */
export function otherMethodReduction(data: OtherMethodData): CompressedAirReductionOutput;

export type CompressedAirReductionModule = {
    CompressedAirMeasurementMethod: typeof CompressedAirMeasurementMethod;
    CompressedAirUtilityType: typeof CompressedAirUtilityType;
    compressedAirReduction: typeof compressedAirReduction;
    flowMeterReduction: typeof flowMeterReduction;
    bagMethodReduction: typeof bagMethodReduction;
    pressureMethodReduction: typeof pressureMethodReduction;
    otherMethodReduction: typeof otherMethodReduction;
};
