import {MotorData} from "../motorDriven/motor/motor";
import {LightingData} from "../other/lighting_data";
import {CompressorsData} from "../compressedAir/compressorsCalc";

/**
 * @brief Struct to hold default gas load/charge material data.
 *
 * @var substance string, name of substance
 * @var specificHeatVapor double, Specific Heat of Vapor in Btu/(lb*°F)
 */
export interface GasLoadChargeMaterial {
    substance: string;
    specificHeatVapor: number;
}

/**
 * @brief Struct to hold default liquid load/charge material data.
 *
 * @var substance string, name of substance
 * @var specificHeatVapor double, Specific Heat of Vapor in Btu/(lb*°F)
 * @var latentHeat double, Latent heat in Btu/lb
 * @var vaporSpecificHeat double, Specific heat of vapor in Btu/(lb*°F)
 * @var boilingPoint double, Boiling point in °F
 */
export interface LiquidLoadChargeMaterial {
    substance: string;
    specificHeat: number;
    latentHeat: number;
    vaporSpecificHeat: number;
    boilingPoint: number;
}

/**
 * @brief Struct to hold default solid load/charge material data.
 * @var substance string, Name of substance
 * @var specificHeatSolid double, Specific heat in Btu/(lb*°F)
 * @var latentHeat double, Latent heat in Btu/lb
 * @var specificHeatLiquid double, Specific heat of liquid in Btu/(lb*°F)
 * @var meltingPoint double, Melting point in °F
 */
export interface SolidLoadChargeMaterial {
    substance: string;
    specificHeatSolid: number;
    latentHeat: number;
    specificHeatLiquid: number;
    meltingPoint: number;
}

/**
 * @brief Struct to hold default gas flue gas material data.
 * @param substance string, Name of the flue gas material
 * @var CH4 double, Methane (CH4) percent by volume
 * @var C2H6 double, Ethane (C2H6) percent by volume
 * @var N2 double, Nitrogen (N2) percent by volume
 * @var H2 double, Hydrogen (H2) percent by volume
 * @var C3H8 double, Propane (C3H8) percent by volume
 * @var C4H10_CnH2n double, Butane/Paraffins (C4H10/CnH2n) percent by volume
 * @var H2O double, Water vapor (H2O) percent by volume
 * @var CO double, Carbon monoxide (CO) percent by volume
 * @var CO2 double, Carbon dioxide (CO2) percent by volume
 * @var SO2 double, Sulphur dioxide (SO2) percent by volume
 * @var O2 double, Oxygen (O2) percent by volume
 * @var heatingValue double, Heating value (Btu/SCF)
 * @var heatingValueVolume double, Heating value (Btu/ft3)
 * @var specificGravity double, Specific gravity (unitless)
 * 
 */
export interface GasFlueGasMaterial {
    substance: string;
    CH4: number;
    C2H6: number;
    N2: number;
    H2: number;
    C3H8: number;
    C4H10_CnH2n: number;
    H2O: number;
    CO: number;
    CO2: number;
    SO2: number;
    O2: number;
    heatingValue: number;
    heatingValueVolume: number;
    specificGravity: number;
}

/**
 * @brief Struct to hold default solid/liquid flue gas material data.
 * @var substance string, name of the substance
 * @var carbon double, percent by mass
 * @var hydrogen double, percent by mass
 * @var sulphur double, percent by mass
 * @var oxygen double, percent by mass
 * @var nitrogen double, percent by mass
 * @var moisture double, percent by mass
 * @var inertAsh double, ash percent by mass
 */
export interface SolidLiquidFlueGasMaterial {
    substance: string;
    carbon: number;
    hydrogen: number;
    sulphur: number;
    oxygen: number;
    nitrogen: number;
    moisture: number;
    inertAsh: number;
}

/**
 * @brief Struct to hold default wall type data.
 * @var wallDescription string, Description of the wall type
 * @var shapeFactor double, Shape factor associated with the wall type (unitless)
 */
export interface WallType {
    wallDescription: string;
    shapeFactor: number;
}

/**
 * @brief Struct to hold default gas type data.
 * @param gasDescription string, Description of the gas type
 * @param specificHeat double, Specific heat in Btu/(scf*°F)
 */
export interface AtmosphereGasType {
    gasDescription: string;
    specificHeat: number;
}

/**
 * @brief Provides access to default database records for motors, compressors, and lighting.
 */
export class DefaultData {
    /**
     * Constructor for DefaultData class, initializes the instance to access default database records.
     */
    constructor();

    getMotorData(): MotorData[];
    getCompressorType1Data(): CompressorsData[];
    getCompressorType1_GT100kWData(): CompressorsData[];
    getCompressorType2Data(): CompressorsData[];
    getCompressorType3Data(): CompressorsData[];
    getCompressorType4Data(): CompressorsData[];
    getCompressorType5Data(): CompressorsData[];
    getCompressorType6Data(): CompressorsData[];
    getLightingData(): LightingData[];

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** @brief Returns default gas load/charge materials. */
export function getDefaultGasLoadChargeMaterials(): GasLoadChargeMaterial[];

/** @brief Returns default liquid load/charge materials. */
export function getDefaultLiquidLoadChargeMaterials(): LiquidLoadChargeMaterial[];

/** @brief Returns default solid load/charge materials. */
export function getDefaultSolidLoadChargeMaterials(): SolidLoadChargeMaterial[];

/** @brief Returns default gas flue gas materials. */
export function getDefaultGasFlueGasMaterials(): GasFlueGasMaterial[];

/** @brief Returns default solid/liquid flue gas materials. */
export function getDefaultSolidLiquidFlueGasMaterials(): SolidLiquidFlueGasMaterial[];

/** @brief Returns default wall types. */
export function getDefaultWallTypes(): WallType[];

/** @brief Returns default atmosphere gas types. */
export function getDefaultGasTypes(): AtmosphereGasType[];

/** Factory function to load the Default Data WASM bindings. */
export default function DefaultDataModule(): Promise<{
    DefaultData: typeof DefaultData;
    getDefaultGasLoadChargeMaterials: typeof getDefaultGasLoadChargeMaterials;
    getDefaultLiquidLoadChargeMaterials: typeof getDefaultLiquidLoadChargeMaterials;
    getDefaultSolidLoadChargeMaterials: typeof getDefaultSolidLoadChargeMaterials;
    getDefaultGasFlueGasMaterials: typeof getDefaultGasFlueGasMaterials;
    getDefaultSolidLiquidFlueGasMaterials: typeof getDefaultSolidLiquidFlueGasMaterials;
    getDefaultWallTypes: typeof getDefaultWallTypes;
    getDefaultGasTypes: typeof getDefaultGasTypes;
}>;

