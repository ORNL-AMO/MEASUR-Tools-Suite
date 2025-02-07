#include "other/CHP.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(chp_enums)
{
    enum_<CHP::Option>("CHPOption")
        .value("PercentAvgkWhElectricCostAvoided", CHP::Option::PercentAvgkWhElectricCostAvoided)
        .value("StandbyRate", CHP::Option::StandbyRate);
}

// CHPcalculator
EMSCRIPTEN_BINDINGS(CHPcalculator)
{
    class_<CHP>("CHP")
        .constructor<double, double, double, double, double, CHP::Option, double, double, double, double, double, double>()
        .function("getCostInfo", &CHP::getCostInfo);

    class_<CHP::CostInfoOutput>("CostInfoOutput")
        .constructor<double, double, double, double, double, double, double>()
        .property("annualOperationSavings", &CHP::CostInfoOutput::annualOperationSavings)
        .property("totalInstalledCostsPayback", &CHP::CostInfoOutput::totalInstalledCostsPayback)
        .property("simplePayback", &CHP::CostInfoOutput::simplePayback)
        .property("fuelCosts", &CHP::CostInfoOutput::fuelCosts)
        .property("thermalCredit", &CHP::CostInfoOutput::thermalCredit)
        .property("incrementalOandM", &CHP::CostInfoOutput::incrementalOandMDollarsKwH)
        .property("totalOperatingCosts", &CHP::CostInfoOutput::totalOperatingCostsToGenerate);
}
