#pragma once

/**
 * @file insulated_tank_reduction.h
 * @ingroup insulated_tank_reduction_calculator
 * @brief Declares structs and functions for the Insulated Tank Reduction Calculator.
 * @copybrief insulated_tank_reduction_calculator
 */

/**
 * @ingroup insulated_tank_reduction_calculator
 * @namespace insulated_tank_reduction
 * @brief Insulated tank heat loss calculations for treasure hunt measures.
 * @details Provides a function-based API for estimating heat loss and annual energy
 * cost for a hot vertical cylindrical tank, with or without thermal insulation.
 * Air properties are evaluated at the ambient temperature using fourth-order
 * polynomial fits to tabulated U.S. customary air data. The calculation uses
 * gravitational acceleration g = 32.174 ft/s² and the Stefan–Boltzmann constant
 * in BTU/(hr·ft²·°R⁴).
 * @see insulated_tank_reduction_calculator
 */
namespace insulated_tank_reduction {

/**
 * @ingroup insulated_tank_reduction_calculator
 * @struct InsulatedTankInput
 * @brief Input parameters for the insulated tank heat loss calculation.
 * @details Temperatures are in degrees Rankine. Geometry (height, diameter,
 * thickness) is in feet. Thermal conductivities are in BTU/(hr·ft·°F).
 * System efficiency is a fraction (0–1). Set insulation_thickness ≤ 0 to
 * compute heat loss for a bare (uninsulated) tank; insulation_conductivity
 * is then ignored.
 */
struct InsulatedTankInput {
    int    operating_hours         = 0;   ///< Annual operating hours @unitb{\hour\per\year}
    double tank_height             = 0.0; ///< Tank lateral height @unitb{\foot}
    double tank_diameter           = 0.0; ///< Tank inner diameter @unitb{\foot}
    double tank_thickness          = 0.0; ///< Tank wall thickness @unitb{\foot}
    double tank_emissivity         = 0.0; ///< Emissivity of the bare tank outer surface (0–1) @unitb{\unitless}
    double tank_conductivity       = 0.0; ///< Thermal conductivity of the tank wall material @unitb{\btu\per(\hour\foot\degreeFahrenheit)}
    double tank_temperature        = 0.0; ///< Temperature of the tank fluid (inner surface) @unitb{\degreeRankine}
    double ambient_temperature     = 0.0; ///< Ambient air temperature @unitb{\degreeRankine}
    double system_efficiency       = 1.0; ///< Heating system efficiency (0–1) @unitb{\unitless}
    double insulation_thickness    = 0.0; ///< Insulation layer thickness; set ≤ 0 for bare tank @unitb{\foot}
    double insulation_conductivity = 0.0; ///< Thermal conductivity of the insulation material @unitb{\btu\per(\hour\foot\degreeFahrenheit)}
    double jacket_emissivity       = 0.0; ///< Emissivity of the insulation jacket outer surface (0–1) @unitb{\unitless}
    double surface_temperature     = 0.0; ///< Outer surface temperature (jacket or bare tank outer wall) @unitb{\degreeRankine}
};

/**
 * @ingroup insulated_tank_reduction_calculator
 * @struct InsulatedTankOutput
 * @brief Output results for the insulated tank heat loss calculation.
 */
struct InsulatedTankOutput {
    double heat_loss        = 0.0; ///< Instantaneous heat loss @unitb{\btu\per\hour}
    double annual_heat_loss = 0.0; ///< Annual heat loss, adjusted for system efficiency @unitb{\btu\per\year}
};

/**
 * @ingroup insulated_tank_reduction_calculator
 * @brief Calculates heat loss and annual heat loss for a tank.
 * @details Dispatches to @ref insulatedTankHeatLoss or @ref bareTankHeatLoss
 * based on whether insulation_thickness is positive.
 * @see insulated_tank_reduction_calculator
 *
 * @param[in] input @ref InsulatedTankInput with tank geometry, material
 *                  properties, operating conditions, and insulation parameters.
 * @return @ref InsulatedTankOutput with heat loss and annual heat loss.
 */
InsulatedTankOutput calculate(const InsulatedTankInput& input);

/**
 * @ingroup insulated_tank_reduction_calculator
 * @brief Calculates heat loss for a tank wrapped in insulation.
 * @details Air properties are evaluated at the ambient temperature. The outer
 * surface temperature (insulation jacket) drives the Rayleigh number and
 * radiation term. A cylindrical multi-layer resistance model (tank wall +
 * insulation annulus + outer air film) yields the overall heat transfer
 * coefficient, which is combined with a radiation term to produce total heat loss.
 * @see insulated_tank_reduction_insulated_formula
 *
 * @param[in] input @ref InsulatedTankInput describing the insulated tank system.
 * @return @ref InsulatedTankOutput with heat loss and annual heat loss.
 */
InsulatedTankOutput insulatedTankHeatLoss(const InsulatedTankInput& input);

/**
 * @ingroup insulated_tank_reduction_calculator
 * @brief Calculates heat loss for an uninsulated (bare) tank.
 * @details Air properties are evaluated at the ambient temperature. The tank
 * fluid temperature is used as the surface temperature driving the Rayleigh
 * number and radiation term. The resistance model includes only the tank wall
 * and the outer air film.
 * @see insulated_tank_reduction_bare_formula
 *
 * @param[in] input @ref InsulatedTankInput describing the bare tank system
 *                  (insulation_thickness and insulation_conductivity are ignored).
 * @return @ref InsulatedTankOutput with heat loss and annual heat loss.
 */
InsulatedTankOutput bareTankHeatLoss(const InsulatedTankInput& input);

/**
 * @ingroup insulated_tank_reduction_calculator
 * @brief Computes the Rayleigh number for natural convection along a vertical
 *        cylinder in U.S. customary units.
 * @details Uses gravitational acceleration g = 32.174 ft/s².
 * @see insulated_tank_reduction_rayleigh_formula
 *
 * @param[in] thermal_expansion   Volumetric thermal expansion coefficient of air (1/T_ambient) @unitb{\per\degreeRankine}
 * @param[in] surface_temperature Outer surface temperature @unitb{\degreeRankine}
 * @param[in] ambient_temperature Ambient air temperature @unitb{\degreeRankine}
 * @param[in] diameter            Tank inner diameter @unitb{\foot}
 * @param[in] kin_viscosity       Kinematic viscosity of air @unitb{\foot\squared\per\second}
 * @param[in] thermal_diffusivity Thermal diffusivity of air @unitb{\foot\squared\per\second}
 * @return Dimensionless Rayleigh number @unitb{\unitless}
 */
double rayleighNumber(double thermal_expansion, double surface_temperature,
                      double ambient_temperature, double diameter,
                      double kin_viscosity, double thermal_diffusivity);

/**
 * @ingroup insulated_tank_reduction_calculator
 * @brief Computes the natural convection heat transfer coefficient for a vertical
 *        cylinder using the Ra^(1/3) empirical correlation.
 * @details Applies h = 0.125 × Ra^(1/3) × k / d, valid for turbulent natural
 * convection along a vertical surface.
 * @see insulated_tank_reduction_natural_convection_formula
 *
 * @param[in] rayleigh     Rayleigh number @unitb{\unitless}
 * @param[in] conductivity Thermal conductivity of air @unitb{\btu\per\hour\foot\degreeFahrenheit}
 * @param[in] diameter     Tank outer diameter @unitb{\foot}
 * @return Natural convection heat transfer coefficient @unitb{\btu\per\hour\foot\squared\degreeFahrenheit}
 */
double naturalConvectionCoefficient(double rayleigh, double conductivity, double diameter);

} // namespace insulated_tank_reduction
