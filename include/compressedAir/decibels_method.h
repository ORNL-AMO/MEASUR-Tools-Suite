#pragma once

/**
 * @ingroup decibels_method_calculator
 * @file decibels_method.h
 * @brief Declarations for the decibels method compressed air leak flow rate estimation.
 * @details Provides a free function to estimate compressed air leak flow rate and
 *          annual air loss using bilinear interpolation from ultrasonic decibel
 *          measurements and two reference pressure-flow data points.
 *          All calculations use U.S. customary units.
 * @see @ref decibels_method_calculator for formula derivations and symbol definitions.
 */

/**
 * @ingroup decibels_method_calculator
 * @namespace decibels_method
 * @brief Compressed air leak flow estimation using ultrasonic decibel measurements.
 * @details The decibels method estimates compressed air leak flow rate by applying
 *          bilinear interpolation to a pair of reference data points. An ultrasonic
 *          detector measures the decibel level at the leak and the line pressure is
 *          recorded. Two calibration reference points — each defined by a pressure,
 *          a decibel rating, and the corresponding flow rates at the adjacent pressure
 *          — bracket the measured values. Bilinear interpolation across the pressure
 *          and decibel axes yields the leak flow rate without requiring physical access
 *          to the leak point.
 *
 * @see @ref decibels_method_calculator
 */
namespace decibels_method {

// ============================================================
//  Decibels Method
// ============================================================

/**
 * @ingroup decibels_method_calculator
 * @struct Input
 * @brief Input parameters for the decibels method compressed air leak calculation.
 * @details Two calibration reference points (A and B) define the interpolation grid.
 *          By convention, point A carries the lower decibel reference and point B the
 *          higher; the two reference pressures (pressure_a and pressure_b) have no
 *          required ordering. For each reference point, flow rates at both reference
 *          pressures are required.
 */
struct Input {
    double operating_time    = 0.0; ///< Annual system operating time @unitb{\hour}
    double line_pressure     = 0.0; ///< Measured compressed air line pressure @unitb{\psig}
    double decibels          = 0.0; ///< Measured ultrasonic decibel level at the leak @unitb{\decibel}
    double decibel_rating_a  = 0.0; ///< Lower reference decibel rating (point A) @unitb{\decibel}
    double pressure_a        = 0.0; ///< Reference pressure for point A @unitb{\psig}
    double first_flow_a      = 0.0; ///< Flow rate at (pressure_a, decibel_rating_a) @unitb{\scfm}
    double second_flow_a     = 0.0; ///< Flow rate at (pressure_b, decibel_rating_a) @unitb{\scfm}
    double decibel_rating_b  = 0.0; ///< Upper reference decibel rating (point B) @unitb{\decibel}
    double pressure_b        = 0.0; ///< Reference pressure for point B @unitb{\psig}
    double first_flow_b      = 0.0; ///< Flow rate at (pressure_a, decibel_rating_b) @unitb{\scfm}
    double second_flow_b     = 0.0; ///< Flow rate at (pressure_b, decibel_rating_b) @unitb{\scfm}
};

/**
 * @ingroup decibels_method_calculator
 * @struct Result
 * @brief Result of the decibels method leak flow rate calculation.
 */
struct Result {
    double leak_rate_estimate = 0.0; ///< Estimated compressed air leak flow rate @unitb{\scfm}
    double annual_consumption = 0.0; ///< Estimated annual air loss from the leak @unitb{\kscf}
};

/**
 * @brief Estimates compressed air leak flow rate and annual consumption using the
 *        decibels method.
 * @details The leak flow rate is determined by bilinear interpolation over two
 *          reference axes: line pressure and ultrasonic decibel level. Two
 *          calibration reference points bracket the measured values; each point
 *          supplies flow rates at two pressures, forming a 2×2 grid of known
 *          flow values. Standard bilinear interpolation across this grid yields
 *          the leak rate at the measured conditions.
 *
 *          Annual consumption scales the instantaneous leak rate by operating
 *          hours and the minutes-per-hour factor, then converts to kiloscf.
 *
 * **Leak Rate Estimate:**
 * @formula{decibels-method-leak-rate;
 *   Q_{leak} = \frac{
 *     (P_2 - P)(L_2 - L)\,Q_{11}
 *     + (P - P_1)(L_2 - L)\,Q_{21}
 *     + (P_2 - P)(L - L_1)\,Q_{12}
 *     + (P - P_1)(L - L_1)\,Q_{22}
 *   }{(P_2 - P_1)(L_2 - L_1)}
 * }
 *
 * where:
 * @symtable
 * @symrow{Q_{leak};  Estimated compressed air leak flow rate;                \scfm}
 * @symrow{P;         Measured line pressure;                                 \psig}
 * @symrow{L;         Measured ultrasonic decibel level at the leak;          \decibel}
 * @symrow{P_1;       Reference pressure (pressure_a);                        \psig}
 * @symrow{P_2;       Reference pressure (pressure_b);                        \psig}
 * @symrow{L_1;       Lower reference decibel rating (decibel_rating_a);      \decibel}
 * @symrow{L_2;       Upper reference decibel rating (decibel_rating_b);      \decibel}
 * @symrow{Q_{11};    Flow rate at (P_1,\, L_1) — first_flow_a;              \scfm}
 * @symrow{Q_{21};    Flow rate at (P_2,\, L_1) — second_flow_a;             \scfm}
 * @symrow{Q_{12};    Flow rate at (P_1,\, L_2) — first_flow_b;              \scfm}
 * @symrow{Q_{22};    Flow rate at (P_2,\, L_2) — second_flow_b;             \scfm}
 * @endsymtable
 *
 * **Annual Consumption:**
 * @formula{decibels-method-annual-consumption;
 *   C_{annual} = \frac{Q_{leak} \cdot t_{op} \cdot 60}{1000}
 * }
 *
 * where:
 * @symtable
 * @symrow{C_{annual}; Estimated annual air loss from the leak; \kscf}
 * @symrow{Q_{leak};   Compressed air leak flow rate;           \scfm}
 * @symrow{t_{op};     Annual system operating time;            \hour}
 * @symrow{60;         Minutes per hour conversion;             \minute\per\hour}
 * @symrow{1000;       Standard cubic feet per kiloscf;         \unitless}
 * @endsymtable
 *
 * @note The reference pressures pressure_a and pressure_b and reference decibel
 *       ratings decibel_rating_a and decibel_rating_b must bracket the measured
 *       line_pressure and decibels respectively. Extrapolation beyond the reference
 *       grid is mathematically valid but may reduce accuracy.
 *
 * @param[in] input  Input
 * @return Result containing @c leak_rate_estimate [scfm] and @c annual_consumption [kscf].
 */
Result calculate(const Input& input);

} // namespace decibels_method
