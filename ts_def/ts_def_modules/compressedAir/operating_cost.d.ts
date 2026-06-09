/**
 * @brief Input parameters for the annual compressor operating cost calculation.
 *
 * @var motorBhp double, full-load motor brake horsepower in bhp.
 * @var bhpUnloaded double, percentage of full-load BHP consumed when unloaded.
 * @var annualOperatingHours double, total compressor operating hours per year in hours.
 * @var runTimeLoaded double, percentage of operating time the compressor runs loaded.
 * @var efficiencyLoaded double, motor efficiency in the loaded condition as percentage.
 * @var efficiencyUnloaded double, motor efficiency in the unloaded condition as percentage.
 * @var costOfElectricity double, electricity unit cost in $/kWh.
 */
export interface OperatingCostInput {
    motorBhp: number;
    bhpUnloaded: number;
    annualOperatingHours: number;
    runTimeLoaded: number;
    efficiencyLoaded: number;
    efficiencyUnloaded: number;
    costOfElectricity: number;
}

/**
 * @brief Result of the annual compressor operating cost calculation.
 *
 * @var runTimeUnloaded double, percentage of operating time the compressor runs unloaded.
 * @var costForLoaded double, annual electricity cost in the loaded condition in $/year.
 * @var costForUnloaded double, annual electricity cost in the unloaded condition in $/year.
 * @var totalAnnualCost double, total annual electricity cost in $/year.
 */
export interface OperatingCostResult {
    runTimeUnloaded: number;
    costForLoaded: number;
    costForUnloaded: number;
    totalAnnualCost: number;
}

/**
 * @brief Calculates the annual electricity cost for a compressor cycling between loaded and unloaded operation.
 * @details Computes unloaded runtime percentage, loaded annual cost, unloaded annual cost, and total annual cost.
 * @note Percentage inputs are provided on a 0-100 scale and converted internally.
 * @param input OperatingCostInput
 * @return OperatingCostResult with unloaded runtime and annual cost components.
 */
export function calculateOperatingCost(input: OperatingCostInput): OperatingCostResult;

/** Factory function to load the Operating Cost. */
export default function OperatingCostModule(): Promise<{
    calculateOperatingCost: typeof calculateOperatingCost;
}>;

