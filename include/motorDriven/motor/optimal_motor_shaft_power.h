#pragma once

/**
 * @ingroup optimal_motor_shaft_power_calculator
 * @file optimal_motor_shaft_power.h
 * @brief Stateless motor shaft output required to supply a pump/fan shaft duty.
 * @authors Subhankar Mishra, Gina Accawi
 * @see @ref optimal_motor_shaft_power_calculator for formulas, examples and interpretation limits.
 */

#include "motorDriven/motor/MotorData.h"

/**
 * @ingroup optimal_motor_shaft_power_calculator
 * @namespace optimal_motor_shaft_power
 * @brief Calculates motor mechanical output required upstream of a pump/fan drive.
 */
namespace optimal_motor_shaft_power {

/** @brief Complete required mover shaft power and drive data. */
struct Input {
    double mover_shaft_power;     ///< Required mechanical input at the pump/fan shaft @unitb{\horsepower}.
    Motor::Drive drive;           ///< Existing drive selection; unknown values use the ordinary V-belt curve.
    double specified_efficiency; ///< Supplied drive efficiency fraction @unitb{\unitless}; used only for SPECIFIED.
};

/** @brief Required motor shaft power and drive efficiency; plain values without cleanup. */
struct Result {
    double motor_shaft_power; ///< Mechanical motor shaft output required before the drive @unitb{\horsepower}.
    double drive_efficiency;  ///< Fraction of motor shaft output delivered to the mover @unitb{\unitless}.
};

/**
 * @brief Calculates motor shaft output required to supply the selected drive and mover.
 * @param[in] input Complete data with units documented per member; not modified.
 * @return Required motor shaft power in hp and drive efficiency as a dimensionless fraction.
 * @details Direct drive returns supplied power and efficiency 1. SPECIFIED divides supplied power
 * by its efficiency fraction. Belt drives add retained empirical losses evaluated at mover power;
 * belt efficiency remains finite at zero mover power. No validation, defaults or clamping are
 * applied; signed and nonfinite arithmetic is retained. "Optimal" describes the supplied duty,
 * not equipment optimization. The belt curve differs from the forward mover_shaft_power model.
 * @see @ref optimal_motor_shaft_power_calculator for equations, examples and interpretation limits.
 */
Result calculate(const Input& input);

} // namespace optimal_motor_shaft_power
