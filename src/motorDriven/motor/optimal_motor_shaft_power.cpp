#include "motorDriven/motor/optimal_motor_shaft_power.h"

#include <cmath>

namespace optimal_motor_shaft_power {

namespace {

// Retained reverse-direction V-belt fit, evaluated at mover shaft power. The legacy source
// points to MoverShaftPower for background but does not establish this fit's derivation.
// Names describe mathematical roles; these coefficients differ from the forward model.
constexpr double kSlowDecayAmplitudePercent = 0.7489574; ///< Slow-term amplitude, percentage points.
constexpr double kSlowDecayExponentPerHp = -0.02067997;  ///< Signed slow-term exponent coefficient, hp^-1.
constexpr double kFastDecayAmplitudePercent = 4.136368;  ///< Fast-term amplitude, percentage points.
constexpr double kFastDecayExponentPerHp = -0.226025;    ///< Signed fast-term exponent coefficient, hp^-1.
constexpr double kHighPowerLossPercent = 4.162707;       ///< Curve's high-positive-power limit, percentage points.

// Reference loss fractions scale the belt curve; they are not fixed returned efficiencies.
// The forward model's historical comments connect these to nominal 93%, 95% and 98%
// efficiencies. Retain the literal fractions rather than computing 1 - efficiency.
constexpr double kVBeltReferenceLossFraction = 0.07;          ///< Reference V-belt loss, dimensionless.
constexpr double kNotchedVBeltReferenceLossFraction = 0.05;   ///< Reference notched V-belt loss, dimensionless.
constexpr double kSynchronousBeltReferenceLossFraction = 0.02; ///< Reference synchronous-belt loss, dimensionless.
constexpr double kNotchedVBeltLossMultiplier =
    kNotchedVBeltReferenceLossFraction / kVBeltReferenceLossFraction; ///< Relative loss scale, dimensionless.
constexpr double kSynchronousBeltLossMultiplier =
    kSynchronousBeltReferenceLossFraction / kVBeltReferenceLossFraction; ///< Relative loss scale, dimensionless.
constexpr double kPercentPerFraction = 100; ///< Percentage points per unit fraction, dimensionless.

} // namespace

Result calculate(const Input& input) {
    if (input.drive == Motor::Drive::DIRECT_DRIVE) {
        const double drive_efficiency = 1;
        const double motor_shaft_power = input.mover_shaft_power;
        return {motor_shaft_power, drive_efficiency};
    } else if (input.drive == Motor::Drive::N_V_BELT_DRIVE) {
        const double loss_fraction =
            (kSlowDecayAmplitudePercent * std::exp(input.mover_shaft_power * kSlowDecayExponentPerHp) +
             kFastDecayAmplitudePercent * std::exp(input.mover_shaft_power * kFastDecayExponentPerHp) +
             kHighPowerLossPercent) * kNotchedVBeltLossMultiplier / kPercentPerFraction;
        const double belt_loss = loss_fraction * input.mover_shaft_power;
        const double drive_efficiency = 1 / (1 + loss_fraction);
        const double motor_shaft_power = input.mover_shaft_power + belt_loss;
        return {motor_shaft_power, drive_efficiency};
    } else if (input.drive == Motor::Drive::S_BELT_DRIVE) {
        const double loss_fraction =
            (kSlowDecayAmplitudePercent * std::exp(input.mover_shaft_power * kSlowDecayExponentPerHp) +
             kFastDecayAmplitudePercent * std::exp(input.mover_shaft_power * kFastDecayExponentPerHp) +
             kHighPowerLossPercent) * kSynchronousBeltLossMultiplier / kPercentPerFraction;
        const double belt_loss = loss_fraction * input.mover_shaft_power;
        const double drive_efficiency = 1 / (1 + loss_fraction);
        const double motor_shaft_power = input.mover_shaft_power + belt_loss;
        return {motor_shaft_power, drive_efficiency};
    } else if (input.drive == Motor::Drive::SPECIFIED) {
        const double drive_efficiency = input.specified_efficiency;
        const double motor_shaft_power = input.mover_shaft_power / input.specified_efficiency;
        return {motor_shaft_power, drive_efficiency};
    }

    // Ordinary V-belt, including the retained fallback for unknown C++ drive values.
    const double loss_fraction =
        (kSlowDecayAmplitudePercent * std::exp(input.mover_shaft_power * kSlowDecayExponentPerHp) +
         kFastDecayAmplitudePercent * std::exp(input.mover_shaft_power * kFastDecayExponentPerHp) +
         kHighPowerLossPercent) / kPercentPerFraction;
    const double belt_loss = loss_fraction * input.mover_shaft_power;
    const double drive_efficiency = 1 / (1 + loss_fraction);
    const double motor_shaft_power = input.mover_shaft_power + belt_loss;
    return {motor_shaft_power, drive_efficiency};
}

} // namespace optimal_motor_shaft_power
