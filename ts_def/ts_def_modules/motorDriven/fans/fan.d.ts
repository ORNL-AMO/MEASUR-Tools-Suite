import { GasType, BaseGasDensityInputType, FanType } from "./fanEnum";
import { Motor } from "../motor/motor";
import { Drive, LoadEstimationMethod } from "../motor/motorEnum";

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
     * @param fanSpeed double, Fan speed in RPM
     * @param airDensity double
     * @param drive Drive, enum for motor drive type (Direct, Belt, VFD)
     * @param specifiedEfficiency double
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
     * @param measuredPower double
     * @param measuredVoltage double
     * @param measuredAmps double
     * @param flowRate double
     * @param inletPressure double
     * @param outletPressure double
     * @param compressibilityFactor double
     * @param loadEstimationMethod LoadEstimationMethod
     * @param velocityPressure double
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
     * @param measuredVoltage double
     * @param measuredAmps double
     * @param flowRate double
     * @param inletPressure double
     * @param outletPressure double
     * @param compressibilityFactor double
     * @param velocityPressure double
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
 * @property fanEfficiency double, fan efficiency as decimal
 * @property motorRatedPower double, motor rated power in hp
 * @property motorShaftPower double, motor shaft power in hp
 * @property fanShaftPower double, fan shaft power in hp
 * @property motorEfficiency double, motor efficiency as decimal
 * @property motorPowerFactor double, motor power factor (unitless)
 * @property motorCurrent double, motor current in A
 * @property motorPower double, motor electric power in kW
 * @property annualEnergy double, annual energy in kWh
 * @property annualCost double, annual cost in $
 * @property fanEnergyIndex double, fan energy index (unitless)
 * @property loadFactor double, load factor as decimal
 * @property driveEfficiency double, drive efficiency as decimal
 * @property estimatedFLA double, estimated full-load amps in A
 */
