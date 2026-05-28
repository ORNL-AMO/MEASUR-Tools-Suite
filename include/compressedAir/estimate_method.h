#pragma once

/**
 * @ingroup estimate_method_calculator
 * @file estimate_method.h
 * @brief Declarations for the estimate method compressed air leak annual consumption estimation.
 * @details Provides a free function to estimate annual compressed air loss from visual and
 *          audible leak assessments. All calculations use U.S. customary units.
 * @see @ref estimate_method_calculator for formula derivation and symbol definitions.
 */

/**
 * @ingroup estimate_method_calculator
 * @namespace estimate_method
 * @brief Compressed air leak estimation using visual and audible assessment.
 * @details The estimate method provides a rapid field assessment of compressed air leak
 *          severity. An operator categorizes a leak by audible and visual clues (e.g., hissing
 *          sound, visible moisture or contamination) and assigns a corresponding estimated
 *          flow rate. That rate is then multiplied by annual operating time to yield the
 *          projected annual air loss. This approach trades precision for speed and is most
 *          appropriate for initial leak surveys, after which higher-accuracy methods such as
 *          the bag method or orifice method can be used for significant leaks.
 *
 * @see @ref estimate_method_calculator
 */
namespace estimate_method {

// ============================================================
//  Estimate Method
// ============================================================

/**
 * @ingroup estimate_method_calculator
 * @struct Input
 * @brief Input parameters for the estimate method compressed air leak calculation.
 */
struct Input {
    double operating_time     = 0.0; ///< Annual system operating time @unitb{\hour}
    double leak_rate_estimate = 0.0; ///< Estimated leak rate from visual/audible assessment @unitb{\scfm}
};

/**
 * @ingroup estimate_method_calculator
 * @struct Result
 * @brief Result of the estimate method leak annual consumption calculation.
 */
struct Result {
    double annual_consumption = 0.0; ///< Estimated annual air loss from the leak @unitb{\kscf}
};

/**
 * @brief Estimates annual compressed air consumption from a leak using the estimate method.
 * @details Annual consumption is the product of the estimated leak rate, annual operating
 *          time, and the minutes-per-hour conversion factor, then divided by the
 *          scf-to-kscf factor.
 *
 * **Annual Consumption:**
 * @formula{estimate-method-annual-consumption;
 *   C_{annual} = \frac{\dot{Q}_{leak} \cdot t_{op} \cdot 60}{1000}
 * }
 *
 * where:
 * @symtable
 * @symrow{C_{annual}; Estimated annual air loss from the leak; \kscf}
 * @symrow{\dot{Q}_{leak}; Estimated compressed air leak flow rate; \scfm}
 * @symrow{t_{op}; Annual system operating time; \hour}
 * @symrow{60; Minutes per hour conversion; \minute\per\hour}
 * @symrow{1000; Standard cubic feet per kiloscf conversion; \unitless}
 * @endsymtable
 *
 * @note Leak rate estimate must be in scfm. Operating time must be in hours per year.
 *
 * @param[in] input  Input
 * @return Result containing @c annual_consumption [kscf].
 */
Result calculate(const Input& input);

} // namespace estimate_method
