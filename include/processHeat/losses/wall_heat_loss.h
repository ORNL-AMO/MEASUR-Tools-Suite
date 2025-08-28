#pragma once
/**
 * @ingroup heat_loss_calculators
 * @file wall_heat_loss.h
 * @authors Gina Accawi, Liam White
 * @brief Defines functions and data structures for calculating heat losses from walls.
 */

#include <string>
#include <vector>

/**
 * @ingroup wall_heat_loss_calculator
 * @namespace wall_heat_loss
 * @brief A collection of functions and data structures for calculating heat losses from walls.
 */
namespace wall_heat_loss {

/**
 * @ingroup wall_heat_loss_calculator
 * @struct ShapeFactor
 * @brief Represents a surface configuration and its associated factor value used in heat loss calculations.
 * @see shape_factors
 */
struct ShapeFactor {
    std::string surface_configuration; ///< Description of the surface shape/orientation/condition.
    double      value;                 ///< Factor value associated with the surface configuration.
};

/**
 * @ingroup wall_heat_loss_calculator
 * @brief A collection of shape factors used in wall heat loss calculations.
 * @see shape_factors
 */
const std::vector<ShapeFactor> kShapeFactors {{"Horizontal cylinders", 1.016},
                                              {"Longer vertical cylinders", 1.235},
                                              {"Vertical plates", 1.394},
                                              {"Horizontal plate facing up, warmer than air", 1.79},
                                              {"Horizontal plate facing down, warmer than air", 0.89},
                                              {"Horizontal plate facing up, cooler than air", 0.89},
                                              {"Horizontal plate facing down, cooler than air", 1.79}};

/**
 * @ingroup wall_heat_loss_calculator
 * @brief Returns the predefined shape factors for wall heat loss calculations.
 * @return A vector of ShapeFactor structs containing surface configurations and their associated factor values.
 * @see shape_factors
 */
inline const std::vector<ShapeFactor>& shapeFactors() { return kShapeFactors; }

/**
 * @ingroup wall_heat_loss_calculator
 * @brief Calculates the total heat loss from a wall to the ambient (convective + radiative).
 * @details Combines convective and radiative heat loss calculations to provide the total heat loss.
 * @param[in] surface_area Total exterior surface area of the wall @unitb{\foot\squared}
 * @param[in] ambient_temperature Ambient temperature measured on the exterior of the wall @unitb{\degreeFahrenheit}
 * @param[in] surface_temperature Average surface temperature measured on the exterior of the wall
 * @unitb{\degreeFahrenheit}
 * @param[in] wind_speed Average wind speed measured on the exterior of the wall @unitb{\mile\per\hour}
 * @param[in] surface_emissivity Surface emissivity of the wall @unitb{\unitless}
 * @param[in] shape_factor The shape factor corresponding to the wall's surface configuration
 * @unitb{\unitless}
 * @param[in] correction_factor Correction factor for the wall heat loss calculations @unitb{\unitless}
 * @return Total heat loss @unitb{\btu\per\hour}.
 * @see wall_total_heat_loss_formula, wall_convective_heat_loss_formula, wall_radiative_heat_loss_formula
 */
double totalHeatLoss(double surface_area, double ambient_temperature, double surface_temperature, double wind_speed,
                     double surface_emissivity, double shape_factor, double correction_factor);

/**
 * @ingroup wall_heat_loss_calculator
 * @brief Computes the convective heat loss from the wall to the ambient.
 * @details Calculates the convective heat loss using an empirical correlation that accounts for surface
 * shape/orientation, duty, temperature difference, mean temperature, and wind speed.
 * @param[in] shape_factor The shape factor corresponding to the wall's surface configuration
 * @unitb{\unitless}
 * @param[in] wind_speed Average wind speed measured on the exterior of the wall @unitb{\mile\per\hour}
 * @param[in] surface_area Total exterior surface area of the wall @unitb{\foot\squared}
 * @param[in] surface_temperature Average surface temperature measured on the exterior of the wall
 * @unitb{\degreeFahrenheit}
 * @param[in] ambient_temperature Ambient temperature measured on the exterior of the wall @unitb{\degreeFahrenheit}
 * @return Convective heat loss @unitb{\btu\per\hour}.
 * @see wall_convective_heat_loss_formula
 */
double convectiveHeatLoss(double shape_factor, double wind_speed, double surface_area, double surface_temperature,
                          double ambient_temperature);

/**
 * @ingroup wall_heat_loss_calculator
 * @brief Calculates the radiative heat loss from the wall to the ambient.
 * @details Calculates the radiative heat loss using the Stefan-Boltzmann law, based on the fourth power of the
 * absolute temperatures of the surface and ambient, the surface area, and the surface emissivity.
 * @param[in] surface_emissivity Surface emissivity of the wall @unitb{\unitless}
 * @param[in] surface_area Total exterior surface area of the wall @unitb{\foot\squared}
 * @param[in] surface_temperature Average surface temperature measured on the exterior of the wall
 * @unitb{\degreeFahrenheit}
 * @param[in] ambient_temperature Ambient temperature measured on the exterior of the wall @unitb{\degreeFahrenheit}
 * @return Radiative heat loss @unitb{\btu\per\hour}
 * @see wall_radiative_heat_loss_formula
 */
double radiativeHeatLoss(double surface_emissivity, double surface_area, double surface_temperature,
                         double ambient_temperature);

} // namespace wall_heat_loss
