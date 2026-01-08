#include "processHeat/energy_equivalency.h"

#include "catch.hpp"

using namespace Catch;
using namespace energy_equivalency;
TEST_CASE("Calculate the Equivalent Electrical Heat Input", "[Electrical Heat Input][EnergyEquivalency][Calculator]") {
    CHECK(calculateElectricalEquivalentHeatInput(10, 60, 90) == Approx(1953.807));
}

TEST_CASE("Calculate the Equivalent Fuel-Fired Heat Input", "[Fuel-Fired Heat Input][EnergyEquivalency][Calculator]") {
    CHECK(calculateFuelFiredEquivalentHeatInput(1800, 90, 60) == Approx(9.21278339));
}
