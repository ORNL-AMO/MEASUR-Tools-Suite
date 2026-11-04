#include "motorDriven/pump/optimal_pump_efficiency.h"

#include <cmath>
#include <limits>

#include "motorDriven/pump/optimal_pre_pump_efficiency.h"
#include "motorDriven/pump/optimal_specific_speed.h"
#include "motorDriven/pump/optimal_specific_speed_correction.h"

namespace optimal_pump_efficiency {

double calculate(const Input& input) {
    if (!std::isfinite(input.rpm) || input.rpm <= 0 ||
        !std::isfinite(input.kinematic_viscosity) || input.kinematic_viscosity < 0 ||
        !std::isfinite(input.head) || input.head <= 0 ||
        !std::isfinite(input.stage_count) || input.stage_count <= 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double pre_pump_efficiency = optimal_pre_pump_efficiency::calculate({input.style, input.flow_rate});
    const double viscosity_parameter =
        26.6 * (std::pow(input.kinematic_viscosity, 0.5) * std::pow(input.head, 0.0625)) /
        (std::pow(input.flow_rate, 0.375) * std::pow(input.rpm, 0.25));
    const double viscosity_correction_factor =
        std::fmin(1, (std::pow(viscosity_parameter, -(0.0547 * std::pow(viscosity_parameter, 0.69)))));
    const double specific_speed =
        optimal_specific_speed::calculate({input.rpm, input.flow_rate, input.head, input.stage_count});
    const double speed_correction = optimal_specific_speed_correction::calculate({input.style, specific_speed});
    if (!std::isfinite(pre_pump_efficiency) || !std::isfinite(viscosity_parameter) ||
        !std::isfinite(speed_correction)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    pre_pump_efficiency = pre_pump_efficiency / 100;
    const double optimal_efficiency = pre_pump_efficiency * viscosity_correction_factor - speed_correction;
    return optimal_efficiency;
}

} // namespace optimal_pump_efficiency
