/**
 * Steam Reduction calculations.
 *
 * Provides a function-based API for estimating annual steam use, energy use, and energy
 * cost for steam reduction measures identified during an energy treasure hunt.
 * Supports four measurement methods: flow meter, air mass flow, water mass flow, and offsheet.
 */

import { SteamReductionInputV } from "../binding/registered_vectors";

import type { ThermodynamicQuantity } from '../steamModeler/ssmtEnum';

export type { ThermodynamicQuantity };

// ---------------------------------------------------------------------------
// Enumerations
// ---------------------------------------------------------------------------

/**
 * Selects the measurement method used to determine steam use for a single measure.
 *
 * - `FlowMeter`     - uses a direct steam or water flow meter reading
 * - `AirMassFlow`   - derives steam use from air flow and temperature rise
 * - `WaterMassFlow` - derives steam use from water flow and temperature rise
 * - `Offsheet`      - uses a directly supplied energy consumption value
 */
export enum SteamMeasurementMethod {
    FlowMeter     = 0,
    AirMassFlow   = 1,
    WaterMassFlow = 2,
    Offsheet      = 3,
}

/**
 * Selects the utility type used to calculate energy cost.
 *
 * - `Steam`      - energy cost is based on steam use (kg/year)
 * - `NaturalGas` - energy cost is based on energy use (kJ/year)
 * - `Other`      - energy cost is based on energy use (kJ/year)
 */
export enum SteamUtilityType {
    Steam      = 0,
    NaturalGas = 1,
    Other      = 2,
}

// ---------------------------------------------------------------------------
// Measurement method data value objects
// ---------------------------------------------------------------------------

/**
 * Input data for the flow meter measurement method.
 *
 * Used when steam or water use is measured with a flow meter. The flow rate is combined
 * with operating hours, units, and system efficiency to calculate steam use.
 *
 * @property flowRate number, flow rate (water m^3/min, steam kg/hr)
 */
