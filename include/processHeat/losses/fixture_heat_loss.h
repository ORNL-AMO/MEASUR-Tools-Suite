#pragma once

/**
 * @ingroup fixture_heat_loss_calculator
 * @file fixture_heat_loss.h
 * @authors Gina Accawi, Liam White
 *
 * @copybrief fixture_heat_loss
 */

/**
 * @ingroup fixture_heat_loss_calculator
 * @namespace fixture_heat_loss
 * @copybrief fixture_heat_loss_calculator
 */
namespace fixture_heat_loss {

/**
 * @ingroup fixture_heat_loss_calculator
 * @brief Calculates the total heat loss from fixtures, trays, or conveyors.
 * @details This function computes the heat loss caused by fixtures, trays, conveyor belts, and similar equipment that
 * enter the furnace at lower temperatures and are heated to the furnace temperature. The calculation assumes there is
 * no melting or phase change of the fixture material involved.
 * @param[in] specific_heat Specific heat of fixture material @unitb{\btu\per\pound\degreeFahrenheit}
 * @param[in] feed_rate Feed rate of fixture material @unitb{\pound\per\hour}
 * @param[in] initial_temperature Initial temperature of fixture @unitb{\degreeFahrenheit}
 * @param[in] final_temperature Final temperature of fixture @unitb{\degreeFahrenheit}
 * @param[in] correction_factor Correction factor @unitb{\unitless}
 * @return Total heat loss @unitb{\btu\per\hour}
 * @see
 * - fixture_heat_loss_formula
 */
double totalHeatLoss(double specific_heat, double feed_rate, double initial_temperature, double final_temperature,
                     double correction_factor);

} // namespace fixture_heat_loss
