#include <emscripten/bind.h>
#include "processHeat/losses/energy_input_electric_arc_furnace.h"

using namespace emscripten;
using namespace energy_input_electric_arc_furnace;

// energyInputEAF
EMSCRIPTEN_BINDINGS(energy_input_electric_arc_furnace) {
    // Parameters for energyInputEAFTotalChemicalEnergyInput:
    //   natural_gas_heat_input (MMBtu/hr), coal_carbon_injection (lb/hr), coal_heating_value (Btu/lb),
    //   electrode_use (lb/hr), electrode_heating_value (Btu/lb), other_fuels (MMBtu/hr)
    function("energyInputEAFTotalChemicalEnergyInput", &totalChemicalEnergyInput);

    // Parameters for energyInputEAFTotalHeatDelivered:
    //   total_chemical_energy_input (MMBtu/hr), electricity_input (MMBtu/hr)
    function("energyInputEAFTotalHeatDelivered", &totalHeatDelivered);
}