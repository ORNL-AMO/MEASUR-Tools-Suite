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
 * @brief Input struct for DryerOperatingCost
 *
 * @var flowRate double, Flow Rate in SCFM (1 - 50,000 SCFM)
 *
 * @var pressure double, Pressure in psig (25 - 150 psig)
 *
 * @var temperature double, Temperature F (50 - 120 F)
 *
 * @var operatingHoursPerDay double, Hours for which the dryer operates per day - hours (1 - 24 hours)
 *
 * @var operatingDaysPerWeek double, Days for which the dryer operates per week - days ( 1 - 7 days)
 *
 * @var operatingWeeksPerYear double, Weeks for which the dryer operates per year - weeks (1 - 52 weeks)
 *
 * @var costOfElectricity double, Cost of electricity per kWh - $ ($0.01 - $0.20 per kWh)
 *
 * @var costOfCompressedAir double, Cost of compressed air per 1000 SCF - $ ($0.20 - $0.50 per 1000 SCF)
 *
 * @var costOfCoolingWater double, Cost of cooling water per 1000 gallons - $ ($0.25 - $10.00 per 1000 gallons)
 *
 * @var heaterPower double, Heater power rating in kW (0 - 1000 kW).
 *
 *          If heater power is not known or needs to be computed set it to 0.
 *
 *          Heater power is required for Heated Externally, Blower Purge With Sweep, Blower Purge Without Sweep and Heat of Compression - HC dryers.
 *
 * @var heatingHoursPerDay double, Hours for which the dryer heater operates per day - hours (0 - 24 hours)
 *
 *          If heating hours per day is not known or needs to be calculated default set it to 0.
 *
 *          Calculator default for heating hours per day is
 *
 *          18 hours for Heated Externally, Blower Purge With Sweep and Blower Purge Without Sweep dryers, and
 *
 *          3 hours for Heat of Compression - HC dryer.
 *
 * @var purgeRate double, Purge rate for the dryer - percentage (0 - 100%)
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
 * @var designDDCPercentage double, Design DDC percentage for the dryer - percentage (0 - 100%)
 *
 *          If design DDC percentage is not known or needs to be calculated default set it to 0.
 *
 *          Calculator default for design DDC percentage is 16.33% for desiccant dryers.
 *
 */
export interface DryerOperatingCostInput {
    flowRate: number;
    pressure: number;
    temperature: number;
    operatingHoursPerDay: number;
    operatingDaysPerWeek: number;
    operatingWeeksPerYear: number;
    costOfElectricity: number;
    costOfCompressedAir: number;
    costOfCoolingWater: number;
    heaterPower: number;
    heatingHoursPerDay: number;
    purgeRate: number;
    designDDCPercentage: number;
}

/**
 * @brief Output struct for DryerOperatingCost
 *
 * @var waterRemoved double, flow rate of water removed by the dryer in pounds per hour (PPH)
 *
 * @var totalCostPerYear double, Total cost of operation of the dryer per year in $
 *
 * @var heaterPower double, Heater power rating in kW (0 - 1000 kW)
 *
 * @var heatingHoursPerDay double, Hours for which the dryer heater operates per day - hours (1 - 24 hours)
 *
 * @var purgeRate double, Purge rate for the dryer - percentage (0 - 100%)
 *
 * @var designDDCPercentage double, Design DDC percentage for the dryer - percentage (0 - 100%)
 *
 */

export interface DryerOperatingCostOutput {
    waterRemoved: number;
    totalCostPerYear: number;
    heaterPower: number;
    heatingHoursPerDay: number;
    purgeRate: number;
    designDDCPercentage: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Calculates annual operating cost for supported desiccant and refrigerated dryers. */
export class DryerOperatingCost {
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
     * @param temperature double, Temperature F (50 - 120 F)
     * @param operatingHoursPerDay double, Hours for which the dryer operates per day - hours (1 - 24 hours)
     * @param operatingDaysPerWeek double, Days for which the dryer operates per week - days (1 - 7 days)
     * @param operatingWeeksPerYear double, Weeks for which the dryer operates per year - weeks (1 - 52 weeks)
     * @param costOfElectricity double, Cost of electricity per kWh - $ ($0.01 - $0.20 per kWh)
     * @param costOfCompressedAir double, Cost of compressed air per 1000 SCF - $ ($0.20 - $0.50 per 1000 SCF)
     * @param costOfCoolingWater double, Cost of cooling water per 1000 gallons - $ ($0.25 - $10.00 per 1000 gallons)
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
     * @param temperature double, Temperature F (50 - 120 F)
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
     * @param costOfCoolingWater double, Cost of cooling water per 1000 gallons - $ ($0.25 - $10.00 per 1000 gallons)
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
     * @param purgeRate double, Purge rate for the dryer - percentage (0 - 100%)
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
     * @param designDDCPercentage double, Design DDC percentage for the dryer - percentage (0 - 100%)
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
     * @return DryerOperatingCostOutput
     *
     */
    calculate(dryerType: DryerType): DryerOperatingCostOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Factory function to load the Dryer Operating Cost WASM bindings. */
export default function DryerOperatingCostModule(): Promise<{
    DryerType: typeof DryerType;
    DryerOperatingCost: typeof DryerOperatingCost;
}>;

