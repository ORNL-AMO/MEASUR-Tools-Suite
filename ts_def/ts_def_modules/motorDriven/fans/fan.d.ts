import { GasType, BaseGasDensityInputType, FanType } from "./fanEnum";
import { Motor } from "../motor/motor";
import { Drive, LoadEstimationMethod } from "../motor/motorEnum";
import type { DoubleVector2D, PlaneDataNodeBindingDataVector, TraversePlaneVector } from "../../binding/registered_vectors";

/**
 * Fan calculations and AMCA 203 utilities.
 *
 * Provides fan-system performance calculators, AMCA 203 data models,
 * base gas density utilities, and helper calculations.
 */

/**
 * Input parameters for fan result calculations.
 */
export declare class FanInput {
    /**
     * Constructor for Fan Input
     * @param fanSpeed Fan speed, units rpm.
     * @param airDensity Air density, units lb/ft3.
     * @param drive Drive, enum for motor drive type (Direct, Belt, VFD)
     * @param specifiedEfficiency Specified drive efficiency, dimensionless fraction.
     */
    constructor(fanSpeed: number, airDensity: number, drive: Drive, specifiedEfficiency: number);

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Baseline field data for existing fan calculations.
 */
export declare class FieldDataBaseline {
    /**
     * To be used for Baseline Fan results
     * @param measuredPower Measured motor power, units kW.
     * @param measuredVoltage Measured voltage, units V.
     * @param measuredAmps Measured current, units A.
     * @param flowRate Fan flow rate, units cfm.
     * @param inletPressure Fan inlet pressure, units in. w.c.
     * @param outletPressure Fan outlet pressure, units in. w.c.
     * @param compressibilityFactor Compressibility factor, dimensionless.
     * @param loadEstimationMethod LoadEstimationMethod
     * @param velocityPressure Velocity pressure, units in. w.c.
     */
    constructor(
        measuredPower: number,
        measuredVoltage: number,
        measuredAmps: number,
        flowRate: number,
        inletPressure: number,
        outletPressure: number,
        compressibilityFactor: number,
        loadEstimationMethod: LoadEstimationMethod,
        velocityPressure: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Modified field data for fan modification calculations.
 */
export declare class FieldDataModified {
    /**
     * To be used for Modified and Optimal Fan results
     * @param measuredVoltage Measured voltage, units V.
     * @param measuredAmps Measured current, units A.
     * @param flowRate Fan flow rate, units cfm.
     * @param inletPressure Fan inlet pressure, units in. w.c.
     * @param outletPressure Fan outlet pressure, units in. w.c.
     * @param compressibilityFactor Compressibility factor, dimensionless.
     * @param velocityPressure Velocity pressure, units in. w.c.
     */
    constructor(
        measuredVoltage: number,
        measuredAmps: number,
        flowRate: number,
        inletPressure: number,
        outletPressure: number,
        compressibilityFactor: number,
        velocityPressure: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by fan system assessments.
 *
 * @property fanEfficiency Fan efficiency, dimensionless fraction.
 * @property motorRatedPower Motor rated power, units hp.
 * @property motorShaftPower Motor shaft power, units hp.
 * @property fanShaftPower Fan shaft power, units hp.
 * @property motorEfficiency Motor efficiency, dimensionless fraction.
 * @property motorPowerFactor Motor power factor, dimensionless.
 * @property motorCurrent Motor current, units A.
 * @property motorPower Motor electric power, units kW.
 * @property annualEnergy Annual energy, units kWh/year.
 * @property annualCost Annual cost, units $/year.
 * @property fanEnergyIndex Fan energy index, dimensionless.
 * @property loadFactor Load factor, dimensionless fraction.
 * @property driveEfficiency Drive efficiency, dimensionless fraction.
 * @property estimatedFLA Estimated full-load current, units A.
 */
export declare class FanOutput {
    /**
     * Constructor for FanOutput
     * @param fanEfficiency Fan efficiency, dimensionless fraction.
     * @param motorRatedPower Motor rated power, units hp.
     * @param motorShaftPower Motor shaft power, units hp.
     * @param fanShaftPower Fan shaft power, units hp.
     * @param motorEfficiency Motor efficiency, dimensionless fraction.
     * @param motorPowerFactor Motor power factor, dimensionless.
     * @param motorCurrent Motor current, units A.
     * @param motorPower Motor electric power, units kW.
     * @param annualEnergy Annual energy, units kWh/year.
     * @param annualCost Annual cost, units $/year.
     * @param fanEnergyIndex Fan energy index, dimensionless.
     * @param loadFactor Load factor, dimensionless fraction.
     * @param driveEfficiency Drive efficiency, dimensionless fraction.
     * @param estimatedFLA Estimated full-load current, units A.
     */
    constructor(
        fanEfficiency: number,
        motorRatedPower: number,
        motorShaftPower: number,
        fanShaftPower: number,
        motorEfficiency: number,
        motorPowerFactor: number,
        motorCurrent: number,
        motorPower: number,
        annualEnergy: number,
        annualCost: number,
        fanEnergyIndex: number,
        loadFactor: number,
        driveEfficiency: number,
        estimatedFLA: number
    );

    /** Fan efficiency, dimensionless fraction. */
    fanEfficiency: number;
    /** motor rated power units hp. */
    motorRatedPower: number;
    /** motor shaft power units hp. */
    motorShaftPower: number;
    /** fan shaft power units hp. */
    fanShaftPower: number;
    /** Motor efficiency, dimensionless fraction. */
    motorEfficiency: number;
    /** Motor power factor, dimensionless. */
    motorPowerFactor: number;
    /** motor current units A. */
    motorCurrent: number;
    /** motor electric power units kW. */
    motorPower: number;
    /** Annual energy, units kWh/year. */
    annualEnergy: number;
    /** Annual cost, units $/year. */
    annualCost: number;
    /** Fan energy index, dimensionless. */
    fanEnergyIndex: number;
    /** Load factor, dimensionless fraction. */
    loadFactor: number;
    /** Drive efficiency, dimensionless fraction. */
    driveEfficiency: number;
    /** estimated full-load amps units A. */
    estimatedFLA: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Calculates existing and modified fan assessment outputs. */
export declare class FanResult {
    /**
     * Constructor for FanResult
     * @param fanInput FanInput
     * @param motor Motor
     * @param operatingHours double, annual operating hours, units hr/year for energy and cost calculations
     * @param unitCost double, energy unit cost for annual cost calculation (e.g., $/kWh)
     */
    constructor(fanInput: FanInput, motor: Motor, operatingHours: number, unitCost: number);

    /**
     * @param fanFieldData {@link FieldDataBaseline}
     * @returns {@link FanOutput}, the results of an existing fan system assessment
     */
    calculateExisting(fanFieldData: FieldDataBaseline): FanOutput;

    /**
     * @param fanFieldData Fan::FieldDataModified
     * @param fanEfficiency Fan efficiency, dimensionless fraction.
     * @returns {@link FanOutput}, the results of a fan system assessment
     */
    calculateModified(fanFieldData: FieldDataModified, fanEfficiency: number): FanOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Fan rated and corrected data used in AMCA 203 calculations. */
export declare class FanRatedInfo {
    /**
     * Constructor for FanRatedInfo
     * @param fanSpeed Fan speed, units rpm.
     * @param motorSpeed Motor speed, units rpm.
     * @param fanSpeedCorrected Fan speed corrected to reference conditions, units rpm.
     * @param densityCorrected Gas density corrected to reference conditions, units lb/scf.
     * @param pressureBarometricCorrected Barometric pressure corrected to reference conditions, units in Hg.
     */
    constructor(
        fanSpeed: number,
        motorSpeed: number,
        fanSpeedCorrected: number,
        densityCorrected: number,
        pressureBarometricCorrected: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Flange plane definition used by AMCA 203 plane data. */
export declare class FlangePlane {
    /**
     * Constructor for FlangePlane
     * @param area Plane area, units ft2.
     * @param tdx Dry-bulb temperature at the plane, units degF.
     * @param pbx Barometric pressure at the plane, units in Hg.
     */
    constructor(area: number, tdx: number, pbx: number);

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Traverse plane with velocity-pressure traverse data. */
export declare class TraversePlane extends VelocityPressureTraverseData {
    /**
     * Constructor for TraversePlane
     * @param area Plane area, units ft2.
     * @param tdx Dry-bulb temperature at the plane, units degF.
     * @param pbx Barometric pressure at the plane, units in Hg.
     * @param psx Static pressure at the plane, units in. w.c.
     * @param pitotTubeCoefficient Pitot tube coefficient, dimensionless.
     * @param traverseHoleData Velocity-pressure traverse data, units in. w.c.
     */
    constructor(
        area: number,
        tdx: number,
        pbx: number,
        psx: number,
        pitotTubeCoefficient: number,
        traverseHoleData: DoubleVector2D
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** MST plane definition used by AMCA 203 plane data. */
export declare class MstPlane {
    /**
     * Constructor for MstPlane
     * @param area Plane area, units ft2.
     * @param tdx Dry-bulb temperature at the plane, units degF.
     * @param pbx Barometric pressure at the plane, units in Hg.
     * @param psx Static pressure at the plane, units in. w.c.
     */
    constructor(area: number, tdx: number, pbx: number, psx: number);

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** AMCA 203 plane data container. */
export declare class PlaneData {
    /**
     * Constructor for PlaneData
     * @param fanInletFlange FlangePlane
     * @param fanOrEvaseOutletFlange FlangePlane
     * @param flowTraverse TraversePlane
     * @param addlTravPlanes vector of TraversePlane
     * @param inletMstPlane MstPlane
     * @param outletMstPlane MstPlane
     * @param totalPressureLossBtwnPlanes1and4 Total pressure loss between planes 1 and 4, units in. w.c.
     * @param totalPressureLossBtwnPlanes2and5 Total pressure loss between planes 2 and 5, units in. w.c.
     * @param plane5upstreamOfPlane2 boolean
     */
    constructor(
        fanInletFlange: FlangePlane,
        fanOrEvaseOutletFlange: FlangePlane,
        flowTraverse: TraversePlane,
        addlTravPlanes: TraversePlaneVector,
        inletMstPlane: MstPlane,
        outletMstPlane: MstPlane,
        totalPressureLossBtwnPlanes1and4: number,
        totalPressureLossBtwnPlanes2and5: number,
        plane5upstreamOfPlane2: boolean
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Fan shaft power helper for AMCA 203 calculations. */
export declare class FanShaftPower {
    /**
     * Constructor for FanShaftPower
     * @param motorShaftPower double, motor shaft power in hp
     * @param efficiencyMotor Motor efficiency, units %.
     * @param efficiencyVFD VFD efficiency, units %.
     * @param efficiencyBelt Belt efficiency, units %.
     * @param sumSEF Sum of static efficiency factors, dimensionless.
     */
    constructor(
        motorShaftPower: number,
        efficiencyMotor: number,
        efficiencyVFD: number,
        efficiencyBelt: number,
        sumSEF: number
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * AMCA 203 intermediate result set.
 * @property kpc Compressibility coefficient, dimensionless.
 * @property power Fan power, units hp.
 * @property flow Fan flow, units cfm.
 * @property pressureTotal Total pressure, units in. w.c.
 * @property pressureStatic Static pressure, units in. w.c.
 * @property staticPressureRise Static pressure rise, units in. w.c.
 */
export declare class Fan203Results {
    /**
     * Constructor for Fan203Results
     * @param kpc Compressibility coefficient, dimensionless.
     * @param power Fan power, units hp.
     * @param flow Fan flow, units cfm.
     * @param pressureTotal Total pressure, units in. w.c.
     * @param pressureStatic Static pressure, units in. w.c.
     * @param staticPressureRise Static pressure rise, units in. w.c.
     */
    constructor(
        kpc: number,
        power: number,
        flow: number,
        pressureTotal: number,
        pressureStatic: number,
        staticPressureRise: number
    );

    /** Compressibility coefficient, dimensionless. */
    kpc: number;
    /** Fan power, units hp. */
    power: number;
    /** Fan flow, units cfm. */
    flow: number;
    /** Total pressure, units in. w.c. */
    pressureTotal: number;
    /** Static pressure, units in. w.c. */
    pressureStatic: number;
    /** Static pressure rise, units in. w.c. */
    staticPressureRise: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * AMCA 203 output bundle.
 * @property fanEfficiencyTotalPressure Fan total-pressure efficiency, dimensionless fraction.
 * @property fanEfficiencyStaticPressure Fan static-pressure efficiency, dimensionless fraction.
 * @property fanEfficiencyStaticPressureRise Fan static-pressure-rise efficiency, dimensionless fraction.
 * @property asTested Fan203Results
 * @property converted Fan203Results
 */
export declare class Fan203Output {
    /**
     * Constructor for Fan203Output
     * @param fanEfficiencyTotalPressure Fan total-pressure efficiency, dimensionless fraction.
     * @param fanEfficiencyStaticPressure Fan static-pressure efficiency, dimensionless fraction.
     * @param fanEfficiencyStaticPressureRise Fan static-pressure-rise efficiency, dimensionless fraction.
     * @param asTested As-tested AMCA 203 results.
     * @param converted Converted AMCA 203 results.
     */
    constructor(
        fanEfficiencyTotalPressure: number,
        fanEfficiencyStaticPressure: number,
        fanEfficiencyStaticPressureRise: number,
        asTested: Fan203Results,
        converted: Fan203Results
    );

    /** Fan total-pressure efficiency, dimensionless fraction. */
    fanEfficiencyTotalPressure: number;
    /** Fan static-pressure efficiency, dimensionless fraction. */
    fanEfficiencyStaticPressure: number;
    /** Fan static-pressure-rise efficiency, dimensionless fraction. */
    fanEfficiencyStaticPressureRise: number;
    /** Fan203Results. */
    asTested: Fan203Results;
    /** Fan203Results. */
    converted: Fan203Results;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** AMCA 203 fan performance calculator. */
export declare class Fan203 {
    /**
     * Constructor for Fan203
     * @param fanRatedInfo FanRatedInfo
     * @param planeData PlaneData
     * @param baseGasDensity BaseGasDensity
     * @param fanShaftPower FanShaftPower
     */
    constructor(fanRatedInfo: FanRatedInfo, planeData: PlaneData, baseGasDensity: BaseGasDensity, fanShaftPower: FanShaftPower);

    /**
     * Calculates AMCA 203 fan performance results.
     *
     * @returns {@link Fan203Output}
     */
    calculate(): Fan203Output;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Base gas density calculator. */
export declare class BaseGasDensity {
    /**
     * Constructor for BaseGasDensity
     * @param dryBulbTemp Input air dry-bulb temperature, units degF.
     * @param staticPressure Static pressure, units in. w.c.
     * @param barometricPressure Barometric pressure, units in Hg.
     * @param gasDensity Gas density, units lb/scf.
     * @param gasType GasType, type of gas
     */
    constructor(dryBulbTemp: number, staticPressure: number, barometricPressure: number, gasDensity: number, gasType: GasType);

    /**
     * Constructor for BaseGasDensity
     * @param dryBulbTemp Input air dry-bulb temperature, units degF.
     * @param staticPressure Static pressure, units in. w.c.
     * @param barometricPressure Barometric pressure, units in Hg.
     * @param relativeHumidityOrDewPoint Relative humidity, units %, or dew point, units degF, depending on inputType.
     * @param gasType GasType
     * @param inputType BaseGasDensityInputType
     * @param specificGravity Specific gravity, dimensionless.
     */
    constructor(
        dryBulbTemp: number,
        staticPressure: number,
        barometricPressure: number,
        relativeHumidityOrDewPoint: number,
        gasType: GasType,
        inputType: BaseGasDensityInputType,
        specificGravity: number
    );

    /**
     * Constructor for BaseGasDensity
     * @param dryBulbTemp Input air dry-bulb temperature, units degF.
     * @param staticPressure Static pressure, units in. w.c.
     * @param barometricPressure Barometric pressure, units in Hg.
     * @param wetBulbTemp Input air wet-bulb temperature, units degF.
     * @param gasType GasType
     * @param inputType BaseGasDensityInputType
     * @param specificGravity Specific gravity, dimensionless.
     * @param cpGas Gas specific heat, units Btu/(lb.degF).
     */
    constructor(
        dryBulbTemp: number,
        staticPressure: number,
        barometricPressure: number,
        wetBulbTemp: number,
        gasType: GasType,
        inputType: BaseGasDensityInputType,
        specificGravity: number,
        cpGas: number
    );

    /** @returns Gas density, units lb/scf. */
    getGasDensity(): number;
    /** @returns Absolute pressure, units in Hg. */
    getAbsolutePressureIn(): number;
    /** @returns Saturated humidity ratio, dimensionless. */
    getSaturatedHumidityRatio(): number;
    /** @returns Degree of saturation, dimensionless. */
    getDegreeOfSaturation(): number;
    /** @returns Humidity ratio, dimensionless. */
    getHumidityRatio(): number;
    /** @returns Specific volume, units ft3/lb. */
    getSpecificVolume(): number;
    /** @returns Enthalpy, units Btu/lb. */
    getEnthalpy(): number;
    /** @returns Dew point temperature, units degF. */
    getDewPoint(): number;
    /** @returns Relative humidity, units %. */
    getRelativeHumidity(): number;
    /** @returns Saturation pressure, units in Hg. */
    getSaturationPressure(): number;
    /** @returns Wet-bulb temperature, units degF. */
    getWetBulbTemp(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Velocity-pressure traverse data utilities. */
export declare class VelocityPressureTraverseData {
    /**
     * @returns double, the velocity pressure traverse data value in inches of water (in WC)
     */
    getPv3Value(): number;

    /**
     * @returns Percent of traverse points that satisfy the 75 percent rule, units %.
     */
    get75percentRule(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Plane data node-binding utility. */
export declare class PlaneDataNodeBinding {
    /**
     * Compute results
     * @param planeData PlaneData
     * @param baseGasDensity BaseGasDensity
     * @returns PlaneDataNodeBindingOutput
     */
    calculate(planeData: PlaneData, baseGasDensity: BaseGasDensity): PlaneDataNodeBindingOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Plane data node-binding output data row.
 * @property gasDensity double, density in pounds per sqft, lb/scf
 * @property gasVelocity double, velocity in ft/min
 * @property gasVolumeFlowRate double, ft3/min
 * @property gasVelocityPressure double, pressure in inches of water (in WC)
 * @property gasTotalPressure double, pressure in inches of water (in WC)
 */
export declare class PlaneDataNodeBindingData {
    /**
     * Constructor for PlaneDataNodeBindingData
     * @param gasDensity Gas density, units lb/scf.
     * @param gasVelocity Gas velocity, units ft/min.
     * @param gasVolumeFlowRate Gas volume flow rate, units ft3/min.
     * @param gasVelocityPressure Gas velocity pressure, units in. w.c.
     * @param gasTotalPressure Gas total pressure, units in. w.c.
     */
    constructor(
        gasDensity: number,
        gasVelocity: number,
        gasVolumeFlowRate: number,
        gasVelocityPressure: number,
        gasTotalPressure: number
    );

    /** density in pounds per sqft, lb/scf. */
    gasDensity: number;
    /** velocity in ft/min. */
    gasVelocity: number;
    /** ft3/min. */
    gasVolumeFlowRate: number;
    /** pressure in inches of water (in WC). */
    gasVelocityPressure: number;
    /** pressure in inches of water (in WC). */
    gasTotalPressure: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Plane data node-binding flange data row.
 * @property gasDensity double, density in pounds per sqft, lb/scf
 * @property gasVelocity double, velocity in ft/min
 * @property gasVolumeFlowRate double, ft3/min
 * @property gasVelocityPressure double, pressure in inches of water (in WC)
 * @property gasTotalPressure double, pressure in inches of water (in WC)
 * @property staticPressure double, pressure in inches of water (in WC)
 */
export declare class PlaneDataNodeBindingDataFlange extends PlaneDataNodeBindingData {
    /**
     * Constructor for PlaneDataNodeBindingDataFlange
     * @param gasDensity Gas density, units lb/scf.
     * @param gasVelocity Gas velocity, units ft/min.
     * @param gasVolumeFlowRate Gas volume flow rate, units ft3/min.
     * @param gasVelocityPressure Gas velocity pressure, units in. w.c.
     * @param gasTotalPressure Gas total pressure, units in. w.c.
     * @param staticPressure Static pressure, units in. w.c.
     */
    constructor(
        gasDensity: number,
        gasVelocity: number,
        gasVolumeFlowRate: number,
        gasVelocityPressure: number,
        gasTotalPressure: number,
        staticPressure: number
    );

    /** pressure in inches of water (in WC). */
    staticPressure: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Plane data node-binding output bundle.
 * @property fanInletFlange PlaneDataNodeBindingDataFlange
 * @property fanOrEvaseOutletFlange PlaneDataNodeBindingDataFlange
 * @property flowTraverse PlaneDataNodeBindingData
 * @property inletMstPlane PlaneDataNodeBindingData
 * @property outletMstPlane PlaneDataNodeBindingData
 * @property addlTravPlanes PlaneDataNodeBindingData array
 */
export declare class PlaneDataNodeBindingOutput {
    /**
     * Constructor for PlaneDataNodeBindingOutput
     */
    constructor(planeData: PlaneData);

    /** PlaneDataNodeBindingDataFlange. */
    fanInletFlange: PlaneDataNodeBindingDataFlange;
    /** PlaneDataNodeBindingDataFlange. */
    fanOrEvaseOutletFlange: PlaneDataNodeBindingDataFlange;
    /** PlaneDataNodeBindingData. */
    flowTraverse: PlaneDataNodeBindingData;
    /** PlaneDataNodeBindingData. */
    inletMstPlane: PlaneDataNodeBindingData;
    /** PlaneDataNodeBindingData. */
    outletMstPlane: PlaneDataNodeBindingData;
    /** PlaneDataNodeBindingData array. */
    addlTravPlanes: PlaneDataNodeBindingDataVector;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * function for plane node-binding calculations.
 * @param planeData PlaneData
 * @param baseGasDensity BaseGasDensity
 * @returns PlaneDataNodeBindingOutput
 */
export function PlaneDataNodeBindingCalculate(
    planeData: PlaneData,
    baseGasDensity: BaseGasDensity
): PlaneDataNodeBindingOutput;

/** Optimal fan efficiency calculator. */
export declare class OptimalFanEfficiency {
    /**
     * Constructor for Optimal Fan Efficiency
     * @param fanType FanType
     * @param fanSpeed Fan speed, units rpm.
     * @param flowRate Fan flow rate, units cfm.
     * @param inletPressure Fan inlet pressure, units in. w.c.
     * @param outletPressure Fan outlet pressure, units in. w.c.
     * @param compressibility Compressibility factor, dimensionless.
     */
    constructor(
        fanType: FanType,
        fanSpeed: number,
        flowRate: number,
        inletPressure: number,
        outletPressure: number,
        compressibility: number
    );

    /**
     * Calculate Thermal Resistance
     * @returns Optimal fan efficiency, units %.
     */
    calculate(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Compressibility factor calculator. */
export declare class CompressibilityFactor {
    /**
     * Constructor
     * @param moverShaftPower double, in horsepower (hp)
     * @param inletPressure double, in inches of water column, gauge
     * @param outletPressure double, in inches of water column, gauge
     * @param barometricPressure double, in Hg
     * @param flowRate double, in cfm
     * @param specificHeatRatio Specific heat ratio, dimensionless.
     */
    constructor(
        moverShaftPower: number,
        inletPressure: number,
        outletPressure: number,
        barometricPressure: number,
        flowRate: number,
        specificHeatRatio: number
    );

    /**
     * Calculate Compressibility Factor
     * @returns Compressibility factor, dimensionless.
     */
    calculate(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type FanModule = {
    FanInput: typeof FanInput;
    FieldDataBaseline: typeof FieldDataBaseline;
    FieldDataModified: typeof FieldDataModified;
    FanResult: typeof FanResult;
    FanRatedInfo: typeof FanRatedInfo;
    PlaneData: typeof PlaneData;
    FlangePlane: typeof FlangePlane;
    TraversePlane: typeof TraversePlane;
    MstPlane: typeof MstPlane;
    FanShaftPower: typeof FanShaftPower;
    Fan203: typeof Fan203;
    BaseGasDensity: typeof BaseGasDensity;
    VelocityPressureTraverseData: typeof VelocityPressureTraverseData;
    PlaneDataNodeBinding: typeof PlaneDataNodeBinding;
    PlaneDataNodeBindingCalculate: typeof PlaneDataNodeBindingCalculate;
    OptimalFanEfficiency: typeof OptimalFanEfficiency;
    CompressibilityFactor: typeof CompressibilityFactor;
    FanOutput: typeof FanOutput;
    Fan203Output: typeof Fan203Output;
    Fan203Results: typeof Fan203Results;
    PlaneDataNodeBindingOutput: typeof PlaneDataNodeBindingOutput;
    PlaneDataNodeBindingData: typeof PlaneDataNodeBindingData;
    PlaneDataNodeBindingDataFlange: typeof PlaneDataNodeBindingDataFlange;
};
