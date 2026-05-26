#include <emscripten/bind.h>

#include "treasureHunt/InsulatedPipeReduction.h"
#include "treasureHunt/InsulatedTankReduction.h"
#include "vector"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(insulatedPipeReduction_class) {
    class_<InsulatedPipeInput>("InsulatedPipeInput")
        .constructor<int, double, double, double, double, double, double, double, double, double, double,
                     std::vector<double>, std::vector<double>>();

    class_<InsulatedPipeOutput>("InsulatedPipeOutput")
        .function("getHeatLength", &InsulatedPipeOutput::getHeatLength)
        .function("getAnnualHeatLoss", &InsulatedPipeOutput::getAnnualHeatLoss);

    class_<InsulatedPipeReduction>("InsulatedPipeReduction")
        .constructor<InsulatedPipeInput>()
        .function("calculate", &InsulatedPipeReduction::calculate);
}

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
