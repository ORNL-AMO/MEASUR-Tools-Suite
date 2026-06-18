import { ChillerInputV, DoubleVector, DoubleVector2D, IntVector } from "../binding/registered_vectors";

/**
 * Process Fluid Cooling Energy Calculations (CWSAT).
 *
 * Calculator estimates energy consumption of operating Chillers, Pumps and
 * Towers in a cooling system (both air and water-cooled). Supports:
 *  - Multiple and varying capacity/types of Chillers operating together
 *  - Flexible input for operating schedule per Chiller
 *  - Apply changes (improvements / measures) and quantify energy/cost savings
 *  - Upgrades: replace chiller refrigerant, install VSD, use free cooling
 */

// ---------------------------------------------------------------------------
// Enumerations
// ---------------------------------------------------------------------------

/**
 * Refrigerant type used by a chiller.
 */
export enum RefrigerantType {
    R_11 = 0,
    R_123 = 1,
    R_12 = 2,
    R_134a = 3,
    R_22 = 4,
    R_717 = 5,
}

/**
 * Location of the air-cooled condenser air source.
 */
export enum ACSourceLocation {
    Inside = 0,
    Outside = 1,
}

/**
 * Cooling system medium type.
 */
export enum CoolingSystemType {
    Water = 0,
    Air = 1,
}

/**
 * Cooling tower cell fan type.
 */
export enum CellFanType {
    AxialFan = 0,
    CentrifugalFan = 1,
}

/**
 * How the cooling tower is sized.
 */
export enum TowerSizedBy {
    Tonnage = 0,
    Fan_HP = 1,
    Unknown = 2,
}

/**
 * Chiller compressor type.
 */
export enum ChillerCompressorType {
    Centrifugal = 0,
    Screw = 1,
    Reciprocating = 2,
}

/**
 * Fan motor speed control type for the cooling tower.
 */
export enum FanMotorSpeedType {
    One = 0,
    Two = 1,
    Variable = 2,
}

// ---------------------------------------------------------------------------
// Output interfaces
// ---------------------------------------------------------------------------

/**
 * Result object returned by {@link ProcessCooling.calculateChillerEnergy}.
 *
 * All arrays contain values corresponding to 11 % load bins:
 * (0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100).
 *
 * @property efficiency 2-D array, units kW/ton
 * @property hours 2-D array, units hours
 * @property power 2-D array, units kW
 * @property energy 2-D array, units kWh
 */
export declare class ChillerOutput {
    private constructor();

    /** 2-D array of efficiency values per chiller per load bin, units kW/ton */
    efficiency: DoubleVector2D;
    /** 2-D array of hours per chiller per load bin, units hours */
    hours: DoubleVector2D;
    /** 2-D array of power per chiller per load bin, units kW */
    power: DoubleVector2D;
    /** 2-D array of energy per chiller per load bin, units kWh */
    energy: DoubleVector2D;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link ProcessCooling.calculatePumpEnergy}.
 *
 * @property chillerPumpingEnergy array of pumping energy values, one entry per chiller, units kWh
 */
export declare class ChillerPumpingEnergyOutput {
    private constructor();

    /** Pumping energy for each chiller, units kWh */
    chillerPumpingEnergy: DoubleVector;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link ProcessCooling.calculateTowerEnergy}.
 *
 * Arrays correspond to 6 wet-bulb temperature bins:
 * < 35, 35-44, 45-54, 55-64, 65-74, >= 75 degF.
 *
 * @property efficiency array of wet-bulb temperature bin boundaries
 * @property hours array of hours in each wet-bulb bin, units hours
 * @property energy array of energy consumed in each wet-bulb bin, units kWh
 */
export declare class TowerOutput {
    private constructor();

