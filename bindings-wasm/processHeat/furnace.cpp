#include <emscripten/bind.h>

#include "processHeat/EfficiencyImprovement.h"

using namespace emscripten;

// efficiencyImprovement
EMSCRIPTEN_BINDINGS(efficiencyImprovement) {
    class_<EfficiencyImprovement>("EfficiencyImprovement")
        .constructor<double, double, double, double, double, double, double>()
        .function("getCurrentExcessAir", &EfficiencyImprovement::getCurrentExcessAir)
        .function("getNewExcessAir", &EfficiencyImprovement::getNewExcessAir)
        .function("getCurrentAvailableHeat", &EfficiencyImprovement::getCurrentAvailableHeat)
        .function("getNewAvailableHeat", &EfficiencyImprovement::getNewAvailableHeat)
        .function("getNewFuelSavings", &EfficiencyImprovement::getNewFuelSavings)
        .function("getNewEnergyInput", &EfficiencyImprovement::getNewEnergyInput);
}