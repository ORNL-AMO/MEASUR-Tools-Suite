#include "compressedAir/operating_cost.h"

namespace operating_cost {

Result calculateOperatingCost(const Input& input) {
    const double run_time_unloaded = 100.0 - input.run_time_loaded;
    const double cost_for_loaded =
        (input.motor_bhp * physics::conversions::kBhpToKw * input.annual_operating_hours *
         input.cost_of_electricity * (input.run_time_loaded / 100.0)) /
        (input.efficiency_loaded / 100.0);
    const double cost_for_unloaded =
        (input.motor_bhp * physics::conversions::kBhpToKw * input.annual_operating_hours *
         input.cost_of_electricity * (input.bhp_unloaded / 100.0) *
         (run_time_unloaded / 100.0)) /
        (input.efficiency_unloaded / 100.0);
    return {run_time_unloaded, cost_for_loaded, cost_for_unloaded,
            cost_for_loaded + cost_for_unloaded};
}

} // namespace operating_cost
