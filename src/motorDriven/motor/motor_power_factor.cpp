#include "motorDriven/motor/motor_power_factor.h"

#include <cmath>

#include "motorDriven/motor/motor_efficiency.h"

namespace motor_power_factor {

double calculate(const Input& input) {
    if (std::abs(input.load_factor) < 0.001) {
        const double motor_kw_input = motor_efficiency::calculate(
            {input.line_frequency, input.motor_rpm, input.efficiency_class, input.motor_rated_power,
             0.25, input.specified_efficiency}).zero_load_power_loss;
        // Preserve the legacy 460 V model reference even when the supplied voltage differs.
        const double motor_kva = 460 * std::sqrt(3) * input.motor_current / 1000;
        return motor_kw_input / motor_kva;
    }
    return (input.load_factor * input.motor_rated_power * 0.746) /
           (input.motor_current * input.motor_efficiency * input.rated_voltage * std::sqrt(3) / 1000);
}

} // namespace motor_power_factor
