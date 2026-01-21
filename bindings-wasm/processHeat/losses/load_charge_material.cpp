#include <emscripten/bind.h>
#include "processHeat/losses/load_charge_material.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(losses_enums) {
    enum_<LoadChargeMaterial::ThermicReactionType>("ThermicReactionType")
        .value("ENDOTHERMIC", LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC)
        .value("EXOTHERMIC", LoadChargeMaterial::ThermicReactionType::EXOTHERMIC)
        .value("NONE", LoadChargeMaterial::ThermicReactionType::NONE);
}


