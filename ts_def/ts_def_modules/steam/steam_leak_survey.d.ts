/**
 * Utility type used to compute steam cost.
 */
export enum UtilityType {
    steam = 0,
    electric = 1,
    natural_gas = 2
}

/**
 * Result object returned by steam leak calculation methods.
 *
 * @property leakRate double, leak rate in lb/hr
 *
 * @property steamLoss double, steam loss in klb/yr
 *
 * @property energyLoss double, energy loss in MMBtu/yr
 *
 * @property leakCost double, annual leak cost
 */
export declare class SteamLeakSurveyResults {
    private constructor();

    /** Leak rate, units lb/hr */
    leakRate: number;
    /** Steam loss, units klb/yr */
    steamLoss: number;
    /** Energy loss, units MMBtu/yr */
    energyLoss: number;
    /** Annual leak cost, units $/year. */
    leakCost: number;
    /** Steam unit cost used in this calculation, units $/lb. */
    steamUnitCost: number;
    /** Steam specific enthalpy at steam conditions, units Btu/lb. */
    steamSpecificEnthalpy: number;
    /** Isentropic enthalpy at leak pressure, units Btu/lb. */
    isentropicEnthalpy: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Implements plume-based steam leak-rate estimation, based on DOE's Quantify and Eliminate Steam Leaks. */
export declare class QuantifySteamLeakByPlumeLength {
    private constructor();

    /**
     * @param steamPressure double, steam pressure in psig
     * @param plumeLength double, visible plume length in feet
     * @param ambTemp double, ambient temperature, units degF
     * @returns Estimated leak rate, units lb/hr.
     */
    static estimate(steamPressure: number, plumeLength: number, ambTemp: number): number;
}

/**
 * Steam leak survey calculations using estimate, orifice, and plume methods.
 */
export declare class SteamLeakSurvey {
    /**
     * Constructor for SteamLeakSurvey, when utility type is steam
     * @param operatingTime double, operating time of the system, units hr/year
     * @param steamTemp double, steam temperature, units degF (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature, units degF
     * @param feedwaterTemp double, feedwater temperature, units degF (must be below boiling point of water, max 212F)
     * @param steamCost double, $/lb
     */
    constructor(
        operatingTime: number,
        steamTemp: number,
        steamPressure: number,
        costOfElectricity: number,
        leakPressure: number,
        leakTemp: number,
        feedwaterTemp: number,
        steamCost: number
    );

    /**
     * Constructor for SteamLeakSurvey, when utility type is electric
     * @param operatingTime double, operating time of the system, units hr/year
     * @param steamTemp double, steam temperature, units degF (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature, units degF
     * @param feedwaterTemp double, feedwater temperature, units degF (must be below boiling point of water, max 212F)
     * @param boilerEfficiency Boiler efficiency, units %.
     * @param systemEfficiency System efficiency, units %.
     */
    constructor(
        operatingTime: number,
        steamTemp: number,
        steamPressure: number,
        costOfElectricity: number,
        leakPressure: number,
        leakTemp: number,
        feedwaterTemp: number,
        boilerEfficiency: number,
        systemEfficiency: number
    );

    /**
     * Constructor for SteamLeakSurvey, when utility type is natural gas
     * @param operatingTime double, operating time of the system, units hr/year
     * @param steamTemp double, steam temperature, units degF (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature, units degF
     * @param feedwaterTemp double, feedwater temperature, units degF (must be below boiling point of water, max 212F)
     * @param boilerEfficiency Boiler efficiency, units %.
     * @param systemEfficiency System efficiency, units %.
     * @param fuelCost double, per MCF (unit cost of fuel for the boiler system), when utility type Natural Gas
     * @param fuelEnergyFactor double, MMBtu/MCF (energy content for a given volume of fuel, when unit is in $/volume)
     */
    constructor(
        operatingTime: number,
        steamTemp: number,
        steamPressure: number,
        costOfElectricity: number,
        leakPressure: number,
        leakTemp: number,
        feedwaterTemp: number,
        boilerEfficiency: number,
        systemEfficiency: number,
        fuelCost: number,
        fuelEnergyFactor: number
    );

