/**
 * Compressor Operating Cost
 *
 * Calculates annual loaded and unloaded compressor electricity cost and
 * total operating cost.
 */

/**
 * Input parameters for the annual compressor operating cost calculation.
 *
 * @property motorBhp double, full-load motor brake horsepower in bhp.
 * @property bhpUnloaded double, percentage of full-load BHP consumed when unloaded.
 * @property annualOperatingHours double, total compressor operating hours per year in hours.
 * @property runTimeLoaded double, percentage of operating time the compressor runs loaded.
 * @property efficiencyLoaded double, motor efficiency, dimensionless in the loaded condition as percentage.
 * @property efficiencyUnloaded double, motor efficiency, dimensionless in the unloaded condition as percentage.
 * @property costOfElectricity double, electricity unit cost in $/kWh.
 */
export interface OperatingCostInput {
    /** full-load motor brake horsepower in bhp. */
    motorBhp: number;
    /** dimensionless % of full-load BHP consumed when unloaded. */
    bhpUnloaded: number;
    /** total compressor operating hours per year in hours. */
    annualOperatingHours: number;
    /** dimensionless % of operating time the compressor runs loaded. */
    runTimeLoaded: number;
    /** motor efficiency, dimensionless in the loaded condition as dimensionless %. */
    efficiencyLoaded: number;
    /** motor efficiency, dimensionless in the unloaded condition as dimensionless %. */
    efficiencyUnloaded: number;
    /** electricity unit cost in $/kWh. */
    costOfElectricity: number;
}

/**
 * Result of the annual compressor operating cost calculation.
 *
 * @property runTimeUnloaded double, percentage of operating time the compressor runs unloaded.
 * @property costForLoaded double, annual electricity cost in the loaded condition in $/year.
 * @property costForUnloaded double, annual electricity cost in the unloaded condition in $/year.
 * @property totalAnnualCost double, total annual electricity cost in $/year.
 */
export interface OperatingCostResult {
    /** dimensionless % of operating time the compressor runs unloaded. */
    runTimeUnloaded: number;
    /** annual electricity cost in the loaded condition units $/year. */
    costForLoaded: number;
    /** annual electricity cost in the unloaded condition units $/year. */
    costForUnloaded: number;
    /** total annual electricity cost units $/year. */
    totalAnnualCost: number;
}

/**
 * Calculates the annual electricity cost for a compressor cycling between loaded and unloaded operation.
 * @details Computes unloaded runtime percentage, loaded annual cost, unloaded annual cost, and total annual cost.
 * @note Percentage inputs are provided on a 0-100 scale and converted internally.
 * @param input {@link OperatingCostInput}
 * @returns {@link OperatingCostResult} with unloaded runtime and annual cost components.
 */
export function calculateOperatingCost(input: OperatingCostInput): OperatingCostResult;

export type OperatingCostModule = {
    calculateOperatingCost: typeof calculateOperatingCost;
};
