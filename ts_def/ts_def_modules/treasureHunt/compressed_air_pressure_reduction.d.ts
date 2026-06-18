/**
 * Compressed-Air Pressure Reduction calculations.
 *
 * Provides a function-based API for estimating annual energy use and annual energy cost
 * for compressed-air systems based on baseline operation or pressure-reduction modification cases.
 */

// ---------------------------------------------------------------------------
// Input / Output value objects
// ---------------------------------------------------------------------------

import {CompressedAirPressureReductionInputV} from "../binding/registered_vectors";

/**
 * Input data for a single compressed-air pressure reduction measure.
 *
 * @property isBaseline boolean, true for baseline calculation, false for modification calculation
 * @property hoursPerYear number, annual operating hours, units hours/year
 * @property electricityCost number, electricity cost rate, units $/kWh
 * @property compressorPower number, compressor power, units kW
 * @property pressure number, baseline compressor discharge pressure, units psi
 * @property proposedPressure number, proposed compressor discharge pressure, units psi
 * @property atmosphericPressure number, local atmospheric pressure, units psi
 * @property pressureRated number, rated compressor pressure, units psi
 */
export interface CompressedAirPressureReductionInput {
    /** True for baseline calculation, false for modification calculation */
    isBaseline: boolean;
    /** Annual operating hours, units hours/year */
    hoursPerYear: number;
    /** Electricity cost rate, units $/kWh */
    electricityCost: number;
    /** Compressor power, units kW */
    compressorPower: number;
    /** Baseline compressor discharge pressure, units psi */
    pressure: number;
    /** Proposed compressor discharge pressure, units psi */
    proposedPressure: number;
    /** Local atmospheric pressure, units psi */
    atmosphericPressure: number;
    /** Rated compressor pressure, units psi */
    pressureRated: number;
}

/**
 * Result object returned by {@link compressedAirPressureReduction}.
 *
 * @property energyUse number, annual energy use, units kWh/year
 * @property energyCost number, annual energy cost, units $/year
 */
export interface CompressedAirPressureReductionOutput {
    /** Annual energy use, units kWh/year */
    energyUse: number;
    /** Annual energy cost, units $/year */
    energyCost: number;
}

// ---------------------------------------------------------------------------
// Calculator function
// ---------------------------------------------------------------------------

/**
 * Calculate total annual energy use and cost for compressed-air pressure reduction measures.
 * @param input_vec Vector of {@link CompressedAirPressureReductionInput} structs representing
 *   one or more baseline/modification cases to accumulate.
 * @returns {@link CompressedAirPressureReductionOutput} containing accumulated annual energy use and cost.
 */
export function compressedAirPressureReduction(
    input_vec: CompressedAirPressureReductionInputV
): CompressedAirPressureReductionOutput;

export type CompressedAirPressureReductionModule = {
    compressedAirPressureReduction: typeof compressedAirPressureReduction;
};
