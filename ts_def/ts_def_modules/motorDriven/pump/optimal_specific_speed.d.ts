/** Pump specific speed in the US customary convention using head per stage. */

/** Plain required pump-duty input; all values are supplied without defaults or conversion. */
export interface OptimalSpecificSpeedInput {
    /** Pump rotational speed, units rpm. */
    readonly rpm: number;
    /** Liquid volumetric flow, units US gpm; no double-suction flow adjustment is applied. */
    readonly flowRate: number;
    /** Total pump head across all stages, units ft. */
    readonly head: number;
    /** Number of pump stages, dimensionless; fractional values are retained. */
    readonly stageCount: number;
}

/**
 * Calculates pump specific speed using total head divided by the supplied stage count.
 * Evaluates signed, zero and nonfinite values directly; no validation or clamping is applied.
 * @param input Plain pump-duty input; not modified and requires no delete().
 * @returns US customary specific speed, units rpm*sqrt(US gpm)/ft^(3/4), not dimensionless.
 * The numeric result requires no cleanup.
 */
export declare function calculateOptimalSpecificSpeed(input: OptimalSpecificSpeedInput): number;

/** Runtime function only; the input interface has no runtime constructor. */
export type OptimalSpecificSpeedModule = {
    calculateOptimalSpecificSpeed: typeof calculateOptimalSpecificSpeed;
};
