#include <string>

#include <emscripten/bind.h>
#include "processHeat/energy_equivalency.h"

using namespace emscripten;
using namespace energy_equivalency;
EMSCRIPTEN_BINDINGS(energy_equivalency_functions) {
    // calculateElectricalEquivalentHeatInput(
    //   fuel_fired_heat_input [MMBtu/hr],
    //   fuel_fired_efficiency [percent],
    //   electrically_heated_efficiency [percent]
    // ) -> [kW]
    function("calculateElectricalEquivalentHeatInput", &calculateElectricalEquivalentHeatInput);

    // calculateFuelFiredEquivalentHeatInput(
    //   electrical_heat_input [kW],
    //   electrically_heated_efficiency [percent],
    //   fuel_fired_efficiency [percent]
    // ) -> [MMBtu/hr]
    function("calculateFuelFiredEquivalentHeatInput", &calculateFuelFiredEquivalentHeatInput);
}