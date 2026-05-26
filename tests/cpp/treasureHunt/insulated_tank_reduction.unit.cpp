#include "treasureHunt/insulated_tank_reduction.h"

#include "catch.hpp"

using namespace Catch;
using namespace insulated_tank_reduction;

// ── Helper function correlations ─────────────────────────────────────────────

TEST_CASE("Rayleigh Number - vertical tank surface", "[insulated_tank_reduction][util]") {
    // At T_ambient = 529.67°R: beta = 1/529.67, kin_visc and thermal_diff from air property polys
    // These values correspond to test case 1 (insulated) at ambient temperature.
    double thermal_expansion   = 1.0 / 529.67;
    double surface_temperature = 959.67;
    double ambient_temperature = 529.67;
    double diameter            = 5.0;
    double kin_viscosity       = 4.5396e-8;   // ft²/s, approx from polynomial
    double thermal_diffusivity = 0.8348 / 3600.0; // ft²/s, converted from ft²/hr polynomial

    double ra = rayleighNumber(thermal_expansion, surface_temperature, ambient_temperature,
                               diameter, kin_viscosity, thermal_diffusivity);
    CHECK(ra > 0.0);
}

TEST_CASE("Natural Convection Coefficient", "[insulated_tank_reduction][util]") {
    // h = 0.125 * Ra^(1/3) * k / d
    // For Ra = 1e9, k = 0.015, d = 5: h = 0.125 * 1000 * 0.015 / 5 = 0.375
    double ra          = 1.0e9;
    double conductivity = 0.015;
    double diameter    = 5.0;
    double h = naturalConvectionCoefficient(ra, conductivity, diameter);
    CHECK(h == Approx(0.375));
}

// ── Full system calculations ──────────────────────────────────────────────────

TEST_CASE("Insulated Tank - with insulation", "[insulated_tank_reduction]") {
    InsulatedTankInput input;
    input.operating_hours         = 8760;
    input.tank_height             = 10.0;
    input.tank_diameter           = 5.0;
    input.tank_thickness          = 0.5;
    input.tank_emissivity         = 0.8;
    input.tank_conductivity       = 46.2320;
    input.tank_temperature        = 959.67;
    input.ambient_temperature     = 529.67;
    input.system_efficiency       = 0.9;
    input.insulation_thickness    = 0.5;
    input.insulation_conductivity = 0.0191;
    input.jacket_emissivity       = 0.9;
    input.surface_temperature     = 959.67;

    InsulatedTankOutput output = calculate(input);
    CHECK(output.heat_loss        == Approx(0.04511472807275703));
    CHECK(output.annual_heat_loss == Approx(43.91166865748351));
}

TEST_CASE("Insulated Tank - with insulation 2", "[insulated_tank_reduction]") {
    InsulatedTankInput input;
    input.operating_hours         = 8760;
    input.tank_height             = 50.0;
    input.tank_diameter           = 1.0;
    input.tank_thickness          = 0.25;
    input.tank_emissivity         = 0.3;
    input.tank_conductivity       = 9.25;
    input.tank_temperature        = 759.67;
    input.ambient_temperature     = 539.67;
    input.system_efficiency       = 0.9;
    input.insulation_thickness    = 0.5;
    input.insulation_conductivity = 0.0231;
    input.jacket_emissivity       = 0.1;
    input.surface_temperature     = 759.67;

    InsulatedTankOutput output = calculate(input);
    CHECK(output.heat_loss        == Approx(0.0312837773195821));
    CHECK(output.annual_heat_loss == Approx(30.44954325772658));
}

TEST_CASE("Insulated Tank - no insulation (bare)", "[insulated_tank_reduction]") {
    InsulatedTankInput input;
    input.operating_hours         = 8760;
    input.tank_height             = 10.0;
    input.tank_diameter           = 5.0;
    input.tank_thickness          = 0.5;
    input.tank_emissivity         = 0.8;
    input.tank_conductivity       = 46.2320;
    input.tank_temperature        = 959.67;
    input.ambient_temperature     = 529.67;
    input.system_efficiency       = 0.9;
    input.insulation_thickness    = 0.0;
    input.insulation_conductivity = 0.0;
    input.jacket_emissivity       = 0.9;
    input.surface_temperature     = 959.67;

    InsulatedTankOutput output = calculate(input);
    CHECK(output.heat_loss        == Approx(4.74279643553729));
    CHECK(output.annual_heat_loss == Approx(4616.32186392296));
}

TEST_CASE("Insulated Tank - emissivity validation throws", "[insulated_tank_reduction]") {
    InsulatedTankInput input;
    input.tank_emissivity = 1.5;
    CHECK_THROWS(calculate(input));

    input.tank_emissivity   = 0.8;
    input.jacket_emissivity = -0.1;
    CHECK_THROWS(calculate(input));
}

TEST_CASE("Insulated Tank - insulatedTankHeatLoss matches calculate with insulation", "[insulated_tank_reduction]") {
    InsulatedTankInput input;
    input.operating_hours         = 8760;
    input.tank_height             = 10.0;
    input.tank_diameter           = 5.0;
    input.tank_thickness          = 0.5;
    input.tank_emissivity         = 0.8;
    input.tank_conductivity       = 46.2320;
    input.tank_temperature        = 959.67;
    input.ambient_temperature     = 529.67;
    input.system_efficiency       = 0.9;
    input.insulation_thickness    = 0.5;
    input.insulation_conductivity = 0.0191;
    input.jacket_emissivity       = 0.9;
    input.surface_temperature     = 959.67;

    InsulatedTankOutput via_calculate    = calculate(input);
    InsulatedTankOutput via_insulated    = insulatedTankHeatLoss(input);
    CHECK(via_calculate.heat_loss        == Approx(via_insulated.heat_loss));
    CHECK(via_calculate.annual_heat_loss == Approx(via_insulated.annual_heat_loss));
}

TEST_CASE("Insulated Tank - bareTankHeatLoss matches calculate with no insulation", "[insulated_tank_reduction]") {
    InsulatedTankInput input;
    input.operating_hours         = 8760;
    input.tank_height             = 10.0;
    input.tank_diameter           = 5.0;
    input.tank_thickness          = 0.5;
    input.tank_emissivity         = 0.8;
    input.tank_conductivity       = 46.2320;
    input.tank_temperature        = 959.67;
    input.ambient_temperature     = 529.67;
    input.system_efficiency       = 0.9;
    input.insulation_thickness    = 0.0;
    input.insulation_conductivity = 0.0;
    input.jacket_emissivity       = 0.9;
    input.surface_temperature     = 959.67;

    InsulatedTankOutput via_calculate = calculate(input);
    InsulatedTankOutput via_bare      = bareTankHeatLoss(input);
    CHECK(via_calculate.heat_loss        == Approx(via_bare.heat_loss));
    CHECK(via_calculate.annual_heat_loss == Approx(via_bare.annual_heat_loss));
}
