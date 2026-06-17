#pragma once

/**
 * @ingroup compressed_air_leak_survey_calculator
 * @file compressed_air_leak_survey.h
 * @brief Declarations for the compressed air leak survey aggregate calculation.
 * @details Provides a free function to aggregate the energy cost and flow rate
 *          impact of multiple compressed air leaks measured using any of the four
 *          available field assessment methods. All calculations use U.S. customary units.
 * @see @ref compressed_air_leak_survey_calculator for formula derivations and
 *      symbol definitions.
 */

#include <vector>

#include "compressedAir/compressed_air_utils.h"
#include "compressedAir/leak_survey/bag_method.h"
#include "compressedAir/leak_survey/decibels_method.h"
#include "compressedAir/leak_survey/estimate_method.h"
#include "compressedAir/leak_survey/orifice_method.h"

/**
 * @ingroup compressed_air_leak_survey_calculator
 * @namespace compressed_air_leak_survey
 * @brief Aggregated compressed air leak survey calculation.
 * @details This namespace provides one function that processes a list of individual
 *          compressed air leak measurements and returns the combined annual energy
 *          and flow impact for the entire survey.
 *
 *          Each leak entry in the survey selects one of four flow-rate measurement
 *          methods (estimate, decibels, bag, or orifice) and one of two cost basis
 *          modes (compressed air utility or electricity). The calculator routes each
 *          leak to the appropriate sub-calculator, applies a leak-count multiplier,
 *          and accumulates the results across all entries.
 *
 * @see @ref compressed_air_leak_survey_calculator
 */
namespace compressed_air_leak_survey {

// ============================================================
//  Enumerations
// ============================================================

/**
 * @ingroup compressed_air_leak_survey_calculator
 * @enum MeasurementMethod
 * @brief Selects the field measurement method used to estimate each leak's flow rate.
 * @details Each method is implemented in its own namespace. The integer value is
 *          passed as the @c measurement_method field of @ref Input.
 * @see estimate_method, decibels_method, bag_method, orifice_method
 */
enum class MeasurementMethod : int {
    kEstimate = 0, ///< Visual and audible leak estimate — see @ref estimate_method
    kDecibels = 1, ///< Ultrasonic decibel measurement — see @ref decibels_method
    kBag      = 2, ///< Bag fill-time measurement — see @ref bag_method
    kOrifice  = 3  ///< Orifice pressure and geometry — see @ref orifice_method
};

/**
 * @ingroup compressed_air_leak_survey_calculator
 * @enum UtilityType
 * @brief Selects the cost basis used to convert the leak's annual flow to an annual cost.
 */
enum class UtilityType : int {
    kCompressedAir = 0, ///< Cost basis: compressed air utility rate @unitb{\dollar\per\cubic\foot}
    kElectricity   = 1  ///< Cost basis: electricity rate @unitb{\dollar\per\kilo\watt\hour}
};

// ============================================================
//  Input / Result
// ============================================================

/**
 * @ingroup compressed_air_leak_survey_calculator
 * @struct Input
 * @brief Input parameters for one leak entry in a compressed air leak survey.
 * @details A single @ref Input represents one or more identical leak points. The
 *          @c units field acts as a multiplier so that a group of identical leaks
 *          can be entered as a single row rather than repeated entries.
 *
 *          All four sub-method input structs must be populated; only the one
 *          selected by @c measurement_method is used in the calculation.
 *          Use the @ref MeasurementMethod and @ref UtilityType enumerators to
 *          assign the integer selector fields.
 */
struct Input {
    int    hours_per_year      = 0;   ///< Annual compressed air system operating time @unitb{\hour\per\year}
    int    utility_type        = 0;   ///< Cost basis selector (see @ref UtilityType) @unitb{\unitless}
    double utility_cost        = 0.0; ///< Utility rate — @unitb{\dollar\per\cubic\foot} when @c utility_type = 0; @unitb{\dollar\per\kilo\watt\hour} when @c utility_type = 1
    int    measurement_method  = 0;   ///< Flow-rate measurement method selector (see @ref MeasurementMethod) @unitb{\unitless}

    estimate_method::Input  estimate_input  = {}; ///< Inputs for the estimate method (used when @c measurement_method = 0)
    decibels_method::Input  decibels_input  = {}; ///< Inputs for the decibels method (used when @c measurement_method = 1)
    bag_method::Input       bag_input       = {}; ///< Inputs for the bag method (used when @c measurement_method = 2)
    orifice_method::Input   orifice_input   = {}; ///< Inputs for the orifice method (used when @c measurement_method = 3)

    compressed_air_utils::CompressorElectricityData compressor_electricity_data = {}; ///< Compressor electricity parameters (used when @c utility_type = 1)

