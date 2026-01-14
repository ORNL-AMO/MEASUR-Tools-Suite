#include <emscripten/bind.h>
#include "processHeat/losses/gas_load_charge_material_heat_required.h"

using namespace emscripten;
using namespace gas_load_charge_material_heat_required;

// gasLoadChargeMaterial
EMSCRIPTEN_BINDINGS(gas_load_charge_material_heat_required) {
    using namespace gas_load_charge_material_heat_required;
    // Parameters for gasLoadChargeMaterialTotalHeatRequired:
    //   thermic_reaction_type (enum: ENDOTHERMIC, EXOTHERMIC, NONE)
    //   specific_heat_gas (Btu/lb°F)
    //   feed_rate (lb/hr)
    //   percent_vapor (% of total)
    //   initial_temperature (°F)
    //   discharge_temperature (°F)
    //   specific_heat_vapor (Btu/lb°F)
    //   percent_reacted (% of total)
    //   reaction_heat (Btu/lb)
    //   additional_heat (Btu/hr)
    function("gasLoadChargeMaterialTotalHeatRequired", &totalHeatRequired);
}