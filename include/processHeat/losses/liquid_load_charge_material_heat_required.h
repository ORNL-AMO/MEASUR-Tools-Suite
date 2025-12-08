
#include <string>

#include "load_charge_material.h"

/**
 * @ingroup liquid_load_charge_material_heat_required_calculator
 * @file liquid_load_charge_material_heat_required.h
 * @authors Gina Accawi, Mark Root
 *
 * @copybrief liquid_load_charge_material_heat_required
 */

/**
 * @ingroup liquid_load_charge_material_heat_required_calculator
 * @namespace liquid_load_charge_material_heat_required
 * @brief Namespace for liquid load/charge material heat required calculation.
 */
namespace liquid_load_charge_material_heat_required {

/**
 * @ingroup liquid_load_charge_material_heat_required_calculator
 * @brief Calculates the total heat required for a liquid load/charge material.
 * @param[in] thermic_reaction_type Thermic reaction type (endothermic, exothermic, or none)
 * @param[in] specific_heat_liquid Specific heat of liquid @unitb{\btu\per\pound\degreeFahrenheit}
 * @param[in] vaporizing_temperature Vaporizing temperature @unitb{\degreeFahrenheit}
 * @param[in] latent_heat Latent heat of vaporization @unitb{\btu\per\pound}
 * @param[in] specific_heat_vapor Specific heat of vapor @unitb{\btu\per\pound\degreeFahrenheit}
 * @param[in] charge_feed_rate Charge (liquid) feed rate @unitb{\pound\per\hour}
 * @param[in] initial_temperature Initial temperature @unitb{\degreeFahrenheit}
 * @param[in] discharge_temperature Discharge temperature @unitb{\degreeFahrenheit}
 * @param[in] percent_vaporized Percent of charge vaporized (as percent, e.g., 10 for 10%)
 * @param[in] percent_reacted Percent of charge reacted (as percent, e.g., 5 for 5%)
 * @param[in] reaction_heat Heat of reaction @unitb{\btu\per\pound}
 * @param[in] additional_heat Additional heat required @unitb{\btu\per\hour}
 * @return Total heat required @unitb{\btu\per\hour}.
 */
double totalHeatRequired(
    LoadChargeMaterial::ThermicReactionType thermic_reaction_type,
    double specific_heat_liquid,
    double vaporizing_temperature,
    double latent_heat,
    double specific_heat_vapor,
    double charge_feed_rate,
    double initial_temperature,
    double discharge_temperature,
    double percent_vaporized,
    double percent_reacted,
    double reaction_heat,
    double additional_heat
);

} // namespace liquid_load_charge_material_heat_required
