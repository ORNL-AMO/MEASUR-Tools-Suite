/** Empirical achievable average and maximum pump-efficiency estimates for a supplied pump duty. */
import type { PumpStyle } from "./pump_enums";

/** Plain required pump-duty input; no defaults, validation, conversion or cleanup. */
export interface PumpEfficiencyInput {
    /** Unitless pump-style classification from the shared runtime PumpStyle enum. */
    readonly style: PumpStyle;
    /** Pump rotational speed, units rpm. */
    readonly rpm: number;
    /** Fluid kinematic viscosity, units cSt. */
    readonly kinematicViscosity: number;
    /** Number of pump stages, dimensionless; fractional values are retained. */
    readonly stageCount: number;
    /** Liquid volumetric flow, units US gpm. */
    readonly flowRate: number;
    /** Total pump head across all stages, units ft. */
    readonly head: number;
}

/** Plain efficiency estimates with no runtime constructor or delete() requirement. */
export interface PumpEfficiencyResult {
    /** Corrected average efficiency estimate, dimensionless fraction; not clamped to 0–1. */
    average: number;
    /** Average estimate multiplied by the deviation factor, dimensionless fraction; not clamped to 0–1. */
    max: number;
}

/**
 * Estimates average and maximum pump efficiency using unrounded intermediate values.
 * Evaluates signed, zero and nonfinite inputs directly; no supplied-efficiency override is applied.
 * @param input Complete plain pump-duty input; not modified and requires no delete().
 * @returns Plain average/max efficiency estimates, both dimensionless fractions; no cleanup is required.
 */
export declare function calculatePumpEfficiency(input: PumpEfficiencyInput): PumpEfficiencyResult;

/** Runtime function only; input/result interfaces have no runtime constructors. */
export type PumpEfficiencyModule = {
    calculatePumpEfficiency: typeof calculatePumpEfficiency;
};
