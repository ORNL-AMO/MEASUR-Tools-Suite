/**
 * Gas Load/Charge Material Heat Required calculations.
 *
 * Calculates the total heat required for a gas load/charge material in a
 * process heating furnace, accounting for sensible heat of the gas and vapor,
 * thermic reactions, and any additional heat required.
 *
 */

import type { ThermicReactionType } from './load_charge_material';

export type { ThermicReactionType };

/**
 * Calculate total heat required for a gas load/charge material.
 *
 * @param thermic_reaction_type {@link ThermicReactionType} - ENDOTHERMIC, EXOTHERMIC, or NONE
 * @param specific_heat_gas Specific heat of gas, units BTU/lb/degF
 * @param feed_rate Feed rate for gas mixture, units lb/hr
 * @param percent_vapor Vapor in gas mixture as percent (e.g. 10 for 10%), units %
 * @param initial_temperature Initial temperature, units degF
 * @param discharge_temperature Discharge temperature, units degF
 * @param specific_heat_vapor Specific heat of vapor, units BTU/lb/degF
 * @param percent_reacted Feed gas reacted as percent (e.g. 5 for 5%), units %
 * @param reaction_heat Heat of reaction, units BTU/lb
 * @param additional_heat Additional heat required, units BTU/hr
 * @returns Total heat required, units BTU/hr
 */
export function gasLoadChargeMaterialTotalHeatRequired(
    thermic_reaction_type: ThermicReactionType,
    specific_heat_gas: number,
    feed_rate: number,
    percent_vapor: number,
    initial_temperature: number,
    discharge_temperature: number,
    specific_heat_vapor: number,
    percent_reacted: number,
    reaction_heat: number,
    additional_heat: number
): number;

export type GasLoadChargeMaterialHeatRequiredModule = {
    ThermicReactionType: typeof ThermicReactionType;
    gasLoadChargeMaterialTotalHeatRequired: typeof gasLoadChargeMaterialTotalHeatRequired;
};
