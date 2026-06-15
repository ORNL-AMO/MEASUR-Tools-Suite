/**
 * Electricity Reduction calculations.
 *
 * Provides a function-based API for estimating annual electricity use and cost savings
 * for electricity reduction measures identified during an energy treasure hunt or efficiency
 * assessment. Supports four measurement methods: multimeter, nameplate, power meter, and other.
 */

// ---------------------------------------------------------------------------
// Enumerations
// ---------------------------------------------------------------------------

import { ElectricityReductionInputV } from "../binding/registered_vectors";

/**
 * Selects the measurement method used to determine electricity use for a single measure.
 *
 * - `Multimeter` - uses voltage, current, and power factor
 * - `Nameplate`  - uses rated motor power, load factor, and efficiency
 * - `PowerMeter` - uses a direct power reading
 * - `Other`      - uses a directly supplied annual energy value
 */
export enum ElectricityReductionMeasurementMethod {
    Multimeter = 0,
    Nameplate  = 1,
    PowerMeter = 2,
    Other      = 3,
}

// ---------------------------------------------------------------------------
// Measurement method data value objects
// ---------------------------------------------------------------------------

/**
 * Input data for the multimeter measurement method.
 *
 * Used when electrical power is measured with a clamp-on ammeter or multimeter.
 * The supply voltage, average current, and power factor are combined with the number
 * of phases to calculate total power draw.
 *
 * @property numberOfPhases number, number of electrical phases (1 or 3)
 * @property supplyVoltage number, supply voltage, units V
 * @property averageCurrent number, average current measured by the meter, units A
 * @property powerFactor number, power factor of the load (dimensionless, 0-1)
 */
