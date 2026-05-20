#include <emscripten/bind.h>

#include "treasureHunt/InsulatedTankReduction.h"
#include "vector"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(insulatedTankReduction_class) {
    class_<InsulatedTankInput>("InsulatedTankInput")
        .constructor<int, double, double, double, double, double, double, double, double, double, double, double,
                     double>();

    class_<InsulatedTankOutput>("InsulatedTankOutput")
        .function("getHeatLoss", &InsulatedTankOutput::getHeatLoss)
        .function("getAnnualHeatLoss", &InsulatedTankOutput::getAnnualHeatLoss);

    class_<InsulatedTankReduction>("InsulatedTankReduction")
        .constructor<InsulatedTankInput>()
        .function("calculate", &InsulatedTankReduction::calculate);
}
