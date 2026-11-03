/** Empirical pump-efficiency decrement from pump style and US customary specific speed. */

import type { PumpStyle } from "./pump_enums";

/** Plain required style/speed input; no defaults, conversion or validation. */
export interface OptimalSpecificSpeedCorrectionInput {
    /** Unitless pump-style classification from the shared runtime PumpStyle enum. */
    readonly style: PumpStyle;
    /** US customary specific speed, units rpm*sqrt(US gpm)/ft^(3/4); not dimensionless. */
    readonly specificSpeed: number;
}

/**
 * Calculates the efficiency fraction to subtract from the viscosity-adjusted pump estimate.
 * Only vertical turbine uses the vertical curves; axial flow and all other styles use the other curves.
 * Equality selects the upper speed interval. The polynomial is lower-clamped with fmax before
 * conversion to a fraction; no upper clamp or input validation is applied.
 * @param input Plain style/speed input; not modified and requires no delete().
 * @returns Dimensionless efficiency decrement as a fraction, not percentage points; no cleanup.
 */
export declare function calculateOptimalSpecificSpeedCorrection(input: OptimalSpecificSpeedCorrectionInput): number;

/** Runtime function only; the input interface has no runtime constructor. */
export type OptimalSpecificSpeedCorrectionModule = {
    calculateOptimalSpecificSpeedCorrection: typeof calculateOptimalSpecificSpeedCorrection;
};
