#pragma once

/**
 * @file constants.h
 * @authors Liam White
 * @brief Defines physical constants and unit conversions.
 * @details https://physics.nist.gov/cuu/Constants/index.html
 */
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

/**
 * @brief Standard density of water at 4°C @unitb{\kilogram\per\meter\cubed}
 * @details Used for water property calculations. Source: NIST, CRC Handbook of Chemistry and Physics.
 */
inline constexpr double kWaterDensityBase = 1000.0;

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

/**
 * @brief Standard gas temperature for exhaust calculations @unitb{\degreeRankine}
 * @details This is an absolute temperature (520°R = 60°F + 460), commonly used as the reference for gas property calculations in U.S. customary units.
inline constexpr double kStandardGasTemperatureR = 520.0;

/**
 * @brief Ambient reference temperature for exhaust calculations @unitb{\degreeFahrenheit}
 */
inline constexpr double kAmbientTemperatureF = 60.0;

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

/// @brief Number of minutes in an hour.
inline constexpr double kMinutesPerHour = 60.0;

/**
 * @brief Conversion factor from kilowatts to BTU/hr @unitb{\btu\per\hour\per\kilowatt}
 * @details Source: NIST, Perry's Chemical Engineers' Handbook
 */
inline constexpr double kKilowattToBtuPerHour = 3412.136247820839;


/**
 * @brief Conversion factor from kilograms per cubic meter to pounds per gallon @unitb{\pound\per\gallon\per\kilogram\per\meter\cubed}
 * @details Multiplies water density in kg/m^3 to obtain lb/gal. Source: NIST, CRC Handbook of Chemistry and Physics.
 */
inline constexpr double kKgPerM3ToLbPerGal = 0.0083454;


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

/**
 * @brief Convert Fahrenheit to Celsius.
 * @details Converts a temperature from degrees Fahrenheit to degrees Celsius:
 *
 * @par Relation
 * @formula{fahrenheit-to-celsius; T_C = \frac{5}{9}(T_F - 32)}
 *
 * @par Symbols
 * @symtable
 * @symrow{T_C; Temperature in degrees Celsius; \degreeCelsius}
 * @symrow{T_F; Temperature in degrees Fahrenheit; \degreeFahrenheit}
 * @endsymtable
 *
 * @param[in] fahrenheit Temperature in degrees Fahrenheit @unitb{\degreeFahrenheit}
 * @return Temperature in degrees Celsius @unitb{\degreeCelsius}
 */
constexpr double fahrenheitToCelsius(double fahrenheit) { return (fahrenheit - 32.0) / 1.8; }




} // namespace physics::conversions
