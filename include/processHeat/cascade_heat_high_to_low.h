
#pragma once

/**
 * @ingroup process_heat
 * @file cascade_heat_high_to_low.h
 * @authors Omer Aziz (omerb)
 * @brief Functions to calculate energy savings from using exhaust gas (waste) of high temperature to supply heat to low temperature equipment.
 * @details Provides a function-based API for cascade heat recovery calculations.
 * @bug No known bugs.
 */

#include "physics/gas_composition.h"
#include "losses/gas_flue_gas_material.h"

/**
 * @ingroup process_heat
 * @namespace cascade_heat_high_to_low
 * @brief Cascade heat recovery calculations for process heating systems.
 */
namespace cascade_heat_high_to_low {

/**
 * @ingroup process_heat
 * @struct CascadeHeatHighToLowResults
 * @brief Results of the cascade heat high-to-low calculation.
 * @details Contains all output values from the cascade heat recovery calculation.
 */
struct CascadeHeatHighToLowResults {
    double pri_flue_volume = 0;      ///< Primary flue gas volume @unitb{SCF/hr}
    double hx_energy_rate = 0;       ///< Heat exchanger energy rate @unitb{MMBtu/hr}
    double eq_energy_supply = 0;     ///< Equivalent energy supply @unitb{MMBtu/hr}
    double eff_op_hours = 0;         ///< Effective operating hours @unitb{hr/yr}
    double energy_savings = 0;       ///< Total energy savings @unitb{MMBtu/yr}
    double cost_savings = 0;         ///< Total cost savings @unitb{USD/yr}
    double hourly_savings = 0;       ///< Hourly energy savings @unitb{MMBtu/hr}
    double pri_excess_air = 0;       ///< Primary excess air (fraction)
    double pri_available_heat = 0;   ///< Primary available heat (fraction)
    double sec_excess_air = 0;       ///< Secondary excess air (fraction)
    double sec_available_heat = 0;   ///< Secondary available heat (fraction)
};

/**
 * @brief Calculates the energy and cost savings from cascading heat from a high-temperature to a low-temperature process.
 * @details Uses flue gas properties and process parameters to estimate the benefit of using waste heat from a primary (high-temp) process to supply heat to a secondary (low-temp) process.
 *
 * @param[in] gas_compositions Fuel gas composition for flue gas calculations.
 * @param[in] fuel_hv Fuel heating value @unitb{Btu/SCF}
 * @param[in] fuel_cost Fuel cost @unitb{USD/MMBtu}
 * @param[in] pri_firing_rate Primary process firing rate @unitb{MMBtu/hr}
 * @param[in] pri_exhaust_temp Primary process exhaust temperature @unitb{\degreeFahrenheit}
 * @param[in] pri_exhaust_o2 Primary process exhaust O2 (fraction)
 * @param[in] pri_comb_air_temp Primary process combustion air temperature @unitb{\degreeFahrenheit}
 * @param[in] pri_op_hours Primary process operating hours @unitb{hr/yr}
 * @param[in] sec_firing_rate Secondary process firing rate @unitb{MMBtu/hr}
 * @param[in] sec_exhaust_temp Secondary process exhaust temperature @unitb{\degreeFahrenheit}
 * @param[in] sec_exhaust_o2 Secondary process exhaust O2 (fraction)
 * @param[in] sec_comb_air_temp Secondary process combustion air temperature @unitb{\degreeFahrenheit}
 * @param[in] sec_op_hours Secondary process operating hours @unitb{hr/yr}
 * @param[in] fuel_temp_f Fuel temperature @unitb{\degreeFahrenheit} (default: 60)
 * @param[in] ambient_air_temp_f Ambient air temperature @unitb{\degreeFahrenheit} (default: 60)
 * @param[in] comb_air_moisture_perc Combustion air moisture percent (default: 0)
 * @return CascadeHeatHighToLowResults struct with all calculated outputs.
 */
CascadeHeatHighToLowResults calculateCascadeHeatHighToLow(
    const gas_composition::GasComposition& gas_compositions,
    double fuel_hv,
    double fuel_cost,
    double pri_firing_rate,
    double pri_exhaust_temp,
    double pri_exhaust_o2,
    double pri_comb_air_temp,
    double pri_op_hours,
    double sec_firing_rate,
    double sec_exhaust_temp,
    double sec_exhaust_o2,
    double sec_comb_air_temp,
    double sec_op_hours,
    double fuel_temp_f = 60,
    double ambient_air_temp_f = 60,
    double comb_air_moisture_perc = 0
);

} // namespace cascade_heat_high_to_low

