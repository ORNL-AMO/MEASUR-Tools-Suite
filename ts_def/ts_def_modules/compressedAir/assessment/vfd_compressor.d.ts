import { CompressorPerformanceResult } from "./compressor";

/** Compressor model for variable frequency drive control. */
export declare class VariableFrequencyDriveCompressor {
    /**
     * @param fullLoadPowerKw Full-load package power, units kW.
     * @param midTurndownPowerKw Mid-turndown package power, units kW.
     * @param turndownPowerKw Turndown package power, units kW.
     * @param noLoadPowerKw No-load package power, units kW.
     * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
     * @param midTurndownAirflowAcfm Mid-turndown airflow, units acfm.
     * @param turndownAirflowAcfm Turndown airflow, units acfm.
     */
    constructor(
        fullLoadPowerKw: number,
        midTurndownPowerKw: number,
        turndownPowerKw: number,
        noLoadPowerKw: number,
        fullLoadAirflowAcfm: number,
        midTurndownAirflowAcfm: number,
        turndownAirflowAcfm: number
    );

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
    /** Frees the underlying resource; must be called when finished with the instance. */
    delete(): void;
}

export type VfdCompressorModule = {
    VariableFrequencyDriveCompressor: typeof VariableFrequencyDriveCompressor;
};
