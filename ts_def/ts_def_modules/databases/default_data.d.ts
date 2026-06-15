import {MotorData} from "../motorDriven/motor/motor";
import {LightingData} from "../other/lighting_data";
import {CompressorsData} from "../compressedAir/compressorsCalc";

/**
 * Default Data module.
 *
 * Provides default datasets used across process heat, compressed air,
 * motor-driven systems, and lighting calculations.
 */

/**
 * Gas load/charge material default record.
 *
 * @property substance string, substance name
 * @property specificHeatVapor double, specific heat of vapor in Btu/(lb*degF)
 */
export interface GasLoadChargeMaterial {
    /** Substance name */
    substance: string;
    /** Specific heat of vapor, units Btu/(lb*degF) */
    specificHeatVapor: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Liquid load/charge material default record.
 *
 * @property substance string, substance name
 * @property specificHeat double, specific heat in Btu/(lb*degF)
 * @property latentHeat double, Latent heat in Btu/lb
 * @property vaporSpecificHeat double, specific heat of vapor in Btu/(lb*degF)
 * @property boilingPoint double, boiling point in degF
 */
export interface LiquidLoadChargeMaterial {
    /** Substance name */
    substance: string;
    /** Specific heat, units Btu/(lb*degF) */
    specificHeat: number;
    /** Latent heat, units Btu/lb */
    latentHeat: number;
    /** Specific heat of vapor, units Btu/(lb*degF) */
    vaporSpecificHeat: number;
    /** Boiling point, units degF */
    boilingPoint: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Solid load/charge material default record.
 *
 * @property substance string, substance name
 * @property specificHeatSolid double, specific heat (solid) in Btu/(lb*degF)
 * @property latentHeat double, latent heat in Btu/lb
 * @property specificHeatLiquid double, specific heat (liquid) in Btu/(lb*degF)
 * @property meltingPoint double, melting point in degF
 */
export interface SolidLoadChargeMaterial {
    /** Substance name */
    substance: string;
    /** Specific heat in solid phase, units Btu/(lb*degF) */
    specificHeatSolid: number;
    /** Latent heat, units Btu/lb */
    latentHeat: number;
    /** Specific heat in liquid phase, units Btu/(lb*degF) */
    specificHeatLiquid: number;
    /** Melting point, units degF */
    meltingPoint: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Gas flue gas material default record.
 */
export interface GasFlueGasMaterial {
    /** Material name */
    substance: string;
    /** Methane (CH4), percent by volume */
    CH4: number;
    /** Ethane (C2H6), percent by volume */
    C2H6: number;
    /** Nitrogen (N2), percent by volume */
    N2: number;
    /** Hydrogen (H2), percent by volume */
    H2: number;
    /** Propane (C3H8), percent by volume */
    C3H8: number;
    /** Butane/paraffins (C4H10/CnH2n), percent by volume */
    C4H10_CnH2n: number;
    /** Water vapor (H2O), percent by volume */
    H2O: number;
    /** Carbon monoxide (CO), percent by volume */
    CO: number;
    /** Carbon dioxide (CO2), percent by volume */
    CO2: number;
    /** Sulfur dioxide (SO2), percent by volume */
    SO2: number;
    /** Oxygen (O2), percent by volume */
    O2: number;
    /** Heating value, units Btu/SCF */
    heatingValue: number;
    /** Heating value by volume, units Btu/ft3 */
    heatingValueVolume: number;
    /** Specific gravity, unitless */
    specificGravity: number;
    delete(): void;

    /** Frees the underlying resource; must be called when finished with the instance */

}

/**
 * Solid/liquid flue gas material default record.
 */
export interface SolidLiquidFlueGasMaterial {
    /** Material name */
    substance: string;
    /** Carbon, percent by mass */
    carbon: number;
    /** Hydrogen, percent by mass */
    hydrogen: number;
    /** Sulfur, percent by mass */
    sulphur: number;
    /** Oxygen, percent by mass */
    oxygen: number;
    /** Nitrogen, percent by mass */
    nitrogen: number;
    /** Moisture, percent by mass */
    moisture: number;
    /** Inert ash, percent by mass */
    inertAsh: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Wall type default record.
 */
export interface WallType {
    /** Wall type description */
    wallDescription: string;
    /** Shape factor, unitless */
    shapeFactor: number;
    delete(): void;

    /** Frees the underlying resource; must be called when finished with the instance */

}

/**
 * Atmosphere gas type default record.
 */
export interface AtmosphereGasType {
    /** Gas type description */
    gasDescription: string;
    /** Specific heat, units Btu/(scf*degF) */
    specificHeat: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Default database accessor.
 *
 * Provides access to default records for motors, compressors, and lighting.
 */
export declare class DefaultData {
    /** Default constructor - no arguments required. */
    constructor();

    /** @returns {@link MotorData} array. */
    getMotorData(): MotorData[];
    /** @returns compressor type 1 defaults as {@link CompressorsData} array. */
    getCompressorType1Data(): CompressorsData[];
    /** @returns compressor type 1 (greater than 100 kW) defaults as {@link CompressorsData} array. */
    getCompressorType1_GT100kWData(): CompressorsData[];
    /** @returns compressor type 2 defaults as {@link CompressorsData} array. */
    getCompressorType2Data(): CompressorsData[];
    /** @returns compressor type 3 defaults as {@link CompressorsData} array. */
    getCompressorType3Data(): CompressorsData[];
    /** @returns compressor type 4 defaults as {@link CompressorsData} array. */
    getCompressorType4Data(): CompressorsData[];
    /** @returns compressor type 5 defaults as {@link CompressorsData} array. */
    getCompressorType5Data(): CompressorsData[];
    /** @returns compressor type 6 defaults as {@link CompressorsData} array. */
    getCompressorType6Data(): CompressorsData[];
    /** @returns {@link LightingData} array. */
    getLightingData(): LightingData[];

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** @returns {@link GasLoadChargeMaterial} array. */
export function getDefaultGasLoadChargeMaterials(): GasLoadChargeMaterial[];

/** @returns {@link LiquidLoadChargeMaterial} array. */
export function getDefaultLiquidLoadChargeMaterials(): LiquidLoadChargeMaterial[];

/** @returns {@link SolidLoadChargeMaterial} array. */
export function getDefaultSolidLoadChargeMaterials(): SolidLoadChargeMaterial[];

/** @returns {@link GasFlueGasMaterial} array. */
export function getDefaultGasFlueGasMaterials(): GasFlueGasMaterial[];

/** @returns {@link SolidLiquidFlueGasMaterial} array. */
export function getDefaultSolidLiquidFlueGasMaterials(): SolidLiquidFlueGasMaterial[];

/** @returns {@link WallType} array. */
export function getDefaultWallTypes(): WallType[];

/** @returns {@link AtmosphereGasType} array. */
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