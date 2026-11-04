import type { MeasurToolsSuite, PumpStyle } from 'measur-tools-suite';

/** Resolve runtime enums explicitly rather than passing native numeric enum ordinals to embind. */
export function pumpStyles(module: MeasurToolsSuite): PumpStyle[] {
    return [module.PumpStyle.END_SUCTION_SLURRY, module.PumpStyle.END_SUCTION_SEWAGE,
        module.PumpStyle.END_SUCTION_STOCK, module.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE,
        module.PumpStyle.API_DOUBLE_SUCTION, module.PumpStyle.MULTISTAGE_BOILER_FEED,
        module.PumpStyle.END_SUCTION_ANSI_API, module.PumpStyle.AXIAL_FLOW,
        module.PumpStyle.DOUBLE_SUCTION, module.PumpStyle.VERTICAL_TURBINE,
        module.PumpStyle.LARGE_END_SUCTION, module.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY,
        module.PumpStyle.POSITIVE_DISPLACEMENT];
}
