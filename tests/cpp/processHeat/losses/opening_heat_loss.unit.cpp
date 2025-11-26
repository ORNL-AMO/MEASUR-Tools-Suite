#include <processHeat/losses/opening_heat_loss_losses.h>

#include "catch.hpp"

using namespace Catch;

// Circular
TEST_CASE("Calculate Heat Loss for opening Heat Losses Circular", "[Heat Loss]") {
    double emissivity = 0.95;
    double diameter = 12.0;
    double ambientTemperature = 75.0;
    double insideTemperature = 1600.0;
    double percentTimeOpen = 100.0;
    double viewFactor = 0.70;
    REQUIRE(opening_heat_loss::totalHeatLossCircular(emissivity, diameter, ambientTemperature, insideTemperature, percentTimeOpen, viewFactor) ==
            Approx(16042.398918636909));
}

// Quadrilateral
TEST_CASE("Calculate Heat Loss for opening Heat Losses Quad", "[Heat Loss]") {
    double emissivity = 0.95;
    double length = 48.0;
    double width = 15.0;
    double ambientTemperature = 75.0;
    double insideTemperature = 1600.0;
    double percentTimeOpen = 20.0;
    double viewFactor = 0.64;
    REQUIRE(opening_heat_loss::totalHeatLossQuad(emissivity, length, width, ambientTemperature, insideTemperature, percentTimeOpen, viewFactor) ==
            Approx(18675.03240742869));
}

TEST_CASE("Calculate viewFactor for Opening Losses Circular", "[Heat Loss][viewFactor]") {
    // Circular view factor calculations
    CHECK(opening_heat_loss::calculateViewFactorCircular(3, 5) == Approx(0.624519890259));
    CHECK(opening_heat_loss::calculateViewFactorCircular(1, 5) == Approx(0.83499999996));
    CHECK(opening_heat_loss::calculateViewFactorCircular(0, 5) == Approx(0.86));
    CHECK(opening_heat_loss::calculateViewFactorCircular(10, 5) == Approx(0.35084375));
    CHECK(opening_heat_loss::calculateViewFactorCircular(50, 5) == Approx(0.098254464286));
    CHECK(opening_heat_loss::calculateViewFactorCircular(50, 9) == Approx(0.160395178571));
    CHECK(opening_heat_loss::calculateViewFactorCircular(50, 19) == Approx(0.289271964286));
}

TEST_CASE("Calculate viewFactor for Opening Losses Quad", "[Heat Loss][viewFactor]") {
    // Rectangular view factor calculations
    CHECK(opening_heat_loss::calculateViewFactorQuad(5, 5, 10) == Approx(0.60));
    CHECK(opening_heat_loss::calculateViewFactorQuad(5, 10, 5) == Approx(0.60));
    CHECK(opening_heat_loss::calculateViewFactorQuad(1, 10, 5) == Approx(0.88));
    CHECK(opening_heat_loss::calculateViewFactorQuad(2, 10, 5) == Approx(0.786933593749));
    CHECK(opening_heat_loss::calculateViewFactorQuad(27, 50, 55) == Approx(0.678646418065));
    CHECK(opening_heat_loss::calculateViewFactorQuad(0.5, 3, 4) == Approx(0.876666666245));
    CHECK(opening_heat_loss::calculateViewFactorQuad(14.05, 3, 3) == Approx(0.2044991347));
}