    /**
     * Constructor for SteamLeakSurvey, generic
     * @param operatingTime double, operating time of the system, units hr/year
     * @param steamTemp double, steam temperature, units degF (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature, units degF
     * @param feedwaterTemp double, feedwater temperature, units degF (must be below boiling point of water, max 212F)
     * @param boilerEfficiency Boiler efficiency, units %.
     * @param systemEfficiency System efficiency, units %.
     * @param utilityType utility type enumeration
     * @param fuelCost double, per MCF (unit cost of fuel for the boiler system), when utility type Natural Gas
     * @param fuelEnergyFactor double, MMBtu/MCF (energy content for a given volume of fuel, when unit is in $/volume)
     * @param steamCost double, $/lb
     */
    constructor(
        operatingTime: number,
        steamTemp: number,
        steamPressure: number,
        costOfElectricity: number,
        leakPressure: number,
        leakTemp: number,
        feedwaterTemp: number,
        boilerEfficiency: number,
        systemEfficiency: number,
        utilityType: UtilityType,
        fuelCost: number,
        fuelEnergyFactor: number,
        steamCost: number
    );

    /**
     * Calculate steam cost based on utility type.
     *
     * @returns Steam cost computed from the configured utility type, units $/lb.
     */
    costOfSteam(): number;

    /**
     * Calculate steam cost based on utility type and turbine efficiency.
     *
     * @param turbineEfficiency Turbine efficiency, units %.
     * @returns Steam cost computed from the configured utility type and turbine efficiency, units $/lb.
     */
    costOfSteam(turbineEfficiency: number): number;

    /**
     * Calculate steam leak losses using an estimated leak rate.
     *
     * @param leakRate double, lb/hr
     * @returns {@link SteamLeakSurveyResults}
     */
    estimateMethodPRVCalc(leakRate: number): SteamLeakSurveyResults;

    /**
     * Calculate steam leak losses using an estimated leak rate and turbine efficiency.
     *
     * @param turbineEfficiency Turbine efficiency, units %.
     * @param leakRate double, lb/hr
     * @returns {@link SteamLeakSurveyResults}
     */
    estimateMethodTurbineCalc(turbineEfficiency: number, leakRate: number): SteamLeakSurveyResults;

    /**
     * Calculate steam leak losses using the orifice method.
     *
     * @param turbineEfficiency Turbine efficiency, units %.
     * @param holeSize double, estimated diameter of orifice through which steam is leaking in inches
     * @param dischargeCoef double, discharge coefficient used to capture the effect of the shape of the leak rate as fraction (0 - 1)
     * @param atmPressure double, atmospheric pressure (standard pressure is 14.7 psia, range 0 - 20)
     * @returns {@link SteamLeakSurveyResults}
     */
    orificeMethodCalc(
        turbineEfficiency: number,
        holeSize: number,
        dischargeCoef: number,
        atmPressure: number
    ): SteamLeakSurveyResults;

    /**
     * Calculate steam leak losses using the plume-length method.
     *
     * @param turbineEfficiency Turbine efficiency, units %.
     * @param plumeLength double, units ft (range 3 - 12 ft)
     * @param ambTemp double, ambient temperature, units degF (usually between 45 and 90 degF)
     * @returns {@link SteamLeakSurveyResults}
     */
    plumeMethodCalc(turbineEfficiency: number, plumeLength: number, ambTemp: number): SteamLeakSurveyResults;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type SteamLeakSurveyModule = {
    UtilityType: typeof UtilityType;
    SteamLeakSurveyResults: typeof SteamLeakSurveyResults;
    QuantifySteamLeakByPlumeLength: typeof QuantifySteamLeakByPlumeLength;
    SteamLeakSurvey: typeof SteamLeakSurvey;
};
