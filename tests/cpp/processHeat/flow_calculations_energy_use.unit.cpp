#include "processHeat/flow_calculations_energy_use.h"

#include "catch.hpp"

using namespace Catch;
using namespace flow_calculations_energy_use;
TEST_CASE("Calculate the Flow(1)", "[Flow][FlowCalculationsEnergyUse][Calculator]") {
    CHECK(flowCalculationsEnergyUse(0.14, 5, 9, 0.6, 7325, 52, 63, 26, 16).flow_per_hour == Approx(647521.0285703765694052));
}

TEST_CASE("Calculate the Heat Input(1)", "[Heat Input][FlowCalculationsEnergyUse][Calculator]") {
    CHECK(flowCalculationsEnergyUse(0.14, 5, 9, 0.6, 7325, 52, 63, 26, 16).heat_input == Approx(75889.4645484481297899));
}

TEST_CASE("Calculate the Total Flow(1)", "[Flow][FlowCalculationsEnergyUse][Calculator]") {
    CHECK(flowCalculationsEnergyUse(1, 3.5, 8, 0.6, 0, 85, 20, 10, 10).total_flow == Approx(462143.21201163821388036));
}

TEST_CASE("Calculate the Flow(2)", "[Flow][FlowCalculationsEnergyUse][Calculator]") {
    CHECK(flowCalculationsEnergyUse(7, 6, 18, 0.8, 60000, 85, 55, 20, 10).flow_per_hour == Approx(135485.24457904856535606));
}

TEST_CASE("Calculate the Heat Input(2)", "[Heat Input][FlowCalculationsEnergyUse][Calculator]") {
    CHECK(flowCalculationsEnergyUse(7, 6, 18, 0.8, 60000, 85, 55, 20, 10).heat_input == Approx(81291.14674742914212402));
}

TEST_CASE("Calculate the Total Flow(2)", "[Flow][FlowCalculationsEnergyUse][Calculator]") {
    CHECK(flowCalculationsEnergyUse(1, 3.5, 8, 0.8, 0, 85, 20, 10, 10).total_flow == Approx(616190.94934885110706091));
}