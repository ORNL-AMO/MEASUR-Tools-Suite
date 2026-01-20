#include <emscripten/bind.h>

#include "processHeat/losses/solid_load_charge_material_heat_required.h"
using namespace emscripten;
using namespace solid_load_charge_material_heat_required;

// solidLoadChargeMaterial
EMSCRIPTEN_BINDINGS(solid_load_charge_material_heat_required) {
    // Parameters for solidLoadChargeMaterialTotalHeatRequired:
    //   thermic_reaction_type (enum: ENDOTHERMIC, EXOTHERMIC, NONE)
    //   specific_heat_solid (Btu/lb°F)
    //   latent_heat (Btu/lb)
    //   specific_heat_liquid (Btu/lb°F)
    //   melting_point (°F)
    //   charge_feed_rate (lb/hr)
    //   water_content_charged (% of total)
    //   water_content_discharged (% of total)
    //   initial_temperature (°F)
    //   discharge_temperature (°F)
    //   water_vapor_discharge_temperature (°F)
    //   charge_melted (% of dry charge)
    //   charge_reacted (% of dry charge)
    //   reaction_heat (Btu/lb)
    //   additional_heat (Btu/hr)
    function("solidLoadChargeMaterialTotalHeatRequired", &totalHeatRequired);
}