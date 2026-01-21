#include <emscripten/bind.h>
#include "processHeat/losses/liquid_load_charge_material_heat_required.h"

using namespace emscripten;
using namespace liquid_load_charge_material_heat_required;

EMSCRIPTEN_BINDINGS(liquid_load_charge_material_heat_required) {
    // Parameters for liquidLoadChargeMaterialTotalHeatRequired:
    //   thermic_reaction_type (enum: ENDOTHERMIC, EXOTHERMIC, NONE)
    //   specific_heat_liquid (Btu/lb°F)
    //   vaporizing_temperature (°F)
    //   latent_heat (Btu/lb)
    //   specific_heat_vapor (Btu/lb°F)
    //   charge_feed_rate (lb/hr)
    //   initial_temperature (°F)
    //   discharge_temperature (°F)
    //   percent_vaporized (% of total)
    //   percent_reacted (% of total)
    //   reaction_heat (Btu/lb)
    //   additional_heat (Btu/hr)
    function("liquidLoadChargeMaterialTotalHeatRequired", &totalHeatRequired);
}