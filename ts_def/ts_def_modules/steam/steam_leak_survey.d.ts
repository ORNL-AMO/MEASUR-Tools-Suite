/**
 * @brief Utility type used to compute steam cost.
 */
export enum UtilityType {
    steam = 0,
    electric = 1,
    natural_gas = 2
}

/**
 * @brief Result struct for steam leak calculations.
 *
 * @var leakRate double, leak rate in lb/hr
 *
 * @var steamLoss double, steam loss in klb/yr
 *
 * @var energyLoss double, energy loss in MMBtu/yr
 *
 * @var leakCost double, annual leak cost
 */
export interface SteamLeakSurveyResults {
    leakRate: number;
    steamLoss: number;
    energyLoss: number;
    leakCost: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Implements plume-based steam leak-rate estimation, based on DOE's Quantify and Eliminate Steam Leaks. */
export class QuantifySteamLeakByPlumeLength {
    /**
     * @param steamPressure double, steam pressure in psig
     * @param plumeLength double, visible plume length in feet
     * @param ambTemp double, ambient temperature in F
     */
    static estimate(steamPressure: number, plumeLength: number, ambTemp: number): number;
}

/**
 * @brief Steam leak survey calculations using estimate, orifice, and plume methods.
 */
export class SteamLeakSurvey {
    /**
     * Constructor for SteamLeakSurvey, when utility type is steam
     * @param operatingTime double, operating time of the system hours per year
     * @param steamTemp double, steam temperature F (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature F
     * @param feedwaterTemp double, feedwater temperature in F (must be below boiling point of water, max 212F)
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
     * @param operatingTime double, operating time of the system hours per year
     * @param steamTemp double, steam temperature F (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature F
     * @param feedwaterTemp double, feedwater temperature in F (must be below boiling point of water, max 212F)
     * @param boilerEfficiency double, boiler efficiency percentage (0 - 100 %)
     * @param systemEfficiency double, system efficiency percentage (0 - 100 %)
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
     * @param operatingTime double, operating time of the system hours per year
     * @param steamTemp double, steam temperature F (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature F
     * @param feedwaterTemp double, feedwater temperature in F (must be below boiling point of water, max 212F)
     * @param boilerEfficiency double, boiler efficiency percentage (1 - 100 %)
     * @param systemEfficiency double, system efficiency percentage (1 - 100 %)
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
     * @param operatingTime double, operating time of the system hours per year
     * @param steamTemp double, steam temperature F (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature F
     * @param feedwaterTemp double, feedwater temperature in F (must be below boiling point of water, max 212F)
     * @param boilerEfficiency double, boiler efficiency percentage (0 - 100 %)
     * @param systemEfficiency double, system efficiency percentage (0 - 100 %)
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
     * @return steamCost computed based on fuel type steam or electric or natural gas
     */
    costOfSteam(): number;

    /**
     * @param turbineEfficiency double, system efficiency percentage (0 - 100 %)
     * @return steamCost computed based on fuel type steam or electric or natural gas and turbine
     */
    costOfSteam(turbineEfficiency: number): number;

    /**
     * @param leakRate double, lb/hr
     * @return SteamLeakSurveyResults
     */
    estimateMethodPRVCalc(leakRate: number): SteamLeakSurveyResults;

    /**
     * @param turbineEfficiency double, system efficiency percentage (0 - 100 %)
     * @param leakRate double, lb/hr
     * @return SteamLeakSurveyResults
     */
    estimateMethodTurbineCalc(turbineEfficiency: number, leakRate: number): SteamLeakSurveyResults;

    /**
     * @param turbineEfficiency double, system efficiency percentage (0 - 100 %)
     * @param holeSize double, estimated diameter of orifice through which steam is leaking in inches
     * @param dischargeCoef double, discharge coefficient used to capture the effect of the shape of the leak rate as fraction (0 - 1)
     * @param atmPressure double, atmospheric pressure (standard pressure is 14.7 psia, range 0 - 20)
     * @return SteamLeakSurveyResults
     */
    orificeMethodCalc(
        turbineEfficiency: number,
        holeSize: number,
        dischargeCoef: number,
        atmPressure: number
    ): SteamLeakSurveyResults;

    /**
     * @param turbineEfficiency double, system efficiency percentage (0 - 100 %)
     * @param plumeLength double, feet (range 3 - 12 feet)
     * @param ambTemp double, ambient temperature (usually between 45 and 90 degrees F)
     * @return SteamLeakSurveyResults
     */
    plumeMethodCalc(turbineEfficiency: number, plumeLength: number, ambTemp: number): SteamLeakSurveyResults;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Factory function to load the Steam Leak Survey. */
export default function SteamLeakSurveyModule(): Promise<{
    UtilityType: typeof UtilityType;
    QuantifySteamLeakByPlumeLength: typeof QuantifySteamLeakByPlumeLength;
    SteamLeakSurvey: typeof SteamLeakSurvey;
}>;

