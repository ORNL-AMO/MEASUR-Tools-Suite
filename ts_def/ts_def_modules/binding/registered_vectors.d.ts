import { TraversePlane, PlaneDataNodeBindingData } from "../motorDriven/fans/fan";
import { LightingData } from "../other/lighting_data";
import { MotorData } from "../motorDriven/motor/motor";
import {
    AtmosphereGasType,
    GasFlueGasMaterial,
    GasLoadChargeMaterial,
    LiquidLoadChargeMaterial, SolidLiquidFlueGasMaterial,
    SolidLoadChargeMaterial, WallType
} from "../databases/default_data";
import { GasType } from "../motorDriven/fans/fanEnum";
import { CompressorsData } from "../compressedAir/compressorsCalc";
import { CompressedAirLeakSurveyInput } from "../compressedAir/leak_survey/compressed_air_leak_survey";
import { GasCompositions } from "../physics/gas_compositions";
import { CalculationsTable } from "../wasteWater/wasteWater";
import { GraphDataPoint } from "../wasteWater/svi";
import { ChillerInput } from "../processCooling/process_cooling";
import { WaterReductionInput } from "../treasureHunt/water_reduction";
import { SteamReductionInput } from "../treasureHunt/steam_reduction";
import { NaturalGasReductionInput } from "../treasureHunt/natural_gas_reduction";
import { ElectricityReductionInput } from "../treasureHunt/electricity_reduction";
import { CompressedAirReductionInput } from "../treasureHunt/compressed_air_reduction";
import { CompressedAirPressureReductionInput } from "../treasureHunt/compressed_air_pressure_reduction";
import { Inlet } from "../steamModeler/ssmt";

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

export type RegisteredVectorConstructor<TVector extends RegisteredVector<unknown>> = {
    new (): TVector;
};

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

/** A vector of {@link AtmosphereGasType} records, mapped from `std::vector<AtmosphereGasType>`. */
export declare interface AtmosphereGasTypeV extends RegisteredVector<AtmosphereGasType> {}

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

/** A vector of int records, mapped from `std::vector<int>`. */
export declare interface IntVector extends RegisteredVector<number> {}

/** A vector of {@link ChillerInput} records, mapped from `std::vector<ChillerInput>`. */
export declare interface ChillerInputV extends RegisteredVector<ChillerInput> {}

/** A vector of {@link Inlet} records, mapped from `std::vector<Inlet>`. */
export declare interface InletVector extends RegisteredVector<Inlet> {}

/** A vector of {@link CompressedAirPressureReductionInput} records, mapped from `std::vector<CompressedAirPressureReductionInput>`. */
export declare interface CompressedAirPressureReductionInputV extends RegisteredVector<CompressedAirPressureReductionInput> {}

/** A vector of {@link CompressedAirReductionInput} records, mapped from `std::vector<CompressedAirReductionInput>`. */
export declare interface CompressedAirReductionInputV extends RegisteredVector<CompressedAirReductionInput> {}

/** A vector of {@link ElectricityReductionInput} records, mapped from `std::vector<ElectricityReductionInput>`. */
export declare interface ElectricityReductionInputV extends RegisteredVector<ElectricityReductionInput> {}

/** A vector of {@link NaturalGasReductionInput} records, mapped from `std::vector<NaturalGasReductionInput>`. */
export declare interface NaturalGasReductionInputV extends RegisteredVector<NaturalGasReductionInput> {}

/** A vector of {@link SteamReductionInput} records, mapped from `std::vector<SteamReductionInput>`. */
export declare interface SteamReductionInputV extends RegisteredVector<SteamReductionInput> {}

/** A vector of {@link WaterReductionInput} records, mapped from `std::vector<WaterReductionInput>`. */
export declare interface WaterReductionInputV extends RegisteredVector<WaterReductionInput> {}

/** A vector of {@link GraphDataPoint} records, mapped from `std::vector<GraphDataPoint>`. */
export declare interface GraphDataV extends RegisteredVector<GraphDataPoint> {}

/** A vector of {@link CalculationsTable} records, mapped from `std::vector<CalculationsTable>`. */
export declare interface CalculationsTableV extends RegisteredVector<CalculationsTable> {}

export type RegisteredVectorsModule = {
    DoubleVector: RegisteredVectorConstructor<DoubleVector>;
    DoubleVector2D: RegisteredVectorConstructor<DoubleVector2D>;

    CompressorsDataV: RegisteredVectorConstructor<CompressorsDataV>;
    CompressedAirLeakSurveyInputV: RegisteredVectorConstructor<CompressedAirLeakSurveyInputV>;

    GasLoadChargeMaterialV: RegisteredVectorConstructor<GasLoadChargeMaterialV>;
    LiquidLoadChargeMaterialV: RegisteredVectorConstructor<LiquidLoadChargeMaterialV>;
    SolidLoadChargeMaterialV: RegisteredVectorConstructor<SolidLoadChargeMaterialV>;
    GasFlueGasMaterialV: RegisteredVectorConstructor<GasFlueGasMaterialV>;
    SolidLiquidFlueGasMaterialV: RegisteredVectorConstructor<SolidLiquidFlueGasMaterialV>;
    WallTypeV: RegisteredVectorConstructor<WallTypeV>;
    AtmosphereGasTypeV: RegisteredVectorConstructor<AtmosphereGasTypeV>;

    TraversePlaneVector: RegisteredVectorConstructor<TraversePlaneVector>;
    PlaneDataNodeBindingDataVector: RegisteredVectorConstructor<PlaneDataNodeBindingDataVector>;

    MotorDataV: RegisteredVectorConstructor<MotorDataV>;
    LightingDataV: RegisteredVectorConstructor<LightingDataV>;

    GasCompositionsV: RegisteredVectorConstructor<GasCompositionsV>;

    IntVector: RegisteredVectorConstructor<IntVector>;
    ChillerInputV: RegisteredVectorConstructor<ChillerInputV>;

    InletVector: RegisteredVectorConstructor<InletVector>;

    CompressedAirPressureReductionInputV: RegisteredVectorConstructor<CompressedAirPressureReductionInputV>;
    CompressedAirReductionInputV: RegisteredVectorConstructor<CompressedAirReductionInputV>;
    ElectricityReductionInputV: RegisteredVectorConstructor<ElectricityReductionInputV>;
    NaturalGasReductionInputV: RegisteredVectorConstructor<NaturalGasReductionInputV>;
    SteamReductionInputV: RegisteredVectorConstructor<SteamReductionInputV>;
    WaterReductionInputV: RegisteredVectorConstructor<WaterReductionInputV>;

    GraphDataV: RegisteredVectorConstructor<GraphDataV>;
    CalculationsTableV: RegisteredVectorConstructor<CalculationsTableV>;
};
