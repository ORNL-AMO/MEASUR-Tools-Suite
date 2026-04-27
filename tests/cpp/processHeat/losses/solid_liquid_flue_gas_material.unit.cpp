#include <processHeat/losses/solid_liquid_flue_gas_material.h>

#include "catch.hpp"

using namespace Catch;
using namespace solid_liquid_flue_gas_material;

TEST_CASE("Calculate SolidLiquidFlueGasMaterial Excess Air From Flue Gas O2", "[Heat Loss]") {
    auto excessAir = calculateExcessAirFromFlueGasO2(0.005, 1.0, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5);
    CHECK(excessAir == Approx(0.0229427817));

    excessAir = calculateExcessAirFromFlueGasO2(0.03, 1.0, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5);
    CHECK(excessAir == Approx(0.1536865757));

    excessAir = calculateExcessAirFromFlueGasO2(0.07, 1.0, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5);
    CHECK(excessAir == Approx(0.4475000362));
}

TEST_CASE("Calculate SolidLiquidFlueGasMaterial Flue Gas O2", "[Heat Loss]") {

    CHECK(calculateFlueGasO2(0.0229427817, 1.0, 75, 5, 1, 9, 7, 0, 1.5) == Approx(0.0049370451));
    CHECK(calculateFlueGasO2(0.1536865757, 1.0, 75, 5, 1, 9, 7, 0, 1.5) == Approx(0.0294401415));
    CHECK(calculateFlueGasO2(0.4475000362, 1.0, 75, 5, 1, 9, 7, 0, 1.5) == Approx(0.0687560661));
}

TEST_CASE("Calculate SolidLiquidFlueGasMaterial Heat Loss", "[Heat Loss]") {
    CHECK(totalHeatLoss(700, 2.29427817, 125, 70, 1.0, 100, 1.5, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5) ==
          Approx(0.8297708724));
    CHECK(totalHeatLoss(700, 15.36865757, 125, 70, 1.0, 100, 1.5, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5) ==
          Approx(0.8151987637));
    CHECK(totalHeatLoss(700, 44.75000362, 125, 70, 1.0, 100, 1.5, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5) ==
          Approx(0.7824331922));
    CHECK(totalHeatLoss(700, 9.0, 125, 70, 1.0, 100, 1.5, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5) == Approx(0.8223));
}

TEST_CASE("BUG 306", "[BUG306]") {
    double flueGasTemperature       = 600;
    double excessAirPercentage      = 20;
    // double o2InFlueGas              = 3.573146432264344;
    // double ambientAirTemp           = 65;
    double combustionAirTemperature = 65;
    double fuelTemperature          = 65;
    double ashDischargeTemperature  = 400;
    double moistureInAirCombustion  = 0.0077;
    double unburnedCarbonInAsh      = 1;
    double carbon                   = 70.3;
    double hydrogen                 = 4.9;
    double sulphur                  = 2.2;
    double inertAsh                 = 1.5;
    double o2                       = 8.7;
    double moisture                 = 4.9;
    double nitrogen                 = 7.5;
    // double heatInput                = 10;
    double ambientAirTempF          = 65;
    // double combAirMoisturePerc      = 0.0077;

    CHECK(totalHeatLoss(flueGasTemperature, excessAirPercentage, combustionAirTemperature, fuelTemperature,
                     moistureInAirCombustion, ashDischargeTemperature, unburnedCarbonInAsh, carbon, hydrogen,
                     sulphur, inertAsh, o2, moisture, nitrogen, ambientAirTempF) == Approx(0.82606233456934197));
}