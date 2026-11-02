import type { PumpStyle } from "./pump_enums";

/** Plain required input for the flow/style estimate before viscosity and specific-speed corrections. */
export interface OptimalPrePumpEfficiencyInput {
    /** Unitless pump-style classification from the shared runtime PumpStyle enum. */
    style: PumpStyle;
    /** Liquid volumetric flow, units US gpm. No validation, conversion or clamping is applied. */
    flowRate: number;
}

/**
 * Estimates pump efficiency before viscosity and specific-speed corrections.
 * Equality at a flow threshold selects the upper interval. Specified-optimal and positive-displacement
 * styles return zero for every flow. Other styles evaluate the empirical curves directly, including
 * zero, negative and nonfinite flows. No defaults, validation or clamping are applied.
 * @param input Plain pump-style/flow input; not modified and requires no delete().
 * @returns Efficiency in percent, not a fraction; numeric result requires no cleanup.
 */
export declare function calculateOptimalPrePumpEfficiency(input: OptimalPrePumpEfficiencyInput): number;

/** Runtime function only; the input interface is type-only, with no runtime constructor. */
export type OptimalPrePumpEfficiencyModule = {
    calculateOptimalPrePumpEfficiency: typeof calculateOptimalPrePumpEfficiency;
};
