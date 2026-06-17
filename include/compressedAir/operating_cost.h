#pragma once

/**
 * @ingroup operating_cost_calculator
 * @file operating_cost.h
 * @brief Declarations for compressed air compressor annual operating cost calculations.
 * @details Provides a function to calculate the annual electricity cost of a compressor
 *          cycling between fully loaded and unloaded (part-load) operation.
 *          All calculations use U.S. customary units.
 * @see @ref operating_cost_calculator for formula derivations and symbol definitions.
 */

#include "physics/constants.h"

/**
 * @ingroup operating_cost_calculator
 * @namespace operating_cost
 * @brief Compressed air compressor annual operating cost calculations.
 * @details This namespace provides a single function for calculating the annual
 *          electricity cost of a compressor that cycles between loaded and unloaded
 *          (no-load) operation:
 *
 * - **Run Time Unloaded** – the percentage of operating time the compressor runs
 *   unloaded, computed as the complement of the loaded run time.
 * - **Loaded Cost** – annual electricity cost while the compressor runs at full load.
 * - **Unloaded Cost** – annual electricity cost while the compressor runs unloaded
 *   (motor continues to turn but compressor is not delivering air).
 * - **Total Annual Cost** – sum of the loaded and unloaded annual costs.
 *
 * @see @ref operating_cost_calculator
 */
namespace operating_cost {

// ============================================================
//  Input / Result
// ============================================================

/**
 * @ingroup operating_cost_calculator
 * @struct Input
 * @brief Input parameters for the annual compressor operating cost calculation.
 */
struct Input {
    double motor_bhp              = 0.0; ///< Full-load motor brake horsepower @unitb{\bhp}
    double bhp_unloaded           = 0.0; ///< Percentage of full-load BHP consumed when unloaded @unitb{\percent}
    double annual_operating_hours = 0.0; ///< Total compressor operating hours per year @unitb{\hour}
    double run_time_loaded        = 0.0; ///< Percentage of operating time the compressor runs loaded @unitb{\percent}
    double efficiency_loaded      = 0.0; ///< Motor efficiency in the loaded condition @unitb{\percent}
    double efficiency_unloaded    = 0.0; ///< Motor efficiency in the unloaded condition @unitb{\percent}
    double cost_of_electricity    = 0.0; ///< Electricity unit cost @unitb{\dollar\per\kilowatt\hour}
};

/**
 * @ingroup operating_cost_calculator
 * @struct Result
 * @brief Result of the annual compressor operating cost calculation.
 */
struct Result {
    double run_time_unloaded = 0.0; ///< Percentage of operating time the compressor runs unloaded @unitb{\percent}
    double cost_for_loaded   = 0.0; ///< Annual electricity cost in the loaded condition @unitb{\dollar\per\year}
    double cost_for_unloaded = 0.0; ///< Annual electricity cost in the unloaded condition @unitb{\dollar\per\year}
    double total_annual_cost = 0.0; ///< Total annual electricity cost @unitb{\dollar\per\year}
};

/**
 * @brief Calculates the annual electricity cost for a compressor cycling between
 *        loaded and unloaded operation.
 *
 * @details A load/unload compressor control strategy cycles the machine between full
 *          delivery (loaded) and zero delivery (unloaded) while the motor continues
 *          to run in both states. The unloaded state still consumes electricity at a
 *          reduced level proportional to @math{f_{bhp,unloaded}}. This function
 *          quantifies both cost components separately and their sum.
 *
 * **Run Time Unloaded:**
 * @formula{operating-cost-run-time-unloaded;
 *   f_{unloaded} = 100 - f_{loaded}
 * }
 *
 * **Loaded Annual Cost:**
 * @formula{operating-cost-loaded;
 *   C_{loaded} = \frac{P_{motor} \cdot k_{BHP} \cdot H_{annual} \cdot f_{loaded} \cdot c_{elec}}{\eta_{loaded}}
 * }
 *
 * **Unloaded Annual Cost:**
 * @formula{operating-cost-unloaded;
 *   C_{unloaded} = \frac{P_{motor} \cdot k_{BHP} \cdot H_{annual} \cdot f_{bhp,unloaded} \cdot f_{unloaded} \cdot c_{elec}}{\eta_{unloaded}}
 * }
 *
 * **Total Annual Cost:**
 * @formula{operating-cost-total;
 *   C_{total} = C_{loaded} + C_{unloaded}
 * }
 *
 * where:
 * @symtable
 * @symrow{f_{unloaded}; Percentage of operating time the compressor runs unloaded; \percent}
 * @symrow{f_{loaded}; Percentage of operating time the compressor runs loaded (input); \percent}
 * @symrow{C_{loaded}; Annual electricity cost in the loaded condition; \dollar\per\year}
 * @symrow{C_{unloaded}; Annual electricity cost in the unloaded condition; \dollar\per\year}
 * @symrow{C_{total}; Total annual electricity cost; \dollar\per\year}
 * @symrow{P_{motor}; Full-load motor brake horsepower; \bhp}
 * @symrow{k_{BHP}; BHP-to-kilowatt conversion factor (0.746); \kilowatt\per\bhp}
 * @symrow{H_{annual}; Total compressor operating hours per year; \hour}
 * @symrow{f_{bhp,unloaded}; Percentage of full-load BHP consumed when unloaded (input); \percent}
 * @symrow{\eta_{loaded}; Motor efficiency in the loaded condition (input); \percent}
 * @symrow{\eta_{unloaded}; Motor efficiency in the unloaded condition (input); \percent}
 * @symrow{c_{elec}; Electricity unit cost; \dollar\per\kilowatt\hour}
 * @endsymtable
 *
 * @note All percentage inputs (@math{f_{loaded}}, @math{f_{bhp,unloaded}},
 *       @math{\eta_{loaded}}, @math{\eta_{unloaded}}) are entered on a 0–100 scale
 *       and divided by 100 internally. Because both the run-time fractions and the
 *       efficiency fractions are divided by 100, the factors cancel in the
 *       loaded-cost formula and reduce to the equivalent dimensionless ratio.
 *       The conversion constant @math{k_{BHP} = 0.746} is the standard mechanical
 *       horsepower-to-kilowatt factor.
 *       See @ref physics::conversions::kBhpToKw.
 *
 * @param[in] input  Input
 * @return Result containing run_time_unloaded [%], cost_for_loaded [$/yr],
 *         cost_for_unloaded [$/yr], and total_annual_cost [$/yr].
 */
Result calculateOperatingCost(const Input& input);

} // namespace operating_cost
