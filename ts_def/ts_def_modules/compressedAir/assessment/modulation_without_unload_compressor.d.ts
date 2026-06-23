import { CompressorPerformanceResult, CompressorType } from "./compressor";

/** Compressor model for modulation without unloading. */
export declare class ModulationWithoutUnloadCompressor {
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param noLoadPowerKw No-load package power, units kW.
     */
    constructor(fullLoadPowerKw: number, fullLoadAirflowAcfm: number, noLoadPowerKw: number);
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param noLoadPowerKw No-load package power, units kW.
     * @param modulationExponent Modulation exponent, dimensionless.
     * @param withoutUnload Whether the compressor does not unload, dimensionless boolean.
     * @param compressorType Compressor type, dimensionless enum.
     * @param noLoadPowerFractionForModulation No-load power fraction for modulation, dimensionless.
     * @param maxPowerKw Maximum package power, units kW.
     */
    constructor(
        fullLoadPowerKw: number,
        fullLoadAirflowAcfm: number,
        noLoadPowerKw: number,
        modulationExponent: number,
        withoutUnload: boolean,
        compressorType: CompressorType,
        noLoadPowerFractionForModulation: number,
        maxPowerKw: number
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

export type ModulationWithoutUnloadCompressorModule = {
    ModulationWithoutUnloadCompressor: typeof ModulationWithoutUnloadCompressor;
};
