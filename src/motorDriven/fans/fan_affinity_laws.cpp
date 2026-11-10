#include "motorDriven/fans/fan_affinity_laws.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace fan_affinity_laws {
namespace {

void validateInput(const Input& input) {
    if (input.electricity_cost <= 0) {
        throw std::invalid_argument("Electricity cost must be greater than 0.");
    }
    if (input.drive_efficiency <= 0 || input.drive_efficiency > 100) {
        throw std::invalid_argument("Drive efficiency must be between 0 and 100.");
    }
    if (input.motor_efficiency <= 0 || input.motor_efficiency > 100) {
        throw std::invalid_argument("Motor efficiency must be between 0 and 100.");
    }
    if (input.flow_percent_baseline < 0 || input.flow_percent_baseline > 100) {
        throw std::invalid_argument("Flow percent baseline must be between 0 and 100.");
    }
    if ((input.motor_control_type_current == MotorControlType::VSD ||
            input.motor_control_type_current == MotorControlType::TwoSpeed) &&
        (!std::isfinite(input.flow_percent_baseline) || input.flow_percent_baseline == 0)) {
        throw std::invalid_argument("VSD and Two-Speed baseline flow must be finite and greater than 0.");
    }
    if (input.operating_hours <= 0 || input.operating_hours > 8760) {
        throw std::invalid_argument("Operating hours must be between 1 and 8760.");
    }
    if (input.motor_power <= 0) {
        throw std::invalid_argument("Motor power must be greater than 0.");
    }
    if (input.rated_flow <= 0) {
        throw std::invalid_argument("Rated flow must be greater than 0.");
    }
    if (input.flow_mode == FlowMode::Percent &&
        (input.desired_flow_rate < 0 || input.desired_flow_rate > 100)) {
        throw std::invalid_argument("Desired flow rate percentage must be between 0 and 100.");
    }
    if (input.flow_mode == FlowMode::Volume && input.desired_flow_rate < 0) {
        throw std::invalid_argument("Desired flow rate volume must be greater than or equal to 0.");
    }
}

double controlFactor(const MotorControlType control, const double flow_fraction) {
    if (control == MotorControlType::VSD) {
        return std::pow(flow_fraction, 3);
    }
    if (control == MotorControlType::TwoSpeed) {
        return get50PercentTimeFactor(flow_fraction).factor;
    }
    return 1;
}

Result compute(const Input& input, const double diameter_ratio) {
    double desired_flow_volume = 0;
    if (input.flow_mode == FlowMode::Percent) {
        desired_flow_volume = input.desired_flow_rate * input.rated_flow / 100;
    }
    else if (input.flow_mode == FlowMode::Volume) {
        desired_flow_volume = input.desired_flow_rate;
    }

    const double motor_efficiency = input.motor_efficiency / 100;
    const double drive_efficiency = input.drive_efficiency / 100;
    const double power_current = input.motor_power / (motor_efficiency * drive_efficiency);
    const double base_factor = controlFactor(input.motor_control_type_current, input.flow_percent_baseline / 100);
    const double power_full_speed = power_current / base_factor;
    const double new_flow_fraction = desired_flow_volume / (input.rated_flow * std::pow(diameter_ratio, 3));
    const double new_factor = controlFactor(input.motor_control_type_new, new_flow_fraction);
    const double power_new = power_full_speed * new_factor * std::pow(diameter_ratio, 5);

    return {power_current * input.operating_hours,
        power_new * input.operating_hours,
        (power_current - power_new) * input.operating_hours * input.electricity_cost};
}

} // namespace

Result calculate(const Input& input) {
    validateInput(input);
    return compute(input, 1);
}

Result changeFanSize(const Input& input, const double fan_diameter_current, const double fan_diameter) {
    validateInput(input);
    if (fan_diameter_current <= 0 || fan_diameter <= 0) {
        throw std::invalid_argument("Fan diameters must be greater than 0.");
    }
    return compute(input, fan_diameter / fan_diameter_current);
}

TimeFactorResult get50PercentTimeFactor(const double flow_percent) {
    if (!std::isfinite(flow_percent) || flow_percent < 0 || flow_percent > 1) {
        throw std::invalid_argument("Two-Speed flow fraction must be finite and between 0 and 1.");
    }
    const double time_above_50_percent = std::max((flow_percent - 0.5) / 0.5, 0.0);
    const double time_at_0_percent = std::max((0.5 - flow_percent) / 0.5, 0.0);
    const double time_at_50_percent = 1 - time_above_50_percent - time_at_0_percent;
    return {time_above_50_percent + time_at_50_percent * 0.125,
        time_above_50_percent, time_at_50_percent, time_at_0_percent};
}

} // namespace fan_affinity_laws
