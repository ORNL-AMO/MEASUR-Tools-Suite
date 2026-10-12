#include "motorDriven/motor/poles.h"

#include <cmath>

namespace poles {

int calculate(const double motor_rpm, const Motor::LineFrequency line_frequency) {
    if (line_frequency == Motor::LineFrequency::FREQ60) {
        if (motor_rpm >= 3240 && motor_rpm <= 3600) {
            return 2;
        }
        else if (motor_rpm >= 1620 && motor_rpm <= 1800) {
            return 4;
        }
        else if (motor_rpm >= 1080 && motor_rpm <= 1200) {
            return 6;
        }
        else if (motor_rpm >= 810 && motor_rpm <= 900) {
            return 8;
        }
        else if (motor_rpm >= 648 && motor_rpm <= 720) {
            return 10;
        }
        else if (motor_rpm >= 540 && motor_rpm <= 600) {
            return 12;
        }
    }
    else if (line_frequency == Motor::LineFrequency::FREQ50) {
        if (motor_rpm >= 2700 && motor_rpm <= 3000) {
            return 2;
        }
        else if (motor_rpm >= 1350 && motor_rpm <= 1500) {
            return 4;
        }
        else if (motor_rpm >= 900 && motor_rpm <= 1000) {
            return 6;
        }
        else if (motor_rpm >= 675 && motor_rpm <= 750) {
            return 8;
        }
        else if (motor_rpm >= 540 && motor_rpm <= 600) {
            return 10;
        }
        else if (motor_rpm >= 450 && motor_rpm <= 500) {
            return 12;
        }
    }

    // Preserve the established 60 Hz fallback when speed is outside the nominal bands.
    if (motor_rpm > 3600) {
        return 2;
    }

    const auto calculated_poles = static_cast<int>(std::floor(std::floor(7200 / motor_rpm) / 2) * 2);
    return (calculated_poles > 12) ? 12 : calculated_poles;
}

} // namespace poles
