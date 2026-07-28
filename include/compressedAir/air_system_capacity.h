#pragma once

/**
 * @ingroup air_system_capacity_calculator
 * @file air_system_capacity.h
 * @brief Declarations for compressed air system capacity calculations.
 * @details Calculates the total air quantity held in a compressed air system from
 *          pipe volume and receiver tank capacity. All calculations use U.S.
 *          customary units.
 * @see @ref air_system_capacity_calculator for formula derivations and symbol definitions.
 */

#include <vector>

#include "compressedAir/pipe_data.h"

/**
 * @ingroup air_system_capacity_calculator
 * @namespace air_system_capacity
 * @brief Compressed air system capacity calculator.
 * @details Provides a namespace free function for total compressed air system capacity.
 */
namespace air_system_capacity {

/// @brief Existing receiver conversion factor @unitb{\gallon\per\cubicFoot}.
inline constexpr double kGallonsPerCubicFoot = 7.480515625;

/**
 * @ingroup air_system_capacity_calculator
 * @struct Input
 * @brief Input parameters for the air system capacity calculation.
 */
struct Input {
    pipe_data::PipeData pipe_lengths; ///< Pipe data constructed from pipe lengths; stored values are volumes @unitb{\cubicFoot}.
    std::vector<double> receivers;    ///< Receiver capacities @unitb{\gallon}.
};

/**
 * @ingroup air_system_capacity_calculator
 * @struct Output
 * @brief Result of the air system capacity calculation.
 */
struct Output {
    double total_pipe_volume                         = 0.0; ///< Total pipe volume @unitb{\cubicFoot}.
    double total_receiver_volume                     = 0.0; ///< Total receiver volume @unitb{\cubicFoot}.
    double total_capacity_of_compressed_air_system   = 0.0; ///< Total system capacity @unitb{\cubicFoot}.
    std::vector<double> receiver_capacities          = {};  ///< Receiver capacities converted to @unitb{\cubicFoot}.
    pipe_data::PipeData pipe_lengths;                       ///< Per-size pipe volumes @unitb{\cubicFoot}.
};

/**
 * @brief Calculates total compressed air system capacity.
 * @param[in] input Pipe and receiver inputs.
 * @return Output containing pipe volume, receiver volumes, and total system capacity @unitb{\cubicFoot}.
 */
Output calculate(const Input& input);

} // namespace air_system_capacity
