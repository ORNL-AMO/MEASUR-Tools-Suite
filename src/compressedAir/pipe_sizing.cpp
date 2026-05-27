#include "compressedAir/pipe_sizing.h"

#include <cmath>

namespace pipe_sizing {

Result calculate(const Input& input) {
    const double cross_sectional_area =
        (physics::conversions::kIn2PerFt2 * input.airflow * input.atmospheric_pressure) /
        (input.design_velocity * physics::conversions::kSecondsPerMinute *
         (input.airline_pressure + input.atmospheric_pressure));
    return {cross_sectional_area, std::sqrt(cross_sectional_area / kCircleAreaFactor)};
}

} // namespace pipe_sizing
