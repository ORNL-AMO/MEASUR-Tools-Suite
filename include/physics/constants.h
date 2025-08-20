/**
 * @file constants.h
 * @authors Liam White
 * @brief Defines physical constants and unit conversions.
 * @details Values are taken from CODATA 2022.
 */
#pragma once

/**
 * @namespace physics
 * @defgroup physics Physics
 * @brief Contains physical constants and unit conversions.
 */
namespace physics {

// Conversion factors
inline constexpr double kFahrenheitToRankine = 459.67; ///< Offset to convert Fahrenheit to Rankine

/**
 * @namespace si
 * @defgroup si Standard International (SI) Units
 * @ingroup physics
 * @brief Contains physical constants in SI units.
 */
namespace si {

inline constexpr double kStefanBoltzmann =
    5.670374419e-8; ///< Stefan-Boltzmann constant @unit{\watt\per\meter\squared\kelvin\tothe{4}}

} // namespace si

/**
 * @namespace uscs
 * @defgroup uscs U.S. Customary System (USCS) Units
 * @ingroup physics
 * @brief Contains physical constants in USCS units.
 */
namespace uscs {

inline constexpr double kStefanBoltzmann =
    1.713441e-9; ///< Stefan-Boltzmann constant @unit{\Btu\per\hour\foot\squared\degreeRankine\tothe{4}}

} // namespace uscs

} // namespace physics