export interface SteamFlowMeterMethodData {
    /** Flow rate (water m^3/min, steam kg/hr) */
    flowRate: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input data for nameplate-based mass flow measurement.
 *
 * Used when the flow rate is taken directly from equipment nameplate data rather than
 * measured in the field.
 *
 * @property flowRate number, nameplate flow rate (water m^3/min, steam kg/hr)
 */
export interface SteamMassFlowNameplateData {
    /** Nameplate flow rate (water m^3/min, steam kg/hr) */
    flowRate: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input data for field-measured mass flow.
 *
 * Used when the flow rate is calculated from field measurements of duct area and air velocity.
 *
 * @property areaOfDuct number, cross-sectional area of the duct, units m^2
 * @property airVelocity number, measured air velocity in the duct, units m/min
 */
export interface SteamMassFlowMeasuredData {
    /** Cross-sectional area of the duct, units m^2 */
    areaOfDuct: number;
    /** Measured air velocity in the duct, units m/min */
    airVelocity: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input data for the air or water mass flow measurement method.
 *
 * Aggregates all data needed for either the air mass flow or water mass flow method.
 * If `isNameplate` is true, the nameplate flow rate is used; otherwise the flow rate is
 * derived from measured duct area and air velocity.
 *
 * @property isNameplate boolean, true to use nameplate data; false to use measured data
 * @property massFlowMeasuredData {@link SteamMassFlowMeasuredData}, field-measured duct area and air velocity
 * @property massFlowNameplateData {@link SteamMassFlowNameplateData}, nameplate flow rate data
 * @property inletTemperature number, inlet temperature, units degC
 * @property outletTemperature number, outlet temperature, units degC
 */
export interface SteamMassFlowMethodData {
    /** True to use nameplate data; false to use measured data */
    isNameplate: boolean;
    /** Field-measured duct area and air velocity */
    massFlowMeasuredData: SteamMassFlowMeasuredData;
    /** Nameplate flow rate data */
    massFlowNameplateData: SteamMassFlowNameplateData;
    /** Inlet temperature, units degC */
    inletTemperature: number;
    /** Outlet temperature, units degC */
    outletTemperature: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input data for the offsheet (direct consumption) measurement method.
 *
 * Used when energy consumption is known directly from a report, bill, or another source
 * without requiring a flow-rate conversion.
 *
 * @property consumption number, total annual energy consumption, units kJ/year
 */
export interface SteamOffsheetMethodData {
    /** Total annual energy consumption, units kJ/year */
    consumption: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Main input / output value objects
// ---------------------------------------------------------------------------

/**
 * Input data for a single steam reduction measure.
 *
 * Aggregates all parameters needed to evaluate one measure. The active measurement method
 * is selected via {@link SteamMeasurementMethod}; only the corresponding method data struct
 * is used in the calculation. Steam properties are determined from the specified pressure and
 * thermodynamic variable.
 *
 * @property hoursPerYear number, annual operating hours, units hours/year
 * @property utilityType {@link SteamUtilityType}, utility type for energy cost calculation
 * @property utilityCost number, utility cost rate ($/kg for steam, $/kJ for gas/other)
 * @property measurementMethod {@link SteamMeasurementMethod}, measurement method to apply
 * @property systemEfficiency number, system efficiency (dimensionless)
 * @property pressure number, steam pressure, units MPaa
 * @property flowMeterMethodData {@link SteamFlowMeterMethodData}, data for flow meter method
 * @property airMassFlowMethodData {@link SteamMassFlowMethodData}, data for air mass flow method
 * @property waterMassFlowMethodData {@link SteamMassFlowMethodData}, data for water mass flow method
 * @property offsheetMethodData {@link SteamOffsheetMethodData}, data for offsheet method
 * @property units number, unit conversion factor (dimensionless)
 * @property boilerEfficiency number, boiler efficiency (dimensionless)
 * @property steamVariableOption {@link ThermodynamicQuantity}, thermodynamic quantity type for steam property lookup
 * @property steamVariable number, steam thermodynamic variable value
 * @property feedWaterTemperature number, feedwater temperature, units K
 */
export interface SteamReductionInput {
    /** Annual operating hours, units hours/year */
    hoursPerYear: number;
    /** Utility type for energy cost calculation */
    utilityType: SteamUtilityType;
    /** Utility cost rate ($/kg for steam, $/kJ for gas/other) */
    utilityCost: number;
    /** Measurement method to apply */
    measurementMethod: SteamMeasurementMethod;
    /** System efficiency (dimensionless) */
    systemEfficiency: number;
    /** Steam pressure, units MPaa */
    pressure: number;
    /** Data for the flow meter method */
    flowMeterMethodData: SteamFlowMeterMethodData;
    /** Data for the air mass flow method */
    airMassFlowMethodData: SteamMassFlowMethodData;
    /** Data for the water mass flow method */
    waterMassFlowMethodData: SteamMassFlowMethodData;
    /** Data for the offsheet method */
    offsheetMethodData: SteamOffsheetMethodData;
    /** Unit conversion factor (dimensionless) */
    units: number;
    /** Boiler efficiency (dimensionless) */
    boilerEfficiency: number;
    /** Thermodynamic quantity type for steam property lookup */
    steamVariableOption: ThermodynamicQuantity;
    /** Steam thermodynamic variable value */
    steamVariable: number;
    /** Feedwater temperature, units K */
    feedWaterTemperature: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link steamReduction}.
 *
 * Contains the accumulated annual steam use, energy use, and energy cost across all
 * measures passed to {@link steamReduction}.
 *
 * @property steamUse number, annual steam use, units kg/year
 * @property energyUse number, annual energy use, units kJ/year
 * @property energyCost number, annual energy cost, units $/year
 */
export interface SteamReductionOutput {
    /** Annual steam use, units kg/year */
    steamUse: number;
    /** Annual energy use, units kJ/year */
    energyUse: number;
    /** Annual energy cost, units $/year */
    energyCost: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Calculator function
// ---------------------------------------------------------------------------

/**
 * Calculate total annual steam use, energy use, and energy cost for a collection of steam reduction measures.
 *
 * Iterates over `input_vec`, dispatches each measure to the appropriate measurement
 * method helper, and accumulates the results.
 *
 * @param input_vec Vector of {@link SteamReductionInput} structs, one per measure.
 * @returns {@link SteamReductionOutput} with summed annual steam use (kg/year),
 *   energy use (kJ/year), and energy cost ($/year).
 */
export function steamReduction(input_vec: SteamReductionInputV): SteamReductionOutput;

export type SteamReductionModule = {
    SteamMeasurementMethod: typeof SteamMeasurementMethod;
    SteamUtilityType: typeof SteamUtilityType;
    SteamFlowMeterMethodData: SteamFlowMeterMethodData;
    SteamMassFlowNameplateData: SteamMassFlowNameplateData;
    SteamMassFlowMeasuredData: SteamMassFlowMeasuredData;
    SteamMassFlowMethodData: SteamMassFlowMethodData;
    SteamOffsheetMethodData: SteamOffsheetMethodData;
    SteamReductionInput: SteamReductionInput;
    SteamReductionOutput: SteamReductionOutput;
    steamReduction: typeof steamReduction;
};
