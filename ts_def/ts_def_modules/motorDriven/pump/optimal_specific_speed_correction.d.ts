/** Empirical pump-efficiency decrement from pump style and US customary specific speed. */

import type { PumpStyle } from "./pump_enums";

/** Plain required style/speed input; no defaults or unit conversion. */
export interface OptimalSpecificSpeedCorrectionInput {
    /** Unitless pump-style classification from the shared runtime PumpStyle enum. */
    readonly style: PumpStyle;
    /** US customary specific speed, units rpm*sqrt(US gpm)/ft^(3/4); not dimensionless. */
    readonly specificSpeed: number;
}

/**
 * Calculates the efficiency fraction to subtract from the viscosity-adjusted pump estimate.
 * Interpolates HI 2020 points and divides by 100. Vertical turbine uses 1717.2–17172;
 * axial flow and all other styles use 630–6300, in US customary specific speed.
 * Returns NaN for nonfinite/out-of-range speed. Inclusive endpoints; no extrapolation.
 * @param input Plain style/speed input; not modified and requires no delete().
 * @returns Dimensionless efficiency decrement as a fraction, not percentage points; no cleanup.
 */
export declare function calculateOptimalSpecificSpeedCorrection(input: OptimalSpecificSpeedCorrectionInput): number;

/** Runtime function only; the input interface has no runtime constructor. */
export type OptimalSpecificSpeedCorrectionModule = {
    calculateOptimalSpecificSpeedCorrection: typeof calculateOptimalSpecificSpeedCorrection;
};
