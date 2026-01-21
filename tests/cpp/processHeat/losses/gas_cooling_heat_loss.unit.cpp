#include "processHeat/losses/gas_cooling_heat_loss.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate Heat Loss for gas cooling Heat Loss Air", "[Heat Loss]") {
    REQUIRE(gas_cooling_heat_loss::totalHeatLoss(2500.0, 80.0, 280.0, 0.02, 1.0, 1) == Approx(600000.0));
    REQUIRE(gas_cooling_heat_loss::totalHeatLoss(600, 80.0, 350.0, 0.02, 1.0, 1) == Approx(194400.0));
}