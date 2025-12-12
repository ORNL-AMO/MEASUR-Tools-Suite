#pragma once
#include <cmath>
namespace gas_constants {

// Shared combustion/stoichiometry constants
constexpr double kCToCO2 = 44.0 / 12.0;
constexpr double kHToH2O = 9.0;
constexpr double kSToSO2 = 2.0;
constexpr double kCToO2 = 32.0 / 12.0;
constexpr double kHToO2 = 8.0;
constexpr double kSToO2 = 1.0;
constexpr double kN2O2Ratio = 76.85 / 23.15;
constexpr double kSO2Cp = 17.472;
constexpr double kSO2Mw = 64.06;
constexpr double kO2Mw = 32.0;
constexpr double kN2Mw = 28.016;
constexpr double kCO2Mw = 44.01;
constexpr double kH2OMw = 18.016;

/**
 * @brief Specific heat for methane (CH4) as a function of temperature (°F).
 * @details Cp = 4.23 + 0.01177 * T @unitb{Btu/(lb·°F)}
 */
inline double specificHeatCH4(double t) { return 4.23 + 0.01177 * t; }

/**
 * @brief Specific heat for ethane (C2H6) as a function of temperature (°F).
 * @details Cp = 4.04 + 0.01636 * T @unitb{Btu/(lb·°F)}
 */
inline double specificHeatC2H6(double t) { return 4.04 + 0.01636 * t; }

/**
 * @brief Specific heat for nitrogen (N2) as a function of temperature (°F).
 * @details Cp = 9.47 - 3.47 * 1000 / T + 1.07 * 1000000 / (T * T) @unitb{Btu/(lb·°F)}
 */
inline double specificHeatN2(double t) { return 9.47 - 3.47 * 1000 / t + 1.07 * 1000000 / (t * t); }

/**
 * @brief Specific heat for hydrogen (H2) as a function of temperature (°F).
 * @details Cp = 5.76 + 0.578 * T / 1000 + 20 / sqrt(T) @unitb{Btu/(lb·°F)}
 */
inline double specificHeatH2(double t) { return 5.76 + 0.578 * t / 1000 + 20 / std::pow(t, 0.5); }

/**
 * @brief Specific heat for propane (C3H8) as a function of temperature (°F).
 * @details Cp = 17.108 @unitb{Btu/(lb·°F)}
 */
inline double specificHeatC3H8(double t) {
    (void)t;
    return 17.108;
}

/**
 * @brief Specific heat for butane/paraffins (C4H10/CnH2n) as a function of temperature (°F).
 * @details Cp = 22.202 @unitb{Btu/(lb·°F)}
 */
inline double specificHeatC4H10CnH2n(double t) {
    (void)t;
    return 22.202;
}

/**
 * @brief Specific heat for water vapor (H2O) as a function of temperature (°F).
 * @details Cp = 19.86 - 597 / sqrt(T) + 7500 / T @unitb{Btu/(lb·°F)}
 */
inline double specificHeatH2O(double t) { return 19.86 - 597 / std::pow(t, 0.5) + 7500 / t; }

/**
 * @brief Specific heat for carbon monoxide (CO) as a function of temperature (°F).
 * @details Cp = 9.46 - 3.29 * 1000 / T + 1.07 * 1000000 / (T * T) @unitb{Btu/(lb·°F)}
 */
inline double specificHeatCO(double t) { return 9.46 - 3.29 * 1000 / t + 1.07 * 1000000 / (t * t); }

/**
 * @brief Specific heat for carbon dioxide (CO2) as a function of temperature (°F).
 * @details Cp = 16.2 - 6.53 * 1000 / T + 1.41 * 1000000 / (T * T) @unitb{Btu/(lb·°F)}
 */
inline double specificHeatCO2(double t) { return 16.2 - 6.53 * 1000 / t + 1.41 * 1000000 / (t * t); }

/**
 * @brief Specific heat for sulfur dioxide (SO2) as a function of temperature (°F).
 * @details Cp = 17.472 @unitb{Btu/(lb·°F)}
 */
inline double specificHeatSO2(double t) {
    (void)t;
    return 17.472;
}

/**
 * @brief Specific heat for oxygen (O2) as a function of temperature (°F).
 * @details Cp = 11.515 - 172 / sqrt(T) + 1530 / T @unitb{Btu/(lb·°F)}
 */
inline double specificHeatO2(double t) { return 11.515 - 172 / std::pow(t, 0.5) + 1530 / t; }

// Methane (CH4)
constexpr double CH4_MOLECULAR_WEIGHT     = 16.042;
constexpr double CH4_SPECIFIC_WEIGHT      = 0.042417;
constexpr double CH4_O2_GENERATED         = 64;
constexpr double CH4_HEATING_VALUE        = 23875;
constexpr double CH4_HEATING_VALUE_VOLUME = 1012;
constexpr double CH4_H2O_GENERATED        = 36.032;
constexpr double CH4_CO2_GENERATED        = 44.01;

// Ethane (C2H6)
constexpr double C2H6_MOLECULAR_WEIGHT     = 30.068;
constexpr double C2H6_SPECIFIC_WEIGHT      = 0.079503;
constexpr double C2H6_O2_GENERATED         = 112;
constexpr double C2H6_HEATING_VALUE        = 22323;
constexpr double C2H6_HEATING_VALUE_VOLUME = 1773;
constexpr double C2H6_H2O_GENERATED        = 54.048;
constexpr double C2H6_CO2_GENERATED        = 88.02;

// Nitrogen (N2)
constexpr double N2_MOLECULAR_WEIGHT = 28.016;
constexpr double N2_SPECIFIC_WEIGHT  = 0.074077;

// Hydrogen (H2)
constexpr double H2_MOLECULAR_WEIGHT     = 2.016;
constexpr double H2_SPECIFIC_WEIGHT      = 0.005331;
constexpr double H2_O2_GENERATED         = 16;
constexpr double H2_HEATING_VALUE        = 61095;
constexpr double H2_HEATING_VALUE_VOLUME = 325;
constexpr double H2_H2O_GENERATED        = 18.016;

// Propane (C3H8)
constexpr double C3H8_MOLECULAR_WEIGHT     = 44.094;
constexpr double C3H8_SPECIFIC_WEIGHT      = 0.116589;
constexpr double C3H8_O2_GENERATED         = 160;
constexpr double C3H8_HEATING_VALUE        = 21669;
constexpr double C3H8_HEATING_VALUE_VOLUME = 2523;
constexpr double C3H8_H2O_GENERATED        = 72.064;
constexpr double C3H8_CO2_GENERATED        = 132.03;

// Butane/Paraffins (C4H10/CnH2n)
constexpr double C4H10_CNH2N_MOLECULAR_WEIGHT     = 58.12;
constexpr double C4H10_CNH2N_SPECIFIC_WEIGHT      = 0.153675;
constexpr double C4H10_CNH2N_O2_GENERATED         = 208;
constexpr double C4H10_CNH2N_HEATING_VALUE        = 21321;
constexpr double C4H10_CNH2N_HEATING_VALUE_VOLUME = 3270;
constexpr double C4H10_CNH2N_H2O_GENERATED        = 90.08;
constexpr double C4H10_CNH2N_CO2_GENERATED        = 176.04;

// Water vapor (H2O)
constexpr double H2O_MOLECULAR_WEIGHT = 18.016;
constexpr double H2O_SPECIFIC_WEIGHT  = 0.047636;
constexpr double H2O_H2O_GENERATED    = 18.016;

// Carbon monoxide (CO)
constexpr double CO_MOLECULAR_WEIGHT     = 28.01;
constexpr double CO_SPECIFIC_WEIGHT      = 0.074061;
constexpr double CO_O2_GENERATED         = 16;
constexpr double CO_HEATING_VALUE        = 4347;
constexpr double CO_HEATING_VALUE_VOLUME = 321;
constexpr double CO_CO2_GENERATED        = 44.01;

// Carbon dioxide (CO2)
constexpr double CO2_MOLECULAR_WEIGHT = 44.01;
constexpr double CO2_SPECIFIC_WEIGHT  = 0.116367;
constexpr double CO2_CO2_GENERATED    = 44.01;

// Sulfur dioxide (SO2)
constexpr double SO2_MOLECULAR_WEIGHT = 64.06;
constexpr double SO2_SPECIFIC_WEIGHT  = 0.169381;

// Oxygen (O2)
constexpr double O2_MOLECULAR_WEIGHT = 32.00;
constexpr double O2_SPECIFIC_WEIGHT  = 0.084611;
constexpr double O2_O2_GENERATED     = -32;

constexpr double MOLAR_VOLUME_STP_L    = 22.414; // L/mol
constexpr double AIR_DENSITY_STP_KG_M3 = 1.205; // kg/m3
}; // namespace gas_constants