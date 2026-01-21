#pragma once
#include <cmath>
namespace gas_constants {

// Shared combustion/stoichiometry constants
constexpr double kCToCO2    = 44.0 / 12.0;
constexpr double kHToH2O    = 9.0;
constexpr double kSToSO2    = 2.0;
constexpr double kCToO2     = 32.0 / 12.0;
constexpr double kHToO2     = 8.0;
constexpr double kSToO2     = 1.0;
constexpr double kN2O2Ratio = 76.85 / 23.15;
constexpr double kSO2Cp     = 17.472;
constexpr double kSO2Mw     = 64.06;
constexpr double kO2Mw      = 32.0;
constexpr double kN2Mw      = 28.016;
constexpr double kCO2Mw     = 44.01;
constexpr double kH2OMw     = 18.016;

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
 * @brief Specific heat for sulphur dioxide (SO2) as a function of temperature (°F).
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

/**
 * @brief Specific heat for liquid feedwater as a function of temperature (K).
 * @details Empirical polynomial fit for Cp of water in kJ/kg-K, valid for typical feedwater temperature range.
 * @param[in] temp_k Temperature in Kelvin @unitb{\kelvin}
 * @return Specific heat in kJ/kg-K @unitb{kJ/kg\kelvin}
 */
inline double specificHeatFeedwater(double temp_k) {
    return +0.000000000000326658 * std::pow(temp_k, 6) - 0.000000000838033377 * std::pow(temp_k, 5) +
           0.000000883910920876 * std::pow(temp_k, 4) - 0.000490348083986228 * std::pow(temp_k, 3) +
           0.150847712358072 * std::pow(temp_k, 2) - 24.3962399473808 * temp_k + 1624.65179353148;
}

// Methane (CH4)
constexpr double kCh4MolecularWeight    = 16.042;
constexpr double kCh4SpecificWeight     = 0.042417;
constexpr double kCh4O2Generated        = 64;
constexpr double kCh4HeatingValue       = 23875;
constexpr double kCh4HeatingValueVolume = 1012;
constexpr double kCh4H2oGenerated       = 36.032;
constexpr double kCh4Co2Generated       = 44.01;

// Ethane (C2H6)
constexpr double kC2h6MolecularWeight    = 30.068;
constexpr double kC2h6SpecificWeight     = 0.079503;
constexpr double kC2h6O2Generated        = 112;
constexpr double kC2h6HeatingValue       = 22323;
constexpr double kC2h6HeatingValueVolume = 1773;
constexpr double kC2h6H2oGenerated       = 54.048;
constexpr double kC2h6Co2Generated       = 88.02;

// Nitrogen (N2)
constexpr double kN2MolecularWeight = 28.016;
constexpr double kN2SpecificWeight  = 0.074077;

// Hydrogen (H2)
constexpr double kH2MolecularWeight    = 2.016;
constexpr double kH2SpecificWeight     = 0.005331;
constexpr double kH2O2Generated        = 16;
constexpr double kH2HeatingValue       = 61095;
constexpr double kH2HeatingValueVolume = 325;
constexpr double kH2H2oGenerated       = 18.016;

// Propane (C3H8)
constexpr double kC3h8MolecularWeight    = 44.094;
constexpr double kC3h8SpecificWeight     = 0.116589;
constexpr double kC3h8O2Generated        = 160;
constexpr double kC3h8HeatingValue       = 21669;
constexpr double kC3h8HeatingValueVolume = 2523;
constexpr double kC3h8H2oGenerated       = 72.064;
constexpr double kC3h8Co2Generated       = 132.03;

// Butane/Paraffins (C4H10/CnH2n)
constexpr double kC4h10Cnh2nMolecularWeight    = 58.12;
constexpr double kC4h10Cnh2nSpecificWeight     = 0.153675;
constexpr double kC4h10Cnh2nO2Generated        = 208;
constexpr double kC4h10Cnh2nHeatingValue       = 21321;
constexpr double kC4h10Cnh2nHeatingValueVolume = 3270;
constexpr double kC4h10Cnh2nH2oGenerated       = 90.08;
constexpr double kC4h10Cnh2nCo2Generated       = 176.04;

// Water vapor (H2O)
constexpr double kH2oMolecularWeight = 18.016;
constexpr double kH2oSpecificWeight  = 0.047636;
constexpr double kH2oH2oGenerated    = 18.016;

// Carbon monoxide (CO)
constexpr double kCoMolecularWeight    = 28.01;
constexpr double kCoSpecificWeight     = 0.074061;
constexpr double kCoO2Generated        = 16;
constexpr double kCoHeatingValue       = 4347;
constexpr double kCoHeatingValueVolume = 321;
constexpr double kCoCo2Generated       = 44.01;

// Carbon dioxide (CO2)
constexpr double kCo2MolecularWeight = 44.01;
constexpr double kCo2SpecificWeight  = 0.116367;
constexpr double kCo2Co2Generated    = 44.01;

// Sulphur dioxide (SO2)
constexpr double kSo2MolecularWeight = 64.06;
constexpr double kSo2SpecificWeight  = 0.169381;

// Oxygen (O2)
constexpr double kO2MolecularWeight = 32.00;
constexpr double kO2SpecificWeight  = 0.084611;
constexpr double kO2O2Generated     = -32;

constexpr double kMolarVolumeStpL   = 22.414; // L/mol
constexpr double kAirDensityStpKgM3 = 1.205;  // kg/m3
}; // namespace gas_constants