import { GasType, BaseGasDensityInputType, FanType } from "./fanEnum";
import { Motor } from "../motor/motor";
import { Drive, LoadEstimationMethod } from "../motor/motorEnum";

/** @brief Input parameters for fan result calculations. */
export class FanInput {
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

/** @brief Baseline field data for existing fan calculations. */
export class FieldDataBaseline {
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

/** @brief Modified field data for fan modification calculations. */
export class FieldDataModified {
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
 * @brief Output for fan system assessments.
 * @var fanEfficiency double
 * @var motorRatedPower double
 * @var motorShaftPower double
 * @var fanShaftPower double
 * @var motorEfficiency double
 * @var motorPowerFactor double
 * @var motorCurrent double
 * @var motorPower double
 * @var annualEnergy double
 * @var annualCost double
 * @var fanEnergyIndex double
 * @var loadFactor double
 * @var driveEfficiency double
 * @var estimatedFLA double
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

/** @brief Calculates existing and modified fan assessment outputs. */
export class FanResult {
    /**
     * Constructor for FanResult
     * @param fanInput FanInput
     * @param motor Motor
     * @param operatingHours double, annual operating hours for energy and cost calculations
     * @param unitCost double, energy unit cost for annual cost calculation (e.g., $/kWh)
     */
    constructor(fanInput: FanInput, motor: Motor, operatingHours: number, unitCost: number);

    /**
     * @param fanFieldData Fan::FieldDataBaseline
     * @return FanOutput, the results of an existing fan system assessment
     */
    calculateExisting(fanFieldData: FieldDataBaseline): FanOutput;

    /**
     * @param fanFieldData Fan::FieldDataModified
     * @param fanEfficiency double
     * @return FanOutput, the results of a fan system assessment
     */
    calculateModified(fanFieldData: FieldDataModified, fanEfficiency: number): FanOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** @brief Fan rated and corrected data used in AMCA 203 calculations. */
export class FanRatedInfo {
    /**
     * @brief Constructor for FanRatedInfo
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

/** @brief Flange plane definition used by AMCA 203 plane data. */
export class FlangePlane {
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

/** @brief Traverse plane with velocity-pressure traverse data. */
export class TraversePlane {
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

/** @brief MST plane definition used by AMCA 203 plane data. */
export class MstPlane {
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

/** @brief AMCA 203 plane data container. */
export class PlaneData {
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

/** @brief Fan shaft power helper for AMCA 203 calculations. */
export class FanShaftPower {
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
 * @brief AMCA 203 intermediate result set.
 * @var kpc double
 * @var power double
 * @var flow double
 * @var pressureTotal double
 * @var pressureStatic double
 * @var staticPressureRise double
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
 * @brief AMCA 203 output bundle.
 * @var fanEfficiencyTotalPressure double
 * @var fanEfficiencyStaticPressure double
 * @var fanEfficiencyStaticPressureRise double
 * @var asTested Fan203Results
 * @var converted Fan203Results
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

/** @brief AMCA 203 fan performance calculator. */
export class Fan203 {
    /**
     * Constructor for Fan203
     * @param fanRatedInfo FanRatedInfo
     * @param planeData PlaneData
     * @param baseGasDensity BaseGasDensity
     * @param fanShaftPower FanShaftPower
     */
    constructor(fanRatedInfo: FanRatedInfo, planeData: PlaneData, baseGasDensity: BaseGasDensity, fanShaftPower: FanShaftPower);

    calculate(): Fan203Output;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** @brief Base gas density calculator. */
export class BaseGasDensity {
    /**
     * Constructor for BaseGasDensity
     * @param dryBulbTemp double, temperature of inputted air in °F
     * @param staticPressure double, pressure in Hg
     * @param barometricPressure double in Hg
     * @param gasDensity double, density of a gas in pounds per sqft,lb/scf
     * @param gasType GasType, type of gas
     */
    constructor(dryBulbTemp: number, staticPressure: number, barometricPressure: number, gasDensity: number, gasType: GasType);

    constructor(
        /**
         * Constructor for BaseGasDensity
         * @param dryBulbTemp double, temperature of inputted air in °F
         * @param staticPressure double, pressure in inches of water (in WC)
         * @param barometricPressure double, pressure in Hg
         * @param relativeHumidityOrDewPoint double, elative humidity in % or Dewpoint in °F
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
     * @param dryBulbTemp double, temperature of inputted air in °F
     * @param staticPressure double, pressure in inches of water (in WC)
     * @param barometricPressure double, pressure in Hg
     * @param wetBulbTemp double, temperature of inputted air in °F
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

/** @brief Velocity-pressure traverse data utilities. */
export class VelocityPressureTraverseData {
    /**
     * @return double, the velocity pressure traverse data value in inches of water (in WC)
     */
    getPv3Value(): number;

    /**
     * @return double
     */
    get75percentRule(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** @brief Plane data node-binding utility. */
export class PlaneDataNodeBinding {
    /**
     * @brief Compute results
     * @param planeData PlaneData
     * @param baseGasDensity BaseGasDensity
     * @return PlaneDataNodeBindingOutput
     */
    calculate(planeData: PlaneData, baseGasDensity: BaseGasDensity): PlaneDataNodeBindingOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * @brief Plane data node-binding output data row.
 * @var gasDensity double, density in pounds per sqft, lb/scf
 * @var gasVelocity double, velocity in ft/min
 * @var gasVolumeFlowRate double, ft3/min
 * @var gasVelocityPressure double, pressure in inches of water (in WC)
 * @var gasTotalPressure double, pressure in inches of water (in WC)
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
 * @brief Plane data node-binding flange data row.
 * @var gasDensity double, density in pounds per sqft, lb/scf
 * @var gasVelocity double, velocity in ft/min
 * @var gasVolumeFlowRate double, ft3/min
 * @var gasVelocityPressure double, pressure in inches of water (in WC)
 * @var gasTotalPressure double, pressure in inches of water (in WC)
 * @var staticPressure double, pressure in inches of water (in WC)
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
 * @brief Plane data node-binding output bundle.
 * @var fanInletFlange PlaneDataNodeBindingDataFlange
 * @var fanOrEvaseOutletFlange PlaneDataNodeBindingDataFlange
 * @var flowTraverse PlaneDataNodeBindingData
 * @var inletMstPlane PlaneDataNodeBindingData
 * @var outletMstPlane PlaneDataNodeBindingData
 * @var addlTravPlanes PlaneDataNodeBindingData array
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
 * @brief function for plane node-binding calculations.
 * @param planeData PlaneData
 * @param baseGasDensity BaseGasDensity
 * @return PlaneDataNodeBindingOutput
 */
export function PlaneDataNodeBindingCalculate(
    planeData: PlaneData,
    baseGasDensity: BaseGasDensity
): PlaneDataNodeBindingOutput;

/** @brief Optimal fan efficiency calculator. */
export class OptimalFanEfficiency {
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
     * @return optimal fan efficiency, double as a %
     */
    calculate(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** @brief Compressibility factor calculator. */
export class CompressibilityFactor {
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
     * @return double Compressibility Factor
     */
    calculate(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Factory function to load the Fan. */
export default function FanModule(): Promise<{
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
}>;

