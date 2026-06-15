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
 * @property recirculatedWater double
 * @property incomingWater double
 * @property wasteDischargedAndRecycledOther double
 */
export interface ProcessWaterUseOutput {
    /** Recirculated water flow */
    recirculatedWater: number;
    /** Incoming water flow */
    incomingWater: number;
    /** Waste discharged and recycled from other sources */
    wasteDischargedAndRecycledOther: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link WaterAssessment.calculateCoolingTowerLoss}.
 *
 * @property grossWaterUse double
 * @property evaporationLoss double
 * @property cycleOfConcentration double
 * @property makeupWater double
 * @property blowdownLoss double
 */
export interface CoolingTowerLossOutput {
    /** Gross water use */
    grossWaterUse: number;
    /** Evaporation loss */
    evaporationLoss: number;
    /** Cycle of concentration */
    cycleOfConcentration: number;
    /** Makeup water */
    makeupWater: number;
    /** Blowdown loss */
    blowdownLoss: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link WaterAssessment.calculateBoilerWaterLosses}.
 *
 * @property cycleOfConcentration double
 * @property grossWaterUse double
 * @property makeupWater double
 * @property steamLoss double
 * @property blowdownLoss double
 * @property condensateReturn double
 * @property rateOfRecirculation double
 */
export interface BoilerWaterLossOutput {
    /** Cycle of concentration */
    cycleOfConcentration: number;
    /** Gross water use */
    grossWaterUse: number;
    /** Makeup water */
    makeupWater: number;
    /** Steam loss */
    steamLoss: number;
    /** Blowdown loss */
    blowdownLoss: number;
    /** Condensate return */
    condensateReturn: number;
    /** Rate of recirculation */
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
     * @param waterRequired double
     * @param waterConsumed double
     * @param waterLoss double
     * @param fractionGrossWaterRecirculated double
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
     * @param hoursPerYear double
     * @param tonnage double
     * @param loadFactor double
     * @param evaporationRateDegree double
     * @param temperatureDrop double
     * @param makeupConductivity double
     * @param blowdownConductivity double
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
     * @param hoursPerYear double
     * @param power double
     * @param loadFactor double
     * @param steamPerPower double
     * @param feedWaterConductivity double
     * @param makeupConductivity double
     * @param blowdownConductivity double
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
     * @param employeeCount double
     * @param workdaysPerYear double
     * @param dailyUsePerEmployee double
     * @returns grossWaterUse double
     */
    calculateKitchenRestroomGrossWaterUse(
        employeeCount: number,
        workdaysPerYear: number,
        dailyUsePerEmployee: number
    ): number;

    /**
     * Calculate gross landscaping water use.
     *
     * @param areaIrrigated double
     * @param yearlyInchesIrrigated double
     * @returns grossWaterUse double
     */
    calculateLandscapingGrossWaterUse(
        areaIrrigated: number,
        yearlyInchesIrrigated: number
    ): number;

    /**
     * Calculate heat energy in wastewater discharge.
     *
     * @param incomingTemp double
     * @param outgoingTemp double
     * @param heatingEfficiency double
     * @param wasteWaterDischarge double
     * @returns heatEnergyUseInDischarge double
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
     * @param numberUnits double
     * @param hoursPerYear double
     * @param ratedPower double
     * @param loadFactor double
     * @param systemEfficiency double
     * @returns energyUse double
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
