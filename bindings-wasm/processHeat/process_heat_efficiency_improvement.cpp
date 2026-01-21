#include <string>

#include <emscripten/bind.h>
#include "processHeat/process_heat_efficiency_improvement.h"


using namespace emscripten;
using namespace process_heat_efficiency_improvement;


EMSCRIPTEN_BINDINGS(process_heat_efficiency_improvement) {
    value_object<ProcessHeatEfficiencyImprovementResults>("ProcessHeatEfficiencyImprovementResults")
        .field("currentExcessAir", &ProcessHeatEfficiencyImprovementResults::current_excess_air)
        .field("newExcessAir", &ProcessHeatEfficiencyImprovementResults::new_excess_air)
        .field("currentHeatInput", &ProcessHeatEfficiencyImprovementResults::current_heat_input)
        .field("newHeatInput", &ProcessHeatEfficiencyImprovementResults::new_heat_input)
        .field("currentAirSpecificHeat", &ProcessHeatEfficiencyImprovementResults::current_air_specific_heat)
        .field("newAirSpecificHeat", &ProcessHeatEfficiencyImprovementResults::new_air_specific_heat)
        .field("currentAirCorrection", &ProcessHeatEfficiencyImprovementResults::current_air_correction)
        .field("newAirCorrection", &ProcessHeatEfficiencyImprovementResults::new_air_correction)
        .field("currentCombustionAirCorrection", &ProcessHeatEfficiencyImprovementResults::current_combustion_air_correction)
        .field("newCombustionAirCorrection", &ProcessHeatEfficiencyImprovementResults::new_combustion_air_correction)
        .field("currentAvailableHeat", &ProcessHeatEfficiencyImprovementResults::current_available_heat)
        .field("newAvailableHeat", &ProcessHeatEfficiencyImprovementResults::new_available_heat)
        .field("newFuelSavings", &ProcessHeatEfficiencyImprovementResults::new_fuel_savings)
        .field("newEnergyInput", &ProcessHeatEfficiencyImprovementResults::new_energy_input);

    // Parameters for processHeatEfficiencyImprovement:
    //   current_flue_gas_oxygen (double, % dry flue gas oxygen)
    //   new_flue_gas_oxygen (double, % dry flue gas oxygen)
    //   current_flue_gas_temp (double, °F)
    //   new_flue_gas_temp (double, °F)
    //   current_combustion_air_temp (double, °F)
    //   new_combustion_air_temp (double, °F)
    //   current_energy_input (double, MM Btu/hr)
    function("processHeatEfficiencyImprovement", &processHeatEfficiencyImprovement);
}