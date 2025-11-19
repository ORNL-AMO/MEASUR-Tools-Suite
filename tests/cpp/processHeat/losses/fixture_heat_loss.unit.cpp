#include "processHeat/losses/fixture_heat_loss.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate total heat loss for fixtures, trays, and conveyors", "[Process Heating][Losses][Fixture]") {
    double specific_heat         = 0.122;  // btu/(lb·°F)
    double feed_rate             = 1250.0; // lb/hr
    double initial_temperature   = 300.0;  // °F
    double final_temperature     = 1800.0; // °F
    double correction_factor     = 1.0;    // unitless

    CHECK(fixture_heat_loss::totalHeatLoss(specific_heat, feed_rate, initial_temperature, final_temperature,
                                           correction_factor) == Approx(228750.0));
}
