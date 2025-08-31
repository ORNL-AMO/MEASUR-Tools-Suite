/**
 * @file constants.h
 * @authors Liam White
 * @brief Defines physical constants and unit conversions.
 * @details https://physics.nist.gov/cuu/Constants/index.html
 */
#pragma once

/**
 * @namespace physics
 * @brief Contains physical constants and unit conversions.
 */

/**
 *  @namespace physics::si
 *  @brief Physical constants defined in Standard International (SI) units.
 */
namespace physics::si {

/// @brief Stefan–Boltzmann constant @unit{\watt\per\meter\squared\kelvin\tothe{4}}
inline constexpr double kStefanBoltzmann = 5.670374419e-8;

} // namespace physics::si

/**
 * @namespace physics::imperial
 * @brief Physical constants defined in British Imperial units.
 */
namespace physics::imperial {}

/**
 * @namespace physics::customary
 * @brief Physical constants defined in U.S. Customary units.
 */
namespace physics::customary {

/// @brief Stefan–Boltzmann constant @unit{\btu\per\hour\foot\squared\degreeRankine\tothe{4}}
inline constexpr double kStefanBoltzmann = 1.713441e-9;

} // namespace physics::customary

/**
 * @namespace physics::conversions
 * @brief Factors and functions for unit conversions.
 */
namespace physics::conversions {

/// @brief Offset to convert Fahrenheit to Rankine.
inline constexpr double kFahrenheitToRankineOffset = 459.67;

/// @brief Number of hours in a day.
inline constexpr double kHoursPerDay = 24.0;

/**
 * @brief Convert Fahrenheit to Rankine.
 * @details Converts a temperature from degrees Fahrenheit to degrees Rankine:
 *
 * @formula{fahrenheit-to-rankine; T_R = T_F + 459.67}
 *
 * @b Symbols
 * - @symbol{T_R; is the temperature in degrees Rankine} @unit{\degreeRankine}
 * - @symbol{T_F; is the temperature in degrees Fahrenheit} @unit{\degreeFahrenheit}
 *
 * @param[in] fahrenheit Temperature in degrees Fahrenheit @unit{\degreeFahrenheit}.
 * @return Temperature in degrees Rankine.
 */
constexpr double fahrenheitToRankine(double fahrenheit) { return fahrenheit + kFahrenheitToRankineOffset; }

} // namespace physics::conversions
