#include "processHeat/losses/auxiliary_power_used.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate power used for Auxiliary Power", "[Power Used]") {
    CHECK(auxiliary_power_used::calculatePowerUsed(3, 460, 19, 0.85, 100) == Approx(43905.3405494047));
    CHECK(auxiliary_power_used::calculatePowerUsed(3, 510, 19, 0.85, 100) == Approx(48677.66017434));
    CHECK(auxiliary_power_used::calculatePowerUsed(3, 510, 25, 0.85, 100) == Approx(64049.5528609737));
    CHECK(auxiliary_power_used::calculatePowerUsed(3, 510, 25, 0.55, 100) == Approx(41443.8283218065));
    CHECK(auxiliary_power_used::calculatePowerUsed(3, 510, 25, 0.550, 75) == Approx(31082.8712413549));
}
