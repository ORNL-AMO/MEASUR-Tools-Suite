#include "compressedAir/air_velocity.h"

#include "physics/constants.h"

namespace air_velocity {

pipe_data::PipeData calculate(const Input& input) {
    const auto compressed_air_velocity = [&input](const double pipe_area) {
        return (input.airflow * input.atmospheric_pressure / (input.pipe_pressure + input.atmospheric_pressure)) *
               (physics::conversions::kIn2PerFt2 / pipe_area) *
               (1.0 / physics::conversions::kSecondsPerMinute);
    };

    return pipe_data::PipeData(compressed_air_velocity);
}

} // namespace air_velocity