    int    units               = 1;   ///< Number of identical leak points represented by this entry @unitb{\unitless}
};

/**
 * @ingroup compressed_air_leak_survey_calculator
 * @struct Result
 * @brief Aggregate result of a compressed air leak survey.
 * @details Accumulates the individual contributions of each leak entry across all
 *          measurement methods and both utility types.
 */
struct Result {
    double annual_total_electricity      = 0.0; ///< Total annual electrical energy consumed by all leaks @unitb{\kilo\watt\hour}
    double annual_total_electricity_cost = 0.0; ///< Total annual utility cost of all leaks @unitb{\dollar\per\year}
    double total_flow_rate               = 0.0; ///< Combined instantaneous flow rate of all leaks @unitb{\scfm}
    double annual_total_flow_rate        = 0.0; ///< Combined annual air volume lost to leaks @unitb{\scf}
};

// ============================================================
//  Function
// ============================================================

/**
 * @brief Calculates the aggregate energy cost and flow impact of a compressed air leak survey.
 * @details Iterates over each @ref Input in the survey, routes the entry to the
 *          appropriate measurement method sub-calculator, applies the leak-count
 *          multiplier (@c units), computes the utility cost for the selected cost
 *          basis, and accumulates the results into a single @ref Result.
 *
 *          The sub-calculators are called as-documented in their own namespaces.
 *          See @ref estimate_method::calculate, @ref decibels_method::calculate,
 *          @ref bag_method::calculate, and @ref orifice_method::calculate for
 *          the individual flow-rate and annual-consumption formulas.
 *
 * **Per-Leak Total Flow Rate:**
 * @formula{leak-survey-total-flow;
 *   Q_{total} = Q_{method} \cdot n
 * }
 *
 * where:
 * @symtable
 * @symrow{Q_{total}; Combined instantaneous flow rate for this leak entry; \scfm}
 * @symrow{Q_{method}; Leak flow rate returned by the selected sub-calculator; \scfm}
 * @symrow{n; Number of identical leak points (units); \unitless}
 * @endsymtable
 *
 * **Per-Leak Annual Volume (estimate and orifice methods):**
 * @formula{leak-survey-time-based-annual;
 *   V_{annual} = t_{op} \cdot Q_{total} \cdot 60
 * }
 *
 * where:
 * @symtable
 * @symrow{V_{annual}; Annual air volume for this leak entry; \scf}
 * @symrow{t_{op}; Annual compressed air system operating time; \hour\per\year}
 * @symrow{Q_{total}; Combined instantaneous flow rate; \scfm}
 * @symrow{60; Minutes per hour conversion; \minute\per\hour}
 * @endsymtable
 *
 * @note For the **estimate method**, @c estimate_input.operating_time is overridden
 *       with @c hours_per_year before calling @ref estimate_method::calculate, and
 *       the returned @c annual_consumption (in kscf) is converted to scf by
 *       multiplying by 1000 before applying the @c units multiplier.
 *
 * @note For the **bag method**, @c annual_total_flow_rate accumulates the sub-calculator's
 *       @c annual_consumption (in kscf) multiplied by @c units directly, without
 *       the 1000× conversion. This preserves the original calculation behavior.
 *
 * **Annual Electricity (utility_type = 1):**
 * @formula{leak-survey-electricity;
 *   E_{annual} = \frac{k_{sp}}{60} \cdot V_{annual}
 * }
 * @formula{leak-survey-electricity-cost;
 *   C_{cost} = E_{annual} \cdot r_{elec}
 * }
 *
 * **Annual Compressed Air Cost (utility_type = 0):**
 * @formula{leak-survey-ca-cost;
 *   C_{cost} = r_{ca} \cdot V_{annual}
 * }
 *
 * where:
 * @symtable
 * @symrow{E_{annual}; Annual electrical energy consumed by the leak; \kilo\watt\hour}
 * @symrow{k_{sp}; Compressor specific power; \kilo\watt\per(\cubic\foot\per\minute)}
 * @symrow{60; Converts kW\cdot{}min/scf to kW\cdot{}hr/scf; \minute\per\hour}
 * @symrow{C_{cost}; Annual utility cost; \dollar\per\year}
 * @symrow{r_{elec}; Electricity utility rate; \dollar\per\kilo\watt\hour}
 * @symrow{r_{ca}; Compressed air utility rate; \dollar\per\cubic\foot}
 * @endsymtable
 *
 * @note When @c utility_type = 0 (compressed air), @c annual_total_electricity
 *       remains zero; only @c annual_total_electricity_cost is computed.
 *       When @c utility_type = 1 (electricity), both fields are populated.
 *
 * @param[in] inputs  Vector of @ref Input, one entry per leak measurement row.
 * @return @ref Result containing accumulated totals across the full survey.
 */
Result calculate(const std::vector<Input>& inputs);

} // namespace compressed_air_leak_survey
