#include "compressedAir/receiver_tank.h"

namespace receiver_tank {

UsableCapacityResult calculateUsableCapacity(const UsableCapacityInput& input) {
    return {(input.tank_size / kGallonsPerCubicFoot) *
            (input.air_pressure_in - input.air_pressure_out) /
            physics::us::kAtmosphericPressurePsi};
}

SizeResult calculateGeneralSize(const GeneralInput& input) {
    return {input.air_demand * (input.atmospheric_pressure / input.allowable_pressure_drop) *
            kGallonsPerCubicFoot};
}

SizeResult calculateDedicatedStorageSize(const DedicatedStorageInput& input) {
    return {kGallonsPerCubicFoot *
            (input.length_of_demand * input.air_flow_requirement * input.atmospheric_pressure) /
            (input.initial_tank_pressure - input.final_tank_pressure)};
}

MeteredStorageResult calculateMeteredStorageSize(const MeteredStorageInput& input) {
    double tank_size_gallons =
        (kGallonsPerCubicFoot * input.length_of_demand *
         (input.air_flow_requirement - input.metered_flow_control) * input.atmospheric_pressure) /
        (input.initial_tank_pressure - input.final_tank_pressure);
    double volume_cf = tank_size_gallons * kCubicFeetPerGallon;
    double refill_time =
        (volume_cf * (input.initial_tank_pressure - input.final_tank_pressure)) /
        (input.metered_flow_control * input.atmospheric_pressure) * 60.0;
    return {tank_size_gallons, refill_time};
}

SizeResult calculateBridgingSize(const BridgingInput& input) {
    return {(input.distance_to_compressor_room / input.speed_of_air) *
            (input.air_demand_cfm / 60.0) *
            (input.atmospheric_pressure / input.allowable_pressure_drop) *
            kGallonsPerCubicFoot};
}

} // namespace receiver_tank
