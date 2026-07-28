/**
 * Water Assessment calculations.
 *
 * Calculates process water use, cooling tower losses, boiler water losses,
 * kitchen and restroom gross water use, landscaping gross water use,
 * heat energy in discharge, and added motor energy use.
 */

/**
 * Result object returned by {@link WaterAssessment.calculateProcessWaterUse}.
 *
 * @property recirculatedWater Recirculated water flow, units gal/year.
 * @property incomingWater Incoming water flow, units gal/year.
 * @property wasteDischargedAndRecycledOther Waste discharged and recycled from other sources, units gal/year.
 */
export interface ProcessWaterUseOutput {
    /** Recirculated water flow, units gal/year. */
    recirculatedWater: number;
    /** Incoming water flow, units gal/year. */
    incomingWater: number;
    /** Waste discharged and recycled from other sources, units gal/year. */
    wasteDischargedAndRecycledOther: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link WaterAssessment.calculateCoolingTowerLoss}.
 *
 * @property grossWaterUse Gross water use, units gal/year.
 * @property evaporationLoss Evaporation loss, units gal/year.
 * @property cycleOfConcentration Cycle of concentration, dimensionless.
 * @property makeupWater Makeup water, units gal/year.
 * @property blowdownLoss Blowdown loss, units gal/year.
 */
export interface CoolingTowerLossOutput {
    /** Gross water use, units gal/year. */
    grossWaterUse: number;
    /** Evaporation loss, units gal/year. */
    evaporationLoss: number;
    /** Cycle of concentration, dimensionless. */
    cycleOfConcentration: number;
    /** Makeup water, units gal/year. */
    makeupWater: number;
    /** Blowdown loss, units gal/year. */
    blowdownLoss: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link WaterAssessment.calculateBoilerWaterLosses}.
 *
 * @property cycleOfConcentration Cycle of concentration, dimensionless.
 * @property grossWaterUse Gross water use, units gal/year.
 * @property makeupWater Makeup water, units gal/year.
 * @property steamLoss Steam loss, units gal/year.
 * @property blowdownLoss Blowdown loss, units gal/year.
 * @property condensateReturn Condensate return, units gal/year.
 * @property rateOfRecirculation Rate of recirculation, dimensionless.
 */
export interface BoilerWaterLossOutput {
    /** Cycle of concentration, dimensionless. */
    cycleOfConcentration: number;
    /** Gross water use, units gal/year. */
    grossWaterUse: number;
    /** Makeup water, units gal/year. */
    makeupWater: number;
    /** Steam loss, units gal/year. */
    steamLoss: number;
    /** Blowdown loss, units gal/year. */
    blowdownLoss: number;
    /** Condensate return, units gal/year. */
    condensateReturn: number;
    /** Rate of recirculation, dimensionless. */
    rateOfRecirculation: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Water assessment calculator.
 */
export declare class WaterAssessment {
    /** Default constructor - no arguments required. */
    constructor();

    /**
     * Calculate process water use.
     *
     * @param waterRequired Water required by the process, units gal/year.
     * @param waterConsumed Water consumed by the process, units gal/year.
     * @param waterLoss Water lost from the process, units gal/year.
     * @param fractionGrossWaterRecirculated Gross water recirculated, dimensionless fraction.
     * @returns {@link ProcessWaterUseOutput}
     */
    calculateProcessWaterUse(
        waterRequired: number,
        waterConsumed: number,
        waterLoss: number,
        fractionGrossWaterRecirculated: number
    ): ProcessWaterUseOutput;

    /**
     * Calculate cooling tower losses.
     *
     * @param hoursPerYear Annual operating hours, units hr/year.
     * @param tonnage Cooling tower load, units refrigeration ton.
     * @param loadFactor Cooling load factor, dimensionless fraction.
     * @param evaporationRateDegree Evaporation rate per degree, dimensionless fraction/degF.
     * @param temperatureDrop Cooling tower temperature drop, units degF.
     * @param makeupConductivity Makeup water conductivity, units match blowdownConductivity.
     * @param blowdownConductivity Blowdown water conductivity, units match makeupConductivity.
     * @returns {@link CoolingTowerLossOutput}
     */
    calculateCoolingTowerLoss(
        hoursPerYear: number,
        tonnage: number,
        loadFactor: number,
        evaporationRateDegree: number,
        temperatureDrop: number,
        makeupConductivity: number,
        blowdownConductivity: number
    ): CoolingTowerLossOutput;

    /**
     * Calculate boiler water losses.
     *
     * @param hoursPerYear Annual operating hours, units hr/year.
     * @param power Boiler power, units hp.
     * @param loadFactor Boiler load factor, dimensionless fraction.
     * @param steamPerPower Steam generation rate per power, units lb/(hp.hr).
     * @param feedWaterConductivity Feedwater conductivity, units match makeupConductivity.
     * @param makeupConductivity Makeup water conductivity, units match blowdownConductivity.
     * @param blowdownConductivity Blowdown water conductivity, units match makeupConductivity.
     * @returns {@link BoilerWaterLossOutput}
     */
    calculateBoilerWaterLosses(
        hoursPerYear: number,
        power: number,
        loadFactor: number,
        steamPerPower: number,
        feedWaterConductivity: number,
        makeupConductivity: number,
        blowdownConductivity: number
    ): BoilerWaterLossOutput;

    /**
     * Calculate gross kitchen and restroom water use.
     *
     * @param employeeCount Employee count.
     * @param workdaysPerYear Workdays per year, units days/year.
     * @param dailyUsePerEmployee Daily water use per employee, units gal/day.
     * @returns Gross water use, units gal/year.
     */
    calculateKitchenRestroomGrossWaterUse(
        employeeCount: number,
        workdaysPerYear: number,
        dailyUsePerEmployee: number
    ): number;

    /**
     * Calculate gross landscaping water use.
     *
     * @param areaIrrigated Irrigated area, units acres.
     * @param yearlyInchesIrrigated Annual irrigation depth, units in/year.
     * @returns Gross water use, units gal/year.
     */
    calculateLandscapingGrossWaterUse(
        areaIrrigated: number,
        yearlyInchesIrrigated: number
    ): number;

    /**
     * Calculate heat energy in wastewater discharge.
     *
     * @param incomingTemp Incoming water temperature, units degF.
     * @param outgoingTemp Outgoing water temperature, units degF.
     * @param heatingEfficiency Heating efficiency, dimensionless fraction.
     * @param wasteWaterDischarge Wastewater discharge, units gal/year.
     * @returns Heat energy use in discharge, units MMBtu/year.
     */
    calculateHeatEnergyInDischarge(
        incomingTemp: number,
        outgoingTemp: number,
        heatingEfficiency: number,
        wasteWaterDischarge: number
    ): number;

    /**
     * Calculate added motor energy use.
     *
     * @param numberUnits Equipment count.
     * @param hoursPerYear Annual operating hours, units hr/year.
     * @param ratedPower Rated motor power, units kW.
     * @param loadFactor Motor load factor, dimensionless fraction.
     * @param systemEfficiency System efficiency, dimensionless fraction.
     * @returns Energy use, units kWh/year.
     */
    calculateAddedMotorEnergyUse(
        numberUnits: number,
        hoursPerYear: number,
        ratedPower: number,
        loadFactor: number,
        systemEfficiency: number
    ): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type WaterAssessmentModule = {
    ProcessWaterUseOutput: ProcessWaterUseOutput;
    CoolingTowerLossOutput: CoolingTowerLossOutput;
    BoilerWaterLossOutput: BoilerWaterLossOutput;
    WaterAssessment: typeof WaterAssessment;
};
