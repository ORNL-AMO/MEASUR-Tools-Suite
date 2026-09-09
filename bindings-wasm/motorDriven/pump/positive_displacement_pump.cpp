#include <emscripten/bind.h>

#include "motorDriven/pump/PositiveDisplacementPump.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(positive_displacement_pump_class) {
    class_<PositiveDisplacementPump>("PositiveDisplacementPump")
        .constructor<double, double, double, double>()
        .function("calculate", &PositiveDisplacementPump::calculate);

    class_<PositiveDisplacementPump::Output>("PositiveDisplacementPumpOutput")
        .constructor<double, double>()
        .property("power", &PositiveDisplacementPump::Output::power)
        .property("energy", &PositiveDisplacementPump::Output::energy);
}
