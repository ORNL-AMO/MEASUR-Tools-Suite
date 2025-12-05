#include <processHeat/losses/slag_other_material_heat_loss.h>

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate SlagOtherMaterialLosses Heat Loss", "[Heat Loss]") {
    auto aluminumSpecificHeat = 0.247910198232625;
    REQUIRE(slag_other_material_heat_loss::totalHeatLoss(3, 500, 550, aluminumSpecificHeat, 1.0) == Approx(37.1865297349));

    auto bismuthSpecificHeat = 0.0329591593026033;
    REQUIRE(slag_other_material_heat_loss::totalHeatLoss(10, 725, 850, bismuthSpecificHeat, 0.8) == Approx(32.9591593026));
}