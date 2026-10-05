#include "motorDriven/pump/pump_head.h"

#include "physics/constants.h"

namespace pump_head {
namespace {

struct CommonHeads {
    double suction_velocity_head;
    double discharge_velocity_head;
    double suction_friction_head;
    double discharge_friction_head;
};

double velocity(const double diameter_feet, const double flow_cubic_feet_per_second) {
    return flow_cubic_feet_per_second /
           (physics::kPi * diameter_feet / 2.0 * diameter_feet / 2.0);
}

double velocityHead(const double velocity_feet_per_second) {
    return ((velocity_feet_per_second * velocity_feet_per_second) / 2.0) /
           physics::us::kGravityFtPerSec2;
}

CommonHeads calculateCommonHeads(const double flow_rate, const double suction_pipe_diameter,
                                 const double suction_line_loss_coefficients,
                                 const double discharge_pipe_diameter,
                                 const double discharge_line_loss_coefficients) {
    const double flow =
        flow_rate / physics::conversions::kGallonsPerMinutePerCubicFootPerSecond;
    const double suctionVelocityHead =
        velocityHead(velocity(suction_pipe_diameter / physics::conversions::kInchesPerFoot, flow));
    const double dischargeVelocityHead =
        velocityHead(velocity(discharge_pipe_diameter / physics::conversions::kInchesPerFoot, flow));

    return {
        suctionVelocityHead,
        dischargeVelocityHead,
        suction_line_loss_coefficients * suctionVelocityHead,
        discharge_line_loss_coefficients * dischargeVelocityHead,
    };
}

Result makeResult(const double elevation_head, const double pressure_head,
                  const double velocity_head_differential, const CommonHeads& common_heads) {
    const double pumpHead = elevation_head + pressure_head + velocity_head_differential +
                            common_heads.suction_friction_head + common_heads.discharge_friction_head;

    return {
        elevation_head,
        pressure_head,
        velocity_head_differential,
        common_heads.suction_friction_head,
        common_heads.discharge_friction_head,
        pumpHead,
    };
}

} // namespace

Result calculateFromSuctionGauge(const SuctionGaugeInput& input) {
    const auto commonHeads = calculateCommonHeads(
        input.flow_rate, input.suction_pipe_diameter, input.suction_line_loss_coefficients,
        input.discharge_pipe_diameter, input.discharge_line_loss_coefficients);
    const double elevationHead = input.discharge_gauge_elevation - input.suction_gauge_elevation;
    const double pressureHead =
        ((input.discharge_gauge_pressure - input.suction_gauge_pressure) /
         physics::conversions::kPsiPerFootOfWater) /
        input.specific_gravity;
    const double velocityHeadDifferential =
        commonHeads.discharge_velocity_head - commonHeads.suction_velocity_head;

    return makeResult(elevationHead, pressureHead, velocityHeadDifferential, commonHeads);
}

Result calculateFromSuctionTank(const SuctionTankInput& input) {
    const auto commonHeads = calculateCommonHeads(
        input.flow_rate, input.suction_pipe_diameter, input.suction_line_loss_coefficients,
        input.discharge_pipe_diameter, input.discharge_line_loss_coefficients);
    const double elevationHead =
        input.discharge_gauge_elevation - input.suction_tank_fluid_surface_elevation;
    const double pressureHead =
        ((input.discharge_gauge_pressure - input.suction_tank_gas_over_pressure) /
         physics::conversions::kPsiPerFootOfWater) /
        input.specific_gravity;

    return makeResult(elevationHead, pressureHead, commonHeads.discharge_velocity_head, commonHeads);
}

} // namespace pump_head
