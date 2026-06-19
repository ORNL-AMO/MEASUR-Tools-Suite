/**
 * Steam System Modeler Tool (SSMT) - modeler entry-point and I/O types.
 *
 * Provides input/output classes and domain result objects for running the full
 * Steam System Modeler (SSMT) calculation, including boiler, header, turbine,
 * and operational inputs plus all intermediate calculation domain outputs.
 *
 * Enumerations (`CondensingTurbineOperation`, `PressureTurbineOperation`) are
 * imported from the `ssmtEnum` module.
 * Core output types (`Boiler`, `Deaerator`, `FlashTank`, `HeatLoss`,
 * `HeatExchangerOutput`, `FluidProperties`, `PrvWithoutDesuperheating`,
 * `Turbine`) are imported from the `ssmt` module.
 */

import type {
    CondensingTurbineOperation,
    PressureTurbineOperation,
} from './ssmtEnum';

import type {
    Boiler,
    Deaerator,
    FlashTank,
    FluidProperties,
    HeatExchangerOutput,
    HeatLoss,
    PrvWithoutDesuperheating,
    Turbine,
} from './ssmt';

export type {
    CondensingTurbineOperation,
    PressureTurbineOperation,
    Boiler,
    Deaerator,
    FlashTank,
    FluidProperties,
    HeatExchangerOutput,
    HeatLoss,
    PrvWithoutDesuperheating,
    Turbine,
};

// ---------------------------------------------------------------------------
// Input classes
// ---------------------------------------------------------------------------

/**
 * Steam Modeler boiler input data.
 */
