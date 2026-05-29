#pragma once

/**
 * @ingroup orifice_method_calculator
 * @file orifice_method.h
 * @brief Declarations for the orifice method compressed air leak flow rate estimation.
 * @details Provides a free function to estimate compressed air leak flow rate and annual
 *          air loss using pressure and orifice geometry measurements. All calculations
 *          use U.S. customary units with isentropic compressible-flow theory.
 * @see @ref orifice_method_calculator for formula derivations and symbol definitions.
 */

#include <cmath>

#include "physics/constants.h"

/**
 * @ingroup orifice_method_calculator
 * @namespace orifice_method
 * @brief Compressed air leak flow estimation using orifice pressure and geometry.
 * @details The orifice method estimates the air loss from a compressed air leak by
 *          treating the leak path as a sharp-edged orifice with known diameter and
 *          discharge coefficient. When the supply pressure exceeds approximately twice
 *          the atmospheric pressure, flow through the orifice is choked (sonic), and the
 *          mass flow rate depends on the upstream (supply) pressure and temperature rather
 *          than the downstream condition.
 *
 *          The calculation proceeds through a series of isentropic gas-dynamics steps:
 *          1. Convert air temperature from °F to °R for thermodynamic calculations.
 *          2. Compute air density at supply conditions and at standard conditions using
 *             the ideal gas law.
 *          3. Apply the isentropic choking relations to find sonic density and velocity
 *             at the orifice throat.
 *          4. Compute the mass flow rate per orifice from throat conditions.
 *          5. Convert to volumetric flow (scfm) using standard-condition density and
 *             scale by the number of orifices.
 *          6. Scale by annual operating time to estimate yearly air consumption.
 *
 *          This method provides the highest field accuracy of the leak-survey techniques
 *          that do not require an inline flow meter, provided the discharge coefficient
 *          is known or can be estimated from the orifice geometry.
 *
 * @see @ref orifice_method_calculator
 */
