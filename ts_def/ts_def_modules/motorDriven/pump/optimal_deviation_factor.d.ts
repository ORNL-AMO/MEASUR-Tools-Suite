/** Flow-based empirical multiplier used to estimate maximum pump efficiency from an average estimate. */

/**
 * Calculates the multiplier applied to an average pump-efficiency estimate.
 * The empirical expression uses numerical flow in US gpm; callers convert units and validate the duty.
 * No defaults, validation or clamping are applied. Both signed zeros yield positive infinity;
 * negative flow and NaN yield NaN; positive infinity yields 1.0010805906.
 * @param flowRate Liquid volumetric flow, units US gpm.
 * @returns Dimensionless multiplier, not an efficiency fraction. Multiply average efficiency by this value.
 * The numeric input and result require no delete().
 */
export declare function calculateOptimalDeviationFactor(flowRate: number): number;

/** Runtime function contributed by the optimal-deviation-factor binding. */
export type OptimalDeviationFactorModule = {
    calculateOptimalDeviationFactor: typeof calculateOptimalDeviationFactor;
};
