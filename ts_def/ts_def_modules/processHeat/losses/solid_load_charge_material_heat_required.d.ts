/**
 * Solid Load/Charge Material Heat Required calculations.
 *
 * Calculates the total heat required for a solid load/charge material in a
 * process heating furnace, accounting for sensible heat of the solid and
 * liquid phases, latent heat of fusion, water evaporation, thermic reactions,
 * and any additional heat required.
 *
 */

import type { ThermicReactionType } from './load_charge_material';

export type { ThermicReactionType };

/**
 * Calculate total heat required for a solid load/charge material.
 *
 * Computes total heat using sensible heat, latent heat of fusion, melting,
 * water content evaporation, reaction heat, and additional heat.
 *
 * @param thermic_reaction_type {@link ThermicReactionType} - ENDOTHERMIC, EXOTHERMIC, or NONE
 * @param specific_heat_solid Average specific heat of solid material (dry), units BTU/lb/degF
 * @param latent_heat Latent heat of fusion, units BTU/lb
 * @param specific_heat_liquid Specific heat of liquid from molten material, units BTU/lb/degF
 * @param melting_point Melting point, units degF
 * @param charge_feed_rate Charge (wet) feed rate, units lb/hr
 * @param water_content_charged Water content as charged (e.g. 10 for 10%), units %
 * @param water_content_discharged Water content as discharged (e.g. 5 for 5%), units %
 * @param initial_temperature Initial temperature, units degF
 * @param discharge_temperature Charge material discharge temperature, units degF
 * @param water_vapor_discharge_temperature Water vapor discharge temperature, units degF
 * @param charge_melted Charge melted as percent of dry charge (e.g. 10 for 10%), units %
 * @param charge_reacted Charge reacted as percent of dry charge (e.g. 5 for 5%), units %
 * @param reaction_heat Heat of reaction, units BTU/lb
 * @param additional_heat Additional heat required, units BTU/hr
 * @returns Total heat required, units BTU/hr
 */
export function solidLoadChargeMaterialTotalHeatRequired(
    thermic_reaction_type: ThermicReactionType,
    specific_heat_solid: number,
    latent_heat: number,
    specific_heat_liquid: number,
    melting_point: number,
    charge_feed_rate: number,
    water_content_charged: number,
    water_content_discharged: number,
    initial_temperature: number,
    discharge_temperature: number,
    water_vapor_discharge_temperature: number,
    charge_melted: number,
    charge_reacted: number,
    reaction_heat: number,
    additional_heat: number
): number;

export type SolidLoadChargeMaterialHeatRequiredModule = {
    ThermicReactionType: typeof ThermicReactionType;
    solidLoadChargeMaterialTotalHeatRequired: typeof solidLoadChargeMaterialTotalHeatRequired;
};
