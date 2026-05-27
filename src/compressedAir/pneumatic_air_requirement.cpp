#include "compressedAir/pneumatic_air_requirement.h"

#include <cmath>

namespace pneumatic_air_requirement {

AirRequirementResult calculateSingleActing(const SingleActingInput& input) {
    auto const volume_air_intake =
        (physics::kPi / 4.0 * std::pow(input.cylinder_diameter, 2) *
         input.cylinder_stroke * input.cycles_per_min) /
        physics::conversions::kFt3ToIn3;
    auto const compression_ratio =
        (input.air_pressure + physics::us::kAtmosphericPressurePsi) /
        physics::us::kAtmosphericPressurePsi;
    return {volume_air_intake, compression_ratio, volume_air_intake * compression_ratio};
}

AirRequirementResult calculateDoubleActing(const DoubleActingInput& input) {
    auto const volume_air_intake_single =
        (physics::kPi / 4.0 * std::pow(input.cylinder_diameter, 2) *
         input.cylinder_stroke * input.cycles_per_min) /
        physics::conversions::kFt3ToIn3;
    auto const volume_air_intake =
        (2.0 * physics::conversions::kFt3ToIn3 * volume_air_intake_single -
         (physics::kPi / 4.0 * std::pow(input.piston_rod_diameter, 2) *
          input.cylinder_stroke * input.cycles_per_min)) /
        physics::conversions::kFt3ToIn3;
    auto const compression_ratio =
        (input.air_pressure + physics::us::kAtmosphericPressurePsi) /
        physics::us::kAtmosphericPressurePsi;
    return {volume_air_intake, compression_ratio, volume_air_intake * compression_ratio};
}

} // namespace pneumatic_air_requirement
