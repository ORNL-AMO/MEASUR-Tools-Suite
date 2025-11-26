#pragma once

/**
 * @ingroup opening_heat_loss_calculator
 * @file opening_heat_loss.h
 * @authors Gina Accawi, Mark Root
 *
 * @copybrief opening_heat_loss
 */

/**
 * @ingroup opening_heat_loss_calculator
 * @namespace opening_heat_loss
 * @copybrief opening_heat_loss_calculator
 */
namespace opening_heat_loss {

/**
 * @ingroup opening_heat_loss_calculator
 * @brief Calculates the total heat loss for a process heating equipment opening with a given area.
 * @details This function computes the radiative heat loss from a process heating equipment opening to the surroundings, based on the
 * opening area, surface emissivity, inside and ambient temperatures, view factor, and percent time open. The
 * calculation assumes radiative losses only and does not account for convection or conduction.
 * @param[in] area Area of the opening @unitb{\inch\squared}
 * @param[in] emissivity Emissivity of the opening surface @unitb{\unitless}
 * @param[in] insideTemperature Inside temperature @unitb{\degreeFahrenheit}
 * @param[in] ambientTemperature Ambient temperature @unitb{\degreeFahrenheit}
 * @param[in] viewFactor View factor for radiative heat transfer @unitb{\unitless}
 * @param[in] percentTimeOpen Percentage of time opening is open @unitb{\percent}
 * @return Total heat loss @unitb{\btu\per\hour}
 * @see
 * - opening_heat_loss_formula
 */
double totalHeatLoss(double area, double emissivity, double insideTemperature, double ambientTemperature,
                     double viewFactor, double percentTimeOpen);

/**
 * @ingroup opening_heat_loss_calculator
 * @brief Calculates total heat loss for a rectangular opening.
 * @param[in] emissivity Emissivity of the opening surface @unitb{\unitless}
 * @param[in] length Length of opening @unitb{\inch}
 * @param[in] width Height of opening @unitb{\inch}
 * @param[in] ambientTemperature Ambient temperature @unitb{\degreeFahrenheit}
 * @param[in] insideTemperature Inside temperature @unitb{\degreeFahrenheit}
 * @param[in] percentTimeOpen Percentage of time opening is open @unitb{\percent}
 * @param[in] viewFactor View factor for radiative heat transfer @unitb{\unitless}
 * @return Total heat loss @unitb{\btu\per\hour}
 * @see
 * - opening_quad_heat_loss_formula
 */
double totalHeatLossQuad(double emissivity, double length, double width, double ambientTemperature,
                         double insideTemperature, double percentTimeOpen, double viewFactor);

/**
 * @ingroup opening_heat_loss_calculator
 * @brief Calculates total heat loss for a circlular opening.
 * @param[in] emissivity Emissivity of the opening surface @unitb{\unitless}
 * @param[in] diameter Diameter of opening @unitb{\inch}
 * @param[in] ambientTemperature Ambient temperature @unitb{\degreeFahrenheit}
 * @param[in] insideTemperature Inside temperature @unitb{\degreeFahrenheit}
 * @param[in] percentTimeOpen Percentage of time opening is open @unitb{\percent}
 * @param[in] viewFactor View factor for radiative heat transfer @unitb{\unitless}
 * @return Total heat loss @unitb{\btu\per\hour}
 * @see
 * - opening_circular_heat_loss_formula
 */
double totalHeatLossCircular(double emissivity, double diameter, double ambientTemperature, double insideTemperature,
                             double percentTimeOpen, double viewFactor);

/**
 * @ingroup opening_heat_loss_calculator
 * @brief Calculates the view factor for a circular opening.
 * @param[in] thickness Process heating equipment wall thickness @unitb{\inch}
 * @param[in] diameter Diameter of opening @unitb{\inch}
 * @return View factor for radiative heat transfer @unitb{\unitless}
 * @see
 * - opening_circular_view_factor_formula
 */
double calculateViewFactorCircular(double thickness, double diameter);

/**
 * @ingroup opening_heat_loss_calculator
 * @brief Calculates the view factor for a rectangular opening.
 * @param[in] thickness Process heating equipment wall thickness @unitb{\inch}
 * @param[in] length Length of opening @unitb{\inch}
 * @param[in] height Height of opening @unitb{\inch}
 * @return View factor for radiative heat transfer @unitb{\unitless}
 * @see
 * - opening_quad_view_factor_formula
 */
double calculateViewFactorQuad(double thickness, double length, double height);

} // namespace opening_heat_loss