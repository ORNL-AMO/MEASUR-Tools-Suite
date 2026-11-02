#include <emscripten/bind.h>

#include "motorDriven/pumpFan/OptimalSpecificSpeedCorrection.h"
#include "motorDriven/pumpFan/PumpEfficiency.h"

using namespace emscripten;

// achievableEfficiency
EMSCRIPTEN_BINDINGS(optimal_specified_speed_class) {
    class_<OptimalSpecificSpeedCorrection>("OptimalSpecificSpeedCorrection")
        .constructor<Pump::Style, double>()
        .function("calculate", &OptimalSpecificSpeedCorrection::calculate);
}
// pumpEfficiency
EMSCRIPTEN_BINDINGS(pump_efficiency) {
    class_<PumpEfficiency>("PumpEfficiency")
        .constructor<Pump::Style, double, double, double, double, double, double>()
        .function("calculate", &PumpEfficiency::calculate);
}

EMSCRIPTEN_BINDINGS(pump_efficiency_output) {
    class_<PumpEfficiency::Output>("PumpEfficiencyResults")
        .constructor<double, double>()
        .property("average", &PumpEfficiency::Output::average)
        .property("max", &PumpEfficiency::Output::max);
}
