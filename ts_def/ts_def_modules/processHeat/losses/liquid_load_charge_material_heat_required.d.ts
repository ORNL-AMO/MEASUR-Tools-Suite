/**
 * Liquid Load/Charge Material Heat Required calculations.
 *
 * Calculates the total heat required for a liquid load/charge material in a
 * process heating furnace, accounting for sensible heat of the liquid and
 * vapor phases, latent heat of vaporization, thermic reactions, and any
 * additional heat required.
 *
 */

import type { ThermicReactionType } from './load_charge_material';

export type { ThermicReactionType };

/**
 * Calculate total heat required for a liquid load/charge material.
 *
 * @param thermic_reaction_type {@link ThermicReactionType} - ENDOTHERMIC, EXOTHERMIC, or NONE
 * @param specific_heat_liquid Specific heat of liquid, units BTU/lb/degF
 * @param vaporizing_temperature Vaporizing temperature, units degF
 * @param latent_heat Latent heat of vaporization, units BTU/lb
 * @param specific_heat_vapor Specific heat of vapor, units BTU/lb/degF
 * @param charge_feed_rate Charge (liquid) feed rate, units lb/hr
 * @param initial_temperature Initial temperature, units degF
 * @param discharge_temperature Discharge temperature, units degF
 * @param percent_vaporized Percent of charge vaporized (e.g. 10 for 10%), units %
 * @param percent_reacted Percent of charge reacted (e.g. 5 for 5%), units %
 * @param reaction_heat Heat of reaction, units BTU/lb
 * @param additional_heat Additional heat required, units BTU/hr
 * @returns Total heat required, units BTU/hr
 */
export function liquidLoadChargeMaterialTotalHeatRequired(
    thermic_reaction_type: ThermicReactionType,
    specific_heat_liquid: number,
    vaporizing_temperature: number,
    latent_heat: number,
    specific_heat_vapor: number,
    charge_feed_rate: number,
    initial_temperature: number,
    discharge_temperature: number,
    percent_vaporized: number,
    percent_reacted: number,
    reaction_heat: number,
    additional_heat: number
): number;

export type LiquidLoadChargeMaterialHeatRequiredModule = {
    ThermicReactionType: typeof ThermicReactionType;
    liquidLoadChargeMaterialTotalHeatRequired: typeof liquidLoadChargeMaterialTotalHeatRequired;
};
