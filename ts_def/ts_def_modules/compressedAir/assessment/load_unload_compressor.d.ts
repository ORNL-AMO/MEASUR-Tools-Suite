import { CompressorControl, CompressorLubricant, CompressorPerformanceResult, CompressorType } from "./compressor";

/** Compressor load/unload cycle model for screw and reciprocating compressors. */
export declare class LoadUnloadCompressor {
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param storageVolumeFt3 Receiver storage volume, units ft3.
     * @param maxPowerKw Maximum package power, units kW.
     * @param fullLoadPressurePsig Full-load pressure, units psig.
     * @param maxPressurePsig Maximum pressure, units psig.
     * @param modulatingPressurePsig Modulating pressure range, units psig.
     * @param unloadedLoadFactor Unloaded load factor, dimensionless.
     */
    constructor(
        fullLoadPowerKw: number,
        fullLoadAirflowAcfm: number,
        storageVolumeFt3: number,
        maxPowerKw: number,
        fullLoadPressurePsig: number,
        maxPressurePsig: number,
        modulatingPressurePsig: number,
        unloadedLoadFactor: number
    );
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param storageVolumeFt3 Receiver storage volume, units ft3.
     * @param maxPowerKw Maximum package power, units kW.
     * @param fullLoadPressurePsig Full-load pressure, units psig.
     * @param maxPressurePsig Maximum pressure, units psig.
     * @param modulatingPressurePsig Modulating pressure range, units psig.
     * @param unloadedLoadFactor Unloaded load factor, dimensionless.
     * @param atmosphericPressurePsia Atmospheric pressure, units psia.
     * @param compressorType Compressor type, dimensionless enum.
     * @param lubricant Lubricant type, dimensionless enum.
     * @param control Control strategy, dimensionless enum.
     * @param noLoadPowerKw No-load package power, units kW.
     * @param unloadCapacityPercent Unload capacity, units percent.
     */
    constructor(
        fullLoadPowerKw: number,
        fullLoadAirflowAcfm: number,
        storageVolumeFt3: number,
        maxPowerKw: number,
        fullLoadPressurePsig: number,
        maxPressurePsig: number,
        modulatingPressurePsig: number,
        unloadedLoadFactor: number,
        atmosphericPressurePsia: number,
        compressorType: CompressorType,
        lubricant: CompressorLubricant,
        control: CompressorControl,
        noLoadPowerKw: number,
        unloadCapacityPercent: number
    );
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param storageVolumeFt3 Receiver storage volume, units ft3.
     * @param maxPowerKw Maximum package power, units kW.
     * @param fullLoadPressurePsig Full-load pressure, units psig.
     * @param maxPressurePsig Maximum pressure, units psig.
     * @param modulatingPressurePsig Modulating pressure range, units psig.
     * @param unloadedLoadFactor Unloaded load factor, dimensionless.
     * @param atmosphericPressurePsia Atmospheric pressure, units psia.
     * @param compressorType Compressor type, dimensionless enum.
     * @param lubricant Lubricant type, dimensionless enum.
     * @param control Control strategy, dimensionless enum.
     * @param noLoadPowerKw No-load package power, units kW.
     * @param unloadCapacityPercent Unload capacity, units percent.
     * @param blowdownTimeSec Blowdown time, units seconds.
     * @param unloadSumpPressurePsig Unload sump pressure, units psig.
     * @param noLoadPowerFractionForModulation No-load modulation power fraction, dimensionless.
     */
    constructor(
        fullLoadPowerKw: number,
        fullLoadAirflowAcfm: number,
        storageVolumeFt3: number,
        maxPowerKw: number,
        fullLoadPressurePsig: number,
        maxPressurePsig: number,
        modulatingPressurePsig: number,
        unloadedLoadFactor: number,
        atmosphericPressurePsia: number,
        compressorType: CompressorType,
        lubricant: CompressorLubricant,
        control: CompressorControl,
        noLoadPowerKw: number,
        unloadCapacityPercent: number,
        blowdownTimeSec: number,
        unloadSumpPressurePsig: number,
        noLoadPowerFractionForModulation: number
    );

    /** Adjusted full-load power, units kW. */
    readonly adjustedFullLoadPowerKw: number;
    /** Adjusted full-load airflow, units acfm. */
    readonly adjustedFullLoadAirflowAcfm: number;
    /** Adjusted maximum power, units kW. */
    readonly adjustedMaxPowerKw: number;
    /** Adjusted maximum airflow, units acfm. */
    readonly adjustedMaxAirflowAcfm: number;

