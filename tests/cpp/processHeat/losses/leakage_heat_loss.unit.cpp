#include "processHeat/losses/leakage_heat_loss.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate Heat Loss for gas leakage", "[Heat Loss]") {
    double draft_pressure = 0.1;            // in WC
    double opening_area = 3.0;              // ft^2
    double leakage_gas_temperature = 1600.0; // °F
    double ambient_temperature = 80.0;      // °F
    double coefficient = 0.8052;            // unitless
    double specific_gravity = 1.02;         // unitless
    double correction_factor = 1.0;         // unitless
    REQUIRE(leakage_heat_loss::totalHeatLoss(draft_pressure, opening_area, leakage_gas_temperature, ambient_temperature, coefficient, specific_gravity, correction_factor) ==
            Approx(2850767.0));
}