#include <emscripten/bind.h>

#include "motorDriven/motor/MotorData.h"
#include "motorDriven/motor/MotorShaftPower.h"
#include "motorDriven/pump/HeadTool.h"
#include "motorDriven/pump/PumpResult.h"

using namespace emscripten;

// headToolSuctionTank
EMSCRIPTEN_BINDINGS(head_tool_suction_tank_class) {
    class_<HeadToolSuctionTank>("HeadToolSuctionTank")
        .constructor<double, double, double, double, double, double, double, double, double, double>()
        .function("calculate", &HeadToolSuctionTank::calculate);
}
// headTool
EMSCRIPTEN_BINDINGS(head_tool_class) {
    class_<HeadTool>("HeadTool")
        .constructor<double, double, double, double, double, double, double, double, double, double>()
        .function("calculate", &HeadTool::calculate);
}
// headToolOutput
EMSCRIPTEN_BINDINGS(head_tool_output) {
    class_<HeadToolBase::Output>("HeadToolOutput")
        .constructor<double, double, double, double, double, double>()
        .property("differentialElevationHead", &HeadToolBase::Output::elevationHead)
        .property("differentialPressureHead", &HeadToolBase::Output::pressureHead)
        .property("differentialVelocityHead", &HeadToolBase::Output::velocityHeadDifferential)
        .property("estimatedSuctionFrictionHead", &HeadToolBase::Output::suctionHead)
        .property("estimatedDischargeFrictionHead", &HeadToolBase::Output::dischargeHead)
        .property("pumpHead", &HeadToolBase::Output::pumpHead);
}

// resultsExisting & resultsModified
EMSCRIPTEN_BINDINGS(pump_results) {
    class_<Pump::Input>("PumpResultInput")
        .constructor<Pump::Style, double, double, Motor::Drive, double, double, int, Pump::SpecificSpeed, double>();

    class_<Pump::FieldData>("PumpFieldData")
        .constructor<double, double, Motor::LoadEstimationMethod, double, double, double>();

    class_<PumpResult>("PumpResult")
        .constructor<Pump::Input, Motor, Pump::FieldData, double, double>()
        .function("calculateExisting", &PumpResult::calculateExisting)
        .function("calculateModified", &PumpResult::calculateModified)
        .function("getAnnualSavingsPotential", &PumpResult::getAnnualSavingsPotential)
        .function("getOptimizationRating", &PumpResult::getOptimizationRating);
}

EMSCRIPTEN_BINDINGS(pump_results_output) {
    class_<PumpResult::Output>("PumpResults")
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double>()
        .property("pump_efficiency", &PumpResult::Output::pumpEfficiency)
        .property("motor_rated_power", &PumpResult::Output::motorRatedPower)
        .property("motor_shaft_power", &PumpResult::Output::motorShaftPower)
        .property("mover_shaft_power", &PumpResult::Output::moverShaftPower)
        .property("motor_efficiency", &PumpResult::Output::motorEfficiency)
        .property("motor_power_factor", &PumpResult::Output::motorPowerFactor)
        .property("motor_current", &PumpResult::Output::motorCurrent)
        .property("motor_power", &PumpResult::Output::motorPower)
        .property("annual_energy", &PumpResult::Output::annualEnergy)
        .property("annual_cost", &PumpResult::Output::annualCost)
        .property("load_factor", &PumpResult::Output::loadFactor)
        .property("drive_efficiency", &PumpResult::Output::driveEfficiency)
        .property("estimatedFLA", &PumpResult::Output::estimatedFLA);
}
