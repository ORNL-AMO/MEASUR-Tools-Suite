
#include "processHeat/air_heating_using_exhaust.h"
#include <algorithm>
#include "processHeat/losses/solid_liquid_flue_gas_material.h"
#include "physics/constants.h"

namespace air_heating_using_exhaust {


/**
 * @brief Calculates air heating using exhaust for gaseous fuels.
 * @details Uses gas composition to determine fuel heating value and stoichiometric air, then estimates heat recovery.
 * @see airHeatingUsingExhaust for calculation details.
 */
AirHeatingUsingExhaustResults airHeatingUsingExhaustWithGasComposition(
    const gas_composition::GasComposition& gas_composition,
    double flue_temperature,
    double excess_air,
    double fire_rate,
    double airflow,
    double inlet_temperature,
    double heater_efficiency,
    double hx_efficiency,
    double operating_hours
) {
    // Extract fuel properties from gas composition
    const double fuel_heating_value = gas_composition.heating_value_volume;
    const double stoich_air         = gas_composition.stoichometric_air;
    // Delegate to main calculation
    return airHeatingUsingExhaust(stoich_air, fuel_heating_value, flue_temperature, excess_air, fire_rate, airflow,
                                  inlet_temperature, heater_efficiency, hx_efficiency, operating_hours);
}


/**
 * @brief Calculates air heating using exhaust for solid/liquid fuels.
 * @details Uses the provided SolidLiquidFlueGasMaterial to determine fuel heating value and stoichiometric air, then estimates heat recovery.
 * @see airHeatingUsingExhaust for calculation details.
 */
AirHeatingUsingExhaustResults airHeatingUsingExhaustWithSolidLiquidFlueGasMaterial(
    const solid_liquid_flue_gas_material_data::SolidLiquidFlueGasMaterial& material,
    double flue_temperature,
    double excess_air,
    double fire_rate,
    double airflow,
    double inlet_temperature,
    double heater_efficiency,
    double hx_efficiency,
    double operating_hours
) {
    // Calculate fuel heating value from material composition
    const double fuel_heating_value = solid_liquid_flue_gas_material::calculateHeatingValueFuel(
        material.carbon, material.hydrogen, material.sulphur, material.inert_ash, material.oxygen, material.moisture,
        material.nitrogen);
    // Calculate stoichiometric air from material composition
    const double stoich_air = solid_liquid_flue_gas_material::calculateStoichiometricAir(
        material.carbon, material.hydrogen, material.sulphur, material.inert_ash, material.oxygen, material.moisture,
        material.nitrogen);
    // Delegate to main calculation
    return airHeatingUsingExhaust(stoich_air, fuel_heating_value, flue_temperature, excess_air, fire_rate, airflow,
                                  inlet_temperature, heater_efficiency, hx_efficiency, operating_hours);
}


/**
 * @brief Core calculation for air heating using exhaust.
 * @details Computes heat recovery, outlet exhaust temperature, and annual energy savings.
 *
 * Steps:
 * 1. Calculate heat capacity of flue gas and air
 * 2. Calculate heat recovered by cold air
 * 3. Calculate outlet exhaust temperature
 * 4. Calculate annual energy savings
 *
 * All constants are defined in physics::constants.h for clarity and maintainability.
 */
AirHeatingUsingExhaustResults airHeatingUsingExhaust(
    double stoich_air,
    double fuel_heating_value,
    double flue_temperature,
    double excess_air,
    double fire_rate,
    double airflow,
    double inlet_temperature,
    double heater_efficiency,
    double hx_efficiency,
    double operating_hours
) {
    // --- Constants ---
    using namespace physics::conversions;
    constexpr double kFlueFactor = 0.021;        ///< Empirical factor for flue gas heat capacity [unitless]
    constexpr double kAirFactor = 0.0186;        ///< Empirical factor for air heat capacity [unitless]
    constexpr double kStoichDivisor = 32.0;      ///< Empirical divisor for stoichiometric air [unitless]

    // --- Step 1: Calculate heat capacity of flue gas ---
    // Formula: Q_flue = (fire_rate [MMBtu/hr] * 1,000,000 [Btu/MMBtu] * ((1 + excess_air) * stoich_air / 32 + 1) * flue_temperature / fuel_heating_value / 1000) * 0.021
    double flue_capacity_term = ((1.0 + excess_air) * stoich_air / kStoichDivisor + 1.0);
    double heat_capacity_flue = (fire_rate * kMMBtuToBtu * flue_capacity_term * flue_temperature / fuel_heating_value / 1000.0) * kFlueFactor;

    // --- Step 2: Calculate heat capacity of air ---
    // Formula: Q_air = 0.0186 * airflow [scfm] * 60 [min/hr]
    double heat_capacity_air = kAirFactor * airflow * kMinutesPerHour;

    // --- Step 3: Calculate heat recovered by cold air ---
    // Use the smaller of air/flue heat capacity, scaled by HX efficiency and temperature difference
    double limiting_capacity = std::min(heat_capacity_air, heat_capacity_flue);
    double hx_cold_air = hx_efficiency * limiting_capacity * (flue_temperature - inlet_temperature);

    // --- Step 4: Calculate outlet exhaust temperature ---
    double hx_outlet_exhaust = flue_temperature - hx_cold_air / heat_capacity_flue;

    // --- Step 5: Calculate annual energy savings ---
    // Formula: savings = operating_hours * hx_cold_air / heater_efficiency / 1,000,000
    double energy_savings = operating_hours * hx_cold_air / heater_efficiency / kMMBtuToBtu;

    // --- Return results struct ---
    return AirHeatingUsingExhaustResults {
        hx_cold_air, hx_outlet_exhaust, energy_savings, heat_capacity_flue, heat_capacity_air
    };
}

} // namespace air_heating_using_exhaust