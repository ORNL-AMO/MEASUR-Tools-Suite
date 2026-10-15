#include "motorDriven/pumpFan/fluid_power.h"

#include "physics/constants.h"

namespace fluid_power {
namespace {

// Retained US customary divisors; their exact historical provenance is unverified.
constexpr double kPumpFlowHeadPerHp = 3961.38; ///< US gpm-ft per hp for specific gravity 1.
constexpr double kFanFlowPressurePerHp = 6362; ///< cfm-inches water column per hp.

} // namespace

double calculatePump(const PumpInput& input) {
    return physics::conversions::kBhpToKw * input.flow_rate * input.head * input.specific_gravity /
           kPumpFlowHeadPerHp;
}

double calculateFan(const FanInput& input) {
    return physics::conversions::kBhpToKw * input.flow_rate *
           (input.outlet_pressure - input.inlet_pressure - input.velocity_pressure) *
           input.compressibility_factor / kFanFlowPressurePerHp;
}

} // namespace fluid_power
