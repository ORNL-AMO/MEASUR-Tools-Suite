#include "processHeat/losses/liquid_cooling_heat_loss.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate Heat Loss for liquid cooling Heat Loss ethylene glycon", "[Heat Loss][Ethylene Glycon][Liquid]") {
    CHECK(liquid_cooling_heat_loss::totalHeatLoss(100.0, 9.35, 80.0, 210.0, 0.52, 1.0) == Approx(3792360.0));
}