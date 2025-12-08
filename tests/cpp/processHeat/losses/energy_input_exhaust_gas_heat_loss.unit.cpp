#include "processHeat/losses/energy_input_exhaust_gas_heat_loss.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate the Heat Delivered to Furnace", "[HeatDelivered][EnergyInputExhaustGasLosses][Calculator]") {
    using namespace energy_input_exhaust_gas_heat_loss;
    EnergyInputExhaustGasResult results = calculate(65, 300, 550, 5000000);
    double available_heat = results.available_heat;
    CHECK(available_heat == Approx(82.727942398));
    double heat_delivered = results.heat_delivered;
    CHECK(heat_delivered == Approx(4136397.1199));
    double exhaust_gas_losses = results.exhaust_gas_losses;
    CHECK(exhaust_gas_losses == Approx(863602.8800999995));
}
