/**
 * CHP cost calculation option.
 */
export enum CHPOption {
    PercentAvgkWhElectricCostAvoided = 0,
    StandbyRate = 1
}

/**
 * Output of CHP cost calculations.
 */
export declare class CostInfoOutput {
    /**
     * Constructor for CostInfoOutput
     * @param annualOperationSavings double
     * @param totalInstalledCostsPayback double
     * @param simplePayback double
     * @param fuelCosts double
     * @param thermalCredit double
     * @param incrementalOandM double
     * @param totalOperatingCosts double
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

    annualOperationSavings: number;
    totalInstalledCostsPayback: number;
    simplePayback: number;
    fuelCosts: number;
    thermalCredit: number;
    incrementalOandM: number;
    totalOperatingCosts: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates CHP-related operating economics.
 */
export declare class CHP {
    /**
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
     * Gets the Net CHP power
     * @returns double const, Net CHP power in  MMBtu
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
