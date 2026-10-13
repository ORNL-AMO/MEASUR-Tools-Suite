#include "motorDriven/motor/motor_current.h"

#include <array>

#include "motorDriven/motor/estimate_fla.h"
#include "util/CurveFitVal.h"

namespace motor_current {
namespace {

// Model reference voltage; retain the two legacy scaling passes and their order.
constexpr double kReferenceVoltage = 460.0;

double interpolateCurrent(const std::array<double, 6>& currents, double load_factor) {
    if (load_factor < 0.251) {
        return CurveFitVal({0, 0.25, 0.5}, {currents[0], currents[1], currents[2]}, 2, load_factor).calculate();
    }
    else if (load_factor < 1.251) {
        return CurveFitVal({0.25, 0.5, 0.75, 1, 1.25},
                           {currents[1], currents[2], currents[3], currents[4], currents[5]}, 4, load_factor)
            .calculate();
    }
    if (load_factor > 1.5) {
        load_factor = 1.5;
    }
    return CurveFitVal({0.75, 1.00, 1.25}, {currents[3], currents[4], currents[5]}, 2, load_factor).calculate();
}

estimate_fla::Result estimateCurrent(const Input& input) {
    return estimate_fla::calculate({input.motor_rated_power, input.motor_rpm, input.line_frequency,
                                   input.efficiency_class, input.specified_efficiency, input.rated_voltage});
}

} // namespace

Result calculate(const Input& input, const double full_load_amps) {
    const auto estimate = estimateCurrent(input);
    auto currents = estimate.partial_load_currents;
    for (auto& current : currents) {
        current *= kReferenceVoltage / input.rated_voltage;
    }
    const double adjusted_full_load_current = currents[4];
    for (auto& current : currents) {
        current *= full_load_amps / adjusted_full_load_current;
    }
    return {interpolateCurrent(currents, input.load_factor), estimate.estimated_fla};
}

double calculateOptimal(const Input& input) {
    return interpolateCurrent(estimateCurrent(input).partial_load_currents, input.load_factor);
}

} // namespace motor_current
