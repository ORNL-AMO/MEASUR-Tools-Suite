#pragma once

/**
 * @ingroup pipe_sizing_calculator
 * @file pipe_sizing.h
 * @brief Declarations for compressed air pipe sizing calculations.
 * @details Provides a function to determine the required cross-sectional area and
 *          minimum internal diameter of a compressed air distribution pipe given the
 *          volumetric flow rate, operating pressure, and design velocity. All
 *          calculations use U.S. customary units.
 * @see @ref pipe_sizing_calculator for formula derivations and symbol definitions.
 */

#include <cmath>
#include "physics/constants.h"

/**
 * @ingroup pipe_sizing_calculator
 * @namespace pipe_sizing
 * @brief Compressed air pipe sizing calculator.
 * @details This namespace provides a single calculation that determines the minimum
 *          internal pipe size needed to carry a given compressed air flow at a
 *          specified design velocity:
 *
 * - **Cross-Sectional Area** – the minimum internal area required so that the
 *   compressed air velocity does not exceed the design limit.
 * - **Pipe Diameter** – the internal diameter corresponding to the computed area,
 *   assuming a circular cross-section.
 *
 * @note A design velocity of 20 ft/s is recommended for main headers; the velocity
 *       should not exceed 30 ft/s in any branch.
 *
 * @see @ref pipe_sizing_calculator
 */
namespace pipe_sizing {

/**
 * @brief Industry-standard approximation of @math{\pi / 4} used in pipe diameter calculations.
 * @details This factor relates the cross-sectional area of a circular pipe to its
 *          diameter squared: @math{A = k_c \cdot D^2}, so
 *          @math{D = \sqrt{A / k_c}}.
 *          The value 0.78 is a rounded approximation of @math{\pi / 4 \approx 0.7854}
 *          used in U.S. customary pipe sizing practice.
 */
inline constexpr double kCircleAreaFactor = 0.78;

// ============================================================
//  Pipe Sizing
// ============================================================

/**
 * @ingroup pipe_sizing_calculator
 * @struct Input
 * @brief Input parameters for the pipe sizing calculation.
 */
struct Input {
    double airflow              = 0.0; ///< Volumetric free-air flow rate @unitb{\cubicFoot\per\minute}
    double airline_pressure     = 0.0; ///< Operating gauge pressure in the pipe @unitb{\psig}
    double design_velocity      = 0.0; ///< Maximum allowable compressed-air velocity @unitb{\foot\per\second}
    double atmospheric_pressure = physics::us::kAtmosphericPressurePsi; ///< Local atmospheric pressure @unitb{\psia}
};

/**
 * @ingroup pipe_sizing_calculator
 * @struct Result
 * @brief Result of the pipe sizing calculation.
 */
struct Result {
    double cross_sectional_area = 0.0; ///< Minimum required internal pipe area @unitb{\inch\squared}
    double pipe_diameter        = 0.0; ///< Minimum required internal pipe diameter @unitb{\inch}
};

/**
 * @brief Calculates the minimum pipe cross-sectional area and diameter for a compressed air system.
 * @details Applies the continuity equation to convert a free-air flow rate to the
 *          compressed-air volumetric flow at operating pressure, then sizes the pipe
 *          so that the resulting velocity does not exceed the design limit.
 *
 * **Cross-Sectional Area:**
 * @formula{pipe-sizing-area;
 *   A = \frac{k_{144} \cdot Q \cdot P_{atm}}{v \cdot k_{60} \cdot (P_{line} + P_{atm})}
 * }
 *
 * **Pipe Diameter:**
 * @formula{pipe-sizing-diameter;
 *   D = \sqrt{\frac{A}{k_c}}
 * }
 *
 * where:
 * @symtable
 * @symrow{A; Minimum required internal cross-sectional area; \inch\squared}
 * @symrow{k_{144}; Square inches per square foot (144); \inch\squared\per\squareFoot}
 * @symrow{Q; Volumetric free-air flow rate; \cubicFoot\per\minute}
 * @symrow{P_{atm}; Atmospheric pressure; \psia}
 * @symrow{v; Design velocity (maximum allowable); \foot\per\second}
 * @symrow{k_{60}; Seconds per minute (60); \second\per\minute}
 * @symrow{P_{line}; Operating gauge pressure in the pipe; \psig}
 * @symrow{D; Minimum required internal pipe diameter; \inch}
 * @symrow{k_c; Circle area factor (0.78 \approx \pi/4); \unitless}
 * @endsymtable
 *
 * @note The factor @math{P_{atm} / (P_{line} + P_{atm})} compresses the free-air
 *       volume to the actual volume at operating pressure (Boyle's Law).
 *       The factor @math{k_{144} / k_{60} = 144 / 60 = 2.4} converts units from
 *       ft²·min/s to in².
 *       @math{k_c = 0.78} is the industry-standard rounded approximation of
 *       @math{\pi / 4 \approx 0.7854} used in U.S. customary pipe sizing.
 *
 * @param[in] input  Input parameters
 * @return Result containing cross-sectional area in in² and pipe diameter in in.
 */
Result calculate(const Input& input);

} // namespace pipe_sizing
