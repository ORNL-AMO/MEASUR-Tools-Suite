import {MotorData} from "../motorDriven/motor/motor";
import {LightingData} from "../other/lighting_data";
import {CompressorsData} from "../compressedAir/compressorsCalc";

/**
 * Struct to hold default gas load/charge material data.
 *
 * @property substance string, name of substance
 * @property specificHeatVapor double, Specific Heat of Vapor in Btu/(lb*°F)
 */
export interface GasLoadChargeMaterial {
    substance: string;
    specificHeatVapor: number;
}

/**
 * Struct to hold default liquid load/charge material data.
 *
 * @property substance string, name of substance
 * @property specificHeatVapor double, Specific Heat of Vapor in Btu/(lb*°F)
 * @property latentHeat double, Latent heat in Btu/lb
 * @property vaporSpecificHeat double, Specific heat of vapor in Btu/(lb*°F)
 * @property boilingPoint double, Boiling point in °F
 */
export interface LiquidLoadChargeMaterial {
    substance: string;
    specificHeat: number;
    latentHeat: number;
    vaporSpecificHeat: number;
    boilingPoint: number;
}

/**
 * Struct to hold default solid load/charge material data.
 * @property substance string, Name of substance
 * @property specificHeatSolid double, Specific heat in Btu/(lb*°F)
 * @property latentHeat double, Latent heat in Btu/lb
 * @property specificHeatLiquid double, Specific heat of liquid in Btu/(lb*°F)
 * @property meltingPoint double, Melting point in °F
 */
export interface SolidLoadChargeMaterial {
    substance: string;
    specificHeatSolid: number;
    latentHeat: number;
    specificHeatLiquid: number;
    meltingPoint: number;
}

/**
 * Struct to hold default gas flue gas material data.
 * @param substance string, Name of the flue gas material
 * @property CH4 double, Methane (CH4) percent by volume
 * @property C2H6 double, Ethane (C2H6) percent by volume
 * @property N2 double, Nitrogen (N2) percent by volume
 * @property H2 double, Hydrogen (H2) percent by volume
 * @property C3H8 double, Propane (C3H8) percent by volume
 * @property C4H10_CnH2n double, Butane/Paraffins (C4H10/CnH2n) percent by volume
 * @property H2O double, Water vapor (H2O) percent by volume
 * @property CO double, Carbon monoxide (CO) percent by volume
 * @property CO2 double, Carbon dioxide (CO2) percent by volume
 * @property SO2 double, Sulphur dioxide (SO2) percent by volume
 * @property O2 double, Oxygen (O2) percent by volume
 * @property heatingValue double, Heating value (Btu/SCF)
 * @property heatingValueVolume double, Heating value (Btu/ft3)
 * @property specificGravity double, Specific gravity (unitless)
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
 * Struct to hold default solid/liquid flue gas material data.
 * @property substance string, name of the substance
 * @property carbon double, percent by mass
 * @property hydrogen double, percent by mass
 * @property sulphur double, percent by mass
 * @property oxygen double, percent by mass
 * @property nitrogen double, percent by mass
 * @property moisture double, percent by mass
 * @property inertAsh double, ash percent by mass
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
 * Struct to hold default wall type data.
 * @property wallDescription string, Description of the wall type
 * @property shapeFactor double, Shape factor associated with the wall type (unitless)
 */
export interface WallType {
    wallDescription: string;
    shapeFactor: number;
}

/**
 * Struct to hold default gas type data.
 * @param gasDescription string, Description of the gas type
 * @param specificHeat double, Specific heat in Btu/(scf*°F)
 */
export interface AtmosphereGasType {
    gasDescription: string;
    specificHeat: number;
}

/**
 * Provides access to default database records for motors, compressors, and lighting.
 */
export declare class DefaultData {
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

/** Returns default gas load/charge materials. */
export function getDefaultGasLoadChargeMaterials(): GasLoadChargeMaterial[];

/** Returns default liquid load/charge materials. */
export function getDefaultLiquidLoadChargeMaterials(): LiquidLoadChargeMaterial[];

/** Returns default solid load/charge materials. */
export function getDefaultSolidLoadChargeMaterials(): SolidLoadChargeMaterial[];

/** Returns default gas flue gas materials. */
export function getDefaultGasFlueGasMaterials(): GasFlueGasMaterial[];

/** Returns default solid/liquid flue gas materials. */
export function getDefaultSolidLiquidFlueGasMaterials(): SolidLiquidFlueGasMaterial[];

/** Returns default wall types. */
export function getDefaultWallTypes(): WallType[];

/** Returns default atmosphere gas types. */
export function getDefaultGasTypes(): AtmosphereGasType[];

export type DefaultDataModule = {
    DefaultData: typeof DefaultData;
    getDefaultGasLoadChargeMaterials: typeof getDefaultGasLoadChargeMaterials;
    getDefaultLiquidLoadChargeMaterials: typeof getDefaultLiquidLoadChargeMaterials;
    getDefaultSolidLoadChargeMaterials: typeof getDefaultSolidLoadChargeMaterials;
    getDefaultGasFlueGasMaterials: typeof getDefaultGasFlueGasMaterials;
    getDefaultSolidLiquidFlueGasMaterials: typeof getDefaultSolidLiquidFlueGasMaterials;
    getDefaultWallTypes: typeof getDefaultWallTypes;
    getDefaultGasTypes: typeof getDefaultGasTypes;
    GasLoadChargeMaterial: GasLoadChargeMaterial;
    LiquidLoadChargeMaterial: LiquidLoadChargeMaterial;
    SolidLoadChargeMaterial: SolidLoadChargeMaterial;
    GasFlueGasMaterial: GasFlueGasMaterial;
    SolidLiquidFlueGasMaterial: SolidLiquidFlueGasMaterial;
    WallType: WallType;
    AtmosphereGasType: AtmosphereGasType;
};
