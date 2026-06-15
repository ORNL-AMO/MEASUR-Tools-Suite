/**
 * Combined Heat and Power (CHP) economics.
 *
 * Provides operating economics calculations for CHP systems, including
 * annual savings, fuel costs, operating costs, and payback metrics.
 */

/**
 * CHP cost calculation option.
 */
export enum CHPOption {
    PercentAvgkWhElectricCostAvoided = 0,
    StandbyRate = 1
}

/**
 * Result object returned by {@link CHP.getCostInfo}.
 *
 * @property annualOperationSavings double, annual operating savings in $
 * @property totalInstalledCostsPayback double, total installed costs used for payback in $
 * @property simplePayback double, simple payback in years
 * @property fuelCosts double, annual fuel costs in $
 * @property thermalCredit double, annual thermal credit in $
 * @property incrementalOandM double, annual incremental O&M costs in $
 * @property totalOperatingCosts double, annual total operating costs in $
 */
export declare class CostInfoOutput {
    /**
     * Creates a CHP cost summary result.
     *
     * @param annualOperationSavings double, annual operating savings in $
     * @param totalInstalledCostsPayback double, total installed costs used for payback in $
     * @param simplePayback double, simple payback in years
     * @param fuelCosts double, annual fuel costs in $
     * @param thermalCredit double, annual thermal credit in $
     * @param incrementalOandM double, annual incremental O&M costs in $
     * @param totalOperatingCosts double, annual total operating costs in $
     */
    constructor(
        annualOperationSavings: number,
        totalInstalledCostsPayback: number,
        simplePayback: number,
        fuelCosts: number,
        thermalCredit: number,
        incrementalOandM: number,
        totalOperatingCosts: number
    );

    /** Annual operating savings, units $ */
    annualOperationSavings: number;
    /** Total installed costs used for payback, units $ */
    totalInstalledCostsPayback: number;
    /** Simple payback, units years */
    simplePayback: number;
    /** Fuel costs, units $ */
    fuelCosts: number;
    /** Thermal credit, units $ */
    thermalCredit: number;
    /** Incremental O&M costs, units $ */
    incrementalOandM: number;
    /** Total operating costs, units $ */
    totalOperatingCosts: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * CHP calculator.
 *
 * Computes CHP operating economics from annual electricity and thermal demand,
 * fuel/electric costs, and utilization/availability assumptions.
 */
export declare class CHP {
    /**
     * Creates a CHP calculation instance.
     *
     * @param annualOperatingHours double, annual operating hours
     * @param annualElectricityConsumption double, annual electricity consumption in kWh
     * @param annualThermalDemand double, annual thermal demand in MMBtu
     * @param boilerThermalFuelCosts double, boiler thermal fuel cost in $/MMBtu
     * @param avgElectricityCosts double, average electricity cost in $/kWh
     * @param option CHPOption, calculation option
     * @param boilerThermalFuelCostsCHPcase double, boiler thermal fuel costs for CHP case in $/MMBtu
     * @param CHPfuelCosts double, CHP fuel costs in $/MMBtu
     * @param percentAvgkWhElectricCostAvoidedOrStandbyRate double, option-dependent value percent
     * @param displacedThermalEfficiency double, displaced thermal efficiency percent
     * @param chpAvailability double, CHP availability percent
     * @param thermalUtilization double, thermal utilization percent
     */
    constructor(
        annualOperatingHours: number,
        annualElectricityConsumption: number,
        annualThermalDemand: number,
        boilerThermalFuelCosts: number,
        avgElectricityCosts: number,
        option: CHPOption,
        boilerThermalFuelCostsCHPcase: number,
        CHPfuelCosts: number,
        percentAvgkWhElectricCostAvoidedOrStandbyRate: number,
        displacedThermalEfficiency: number,
        chpAvailability: number,
        thermalUtilization: number
    );

    /**
     * Calculates CHP cost outputs.
     *
     * @returns {@link CostInfoOutput}
     */
    getCostInfo(): CostInfoOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type ChpModule = {
    CHPOption: typeof CHPOption;
    CHP: typeof CHP;
    CostInfoOutput: typeof CostInfoOutput;
};
