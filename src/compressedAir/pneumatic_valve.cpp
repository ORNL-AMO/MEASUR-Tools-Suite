#include "compressedAir/pneumatic_valve.h"

#include <cmath>

namespace pneumatic_valve {

FlowRateResult calculateFlowRate(const FlowRateInput& input) {
    return {kAirFlowFactor *
            std::sqrt(input.inlet_pressure - input.outlet_pressure) *
            std::sqrt(input.inlet_pressure + input.outlet_pressure)};
}

CvResult calculateCv(const CvInput& input) {
    return {input.flow_rate /
            (kAirFlowFactor *
             std::sqrt(input.inlet_pressure - input.outlet_pressure) *
             std::sqrt(input.inlet_pressure + input.outlet_pressure))};
}

} // namespace pneumatic_valve
