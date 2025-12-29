#include "processHeat/process_heat_efficiency_improvement.h"

#include "catch.hpp"

using namespace Catch;
using namespace process_heat_efficiency_improvement;

TEST_CASE("Calculate the Current Excess Air", "[Current Excess Air][EfficiencyImprovement][Calculator]") {
    CHECK(processHeatEfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).current_excess_air == Approx(35.80));
}

TEST_CASE("Calculate the New Excess Air", "[New Excess Air][EfficiencyImprovement][Calculator]") {
    CHECK(processHeatEfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).new_excess_air == Approx(9.4210532075));
}

TEST_CASE("Calculate the Current Available Heat", "[Current Available Heat][EfficiencyImprovement][Calculator]") {
    CHECK(processHeatEfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).current_available_heat == Approx(45.5508888775));
}

TEST_CASE("Calculate the New Available Heat", "[New Available Heat][EfficiencyImprovement][Calculator]") {
    CHECK(processHeatEfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).new_available_heat == Approx(77.8931185299));
}

TEST_CASE("Calculate the New Fuel Savings", "[New Fuel Savings][EfficiencyImprovement][Calculator]") {
    CHECK(processHeatEfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).new_fuel_savings == Approx(41.5212925902));
}

TEST_CASE("Calculate the New Energy Input", "[New Energy Input][EfficiencyImprovement][Calculator]") {
    CHECK(processHeatEfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).new_energy_input == Approx(5.847870741));
}