    /** Wet-bulb temperature bin boundaries */
    efficiency: DoubleVector;
    /** Hours in each wet-bulb temperature bin, units hours */
    hours: DoubleVector;
    /** Energy consumed in each wet-bulb temperature bin, units kWh */
    energy: DoubleVector;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Input data classes
// ---------------------------------------------------------------------------

/**
 * System input for a water-cooled cooling system.
 */
export declare class WaterCooledSystemInput {
    /**
     * @param CHWT double, Chilled Water Supply Temperature, units F (35-55, default 44)
     * @param useFreeCooling boolean, enable free cooling
     * @param HEXApproachTemp double, heat exchange approach temperature when free cooling with HEX, units F (5-20)
     * @param constantCWT boolean, whether condenser water temperature is held constant
     * @param CWT double, constant condenser water temperature, units F (70-90)
     * @param CWVariableFlow boolean, variable condenser water flow
     * @param CWFlowRate double, condenser water flow rate, units gpm/ton
     * @param CWTFollow double, condenser water temperature follow offset when not constant, units F
     */
    constructor(
        CHWT: number,
        useFreeCooling: boolean,
        HEXApproachTemp: number,
        constantCWT: boolean,
        CWT: number,
        CWVariableFlow: boolean,
        CWFlowRate: number,
        CWTFollow: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * System input for an air-cooled cooling system.
 */
export declare class AirCooledSystemInput {
    /**
     * @param CHWT double, Chilled Water Supply Temperature, units F (35-55, default 44)
     * @param OADT double, Outdoor Air Design Temperature, units F (80-110, standard 95)
     * @param ACSource {@link ACSourceLocation} - cooling air source location (Inside or Outside)
     * @param indoorTemp double, indoor temperature if air source is Inside, units F (60-90)
     * @param CWTFollow double, condenser water temperature follow offset if air source is Outside, units F (5-20)
     */
    constructor(
        CHWT: number,
        OADT: number,
        ACSource: ACSourceLocation,
        indoorTemp: number,
        CWTFollow: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Pump input data for chiller pumping energy calculation.
 */
export declare class PumpInput {
    /**
     * @param variableFlow boolean, whether the pump uses variable flow
     * @param flowRate double, pump flow rate, units gpm/ton
     * @param efficiency double, pump efficiency as a fraction (0-1)
     * @param motorSize double, motor size, units hp (set to 0 to estimate from flow rate and efficiency)
     * @param motorEfficiency double, motor efficiency as a fraction (0-1)
     */
    constructor(
        variableFlow: boolean,
        flowRate: number,
        efficiency: number,
        motorSize: number,
        motorEfficiency: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Cooling tower configuration input.
 */
export declare class TowerInput {
    /**
     * @param numTower int, number of towers
     * @param numFanPerTower_Cells int, number of cells per tower
     * @param fanSpeedType {@link FanMotorSpeedType} fan motor speed control type
     * @param towerSizing {@link TowerSizedBy} how the tower is sized; if Unknown, sized to match chiller capacity
     * @param towerCellFanType {@link CellFanType} cell fan type (AxialFan or CentrifugalFan; assume AxialFan if unknown)
     * @param cellFanHP double, cell fan motor size, units hp (1-100)
     * @param tonnage double, tower tonnage, units ton (20-3000)
     */
    constructor(
        numTower: number,
        numFanPerTower_Cells: number,
        fanSpeedType: FanMotorSpeedType,
        towerSizing: TowerSizedBy,
        towerCellFanType: CellFanType,
        cellFanHP: number,
        tonnage: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Chiller configuration input.
 *
 * Four constructor overloads are provided:
 *  1. Standard chiller (no refrigerant replacement, no custom curve)
 *  2. Standard chiller with refrigerant replacement
 *  3. Custom chiller (user-supplied efficiency curve, no refrigerant replacement)
 *  4. Custom chiller with refrigerant replacement
 */
export declare class ChillerInput {
    /**
     * Standard chiller - no refrigerant replacement, no custom efficiency curve.
     *
     * @param chillerType {@link ChillerCompressorType}
     * @param capacity double, chiller capacity, units ton
     * @param isFullLoadEffKnown boolean, whether the full-load efficiency is known
     * @param fullLoadEff double, full-load efficiency as a fraction (0.2-2.5, increments of 0.01)
     * @param age double, chiller age in years (0-20); efficiency degraded 1 % per year
     * @param installVSD boolean, install a VSD on the centrifugal compressor motor
     * @param useARIMonthlyLoadSchedule boolean, use ARI monthly load schedule (monthlyLoads may be empty if true)
     * @param monthlyLoads DoubleVector2D, 12 x 11 array of % load bins per calendar month;
     *   pass a 1 x 11 array for a non-varying monthly schedule
     */
    constructor(
        chillerType: ChillerCompressorType,
        capacity: number,
        isFullLoadEffKnown: boolean,
        fullLoadEff: number,
        age: number,
        installVSD: boolean,
        useARIMonthlyLoadSchedule: boolean,
        monthlyLoads: DoubleVector2D
    );

    /**
     * Standard chiller with refrigerant replacement.
     *
     * @param chillerType {@link ChillerCompressorType}
     * @param capacity double, chiller capacity, units ton
     * @param isFullLoadEffKnown boolean
     * @param fullLoadEff double, fraction (0.2-2.5)
     * @param age double, years (0-20)
     * @param installVSD boolean
     * @param useARIMonthlyLoadSchedule boolean
     * @param monthlyLoads DoubleVector2D, 12 x 11 or 1 x 11 array
     * @param changeRefrig boolean, whether to replace the refrigerant
     * @param currentRefrig {@link RefrigerantType} current refrigerant
     * @param proposedRefrig {@link RefrigerantType} proposed replacement refrigerant
     */
    constructor(
        chillerType: ChillerCompressorType,
        capacity: number,
        isFullLoadEffKnown: boolean,
        fullLoadEff: number,
        age: number,
        installVSD: boolean,
        useARIMonthlyLoadSchedule: boolean,
        monthlyLoads: DoubleVector2D,
        changeRefrig: boolean,
        currentRefrig: RefrigerantType,
        proposedRefrig: RefrigerantType
    );

    /**
     * Custom chiller - user-supplied efficiency curve, no refrigerant replacement.
     *
     * @param chillerType {@link ChillerCompressorType}
     * @param capacity double, chiller capacity, units ton
     * @param isFullLoadEffKnown boolean
     * @param fullLoadEff double, fraction (0.2-2.5)
     * @param age double, years (0-20)
     * @param installVSD boolean
     * @param useARIMonthlyLoadSchedule boolean
     * @param monthlyLoads DoubleVector2D, 12 x 11 or 1 x 11 array
     * @param loadAtPercent DoubleVector, % loading points in ascending order (e.g. [25, 50, 75, 100])
     * @param kwPerTonLoads DoubleVector, kW/ton values at each corresponding % loading point
     */
    constructor(
        chillerType: ChillerCompressorType,
        capacity: number,
        isFullLoadEffKnown: boolean,
        fullLoadEff: number,
        age: number,
        installVSD: boolean,
        useARIMonthlyLoadSchedule: boolean,
        monthlyLoads: DoubleVector2D,
        loadAtPercent: DoubleVector,
        kwPerTonLoads: DoubleVector
    );

    /**
     * Custom chiller with refrigerant replacement.
     *
     * @param chillerType {@link ChillerCompressorType}
     * @param capacity double, chiller capacity, units ton
     * @param isFullLoadEffKnown boolean
     * @param fullLoadEff double, fraction (0.2-2.5)
     * @param age double, years (0-20)
     * @param installVSD boolean
     * @param useARIMonthlyLoadSchedule boolean
     * @param monthlyLoads DoubleVector2D, 12 x 11 or 1 x 11 array
     * @param loadAtPercent DoubleVector, % loading points in ascending order
     * @param kwPerTonLoads DoubleVector, kW/ton at each loading point
     * @param currentRefrig {@link RefrigerantType} current refrigerant
     * @param proposedRefrig {@link RefrigerantType} proposed replacement refrigerant
     */
    constructor(
        chillerType: ChillerCompressorType,
        capacity: number,
        isFullLoadEffKnown: boolean,
        fullLoadEff: number,
        age: number,
        installVSD: boolean,
        useARIMonthlyLoadSchedule: boolean,
        monthlyLoads: DoubleVector2D,
        loadAtPercent: DoubleVector,
        kwPerTonLoads: DoubleVector,
        currentRefrig: RefrigerantType,
        proposedRefrig: RefrigerantType
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Main calculator
// ---------------------------------------------------------------------------

/**
 * Process cooling system energy calculator (Chillers + Pumps + Towers).
 *
 * Two constructor overloads are provided: one for water-cooled systems
 * (requires `TowerInput` and `WaterCooledSystemInput`) and one for air-cooled
 * systems (requires `AirCooledSystemInput`).
 */
export declare class ProcessCooling {
    /**
     * Water-cooled system constructor.
     *
     * @param systemOperationAnnualHours IntVector, 8760-element array (values 0 or 1) indicating
     *   whether the system operates in each hour of the year
     * @param weatherDryBulbHourlyTemp DoubleVector, 8760-element array of dry-bulb temperatures, units F
     * @param weatherWetBulbHourlyTemp DoubleVector, 8760-element array of wet-bulb temperatures, units F
     * @param chillerInputList ChillerInputV, list of chiller configurations
     * @param towerInput {@link TowerInput} cooling tower configuration
     * @param waterCooledSystemInput {@link WaterCooledSystemInput} water-cooled system parameters
     */
    constructor(
        systemOperationAnnualHours: IntVector,
        weatherDryBulbHourlyTemp: DoubleVector,
        weatherWetBulbHourlyTemp: DoubleVector,
        chillerInputList: ChillerInputV,
        towerInput: TowerInput,
        waterCooledSystemInput: WaterCooledSystemInput
    );

    /**
     * Air-cooled system constructor.
     *
     * @param systemOperationAnnualHours IntVector, 8760-element array (values 0 or 1)
     * @param weatherDryBulbHourlyTemp DoubleVector, 8760-element array of dry-bulb temperatures, units F
     * @param weatherWetBulbHourlyTemp DoubleVector, 8760-element array of wet-bulb temperatures, units F
     * @param chillerInputList ChillerInputV, list of chiller configurations
     * @param airCooledSystemInput {@link AirCooledSystemInput} air-cooled system parameters
     */
    constructor(
        systemOperationAnnualHours: IntVector,
        weatherDryBulbHourlyTemp: DoubleVector,
        weatherWetBulbHourlyTemp: DoubleVector,
        chillerInputList: ChillerInputV,
        airCooledSystemInput: AirCooledSystemInput
    );

    /**
     * Calculate cooling tower energy consumption.
     *
     * @returns {@link TowerOutput}
     */
    calculateTowerEnergy(): TowerOutput;

    /**
     * Calculate chiller energy consumption.
     *
     * @returns {@link ChillerOutput}
     */
    calculateChillerEnergy(): ChillerOutput;

    /**
     * Calculate chiller pump energy consumption.
     *
     * @param pump {@link PumpInput} pump configuration
     * @returns {@link ChillerPumpingEnergyOutput}
     */
    calculatePumpEnergy(pump: PumpInput): ChillerPumpingEnergyOutput;

    /**
     * Returns the polynomial efficiency coefficients for a specific chiller.
     *
     * @param chillerIndex int, zero-based index into the chiller input list
     * @returns DoubleVector - 4 coefficients for a 3rd-degree polynomial (FullLoadEffKnown or custom),
     *   or 7 coefficients for a 5th-degree polynomial
     */
    getChillerEfficiencyCoeffs(chillerIndex: number): DoubleVector;

    /**
     * Returns energy efficiency values for a chiller at the specified % load points.
     *
     * @param chillerIndex int, zero-based index into the chiller input list
     * @param loadAtPercent DoubleVector, % loading values (0-100); may be in any order
     * @returns DoubleVector - energy efficiency (kW/ton) at each % loading point,
     *   in the same order as the input array
     */
    getChillerEnergyEfficiency(chillerIndex: number, loadAtPercent: DoubleVector): DoubleVector;

    /**
     * Generates the system operation annual hours array from weekly and monthly schedules.
     *
     * @param weeklyOpStartHour IntVector, 7-element array - start hour of operation for each day of the week (0-23)
     * @param weeklyOpStopHour IntVector, 7-element array - stop hour of operation for each day of the week (0-24)
     * @param monthlyOpMaxHour IntVector, 12-element array - maximum operating hours for each calendar month (0-744);
     *   use 0 for no operation; hours are capped at the maximum available hours in that month
     * @returns IntVector, 8760-element array with values 0 or 1 based on the supplied schedules
     */
    static getSysOpAnnualHours(
        weeklyOpStartHour: IntVector,
        weeklyOpStopHour: IntVector,
        monthlyOpMaxHour: IntVector
    ): IntVector;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type ProcessCoolingModule = {
    RefrigerantType: typeof RefrigerantType;
    ACSourceLocation: typeof ACSourceLocation;
    CoolingSystemType: typeof CoolingSystemType;
    CellFanType: typeof CellFanType;
    TowerSizedBy: typeof TowerSizedBy;
    ChillerCompressorType: typeof ChillerCompressorType;
    FanMotorSpeedType: typeof FanMotorSpeedType;
    ChillerOutput: typeof ChillerOutput;
    ChillerPumpingEnergyOutput: typeof ChillerPumpingEnergyOutput;
    TowerOutput: typeof TowerOutput;
    WaterCooledSystemInput: typeof WaterCooledSystemInput;
    AirCooledSystemInput: typeof AirCooledSystemInput;
    PumpInput: typeof PumpInput;
    TowerInput: typeof TowerInput;
    ChillerInput: typeof ChillerInput;
    ProcessCooling: typeof ProcessCooling;
};
