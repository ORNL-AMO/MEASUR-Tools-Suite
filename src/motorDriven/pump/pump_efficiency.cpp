#include "motorDriven/pump/pump_efficiency.h"

#include <algorithm>
#include <cmath>
#include <limits>

#include "motorDriven/pump/optimal_deviation_factor.h"
#include "motorDriven/pump/optimal_pump_efficiency.h"
#include "motorDriven/pump/optimal_pre_pump_efficiency.h"
#include "motorDriven/pump/optimal_specific_speed_correction.h"

namespace pump_efficiency {

Limits getLimits(Pump::Style style) {
    const auto base = optimal_pre_pump_efficiency::flowLimits(style);
    const auto deviation = optimal_deviation_factor::flowLimits();
    const auto speed = optimal_specific_speed_correction::speedLimits(style);
    if (!std::isfinite(base.minimum)) {
        const double nan = std::numeric_limits<double>::quiet_NaN();
        return {false, nan, nan, nan, nan};
    }
    return {true, std::max(base.minimum, deviation.minimum), std::min(base.maximum, deviation.maximum),
            speed.minimum, speed.maximum};
}

Result calculate(const Input& input) {
    const double average_efficiency = optimal_pump_efficiency::calculate(
        {input.style, input.rpm, input.kinematic_viscosity, input.stage_count, input.flow_rate, input.head});
    const double deviation_factor = optimal_deviation_factor::calculate(input.flow_rate);
    const double maximum_efficiency = average_efficiency * deviation_factor;
    if (!std::isfinite(average_efficiency) || !std::isfinite(maximum_efficiency)) {
        const double nan = std::numeric_limits<double>::quiet_NaN();
        return {nan, nan};
    }
    return {average_efficiency, maximum_efficiency};
}

} // namespace pump_efficiency
