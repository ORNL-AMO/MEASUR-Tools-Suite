#include "motorDriven/motor/motor_power.h"

#include <cmath>

namespace motor_power {

double calculate(const double rated_voltage, const double motor_current, const double power_factor) {
    return rated_voltage * motor_current * std::sqrt(3) * power_factor / 1000;
}

} // namespace motor_power
