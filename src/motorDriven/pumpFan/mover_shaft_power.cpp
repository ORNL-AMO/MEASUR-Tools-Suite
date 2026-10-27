#include "motorDriven/pumpFan/mover_shaft_power.h"

#include <cmath>

namespace mover_shaft_power {

namespace {

// Empirical V-belt loss curve: two decaying exponential terms plus a high-power loss term.
// Historical source attributes the curve to AMCA 203-90 Appendix L; the exact fit derivation
// is unverified. Names describe mathematical roles rather than inferred physical mechanisms.
constexpr double kSlowDecayAmplitudePercent = 0.68759; ///< Slow-term amplitude, percentage points.
constexpr double kSlowDecayExponentPerHp = -0.019791;  ///< Signed slow-term exponent coefficient, hp^-1.
constexpr double kFastDecayAmplitudePercent = 3.7558;  ///< Fast-term amplitude, percentage points.
constexpr double kFastDecayExponentPerHp = -0.21507;   ///< Signed fast-term exponent coefficient, hp^-1.
constexpr double kHighPowerLossPercent = 3.9963;       ///< Curve's high-positive-power limit, percentage points.

// Legacy Belt Drive Tip Sheet comments cite nominal efficiencies of 93%, 95% and 98%.
// Their reference loss fractions scale the V-belt loss curve; they are not fixed efficiencies
// returned by this calculator. Retain the literal fractions rather than computing 1 - efficiency.
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
        const double belt_loss = 0;
        const double drive_efficiency = 1 - belt_loss;
        return {input.motor_shaft_power, drive_efficiency};
    } else if (input.drive == Motor::Drive::N_V_BELT_DRIVE) {
        const double belt_loss = input.motor_shaft_power *
            ((kSlowDecayAmplitudePercent * std::exp(input.motor_shaft_power * kSlowDecayExponentPerHp) +
              kFastDecayAmplitudePercent * std::exp(input.motor_shaft_power * kFastDecayExponentPerHp) +
              kHighPowerLossPercent) * kNotchedVBeltLossMultiplier / kPercentPerFraction);
        const double drive_efficiency = 1 - belt_loss / input.motor_shaft_power;
        const double mover_shaft_power = input.motor_shaft_power - belt_loss;
        return {mover_shaft_power, drive_efficiency};
    } else if (input.drive == Motor::Drive::S_BELT_DRIVE) {
        const double belt_loss = input.motor_shaft_power *
            ((kSlowDecayAmplitudePercent * std::exp(input.motor_shaft_power * kSlowDecayExponentPerHp) +
              kFastDecayAmplitudePercent * std::exp(input.motor_shaft_power * kFastDecayExponentPerHp) +
              kHighPowerLossPercent) * kSynchronousBeltLossMultiplier / kPercentPerFraction);
        const double drive_efficiency = 1 - belt_loss / input.motor_shaft_power;
        const double mover_shaft_power = input.motor_shaft_power - belt_loss;
        return {mover_shaft_power, drive_efficiency};
    } else if (input.drive == Motor::Drive::SPECIFIED) {
        const double drive_efficiency = input.specified_efficiency;
        const double mover_shaft_power = input.motor_shaft_power * input.specified_efficiency;
        return {mover_shaft_power, drive_efficiency};
    }

    const double belt_loss =
        input.motor_shaft_power *
        ((kSlowDecayAmplitudePercent * std::exp(input.motor_shaft_power * kSlowDecayExponentPerHp) +
          kFastDecayAmplitudePercent * std::exp(input.motor_shaft_power * kFastDecayExponentPerHp) +
          kHighPowerLossPercent) / kPercentPerFraction);
    const double drive_efficiency = 1 - belt_loss / input.motor_shaft_power;
    const double mover_shaft_power = input.motor_shaft_power - belt_loss;
    return {mover_shaft_power, drive_efficiency};
}

} // namespace mover_shaft_power
