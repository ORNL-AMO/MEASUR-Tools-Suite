#include "treasureHunt/insulated_pipe_reduction.h"

#include <vector>

#include "catch.hpp"

using namespace Catch;
using namespace insulated_pipe_reduction;

// ── Helper number correlations ───────────────────────────────────────────────

TEST_CASE("Reynolds Number", "[insulated_pipe_reduction][util]") {
    CHECK(reynoldsNumber(0.1778, 0.89408, 0.0000159) == Approx(9997.9511949686));
}

TEST_CASE("Reynolds Number 2", "[insulated_pipe_reduction][util]") {
    CHECK(reynoldsNumber(0.13335, 0.44704, 0.0000149) == Approx(4000.8579865772));
}

TEST_CASE("Rayleigh Number", "[insulated_pipe_reduction][util]") {
    CHECK(rayleighNumber(0.003329819, 300.817, 299.817, 0.177799, 0.0000159, 0.0000225)
          == Approx(513213.3371527603));
}

TEST_CASE("Rayleigh Number 2", "[insulated_pipe_reduction][util]") {
    CHECK(rayleighNumber(0.0034577, 289.71, 288.71, 0.133335, 0.0000149, 0.0000209)
          == Approx(258200.0122627911));
}

TEST_CASE("Radiative Heat Transfer Coefficient", "[insulated_pipe_reduction][util]") {
    CHECK(radiativeHeatTransferCoefficient(0.1, 300.817, 299.817)
          == Approx(0.6143453478));
}

TEST_CASE("Radiative Heat Transfer Coefficient 2", "[insulated_pipe_reduction][util]") {
    CHECK(radiativeHeatTransferCoefficient(0.8, 289.71, 288.75)
          == Approx(4.390286024));
}

TEST_CASE("Convective Heat Transfer Coefficient", "[insulated_pipe_reduction][util]") {
    CHECK(convectiveHeatTransferCoefficient(32.8, 0.02534, 0.13335) == Approx(6.2328608924));
}

TEST_CASE("Convective Heat Transfer Coefficient 2", "[insulated_pipe_reduction][util]") {
    CHECK(convectiveHeatTransferCoefficient(12.06, 0.0263, 0.177799) == Approx(1.7839132954));
}

TEST_CASE("Convective Heat Transfer Coefficient 3", "[insulated_pipe_reduction][util]") {
    CHECK(convectiveHeatTransferCoefficient(53.5, 0.0263, 0.177799) == Approx(7.9137115507));
}

TEST_CASE("Nusselt - Forced", "[insulated_pipe_reduction][util]") {
    CHECK(nusseltForcedConvection(9975, 0.707) == Approx(53.4659543621));
}

TEST_CASE("Nusselt - Forced 2", "[insulated_pipe_reduction][util]") {
    CHECK(nusseltForcedConvection(4000.09, 0.71) == Approx(32.7247843626));
}

TEST_CASE("Nusselt - Free", "[insulated_pipe_reduction][util]") {
    CHECK(nusseltFreeConvection(511466, 0.707) == Approx(12.0557933229));
}

TEST_CASE("Nusselt - Free 2", "[insulated_pipe_reduction][util]") {
    CHECK(nusseltFreeConvection(257651.95, 0.71) == Approx(10.0034601706));
}

TEST_CASE("Nusselt - Combined", "[insulated_pipe_reduction][util]") {
    CHECK(nusseltNumber(53.5, 12.06) == Approx(53.5345022804));
}

TEST_CASE("Nusselt - Combined 2", "[insulated_pipe_reduction][util]") {
    CHECK(nusseltNumber(32.7, 10.00) == Approx(32.7712651627));
}

TEST_CASE("Thermal Resistance", "[insulated_pipe_reduction][util]") {
    CHECK(thermalResistance(0.177799, 0.177799, 0.025399, 0.05056) == Approx(3.4215474554));
}

TEST_CASE("Thermal Resistance 2", "[insulated_pipe_reduction][util]") {
    CHECK(thermalResistance(0.177799, 0.025399, 0.0220208, 57.60) == Approx(0.00022).epsilon(0.005));
}

TEST_CASE("Thermal Resistance 3", "[insulated_pipe_reduction][util]") {
    CHECK(thermalResistance(0.03175, 0.03175, 0.0282, 17.98) == Approx(0.000105).epsilon(0.005));
}

// ── Full system calculations ──────────────────────────────────────────────────

TEST_CASE("Insulated Pipe", "[insulated_pipe_reduction]") {
    InsulatedPipeInput input;
    input.operating_hours                  = 8640;
    input.pipe_length                      = 15.24;
    input.pipe_diameter                    = 0.025399;
    input.pipe_thickness                   = 0.0033782;
    input.pipe_temperature                 = 422.039;
    input.ambient_temperature              = 299.817;
    input.wind_velocity                    = 0.89408;
    input.system_efficiency                = 0.9;
    input.insulation_thickness             = 0.0762;
    input.pipe_emissivity                  = 0.8;
    input.jacket_emissivity                = 0.1;
    input.pipe_material_coefficients       = {0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1};
    input.insulation_material_coefficients = {1.57526e-12, -2.02822e-09, 8.6328e-07, 0, 0.006729488};

    InsulatedPipeOutput output = calculate(input);
    CHECK(output.heat_loss_per_length == Approx(19.3858771378));
    CHECK(output.annual_heat_loss     == Approx(2836231.3687633672));
}

TEST_CASE("Non-Insulated Pipe", "[insulated_pipe_reduction]") {
    InsulatedPipeInput input;
    input.operating_hours                  = 8640;
    input.pipe_length                      = 15.24;
    input.pipe_diameter                    = 0.025399;
    input.pipe_thickness                   = 0.0033782;
    input.pipe_temperature                 = 422.039;
    input.ambient_temperature              = 299.817;
    input.wind_velocity                    = 0.89408;
    input.system_efficiency                = 0.9;
    input.insulation_thickness             = 0;
    input.pipe_emissivity                  = 0.8;
    input.jacket_emissivity                = 0.1;
    input.pipe_material_coefficients       = {0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1};
    input.insulation_material_coefficients = {1.57526e-12, -2.02822e-09, 8.6328e-07, 0, 0.006729488};

    InsulatedPipeOutput output = calculate(input);
    CHECK(output.heat_loss_per_length == Approx(278.8984025085));
    CHECK(output.annual_heat_loss     == Approx(40803938.64));
}
