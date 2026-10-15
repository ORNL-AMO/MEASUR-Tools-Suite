#include "motorDriven/motor/optimal_motor_power.h"

#include <cmath>

#include "motorDriven/motor/motor_current.h"
#include "motorDriven/motor/motor_efficiency.h"
#include "motorDriven/motor/motor_power.h"
#include "motorDriven/motor/motor_power_factor.h"
#include "physics/constants.h"

namespace optimal_motor_power {
namespace {

constexpr double kLoadIncrement = 0.01;
constexpr double kLoadStepsPerUnit = 100.0;
constexpr double kMaximumSearchLoad = 1.5;
constexpr double kReferenceVoltage = 460.0;

// Trial current includes the field-voltage adjustment but not the final reference-voltage scaling.
struct OperatingPoint {
    double load_factor;
    double current;
    double efficiency;
    double power;
    double shaft_power_kw;
};

OperatingPoint calculateOperatingPoint(const Input& input, double load_factor) {
    double current = motor_current::calculateOptimal(
        {input.motor_rated_power, input.motor_rpm, input.line_frequency, input.efficiency_class,
         input.specified_efficiency, load_factor, input.rated_voltage});
    current = current * ((((input.field_voltage / input.rated_voltage) - 1) * (1 + (-2 * load_factor))) + 1);
    const double efficiency = motor_efficiency::calculate(
        {input.line_frequency, input.motor_rpm, input.efficiency_class, input.motor_rated_power,
         load_factor, input.specified_efficiency}).efficiency;
    const double power_factor = motor_power_factor::calculate(
        {input.line_frequency, input.motor_rpm, input.efficiency_class, input.specified_efficiency,
         input.motor_rated_power, load_factor, current, efficiency, input.field_voltage});
    const double power = motor_power::calculate(input.field_voltage, current, power_factor);
    return {load_factor, current, efficiency, power, power * efficiency};
}

double interpolateAtLoad(double load_factor, double lower_load, double lower_value, double upper_value) {
    return lower_value + kLoadStepsPerUnit * (load_factor - lower_load) * (upper_value - lower_value);
}

} // namespace

Result calculate(const Input& input) {
    // Retain the all-zero initial lower anchor if the first trial terminates the search.
    OperatingPoint lower = {};
    OperatingPoint upper = {};
    double trial_load = 0.00;
    double target_shaft_power_kw;
    while (true) {
        upper = calculateOperatingPoint(input, trial_load);
        target_shaft_power_kw = input.optimal_motor_shaft_power * physics::conversions::kBhpToKw;
        if (upper.shaft_power_kw > target_shaft_power_kw || trial_load > kMaximumSearchLoad) {
            break;
        }
        lower = upper;
        trial_load += kLoadIncrement;
    }

    const double modeled_difference = upper.shaft_power_kw - lower.shaft_power_kw;
    const double required_difference = target_shaft_power_kw - lower.shaft_power_kw;
    const double load_factor = lower.load_factor + ((required_difference / modeled_difference) / kLoadStepsPerUnit);
    const double current = interpolateAtLoad(load_factor, lower.load_factor, lower.current, upper.current) *
                           kReferenceVoltage / input.rated_voltage;
    const double efficiency = interpolateAtLoad(load_factor, lower.load_factor, lower.efficiency, upper.efficiency);
    const double power = interpolateAtLoad(load_factor, lower.load_factor, lower.power, upper.power);
    const double power_factor = power / (current * input.field_voltage * std::sqrt(3) / 1000);
    return {power, efficiency, current, power_factor, load_factor};
}

} // namespace optimal_motor_power
