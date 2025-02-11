#include "motorDriven/pumpFan/PumpEfficiency.h"
#include "motorDriven/pumpFan/PumpShaftPower.h"
#include "motorDriven/pumpFan/OptimalSpecificSpeedCorrection.h"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(pump_enums)
{
    enum_<Pump::Style>("PumpStyle")
        .value("END_SUCTION_SLURRY", Pump::Style::END_SUCTION_SLURRY)
        .value("END_SUCTION_SEWAGE", Pump::Style::END_SUCTION_SEWAGE)
        .value("END_SUCTION_STOCK", Pump::Style::END_SUCTION_STOCK)
        .value("END_SUCTION_SUBMERSIBLE_SEWAGE", Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE)
        .value("API_DOUBLE_SUCTION", Pump::Style::API_DOUBLE_SUCTION)
        .value("MULTISTAGE_BOILER_FEED", Pump::Style::MULTISTAGE_BOILER_FEED)
        .value("END_SUCTION_ANSI_API", Pump::Style::END_SUCTION_ANSI_API)
        .value("AXIAL_FLOW", Pump::Style::AXIAL_FLOW)
        .value("DOUBLE_SUCTION", Pump::Style::DOUBLE_SUCTION)
        .value("VERTICAL_TURBINE", Pump::Style::VERTICAL_TURBINE)
        .value("LARGE_END_SUCTION", Pump::Style::LARGE_END_SUCTION)
        .value("SPECIFIED_OPTIMAL_EFFICIENCY", Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY);

    enum_<Pump::SpecificSpeed>("SpecificSpeed")
        .value("FIXED_SPEED", Pump::SpecificSpeed::FIXED_SPEED)
        .value("NOT_FIXED_SPEED", Pump::SpecificSpeed::NOT_FIXED_SPEED);
}

//pump shaft power
EMSCRIPTEN_BINDINGS(pump_shaft_class)
        {
                class_<PumpShaftPower>("PumpShaftPower")
                        .constructor<double, Motor::Drive, double>()
                        .function("calculate", &PumpShaftPower::calculate);

        class_<PumpShaftPower::Output>("PumpShaftPowerOutput")
        .constructor<double, double>()
        .property("pumpShaftPower", &PumpShaftPower::Output::pumpShaftPower)
        .property("driveEfficiency", &PumpShaftPower::Output::driveEfficiency);
        }

//achievableEfficiency
EMSCRIPTEN_BINDINGS(optimal_specified_speed_class)
{
    class_<OptimalSpecificSpeedCorrection>("OptimalSpecificSpeedCorrection")
        .constructor<Pump::Style, double>()
        .function("calculate", &OptimalSpecificSpeedCorrection::calculate);
}
//pumpEfficiency
EMSCRIPTEN_BINDINGS(pump_efficiency)
{
    class_<PumpEfficiency>("PumpEfficiency")
        .constructor<Pump::Style, double>()
        .function("calculate", &PumpEfficiency::calculate);
}

EMSCRIPTEN_BINDINGS(pump_efficiency_output)
{
    class_<PumpEfficiency::Output>("PumpEfficiencyResults")
        .constructor<double, double>()
        .property("average", &PumpEfficiency::Output::average)
        .property("max", &PumpEfficiency::Output::max);
}