export interface MultimeterData {
    /** Number of electrical phases (1 or 3) */
    numberOfPhases: number;
    /** Supply voltage, units V */
    supplyVoltage: number;
    /** Average current measured by the meter, units A */
    averageCurrent: number;
    /** Power factor of the load (dimensionless, 0-1) */
    powerFactor: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input data for the nameplate measurement method.
 *
 * Used when power draw is estimated from motor nameplate information rather than direct
 * measurement. The rated motor power is adjusted for load factor, speed ratio, and combined
 * motor-and-drive efficiency to obtain an operating power estimate.
 *
 * @property ratedMotorPower number, rated motor power from the nameplate, units kW
 * @property variableSpeedMotor boolean, whether the motor is driven by a variable-speed drive
 * @property operationalFrequency number, actual operating frequency, units Hz
 * @property lineFrequency number, nominal line frequency, units Hz
 * @property motorAndDriveEfficiency number, combined motor and drive efficiency, units % (0-100)
 * @property loadFactor number, motor load factor (dimensionless, 0-1)
 */
export interface NameplateData {
    /** Rated motor power from the nameplate, units kW */
    ratedMotorPower: number;
    /** Whether the motor is driven by a variable-speed drive */
    variableSpeedMotor: boolean;
    /** Actual operating frequency, units Hz */
    operationalFrequency: number;
    /** Nominal line frequency, units Hz */
    lineFrequency: number;
    /** Combined motor and drive efficiency, units % (0-100) */
    motorAndDriveEfficiency: number;
    /** Motor load factor (dimensionless, 0-1) */
    loadFactor: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input data for the power meter measurement method.
 *
 * Used when a power meter provides a direct reading of the electrical power drawn by the load.
 * The power reading is combined with operating hours to calculate annual energy use.
 *
 * @property power number, direct power reading from the power meter, units kW
 */
export interface PowerMeterData {
    /** Direct power reading from the power meter, units kW */
    power: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input data for the other (direct energy) measurement method.
 *
 * Used when annual energy consumption is known directly from a utility bill, report, or other
 * source without requiring a power-to-energy conversion.
 *
 * @property energy number, annual energy consumption, units kWh/year
 */
export interface ElectricityOtherMethodData {
    /** Annual energy consumption, units kWh/year */
    energy: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Main input / output value objects
// ---------------------------------------------------------------------------

/**
 * Input data for a single electricity reduction measure.
 *
 * Aggregates all parameters needed to evaluate one measure. The active measurement method
 * is selected via {@link ElectricityReductionMeasurementMethod}; only the corresponding method
 * data struct is used in the calculation. The `units` field is a quantity multiplier (e.g.,
 * number of identical loads).
 *
 * @property operatingHours number, annual operating hours, units hours/year
 * @property electricityCost number, electricity cost rate, units $/kWh
 * @property measurementMethod {@link ElectricityReductionMeasurementMethod}, measurement method to apply
 * @property multimeterData {@link MultimeterData}, data for the multimeter method
 * @property nameplateData {@link NameplateData}, data for the nameplate method
 * @property powerMeterData {@link PowerMeterData}, data for the power meter method
 * @property otherMethodData {@link ElectricityOtherMethodData}, data for the other method
 * @property units number, quantity multiplier (number of identical loads)
 */
export interface ElectricityReductionInput {
    /** Annual operating hours, units hours/year */
    operatingHours: number;
    /** Electricity cost rate, units $/kWh */
    electricityCost: number;
    /** Measurement method to apply */
    measurementMethod: ElectricityReductionMeasurementMethod;
    /** Data for the multimeter method */
    multimeterData: MultimeterData;
    /** Data for the nameplate method */
    nameplateData: NameplateData;
    /** Data for the power meter method */
    powerMeterData: PowerMeterData;
    /** Data for the other method */
    otherMethodData: ElectricityOtherMethodData;
    /** Quantity multiplier (number of identical loads) */
    units: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link electricityReduction} and method-specific helper functions.
 *
 * Contains the accumulated annual energy use, annual energy cost, and total power across
 * all measures passed to {@link electricityReduction}, or the individual result from a
 * single-method helper function.
 *
 * @property energyUse number, annual energy use, units kWh/year
 * @property energyCost number, annual energy cost, units $/year
 * @property power number, power draw per load (single unit), units kW
 */
export interface ElectricityReductionOutput {
    /** Annual energy use, units kWh/year */
    energyUse: number;
    /** Annual energy cost, units $/year */
    energyCost: number;
    /** Power draw per load (single unit), units kW */
    power: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Calculator functions
// ---------------------------------------------------------------------------

/**
 * Calculate total annual electricity use, cost, and power for a collection of measures.
 *
 * Iterates over `input_vec`, dispatches each measure to the appropriate single-method helper
 * (multimeter, nameplate, power meter, or other), and accumulates the results.
 *
 * @param input_vec Vector of {@link ElectricityReductionInput} structs, one per measure.
 * @returns {@link ElectricityReductionOutput} with the summed annual energy use (kWh/year),
 *   annual energy cost ($/year), and summed per-load power (kW) across all measures.
 */
export function electricityReduction(input_vec: ElectricityReductionInputV): ElectricityReductionOutput;

/**
 * Calculate annual energy use and cost using the multimeter measurement method.
 *
 * Computes power per load from the supply voltage, average current, power factor, and number
 * of phases, then scales to annual energy use using the operating hours and the units multiplier.
 *
 * @param data {@link MultimeterData} with voltage (V), current (A), power factor, and number of phases.
 * @param operating_hours Annual operating hours, units hours/year.
 * @param electricity_cost Electricity cost rate, units $/kWh.
 * @param units Quantity multiplier (number of identical loads).
 * @returns {@link ElectricityReductionOutput} with annual energy use (kWh/year),
 *   annual energy cost ($/year), and power per load (kW).
 */
export function multimeterReduction(
    data: MultimeterData,
    operating_hours: number,
    electricity_cost: number,
    units: number
): ElectricityReductionOutput;

/**
 * Calculate annual energy use and cost using the nameplate measurement method.
 *
 * Estimates power per load from the rated motor power, load factor, frequency ratio, and
 * motor-and-drive efficiency. Annual energy use is then obtained by multiplying by the operating
 * hours and the units multiplier.
 *
 * @param data {@link NameplateData} with rated motor power (kW), load factor, operational and
 *   line frequencies (Hz), and motor-and-drive efficiency (%).
 * @param operating_hours Annual operating hours, units hours/year.
 * @param electricity_cost Electricity cost rate, units $/kWh.
 * @param units Quantity multiplier (number of identical loads).
 * @returns {@link ElectricityReductionOutput} with annual energy use (kWh/year),
 *   annual energy cost ($/year), and power per load (kW).
 */
export function nameplateReduction(
    data: NameplateData,
    operating_hours: number,
    electricity_cost: number,
    units: number
): ElectricityReductionOutput;

/**
 * Calculate annual energy use and cost using the power meter measurement method.
 *
 * Multiplies the direct power reading by the annual operating hours and the units multiplier
 * to obtain annual energy use.
 *
 * @param data {@link PowerMeterData} with the direct power reading, units kW.
 * @param operating_hours Annual operating hours, units hours/year.
 * @param electricity_cost Electricity cost rate, units $/kWh.
 * @param units Quantity multiplier (number of identical loads).
 * @returns {@link ElectricityReductionOutput} with annual energy use (kWh/year),
 *   annual energy cost ($/year), and power per load (kW).
 */
export function powerMeterReduction(
    data: PowerMeterData,
    operating_hours: number,
    electricity_cost: number,
    units: number
): ElectricityReductionOutput;

/**
 * Calculate annual energy cost using a directly supplied energy consumption value.
 *
 * Uses the energy field directly as the annual energy use without any power-to-energy
 * conversion.
 *
 * @param data {@link ElectricityOtherMethodData} with the annual energy consumption, units kWh/year.
 * @param electricity_cost Electricity cost rate, units $/kWh.
 * @returns {@link ElectricityReductionOutput} with annual energy use (kWh/year),
 *   annual energy cost ($/year), and power (kW).
 */
export function electricityOtherReduction(
    data: ElectricityOtherMethodData,
    electricity_cost: number
): ElectricityReductionOutput;

export type ElectricityReductionModule = {
    ElectricityReductionMeasurementMethod: typeof ElectricityReductionMeasurementMethod;
    MultimeterData: MultimeterData;
    NameplateData: NameplateData;
    PowerMeterData: PowerMeterData;
    ElectricityOtherMethodData: ElectricityOtherMethodData;
    ElectricityReductionInput: ElectricityReductionInput;
    ElectricityReductionOutput: ElectricityReductionOutput;
    electricityReduction: typeof electricityReduction;
    multimeterReduction: typeof multimeterReduction;
    nameplateReduction: typeof nameplateReduction;
    powerMeterReduction: typeof powerMeterReduction;
    electricityOtherReduction: typeof electricityOtherReduction;
};
