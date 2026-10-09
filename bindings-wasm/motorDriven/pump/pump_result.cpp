#include "motorDriven/pump/pump_result.h"

#include <emscripten/bind.h>

using namespace emscripten;
using namespace pump_result;

EMSCRIPTEN_BINDINGS(pump_result) {
    value_object<SystemInput>("PumpResultSystemInput")
        .field("pumpStyle", &SystemInput::pump_style)
        .field("drive", &SystemInput::drive)
        .field("specifiedDriveEfficiency", &SystemInput::specified_drive_efficiency)
        .field("specificGravity", &SystemInput::specific_gravity)
        .field("flowRate", &SystemInput::flow_rate)
        .field("head", &SystemInput::head)
        .field("differentialPressure", &SystemInput::differential_pressure)
        .field("motorRatedPower", &SystemInput::motor_rated_power)
        .field("motorRatedSpeed", &SystemInput::motor_rated_speed)
        .field("lineFrequency", &SystemInput::line_frequency)
        .field("motorEfficiencyClass", &SystemInput::motor_efficiency_class)
        .field("specifiedMotorEfficiency", &SystemInput::specified_motor_efficiency)
        .field("motorRatedVoltage", &SystemInput::motor_rated_voltage)
        .field("operatingVoltage", &SystemInput::operating_voltage)
        .field("operatingHours", &SystemInput::operating_hours)
        .field("unitCost", &SystemInput::unit_cost);

    value_object<ExistingInput>("ExistingPumpResultInput")
        .field("system", &ExistingInput::system)
        .field("motorFullLoadAmps", &ExistingInput::motor_full_load_amps)
        .field("loadEstimationMethod", &ExistingInput::load_estimation_method)
        .field("measuredMotorPower", &ExistingInput::measured_motor_power)
        .field("measuredMotorCurrent", &ExistingInput::measured_motor_current);

    value_object<ModifiedInput>("ModifiedPumpResultInput")
        .field("system", &ModifiedInput::system)
        .field("pumpEfficiency", &ModifiedInput::pump_efficiency);

    value_object<Result>("PumpResultOutput")
        .field("pumpEfficiency", &Result::pump_efficiency)
        .field("motorRatedPower", &Result::motor_rated_power)
        .field("motorShaftPower", &Result::motor_shaft_power)
        .field("moverShaftPower", &Result::mover_shaft_power)
        .field("motorEfficiency", &Result::motor_efficiency)
        .field("motorPowerFactor", &Result::motor_power_factor)
        .field("motorCurrent", &Result::motor_current)
        .field("motorPower", &Result::motor_power)
        .field("annualEnergy", &Result::annual_energy)
        .field("annualCost", &Result::annual_cost)
        .field("loadFactor", &Result::load_factor)
        .field("driveEfficiency", &Result::drive_efficiency)
        .field("estimatedFullLoadAmps", &Result::estimated_full_load_amps);

    function("calculateExistingPumpResult", &calculateExisting);
    function("calculateModifiedPumpResult", &calculateModified);
}
