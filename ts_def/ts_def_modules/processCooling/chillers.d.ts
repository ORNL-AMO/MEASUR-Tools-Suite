/**
 * Consumption (Water / Power / Energy) & Savings calculators for
 * Cooling Tower (Makeup Water, Basin Heater Energy, Fan Energy) and
 * Chiller Efficiency (Temperature Reset Capacity, Staging).
 */

import type { DoubleVector } from '../binding/registered_vectors';

// ---------------------------------------------------------------------------
// Enumerations
// ---------------------------------------------------------------------------

/**
 * Fan control speed type for cooling tower fan energy calculations.
 */
export enum FanControlSpeedType {
    One = 0,
    Two = 1,
    Variable = 2,
}

/**
 * Chiller compressor type.
 */
export enum ChillerType {
    Centrifugal = 0,
    Screw = 1,
}

/**
 * Condenser cooling medium type.
 */
export enum CondenserCoolingType {
    Water = 0,
    Air = 1,
}

/**
 * Compressor configuration type.
 */
export enum CompressorConfigType {
    NoVFD = 0,
    VFD = 1,
    MagneticBearing = 2,
}

// ---------------------------------------------------------------------------
// Output interfaces
// ---------------------------------------------------------------------------

/**
 * Result object returned by {@link CoolingTowerMakeupWaterCalculator.calculate}.
 *
 * @property wcBaseline double, water consumption before modifications, units gallons
 * @property wcModification double, water consumption after modifications, units gallons
 * @property waterSavings double, water saved, units gallons
 */
export interface CoolingTowerMakeupWaterCalculatorOutput {
    /** Water consumption before modifications, units gallons */
    wcBaseline: number;
    /** Water consumption after modifications, units gallons */
    wcModification: number;
    /** Water saved, units gallons */
    waterSavings: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link BasinHeaterEnergyConsumption} and
 * {@link FanEnergyConsumption}.
 *
 * @property baselinePower double, units kW (fan: HP)
 * @property baselineEnergy double, units kWh
 * @property modPower double, units kW (fan: HP)
 * @property modEnergy double, units kWh
 * @property savingsEnergy double, units kWh
 */
export interface PowerEnergyConsumptionOutput {
    /** Baseline power, units kW (fan: HP) */
    baselinePower: number;
    /** Baseline energy, units kWh */
    baselineEnergy: number;
    /** Modification power, units kW (fan: HP) */
    modPower: number;
    /** Modification energy, units kWh */
    modEnergy: number;
    /** Energy savings, units kWh */
    savingsEnergy: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link ChillerStagingEfficiency}.
 *
 * @property baselinePowerList list of power consumption values for each baseline chiller load, units kW
 * @property modPowerList list of power consumption values for each modification chiller load, units kW
 * @property baselineTotalPower double, units kW
 * @property baselineTotalEnergy double, units kWh
 * @property modTotalPower double, units kW
 * @property modTotalEnergy double, units kWh
 * @property savingsEnergy double, units kWh
 */
export interface StagingPowerConsumptionOutput {
    /**
     * Registered WASM vector of baseline chiller power values, units kW.
     * Call `delete()` when finished.
     */
    baselinePowerList: DoubleVector;
    /**
     * Registered WASM vector of modification chiller power values, units kW.
     * Call `delete()` when finished.
     */
    modPowerList: DoubleVector;
    /** Total baseline power, units kW */
    baselineTotalPower: number;
    /** Total baseline energy, units kWh */
    baselineTotalEnergy: number;
    /** Total modification power, units kW */
    modTotalPower: number;
    /** Total modification energy, units kWh */
    modTotalEnergy: number;
    /** Energy savings, units kWh */
    savingsEnergy: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link ChillerCapacityEfficiency}.
 *
 * @property baselineActualCapacity double, units ton
 * @property baselineActualEfficiency double, units kW/ton
 * @property baselinePower double, units kW
 * @property baselineEnergy double, units kWh
 * @property modActualCapacity double, units ton
 * @property modActualEfficiency double, units kW/ton
 * @property modPower double, units kW
 * @property modEnergy double, units kWh
 * @property savingsEnergy double, units kWh
 */
