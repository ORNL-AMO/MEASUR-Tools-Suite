#include "processHeat/losses/energy_input_exhaust_gas_losses.h"

#include "catch.hpp"

TEST_CASE("Calculate the Heat Delivered to Furnace", "[HeatDelivered][EnergyInputExhaustGasLosses][Calculator]") {
    CHECK(EnergyInputExhaustGasLosses(65, 300, 550).getAvailableHeat() == Approx(82.727942398));
    CHECK(EnergyInputExhaustGasLosses(65, 300, 550, 5000000).getHeatDelivered() == Approx(4136397.1199));
    CHECK(EnergyInputExhaustGasLosses(65, 300, 550, 5000000).getExhaustGasLosses() == Approx(863602.8800999995));
}
