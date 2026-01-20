#include "processHeat/air_heating_using_exhaust.h"

#include "catch.hpp"
#include "processHeat/losses/gas_flue_gas_material.h"

using namespace Catch;
using namespace air_heating_using_exhaust;
using namespace gas_composition;
using namespace solid_liquid_flue_gas_material_data;
TEST_CASE("Calculate results for air heating using exhaust with gas composition",
          "[Process Heating][airHeatingUsingExhaust]") {

    GasComposition                gas("Gas", 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    AirHeatingUsingExhaustResults res =
        airHeatingUsingExhaustWithGasComposition(gas, 400, 0.358, 8, 4000, 45, 0.85, 0.60, 4000);
    CHECK(res.hx_cold_air == Approx(197829.27));
    CHECK(res.hx_outlet_exhaust == Approx(187));
    CHECK(res.energy_savings == Approx(930.96));
    CHECK(res.heat_capacity_flue == Approx(928.78));
    CHECK(res.heat_capacity_air == Approx(4464));
}

TEST_CASE("Calculate results for air heating using exhaust with solid liquid flue gas material",
          "[Process Heating][airHeatingUsingExhaust]") {
    SolidLiquidFlueGasMaterial material = SolidLiquidFlueGasMaterial {"test fuel", 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5};
    AirHeatingUsingExhaustResults res = airHeatingUsingExhaustWithSolidLiquidFlueGasMaterial(material, 400, 0.358, 8, 4000, 45, 0.85, 0.60, 4000);
    CHECK(res.hx_cold_air == Approx(15621.25));
    CHECK(res.hx_outlet_exhaust == Approx(187));
    CHECK(res.energy_savings == Approx(73.512));
    CHECK(res.heat_capacity_flue == Approx(73.339));
    CHECK(res.heat_capacity_air == Approx(4464));
}
