#pragma once

/**
 * @ingroup compressed_air_pipe_data
 * @file pipe_data.h
 * @brief Shared pipe-size data shape for compressed air capacity and velocity calculations.
 * @details Provides the per-nominal-size data structure used by both the air system capacity
 *          and air velocity calculators. All calculations use U.S. customary units.
 */

#include <functional>

/**
 * @ingroup compressed_air_pipe_data
 * @namespace pipe_data
 * @brief Shared pipe data for compressed air calculators.
 * @details The same public data shape is used in two contexts:
 *          - air system capacity stores pipe volumes by nominal pipe size, in ft3;
 *          - air velocity stores calculated air velocities by nominal pipe size, in ft/s.
 */
namespace pipe_data {

/**
 * @ingroup compressed_air_pipe_data
 * @struct PipeData
 * @brief Per-size values for standard compressed air pipe sizes.
 * @details The length constructor converts pipe lengths in ft to contained pipe
 *          volumes in ft3. The velocity constructor applies a velocity function to
 *          each nominal pipe's internal area in in2 and stores velocities in ft/s.
 */
struct PipeData {
    /**
     * @brief Constructs an empty pipe-data object with all values set to zero.
     * @details Used by embind value-object conversion for module inputs/results.
     */
    PipeData() = default;

    /**
     * @brief Constructs per-size pipe volumes from pipe lengths.
     * @param[in] one_half Nominal 1/2 in pipe length @unitb{\foot}
     * @param[in] three_fourths Nominal 3/4 in pipe length @unitb{\foot}
     * @param[in] one Nominal 1 in pipe length @unitb{\foot}
     * @param[in] one_and_one_fourth Nominal 1-1/4 in pipe length @unitb{\foot}
     * @param[in] one_and_one_half Nominal 1-1/2 in pipe length @unitb{\foot}
     * @param[in] two Nominal 2 in pipe length @unitb{\foot}
     * @param[in] two_and_one_half Nominal 2-1/2 in pipe length @unitb{\foot}
     * @param[in] three Nominal 3 in pipe length @unitb{\foot}
     * @param[in] three_and_one_half Nominal 3-1/2 in pipe length @unitb{\foot}
     * @param[in] four Nominal 4 in pipe length @unitb{\foot}
     * @param[in] five Nominal 5 in pipe length @unitb{\foot}
     * @param[in] six Nominal 6 in pipe length @unitb{\foot}
     * @param[in] eight Nominal 8 in pipe length @unitb{\foot}
     * @param[in] ten Nominal 10 in pipe length @unitb{\foot}
     * @param[in] twelve Nominal 12 in pipe length @unitb{\foot}
     * @param[in] fourteen Nominal 14 in pipe length @unitb{\foot}
     * @param[in] sixteen Nominal 16 in pipe length @unitb{\foot}
     * @param[in] eighteen Nominal 18 in pipe length @unitb{\foot}
     * @param[in] twenty Nominal 20 in pipe length @unitb{\foot}
     * @param[in] twenty_four Nominal 24 in pipe length @unitb{\foot}
     */
    PipeData(double one_half, double three_fourths, double one, double one_and_one_fourth, double one_and_one_half,
             double two, double two_and_one_half, double three, double three_and_one_half, double four, double five,
             double six, double eight, double ten, double twelve, double fourteen, double sixteen, double eighteen,
             double twenty, double twenty_four);

    /**
     * @brief Constructs per-size velocity results from a velocity function.
     * @param[in] velocity_from_area Function that returns air velocity @unitb{\foot\per\second}
     *                              from a pipe internal area @unitb{\inch\squared}.
     */
    explicit PipeData(const std::function<double(double)>& velocity_from_area);

    double oneHalf         = 0.0; ///< Nominal 1/2 in value; ft3 for capacity, ft/s for velocity.
    double threeFourths    = 0.0; ///< Nominal 3/4 in value; ft3 for capacity, ft/s for velocity.
    double one             = 0.0; ///< Nominal 1 in value; ft3 for capacity, ft/s for velocity.
    double oneAndOneFourth = 0.0; ///< Nominal 1-1/4 in value; ft3 for capacity, ft/s for velocity.
    double oneAndOneHalf   = 0.0; ///< Nominal 1-1/2 in value; ft3 for capacity, ft/s for velocity.
    double two             = 0.0; ///< Nominal 2 in value; ft3 for capacity, ft/s for velocity.
    double twoAndOneHalf   = 0.0; ///< Nominal 2-1/2 in value; ft3 for capacity, ft/s for velocity.
    double three           = 0.0; ///< Nominal 3 in value; ft3 for capacity, ft/s for velocity.
    double threeAndOneHalf = 0.0; ///< Nominal 3-1/2 in value; ft3 for capacity, ft/s for velocity.
    double four            = 0.0; ///< Nominal 4 in value; ft3 for capacity, ft/s for velocity.
    double five            = 0.0; ///< Nominal 5 in value; ft3 for capacity, ft/s for velocity.
    double six             = 0.0; ///< Nominal 6 in value; ft3 for capacity, ft/s for velocity.
    double eight           = 0.0; ///< Nominal 8 in value; ft3 for capacity, ft/s for velocity.
    double ten             = 0.0; ///< Nominal 10 in value; ft3 for capacity, ft/s for velocity.
    double twelve          = 0.0; ///< Nominal 12 in value; ft3 for capacity, ft/s for velocity.
    double fourteen        = 0.0; ///< Nominal 14 in value; ft3 for capacity, ft/s for velocity.
    double sixteen         = 0.0; ///< Nominal 16 in value; ft3 for capacity, ft/s for velocity.
    double eighteen        = 0.0; ///< Nominal 18 in value; ft3 for capacity, ft/s for velocity.
    double twenty          = 0.0; ///< Nominal 20 in value; ft3 for capacity, ft/s for velocity.
    double twentyFour      = 0.0; ///< Nominal 24 in value; ft3 for capacity, ft/s for velocity.
    double totalPipeVolume = 0.0; ///< Sum of per-size pipe volumes @unitb{\cubicFoot}.
};

} // namespace pipe_data
