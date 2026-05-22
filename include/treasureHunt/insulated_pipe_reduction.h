#pragma once

/**
 * @file insulated_pipe_reduction.h
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Declares structs and functions for the Insulated Pipe Reduction Calculator.
 * @copybrief insulated_pipe_reduction_calculator
 */

#include <vector>

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @namespace insulated_pipe_reduction
 * @brief Insulated pipe heat loss calculations for treasure hunt measures.
 * @details Provides a function-based API for estimating heat loss per unit length and annual
 * heat loss from a hot pipe, with or without insulation. The iterative solver converges on
 * the surface temperature and interface temperature using heat transfer correlations for
 * forced and free convection and radiation. Air properties are computed from fourth-order
 * polynomial fits to tabulated data.
 * @see insulated_pipe_reduction_calculator
 */
namespace insulated_pipe_reduction {

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @struct InsulatedPipeInput
 * @brief Input parameters for the insulated pipe heat loss calculation.
 * @details All temperatures are in Kelvin and all lengths are in SI units (meters or
 * millimeters as noted). The material coefficient vectors must each contain exactly 5
 * values representing polynomial fit coefficients (order 4 down to order 0) for thermal
 * conductivity as a function of temperature.
 */
struct InsulatedPipeInput {
    int    operating_hours                   = 0;   ///< Annual operating hours @unitb{\hour\per\year}
    double pipe_length                       = 0.0; ///< Total pipe length @unitb{\meter}
    double pipe_diameter                     = 0.0; ///< Outer pipe diameter @unitb{\meter}
    double pipe_thickness                    = 0.0; ///< Pipe wall thickness @unitb{\meter}
    double pipe_temperature                  = 0.0; ///< Pipe inner surface (fluid) temperature @unitb{\kelvin}
    double ambient_temperature               = 0.0; ///< Ambient air temperature @unitb{\kelvin}
    double wind_velocity                     = 0.0; ///< Wind velocity across the pipe @unitb{\meter\per\second}
    double system_efficiency                 = 1.0; ///< Heating system efficiency (0–1) @unitb{\unitless}
    double insulation_thickness              = 0.0; ///< Insulation thickness; set ≤ 0 for uninsulated pipe @unitb{\meter}
    double pipe_emissivity                   = 0.0; ///< Emissivity of the bare pipe outer surface (0–1) @unitb{\unitless}
    double jacket_emissivity                 = 0.0; ///< Emissivity of the insulation jacket outer surface (0–1) @unitb{\unitless}
    std::vector<double> pipe_material_coefficients;        ///< 4th-order polynomial fit coefficients for pipe thermal conductivity
    std::vector<double> insulation_material_coefficients;  ///< 4th-order polynomial fit coefficients for insulation thermal conductivity
};

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @struct InsulatedPipeOutput
 * @brief Output results for the insulated pipe heat loss calculation.
 */
struct InsulatedPipeOutput {
    double heat_loss_per_length = 0.0; ///< Converged heat loss per unit length @unitb{\watt\per\meter}
    double annual_heat_loss     = 0.0; ///< Annual heat loss for the full pipe @unitb{\watt\hour\per\year}
};

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Calculates heat loss per unit length and annual heat loss for a pipe.
 * @details Dispatches to @ref insulatedPipeHeatLoss or @ref bareInsulatedPipeHeatLoss based
 * on whether insulation thickness is positive. The iterative solver (max 30 iterations)
 * converges when the change in heat loss per unit length is less than 0.0001 W/m.
 * @see insulated_pipe_reduction_calculator
 *
 * @param[in] input @ref InsulatedPipeInput with all pipe and insulation geometry, material
 *                  properties, and environmental conditions.
 * @return @ref InsulatedPipeOutput with heat loss per unit length @unitb{\watt\per\meter}
 *         and annual heat loss @unitb{\watt\hour\per\year}.
 */
InsulatedPipeOutput calculate(const InsulatedPipeInput& input);

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Calculates heat loss per unit length for a pipe with insulation.
 * @details Iteratively solves for surface temperature and pipe-insulation interface temperature
 * using forced and free convection and radiation on the insulation jacket outer surface.
 * @see insulated_pipe_reduction_insulated_formula
 *
 * @param[in] input @ref InsulatedPipeInput describing the insulated pipe system.
 * @return @ref InsulatedPipeOutput with heat loss per unit length and annual heat loss.
 */
InsulatedPipeOutput insulatedPipeHeatLoss(const InsulatedPipeInput& input);

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Calculates heat loss per unit length for an uninsulated (bare) pipe.
 * @details Iteratively solves for surface temperature using convection and radiation directly
 * on the bare pipe outer surface. No insulation resistance is included.
 * @see insulated_pipe_reduction_bare_formula
 *
 * @param[in] input @ref InsulatedPipeInput describing the bare pipe system
 *                  (insulation_thickness is ignored).
 * @return @ref InsulatedPipeOutput with heat loss per unit length and annual heat loss.
 */
InsulatedPipeOutput bareInsulatedPipeHeatLoss(const InsulatedPipeInput& input);

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Computes the thermal resistance of a cylindrical shell.
 * @see insulated_pipe_reduction_thermal_resistance_formula
 *
 * @param[in] diameter_a          Outer diameter of the shell @unitb{\meter}
 * @param[in] diameter_b          Outer diameter used in the logarithm (numerator) @unitb{\meter}
 * @param[in] diameter_c          Inner diameter used in the logarithm (denominator) @unitb{\meter}
 * @param[in] thermal_conductivity Thermal conductivity of the shell material @unitb{\watt\per(\meter\kelvin)}
 * @return Thermal resistance per unit length @unitb{(\meter\kelvin)\per\watt}
 */
double thermalResistance(double diameter_a, double diameter_b, double diameter_c,
                         double thermal_conductivity);

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Computes the Reynolds number for external cross-flow over a cylinder.
 * @see insulated_pipe_reduction_reynolds_formula
 *
 * @param[in] diameter             Outer diameter of the cylinder @unitb{\meter}
 * @param[in] wind_velocity        Free-stream wind velocity @unitb{\meter\per\second}
 * @param[in] kinematic_viscosity  Kinematic viscosity of air at the film temperature @unitb{\meter\squared\per\second}
 * @return Dimensionless Reynolds number @unitb{\unitless}
 */
double reynoldsNumber(double diameter, double wind_velocity, double kinematic_viscosity);

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Computes the Rayleigh number for natural convection from a horizontal cylinder.
 * @see insulated_pipe_reduction_rayleigh_formula
 *
 * @param[in] expansion_coefficient Volumetric thermal expansion coefficient of air @unitb{\per\kelvin}
 * @param[in] surface_temperature   Outer surface temperature @unitb{\kelvin}
 * @param[in] ambient_temperature   Ambient air temperature @unitb{\kelvin}
 * @param[in] diameter              Outer diameter of the cylinder @unitb{\meter}
 * @param[in] kinematic_viscosity   Kinematic viscosity of air at the film temperature @unitb{\meter\squared\per\second}
 * @param[in] alpha                 Thermal diffusivity of air at the film temperature @unitb{\meter\squared\per\second}
 * @return Dimensionless Rayleigh number @unitb{\unitless}
 */
double rayleighNumber(double expansion_coefficient, double surface_temperature,
                      double ambient_temperature, double diameter,
                      double kinematic_viscosity, double alpha);

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Combines forced and free convection Nusselt numbers using the Churchill–Bernstein power-sum rule.
 * @details Uses the rule Nu = (Nu_forced^4 + Nu_free^4)^(1/4) to combine the two contributions.
 * @see insulated_pipe_reduction_nusselt_formula
 *
 * @param[in] nusselt_forced Forced-convection Nusselt number @unitb{\unitless}
 * @param[in] nusselt_free   Free-convection Nusselt number @unitb{\unitless}
 * @return Combined Nusselt number @unitb{\unitless}
 */
double nusseltNumber(double nusselt_forced, double nusselt_free);

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Computes the forced-convection Nusselt number for external flow over a cylinder
 *        using the Churchill–Bernstein correlation.
 * @see insulated_pipe_reduction_nusselt_forced_formula
 *
 * @param[in] reynolds Reynolds number @unitb{\unitless}
 * @param[in] prandtl  Prandtl number of air at film temperature @unitb{\unitless}
 * @return Forced-convection Nusselt number @unitb{\unitless}
 */
double nusseltForcedConvection(double reynolds, double prandtl);

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Computes the free-convection Nusselt number for a horizontal cylinder
 *        using the Churchill–Chu correlation.
 * @see insulated_pipe_reduction_nusselt_free_formula
 *
 * @param[in] rayleigh Rayleigh number @unitb{\unitless}
 * @param[in] prandtl  Prandtl number of air at film temperature @unitb{\unitless}
 * @return Free-convection Nusselt number @unitb{\unitless}
 */
double nusseltFreeConvection(double rayleigh, double prandtl);

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Computes the linearized radiative heat transfer coefficient.
 * @see insulated_pipe_reduction_radiation_formula
 *
 * @param[in] emissivity          Surface emissivity (0–1) @unitb{\unitless}
 * @param[in] surface_temperature Outer surface temperature @unitb{\kelvin}
 * @param[in] ambient_temperature Ambient air temperature @unitb{\kelvin}
 * @return Radiative heat transfer coefficient @unitb{\watt\per(\meter\squared\kelvin)}
 */
double radiativeHeatTransferCoefficient(double emissivity, double surface_temperature,
                                        double ambient_temperature);

/**
 * @ingroup insulated_pipe_reduction_calculator
 * @brief Computes the convective heat transfer coefficient from a Nusselt number.
 * @see insulated_pipe_reduction_convection_formula
 *
 * @param[in] nusselt          Combined Nusselt number @unitb{\unitless}
 * @param[in] air_conductivity Thermal conductivity of air at film temperature @unitb{\watt\per(\meter\kelvin)}
 * @param[in] diameter         Outer diameter of the surface @unitb{\meter}
 * @return Convective heat transfer coefficient @unitb{\watt\per(\meter\squared\kelvin)}
 */
double convectiveHeatTransferCoefficient(double nusselt, double air_conductivity, double diameter);

} // namespace insulated_pipe_reduction
