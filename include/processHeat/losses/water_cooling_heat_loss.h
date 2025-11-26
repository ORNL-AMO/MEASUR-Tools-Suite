#pragma once

/**
 * @ingroup water_cooling_heat_loss_calculator
 * @file water_cooling_heat_loss.h
 * @authors Gina Accawi, Mark Root
 *
 * @copybrief water_cooling_heat_loss
 */

/**
 * @ingroup water_cooling_heat_loss_calculator
 * @namespace water_cooling_heat_loss
 * @copybrief water_cooling_heat_loss_calculator
 */
namespace water_cooling_heat_loss {

/**
 * @ingroup water_cooling_heat_loss_calculator
 * @brief Calculates the total heat loss due to water cooling in process heating equipment.
 * @details This function computes the heat loss removed by water cooling, based on flow rate, initial temperature, outlet temperature, and a correction factor. The calculation assumes no phase change and uses sensible heat only.
 * @param[in] flowRate Cooling water flow rate @unitb{\gallon\per\minute}
 * @param[in] initialTemperature Initial/inlet water temperature @unitb{\degreeFahrenheit}
 * @param[in] outletTemperature Outlet water temperature @unitb{\degreeFahrenheit}
 * @param[in] correctionFactor Correction factor @unitb{\unitless}
 * @return Total heat loss @unitb{\btu\per\hour}
 * @see
 * - water_cooling_heat_loss_formula
 */
double totalHeatLoss(double flowRate, double initialTemperature, double outletTemperature, double correctionFactor);
}// namespace water_cooling_heat_loss