    /** @param powerFraction Fraction of full-load power, dimensionless. */
    calculateFromPowerFraction(powerFraction: number): CompressorPerformanceResult;
    /** @param airflowFraction Fraction of full-load airflow, dimensionless. */
    calculateFromCapacityFraction(airflowFraction: number): CompressorPerformanceResult;
    /** @param powerKw Measured package power, units kW. */
    calculateFromMeasuredPower(powerKw: number): CompressorPerformanceResult;
    /** @param airflowAcfm Measured airflow, units acfm. */
    calculateFromMeasuredCapacity(airflowAcfm: number): CompressorPerformanceResult;
    /**
     * @param voltage Electrical voltage, units V.
     * @param current Electrical current, units A.
     * @param powerFactor Power factor, dimensionless.
     */
    calculateFromElectrical(voltage: number, current: number, powerFactor: number): CompressorPerformanceResult;
    /**
     * @param capacityAcfm Rated capacity, units acfm.
     * @param fullLoadBhp Full-load brake horsepower, units hp.
     * @param polyExponent Polytropic exponent, dimensionless.
     * @param ratedDischargePressurePsig Rated discharge pressure, units psig.
     * @param ratedInletPressurePsia Rated inlet pressure, units psia.
     * @param efficiency Motor efficiency, dimensionless.
     * @param fullLoadPressurePsig Full-load pressure, units psig.
     * @param maxPressurePsig Maximum pressure, units psig.
     * @param inletPressurePsia Inlet pressure, units psia.
     * @param pressureAdjustment Whether to adjust for pressure, dimensionless boolean.
     * @param atmosphericPressurePsia Atmospheric pressure, units psia.
     */
    applyPressureInletCorrection(
        capacityAcfm: number,
        fullLoadBhp: number,
        polyExponent: number,
        ratedDischargePressurePsig: number,
        ratedInletPressurePsia: number,
        efficiency: number,
        fullLoadPressurePsig: number,
        maxPressurePsig: number,
        inletPressurePsia: number,
        pressureAdjustment: boolean,
        atmosphericPressurePsia: number
    ): void;
    /** Frees the underlying resource; must be called when finished with the instance. */
    delete(): void;
}

/** Screw compressor model for modulation or variable displacement with unloading. */
export declare class ModulationWithUnloadCompressor extends LoadUnloadCompressor {
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param storageVolumeFt3 Receiver storage volume, units ft3.
     * @param maxPowerKw Maximum package power, units kW.
     * @param noLoadPowerKw No-load package power, units kW.
     * @param fullLoadPressurePsig Full-load pressure, units psig.
     * @param maxPressurePsig Maximum pressure, units psig.
     * @param modulatingPressurePsig Modulating pressure range, units psig.
     */
    constructor(
        fullLoadPowerKw: number,
        fullLoadAirflowAcfm: number,
        storageVolumeFt3: number,
        maxPowerKw: number,
        noLoadPowerKw: number,
        fullLoadPressurePsig: number,
        maxPressurePsig: number,
        modulatingPressurePsig: number
    );
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param storageVolumeFt3 Receiver storage volume, units ft3.
     * @param maxPowerKw Maximum package power, units kW.
     * @param noLoadPowerKw No-load package power, units kW.
     * @param fullLoadPressurePsig Full-load pressure, units psig.
     * @param maxPressurePsig Maximum pressure, units psig.
     * @param modulatingPressurePsig Modulating pressure range, units psig.
     * @param atmosphericPressurePsia Atmospheric pressure, units psia.
     * @param unloadCapacityPercent Unload capacity, units percent.
     * @param control Control strategy, dimensionless enum.
     * @param blowdownTimeSec Blowdown time, units seconds.
     * @param unloadSumpPressurePsig Unload sump pressure, units psig.
     * @param noLoadPowerFractionForModulation No-load modulation power fraction, dimensionless.
     */
    constructor(
        fullLoadPowerKw: number,
        fullLoadAirflowAcfm: number,
        storageVolumeFt3: number,
        maxPowerKw: number,
        noLoadPowerKw: number,
        fullLoadPressurePsig: number,
        maxPressurePsig: number,
        modulatingPressurePsig: number,
        atmosphericPressurePsia: number,
        unloadCapacityPercent: number,
        control: CompressorControl,
        blowdownTimeSec: number,
        unloadSumpPressurePsig: number,
        noLoadPowerFractionForModulation: number
    );
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param storageVolumeFt3 Receiver storage volume, units ft3.
     * @param maxPowerKw Maximum package power, units kW.
     * @param noLoadPowerKw No-load package power, units kW.
     * @param fullLoadPressurePsig Full-load pressure, units psig.
     * @param maxPressurePsig Maximum pressure, units psig.
     * @param modulatingPressurePsig Modulating pressure range, units psig.
     * @param atmosphericPressurePsia Atmospheric pressure, units psia.
     * @param unloadCapacityPercent Unload capacity, units percent.
     * @param control Control strategy, dimensionless enum.
     * @param blowdownTimeSec Blowdown time, units seconds.
     * @param unloadSumpPressurePsig Unload sump pressure, units psig.
     * @param noLoadPowerFractionForModulation No-load modulation power fraction, dimensionless.
     * @param unloadPowerKw Unload package power, units kW.
     * @param unloadPressurePsig Unload pressure, units psig.
     * @param unloadAirflowAcfm Unload airflow, units acfm.
     */
    constructor(
        fullLoadPowerKw: number,
        fullLoadAirflowAcfm: number,
        storageVolumeFt3: number,
        maxPowerKw: number,
        noLoadPowerKw: number,
        fullLoadPressurePsig: number,
        maxPressurePsig: number,
        modulatingPressurePsig: number,
        atmosphericPressurePsia: number,
        unloadCapacityPercent: number,
        control: CompressorControl,
        blowdownTimeSec: number,
        unloadSumpPressurePsig: number,
        noLoadPowerFractionForModulation: number,
        unloadPowerKw: number,
        unloadPressurePsig: number,
        unloadAirflowAcfm: number
    );
}

export type LoadUnloadCompressorModule = {
    LoadUnloadCompressor: typeof LoadUnloadCompressor;
    ModulationWithUnloadCompressor: typeof ModulationWithUnloadCompressor;
};
