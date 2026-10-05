#include "motorDriven/pump/pump_head.h"

#include <emscripten/bind.h>

using namespace emscripten;
using namespace pump_head;

EMSCRIPTEN_BINDINGS(pump_head) {
    value_object<SuctionGaugeInput>("PumpHeadSuctionGaugeInput")
        .field("specificGravity", &SuctionGaugeInput::specific_gravity)
        .field("flowRate", &SuctionGaugeInput::flow_rate)
        .field("suctionPipeDiameter", &SuctionGaugeInput::suction_pipe_diameter)
        .field("suctionGaugePressure", &SuctionGaugeInput::suction_gauge_pressure)
        .field("suctionGaugeElevation", &SuctionGaugeInput::suction_gauge_elevation)
        .field("suctionLineLossCoefficients", &SuctionGaugeInput::suction_line_loss_coefficients)
        .field("dischargePipeDiameter", &SuctionGaugeInput::discharge_pipe_diameter)
        .field("dischargeGaugePressure", &SuctionGaugeInput::discharge_gauge_pressure)
        .field("dischargeGaugeElevation", &SuctionGaugeInput::discharge_gauge_elevation)
        .field("dischargeLineLossCoefficients", &SuctionGaugeInput::discharge_line_loss_coefficients);

    value_object<SuctionTankInput>("PumpHeadSuctionTankInput")
        .field("specificGravity", &SuctionTankInput::specific_gravity)
        .field("flowRate", &SuctionTankInput::flow_rate)
        .field("suctionPipeDiameter", &SuctionTankInput::suction_pipe_diameter)
        .field("suctionTankGasOverPressure", &SuctionTankInput::suction_tank_gas_over_pressure)
        .field("suctionTankFluidSurfaceElevation", &SuctionTankInput::suction_tank_fluid_surface_elevation)
        .field("suctionLineLossCoefficients", &SuctionTankInput::suction_line_loss_coefficients)
        .field("dischargePipeDiameter", &SuctionTankInput::discharge_pipe_diameter)
        .field("dischargeGaugePressure", &SuctionTankInput::discharge_gauge_pressure)
        .field("dischargeGaugeElevation", &SuctionTankInput::discharge_gauge_elevation)
        .field("dischargeLineLossCoefficients", &SuctionTankInput::discharge_line_loss_coefficients);

    value_object<Result>("PumpHeadResult")
        .field("differentialElevationHead", &Result::differential_elevation_head)
        .field("differentialPressureHead", &Result::differential_pressure_head)
        .field("differentialVelocityHead", &Result::differential_velocity_head)
        .field("estimatedSuctionFrictionHead", &Result::estimated_suction_friction_head)
        .field("estimatedDischargeFrictionHead", &Result::estimated_discharge_friction_head)
        .field("pumpHead", &Result::pump_head);

    function("calculatePumpHeadFromSuctionGauge", &calculateFromSuctionGauge);
    function("calculatePumpHeadFromSuctionTank", &calculateFromSuctionTank);
}
