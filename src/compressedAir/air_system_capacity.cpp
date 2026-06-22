#include "compressedAir/air_system_capacity.h"

namespace air_system_capacity {

Output calculate(const Input& input) {
    auto receiver_capacities = input.receivers;

    double total_receiver_volume = 0.0;
    for (auto& gallons : receiver_capacities) {
        gallons /= kGallonsPerCubicFoot;
        total_receiver_volume += gallons;
    }

    return {input.pipe_lengths.totalPipeVolume,
            total_receiver_volume,
            input.pipe_lengths.totalPipeVolume + total_receiver_volume,
            receiver_capacities,
            input.pipe_lengths};
}

} // namespace air_system_capacity
