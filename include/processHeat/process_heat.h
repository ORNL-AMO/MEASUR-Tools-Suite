
#pragma once

/**
 * @file process_heat.h
 * @ingroup process_heat
 * @brief Utility section for common process heat functions.
 * @details This header will collect reusable functions and helpers for process heating calculations, such as excess air, available heat, and other shared logic.
 */

namespace process_heat {

/**
 * @ingroup process_heat
 * @brief Calculates excess air from O2 in flue gas.
 * @param[in] o2_flue_gas O2 in flue gas (fraction)
 * @return Excess air (fraction)
 */
double calculateExcessAir(double o2_flue_gas);

} // namespace process_heat
