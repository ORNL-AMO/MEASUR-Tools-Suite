#include "catch.hpp"
#include "databases/gas_load_charge_material_data.h"
using namespace Catch;
using namespace gas_load_charge_material_data;

TEST_CASE("DefaultData - getGasLoadChargeMaterials", "[databases]") {
    {
        auto const outputs = get_default_gas_load_charge_materials();
        CHECK(outputs.size() == 10);
    }

    {
        auto const output = get_default_gas_load_charge_materials()[0];

        GasLoadChargeMaterial expected = {"Water vapor - Near Atm. Pressure", 0.47};
        CHECK(expected.specific_heat_vapor == output.specific_heat_vapor);
        CHECK(expected.substance == output.substance);
    }
}