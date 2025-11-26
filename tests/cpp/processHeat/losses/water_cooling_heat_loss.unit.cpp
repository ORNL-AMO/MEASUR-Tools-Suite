#include <processHeat/losses/water_cooling_heat_loss.h>

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate Heat Loss for liquid cooling Losses Water", "[Heat Loss]") {

    REQUIRE(water_cooling_heat_loss::totalHeatLoss(100.0, 80.0, 120.0, 1.0) == Approx(1989032));
}