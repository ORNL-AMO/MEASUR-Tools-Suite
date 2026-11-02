#include "motorDriven/pump/pump_efficiency.h"

#include "motorDriven/pump/optimal_deviation_factor.h"
#include "motorDriven/pump/optimal_pump_efficiency.h"

namespace pump_efficiency {

Result calculate(const Input& input) {
    const double average_efficiency = optimal_pump_efficiency::calculate(
        {input.style, input.rpm, input.kinematic_viscosity, input.stage_count, input.flow_rate, input.head});
    const double deviation_factor = optimal_deviation_factor::calculate(input.flow_rate);
    const double maximum_efficiency = average_efficiency * deviation_factor;
    return {average_efficiency, maximum_efficiency};
}

} // namespace pump_efficiency
