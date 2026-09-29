#pragma once

/**
 * @ingroup air_velocity_calculator
 * @file air_velocity.h
 * @brief Declarations for compressed air velocity calculations.
 * @details Calculates compressed air velocity by nominal pipe size from airflow,
 *          pipe pressure, and atmospheric pressure. All calculations use U.S.
 *          customary units.
 * @see @ref air_velocity_calculator for formula derivations and symbol definitions.
 */

#include "compressedAir/pipe_data.h"

/**
 * @ingroup air_velocity_calculator
 * @namespace air_velocity
 * @brief Compressed air velocity calculator.
 * @details Provides a namespace free function for velocity-by-size results.
 */
namespace air_velocity {

/**
 * @ingroup air_velocity_calculator
 * @struct Input
 * @brief Input parameters for the air velocity calculation.
 */
struct Input {
    double airflow              = 0.0; ///< Volumetric free-air flow rate @unitb{\standardCubicFeetPerMinute}.
    double pipe_pressure        = 0.0; ///< Pipe gauge pressure @unitb{\psig}.
    double atmospheric_pressure = 0.0; ///< Atmospheric absolute pressure @unitb{\psia}.
};

/**
 * @brief Calculates compressed air velocities by nominal pipe size.
 * @param[in] input Airflow and pressure inputs.
 * @return Per-size air velocity results @unitb{\foot\per\second}.
 */
pipe_data::PipeData calculate(const Input& input);

} // namespace air_velocity
