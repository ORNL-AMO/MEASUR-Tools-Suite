#include "processHeat/losses/wall_heat_loss.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate total heat loss for furnace walls", "[Process Heating][Losses][Wall]") {
    double surface_area        = 500.0; // ft²
    double ambient_temperature = 80.0;  // °F
    double surface_temperature = 225.0; // °F
    double wind_speed          = 10.0;  // mph
    double surface_emissivity  = 0.9;   // unitless
    double shape_factor        = 1.394; // Vertical plates
    double correction_factor   = 1.0;   // unitless

    REQUIRE(wall_heat_loss::totalHeatLoss(surface_area, ambient_temperature, surface_temperature, wind_speed,
                                          surface_emissivity, shape_factor,
                                          correction_factor) == Approx(404487.5887582747));
}