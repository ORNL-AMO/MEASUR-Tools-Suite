#include "motorDriven/fans/fan_affinity_laws.h"

#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(fan_affinity_laws) {
    emscripten::enum_<fan_affinity_laws::MotorControlType>("MotorControlType")
        .value("OnOff", fan_affinity_laws::MotorControlType::OnOff)
        .value("TwoSpeed", fan_affinity_laws::MotorControlType::TwoSpeed)
        .value("VSD", fan_affinity_laws::MotorControlType::VSD)
        .value("None", fan_affinity_laws::MotorControlType::None);

    emscripten::enum_<fan_affinity_laws::FlowMode>("FlowMode")
        .value("Percent", fan_affinity_laws::FlowMode::Percent)
        .value("Volume", fan_affinity_laws::FlowMode::Volume);

    emscripten::value_object<fan_affinity_laws::Input>("FanAffinityLawsInput")
        .field("electricityCost", &fan_affinity_laws::Input::electricity_cost)
        .field("driveEfficiency", &fan_affinity_laws::Input::drive_efficiency)
        .field("motorEfficiency", &fan_affinity_laws::Input::motor_efficiency)
        .field("flowPercentBaseline", &fan_affinity_laws::Input::flow_percent_baseline)
        .field("operatingHours", &fan_affinity_laws::Input::operating_hours)
        .field("motorPower", &fan_affinity_laws::Input::motor_power)
        .field("ratedFlow", &fan_affinity_laws::Input::rated_flow)
        .field("motorControlTypeCurrent", &fan_affinity_laws::Input::motor_control_type_current)
        .field("motorControlTypeNew", &fan_affinity_laws::Input::motor_control_type_new)
        .field("flowMode", &fan_affinity_laws::Input::flow_mode)
        .field("desiredFlowRate", &fan_affinity_laws::Input::desired_flow_rate);

    emscripten::value_object<fan_affinity_laws::Result>("FanAffinityLawsResult")
        .field("annualEnergyBaseline", &fan_affinity_laws::Result::annual_energy_baseline)
        .field("annualEnergyNew", &fan_affinity_laws::Result::annual_energy_new)
        .field("annualCostSavings", &fan_affinity_laws::Result::annual_cost_savings);

    emscripten::value_object<fan_affinity_laws::TimeFactorResult>("FanAffinityLawsTimeFactorResult")
        .field("factor", &fan_affinity_laws::TimeFactorResult::factor)
        .field("timeAbove50Percent", &fan_affinity_laws::TimeFactorResult::time_above_50_percent)
        .field("timeAt50Percent", &fan_affinity_laws::TimeFactorResult::time_at_50_percent)
        .field("timeAt0Percent", &fan_affinity_laws::TimeFactorResult::time_at_0_percent);

    emscripten::function("calculateFanAffinityLaws", &fan_affinity_laws::calculate);
    emscripten::function("calculateFanAffinityLawsWithFanSize", &fan_affinity_laws::changeFanSize);
    emscripten::function("get50PercentTimeFactor", &fan_affinity_laws::get50PercentTimeFactor);
}
