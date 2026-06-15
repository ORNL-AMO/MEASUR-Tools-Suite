/**
 * Natural Gas Reduction calculations.
 *
 * Provides a function-based API for estimating annual natural gas energy use and cost savings
 * for natural gas reduction measures. Supports four measurement methods: flow meter,
 * air mass flow, water mass flow, and other.
 */

// ---------------------------------------------------------------------------
// Enumerations
// ---------------------------------------------------------------------------

import { NaturalGasReductionInputV } from "../binding/registered_vectors";

/**
 * Selects the measurement method used to determine natural gas energy use for a single measure.
 *
 * - `FlowMeter`     - uses a direct gas flow rate measurement
 * - `AirMassFlow`   - uses heat transferred to an air stream
 * - `WaterMassFlow` - uses heat transferred to a water stream
 * - `Other`         - uses a directly supplied annual consumption value
 */
export enum NaturalGasMeasurementMethod {
    FlowMeter     = 0,
    AirMassFlow   = 1,
    WaterMassFlow = 2,
    Other         = 3,
}

// ---------------------------------------------------------------------------
// Measurement method data value objects
// ---------------------------------------------------------------------------

/**
 * Input data for the flow meter measurement method.
 *
 * Used when natural gas flow is measured directly by a flow meter. The flow rate is
 * combined with operating hours and units to calculate annual energy use.
 *
 * @property flowRate number, gas flow rate measured by the flow meter, units ft^3/hr
 */