export interface FanOutput {
    fanEfficiency: number;
    motorRatedPower: number;
    motorShaftPower: number;
    fanShaftPower: number;
    motorEfficiency: number;
    motorPowerFactor: number;
    motorCurrent: number;
    motorPower: number;
    annualEnergy: number;
    annualCost: number;
    fanEnergyIndex: number;
    loadFactor: number;
    driveEfficiency: number;
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
     * @param operatingHours double, annual operating hours for energy and cost calculations
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
     * @param fanEfficiency double
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
     * @param fanSpeed double, Fan speed RPM
     * @param motorSpeed double, Motor speed RPM
     * @param fanSpeedCorrected double, Fan speed corrected to reference conditions RPM
     * @param densityCorrected double, Gas density corrected to reference conditions  lb/scf
     * @param pressureBarometricCorrected double, Barometric pressure corrected to reference conditions in Hg
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
     * @param area double
     * @param tdx double
     * @param pbx double
     */
    constructor(area: number, tdx: number, pbx: number);

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Traverse plane with velocity-pressure traverse data. */
export declare class TraversePlane {
    /**
     * Constructor for TraversePlane
     * @param area double
     * @param tdx double
     * @param pbx double
     * @param psx double
     * @param pitotTubeCoefficient double
     * @param traverseHoleData array of double array
     */
    constructor(
        area: number,
        tdx: number,
        pbx: number,
        psx: number,
        pitotTubeCoefficient: number,
        traverseHoleData: number[][]
    );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** MST plane definition used by AMCA 203 plane data. */
export declare class MstPlane {
    /**
     * Constructor for MstPlane
     * @param area double
     * @param tdx double
     * @param pbx double
     * @param psx double
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
     * @param addlTravPlanes array of TraversePlane
     * @param inletMstPlane MstPlane
     * @param outletMstPlane MstPlane
     * @param totalPressureLossBtwnPlanes1and4 double
     * @param totalPressureLossBtwnPlanes2and5 double
     * @param plane5upstreamOfPlane2 boolean
     */
    constructor(
        fanInletFlange: FlangePlane,
        fanOrEvaseOutletFlange: FlangePlane,
        flowTraverse: TraversePlane,
        addlTravPlanes: TraversePlane[],
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
     * @param efficiencyMotor double, percentage
     * @param efficiencyVFD double, percentage
     * @param efficiencyBelt double, percentage
     * @param sumSEF double
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
 * @property kpc double
 * @property power double
 * @property flow double
 * @property pressureTotal double
 * @property pressureStatic double
 * @property staticPressureRise double
 */
export interface Fan203Results {
    kpc: number;
    power: number;
    flow: number;
    pressureTotal: number;
    pressureStatic: number;
    staticPressureRise: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * AMCA 203 output bundle.
 * @property fanEfficiencyTotalPressure double
 * @property fanEfficiencyStaticPressure double
 * @property fanEfficiencyStaticPressureRise double
 * @property asTested Fan203Results
 * @property converted Fan203Results
 */
export interface Fan203Output {
    fanEfficiencyTotalPressure: number;
    fanEfficiencyStaticPressure: number;
    fanEfficiencyStaticPressureRise: number;
    asTested: Fan203Results;
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
     * @param dryBulbTemp double, temperature of inputted air in degF
     * @param staticPressure double, pressure in Hg
     * @param barometricPressure double in Hg
     * @param gasDensity double, density of a gas in pounds per sqft,lb/scf
     * @param gasType GasType, type of gas
     */
    constructor(dryBulbTemp: number, staticPressure: number, barometricPressure: number, gasDensity: number, gasType: GasType);

    constructor(
        /**
         * Constructor for BaseGasDensity
         * @param dryBulbTemp double, temperature of inputted air in degF
         * @param staticPressure double, pressure in inches of water (in WC)
         * @param barometricPressure double, pressure in Hg
         * @param relativeHumidityOrDewPoint double, elative humidity in % or Dewpoint in degF
         * @param gasType GasType
         * @param inputType BaseGasDensityInputType
         * @param specificGravity double, specific gravity unitless
         */
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
     * @param dryBulbTemp double, temperature of inputted air in degF
     * @param staticPressure double, pressure in inches of water (in WC)
     * @param barometricPressure double, pressure in Hg
     * @param wetBulbTemp double, temperature of inputted air in degF
     * @param gasType GasType
     * @param inputType BaseGasDensityInputType
     * @param specificGravity double, specific gravity unitless
     * @param cpGas double, specific heat of gas
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

    /** Getter for GasDensity */
    getGasDensity(): number;
    /** Getter for AbsolutePressureIn */
    getAbsolutePressureIn(): number;
    /** Getter for SaturatedHumidityRatio */
    getSaturatedHumidityRatio(): number;
    /** Getter for DegreeOfSaturation */
    getDegreeOfSaturation(): number;
    /** Getter for HumidityRatio */
    getHumidityRatio(): number;
    /** Getter for SpecificVolume */
    getSpecificVolume(): number;
    /** Getter for Enthalpy */
    getEnthalpy(): number;
    /** Getter for DewPoint */
    getDewPoint(): number;
    /** Getter for RelativeHumidity */
    getRelativeHumidity(): number;
    /** Getter for SaturationPressure */
    getSaturationPressure(): number;
    /** Getter for WetBulbTemp */
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
     * @returns double
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
export interface PlaneDataNodeBindingData {
    gasDensity: number;
    gasVelocity: number;
    gasVolumeFlowRate: number;
    gasVelocityPressure: number;
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
export interface PlaneDataNodeBindingDataFlange {
    gasDensity: number;
    gasVelocity: number;
    gasVolumeFlowRate: number;
    gasVelocityPressure: number;
    gasTotalPressure: number;
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
export interface PlaneDataNodeBindingOutput {
    fanInletFlange: PlaneDataNodeBindingDataFlange;
    fanOrEvaseOutletFlange: PlaneDataNodeBindingDataFlange;
    flowTraverse: PlaneDataNodeBindingData;
    inletMstPlane: PlaneDataNodeBindingData;
    outletMstPlane: PlaneDataNodeBindingData;
    addlTravPlanes: PlaneDataNodeBindingData[];

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
     * @param fanSpeed double
     * @param flowRate double
     * @param inletPressure double
     * @param outletPressure double
     * @param compressibility double
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
     * @returns optimal fan efficiency, double as a %
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
     * @param specificHeatRatio double, unitless
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
     * @returns double Compressibility Factor
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
    FanOutput: FanOutput;
    Fan203Output: Fan203Output;
    Fan203Results: Fan203Results;
    PlaneDataNodeBindingOutput: PlaneDataNodeBindingOutput;
    PlaneDataNodeBindingData: PlaneDataNodeBindingData;
    PlaneDataNodeBindingDataFlange: PlaneDataNodeBindingDataFlange;
};
