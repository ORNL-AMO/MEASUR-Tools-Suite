#include "catch.hpp"
#include "databases/solid_load_charge_material_data.h"
using namespace Catch;
using namespace solid_load_charge_material_data;

TEST_CASE("SolidLoadChargeMaterial - getSolidLoadChargeMaterials", "[databases]") {
    {
        auto const outputs = get_default_solid_load_charge_materials();
        CHECK(outputs.size() == 40);
    }

    {
        SolidLoadChargeMaterial output = get_default_solid_load_charge_materials()[0];
        SolidLoadChargeMaterial expected = {"Aluminum", 0.247910198232625, 169, 0.2601, 1215};
        CHECK(expected.substance == output.substance);
        CHECK(expected.specific_heat_solid == output.specific_heat_solid);
        CHECK(expected.latent_heat == output.latent_heat);
        CHECK(expected.specific_heat_liquid == output.specific_heat_liquid);
        CHECK(expected.melting_point == output.melting_point);
    }
}