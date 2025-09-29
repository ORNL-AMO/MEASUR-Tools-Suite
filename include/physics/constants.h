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

/// @brief Stefan–Boltzmann constant @unitb{\watt\per\meter\squared\kelvin\tothe{4}}
inline constexpr double kStefanBoltzmann = 5.670374419e-8;

} // namespace physics::si

/**
 * @namespace physics::imperial
 * @brief Physical constants defined in British Imperial units.
 */
namespace physics::imperial {}

/**
 * @namespace physics::us
 * @brief Physical constants defined in U.S. Customary units.
 */
namespace physics::us {

/**
 * @brief Stefan–Boltzmann constant @unitb{\btu\per\hour\foot\squared\degreeRankine\tothe{4}}
 * @details Source: @cite capehart2007guide
 */
inline constexpr double kStefanBoltzmann = 1.713441e-9;

} // namespace physics::us

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
 * @par Relation
 * @formula{fahrenheit-to-rankine; T_R = T_F + 459.67}
 *
 * @par Symbols
 * @symtable
 * @symrow{T_R; Temperature in degrees Rankine; \degreeRankine}
 * @symrow{T_F; Temperature in degrees Fahrenheit; \degreeFahrenheit}
 * @endsymtable
 *
 * @param[in] fahrenheit Temperature in degrees Fahrenheit @unitb{\degreeFahrenheit}
 * @return Temperature in degrees Rankine @unitb{\degreeRankine}
 */
constexpr double fahrenheitToRankine(double fahrenheit) { return fahrenheit + kFahrenheitToRankineOffset; }

} // namespace physics::conversions
