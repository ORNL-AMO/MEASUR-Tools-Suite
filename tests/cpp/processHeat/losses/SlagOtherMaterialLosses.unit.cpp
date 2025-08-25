#include <processHeat/losses/SlagOtherMaterialLosses.h>
#include <processHeat/losses/SolidLoadChargeMaterial.h>

#include "catch.hpp"

TEST_CASE("Calculate SlagOtherMaterialLosses Heat Loss", "[Heat Loss]") {
    auto aluminumSpecificHeat = 0.247910198232625;
    auto slag                 = SlagOtherMaterialLosses(3, 500, 550, aluminumSpecificHeat, 1.0);
    REQUIRE(slag.getHeatLoss() == Approx(37.1865297349));

    auto bismuthSpecificHeat = 0.0329591593026033;
    slag                     = SlagOtherMaterialLosses(10, 725, 850, bismuthSpecificHeat, 0.8);
    REQUIRE(slag.getHeatLoss() == Approx(32.9591593026));
}