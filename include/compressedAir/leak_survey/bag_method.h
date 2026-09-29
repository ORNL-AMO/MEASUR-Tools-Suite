#pragma once

/**
 * @ingroup bag_method_calculator
 * @file bag_method.h
 * @brief Declarations for the bag method compressed air leak flow rate measurement.
 * @details Provides a free function to estimate compressed air leak flow rate and
 *          annual air loss using the bag fill-time field measurement technique.
 *          All calculations use U.S. customary units.
 * @see @ref bag_method_calculator for formula derivations and symbol definitions.
 */

/**
 * @ingroup bag_method_calculator
 * @namespace bag_method
 * @brief Compressed air leak flow estimation using the bag fill-time method.
 * @details The bag method is a practical field technique for estimating compressed
 *          air leaks. A measurement bag (typically a pre-measured trash bag) is
 *          placed over the leak point and the time required to fill the bag is
 *          recorded. The fill time and known bag volume together determine the
 *          volumetric flow rate of the leak. This method is the second most accurate
 *          field technique for measuring compressed air consumption after inline
 *          flow meters.
 *
 * @see @ref bag_method_calculator
 */
namespace bag_method {

// ============================================================
//  Bag Method
// ============================================================

/**
 * @ingroup bag_method_calculator
 * @struct Input
 * @brief Input parameters for the bag method compressed air leak calculation.
 */
struct Input {
    double operating_time  = 0.0; ///< Annual system operating time @unitb{\hour}
    double bag_fill_time   = 0.0; ///< Time for the measurement bag to fill with leaked air @unitb{\second}
    double bag_volume      = 0.0; ///< Pre-measured volume of the measurement bag @unitb{\cubicFoot}
};

/**
 * @ingroup bag_method_calculator
 * @struct Result
 * @brief Result of the bag method leak flow rate calculation.
 */
struct Result {
    double flow_rate          = 0.0; ///< Measured compressed air leak flow rate @unitb{\scfm}
    double annual_consumption = 0.0; ///< Estimated annual air loss from the leak @unitb{\kscf}
};

/**
 * @brief Estimates compressed air leak flow rate and annual consumption using the bag method.
 * @details The leak flow rate is the bag volume divided by the fill time (converted to minutes).
 *          Annual consumption scales by operating hours and the minutes-per-hour factor,
 *          then converts to kiloscf.
 *
 * **Flow Rate:**
 * @formula{bag-method-flow-rate;
 *   Q_{leak} = \frac{V_{bag} \cdot 60}{t_{fill}}
 * }
 *
 * where:
 * @symtable
 * @symrow{Q_{leak}; Compressed air leak flow rate; \scfm}
 * @symrow{V_{bag}; Pre-measured volume of the measurement bag; \cubicFoot}
 * @symrow{t_{fill}; Time for the bag to fill with leaked air; \second}
 * @symrow{60; Seconds per minute conversion; \second\per\minute}
 * @endsymtable
 *
 * **Annual Consumption:**
 * @formula{bag-method-annual-consumption;
 *   C_{annual} = \frac{Q_{leak} \cdot t_{op} \cdot 60}{1000}
 * }
 *
 * where:
 * @symtable
 * @symrow{C_{annual}; Estimated annual air loss from the leak; \kscf}
 * @symrow{Q_{leak}; Compressed air leak flow rate; \scfm}
 * @symrow{t_{op}; Annual system operating time; \hour}
 * @symrow{60; Minutes per hour conversion; \minute\per\hour}
 * @symrow{1000; Standard cubic feet per kiloscf conversion; \unitless}
 * @endsymtable
 *
 * @note Bag fill time must be measured in seconds. Bag volume must be
 *       pre-measured in cubic feet. The flow rate @math{Q_{leak}} is at
 *       approximately standard atmospheric conditions.
 *
 * @param[in] input  Input
 * @return Result containing @c flow_rate [scfm] and @c annual_consumption [kscf].
 */
Result calculate(const Input& input);

} // namespace bag_method
