#include "catch.hpp"
#include "databases/liquid_load_charge_material_data.h"
using namespace Catch;
using namespace liquid_load_charge_material_data;

TEST_CASE("DefaultData - getLiquidLoadChargeMaterials", "[databases]") {
    {
        auto const outputs = get_default_liquid_load_charge_materials();
        CHECK(outputs.size() == 13);
    }

    {
        auto const output = get_default_liquid_load_charge_materials()[0];
        LiquidLoadChargeMaterial expected = {"Crude", 0.6501, 105, 0.55, 900};
        CHECK(expected.specific_heat == output.specific_heat);
        CHECK(expected.substance == output.substance);
        CHECK(expected.latent_heat == output.latent_heat);
        CHECK(expected.vapor_specific_heat == output.vapor_specific_heat);
        CHECK(expected.boiling_point == output.boiling_point);
    }
}