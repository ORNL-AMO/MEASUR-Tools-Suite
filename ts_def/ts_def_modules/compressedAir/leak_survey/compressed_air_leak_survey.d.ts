import {BagMethodInput} from "./bag_method";
import {DecibelsMethodInput} from "./decibels_method";
import {EstimateMethodInput} from "./estimate_method";
import {OrificeMethodInput} from "./orifice_method";
import {CompressorElectricityData} from "../compressed_air_utils";

/**
 * @brief Selects the field measurement method used to estimate each leak's flow rate.
 * @details Each method is implemented in its own leak survey binding module.
 */
export enum MeasurementMethod {
    Estimate = 0,
    Decibels = 1,
    Bag = 2,
    Orifice = 3
}

/**
 * @brief Selects the cost basis used to convert annual leak flow to annual cost.
 */
export enum UtilityType {
    CompressedAir = 0,
    Electricity = 1
}

/**
 * @brief Input parameters for one leak entry in a compressed air leak survey.
 * @details A single input represents one or more identical leak points. The
 *          `units` field acts as a multiplier so groups of identical leaks can
 *          be entered as one row.
 *
 *          All sub-method input structs are provided; only the one selected by
 *          `measurementMethod` is used in calculation.
 *
 * @var hoursPerYear double, annual system operating time in hours per year.
 * @var utilityType UtilityType, unitless enum selecting the cost basis for annual cost calculation. 0 = compressed air, 1 = electricity
 * @var utilityCost double, cost per unit of utility in $/kWh or $/scf depending on utilityType.
 * @var measurementMethod MeasurementMethod, unitless enum selecting the field measurement method used to estimate leak flow rate. 0 = estimate, 1 = decibels, 2 = bag, 3 = orifice
 * @var estimateMethodInput EstimateMethodInput, input parameters for the estimate method.
 * @var decibelsMethodInput DecibelsMethodInput, input parameters for the decibels method.
 * @var bagMethodInput BagMethodInput, input parameters for the bag method.
 * @var orificeMethodInput OrificeMethodInput, input parameters for the orifice method.
 * @var compressorElectricityData CompressorElectricityData, electricity data for converting leak flow to cost when utilityType is electricity.
 * @var units number, multiplier to represent multiple identical leak points.
 */
export interface CompressedAirLeakSurveyInput {
    hoursPerYear: number;
    utilityType: UtilityType;
    utilityCost: number;
    measurementMethod: MeasurementMethod;
    estimateMethodInput: EstimateMethodInput;
    decibelsMethodInput: DecibelsMethodInput;
    bagMethodInput: BagMethodInput;
    orificeMethodInput: OrificeMethodInput;
    compressorElectricityData: CompressorElectricityData;
    units: number;
}

/**
 * @brief Aggregate result of a compressed air leak survey.
 *
 * @var annualTotalElectricity double, total annual electrical energy consumed by all leaks in kWh.
 * @var annualTotalElectricityCost double, total annual utility cost of all leaks in $/year.
 * @var totalFlowRate double, combined instantaneous flow rate of all leaks in scfm.
 * @var annualTotalFlowRate double, combined annual air volume lost to leaks in scf.
 */
export interface CompressedAirLeakSurveyResult {
    annualTotalElectricity: number;
    annualTotalElectricityCost: number;
    totalFlowRate: number;
    annualTotalFlowRate: number;
}

/**
 * @brief Calculates the aggregate energy cost and flow impact of a compressed air leak survey.
 * @details Iterates over each survey entry, routes it to the selected measurement
 *          sub-calculator, applies the `units` multiplier, computes utility cost,
 *          and accumulates totals.
 * @param inputs Array of survey entries, one per leak measurement row.
 * @return CompressedAirLeakSurveyResult containing accumulated survey totals.
 */
export function calculateCompressedAirLeakSurvey(
    inputs: CompressedAirLeakSurveyInput[]
): CompressedAirLeakSurveyResult;

/** Factory function to load the Compressed Air Leak Survey. */
export default function CompressedAirLeakSurveyModule(): Promise<{
    calculateCompressedAirLeakSurvey: typeof calculateCompressedAirLeakSurvey;
}>;

