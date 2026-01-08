
#pragma once

/**
 * @ingroup energy_equivalency_calculator
 * @file energy_equivalency.h
 * 
 * @copybrief energy_equivalency
 */

/**
 * @ingroup energy_equivalency_calculator
 * @namespace energy_equivalency
 * @brief Energy equivalency calculations for process heating systems.
 */
namespace energy_equivalency {

/**
 * @ingroup energy_equivalency_calculator
 * @brief Calculates the equivalent electrical heat input required to replace a fuel-fired furnace.
 * @details Uses the fuel-fired heat input and efficiencies to determine the equivalent electrical input.
 *
 * @param[in] fuel_fired_heat_input Fuel-fired heat input @unitb{MMBtu/hr}
 * @param[in] fuel_fired_efficiency Fuel-fired furnace efficiency @unitb{\percent}
 * @param[in] electrically_heated_efficiency Electrically heated furnace efficiency @unitb{\percent}
 * @return Equivalent electrical heat input @unitb{kW}
 */
double calculateElectricalEquivalentHeatInput(
    double fuel_fired_heat_input,
    double fuel_fired_efficiency,
    double electrically_heated_efficiency
);

/**
 * @ingroup energy_equivalency_calculator
 * @brief Calculates the equivalent fuel-fired heat input required to replace an electrically heated furnace.
 * @details Uses the electrical heat input and efficiencies to determine the equivalent fuel-fired input.
 *
 * @param[in] electrical_heat_input Electrical heat input @unitb{kW}
 * @param[in] electrically_heated_efficiency Electrically heated furnace efficiency @unitb{\percent}
 * @param[in] fuel_fired_efficiency Fuel-fired furnace efficiency @unitb{\percent}
 * @return Equivalent fuel-fired heat input @unitb{MMBtu/hr}
 */
double calculateFuelFiredEquivalentHeatInput(
    double electrical_heat_input,
    double electrically_heated_efficiency,
    double fuel_fired_efficiency
);

} // namespace energy_equivalency
