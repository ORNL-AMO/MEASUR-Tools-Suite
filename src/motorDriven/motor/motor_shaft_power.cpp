#include "motorDriven/motor/motor_shaft_power.h"

#include <cmath>

#include "motorDriven/motor/motor_current.h"
#include "motorDriven/motor/motor_efficiency.h"
#include "motorDriven/motor/motor_power.h"
#include "motorDriven/motor/motor_power_factor.h"
#include "physics/constants.h"

namespace motor_shaft_power {
namespace {

constexpr double kLoadIncrement = 0.01;
constexpr double kLoadStepsPerUnit = 100.0;
constexpr double kMaximumSearchLoad = 1.5;

// A trial operating point at nameplate voltage, before field-voltage correction.
struct OperatingPoint {
    double load_factor;
    double current;
    double power_factor;
    double efficiency;
    double power;
    double estimated_fla;
};

motor_current::Result calculateCurrentAtLoad(const Input& input, double load_factor) {
    return motor_current::calculate(
        {input.motor_rated_power, input.motor_rpm, input.line_frequency, input.efficiency_class,
         input.specified_efficiency, load_factor, input.rated_voltage},
        input.full_load_amps);
}

OperatingPoint calculateOperatingPoint(const Input& input, double load_factor,
                                       const motor_current::Result& current_result) {
    const double efficiency = motor_efficiency::calculate(
        {input.line_frequency, input.motor_rpm, input.efficiency_class, input.motor_rated_power,
         load_factor, input.specified_efficiency}).efficiency;
    const double power_factor = motor_power_factor::calculate(
        {input.line_frequency, input.motor_rpm, input.efficiency_class, input.specified_efficiency,
         input.motor_rated_power, load_factor, current_result.current, efficiency, input.rated_voltage});
    const double power = motor_power::calculate(input.rated_voltage, current_result.current, power_factor);
    return {load_factor, current_result.current, power_factor, efficiency, power, current_result.estimated_fla};
}

// Retain the 1% interpolation arithmetic, including extrapolation outside the selected pair.
double interpolateAtLoad(double load_factor, double lower_load, double lower_value, double upper_value) {
    return lower_value + kLoadStepsPerUnit * (load_factor - lower_load) * (upper_value - lower_value);
}

double adjustPowerFactorForVoltage(const OperatingPoint& point, double voltage_ratio) {
    return point.power_factor / ((((voltage_ratio - 1) * (-2 * point.load_factor + 1)) + 1) * voltage_ratio);
}

double adjustCurrentForVoltage(const OperatingPoint& point, double voltage_ratio) {
    return ((voltage_ratio - 1) * (1 - 2 * point.load_factor) + 1) * point.current;
}

Result calculateFromPower(const Input& input) {
    // The legacy lower anchor is all zeroes, rather than an evaluated no-load point.
    OperatingPoint lower = {};
    OperatingPoint upper = {};
    double trial_load = kLoadIncrement;
    while (true) {
        const auto current_result = calculateCurrentAtLoad(input, trial_load);
        upper = calculateOperatingPoint(input, trial_load, current_result);
        if (upper.power > input.motor_measured_power || trial_load > kMaximumSearchLoad) {
            break;
        }
        lower = upper;
        trial_load += kLoadIncrement;
    }

    const double modeled_power_difference = upper.power - lower.power;
    const double measured_power_difference = input.motor_measured_power - lower.power;
    const double load_factor = lower.load_factor +
                               ((measured_power_difference / modeled_power_difference) / kLoadStepsPerUnit);
    const double efficiency = interpolateAtLoad(load_factor, lower.load_factor, lower.efficiency, upper.efficiency);

    const double voltage_ratio = input.field_voltage / input.rated_voltage;
    const double lower_power_factor = adjustPowerFactorForVoltage(lower, voltage_ratio);
    const double upper_power_factor = adjustPowerFactorForVoltage(upper, voltage_ratio);
    const double power_factor = interpolateAtLoad(load_factor, lower.load_factor,
                                                  lower_power_factor, upper_power_factor);
    const double current = input.motor_measured_power / (input.field_voltage * std::sqrt(3) * power_factor / 1000);
    const double shaft_power = (input.motor_measured_power * efficiency) / physics::conversions::kBhpToKw;
    return {shaft_power, current, power_factor, efficiency, input.motor_measured_power,
            upper.estimated_fla, load_factor};
}

Result calculateFromCurrent(const Input& input) {
    motor_current::Result upper_current = {};
    double trial_load = 0.00;
    while (true) {
        upper_current = calculateCurrentAtLoad(input, trial_load);
        if (upper_current.current > input.field_current || trial_load > kMaximumSearchLoad) {
            break;
        }
        trial_load += kLoadIncrement;
    }
    const auto upper = calculateOperatingPoint(input, trial_load, upper_current);

    // Subtract from the accumulated trial load; the first bracket can start at negative load.
    trial_load -= kLoadIncrement;
    const auto lower_current = calculateCurrentAtLoad(input, trial_load);
    const auto lower = calculateOperatingPoint(input, trial_load, lower_current);

    // Select the pair using unadjusted current, then apply the retained voltage correction.
    const double voltage_ratio = input.field_voltage / input.rated_voltage;
    const double lower_adjusted_current = adjustCurrentForVoltage(lower, voltage_ratio);
    const double upper_adjusted_current = adjustCurrentForVoltage(upper, voltage_ratio);
    const double modeled_current_difference = upper_adjusted_current - lower_adjusted_current;
    const double measured_current_difference = input.field_current - lower_adjusted_current;
    const double load_factor = lower.load_factor +
                               (measured_current_difference / modeled_current_difference) / kLoadStepsPerUnit;

    const double efficiency = interpolateAtLoad(load_factor, lower.load_factor, lower.efficiency, upper.efficiency);
    const double power = interpolateAtLoad(load_factor, lower.load_factor, lower.power, upper.power);
    const double power_factor = power / (input.field_current * input.field_voltage * std::sqrt(3) / 1000);
    const double shaft_power = (power * efficiency) / physics::conversions::kBhpToKw;
    return {shaft_power, input.field_current, power_factor, efficiency, power, upper.estimated_fla, load_factor};
}

} // namespace

Result calculate(const Input& input) {
    if (input.load_estimation_method == Motor::LoadEstimationMethod::POWER) {
        return calculateFromPower(input);
    }
    // Preserve the legacy CURRENT fallback for any other enum value.
    return calculateFromCurrent(input);
}

} // namespace motor_shaft_power
