#include "processHeat/furnace/EfficiencyImprovement.h"
#include "processHeat/furnace/EnergyEquivalency.h"
#include "processHeat/furnace/FlowCalculationsEnergyUse.h"
#include "processHeat/furnace/O2Enrichment.h"
#include "processHeat/furnace/HumidityRatio.h"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(furnace_enums)
{
    enum_<FlowCalculationsEnergyUse::Gas>("Gas")
        .value("AIR", FlowCalculationsEnergyUse::Gas::AIR)
        .value("AMMONIA_DISSOCIATED", FlowCalculationsEnergyUse::Gas::AMMONIA_DISSOCIATED)
        .value("ARGON", FlowCalculationsEnergyUse::Gas::ARGON)
        .value("BUTANE", FlowCalculationsEnergyUse::Gas::BUTANE)
        .value("ENDOTHERMIC_AMMONIA", FlowCalculationsEnergyUse::Gas::ENDOTHERMIC_AMMONIA)
        .value("EXOTHERMIC_CRACKED_LEAN", FlowCalculationsEnergyUse::Gas::EXOTHERMIC_CRACKED_LEAN)
        .value("EXOTHERMIC_CRACKED_RICH", FlowCalculationsEnergyUse::Gas::EXOTHERMIC_CRACKED_RICH)
        .value("HELIUM", FlowCalculationsEnergyUse::Gas::HELIUM)
        .value("HYDROGEN", FlowCalculationsEnergyUse::Gas::HYDROGEN)
        .value("NATURAL_GAS", FlowCalculationsEnergyUse::Gas::NATURAL_GAS)
        .value("NITROGEN", FlowCalculationsEnergyUse::Gas::NITROGEN)
        .value("OXYGEN", FlowCalculationsEnergyUse::Gas::OXYGEN)
        .value("PROPANE", FlowCalculationsEnergyUse::Gas::PROPANE)
        .value("OTHER", FlowCalculationsEnergyUse::Gas::OTHER);

    enum_<FlowCalculationsEnergyUse::Section>("Section")
        .value("SQUARE_EDGE", FlowCalculationsEnergyUse::Section::SQUARE_EDGE)
        .value("SHARP_EDGE", FlowCalculationsEnergyUse::Section::SHARP_EDGE)
        .value("VENTURI", FlowCalculationsEnergyUse::Section::VENTURI);
}

// efficiencyImprovement
EMSCRIPTEN_BINDINGS(efficiencyImprovement)
{
    class_<EfficiencyImprovement>("EfficiencyImprovement")
        .constructor<double, double, double, double, double, double, double>()
        .function("getCurrentExcessAir", &EfficiencyImprovement::getCurrentExcessAir)
        .function("getNewExcessAir", &EfficiencyImprovement::getNewExcessAir)
        .function("getCurrentAvailableHeat", &EfficiencyImprovement::getCurrentAvailableHeat)
        .function("getNewAvailableHeat", &EfficiencyImprovement::getNewAvailableHeat)
        .function("getNewFuelSavings", &EfficiencyImprovement::getNewFuelSavings)
        .function("getNewEnergyInput", &EfficiencyImprovement::getNewEnergyInput);
}
// energyEquivalencyElectric
EMSCRIPTEN_BINDINGS(energyEquivalencyElectric)
{
    class_<ElectricalEnergyEquivalency>("ElectricalEnergyEquivalency")
        .constructor<double, double, double>()
        .function("getElectricalHeatInput", &ElectricalEnergyEquivalency::getElectricalHeatInput);
}

// energyEquivalencyFuel
EMSCRIPTEN_BINDINGS(energyEquivalencyFuel)
{
    class_<FuelFiredEnergyEquivalency>("FuelFiredEnergyEquivalency")
        .constructor<double, double, double>()
        .function("getFuelFiredHeatInput", &FuelFiredEnergyEquivalency::getFuelFiredHeatInput);
}

// flowCalculations
EMSCRIPTEN_BINDINGS(flowCalculations)
{
    class_<FlowCalculationsEnergyUse>("FlowCalculationsEnergyUse")
        .constructor<FlowCalculationsEnergyUse::Gas, double, double, double, FlowCalculationsEnergyUse::Section, double, double, double, double, double, double>()
        .function("getFlow", &FlowCalculationsEnergyUse::getFlow)
        .function("getHeatInput", &FlowCalculationsEnergyUse::getHeatInput)
        .function("getTotalFlow", &FlowCalculationsEnergyUse::getTotalFlow);
}

// o2Enrichment
EMSCRIPTEN_BINDINGS(o2Enrichment)
{
    class_<O2Enrichment>("O2Enrichment")
        .constructor<double, double, double, double, double, double, double, double, double>()
        .function("getAvailableHeat", &O2Enrichment::getAvailableHeat)
        .function("getAvailableHeatEnriched", &O2Enrichment::getAvailableHeatEnriched)
        .function("getFuelSavingsEnriched", &O2Enrichment::getFuelSavingsEnriched)
        .function("getFuelConsumptionEnriched", &O2Enrichment::getFuelConsumptionEnriched);
}

// humidityRatio
EMSCRIPTEN_BINDINGS(humidityRatio)
{
    class_<HumidityRatio>("HumidityRatio")
        .constructor<double, double, double, double>()
        .function("getHumidityRatioUsingRH", &HumidityRatio::getHumidityRatioUsingRH)
        .function("getHumidityRatioUsingWBT", &HumidityRatio::getHumidityRatioUsingWBT);
}