namespace orifice_method {

// ============================================================
//  Orifice Method
// ============================================================

/**
 * @ingroup orifice_method_calculator
 * @struct Input
 * @brief Input parameters for the orifice method compressed air leak calculation.
 */
struct Input {
    double operating_time  = 0.0;                               ///< Annual system operating time @unitb{\hour}
    double air_temp        = 0.0;                               ///< Compressed air temperature at the leak point @unitb{\degreeFahrenheit}
    double atm_pressure    = physics::us::kAtmosphericPressurePsi; ///< Local atmospheric (barometric) pressure @unitb{\psia}
    double discharge_coef  = 1.0;                               ///< Orifice discharge coefficient, accounting for vena contracta @unitb{\unitless}
    double diameter        = 0.0;                               ///< Orifice (leak opening) diameter @unitb{\inch}
    double supply_pressure = 0.0;                               ///< Compressed air supply pressure (gauge) @unitb{\psig}
    int    num_orifices    = 1;                                 ///< Number of identical orifice leak points @unitb{\unitless}
};

/**
 * @ingroup orifice_method_calculator
 * @struct Result
 * @brief Result of the orifice method leak flow rate and annual consumption calculation.
 */
struct Result {
    double standard_density   = 0.0; ///< Air density at standard (atmospheric) conditions @unitb{\pound\per\cubicFoot}
    double sonic_density      = 0.0; ///< Air density at the isentropic sonic throat @unitb{\pound\per\cubicFoot}
    double leak_velocity      = 0.0; ///< Sonic air velocity at the orifice throat @unitb{\foot\per\second}
    double leak_rate_lbm_min  = 0.0; ///< Mass flow rate of leaked air through one orifice @unitb{\pound\per\minute}
    double leak_rate_scfm     = 0.0; ///< Volumetric flow rate of leaked air through one orifice @unitb{\scfm}
    double leak_rate_estimate = 0.0; ///< Total volumetric leak flow rate through all orifices @unitb{\scfm}
    double annual_consumption = 0.0; ///< Estimated annual compressed air loss @unitb{\kscf}
};

/**
 * @brief Estimates compressed air leak flow rate and annual consumption using the orifice method.
 * @details Applies isentropic choked-flow theory to estimate the mass flow rate of air
 *          escaping through a small orifice at sonic conditions. The flow is assumed choked
 *          when the supply absolute pressure exceeds twice atmospheric pressure, which is
 *          the typical case for industrial compressed air systems operating above
 *          14.7 psia (i.e., above ~15 psig gauge).
 *
 *          All densities use the ideal gas law:
 *          @f$\rho = P \cdot 144 / (R_{air} \cdot T_R)@f$
 *          where the factor 144 converts pressure from psia (lbf/in²) to lbf/ft²,
 *          @f$R_{air} = 53.34@f$ ft·lbf/(lbm·°R) is the specific gas constant for dry air,
 *          and @f$T_R@f$ is absolute temperature in degrees Rankine.
 *
 *          The isentropic choking relations use @f$\gamma = 1.4@f$ for dry air.
 *
 * **Temperature Conversion:**
 * @formula{orifice-method-temperature;
 *   T_R = T_F + 459.67
 * }
 *
 * where:
 * @symtable
 * @symrow{T_R; Air temperature in degrees Rankine; \degreeRankine}
 * @symrow{T_F; Compressed air temperature at the leak point; \degreeFahrenheit}
 * @symrow{459.67; Fahrenheit-to-Rankine offset; \degreeRankine}
 * @endsymtable
 *
 * **Absolute Supply Pressure:**
 * @formula{orifice-method-abs-pressure;
 *   P_{abs} = P_{atm} + P_{supply}
 * }
 *
 * where:
 * @symtable
 * @symrow{P_{abs}; Absolute supply pressure; \psia}
 * @symrow{P_{atm}; Local atmospheric (barometric) pressure; \psia}
 * @symrow{P_{supply}; Compressed air supply pressure (gauge); \psig}
 * @endsymtable
 *
 * **Air Density at Supply Conditions:**
 * @formula{orifice-method-ca-density;
 *   \rho_{ca} = \frac{P_{abs} \cdot 144}{R_{air} \cdot T_R}
 * }
 *
 * where:
 * @symtable
 * @symrow{\rho_{ca}; Air density at supply (compressed) conditions; \pound\per\cubicFoot}
 * @symrow{P_{abs}; Absolute supply pressure; \psia}
 * @symrow{144; Unit conversion factor (in² per ft²); \squareInch\per\squareFoot}
 * @symrow{R_{air}; Specific gas constant for dry air (53.34); \unitless}
 * @symrow{T_R; Air temperature in degrees Rankine; \degreeRankine}
 * @endsymtable
 *
 * **Air Density at Standard (Atmospheric) Conditions:**
 * @formula{orifice-method-standard-density;
 *   \rho_{std} = \frac{P_{atm} \cdot 144}{R_{air} \cdot T_R}
 * }
 *
 * where:
 * @symtable
 * @symrow{\rho_{std}; Air density at standard atmospheric conditions; \pound\per\cubicFoot}
 * @symrow{P_{atm}; Local atmospheric pressure; \psia}
 * @symrow{144; Unit conversion factor (in² per ft²); \squareInch\per\squareFoot}
 * @symrow{R_{air}; Specific gas constant for dry air (53.34); \unitless}
 * @symrow{T_R; Air temperature in degrees Rankine; \degreeRankine}
 * @endsymtable
 *
 * **Sonic Density at Orifice Throat (Isentropic Choked Flow):**
 * @formula{orifice-method-sonic-density;
 *   \rho^* = \rho_{ca} \cdot \left(\frac{2}{\gamma + 1}\right)^{\frac{1}{\gamma - 1}}
 * }
 *
 * where:
 * @symtable
 * @symrow{\rho^*; Air density at the isentropic sonic throat; \pound\per\cubicFoot}
 * @symrow{\rho_{ca}; Air density at supply conditions; \pound\per\cubicFoot}
 * @symrow{\gamma; Ratio of specific heats for dry air (1.4); \unitless}
 * @endsymtable
 *
 * **Sonic Velocity at Orifice Throat:**
 * @formula{orifice-method-sonic-velocity;
 *   V^* = \sqrt{\frac{2\gamma}{\gamma + 1} \cdot R_{air} \cdot T_R \cdot g_c}
 * }
 *
 * where:
 * @symtable
 * @symrow{V^*; Sonic air velocity at the orifice throat; \foot\per\second}
 * @symrow{\gamma; Ratio of specific heats for dry air (1.4); \unitless}
 * @symrow{R_{air}; Specific gas constant for dry air (53.34); \unitless}
 * @symrow{T_R; Air temperature in degrees Rankine; \degreeRankine}
 * @symrow{g_c; Gravitational conversion constant (32.2); \unitless}
 * @endsymtable
 *
 * **Mass Flow Rate per Orifice:**
 * @formula{orifice-method-mass-flow;
 *   \dot{m} = \rho^* \cdot \frac{\pi d^2}{4 \cdot 144} \cdot V^* \cdot 60 \cdot C_d
 * }
 *
 * where:
 * @symtable
 * @symrow{\dot{m}; Mass flow rate of leaked air through one orifice; \pound\per\minute}
 * @symrow{\rho^*; Air density at the sonic throat; \pound\per\cubicFoot}
 * @symrow{d; Orifice (leak opening) diameter; \inch}
 * @symrow{144; Unit conversion factor (in² per ft²); \squareInch\per\squareFoot}
 * @symrow{V^*; Sonic velocity at the orifice throat; \foot\per\second}
 * @symrow{60; Seconds per minute conversion; \second\per\minute}
 * @symrow{C_d; Orifice discharge coefficient; \unitless}
 * @endsymtable
 *
 * **Volumetric Flow Rate per Orifice:**
 * @formula{orifice-method-volume-flow;
 *   Q_{scfm} = \frac{\dot{m}}{\rho_{std}}
 * }
 *
 * where:
 * @symtable
 * @symrow{Q_{scfm}; Volumetric flow rate of leaked air through one orifice; \scfm}
 * @symrow{\dot{m}; Mass flow rate per orifice; \pound\per\minute}
 * @symrow{\rho_{std}; Air density at standard atmospheric conditions; \pound\per\cubicFoot}
 * @endsymtable
 *
 * **Total Leak Rate:**
 * @formula{orifice-method-total-leak;
 *   Q_{leak} = Q_{scfm} \cdot n
 * }
 *
 * where:
 * @symtable
 * @symrow{Q_{leak}; Total volumetric leak flow rate through all orifices; \scfm}
 * @symrow{Q_{scfm}; Volumetric flow rate per orifice; \scfm}
 * @symrow{n; Number of identical orifice leak points; \unitless}
 * @endsymtable
 *
 * **Annual Consumption:**
 * @formula{orifice-method-annual-consumption;
 *   C_{annual} = \frac{Q_{leak} \cdot t_{op} \cdot 60}{1000}
 * }
 *
 * where:
 * @symtable
 * @symrow{C_{annual}; Estimated annual compressed air loss; \kscf}
 * @symrow{Q_{leak}; Total leak flow rate; \scfm}
 * @symrow{t_{op}; Annual system operating time; \hour}
 * @symrow{60; Minutes per hour conversion; \minute\per\hour}
 * @symrow{1000; Standard cubic feet per kiloscf conversion; \unitless}
 * @endsymtable
 *
 * @note Supply pressure must be in gauge (psig); the calculation converts to absolute
 *       pressure internally. Air temperature must be in degrees Fahrenheit; conversion
 *       to Rankine is performed internally. The discharge coefficient @f$C_d@f$ for a
 *       sharp-edged orifice is typically 0.61; for a well-rounded nozzle it approaches
 *       1.0. For most leak-survey work, @f$C_d = 1.0@f$ is used as a conservative
 *       upper bound.
 *
 * @param[in] input  Input
 * @return Result containing all intermediate and final flow values.
 */
Result calculate(const Input& input);

} // namespace orifice_method
