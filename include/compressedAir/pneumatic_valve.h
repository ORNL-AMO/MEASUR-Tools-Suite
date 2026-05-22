#pragma once

/**
 * @ingroup pneumatic_valve_calculator
 * @file pneumatic_valve.h
 * @brief Declarations for pneumatic valve flow rate and flow coefficient calculations.
 * @details Provides two functions for pneumatic valve sizing in compressed air systems:
 *          one to calculate the theoretical air flow rate through a valve with a unit flow
 *          coefficient (Cv = 1), and one to calculate the valve flow coefficient (Cv) when
 *          the actual flow rate and operating pressures are known.
 *          All calculations use U.S. customary units.
 * @see @ref pneumatic_valve_calculator for formula derivations and symbol definitions.
 */

/**
 * @ingroup pneumatic_valve_calculator
 * @namespace pneumatic_valve
 * @brief Pneumatic valve flow rate and flow coefficient (Cv) calculations.
 * @details This namespace provides two calculation modes for pneumatic valve sizing
 *          in compressed air distribution systems:
 *
 * - **Flow Rate** – calculates the theoretical air flow rate through a valve with a
 *   unit flow coefficient (Cv = 1) given the inlet and outlet pressures. For a valve
 *   with a known Cv, multiply the result by that value.
 * - **Flow Coefficient (Cv)** – calculates the dimensionless valve flow coefficient
 *   when the actual flow rate and operating pressures are known. Use this to select
 *   or verify a valve for a given application.
 *
 * Both calculations use the simplified compressible-flow pneumatic valve formula
 * with an empirically derived air flow constant for dry air at standard conditions.
 *
 * @see @ref pneumatic_valve_calculator
 */
namespace pneumatic_valve {

/**
 * @brief Empirical air flow constant for dry air at standard conditions (60°F, 14.696 psia).
 * @details This constant combines the isentropic flow factor for dry air, standard air
 *          density, and the necessary unit conversions to produce a dimensional factor
 *          valid for U.S. customary inputs (pressures in psia, flow rate in scfm).
 *          It appears in the standard simplified pneumatic valve flow formula used in
 *          industrial compressed air system design.
 * @unitb{\scfm\per\psi}
 */
inline constexpr double kAirFlowFactor = 0.6875;

// ============================================================
//  Flow Rate (Cv = 1)
// ============================================================

/**
 * @ingroup pneumatic_valve_calculator
 * @struct FlowRateInput
 * @brief Input parameters for the flow rate calculation (Cv = 1).
 */
struct FlowRateInput {
    double inlet_pressure  = 0.0; ///< Inlet (upstream) gauge pressure @unitb{\psi}
    double outlet_pressure = 0.0; ///< Outlet (downstream) gauge pressure @unitb{\psi}
};

/**
 * @ingroup pneumatic_valve_calculator
 * @struct FlowRateResult
 * @brief Result of the flow rate calculation (Cv = 1).
 */
struct FlowRateResult {
    double flow_rate = 0.0; ///< Air flow rate through a valve with Cv = 1 @unitb{\scfm}
};

/**
 * @brief Calculates the air flow rate through a pneumatic valve with unit flow coefficient (Cv = 1).
 * @details Uses the simplified compressible-flow pneumatic valve formula to compute
 *          the theoretical air flow rate for a valve with Cv = 1. The formula is
 *          equivalent to @math{Q = k_{flow} \cdot \sqrt{P_{in}^2 - P_{out}^2}}, a form
 *          commonly found in pneumatic system design references. For a valve with a
 *          specific Cv, multiply the result by that Cv value.
 *
 * @formula{pneumatic-valve-flow-rate;
 *   Q = k_{flow} \cdot \sqrt{(P_{in} - P_{out}) \cdot (P_{in} + P_{out})}
 * }
 *
 * where:
 * @symtable
 * @symrow{Q; Air flow rate through the valve (Cv = 1); \scfm}
 * @symrow{k_{flow}; Empirical air flow constant for dry air at standard conditions (0.6875); \scfm\per\psi}
 * @symrow{P_{in}; Inlet (upstream) gauge pressure; \psi}
 * @symrow{P_{out}; Outlet (downstream) gauge pressure; \psi}
 * @endsymtable
 *
 * @note The factored form @math{\sqrt{(P_{in}-P_{out})(P_{in}+P_{out})}} is algebraically
 *       identical to @math{\sqrt{P_{in}^2 - P_{out}^2}}.
 *       The constant @math{k_{flow} = 0.6875} is empirically derived for dry air at
 *       standard conditions (60°F, 14.696 psia). Pressures must be in psia (absolute).
 *       To find the flow through a valve with a specific Cv, multiply @math{Q} by that Cv.
 *
 * @param[in] input  FlowRateInput
 * @return FlowRateResult containing the flow rate in scfm.
 */
FlowRateResult calculateFlowRate(const FlowRateInput& input);

// ============================================================
//  Flow Coefficient (Cv)
// ============================================================

/**
 * @ingroup pneumatic_valve_calculator
 * @struct CvInput
 * @brief Input parameters for the valve flow coefficient (Cv) calculation.
 */
struct CvInput {
    double inlet_pressure  = 0.0; ///< Inlet (upstream) gauge pressure @unitb{\psi}
    double outlet_pressure = 0.0; ///< Outlet (downstream) gauge pressure @unitb{\psi}
    double flow_rate       = 0.0; ///< Measured or required air flow rate @unitb{\scfm}
};

/**
 * @ingroup pneumatic_valve_calculator
 * @struct CvResult
 * @brief Result of the valve flow coefficient (Cv) calculation.
 */
struct CvResult {
    double flow_coefficient = 0.0; ///< Dimensionless valve flow coefficient (Cv) @unitb{\unitless}
};

/**
 * @brief Calculates the valve flow coefficient (Cv) for a pneumatic valve.
 * @details Rearranges the pneumatic valve flow formula to solve for the dimensionless
 *          valve flow coefficient Cv when the actual flow rate and operating pressures
 *          are known. A higher Cv indicates a valve with lower flow restriction.
 *          Select a valve whose rated Cv meets or exceeds the calculated value.
 *
 * @formula{pneumatic-valve-cv;
 *   C_v = \frac{Q}{k_{flow} \cdot \sqrt{(P_{in} - P_{out}) \cdot (P_{in} + P_{out})}}
 * }
 *
 * where:
 * @symtable
 * @symrow{C_v; Dimensionless valve flow coefficient; \unitless}
 * @symrow{Q; Measured or required air flow rate; \scfm}
 * @symrow{k_{flow}; Empirical air flow constant for dry air at standard conditions (0.6875); \scfm\per\psi}
 * @symrow{P_{in}; Inlet (upstream) gauge pressure; \psi}
 * @symrow{P_{out}; Outlet (downstream) gauge pressure; \psi}
 * @endsymtable
 *
 * @note Cv is a dimensionless sizing coefficient with implicit unit dependence on the
 *       formula constant @math{k_{flow}}. Pressures must be in psia (absolute).
 *       Select a valve whose catalog Cv equals or exceeds the calculated value.
 *
 * @param[in] input  CvInput
 * @return CvResult containing the dimensionless valve flow coefficient.
 */
CvResult calculateCv(const CvInput& input);

} // namespace pneumatic_valve
