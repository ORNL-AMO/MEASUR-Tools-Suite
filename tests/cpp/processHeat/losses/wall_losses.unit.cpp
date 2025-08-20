#include "processHeat/losses/wall_losses.h"

#include <catch.hpp>

TEST_CASE("Calculate Heat Loss for furnace walls", "[Heat Loss]") {
    REQUIRE(WallLosses(500.0, 80.0, 225.0, 10.0, 0.9, 1.394, 1.0).totalHeatLoss() == Approx(404487.5887582747));
}