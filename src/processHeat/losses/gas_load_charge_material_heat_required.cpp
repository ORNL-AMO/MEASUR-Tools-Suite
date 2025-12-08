#include "processHeat/losses/gas_load_charge_material_heat_required.h"

namespace gas_load_charge_material_heat_required {

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
) {
	// Convert percent inputs to fractions
	double vapor_frac   = percent_vapor / 100.0;
	double reacted_frac = percent_reacted / 100.0;

	// Temperature difference
	double temp_diff = discharge_temperature - initial_temperature;

	// Sensible heat for gas and vapor
	double heat_gas   = (1.0 - vapor_frac) * feed_rate * specific_heat_gas * temp_diff;
	double heat_vapor = vapor_frac * feed_rate * specific_heat_vapor * temp_diff;

	// Heat of reaction (only for endothermic)
	double heat_reaction = 0.0;
	if (thermic_reaction_type == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
		heat_reaction = feed_rate * reacted_frac * reaction_heat;
	}

	// Total heat required
	double total_heat_required = heat_gas + heat_vapor + heat_reaction + additional_heat;
	return total_heat_required;
}

} // namespace gas_load_charge_material_heat_required
