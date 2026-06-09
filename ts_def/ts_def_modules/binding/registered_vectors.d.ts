import { TraversePlane, PlaneDataNodeBindingData } from "../motorDriven/fans/fan";
import {LightingData} from "../other/lighting_data";
import {MotorData} from "../motorDriven/motor/motor";
import {
    GasFlueGasMaterial,
    GasLoadChargeMaterial,
    LiquidLoadChargeMaterial, SolidLiquidFlueGasMaterial,
    SolidLoadChargeMaterial, WallType
} from "../databases/default_data";
import {GasType} from "../motorDriven/fans/fanEnum";
import {CompressorsData} from "../compressedAir/compressorsCalc";
import {CompressedAirLeakSurveyInput} from "../compressedAir/leak_survey/compressed_air_leak_survey";

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
    resize(size: number, elementOfTypeT?: number): void;

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

/** @brief A vector of {@link number} records, mapped from `std::vector<number>`. */
export declare class DoubleVector extends RegisteredVector<number> {}

/** @brief A vector of {@link number[]} records, mapped from `std::vector<std::vector<number>>`. */
export declare class DoubleVector2D extends RegisteredVector<number[]> {}

/** @brief A vector of {@link CompressorsData} records, mapped from `std::vector<CompressorsData>`. */
export declare class CompressorsDataV extends RegisteredVector<CompressorsData> {}

/** @brief A vector of {@link CompressedAirLeakSurveyInput} records, mapped from `std::vector<CompressedAirLeakSurveyInput>`. */
export declare class CompressedAirLeakSurveyInputV extends RegisteredVector<CompressedAirLeakSurveyInput> {}

/** @brief A vector of {@link GasLoadChargeMaterial} records, mapped from `std::vector<GasLoadChargeMaterial>`. */
export declare class GasLoadChargeMaterialV extends RegisteredVector<GasLoadChargeMaterial> {}

/** @brief A vector of {@link LiquidLoadChargeMaterial} records, mapped from `std::vector<LiquidLoadChargeMaterial>`. */
export declare class LiquidLoadChargeMaterialV extends RegisteredVector<LiquidLoadChargeMaterial> {}

/** @brief A vector of {@link SolidLoadChargeMaterial} records, mapped from `std::vector<SolidLoadChargeMaterial>`. */
export declare class SolidLoadChargeMaterialV extends RegisteredVector<SolidLoadChargeMaterial> {}

/** @brief A vector of {@link GasFlueGasMaterial} records, mapped from `std::vector<GasFlueGasMaterial>`. */
export declare class GasFlueGasMaterialV extends RegisteredVector<GasFlueGasMaterial> {}

/** @brief A vector of {@link SolidLiquidFlueGasMaterial} records, mapped from `std::vector<SolidLiquidFlueGasMaterial>`. */
export declare class SolidLiquidFlueGasMaterialV extends RegisteredVector<SolidLiquidFlueGasMaterial> {}

/** @brief A vector of {@link WallType} records, mapped from `std::vector<WallType>`. */
export declare class WallTypeV extends RegisteredVector<WallType> {}

/** @brief A vector of {@link GasType} records, mapped from `std::vector<GasType>`. */
export declare class AtmosphereGasTypeV extends RegisteredVector<GasType> {}

/** @brief A vector of {@link TraversePlane} records, mapped from `std::vector<TraversePlane>`. */
export declare class TraversePlaneVector extends RegisteredVector<TraversePlane> {}

/** @brief A vector of {@link PlaneDataNodeBindingData} records, mapped from `std::vector<PlaneDataNodeBindingData>`. */
export declare class PlaneDataNodeBindingDataVector extends RegisteredVector<PlaneDataNodeBindingData> {}

/** @brief A vector of {@link MotorData} records, mapped from `std::vector<MotorData>`. */
export declare class MotorDataV extends RegisteredVector<MotorData> {}

/** @brief A vector of {@link LightingData} records, mapped from `std::vector<LightingData>`. */
export declare class LightingDataV extends RegisteredVector<LightingData> {}

export interface RegisteredVectorsModuleExports {
    DoubleVector: typeof DoubleVector;
    DoubleVector2D: typeof DoubleVector2D;

    CompressorsDataV: typeof CompressorsDataV;
    CompressedAirLeakSurveyInput: typeof CompressedAirLeakSurveyInputV;

    GasLoadChargeMaterialV: typeof GasLoadChargeMaterialV;
    LiquidLoadChargeMaterialV: typeof LiquidLoadChargeMaterialV;
    SolidLoadChargeMaterialV: typeof SolidLoadChargeMaterialV;
    GasFlueGasMaterialV: typeof GasFlueGasMaterialV;
    SolidLiquidFlueGasMaterialV: typeof SolidLiquidFlueGasMaterialV;
    WallTypeV: typeof WallTypeV;
    AtmosphereGasTypeV: typeof AtmosphereGasTypeV;

    TraversePlaneVector: typeof TraversePlaneVector;
    PlaneDataNodeBindingDataVector: typeof PlaneDataNodeBindingDataVector;

    MotorDataV: typeof MotorDataV;
    LightingDataV: typeof LightingDataV;
}

export default function RegisteredVectorsModule(): Promise<RegisteredVectorsModuleExports>;