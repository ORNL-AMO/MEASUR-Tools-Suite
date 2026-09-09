#include "motorDriven/pump/PositiveDisplacementPump.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate Positive Displacement Pump power and energy", "[PositiveDisplacementPump]") {
    auto output = PositiveDisplacementPump(100, 50, 0.8, 2000).calculate();

    CHECK(output.power == Approx(2.7198784761));
    CHECK(output.energy == Approx(5439.75695224));
}

TEST_CASE("Calculate Positive Displacement Pump scales with efficiency and operating hours",
          "[PositiveDisplacementPump]") {
    auto lowerEfficiency = PositiveDisplacementPump(100, 50, 0.4, 2000).calculate();
    auto zeroHours       = PositiveDisplacementPump(100, 50, 0.8, 0).calculate();

    CHECK(lowerEfficiency.power == Approx(5.4397569522));
    CHECK(lowerEfficiency.energy == Approx(10879.5139045));
    CHECK(zeroHours.power == Approx(2.7198784761));
    CHECK(zeroHours.energy == Approx(0));
}