export declare class BoilerInput {
    /**
     * @param fuelType Fuel type identifier, unitless enum value.
     * @param fuel Fuel heating value, units MMBtu/unit fuel.
     * @param combustionEfficiency Combustion efficiency, units %.
     * @param blowdownRate Blowdown rate as percent of inlet mass flow, units %.
     * @param blowdownFlashed boolean, whether blowdown is flashed
     * @param preheatMakeupWater boolean, whether makeup water is preheated
     * @param steamTemperature double, steam temperature, units K
     * @param deaeratorVentRate Deaerator vent rate, units %.
     * @param deaeratorPressure double, deaerator pressure, units MPa
     * @param approachTemperature double, approach temperature, units K
     */
    constructor(
        fuelType: number,
        fuel: number,
        combustionEfficiency: number,
        blowdownRate: number,
        blowdownFlashed: boolean,
        preheatMakeupWater: boolean,
        steamTemperature: number,
        deaeratorVentRate: number,
        deaeratorPressure: number,
        approachTemperature: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Steam Modeler header input data base class.
 */
export declare class HeaderWithPressure {
    /**
     * @param pressure double, header pressure, units MPa
     * @param processSteamUsage double, process steam usage, units kg/hr
     * @param condensationRecoveryRate Condensation recovery rate, units %.
     * @param heatLoss Header heat loss, units %.
     * @param flashCondensate boolean, whether to flash condensate
     */
    constructor(
        pressure: number,
        processSteamUsage: number,
        condensationRecoveryRate: number,
        heatLoss: number,
        flashCondensate: boolean
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Steam Modeler header input data for the header with the highest pressure.
 */
export declare class HeaderWithHighestPressure extends HeaderWithPressure {
    /**
     * @param pressure double, header pressure, units MPa
     * @param processSteamUsage double, process steam usage, units kg/hr
     * @param condensationRecoveryRate Condensation recovery rate, units %.
     * @param heatLoss Header heat loss, units %.
     * @param condensateReturnTemperature double, condensate return temperature, units K
     * @param flashCondensateReturn boolean, whether to flash the condensate return
     */
    constructor(
        pressure: number,
        processSteamUsage: number,
        condensationRecoveryRate: number,
        heatLoss: number,
        condensateReturnTemperature: number,
        flashCondensateReturn: boolean
    );
}

/**
 * Steam Modeler header input data for a header with non-highest pressure.
 */
export declare class HeaderNotHighestPressure extends HeaderWithPressure {
    /**
     * @param pressure double, header pressure, units MPa
     * @param processSteamUsage double, process steam usage, units kg/hr
     * @param condensationRecoveryRate Condensation recovery rate, units %.
     * @param heatLoss Header heat loss, units %.
     * @param flashCondensateIntoHeader boolean, whether to flash condensate into the header
     * @param desuperheatSteamIntoNextHighest boolean, whether to desuperheat steam into the next highest pressure header
     * @param desuperheatSteamTemperature double, desuperheat steam temperature, units K
     */
    constructor(
        pressure: number,
        processSteamUsage: number,
        condensationRecoveryRate: number,
        heatLoss: number,
        flashCondensateIntoHeader: boolean,
        desuperheatSteamIntoNextHighest: boolean,
        desuperheatSteamTemperature: number
    );
}

/**
 * Steam Modeler header input data; aggregates all pressure headers.
 */
export declare class HeaderInput {
    /**
     * @param highPressureHeader {@link HeaderWithHighestPressure} high-pressure header configuration
     * @param mediumPressureHeader {@link HeaderNotHighestPressure} | null, optional medium-pressure header (nullptr when absent)
     * @param lowPressureHeader {@link HeaderNotHighestPressure} | null, optional low-pressure header (nullptr when absent)
     */
    constructor(
        highPressureHeader: HeaderWithHighestPressure,
        mediumPressureHeader: HeaderNotHighestPressure | null,
        lowPressureHeader: HeaderNotHighestPressure | null
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Steam Modeler operations input data.
 */
export declare class OperationsInput {
    /**
     * @param sitePowerImport double, site power import, units kW
     * @param makeUpWaterTemperature double, makeup water temperature, units K
     * @param operatingHoursPerYear Operating hours per year, units hr/year.
     * @param fuelCosts Fuel cost, units $/MMBtu.
     * @param electricityCosts Electricity cost, units $/kWh.
     * @param makeUpWaterCosts Makeup water cost, units $/1000 gal.
     */
    constructor(
        sitePowerImport: number,
        makeUpWaterTemperature: number,
        operatingHoursPerYear: number,
        fuelCosts: number,
        electricityCosts: number,
        makeUpWaterCosts: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Steam Modeler condensing turbine input data.
 */
export declare class CondensingTurbine {
    /**
     * @param isentropicEfficiency double, isentropic efficiency (fraction 0-1)
     * @param generationEfficiency double, generation efficiency (fraction 0-1)
     * @param condenserPressure double, condenser pressure, units MPa
     * @param operationType {@link CondensingTurbineOperation} turbine operation mode
     * @param operationValue double, value corresponding to the operation type (kg/hr or kW)
     * @param useTurbine boolean, whether to use this turbine in modelling
     */
    constructor(
        isentropicEfficiency: number,
        generationEfficiency: number,
        condenserPressure: number,
        operationType: CondensingTurbineOperation,
        operationValue: number,
        useTurbine: boolean
    );

    /** @returns Isentropic efficiency (fraction) */
    getIsentropicEfficiency(): number;
    /** @returns Generation efficiency (fraction) */
    getGenerationEfficiency(): number;
    /** @returns Condenser pressure, units MPa */
    getCondenserPressure(): number;
    /** @returns Operation value (kg/hr or kW) */
    getOperationValue(): number;
    /** @returns {@link CondensingTurbineOperation} operation type */
    getOperationType(): CondensingTurbineOperation;
    /** @returns Whether this turbine is used in modelling */
    isUseTurbine(): boolean;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Steam Modeler pressure turbine input data.
 */
export declare class PressureTurbine {
    /**
     * @param isentropicEfficiency double, isentropic efficiency (fraction 0-1)
     * @param generationEfficiency double, generation efficiency (fraction 0-1)
     * @param operationType {@link PressureTurbineOperation} turbine operation mode
     * @param operationValue1 double, primary operation value (kg/hr or kW depending on mode)
     * @param operationValue2 Secondary operation value, units kg/hr or kW depending on operationType.
     * @param useTurbine boolean, whether to use this turbine in modelling
     */
    constructor(
        isentropicEfficiency: number,
        generationEfficiency: number,
        operationType: PressureTurbineOperation,
        operationValue1: number,
        operationValue2: number,
        useTurbine: boolean
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Steam Modeler turbine input data; holds all turbine configurations.
 */
export declare class TurbineInput {
    /**
     * @param condensingTurbine {@link CondensingTurbine} condensing turbine configuration
     * @param highToLowTurbine {@link PressureTurbine} high-to-low pressure turbine configuration
     * @param highToMediumTurbine {@link PressureTurbine} high-to-medium pressure turbine configuration
     * @param mediumToLowTurbine {@link PressureTurbine} medium-to-low pressure turbine configuration
     */
    constructor(
        condensingTurbine: CondensingTurbine,
        highToLowTurbine: PressureTurbine,
        highToMediumTurbine: PressureTurbine,
        mediumToLowTurbine: PressureTurbine
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Steam Modeler input data; aggregates all input data for a single model run.
 */
export declare class SteamModelerInput {
    /**
     * @param isBaselineCalc boolean, true if this is a baseline calculation run
     * @param baselinePowerDemand double, baseline power demand, units kW
     * @param boilerInput {@link BoilerInput} boiler configuration
     * @param headerInput {@link HeaderInput} header configuration
     * @param operationsInput {@link OperationsInput} operational parameters
     * @param turbineInput {@link TurbineInput} turbine configurations
     */
    constructor(
        isBaselineCalc: boolean,
        baselinePowerDemand: number,
        boilerInput: BoilerInput,
        headerInput: HeaderInput,
        operationsInput: OperationsInput,
        turbineInput: TurbineInput
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Domain result interfaces
// ---------------------------------------------------------------------------

/**
 * Process steam usage at a given header pressure level.
 *
 * @property pressure double, header pressure, units MPa
 * @property temperature double, header temperature, units K
 * @property energyFlow double, energy flow, units MJ/hr
 * @property massFlow double, mass flow, units kg/hr
 * @property processUsage double, process usage, units kg/hr
 */
export declare class ProcessSteamUsage {
    private constructor();

    /** Header pressure, units MPa */
    pressure: number;
    /** Header temperature, units K */
    temperature: number;
    /** Energy flow, units MJ/hr */
    energyFlow: number;
    /** Mass flow, units kg/hr */
    massFlow: number;
    /** Process usage, units kg/hr */
    processUsage: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Makeup water volume flow calculation results.
 *
 * @property makeupWaterVolumeFlow double, instantaneous makeup water volume flow, units m3/hr
 * @property makeupWaterVolumeFlowAnnual double, annual makeup water volume flow, units m3/yr
 */
export declare class MakeupWaterVolumeFlowCalculationsDomain {
    private constructor();

    /** Instantaneous makeup water volume flow, units m3/hr */
    makeupWaterVolumeFlow: number;
    /** Annual makeup water volume flow, units m3/yr */
    makeupWaterVolumeFlowAnnual: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Return condensate calculation domain results.
 *
 * @property condensateFlashTank {@link FlashTank} | null, optional flash tank for condensate
 * @property returnCondensateFlashed {@link FluidProperties}, properties of the flashed return condensate
 */
export declare class ReturnCondensateCalculationsDomain {
    private constructor();

    /** Optional flash tank for condensate; null when not present */
    condensateFlashTank: FlashTank | null;
    /** Properties of the flashed return condensate */
    returnCondensateFlashed: FluidProperties;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Low-pressure flashed steam into header calculation domain results.
 *
 * @property mediumPressureCondensateFlashTank {@link FlashTank} | null, medium-pressure condensate flash tank
 * @property highPressureCondensateFlashTank {@link FlashTank} | null, original or updated high and medium pressure mix flash tank
 */
export declare class LowPressureFlashedSteamIntoHeaderCalculatorDomain {
    private constructor();

    /** Medium-pressure condensate flash tank; null when not present */
    mediumPressureCondensateFlashTank: FlashTank | null;
    /** Original one or updated with high and medium pressure mix flash tank; null when not present */
    highPressureCondensateFlashTank: FlashTank | null;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Low-pressure vented steam calculation domain results.
 *
 * @property lowPressureVentedSteam double, vented steam quantity, units kg/hr
 * @property makeupWater {@link FluidProperties}, updated makeup water properties
 * @property makeupWaterAndCondensateHeaderOutputUpdated {@link FluidProperties}, updated makeup water and condensate header output
 * @property makeupWaterVolumeFlowCalculationsDomain {@link MakeupWaterVolumeFlowCalculationsDomain}
 * @property deaerator {@link Deaerator}, updated deaerator output
 */
export declare class LowPressureVentedSteamCalculationsDomain {
    private constructor();

    /** Vented steam quantity, units kg/hr */
    lowPressureVentedSteam: number;
    /** Updated makeup water properties */
    makeupWater: FluidProperties;
    /** Updated makeup water and condensate header output properties */
    makeupWaterAndCondensateHeaderOutputUpdated: FluidProperties;
    /** Makeup water volume flow calculation results */
    makeupWaterVolumeFlowCalculationsDomain: MakeupWaterVolumeFlowCalculationsDomain;
    /** Updated deaerator output */
    deaerator: Deaerator;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Energy and cost calculation domain results.
 *
 * @property powerGenerated double, power generated by all turbines, units kW
 * @property sitePowerImport double, net site power import (positive = import), units kW
 * @property powerDemand double, total power demand, units kW
 * @property powerGenerationCost double, annual power generation cost, units $/yr
 * @property boilerFuelCost double, annual boiler fuel cost, units $/yr
 * @property makeupWaterCost double, annual makeup water cost, units $/yr
 * @property totalOperatingCost double, total annual operating cost, units $/yr
 * @property boilerFuelUsage double, boiler fuel usage, units MMBtu/hr
 */
export declare class EnergyAndCostCalculationsDomain {
    private constructor();

    /** Power generated by all turbines, units kW */
    powerGenerated: number;
    /** Net site power import (positive = importing), units kW */
    sitePowerImport: number;
    /** Total power demand, units kW */
    powerDemand: number;
    /** Annual power generation cost, units $/yr */
    powerGenerationCost: number;
    /** Annual boiler fuel cost, units $/yr */
    boilerFuelCost: number;
    /** Annual makeup water cost, units $/yr */
    makeupWaterCost: number;
    /** Total annual operating cost, units $/yr */
    totalOperatingCost: number;
    /** Boiler fuel usage, units MMBtu/hr */
    boilerFuelUsage: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Process steam usage calculation domain results for all pressure levels.
 *
 * @property highPressureProcessSteamUsage {@link ProcessSteamUsage}, high-pressure process steam usage
 * @property lowPressureProcessUsagePtr {@link ProcessSteamUsage} | null, low-pressure process steam usage (null when header is absent)
 * @property mediumPressureProcessUsagePtr {@link ProcessSteamUsage} | null, medium-pressure process steam usage (null when header is absent)
 */
export declare class ProcessSteamUsageCalculationsDomain {
    private constructor();

    /** High-pressure process steam usage */
    highPressureProcessSteamUsage: ProcessSteamUsage;
    /** Low-pressure process steam usage; null when low-pressure header is absent */
    lowPressureProcessUsagePtr: ProcessSteamUsage | null;
    /** Medium-pressure process steam usage; null when medium-pressure header is absent */
    mediumPressureProcessUsagePtr: ProcessSteamUsage | null;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Power balance checker calculation domain results.
 *
 * @property steamBalance double, steam balance across the system, units kg/hr
 * @property lowPressureVentedSteamCalculationsDomain {@link LowPressureVentedSteamCalculationsDomain} | null, vented steam domain (null when absent)
 * @property lowPressureVentedSteam {@link FluidProperties} | null, properties of the low-pressure vented steam (null when absent)
 */
export declare class PowerBalanceCheckerCalculationsDomain {
    private constructor();

    /** Steam balance across the system, units kg/hr */
    steamBalance: number;
    /** Low-pressure vented steam domain; null when not present */
    lowPressureVentedSteamCalculationsDomain: LowPressureVentedSteamCalculationsDomain | null;
    /** Properties of the low-pressure vented steam; null when not present */
    lowPressureVentedSteam: FluidProperties | null;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Makeup water and condensate header calculation domain results.
 *
 * @property combinedCondensate {@link FluidProperties}, combined condensate stream properties
 * @property returnCondensate {@link FluidProperties}, return condensate stream properties
 * @property returnCondensateCalculationsDomain {@link ReturnCondensateCalculationsDomain}
 * @property makeupWater {@link FluidProperties}, makeup water stream properties
 * @property makeupWaterVolumeFlowCalculationsDomain {@link MakeupWaterVolumeFlowCalculationsDomain}
 * @property heatExchangerOutput {@link HeatExchangerOutput} | null, optional heat exchanger output (null when absent)
 * @property makeupWaterAndCondensateHeaderOutput {@link FluidProperties}, combined makeup water and condensate header output
 */
export declare class MakeupWaterAndCondensateHeaderCalculationsDomain {
    private constructor();

    /** Combined condensate stream properties */
    combinedCondensate: FluidProperties;
    /** Return condensate stream properties */
    returnCondensate: FluidProperties;
    /** Return condensate calculation domain */
    returnCondensateCalculationsDomain: ReturnCondensateCalculationsDomain;
    /** Makeup water stream properties */
    makeupWater: FluidProperties;
    /** Makeup water volume flow calculation domain */
    makeupWaterVolumeFlowCalculationsDomain: MakeupWaterVolumeFlowCalculationsDomain;
    /** Heat exchanger output; null when the heat exchanger is absent */
    heatExchangerOutput: HeatExchangerOutput | null;
    /** Combined makeup water and condensate header output properties */
    makeupWaterAndCondensateHeaderOutput: FluidProperties;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Low-pressure header calculation domain results.
 *
 * @property lowPressurePrv {@link PrvWithoutDesuperheating} | null, low-pressure PRV (may be with desuperheating; null when absent)
 * @property lowPressureHeaderOutput {@link FluidProperties}, low-pressure header steam properties
 * @property lowPressureHeaderHeatLoss {@link HeatLoss}, heat loss across the low-pressure header
 * @property lowPressureCondensate {@link FluidProperties}, low-pressure condensate properties
 * @property lowPressureFlashedSteamIntoHeaderCalculatorDomain {@link LowPressureFlashedSteamIntoHeaderCalculatorDomain}
 */
export declare class LowPressureHeaderCalculationsDomain {
    private constructor();

    /** Low-pressure PRV (may be PrvWithDesuperheating); null when absent */
    lowPressurePrv: PrvWithoutDesuperheating | null;
    /** Low-pressure header steam properties */
    lowPressureHeaderOutput: FluidProperties;
    /** Heat loss across the low-pressure header */
    lowPressureHeaderHeatLoss: HeatLoss;
    /** Low-pressure condensate properties */
    lowPressureCondensate: FluidProperties;
    /** Low-pressure flashed steam into header domain results */
    lowPressureFlashedSteamIntoHeaderCalculatorDomain: LowPressureFlashedSteamIntoHeaderCalculatorDomain;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Medium-pressure header calculation domain results.
 *
 * @property highToMediumPressurePrv {@link PrvWithoutDesuperheating} | null, high-to-medium pressure PRV (may be with desuperheating; null when absent)
 * @property highPressureCondensateFlashTank {@link FlashTank} | null, high-pressure condensate flash tank (null when absent)
 * @property mediumPressureHeaderHeatLoss {@link HeatLoss}, heat loss across the medium-pressure header
 * @property mediumPressureHeaderOutput {@link FluidProperties}, medium-pressure header steam properties
 * @property mediumPressureCondensate {@link FluidProperties}, medium-pressure condensate properties
 * @property mediumToLowPressureTurbine {@link Turbine} | null, medium-to-low pressure turbine (null when absent)
 * @property mediumToLowPressureTurbineIdeal {@link Turbine} | null, ideal medium-to-low pressure turbine (null when absent)
 * @property highToLowPressureTurbineUpdated {@link Turbine} | null, updated high-to-low pressure turbine (null when absent)
 * @property highToLowPressureTurbineIdealUpdated {@link Turbine} | null, updated ideal high-to-low pressure turbine (null when absent)
 */
export declare class MediumPressureHeaderCalculationsDomain {
    private constructor();

    /** High-to-medium pressure PRV (may be PrvWithDesuperheating); null when absent */
    highToMediumPressurePrv: PrvWithoutDesuperheating | null;
    /** High-pressure condensate flash tank; null when absent */
    highPressureCondensateFlashTank: FlashTank | null;
    /** Heat loss across the medium-pressure header */
    mediumPressureHeaderHeatLoss: HeatLoss;
    /** Medium-pressure header steam properties */
    mediumPressureHeaderOutput: FluidProperties;
    /** Medium-pressure condensate properties */
    mediumPressureCondensate: FluidProperties;
    /** Medium-to-low pressure turbine; null when absent */
    mediumToLowPressureTurbine: Turbine | null;
    /** Ideal medium-to-low pressure turbine; null when absent */
    mediumToLowPressureTurbineIdeal: Turbine | null;
    /** Updated high-to-low pressure turbine after medium-pressure balancing; null when absent */
    highToLowPressureTurbineUpdated: Turbine | null;
    /** Updated ideal high-to-low pressure turbine after medium-pressure balancing; null when absent */
    highToLowPressureTurbineIdealUpdated: Turbine | null;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * High-pressure header calculation domain results.
 *
 * @property highPressureHeaderOutput {@link FluidProperties}, high-pressure header steam properties
 * @property highPressureHeaderHeatLoss {@link HeatLoss}, heat loss across the high-pressure header
 * @property highPressureCondensate {@link FluidProperties}, high-pressure condensate properties
 * @property highPressureCondensateFlashTank {@link FlashTank} | null, optional high-pressure condensate flash tank
 * @property condensingTurbine {@link Turbine} | null, condensing turbine (null when absent or unused)
 * @property condensingTurbineIdeal {@link Turbine} | null, ideal condensing turbine (null when absent)
 * @property highToMediumPressureTurbine {@link Turbine} | null, high-to-medium pressure turbine (null when absent)
 * @property highToMediumPressureTurbineIdeal {@link Turbine} | null, ideal high-to-medium pressure turbine (null when absent)
 * @property highToLowPressureTurbine {@link Turbine} | null, high-to-low pressure turbine (null when absent)
 * @property highToLowPressureTurbineIdeal {@link Turbine} | null, ideal high-to-low pressure turbine (null when absent)
 */
export declare class HighPressureHeaderCalculationsDomain {
    private constructor();

    /** High-pressure header steam properties */
    highPressureHeaderOutput: FluidProperties;
    /** Heat loss across the high-pressure header */
    highPressureHeaderHeatLoss: HeatLoss;
    /** High-pressure condensate properties */
    highPressureCondensate: FluidProperties;
    /** Optional high-pressure condensate flash tank; null when not present */
    highPressureCondensateFlashTank: FlashTank | null;
    /** Condensing turbine; null when absent or not used */
    condensingTurbine: Turbine | null;
    /** Ideal condensing turbine; null when absent */
    condensingTurbineIdeal: Turbine | null;
    /** High-to-medium pressure turbine; null when absent */
    highToMediumPressureTurbine: Turbine | null;
    /** Ideal high-to-medium pressure turbine; null when absent */
    highToMediumPressureTurbineIdeal: Turbine | null;
    /** High-to-low pressure turbine; null when absent */
    highToLowPressureTurbine: Turbine | null;
    /** Ideal high-to-low pressure turbine; null when absent */
    highToLowPressureTurbineIdeal: Turbine | null;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link SteamModeler.model}.
 *
 * @property boiler {@link Boiler}, boiler output
 * @property blowdownFlashTank {@link FlashTank} | null, blowdown flash tank (null when blowdown is not flashed)
 * @property highPressureHeaderCalculationsDomain {@link HighPressureHeaderCalculationsDomain}
 * @property mediumPressureHeaderCalculationsDomain {@link MediumPressureHeaderCalculationsDomain} | null (null when medium-pressure header is absent)
 * @property lowPressureHeaderCalculationsDomain {@link LowPressureHeaderCalculationsDomain} | null (null when low-pressure header is absent)
 * @property makeupWaterAndCondensateHeaderCalculationsDomain {@link MakeupWaterAndCondensateHeaderCalculationsDomain}
 * @property deaerator {@link Deaerator}, deaerator output
 * @property powerBalanceCheckerCalculationsDomain {@link PowerBalanceCheckerCalculationsDomain}
 * @property processSteamUsageCalculationsDomain {@link ProcessSteamUsageCalculationsDomain}
 * @property energyAndCostCalculationsDomain {@link EnergyAndCostCalculationsDomain}
 */
export declare class SteamModelerOutput {
    private constructor();

    /** Boiler output */
    boiler: Boiler;
    /** Blowdown flash tank; null when blowdown is not flashed */
    blowdownFlashTank: FlashTank | null;
    /** High-pressure header calculation domain results */
    highPressureHeaderCalculationsDomain: HighPressureHeaderCalculationsDomain;
    /** Medium-pressure header calculation domain results; null when header is absent */
    mediumPressureHeaderCalculationsDomain: MediumPressureHeaderCalculationsDomain | null;
    /** Low-pressure header calculation domain results; null when header is absent */
    lowPressureHeaderCalculationsDomain: LowPressureHeaderCalculationsDomain | null;
    /** Makeup water and condensate header calculation domain results */
    makeupWaterAndCondensateHeaderCalculationsDomain: MakeupWaterAndCondensateHeaderCalculationsDomain;
    /** Deaerator output */
    deaerator: Deaerator;
    /** Power balance checker calculation domain results */
    powerBalanceCheckerCalculationsDomain: PowerBalanceCheckerCalculationsDomain;
    /** Process steam usage calculation domain results for all pressure levels */
    processSteamUsageCalculationsDomain: ProcessSteamUsageCalculationsDomain;
    /** Energy and cost calculation domain results */
    energyAndCostCalculationsDomain: EnergyAndCostCalculationsDomain;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Main modeler
// ---------------------------------------------------------------------------

/**
 * The entry-point into the Steam Modeler.
 *
 * Use the `model` method to initiate system balancing with a fully populated
 * {@link SteamModelerInput} object.
 */
export declare class SteamModeler {
    constructor();

    /**
     * Run the Steam Modeler using a {@link SteamModelerInput} object.
     *
     * @param steamModelerInput The object containing the Steam Modeler data for processing
     * @returns {@link SteamModelerOutput}
     */
    model(steamModelerInput: SteamModelerInput): SteamModelerOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type SsmtModelerModule = {
    ProcessSteamUsage: typeof ProcessSteamUsage;
    MakeupWaterVolumeFlowCalculationsDomain: typeof MakeupWaterVolumeFlowCalculationsDomain;
    ReturnCondensateCalculationsDomain: typeof ReturnCondensateCalculationsDomain;
    LowPressureFlashedSteamIntoHeaderCalculatorDomain: typeof LowPressureFlashedSteamIntoHeaderCalculatorDomain;
    LowPressureVentedSteamCalculationsDomain: typeof LowPressureVentedSteamCalculationsDomain;
    EnergyAndCostCalculationsDomain: typeof EnergyAndCostCalculationsDomain;
    ProcessSteamUsageCalculationsDomain: typeof ProcessSteamUsageCalculationsDomain;
    PowerBalanceCheckerCalculationsDomain: typeof PowerBalanceCheckerCalculationsDomain;
    MakeupWaterAndCondensateHeaderCalculationsDomain: typeof MakeupWaterAndCondensateHeaderCalculationsDomain;
    LowPressureHeaderCalculationsDomain: typeof LowPressureHeaderCalculationsDomain;
    MediumPressureHeaderCalculationsDomain: typeof MediumPressureHeaderCalculationsDomain;
    HighPressureHeaderCalculationsDomain: typeof HighPressureHeaderCalculationsDomain;
    SteamModelerOutput: typeof SteamModelerOutput;
    BoilerInput: typeof BoilerInput;
    HeaderWithPressure: typeof HeaderWithPressure;
    HeaderWithHighestPressure: typeof HeaderWithHighestPressure;
    HeaderNotHighestPressure: typeof HeaderNotHighestPressure;
    HeaderInput: typeof HeaderInput;
    OperationsInput: typeof OperationsInput;
    CondensingTurbine: typeof CondensingTurbine;
    PressureTurbine: typeof PressureTurbine;
    TurbineInput: typeof TurbineInput;
    SteamModelerInput: typeof SteamModelerInput;
    SteamModeler: typeof SteamModeler;
};
