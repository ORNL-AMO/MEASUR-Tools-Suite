import { BagMethodInput } from "./bag_method";
import { DecibelsMethodInput } from "./decibels_method";
import { EstimateMethodInput } from "./estimate_method";
import { OrificeMethodInput } from "./orifice_method";
import { CompressorElectricityData } from "../compressed_air_utils";

/**
 * Compressed Air Leak Survey
 *
 * Aggregates leak estimates from supported field measurement methods and
 * computes annual air, electricity, and cost impact.
 */

/**
 * Selects the field measurement method used to estimate each leak's flow rate.
 * @details Each method is implemented in its own leak survey binding module.
 */
export enum MeasurementMethod {
    Estimate = 0,
    Decibels = 1,
    Bag = 2,
    Orifice = 3
}

/**
 * Selects the cost basis used to convert annual leak flow to annual cost.
 */
export enum UtilityTypeCA {
    CompressedAir = 0,
    Electricity = 1
}

/**
 * Input parameters for one leak entry in a compressed air leak survey.
 * @details A single input represents one or more identical leak points. The
 *          `units` field acts as a multiplier so groups of identical leaks can
 *          be entered as one row.
 *
 *          All sub-method input structs are provided; only the one selected by
 *          `measurementMethod` is used in calculation.
 *
 * @property hoursPerYear double, annual system operating time in hours per year.
 * @property utilityType UtilityTypeCA, unitless enum selecting the cost basis for annual cost calculation. 0 = compressed air, 1 = electricity
 * @property utilityCost double, cost per unit of utility in $/kWh or $/scf depending on utilityType.
 * @property measurementMethod MeasurementMethod, unitless enum selecting the field measurement method used to estimate leak flow rate. 0 = estimate, 1 = decibels, 2 = bag, 3 = orifice
 * @property estimateMethodInput EstimateMethodInput, input parameters for the estimate method.
 * @property decibelsMethodInput DecibelsMethodInput, input parameters for the decibels method.
 * @property bagMethodInput BagMethodInput, input parameters for the bag method.
 * @property orificeMethodInput OrificeMethodInput, input parameters for the orifice method.
 * @property compressorElectricityData CompressorElectricityData, electricity data for converting leak flow to cost when utilityType is electricity.
 * @property units number, multiplier to represent multiple identical leak points.
 */
export interface CompressedAirLeakSurveyInput {
    hoursPerYear: number;
    utilityType: UtilityTypeCA;
    utilityCost: number;
    measurementMethod: MeasurementMethod;
    estimateMethodInput: EstimateMethodInput;
    decibelsMethodInput: DecibelsMethodInput;
    bagMethodInput: BagMethodInput;
    orificeMethodInput: OrificeMethodInput;
    compressorElectricityData: CompressorElectricityData;
    units: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Aggregate result of a compressed air leak survey.
 *
 * @property annualTotalElectricity double, total annual electrical energy consumed by all leaks in kWh.
 * @property annualTotalElectricityCost double, total annual utility cost of all leaks in $/year.
 * @property totalFlowRate double, combined instantaneous flow rate of all leaks in scfm.
 * @property annualTotalFlowRate double, combined annual air volume lost to leaks in scf.
 */
export interface CompressedAirLeakSurveyResult {
    annualTotalElectricity: number;
    annualTotalElectricityCost: number;
    totalFlowRate: number;
    annualTotalFlowRate: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates the aggregate energy cost and flow impact of a compressed air leak survey.
 * @details Iterates over each survey entry, routes it to the selected measurement
 *          sub-calculator, applies the `units` multiplier, computes utility cost,
 *          and accumulates totals.
 * @param inputs {@link CompressedAirLeakSurveyInput} Array of survey entries, one per leak measurement row.
 * @returns {@link CompressedAirLeakSurveyResult} containing accumulated survey totals.
 */
export function calculateCompressedAirLeakSurvey(
    inputs: CompressedAirLeakSurveyInput[]
): CompressedAirLeakSurveyResult;

export type CompressedAirLeakSurveyModule = {
    MeasurementMethod: typeof MeasurementMethod;
    UtilityTypeCA: typeof UtilityTypeCA;
    calculateCompressedAirLeakSurvey: typeof calculateCompressedAirLeakSurvey;
    CompressedAirLeakSurveyInput: CompressedAirLeakSurveyInput;
    CompressedAirLeakSurveyResult: CompressedAirLeakSurveyResult;
};