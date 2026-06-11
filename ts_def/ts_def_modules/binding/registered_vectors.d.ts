import { TraversePlane, PlaneDataNodeBindingData } from "../motorDriven/fans/fan";
import { LightingData } from "../other/lighting_data";
import { MotorData } from "../motorDriven/motor/motor";
import {
    GasFlueGasMaterial,
    GasLoadChargeMaterial,
    LiquidLoadChargeMaterial, SolidLiquidFlueGasMaterial,
    SolidLoadChargeMaterial, WallType
} from "../databases/default_data";
import { GasType } from "../motorDriven/fans/fanEnum";
import { CompressorsData } from "../compressedAir/compressorsCalc";
import { CompressedAirLeakSurveyInput } from "../compressedAir/leak_survey/compressed_air_leak_survey";
import {GasCompositions} from "../physics/gas_compositions";

export declare abstract class RegisteredVector<T> {
    /** Constructor for creating an array of elements of type <T> */
    constructor();

    /** Returns the number of elements or size or length */
    size(): number;

    /**
     * Resizes and adds x elements of <T>
     * @param size new size of the vector
     * @param elementOfTypeT element of type <T> to add if the vector is resized to be larger than the current size; optional parameter, default value is determined by the implementation
     */
    resize(size: number, elementOfTypeT?: T): void;

    /**
     * Gets the element of <T> at the index
     * @param index zero-based position in the vector
     */
    get(index: number): T;

    /**
     * Sets element of <T> at the index
     * @param index zero-based position in the vector
     * @param elementOfTypeT element of type <T> to set at the index
     */
    set(index: number, elementOfTypeT: T): boolean;

    /** Add the element of <T> at the end */
    push_back(elementOfTypeT: T): void;

    /** Empties the data */
    clear(): void;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** A vector of {@link number} records, mapped from `std::vector<number>`. */
export declare interface DoubleVector extends RegisteredVector<number> {}

/** A vector of {@link number[]} records, mapped from `std::vector<std::vector<number>>`. */
export declare interface DoubleVector2D extends RegisteredVector<number[]> {}

/** A vector of {@link CompressorsData} records, mapped from `std::vector<CompressorsData>`. */
export declare interface CompressorsDataV extends RegisteredVector<CompressorsData> {}

/** A vector of {@link CompressedAirLeakSurveyInput} records, mapped from `std::vector<CompressedAirLeakSurveyInput>`. */
export declare interface CompressedAirLeakSurveyInputV extends RegisteredVector<CompressedAirLeakSurveyInput> {}

/** A vector of {@link GasLoadChargeMaterial} records, mapped from `std::vector<GasLoadChargeMaterial>`. */
export declare interface GasLoadChargeMaterialV extends RegisteredVector<GasLoadChargeMaterial> {}

/** A vector of {@link LiquidLoadChargeMaterial} records, mapped from `std::vector<LiquidLoadChargeMaterial>`. */
export declare interface LiquidLoadChargeMaterialV extends RegisteredVector<LiquidLoadChargeMaterial> {}

/** A vector of {@link SolidLoadChargeMaterial} records, mapped from `std::vector<SolidLoadChargeMaterial>`. */
export declare interface SolidLoadChargeMaterialV extends RegisteredVector<SolidLoadChargeMaterial> {}

/** A vector of {@link GasFlueGasMaterial} records, mapped from `std::vector<GasFlueGasMaterial>`. */
export declare interface GasFlueGasMaterialV extends RegisteredVector<GasFlueGasMaterial> {}

/** A vector of {@link SolidLiquidFlueGasMaterial} records, mapped from `std::vector<SolidLiquidFlueGasMaterial>`. */
export declare interface SolidLiquidFlueGasMaterialV extends RegisteredVector<SolidLiquidFlueGasMaterial> {}

/** A vector of {@link WallType} records, mapped from `std::vector<WallType>`. */
export declare interface WallTypeV extends RegisteredVector<WallType> {}

/** A vector of {@link GasType} records, mapped from `std::vector<GasType>`. */
export declare interface AtmosphereGasTypeV extends RegisteredVector<GasType> {}

/** A vector of {@link TraversePlane} records, mapped from `std::vector<TraversePlane>`. */
export declare interface TraversePlaneVector extends RegisteredVector<TraversePlane> {}

/** A vector of {@link PlaneDataNodeBindingData} records, mapped from `std::vector<PlaneDataNodeBindingData>`. */
export declare interface PlaneDataNodeBindingDataVector extends RegisteredVector<PlaneDataNodeBindingData> {}

/** A vector of {@link MotorData} records, mapped from `std::vector<MotorData>`. */
export declare interface MotorDataV extends RegisteredVector<MotorData> {}

/** A vector of {@link LightingData} records, mapped from `std::vector<LightingData>`. */
export declare interface LightingDataV extends RegisteredVector<LightingData> {}

/** A vector of {@link GasCompositions} records, mapped from `std::vector<GasCompositions>`. */
export declare interface GasCompositionsV extends RegisteredVector<GasCompositions> {}

export type RegisteredVectorsModule = {
    DoubleVector: DoubleVector;
    DoubleVector2D: DoubleVector2D;

    CompressorsDataV: CompressorsDataV;
    CompressedAirLeakSurveyInputV: CompressedAirLeakSurveyInputV;

    GasLoadChargeMaterialV: GasLoadChargeMaterialV;
    LiquidLoadChargeMaterialV: LiquidLoadChargeMaterialV;
    SolidLoadChargeMaterialV: SolidLoadChargeMaterialV;
    GasFlueGasMaterialV: GasFlueGasMaterialV;
    SolidLiquidFlueGasMaterialV: SolidLiquidFlueGasMaterialV;
    WallTypeV: WallTypeV;
    AtmosphereGasTypeV: AtmosphereGasTypeV;

    TraversePlaneVector: TraversePlaneVector;
    PlaneDataNodeBindingDataVector: PlaneDataNodeBindingDataVector;

    MotorDataV: MotorDataV;
    LightingDataV: LightingDataV;

    GasCompositionsV: GasCompositionsV;
};
