#include "processHeat/losses/gas_flue_gas_material.h"

#include "catch.hpp"
#include "physics/gas_composition.h"

using namespace Catch;
using namespace gas_composition;
using namespace gas_flue_gas_material;

TEST_CASE("Calculate Gas Flue Gas Material", "[Gas Flue Gas Material]") {
    GasComposition composition("unit test gas", 94.1, 2.4, 1.41, 0.03, 0.49, 0.29, 0, 0.42, 0.71, 0, 0);

    CHECK(processHeatProperties(composition, 700, 0.0231722095, 125, 125, 60, 0).available_heat ==
          Approx(0.7831351536));
    CHECK(processHeatProperties(composition, 700, 0.1552234415, 125, 125, 60, 0).available_heat ==
          Approx(0.5615301965));
    CHECK(processHeatProperties(composition, 700, 0.09, 125, 125, 60, 0).available_heat == Approx(0.7264072116));
}