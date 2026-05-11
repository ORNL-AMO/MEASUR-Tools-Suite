#pragma once

#include <vector>

/**
 * @ingroup compressed_air_pressure_reduction_calculator
 * @file compressed_air_pressure_reduction.h
 * @brief Declares structs and functions for the Compressed Air Pressure Reduction Calculator.
 * @copybrief compressed_air_pressure_reduction_calculator
 */

/**
 * @ingroup compressed_air_pressure_reduction_calculator
 * @namespace compressed_air_pressure_reduction
 * @brief Compressed-air pressure reduction calculations for treasure hunt measures.
 * @details Provides a function-based API for estimating annual energy use and annual energy cost
 * for compressed-air systems based on baseline operation or pressure-reduction modification cases.
 * @see compressed_air_pressure_reduction_calculator
 */
namespace compressed_air_pressure_reduction {

/**
 * @ingroup compressed_air_pressure_reduction_calculator
 * @struct CompressedAirPressureReductionInput
 * @brief Input data for a single compressed-air pressure reduction measure.
 */
struct CompressedAirPressureReductionInput {
    bool   is_baseline = true;        ///< True for baseline calculation, false for modification calculation
    int    hours_per_year = 0;        ///< Annual operating hours @unitb{\hour\per\year}
    double electricity_cost = 0.0;    ///< Electricity cost rate @unitb{\dollar\per\kWh}
    double compressor_power = 0.0;    ///< Compressor power @unitb{\kW}
    double pressure = 0.0;            ///< Baseline compressor discharge pressure @unitb{\psi}
    double proposed_pressure = 0.0;   ///< Proposed compressor discharge pressure @unitb{\psi}
    double atmospheric_pressure = 0.0; ///< Local atmospheric pressure @unitb{\psi}
    double pressure_rated = 0.0;      ///< Rated compressor pressure @unitb{\psi}
};

/**
 * @ingroup compressed_air_pressure_reduction_calculator
 * @struct CompressedAirPressureReductionOutput
 * @brief Output data for compressed-air pressure reduction calculations.
 */
struct CompressedAirPressureReductionOutput {
    double energy_use = 0.0;  ///< Annual energy use @unitb{\kWh\per\year}
    double energy_cost = 0.0; ///< Annual energy cost @unitb{\dollar\per\year}
};

/**
 * @ingroup compressed_air_pressure_reduction_calculator
 * @brief Calculates total annual energy use and cost for compressed-air pressure reduction measures.
 * @param[in] input_vec Vector of @ref CompressedAirPressureReductionInput structs.
 * @return @ref CompressedAirPressureReductionOutput containing accumulated annual energy use and cost.
 */
CompressedAirPressureReductionOutput compressedAirPressureReduction(
    const std::vector<CompressedAirPressureReductionInput>& input_vec);

/**
 * @ingroup compressed_air_pressure_reduction_calculator
 * @brief Calculates annual energy use and cost for a baseline compressed-air case.
 * @param[in] hours_per_year Annual operating hours @unitb{\hour\per\year}.
 * @param[in] electricity_cost Electricity cost rate @unitb{\dollar\per\kWh}.
 * @param[in] compressor_power Compressor power @unitb{\kW}.
 * @return @ref CompressedAirPressureReductionOutput with annual energy use and cost.
 */
CompressedAirPressureReductionOutput baselineReduction(int hours_per_year, double electricity_cost,
                                                       double compressor_power);

/**
 * @ingroup compressed_air_pressure_reduction_calculator
 * @brief Calculates annual energy use and cost for a compressed-air pressure-reduction modification.
 * @param[in] hours_per_year Annual operating hours @unitb{\hour\per\year}.
 * @param[in] electricity_cost Electricity cost rate @unitb{\dollar\per\kWh}.
 * @param[in] compressor_power Compressor power @unitb{\kW}.
 * @param[in] proposed_pressure Proposed compressor discharge pressure @unitb{\psi}.
 * @param[in] atmospheric_pressure Local atmospheric pressure @unitb{\psi}.
 * @param[in] pressure_rated Rated compressor pressure @unitb{\psi}.
 * @return @ref CompressedAirPressureReductionOutput with annual energy use and cost.
 */
CompressedAirPressureReductionOutput modificationReduction(int hours_per_year, double electricity_cost,
                                                           double compressor_power, double proposed_pressure,
                                                           double atmospheric_pressure, double pressure_rated);

} // namespace compressed_air_pressure_reduction
