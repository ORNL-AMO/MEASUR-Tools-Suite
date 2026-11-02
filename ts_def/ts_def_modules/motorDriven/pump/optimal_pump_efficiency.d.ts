/** Pump-efficiency estimate after viscosity and specific-speed corrections. */
import type { PumpStyle } from "./pump_enums";

/** Plain required pump-duty input; no defaults or conversion are applied. */
export interface OptimalPumpEfficiencyInput {
    /** Unitless pump-style classification from the shared runtime PumpStyle enum. */
    readonly style: PumpStyle;
    /** Pump rotational speed, units rpm. */
    readonly rpm: number;
    /** Liquid kinematic viscosity, units cSt. */
    readonly kinematicViscosity: number;
    /** Number of pump stages, dimensionless; fractional values are retained. */
    readonly stageCount: number;
    /** Liquid volumetric flow, units US gpm. */
    readonly flowRate: number;
    /** Total pump head across all stages, units ft. */
    readonly head: number;
}

/**
 * Estimates pump efficiency using the flow/style estimate and viscosity/specific-speed corrections.
 * No input validation or final result clamp is applied; nonfinite arithmetic retains fmin/fmax behavior.
 * Specified-optimal and positive-displacement styles retain a zero pre-efficiency fallback and can
 * produce negative estimates; this function does not implement a specified-efficiency override.
 * @param input Plain pump-duty input; not modified and requires no delete().
 * @returns Efficiency as a dimensionless fraction, not percentage points; no cleanup is required.
 */
export declare function calculateOptimalPumpEfficiency(input: OptimalPumpEfficiencyInput): number;

/** Runtime function only; the input interface has no runtime constructor. */
export type OptimalPumpEfficiencyModule = {
    calculateOptimalPumpEfficiency: typeof calculateOptimalPumpEfficiency;
};
