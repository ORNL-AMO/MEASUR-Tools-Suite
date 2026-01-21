#include "processHeat/losses/exhaust_gas_heat_loss_electric_arc_furnace.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate the Total Heat Exhaust", "[Total Heat Exhaust][ExhaustGasEAF][EAF]") {
    CHECK(exhaust_gas_heat_loss_electric_arc_furnace::totalHeatLoss(2800, 12, 10, 3, 8000, 0.001) == Approx(12553119.02));
    CHECK(exhaust_gas_heat_loss_electric_arc_furnace::totalHeatLoss(2800, 8, 6, 3, 6500, 0.001) == Approx(8591939.26));
}
