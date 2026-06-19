/**
 * Dryer Operating Cost
 *
 * Calculates annual operating cost and moisture removal for supported
 * compressed-air dryer types.
 */

/** Enumeration for supported compressed-air dryer types. */
export enum DryerType {
    Heatless = 0,
    HeatedExternally = 1,
    BlowerPurgeWithSweep = 2,
    BlowerPurgeWithoutSweep = 3,
    HeatOfCompressionHC = 4,
    HeatOfCompressionSP = 5,
    Refrigerated = 6
}

/**
 * Input struct for DryerOperatingCost
 *
 * @property flowRate double, Flow Rate in SCFM (1 - 50,000 SCFM)
 *
 * @property pressure double, Pressure in psig (25 - 150 psig)
 *
 * @property temperature double, temperature, units degF (50 - 120 F)
 *
 * @property operatingHoursPerDay double, Hours for which the dryer operates per day - hours (1 - 24 hours)
 *
 * @property operatingDaysPerWeek double, Days for which the dryer operates per week - days ( 1 - 7 days)
 *
 * @property operatingWeeksPerYear double, Weeks for which the dryer operates per year - weeks (1 - 52 weeks)
 *
 * @property costOfElectricity double, Cost of electricity per kWh - $ ($0.01 - $0.20 per kWh)
 *
 * @property costOfCompressedAir double, Cost of compressed air per 1000 SCF - $ ($0.20 - $0.50 per 1000 SCF)
 *
 * @property costOfCoolingWater double, Cost of cooling water per 1000 gallons - $ ($0.25 - $10.00 per 1000 gallons)
 *
 * @property heaterPower double, Heater power rating in kW (0 - 1000 kW).
 *
 *          If heater power is not known or needs to be computed set it to 0.
 *
 *          Heater power is required for Heated Externally, Blower Purge With Sweep, Blower Purge Without Sweep and Heat of Compression - HC dryers.
 *
 * @property heatingHoursPerDay double, Hours for which the dryer heater operates per day - hours (0 - 24 hours)
 *
 *          If heating hours per day is not known or needs to be calculated default set it to 0.
 *
 *          Calculator default for heating hours per day is
 *
 *          18 hours for Heated Externally, Blower Purge With Sweep and Blower Purge Without Sweep dryers, and
 *
 *          3 hours for Heat of Compression - HC dryer.
 *
 * @property purgeRate double, Purge rate for the dryer - percentage (0 - 100%)
 *
 *          If purge rate is not known or needs to be calculated default set it to 0.
 *
 *          Calculator default for purge rate is
 *
 *          15% for Heatless dryer,
 *
 *          7% for Heated Externally, Blower Purge With Sweep and Blower Purge Without Sweep dryers, and
 *
 *          2% for Heat of Compression - HC dryer.
 *
 * @property designDDCPercentage double, Design DDC percentage for the dryer - percentage (0 - 100%)
 *
 *          If design DDC percentage is not known or needs to be calculated default set it to 0.
 *
 *          Calculator default for design DDC percentage is 16.33% for desiccant dryers.
 *
 */
export interface DryerOperatingCostInput {
    /** Flow Rate units scfm (1 - 50,000 SCFM). */
    flowRate: number;
    /** Pressure units psig (25 - 150 psig). */
    pressure: number;
    /** Temperature units degF (50 - 120 degF). */
    temperature: number;
    /** Hours for which the dryer operates per day - hours (1 - 24 hours). */
    operatingHoursPerDay: number;
    /** Days for which the dryer operates per week - days ( 1 - 7 days). */
    operatingDaysPerWeek: number;
    /** Weeks for which the dryer operates per year - weeks (1 - 52 weeks). */
    operatingWeeksPerYear: number;
    /** Cost of electricity units $/kWh ($0.01 - $0.20 per kWh). */
    costOfElectricity: number;
    /** Cost of compressed air units $/1000 scf ($0.20 - $0.50 per 1000 SCF). */
    costOfCompressedAir: number;
    /** Cost of cooling water units $/1000 gal ($0.25 - $10.00 per 1000 gallons). */
    costOfCoolingWater: number;
    /** Heater power rating units kW (0 - 1000 kW). */
    heaterPower: number;
    /** Hours for which the dryer heater operates per day - hours (0 - 24 hours). */
    heatingHoursPerDay: number;
    /** Purge rate for the dryer - dimensionless % (0 - 100%). */
    purgeRate: number;
    /** Design DDC dimensionless % for the dryer - dimensionless % (0 - 100%). */
    designDDCPercentage: number;
}

/**
 * Output struct for DryerOperatingCost
 *
 * @property waterRemoved double, flow rate of water removed by the dryer in pounds per hour (PPH)
 *
 * @property totalCostPerYear double, Total cost of operation of the dryer per year in $
 *
 * @property heaterPower double, Heater power rating in kW (0 - 1000 kW)
 *
 * @property heatingHoursPerDay double, Hours for which the dryer heater operates per day - hours (1 - 24 hours)
 *
 * @property purgeRate double, Purge rate for the dryer - percentage (0 - 100%)
 *
 * @property designDDCPercentage double, Design DDC percentage for the dryer - percentage (0 - 100%)
 *
 */
export declare class DryerOperatingCostOutput {
    private constructor();

