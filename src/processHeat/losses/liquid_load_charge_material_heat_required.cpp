#include "processHeat/losses/liquid_load_charge_material_heat_required.h"

namespace liquid_load_charge_material_heat_required {

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
) {
    // Convert percent inputs to fractions
    const double vaporized_fraction = percent_vaporized / 100.0;
    const double reacted_fraction   = percent_reacted / 100.0;

    // Step 1: Sensible heat to discharge temperature (if below vaporizing temp)
    double sensible_heat_liquid = 0.0;
    double vaporization_heat = 0.0;
    double sensible_heat_vapor = 0.0;
    double sensible_heat_remaining_liquid = 0.0;

    if (discharge_temperature < vaporizing_temperature) {
        sensible_heat_liquid = charge_feed_rate * specific_heat_liquid * (discharge_temperature - initial_temperature);
    } else {
        // Step 2: Sensible heat to vaporizing temperature
        sensible_heat_liquid = charge_feed_rate * specific_heat_liquid * (vaporizing_temperature - initial_temperature);

        // Step 3: Vaporization heat for vaporized fraction
        vaporization_heat = charge_feed_rate * vaporized_fraction * latent_heat;

        // Step 4: Sensible heat for vaporized fraction (vapor)
        sensible_heat_vapor = charge_feed_rate * vaporized_fraction * specific_heat_vapor * (discharge_temperature - vaporizing_temperature);

        // Step 5: Sensible heat for remaining liquid fraction
        sensible_heat_remaining_liquid = charge_feed_rate * (1.0 - vaporized_fraction) * specific_heat_liquid * (discharge_temperature - vaporizing_temperature);
    }

    // Step 6: Heat of reaction (endothermic only)
    double reaction_heat_total = 0.0;
    if (thermic_reaction_type == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
        reaction_heat_total = charge_feed_rate * reacted_fraction * reaction_heat;
    }

    // Step 7: Sum all heat contributions
    double total_heat_required = 0.0;
    if (discharge_temperature < vaporizing_temperature) {
        total_heat_required = sensible_heat_liquid + reaction_heat_total + additional_heat;
    } else {
        total_heat_required = sensible_heat_liquid + vaporization_heat + sensible_heat_vapor + sensible_heat_remaining_liquid + reaction_heat_total + additional_heat;
    }

    return total_heat_required;
}

} // namespace liquid_load_charge_material_heat_required
