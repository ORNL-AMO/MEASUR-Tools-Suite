#include "processHeat/losses/solid_load_charge_material_heat_required.h"
#include "physics/constants.h"

namespace solid_load_charge_material_heat_required {

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
) {
    // Convert percent inputs to fractions
    const double water_charged_frac = water_content_charged / 100.0;
    const double water_discharged_frac = water_content_discharged / 100.0;
    const double charge_melted_frac = charge_melted / 100.0;
    const double charge_reacted_frac = charge_reacted / 100.0;

    // Water constants from physics::us
    using namespace physics::us;

    // Step 1: Heat required for removal of moisture
    double heat_moisture_vapor = 0.0;
    if (water_vapor_discharge_temperature < kWaterBoilingPointF) {
        // Only sensible heat up to discharge temperature
        double sensible_heat_to_discharge = charge_feed_rate * water_charged_frac * (water_vapor_discharge_temperature - initial_temperature);
        heat_moisture_vapor = sensible_heat_to_discharge;
    } else {
        // Sensible heat to boiling point
        double sensible_heat_to_boiling = charge_feed_rate * water_charged_frac * (kWaterBoilingPointF - initial_temperature);

        // Vaporization heat for moisture removed
        double vaporization_heat = charge_feed_rate * (water_charged_frac - water_discharged_frac) * kWaterEvaporation;

        // Sensible heat for vapor above boiling point
        double sensible_heat_vapor_above_boiling = charge_feed_rate * (water_charged_frac - water_discharged_frac) * kSpecificHeatWaterVapor * (water_vapor_discharge_temperature - kWaterBoilingPointF);

        // Final summation
        heat_moisture_vapor = sensible_heat_to_boiling + vaporization_heat + sensible_heat_vapor_above_boiling;
    }

    // Step 2: Heat required for remaining moisture
    double heat_moisture_remaining = charge_feed_rate * water_discharged_frac * (water_vapor_discharge_temperature - kWaterBoilingPointF);

    // Step 3: Heat required for solid
    double heat_solid = 0.0;
    if (discharge_temperature < melting_point) {
        // Only sensible heat up to discharge temperature
        heat_solid = charge_feed_rate * (1.0 - water_charged_frac) * specific_heat_solid * (discharge_temperature - initial_temperature);
    } else {
        // Sensible heat to melting point
        double sensible_heat_to_melting = specific_heat_solid * (melting_point - initial_temperature);

        // Latent heat for melted fraction
        double latent_heat_melting = latent_heat * charge_melted_frac;

        // Sensible heat for liquid fraction above melting point
        double sensible_heat_liquid_above_melting = specific_heat_liquid * (discharge_temperature - melting_point) * charge_melted_frac;

        // Sensible heat for remaining solid fraction above melting point
        double sensible_heat_remaining_solid = specific_heat_solid * (1.0 - charge_melted_frac) * (discharge_temperature - melting_point);

        // Final summation
        heat_solid = charge_feed_rate * (1.0 - water_charged_frac) * (
            sensible_heat_to_melting +
            latent_heat_melting +
            sensible_heat_liquid_above_melting +
            sensible_heat_remaining_solid
        );
    }

    // Step 4: Heat of reaction (endothermic only)
    double heat_reaction = 0.0;
    if (thermic_reaction_type == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
        heat_reaction = charge_feed_rate * (1.0 - water_charged_frac) * charge_reacted_frac * reaction_heat;
    }

    // Step 5: Sum all heat contributions
    double total_heat_required = heat_moisture_vapor + heat_moisture_remaining + heat_solid + heat_reaction + additional_heat;
    return total_heat_required;
}

} // namespace solid_load_charge_material_heat_required