export interface CapacityPowerEnergyConsumptionOutput {
    /** Baseline actual capacity, units ton */
    baselineActualCapacity: number;
    /** Baseline actual efficiency, units kW/ton */
    baselineActualEfficiency: number;
    /** Baseline power, units kW */
    baselinePower: number;
    /** Baseline energy, units kWh */
    baselineEnergy: number;
    /** Modification actual capacity, units ton */
    modActualCapacity: number;
    /** Modification actual efficiency, units kW/ton */
    modActualEfficiency: number;
    /** Modification power, units kW */
    modPower: number;
    /** Modification energy, units kWh */
    modEnergy: number;
    /** Energy savings, units kWh */
    savingsEnergy: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Input data classes
// ---------------------------------------------------------------------------

/**
 * Operating conditions data for a cooling tower.
 */
export declare class CoolingTowerOperatingConditionsData {
    /**
     * @param flowRate double, water flow rate, units gpm
     * @param coolingLoad double, cooling load, units MMBtu/h
     * @param operationalHours int, number of hours the cooling tower operates
     * @param lossCorrectionFactor Correction factor for evaporation loss, dimensionless.
     */
    constructor(
        flowRate: number,
        coolingLoad: number,
        operationalHours: number,
        lossCorrectionFactor: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Water conservation data for a cooling tower (baseline or modification).
 */
export declare class CoolingTowerWaterConservationData {
    /**
     * @param cyclesOfConcentration int, cycles of concentration
     * @param driftLossFactor Correction factor for drift loss, dimensionless.
     */
    constructor(cyclesOfConcentration: number, driftLossFactor: number);

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Calculators
// ---------------------------------------------------------------------------

/**
 * Calculates cooling tower makeup water consumption and savings.
 */
export declare class CoolingTowerMakeupWaterCalculator {
    /**
     * @param operatingConditionsData Operating conditions for the cooling tower
     * @param waterConservationBaselineData Baseline water conservation data
     * @param waterConservationModificationData Modification water conservation data
     */
    constructor(
        operatingConditionsData: CoolingTowerOperatingConditionsData,
        waterConservationBaselineData: CoolingTowerWaterConservationData,
        waterConservationModificationData: CoolingTowerWaterConservationData
    );

    /**
     * Calculate cooling tower makeup water consumption and savings.
     *
     * @returns {@link CoolingTowerMakeupWaterCalculatorOutput}
     */
    calculate(): CoolingTowerMakeupWaterCalculatorOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Free functions
// ---------------------------------------------------------------------------

/**
 * Calculates basin heater power and energy consumption for a cooling tower.
 *
 * @param ratedCapacity double, rated capacity, units ton
 * @param ratedTempSetPoint double, rated temperature set point, units F
 * @param ratedTempDryBulb double, rated dry-bulb temperature, units F
 * @param ratedWindSpeed double, rated wind speed, units mph
 * @param operatingTempDryBulb double, operating dry-bulb temperature, units F
 * @param operatingWindSpeed double, operating wind speed, units mph
 * @param operatingHours double, operating hours, units hours
 * @param baselineTempSetPoint double, baseline temperature set point, units F
 * @param modTempSetPoint double, modification temperature set point, units F
 * @param panLossRatio double, pan loss ratio, fraction
 * @returns {@link PowerEnergyConsumptionOutput}
 */
export function BasinHeaterEnergyConsumption(
    ratedCapacity: number,
    ratedTempSetPoint: number,
    ratedTempDryBulb: number,
    ratedWindSpeed: number,
    operatingTempDryBulb: number,
    operatingWindSpeed: number,
    operatingHours: number,
    baselineTempSetPoint: number,
    modTempSetPoint: number,
    panLossRatio: number
): PowerEnergyConsumptionOutput;

/**
 * Calculates cooling tower fan power and energy consumption.
 *
 * @param ratedFanPower double, rated fan power, units HP
 * @param waterLeavingTemp double, water leaving temperature, units F
 * @param waterEnteringTemp double, water entering temperature, units F
 * @param operatingTempWetBulb double, operating wet-bulb temperature, units F
 * @param operatingHours double, operating hours, units hours
 * @param baselineSpeedType {@link FanControlSpeedType} baseline fan speed control type
 * @param modSpeedType {@link FanControlSpeedType} modification fan speed control type
 * @returns {@link PowerEnergyConsumptionOutput}
 */
export function FanEnergyConsumption(
    ratedFanPower: number,
    waterLeavingTemp: number,
    waterEnteringTemp: number,
    operatingTempWetBulb: number,
    operatingHours: number,
    baselineSpeedType: FanControlSpeedType,
    modSpeedType: FanControlSpeedType
): PowerEnergyConsumptionOutput;

/**
 * Calculates chiller capacity and efficiency with temperature reset.
 *
 * @param chillerType {@link ChillerType} enum - Centrifugal or Screw
 * @param condenserCoolingType {@link CondenserCoolingType} enum - Water or Air
 * @param compressorConfigType {@link CompressorConfigType} enum - NoVFD, VFD, or MagneticBearing
 * @param ariCapacity double, ARI rated capacity, units ton
 * @param ariEfficiency double, ARI rated efficiency, units kW/ton
 * @param maxCapacityRatio double, maximum capacity ratio (unitless)
 * @param operatingHours double, operating hours, units hours
 * @param waterFlowRate double, chilled water flow rate, units GPM
 * @param waterDeltaT double, chilled water temperature difference, units F
 * @param baselineWaterSupplyTemp double, baseline chilled water supply temperature, units F
 * @param baselineWaterEnteringTemp double, baseline condenser water entering temperature, units F
 * @param modWaterSupplyTemp double, modification chilled water supply temperature, units F
 * @param modWaterEnteringTemp double, modification condenser water entering temperature, units F
 * @returns {@link CapacityPowerEnergyConsumptionOutput}
 */
export function ChillerCapacityEfficiency(
    chillerType: ChillerType,
    condenserCoolingType: CondenserCoolingType,
    compressorConfigType: CompressorConfigType,
    ariCapacity: number,
    ariEfficiency: number,
    maxCapacityRatio: number,
    operatingHours: number,
    waterFlowRate: number,
    waterDeltaT: number,
    baselineWaterSupplyTemp: number,
    baselineWaterEnteringTemp: number,
    modWaterSupplyTemp: number,
    modWaterEnteringTemp: number
): CapacityPowerEnergyConsumptionOutput;

/**
 * Calculates chiller staging power and energy consumption.
 *
 * @param chillerType {@link ChillerType} enum - Centrifugal or Screw
 * @param condenserCoolingType {@link CondenserCoolingType} enum - Water or Air
 * @param compressorConfigType {@link CompressorConfigType} enum - NoVFD, VFD, or MagneticBearing
 * @param ariCapacity double, ARI rated capacity, units ton
 * @param ariEfficiency double, ARI rated efficiency, units kW/ton
 * @param maxCapacityRatio double, maximum capacity ratio (unitless)
 * @param operatingHours double, operating hours, units hours
 * @param waterSupplyTemp double, chilled water supply temperature, units F
 * @param waterEnteringTemp double, condenser water entering temperature, units F
 * @param baselineLoadList Registered WASM vector of baseline chiller loads, units ton
 * @param modLoadList Registered WASM vector of modification chiller loads, units ton
 * @returns {@link StagingPowerConsumptionOutput}
 */
export function ChillerStagingEfficiency(
    chillerType: ChillerType,
    condenserCoolingType: CondenserCoolingType,
    compressorConfigType: CompressorConfigType,
    ariCapacity: number,
    ariEfficiency: number,
    maxCapacityRatio: number,
    operatingHours: number,
    waterSupplyTemp: number,
    waterEnteringTemp: number,
    baselineLoadList: DoubleVector,
    modLoadList: DoubleVector
): StagingPowerConsumptionOutput;

export type ChillersModule = {
    FanControlSpeedType: typeof FanControlSpeedType;
    ChillerType: typeof ChillerType;
    CondenserCoolingType: typeof CondenserCoolingType;
    CompressorConfigType: typeof CompressorConfigType;
    CoolingTowerMakeupWaterCalculatorOutput: CoolingTowerMakeupWaterCalculatorOutput;
    PowerEnergyConsumptionOutput: PowerEnergyConsumptionOutput;
    StagingPowerConsumptionOutput: StagingPowerConsumptionOutput;
    CapacityPowerEnergyConsumptionOutput: CapacityPowerEnergyConsumptionOutput;
    CoolingTowerOperatingConditionsData: typeof CoolingTowerOperatingConditionsData;
    CoolingTowerWaterConservationData: typeof CoolingTowerWaterConservationData;
    CoolingTowerMakeupWaterCalculator: typeof CoolingTowerMakeupWaterCalculator;
    BasinHeaterEnergyConsumption: typeof BasinHeaterEnergyConsumption;
    FanEnergyConsumption: typeof FanEnergyConsumption;
    ChillerCapacityEfficiency: typeof ChillerCapacityEfficiency;
    ChillerStagingEfficiency: typeof ChillerStagingEfficiency;
};
