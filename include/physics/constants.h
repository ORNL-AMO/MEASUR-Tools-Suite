#pragma once

/**
 * @file constants.h
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

/**
 * @brief Specific heat of liquid water at standard conditions @unitb{\kilo\joule\per\kilogram\per\kelvin}
 * @details 4.1796 kJ/(kg·K) is the widely accepted value for the specific heat capacity of water at room temperature (15–25°C).
 */
inline constexpr double kSpecificHeatWater = 4.1796;

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
 * @brief Orifice area factor for volumetric flow calculations @unitb{\dimensionless}
 * @details Empirical, effectively dimensionless factor used in U.S. customary orifice meter equations to convert orifice diameter (in) squared to effective area for volumetric flow (scfh).
 * @note Standard value for fuel-fired furnace gas flow calculations.
 */
inline constexpr double kOrificeAreaFactor = 1300.0;

/**
 * @brief Standard atmospheric pressure at sea level @unitb{psia}
 * @details Used as the reference pressure for gas property and flow calculations in U.S. customary units.
 * @note 1 atmosphere = 14.7 psia (pounds per square inch absolute).
 */
inline constexpr double kAtmosphericPressurePsi = 14.7;

/**
 * @brief Boiling point of water @unitb{\degreeFahrenheit}
 */
inline constexpr double kWaterBoilingPointF = 212.0;

/**
 * @brief Specific heat of water vapor @unitb{\btu\per\pound\degreeFahrenheit}
 */
inline constexpr double kSpecificHeatWaterVapor = 0.481;

/**
 * @brief Latent heat of evaporation for water @unitb{\btu\per\pound}
 */
inline constexpr double kWaterEvaporation = 970.0;

/**
 * @brief Stefan–Boltzmann constant @unitb{\btu\per\hour\foot\squared\degreeRankine\tothe{4}}
 * @details Source: @cite capehart2007guide
 */
inline constexpr double kStefanBoltzmann = 1.713441e-9;

/**
 * @brief Standard gas temperature for exhaust calculations @unitb{\degreeRankine}
 * @details This is an absolute temperature (520°R = 60°F + 460), commonly used as the reference for gas property
 * calculations in U.S. customary units.
 */
inline constexpr double kStandardGasTemperatureR = 520.0;

/**
 * @brief Ambient reference temperature for exhaust calculations @unitb{\degreeFahrenheit}
 */
inline constexpr double kAmbientTemperatureF = 60.0;

/**
 * @brief Base specific heat of air @unitb{\btu\per\pound\degreeFahrenheit}
 * @details Used for exhaust gas heat loss calculations in non-EAF electric furnaces.
 */
inline constexpr double kSpecificHeatAirBase = 0.017828518;

/**
 * @brief Temperature coefficient for specific heat of air @unitb{\btu\per\pound\degreeFahrenheit\per\degreeFahrenheit}
 * @details Used for exhaust gas heat loss calculations in non-EAF electric furnaces.
 */
inline constexpr double kSpecificHeatAirCoeff = 0.000002556;

/**
 * @brief Base for air correction in exhaust gas heat loss calculations @unitb{\btu\per\pound}
 * @details Used for exhaust gas heat loss calculations in non-EAF electric furnaces.
 */
inline constexpr double kAirCorrectionBase = -1.078913827;


/**
 * @brief Water density @unitb{lb/gal}
 * @details Used for water flow calculations in process heating systems. Source: CRC Handbook of Chemistry and Physics.
 */
constexpr double kWaterDensity = 8.335;



} // namespace physics::us

/**
 * @namespace physics::conversions
 * @brief Factors and functions for unit conversions.
 */
namespace physics::conversions {

/**
 * @brief Conversion factor from Btu/(lb·°F) to kJ/(kg·K).
 * @details 1 Btu/(lb·°F) = 4.1868 kJ/(kg·K)
 */
inline constexpr double kBtuPerLbFToKJPerKgK = 4.1868;


/**
 * @brief Convert Fahrenheit to Kelvin.
 * @details Converts a temperature from degrees Fahrenheit to Kelvin:
 * @par Relation
 * @formula{fahrenheit-to-kelvin; T_K = (T_F - 32) / 1.8 + 273.15}
 * @par Symbols
 * @symtable
 * @symrow{T_K; Temperature in Kelvin; \kelvin}
 * @symrow{T_F; Temperature in degrees Fahrenheit; \degreeFahrenheit}
 * @endsymtable
 * @param[in] fahrenheit Temperature in degrees Fahrenheit @unitb{\degreeFahrenheit}
 * @return Temperature in Kelvin @unitb{\kelvin}
 */
constexpr double fahrenheitToKelvin(double fahrenheit) { return ((fahrenheit - 32.0) / 1.8) + 273.15; }

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
 * @brief Conversion factor from kilograms per cubic meter to pounds per gallon
 * @unitb{\pound\per\gallon\per\kilogram\per\meter\cubed}
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

/// @brief Conversion factor: 1 MMBtu = 1,000,000 Btu
inline constexpr double kMMBtuToBtu = 1'000'000.0;

/**
 * @brief Conversion factor: 1 pound per cubic foot = 16.018463 kilograms per cubic meter
 * @unitb{\kilogram\per\meter\cubed\per\pound\per\foot\cubed}
 * @details Use this to convert a mass density from lb/ft^3 to kg/m^3.
 */
inline constexpr double kLbPerFt3ToKgPerM3 = 16.018463;


/**
 * @brief BTU per ton of refrigeration @unitb{Btu/Ton}
 * @details Used for refrigeration capacity calculations. Source: ASHRAE Handbook.
 */
constexpr double kBtuPerTonRefrigeration = 12000.0;

/**
 * @brief Converts power from MMBtu/hr to kW.
 * @details 1 MMBtu/hr = 293.07107 kW.
 *
 * @par Relation
 * @formula{mmbtu-per-hr-to-kw; P_\mathrm{kW} = P_\mathrm{MMBtu/hr} \times 293.07107}
 *
 * @par Symbols
 * @symtable
 * @symrow{P_\mathrm{kW}; Power in kilowatts; \kilo\watt}
 * @symrow{P_\mathrm{MMBtu/hr}; Power in MMBtu/hr; \mega\btu\per\hour}
 * @endsymtable
 *
 * @param[in] mmbtu_per_hr Power in MMBtu/hr @unitb{\mega\btu\per\hour}
 * @return Power in kilowatts (kW) @unitb{\kilo\watt}
 */
constexpr double mmbtuPerHrToKW(double mmbtu_per_hr) { return mmbtu_per_hr * 293.07107; }

/**
 * @brief Converts power from kW to MMBtu/hr.
 * @details 1 kW = 0.003412142 MMBtu/hr.
 *
 * @par Relation
 * @formula{kw-to-mmbtu-per-hr; P_\mathrm{MMBtu/hr} = P_\mathrm{kW} \times 0.003412142}
 *
 * @par Symbols
 * @symtable
 * @symrow{P_\mathrm{MMBtu/hr}; Power in MMBtu/hr; \mega\btu\per\hour}
 * @symrow{P_\mathrm{kW}; Power in kilowatts; \kilo\watt}
 * @endsymtable
 *
 * @param[in] kw Power in kilowatts (kW) @unitb{\kilo\watt}
 * @return Power in MMBtu/hr @unitb{\mega\btu\per\hour}
 */
constexpr double kWToMMBtuPerHr(double kw) { return kw * 0.003412142; }



} // namespace physics::conversions