export interface NaturalGasFlowMeterMethodData {
    /** Gas flow rate measured by the flow meter, units ft^3/hr */
    flowRate: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input data for the other (direct consumption) measurement method.
 *
 * Used when annual natural gas consumption is known directly from a report, bill, or
 * other source without requiring a flow-rate conversion.
 *
 * @property consumption number, annual natural gas consumption, units MMBtu/year
 */
export interface NaturalGasOtherMethodData {
    /** Annual natural gas consumption, units MMBtu/year */
    consumption: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Measured air duct data used to derive the air flow rate.
 *
 * Used when air mass flow is determined by direct measurements of duct area and
 * air velocity rather than nameplate specifications.
 *
 * @property areaOfDuct number, cross-sectional area of the duct, units ft^2
 * @property airVelocity number, air velocity measured in the duct, units ft/min
 */
export interface AirMassFlowMeasuredData {
    /** Cross-sectional area of the duct, units ft^2 */
    areaOfDuct: number;
    /** Air velocity measured in the duct, units ft/min */
    airVelocity: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Nameplate air flow data used as the air flow rate.
 *
 * Used when the air flow rate is taken directly from the equipment nameplate
 * rather than being derived from duct measurements.
 *
 * @property airFlow number, nameplate air flow rate, units ft^3/min
 */
export interface AirMassFlowNameplateData {
    /** Nameplate air flow rate, units ft^3/min */
    airFlow: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input data for the air mass flow measurement method.
 *
 * Aggregates parameters for calculating heat transfer via air mass flow. The flow rate
 * is taken either from nameplate data or from direct duct measurements, selected by `isNameplate`.
 *
 * @property isNameplate boolean, true if using nameplate data; false for measured data
 * @property measuredData {@link AirMassFlowMeasuredData}, measured air duct data (used when isNameplate is false)
 * @property nameplateData {@link AirMassFlowNameplateData}, nameplate air flow data (used when isNameplate is true)
 * @property inletTemperature number, inlet air temperature, units degF
 * @property outletTemperature number, outlet air temperature, units degF
 * @property systemEfficiency number, system efficiency (dimensionless, 0-1)
 */
export interface AirMassFlowData {
    /** True if using nameplate data; false for measured data */
    isNameplate: boolean;
    /** Measured air duct data (used when isNameplate is false) */
    measuredData: AirMassFlowMeasuredData;
    /** Nameplate air flow data (used when isNameplate is true) */
    nameplateData: AirMassFlowNameplateData;
    /** Inlet air temperature, units degF */
    inletTemperature: number;
    /** Outlet air temperature, units degF */
    outletTemperature: number;
    /** System efficiency (dimensionless, 0-1) */
    systemEfficiency: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input data for the water mass flow measurement method.
 *
 * Used when natural gas energy use is estimated from the heat transferred to a water
 * stream, calculated from the water flow rate and temperature differential.
 *
 * @property waterFlow number, water flow rate, units gal/min
 * @property inletTemperature number, inlet water temperature, units degF
 * @property outletTemperature number, outlet water temperature, units degF
 * @property systemEfficiency number, system efficiency (dimensionless, 0-1)
 */
export interface WaterMassFlowData {
    /** Water flow rate, units gal/min */
    waterFlow: number;
    /** Inlet water temperature, units degF */
    inletTemperature: number;
    /** Outlet water temperature, units degF */
    outletTemperature: number;
    /** System efficiency (dimensionless, 0-1) */
    systemEfficiency: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Main input / output value objects
// ---------------------------------------------------------------------------

/**
 * Input data for a single natural gas reduction measure.
 *
 * Aggregates all parameters needed to evaluate one measure. The active measurement method
 * is selected via {@link NaturalGasMeasurementMethod}; only the corresponding method data struct
 * is used in the calculation.
 *
 * @property operatingHours number, annual operating hours, units hours/year
 * @property fuelCost number, natural gas fuel cost rate, units $/MMBtu
 * @property measurementMethod {@link NaturalGasMeasurementMethod}, measurement method to apply
 * @property flowMeterMethodData {@link NaturalGasFlowMeterMethodData}, data for the flow meter method
 * @property otherMethodData {@link NaturalGasOtherMethodData}, data for the other method
 * @property airMassFlowData {@link AirMassFlowData}, data for the air mass flow method
 * @property waterMassFlowData {@link WaterMassFlowData}, data for the water mass flow method
 * @property units number, unit conversion multiplier applied to flow rates
 */
export interface NaturalGasReductionInput {
    /** Annual operating hours, units hours/year */
    operatingHours: number;
    /** Natural gas fuel cost rate, units $/MMBtu */
    fuelCost: number;
    /** Measurement method to apply */
    measurementMethod: NaturalGasMeasurementMethod;
    /** Data for the flow meter method */
    flowMeterMethodData: NaturalGasFlowMeterMethodData;
    /** Data for the other method */
    otherMethodData: NaturalGasOtherMethodData;
    /** Data for the air mass flow method */
    airMassFlowData: AirMassFlowData;
    /** Data for the water mass flow method */
    waterMassFlowData: WaterMassFlowData;
    /** Unit conversion multiplier applied to flow rates */
    units: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link naturalGasReduction} and method-specific helper functions.
 *
 * Contains the accumulated annual energy use, energy cost, heat flow, and total flow
 * across all measures passed to {@link naturalGasReduction}, or the individual result from a
 * single-method helper function.
 *
 * @property energyUse number, annual natural gas energy use, units MMBtu/year
 * @property energyCost number, annual natural gas energy cost, units $/year
 * @property heatFlow number, heat flow rate, units MMBtu/hr
 * @property totalFlow number, total gas or fluid flow, units ft^3/hr
 */
export interface NaturalGasReductionOutput {
    /** Annual natural gas energy use, units MMBtu/year */
    energyUse: number;
    /** Annual natural gas energy cost, units $/year */
    energyCost: number;
    /** Heat flow rate, units MMBtu/hr */
    heatFlow: number;
    /** Total gas or fluid flow, units ft^3/hr */
    totalFlow: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Calculator functions
// ---------------------------------------------------------------------------

/**
 * Calculate total annual natural gas energy use and cost for a collection of reduction measures.
 *
 * Iterates over `input_vec`, dispatches each measure to the appropriate single-method helper
 * (flow meter, air mass flow, water mass flow, or other), and accumulates the results.
 *
 * @param input_vec Vector of {@link NaturalGasReductionInput} structs, one per measure.
 * @returns {@link NaturalGasReductionOutput} with summed annual energy use (MMBtu/year),
 *   energy cost ($/year), heat flow (MMBtu/hr), and total flow across all measures.
 */
export function naturalGasReduction(input_vec: NaturalGasReductionInputV): NaturalGasReductionOutput;

/**
 * Calculate annual natural gas energy use and cost using the flow meter method.
 *
 * Multiplies the flow rate by the unit conversion factor and annual operating hours,
 * then applies natural gas energy content to obtain annual energy use.
 *
 * @param data {@link NaturalGasFlowMeterMethodData} with the measured gas flow rate.
 * @param operating_hours Annual operating hours, units hours/year.
 * @param fuel_cost Natural gas fuel cost rate, units $/MMBtu.
 * @param units Unit conversion multiplier applied to the flow rate.
 * @returns {@link NaturalGasReductionOutput} with annual energy use and annual energy cost.
 */
export function flowMeterMethodReduction(
    data: NaturalGasFlowMeterMethodData,
    operating_hours: number,
    fuel_cost: number,
    units: number
): NaturalGasReductionOutput;

/**
 * Calculate annual natural gas energy use and cost using the air mass flow method.
 *
 * Determines the air flow rate from either nameplate or measured duct data, then calculates
 * heat transferred to the air stream from the temperature differential.
 *
 * @param data {@link AirMassFlowData} with air flow and temperature parameters.
 * @param operating_hours Annual operating hours, units hours/year.
 * @param fuel_cost Natural gas fuel cost rate, units $/MMBtu.
 * @param units Unit conversion multiplier applied to the flow rate.
 * @returns {@link NaturalGasReductionOutput} with annual energy use, annual energy cost,
 *   heat flow, and total flow.
 */
export function airMassFlowMethodReduction(
    data: AirMassFlowData,
    operating_hours: number,
    fuel_cost: number,
    units: number
): NaturalGasReductionOutput;

/**
 * Calculate annual natural gas energy use and cost using the water mass flow method.
 *
 * Calculates heat transferred to a water stream from water flow rate and temperature differential.
 *
 * @param data {@link WaterMassFlowData} with water flow and temperature parameters.
 * @param operating_hours Annual operating hours, units hours/year.
 * @param fuel_cost Natural gas fuel cost rate, units $/MMBtu.
 * @param units Unit conversion multiplier applied to the flow rate.
 * @returns {@link NaturalGasReductionOutput} with annual energy use, annual energy cost,
 *   heat flow, and total flow.
 */
export function waterMassFlowMethodReduction(
    data: WaterMassFlowData,
    operating_hours: number,
    fuel_cost: number,
    units: number
): NaturalGasReductionOutput;

/**
 * Calculate annual natural gas energy use and cost using a directly supplied consumption value.
 *
 * Uses the `consumption` field directly as annual energy use without any flow-rate conversion.
 *
 * @param data {@link NaturalGasOtherMethodData} with the annual gas consumption, units MMBtu/year.
 * @param fuel_cost Natural gas fuel cost rate, units $/MMBtu.
 * @returns {@link NaturalGasReductionOutput} with annual energy use and annual energy cost.
 */
export function naturalGasOtherMethodReduction(
    data: NaturalGasOtherMethodData,
    fuel_cost: number
): NaturalGasReductionOutput;

export type NaturalGasReductionModule = {
    NaturalGasMeasurementMethod: typeof NaturalGasMeasurementMethod;
    NaturalGasFlowMeterMethodData: NaturalGasFlowMeterMethodData;
    NaturalGasOtherMethodData: NaturalGasOtherMethodData;
    AirMassFlowMeasuredData: AirMassFlowMeasuredData;
    AirMassFlowNameplateData: AirMassFlowNameplateData;
    AirMassFlowData: AirMassFlowData;
    WaterMassFlowData: WaterMassFlowData;
    NaturalGasReductionInput: NaturalGasReductionInput;
    NaturalGasReductionOutput: NaturalGasReductionOutput;
    naturalGasReduction: typeof naturalGasReduction;
    flowMeterMethodReduction: typeof flowMeterMethodReduction;
    airMassFlowMethodReduction: typeof airMassFlowMethodReduction;
    waterMassFlowMethodReduction: typeof waterMassFlowMethodReduction;
    naturalGasOtherMethodReduction: typeof naturalGasOtherMethodReduction;
};
