#pragma once
#include <string>
#include "load_charge_material.h"

/**
 * @ingroup gas_load_charge_material_heat_required_calculator
 * @file gas_load_charge_material_heat_required.h
 * @authors Gina Accawi, Mark Root
 *
 * @copybrief gas_load_charge_material_heat_required
 */

/**
 * @ingroup gas_load_charge_material_heat_required_calculator
 * @namespace gas_load_charge_material_heat_required
 * @copybrief gas_load_charge_material_heat_required_calculator
 */

namespace gas_load_charge_material_heat_required {

/**
 * @ingroup gas_load_charge_material_heat_required_calculator
 * @brief Calculates the total heat required for a gas load/charge material.
 * @param[in] thermic_reaction_type Thermic reaction type (endothermic, exothermic, or none)
 * @param[in] specific_heat_gas Specific heat of gas @unitb{\btu\per\pound\degreeFahrenheit}
 * @param[in] feed_rate Feed rate for gas mixture @unitb{\pound\per\hour}
 * @param[in] percent_vapor Vapor in gas mixture (as percent, e.g., 10 for 10%)
 * @param[in] initial_temperature Initial temperature @unitb{\degreeFahrenheit}
 * @param[in] discharge_temperature Discharge temperature @unitb{\degreeFahrenheit}
 * @param[in] specific_heat_vapor Specific heat of vapor @unitb{\btu\per\pound\degreeFahrenheit}
 * @param[in] percent_reacted Feed gas reacted (as percent, e.g., 5 for 5%)
 * @param[in] reaction_heat Heat of reaction @unitb{\btu\per\pound}
 * @param[in] additional_heat Additional heat required @unitb{\btu\per\hour}
 * @return Total heat required @unitb{\btu\per\hour}.
 */
double totalHeatRequired(
  LoadChargeMaterial::ThermicReactionType thermic_reaction_type,
  double specific_heat_gas,
  double feed_rate,
  double percent_vapor,
  double initial_temperature,
  double discharge_temperature,
  double specific_heat_vapor,
  double percent_reacted,
  double reaction_heat,
  double additional_heat
);

} // namespace gas_load_charge_material_heat_required

