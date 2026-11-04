/** Empirical achievable average and maximum pump-efficiency estimates for a supplied pump duty. */
import type { PumpStyle } from "./pump_enums";

/** Plain required pump-duty input; no defaults, unit conversion or cleanup. */
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
    /** Corrected average, dimensionless fraction; NaN when unavailable; not clamped to 0–1. */
    average: number;
    /** Maximum estimate, dimensionless fraction; NaN when unavailable; not clamped to 0–1. */
    max: number;
}

/** Plain inclusive reference limits derived from the HI 2020 calculation tables. */
export interface PumpEfficiencyLimits {
    /** Whether this pump style supports an HI estimate. */
    supported: boolean;
    /** Minimum flow, units US gpm; NaN if unsupported. */
    minimumFlowRate: number;
    /** Maximum flow, units US gpm; NaN if unsupported. */
    maximumFlowRate: number;
    /** Minimum specific speed, units rpm*sqrt(US gpm)/ft^(3/4); NaN if unsupported. */
    minimumSpecificSpeed: number;
    /** Maximum specific speed, units rpm*sqrt(US gpm)/ft^(3/4); NaN if unsupported. */
    maximumSpecificSpeed: number;
}

/**
 * Returns the inclusive HI 2020 flow/specific-speed limits for the selected style.
 * @param style Unitless pump-style classification.
 * @returns Plain supported flag and bounds in US gpm / US customary specific speed; no cleanup.
 */
export declare function getPumpEfficiencyLimits(style: PumpStyle): PumpEfficiencyLimits;

/**
 * Estimates average and maximum pump efficiency using unrounded intermediate values.
 * Returns both fields as NaN for unavailable estimates or invalid duties. No extrapolation.
 * Supplied-efficiency and positive-displacement styles bypass HI estimation and are unavailable here.
 * @param input Complete plain pump-duty input; not modified and requires no delete().
 * @returns Plain average/max efficiency estimates, both dimensionless fractions; no cleanup is required.
 */
export declare function calculatePumpEfficiency(input: PumpEfficiencyInput): PumpEfficiencyResult;

/** Runtime function only; input/result interfaces have no runtime constructors. */
export type PumpEfficiencyModule = {
    calculatePumpEfficiency: typeof calculatePumpEfficiency;
    getPumpEfficiencyLimits: typeof getPumpEfficiencyLimits;
};
