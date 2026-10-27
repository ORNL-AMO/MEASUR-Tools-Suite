#include "motorDriven/pumpFan/mover_efficiency.h"

#include "motorDriven/pumpFan/fluid_power.h"
#include "physics/constants.h"

namespace mover_efficiency {

double calculatePump(const PumpInput& input) {
    const double fluidPower   = fluid_power::calculatePump({input.specific_gravity, input.flow_rate, input.head});
    const double fluidPowerHp = fluidPower / physics::conversions::kBhpToKw;
    return fluidPowerHp / input.mover_shaft_power;
}

double calculateFan(const FanInput& input) {
    const double fluidPower = fluid_power::calculateFan({input.flow_rate, input.inlet_pressure,
        input.outlet_pressure, input.compressibility_factor, input.velocity_pressure});
    const double fluidPowerHp = fluidPower / physics::conversions::kBhpToKw;
    return fluidPowerHp / input.mover_shaft_power;
}

} // namespace mover_efficiency
