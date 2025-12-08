#include "processHeat/losses/gas_load_charge_material_heat_required.h"

#include "catch.hpp"

using namespace Catch;
#include "processHeat/losses/load_charge_material.h"

TEST_CASE("Calculate Total Heat for Charge Material - Gas", "[Total Heat][ChargeMaterial][Gas]") {
    using namespace gas_load_charge_material_heat_required;
    CHECK(totalHeatRequired(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.24, 1000.0, 15.0, 80.0, 1150.0,
                                0.5, 100.0, 80.0, 5000.0) == Approx(383530.0));
}