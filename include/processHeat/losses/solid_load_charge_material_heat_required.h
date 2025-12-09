#pragma once
#include <string>
#include "load_charge_material.h"

/**
 * @ingroup solid_load_charge_material_heat_required_calculator
 * @file solid_load_charge_material_heat_required.h
 * @authors Mark Adams, Gina Accawi
 * @brief Calculates total heat required for a solid load/charge material.
 * @details Computes the total heat required for a solid load/charge material using sensible heat, latent heat, melting, reaction heat, and additional heat.
 */

/**
 * @ingroup solid_load_charge_material_heat_required_calculator
 * @namespace solid_load_charge_material_heat_required
 * @brief Namespace for solid load/charge material heat required calculation.
 */
namespace solid_load_charge_material_heat_required {

/**
 * @brief Calculates the total heat required for a solid load/charge material.
 * @param thermic_reaction_type Thermic reaction type (endothermic, exothermic, or none)
 * @param specific_heat_solid Average specific heat of solid material (dry) @unitb{\btu\per\pound\degreeFahrenheit}
 * @param latent_heat Latent heat of fusion @unitb{\btu\per\pound}
 * @param specific_heat_liquid Specific heat of liquid from molten material @unitb{\btu\per\pound\degreeFahrenheit}
 * @param melting_point Melting point @unitb{\degreeFahrenheit}
 * @param charge_feed_rate Charge (wet) feed rate @unitb{\pound\per\hour}
 * @param water_content_charged Water content as charged (percent, e.g., 10 for 10%)
 * @param water_content_discharged Water content as discharged (percent, e.g., 5 for 5%)
 * @param initial_temperature Initial temperature @unitb{\degreeFahrenheit}
 * @param discharge_temperature Charge material discharge temperature @unitb{\degreeFahrenheit}
 * @param water_vapor_discharge_temperature Water vapor discharge temperature @unitb{\degreeFahrenheit}
 * @param charge_melted Charge melted (percent of dry charge, e.g., 10 for 10%)
 * @param charge_reacted Charge reacted (percent of dry charge, e.g., 5 for 5%)
 * @param reaction_heat Heat of reaction @unitb{\btu\per\pound}
 * @param additional_heat Additional heat required @unitb{\btu\per\hour}
 * @return Total heat required @unitb{\btu\per\hour}.
 */
double totalHeatRequired(
    LoadChargeMaterial::ThermicReactionType thermic_reaction_type,
    double specific_heat_solid,
    double latent_heat,
    double specific_heat_liquid,
    double melting_point,
    double charge_feed_rate,
    double water_content_charged,
    double water_content_discharged,
    double initial_temperature,
    double discharge_temperature,
    double water_vapor_discharge_temperature,
    double charge_melted,
    double charge_reacted,
    double reaction_heat,
    double additional_heat
);

} // namespace solid_load_charge_material_heat_required

