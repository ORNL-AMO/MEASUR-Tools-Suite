#include "processHeat/losses/energy_input_electric_arc_furnace.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate the Total Chemical Energy Input 1", "[Total Chemical Energy Input][EnergyInputEAF][Furnace]") {
    const double naturalGasHeatInput   = 50;
    const double coalCarbonInjection   = 3300;
    const double coalHeatingValue      = 9000;
    const double electrodeUse          = 500;
    const double electrodeHeatingValue = 12000;
    const double otherFuels            = 20;
    double totalChemicalEnergyInput = energy_input_electric_arc_furnace::totalChemicalEnergyInput(
        naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels);
    CHECK(totalChemicalEnergyInput == Approx(105700000));
}
TEST_CASE("Calculate the Total Chemical Energy Input 2", "[Total Chemical Energy Input][EnergyInputEAF][Furnace]") {
    const double naturalGasHeatInput   = 15;
    const double coalCarbonInjection   = 900;
    const double coalHeatingValue      = 9000;
    const double electrodeUse          = 200;
    const double electrodeHeatingValue = 12000;
    const double otherFuels            = 0;
    const double electricityInput = 18000;
    double totalChemicalEnergyInput = energy_input_electric_arc_furnace::totalChemicalEnergyInput(
        naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels);
    CHECK(totalChemicalEnergyInput == Approx(25500000.0));
}

TEST_CASE("Calculate the Heat Delivered 1", "[Heat Delivered][EnergyInputEAF][Furnace]") {
    const double naturalGasHeatInput   = 50;
    const double coalCarbonInjection   = 3300;
    const double coalHeatingValue      = 9000;
    const double electrodeUse          = 500;
    const double electrodeHeatingValue = 12000;
    const double otherFuels            = 20;
    const double electricityInput = 18000;
    double totalChemicalEnergyInput = energy_input_electric_arc_furnace::totalChemicalEnergyInput(
        naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels);
    double heatDelivered = energy_input_electric_arc_furnace::totalHeatDelivered(totalChemicalEnergyInput, electricityInput);
    CHECK(heatDelivered == Approx(167118452.4607751));
}

TEST_CASE("Calculate the Heat Delivered 1", "[Heat Delivered][EnergyInputEAF][Furnace]") {
    const double naturalGasHeatInput   = 50;
    const double coalCarbonInjection   = 900;
    const double coalHeatingValue      = 9000;
    const double electrodeUse          = 200;
    const double electrodeHeatingValue = 12000;
    const double otherFuels            = 0;
    const double electricityInput = 18000;
    double totalChemicalEnergyInput = energy_input_electric_arc_furnace::totalChemicalEnergyInput(
        naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels);
    double heatDelivered = energy_input_electric_arc_furnace::totalHeatDelivered(totalChemicalEnergyInput, electricityInput);
    CHECK(heatDelivered == Approx(86916000));
}