    /** flow rate of water removed by the dryer units lb/hr. */
    waterRemoved: number;
    /** Total cost of operation of the dryer per year in $. */
    totalCostPerYear: number;
    /** Heater power rating units kW (0 - 1000 kW). */
    heaterPower: number;
    /** Hours for which the dryer heater operates per day - hours (1 - 24 hours). */
    heatingHoursPerDay: number;
    /** Purge rate for the dryer - dimensionless % (0 - 100%). */
    purgeRate: number;
    /** Design DDC dimensionless % for the dryer - dimensionless % (0 - 100%). */
    designDDCPercentage: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Calculates annual operating cost for supported desiccant and refrigerated dryers. */
export declare class DryerOperatingCost {
    /**
     * Constructor for DryerOperatingCost - Use this constructor when all input parameters are available.
     * @param input Input struct, input parameters for calculation of dryer operating cost including optional parameters
     * that can be calculated within the class if not provided.
     */
    constructor(input: DryerOperatingCostInput);

    /**
     * Constructor for DryerOperatingCost - Use this constructor when heater power rating, heating hours per day, purge rate and design DDC percentage is not known or needs to be computed.
     * @param flowRate double, Flow Rate in SCFM (1 - 50,000 SCFM)
     * @param pressure double, Pressure in psig (25 - 150 psig)
     * @param temperature double, temperature, units degF (50 - 120 F)
     * @param operatingHoursPerDay double, Hours for which the dryer operates per day - hours (1 - 24 hours)
     * @param operatingDaysPerWeek double, Days for which the dryer operates per week - days (1 - 7 days)
     * @param operatingWeeksPerYear double, Weeks for which the dryer operates per year - weeks (1 - 52 weeks)
     * @param costOfElectricity double, Cost of electricity per kWh - $ ($0.01 - $0.20 per kWh)
     * @param costOfCompressedAir double, Cost of compressed air per 1000 SCF - $ ($0.20 - $0.50 per 1000 SCF)
     * @param costOfCoolingWater Cost of cooling water, units $/1000 gal.
     */
    constructor(
        flowRate: number,
        pressure: number,
        temperature: number,
        operatingHoursPerDay: number,
        operatingDaysPerWeek: number,
        operatingWeeksPerYear: number,
        costOfElectricity: number,
        costOfCompressedAir: number,
        costOfCoolingWater: number
    );

    /**
     * Constructor for DryerOperatingCost - Use this constructor when heater power rating, heating hours per day, purge rate and design DDC percentage is known.
     *
     * @param flowRate double, Flow Rate in SCFM (1 - 50,000 SCFM)
     *
     * @param pressure double, Pressure in psig (25 - 150 psig)
     *
     * @param temperature double, temperature, units degF (50 - 120 F)
     *
     * @param operatingHoursPerDay double, Hours for which the dryer operates per day - hours (1 - 24 hours)
     *
     * @param operatingDaysPerWeek double, Days for which the dryer operates per week - days ( 1 - 7 days)
     *
     * @param operatingWeeksPerYear double, Weeks for which the dryer operates per year - weeks (1 - 52 weeks)
     *
     * @param costOfElectricity double, Cost of electricity per kWh - $ ($0.01 - $0.20 per kWh)
     *
     * @param costOfCompressedAir double, Cost of compressed air per 1000 SCF - $ ($0.20 - $0.50 per 1000 SCF)
     *
     * @param costOfCoolingWater Cost of cooling water, units $/1000 gal.
     *
     * @param heaterPower double, Heater power rating in kW (0 - 1000 kW).
     *
     *          If heater power is not known or needs to be computed set it to 0.
     *
     * @param heatingHoursPerDay double, Hours for which the dryer heater operates per day - hours (0 - 24 hours)
     *
     *          If heating hours per day is not known or needs to be calculated default set it to 0.
     *
     *          Calculator default for heating hours per day is
     *
     *          18 hours for Heated Externally, Blower Purge With Sweep and Blower Purge Without Sweep dryers, and
     *
     *          3 hours for Heat of Compression - HC dryer.
     *
     * @param purgeRate Purge rate for the dryer, units %.
     *
     *          If purge rate is not known or needs to be calculated default set it to 0.
     *
     *          Calculator default for purge rate is
     *
     *          15% for Heatless dryer,
     *
     *          7% for Heated Externally, Blower Purge With Sweep and Blower Purge Without Sweep dryers, and
     *
     *          2% for Heat of Compression - HC dryer.
     *
     * @param designDDCPercentage Design DDC percentage for the dryer, units %.
     *
     *          If design DDC percentage is not known or needs to be calculated default set it to 0.
     *
     *          Calculator default for design DDC percentage is 16.33% for desiccant dryers.
     *
     */
    constructor(
        flowRate: number,
        pressure: number,
        temperature: number,
        operatingHoursPerDay: number,
        operatingDaysPerWeek: number,
        operatingWeeksPerYear: number,
        costOfElectricity: number,
        costOfCompressedAir: number,
        costOfCoolingWater: number,
        heaterPower: number,
        heatingHoursPerDay: number,
        purgeRate: number,
        designDDCPercentage: number
    );

    /**
     *
     * @param dryerType DryerType enum, type of dryer for which operating cost is to be calculated
     *
     * @returns DryerOperatingCostOutput
     *
     */
    calculate(dryerType: DryerType): DryerOperatingCostOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type DryerOperatingCostModule = {
    DryerType: typeof DryerType;
    DryerOperatingCost: typeof DryerOperatingCost;
    DryerOperatingCostOutput: typeof DryerOperatingCostOutput;
};
