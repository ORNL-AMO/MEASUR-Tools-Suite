#include "motorDriven/fans/fan_affinity_laws.h"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(fan_affinity_laws) {
    enum_<FanAffinityLaws::MotorControlType>("MotorControlType")
        .value("OnOff", FanAffinityLaws::OnOff)
        .value("TwoSpeed", FanAffinityLaws::TwoSpeed)
        .value("VSD", FanAffinityLaws::VSD)
        .value("None", FanAffinityLaws::None);

    enum_<FanAffinityLaws::FlowMode>("FlowMode")
        .value("Percent", FanAffinityLaws::Percent)
        .value("Volume", FanAffinityLaws::Volume);

    class_<FanAffinityLaws::Output>("FanAffinityLawsOutput")
        .property("annualEnergyBaseline", &FanAffinityLaws::Output::annualEnergyBaseline)
        .property("annualEnergyNew", &FanAffinityLaws::Output::annualEnergyNew)
        .property("annualCostSavings", &FanAffinityLaws::Output::annualCostSavings);

    value_object<FanAffinityLaws::Input>("FanAffinityLawsInput")
        .field("electricityCost", &FanAffinityLaws::Input::electricityCost)
        .field("driveEfficiency", &FanAffinityLaws::Input::driveEfficiency)
        .field("motorEfficiency", &FanAffinityLaws::Input::motorEfficiency)
        .field("flowPercentBaseline", &FanAffinityLaws::Input::flowPercentBaseline)
        .field("operatingHours", &FanAffinityLaws::Input::operatingHours)
        .field("motorPower", &FanAffinityLaws::Input::motorPower)
        .field("ratedFlow", &FanAffinityLaws::Input::ratedFlow)
        .field("motorControlTypeCurrent", &FanAffinityLaws::Input::motorControlTypeCurrent)
        .field("motorControlTypeNew", &FanAffinityLaws::Input::motorControlTypeNew)
        .field("flowMode", &FanAffinityLaws::Input::flowMode)
        .field("desiredFlowRate", &FanAffinityLaws::Input::desiredFlowRate);

    /**
     * Function calculate computes the annual energy and cost savings based on current and changed state of motor control
     * Function changeFanSize takes in two paramters current fan diameter and new fan diameter and
     * computes the annual energy and cost savings based on current and changed state of motor control and  change in fan size.
     */
    class_<FanAffinityLaws>("FanAffinityLaws")
        .constructor<const FanAffinityLaws::Input&>()
        .constructor<const double, const double, const double, const double, const double, const double, const double,
            const FanAffinityLaws::MotorControlType, const FanAffinityLaws::MotorControlType,
            const FanAffinityLaws::FlowMode, const double>()
        .function("calculate", &FanAffinityLaws::calculate)
        .function("changeFanSize", &FanAffinityLaws::changeFanSize);
}