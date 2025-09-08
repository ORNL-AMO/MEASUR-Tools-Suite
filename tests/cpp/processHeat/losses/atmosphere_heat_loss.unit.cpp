#include "processHeat/losses/atmosphere_heat_loss.h"

#include <catch.hpp>

TEST_CASE("Calculate Total Heat loss for atmospheric gasses", "[Process Heating][Losses][Atmosphere]") {
    double flow_rate          = 1200.0; // scfh
    double specific_heat      = 0.02;   // btu/scf°F
    double inlet_temperature  = 100.0;  // °F
    double outlet_temperature = 1400.0; // °F
    double correction_factor  = 1.0;    // unitless

    CHECK(atmosphere_heat_loss::totalHeatLoss(flow_rate, specific_heat, inlet_temperature, outlet_temperature,
                                              correction_factor) == Approx(31200.0));
}
