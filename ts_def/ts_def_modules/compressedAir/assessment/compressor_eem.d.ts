/** Result for compressed-air leak reduction. */
export interface ReduceAirLeaksResult {
    /** Reduced leak airflow, units acfm. */
    reducedLeakAirflowAcfm: number;
    /** Adjusted use airflow after leak reduction, units acfm. */
    adjustedUseAirflowAcfm: number;
    /** Adjusted use airflow fraction, dimensionless. */
    adjustedUseFraction: number;
}

/** Result for compressed-air end-use efficiency improvement. */
export interface ImproveEndUseEfficiencyResult {
    /** Reduced airflow, units acfm. */
    reducedAirflowAcfm: number;
    /** Reduced airflow fraction, dimensionless. */
    reducedAirflowFraction: number;
}

/** Result for system air-pressure reduction. */
export interface ReduceSystemAirPressureResult {
    /** Adjusted full-load pressure, units psig. */
    adjustedFullLoadPressurePsig: number;
    /** Adjusted full-load power, units kW. */
    adjustedFullLoadPowerKw: number;
    /** Adjusted use airflow, units acfm. */
    adjustedUseAirflowAcfm: number;
    /** Adjusted use airflow fraction, dimensionless. */
    adjustedUseFraction: number;
}

/** Result for cascading set point adjustment. */
export interface AdjustCascadingSetPointResult {
    /** Adjusted full-load power, units kW. */
    adjustedFullLoadPowerKw: number;
    /** Adjusted use airflow, units acfm. */
    adjustedUseAirflowAcfm: number;
    /** Adjusted use airflow fraction, dimensionless. */
    adjustedUseFraction: number;
}

/** Result for pressure-reduction savings. */
export interface PressureReductionSavingResult {
    /** Demand savings, units kW. */
    powerSavingsKw: number;
    /** Annual energy savings, units kWh. */
    energySavingsKwh: number;
    /** Annual cost savings, units dollars. */
    costSavings: number;
}

/**
 * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
 * @param useAirflowAcfm Baseline use airflow, units acfm.
 * @param leakAirflowAcfm Leak airflow, units acfm.
 * @param leakReductionFraction Leak reduction fraction, dimensionless.
 */
export function reduceAirLeaks(
    fullLoadAirflowAcfm: number,
    useAirflowAcfm: number,
    leakAirflowAcfm: number,
    leakReductionFraction: number
): ReduceAirLeaksResult;

/**
 * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
 * @param useAirflowAcfm Baseline use airflow, units acfm.
 * @param reducedAverageAirflowAcfm Average airflow reduction, units acfm.
 */
export function improveEndUseEfficiency(
    fullLoadAirflowAcfm: number,
    useAirflowAcfm: number,
    reducedAverageAirflowAcfm: number
): ImproveEndUseEfficiencyResult;

/**
 * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
 * @param useAirflowAcfm Baseline use airflow, units acfm.
 * @param fullLoadPressurePsig Full-load pressure, units psig.
 * @param fullLoadPowerKw Full-load package power, units kW.
 * @param pressureReductionPsig Pressure reduction, units psig.
 * @param altitudePressurePsia Altitude pressure, units psia.
 * @param atmosphericPressurePsia Atmospheric pressure, units psia.
 */
export function reduceSystemAirPressure(
    fullLoadAirflowAcfm: number,
    useAirflowAcfm: number,
    fullLoadPressurePsig: number,
    fullLoadPowerKw: number,
    pressureReductionPsig: number,
    altitudePressurePsia: number,
    atmosphericPressurePsia: number
): ReduceSystemAirPressureResult;

/**
 * @param fullLoadAirflowAcfm Full-load airflow, units acfm.
 * @param useAirflowAcfm Baseline use airflow, units acfm.
 * @param fullLoadPressurePsig Full-load pressure, units psig.
 * @param fullLoadPowerKw Full-load package power, units kW.
 * @param adjustedFullLoadPressurePsig Adjusted full-load pressure, units psig.
 * @param altitudePressurePsia Altitude pressure, units psia.
 * @param atmosphericPressurePsia Atmospheric pressure, units psia.
 */
export function adjustCascadingSetPoint(
    fullLoadAirflowAcfm: number,
    useAirflowAcfm: number,
    fullLoadPressurePsig: number,
    fullLoadPowerKw: number,
    adjustedFullLoadPressurePsig: number,
    altitudePressurePsia: number,
    atmosphericPressurePsia: number
): AdjustCascadingSetPointResult;

/**
 * @param operatingHours Annual operating hours, units hr/yr.
 * @param costPerKwh Electricity cost, units dollars/kWh.
 * @param ratedFullLoadPowerKw Rated full-load package power, units kW.
 * @param ratedFullLoadPressurePsig Rated full-load pressure, units psig.
 * @param baselineDischargePressurePsig Baseline discharge pressure, units psig.
 * @param modifiedDischargePressurePsig Modified discharge pressure, units psig.
 * @param altitudePressurePsia Altitude pressure, units psia.
 * @param atmosphericPressurePsia Atmospheric pressure, units psia.
 */
export function pressureReductionSaving(
    operatingHours: number,
    costPerKwh: number,
    ratedFullLoadPowerKw: number,
    ratedFullLoadPressurePsig: number,
    baselineDischargePressurePsig: number,
    modifiedDischargePressurePsig: number,
    altitudePressurePsia: number,
    atmosphericPressurePsia: number
): PressureReductionSavingResult;

/**
 * @param ratedFullLoadPowerKw Rated full-load package power, units kW.
 * @param ratedFullLoadPressurePsig Rated full-load pressure, units psig.
 * @param dischargePressurePsig Discharge pressure, units psig.
 * @param altitudePressurePsia Altitude pressure, units psia.
 * @param atmosphericPressurePsia Atmospheric pressure, units psia.
 * @returns Adjusted package power, units kW.
 */
export function adjustedPower(
    ratedFullLoadPowerKw: number,
    ratedFullLoadPressurePsig: number,
    dischargePressurePsig: number,
    altitudePressurePsia: number,
    atmosphericPressurePsia: number
): number;

export type CompressorEemModule = {
    reduceAirLeaks: typeof reduceAirLeaks;
    improveEndUseEfficiency: typeof improveEndUseEfficiency;
    reduceSystemAirPressure: typeof reduceSystemAirPressure;
    adjustCascadingSetPoint: typeof adjustCascadingSetPoint;
    pressureReductionSaving: typeof pressureReductionSaving;
    adjustedPower: typeof adjustedPower;
};
