import type { PumpStyle } from "./pump_enums";

/** Plain required input for the flow/style estimate before viscosity and specific-speed corrections. */
export interface OptimalPrePumpEfficiencyInput {
    /** Unitless pump-style classification from the shared runtime PumpStyle enum. */
    style: PumpStyle;
    /** Liquid volumetric flow, units US gpm, within the selected HI 2020 table range. */
    flowRate: number;
}

/**
 * Estimates pump efficiency before viscosity and specific-speed corrections.
 * PCHIP interpolates HI 2020 reference points without extrapolation; endpoints are inclusive.
 * Returns NaN for nonfinite/out-of-range flow or unsupported styles. Axial flow uses V's base table.
 * @param input Plain pump-style/flow input; not modified and requires no delete().
 * @returns Efficiency in percent, not a fraction; numeric result requires no cleanup.
 */
export declare function calculateOptimalPrePumpEfficiency(input: OptimalPrePumpEfficiencyInput): number;

/** Runtime function only; the input interface is type-only, with no runtime constructor. */
export type OptimalPrePumpEfficiencyModule = {
    calculateOptimalPrePumpEfficiency: typeof calculateOptimalPrePumpEfficiency;
};
