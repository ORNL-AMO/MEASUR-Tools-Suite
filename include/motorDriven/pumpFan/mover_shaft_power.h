#pragma once

/**
 * @ingroup mover_shaft_power_calculator
 * @file mover_shaft_power.h
 * @brief Stateless calculation of pump/fan shaft input after motor-drive losses.
 * @authors Gina Accawi, Allie Ledbetter
 * @see @ref mover_shaft_power_calculator for equations, examples and limitations.
 */

#include "motorDriven/motor/MotorData.h"

/**
 * @ingroup mover_shaft_power_calculator
 * @namespace mover_shaft_power
 * @brief Calculates the motor shaft output delivered through a pump/fan drive.
 */
namespace mover_shaft_power {

/** @brief Complete required motor shaft power and drive data. */
struct Input {
    double motor_shaft_power;     ///< Mechanical motor shaft output @unitb{\horsepower}.
    Motor::Drive drive;           ///< Existing drive selection; unknown values use the ordinary V-belt curve.
    double specified_efficiency; ///< Supplied drive efficiency fraction @unitb{\unitless}; used only for SPECIFIED.
};

/** @brief Delivered shaft power and drive efficiency; plain values without cleanup. */
struct Result {
    double mover_shaft_power; ///< Mechanical input at the pump/fan shaft @unitb{\horsepower}.
    double drive_efficiency;  ///< Fraction of motor shaft output delivered @unitb{\unitless}.
};

/**
 * @brief Calculates power delivered through the selected drive to a pump or fan.
 * @param[in] input Complete data with units documented per member; not modified.
 * @return Delivered shaft power in hp and drive efficiency as a dimensionless fraction.
 * @details Direct drive returns the supplied power and efficiency 1. SPECIFIED uses the supplied
 * efficiency fraction; other drives use the retained empirical belt-loss curves. No validation,
 * defaults or clamping are applied. Signed and nonfinite arithmetic is retained, including NaN
 * belt-drive efficiency at zero motor shaft power. This is a forward drive-loss calculation,
 * distinct from the reverse-direction @ref optimal_motor_shaft_power_calculator calculation.
 * @see @ref mover_shaft_power_calculator for formulas, worked examples and interpretation limits.
 */
Result calculate(const Input& input);

} // namespace mover_shaft_power
