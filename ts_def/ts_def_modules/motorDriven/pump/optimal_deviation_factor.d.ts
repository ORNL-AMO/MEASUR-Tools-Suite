/** Flow-based empirical multiplier used to estimate maximum pump efficiency from an average estimate. */

/**
 * Calculates the multiplier applied to an average pump-efficiency estimate.
 * Interpolates HI 2020 positive deviation against raw US gpm and returns 1 + deviation/100.
 * Returns NaN outside inclusive range 35–100000 US gpm or for nonfinite flow. No extrapolation.
 * @param flowRate Liquid volumetric flow, units US gpm.
 * @returns Dimensionless multiplier, not an efficiency fraction. Multiply average efficiency by this value.
 * The numeric input and result require no delete().
 */
export declare function calculateOptimalDeviationFactor(flowRate: number): number;

/** Runtime function contributed by the optimal-deviation-factor binding. */
export type OptimalDeviationFactorModule = {
    calculateOptimalDeviationFactor: typeof calculateOptimalDeviationFactor;
};
