#include "motorDriven/pumpFan/optimal_pump_shaft_power.h"

#include "motorDriven/pumpFan/fluid_power.h"
#include "physics/constants.h"

namespace optimal_pump_shaft_power {

double calculatePump(const PumpInput& input) {
    const double fluid_power_kw = fluid_power::calculatePump({input.specific_gravity, input.flow_rate, input.head});
    return (fluid_power_kw / input.pump_efficiency) / physics::conversions::kBhpToKw;
}

double calculateFan(const FanInput& input) {
    const double fluid_power_kw = fluid_power::calculateFan({input.flow_rate, input.inlet_pressure,
        input.outlet_pressure, input.compressibility_factor, input.velocity_pressure});
    return (fluid_power_kw / input.fan_efficiency) / physics::conversions::kBhpToKw;
}

} // namespace optimal_pump_shaft_power
