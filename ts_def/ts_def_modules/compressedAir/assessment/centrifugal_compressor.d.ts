import { DoubleVector } from "../../binding/registered_vectors";
import { CompressorBlowOffResult, CompressorPerformanceResult } from "./compressor";

/** Centrifugal compressor model with load/unload control. */
export declare class CentrifugalLoadUnloadCompressor {
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param noLoadPowerKw No-load package power, units kW.
     */
    constructor(fullLoadPowerKw: number, fullLoadAirflowAcfm: number, noLoadPowerKw: number);

    /** Adjusted full-load airflow, units acfm. */
    readonly adjustedFullLoadAirflowAcfm: number;

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
     * @param capacityAcfm Curve capacities, units acfm.
     * @param dischargePressurePsig Curve discharge pressures, units psig.
     * @param fullLoadPressurePsig Full-load pressure, units psig.
     * @param maxPressurePsig Maximum pressure, units psig.
     */
    adjustDischargePressure(
        capacityAcfm: DoubleVector,
        dischargePressurePsig: DoubleVector,
        fullLoadPressurePsig: number,
        maxPressurePsig: number
    ): void;
    /** Frees the underlying resource; must be called when finished with the instance. */
    delete(): void;
}

/** Centrifugal compressor model with modulation and unloading. */
export declare class CentrifugalModulationUnloadCompressor {
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param noLoadPowerKw No-load package power, units kW.
     * @param maxAirflowAcfm Maximum full-flow airflow, units acfm.
     * @param unloadPowerKw Unload package power, units kW.
     * @param unloadAirflowAcfm Unload airflow, units acfm.
     */
    constructor(
        fullLoadPowerKw: number,
        fullLoadAirflowAcfm: number,
        noLoadPowerKw: number,
        maxAirflowAcfm: number,
        unloadPowerKw: number,
        unloadAirflowAcfm: number
    );

    /** Adjusted full-load airflow, units acfm. */
    readonly adjustedFullLoadAirflowAcfm: number;
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
     * @param capacityAcfm Curve capacities, units acfm.
     * @param dischargePressurePsig Curve discharge pressures, units psig.
     * @param fullLoadPressurePsig Full-load pressure, units psig.
     * @param maxPressurePsig Maximum pressure, units psig.
     */
    adjustDischargePressure(
        capacityAcfm: DoubleVector,
        dischargePressurePsig: DoubleVector,
        fullLoadPressurePsig: number,
        maxPressurePsig: number
    ): void;
    /** Frees the underlying resource; must be called when finished with the instance. */
    delete(): void;
}

/** Centrifugal compressor model with blow-off control. */
export declare class CentrifugalBlowOffCompressor {
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param blowOffPowerKw Blow-off package power, units kW.
     * @param blowOffAirflowAcfm Blow-off airflow, units acfm.
     */
    constructor(
        fullLoadPowerKw: number,
        fullLoadAirflowAcfm: number,
        blowOffPowerKw: number,
        blowOffAirflowAcfm: number
    );

    /** Adjusted full-load airflow, units acfm. */
    readonly adjustedFullLoadAirflowAcfm: number;

    /**
     * @param powerFraction Fraction of full-load power, dimensionless.
     * @param blowOffFraction Fraction of full-load airflow blown off, dimensionless.
     */
    calculateFromPowerFraction(powerFraction: number, blowOffFraction: number): CompressorBlowOffResult;
    /** @param airflowFraction Fraction of full-load useful airflow, dimensionless. */
    calculateFromCapacityFraction(airflowFraction: number): CompressorBlowOffResult;
    /**
     * @param powerKw Measured package power, units kW.
     * @param blowOffFraction Fraction of full-load airflow blown off, dimensionless.
     */
    calculateFromMeasuredPower(powerKw: number, blowOffFraction: number): CompressorBlowOffResult;
    /** @param airflowAcfm Measured useful airflow, units acfm. */
    calculateFromMeasuredCapacity(airflowAcfm: number): CompressorBlowOffResult;
    /**
     * @param voltage Electrical voltage, units V.
     * @param current Electrical current, units A.
     * @param powerFactor Power factor, dimensionless.
     * @param blowOffFraction Fraction of full-load airflow blown off, dimensionless.
     */
    calculateFromElectrical(
        voltage: number,
        current: number,
        powerFactor: number,
        blowOffFraction: number
    ): CompressorBlowOffResult;
    /**
     * @param capacityAcfm Curve capacities, units acfm.
     * @param dischargePressurePsig Curve discharge pressures, units psig.
     * @param fullLoadPressurePsig Full-load pressure, units psig.
     * @param maxPressurePsig Maximum pressure, units psig.
     */
    adjustDischargePressure(
        capacityAcfm: DoubleVector,
        dischargePressurePsig: DoubleVector,
        fullLoadPressurePsig: number,
        maxPressurePsig: number
    ): void;
    /** Frees the underlying resource; must be called when finished with the instance. */
    delete(): void;
}

export type CentrifugalCompressorModule = {
    CentrifugalLoadUnloadCompressor: typeof CentrifugalLoadUnloadCompressor;
    CentrifugalModulationUnloadCompressor: typeof CentrifugalModulationUnloadCompressor;
    CentrifugalBlowOffCompressor: typeof CentrifugalBlowOffCompressor;
};
