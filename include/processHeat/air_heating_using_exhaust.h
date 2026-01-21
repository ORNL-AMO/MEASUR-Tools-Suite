#pragma once
#include "physics/gas_composition.h"
#include "databases/solid_liquid_flue_gas_material_data.h"

/**
 * @ingroup air_heating_using_exhaust_calculator
 * @file air_heating_using_exhaust.h
 *
 * @copybrief air_heating_using_exhaust
 */

/**
 * @ingroup air_heating_using_exhaust_calculator
 * @namespace air_heating_using_exhaust
 * @brief Air heating using exhaust calculations for process heating systems.
 */
namespace air_heating_using_exhaust {

/**
 * @ingroup air_heating_using_exhaust_calculator
 * @struct AirHeatingUsingExhaustResults
 * @brief Results of the air heating using exhaust calculation.
 * @details Contains all output values from the air heating using exhaust calculation.
 */
struct AirHeatingUsingExhaustResults {
  double hx_cold_air = 0;         ///< Heat recovered by cold air @unitb{Btu/hr}
  double hx_outlet_exhaust = 0;   ///< Outlet exhaust temperature @unitb{\degreeFahrenheit}
  double energy_savings = 0;      ///< Annual energy savings @unitb{MMBtu/yr}
  double heat_capacity_flue = 0;  ///< Heat capacity of flue gas
  double heat_capacity_air = 0;   ///< Heat capacity of air
};

/**
 * @ingroup air_heating_using_exhaust_calculator
 * @brief Calculates air heating using exhaust for gaseous fuels.
 * @details Uses gas composition to determine fuel heating value and stoichiometric air, then estimates heat recovery.
 *
 * @param gas_composition GasComposition object with fuel properties
 * @param flue_temperature Flue gas temperature @unitb{\degreeFahrenheit}
 * @param excess_air Excess air (fraction)
 * @param fire_rate Firing rate @unitb{MMBtu/hr}
 * @param airflow Air flow @unitb{scfm}
 * @param inlet_temperature Inlet air temperature @unitb{\degreeFahrenheit}
 * @param heater_efficiency Heater efficiency (fraction)
 * @param hx_efficiency Heat exchanger efficiency (fraction)
 * @param operating_hours Annual operating hours @unitb{hr}
 * @return AirHeatingUsingExhaustResults struct with all calculated outputs.
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
);

/**
 * @ingroup air_heating_using_exhaust_calculator
 * @brief Calculates air heating using exhaust for solid/liquid fuels.
 * @details Uses the provided SolidLiquidFlueGasMaterial to determine fuel heating value and stoichiometric air, then estimates heat recovery.
 *
 * @param material SolidLiquidFlueGasMaterial object with fuel composition and properties
 * @param flue_temperature Flue gas temperature @unitb{\degreeFahrenheit}
 * @param excess_air Excess air (fraction)
 * @param fire_rate Firing rate @unitb{MMBtu/hr}
 * @param airflow Air flow @unitb{scfm}
 * @param inlet_temperature Inlet air temperature @unitb{\degreeFahrenheit}
 * @param heater_efficiency Heater efficiency (fraction)
 * @param hx_efficiency Heat exchanger efficiency (fraction)
 * @param operating_hours Annual operating hours @unitb{hr}
 * @return AirHeatingUsingExhaustResults struct with all calculated outputs.
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
);

/**
 * @brief Internal calculation for air heating using exhaust, given stoichiometric air and fuel heating value.
 * @details Used by public API functions for both gas and solid/liquid fuels.
 *
 * @param stoich_air Stoichiometric air required
 * @param fuel_heating_value Fuel heating value
 * @param flue_temperature Flue gas temperature @unitb{\degreeFahrenheit}
 * @param excess_air Excess air (fraction)
 * @param fire_rate Firing rate @unitb{MMBtu/hr}
 * @param airflow Air flow @unitb{scfm}
 * @param inlet_temperature Inlet air temperature @unitb{\degreeFahrenheit}
 * @param heater_efficiency Heater efficiency (fraction)
 * @param hx_efficiency Heat exchanger efficiency (fraction)
 * @param operating_hours Annual operating hours @unitb{hr}
 * @return AirHeatingUsingExhaustResults struct with all calculated outputs.
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
);

} // namespace air_heating_using_exhaust

