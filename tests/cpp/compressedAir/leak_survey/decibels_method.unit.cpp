#include "catch.hpp"

#include "compressedAir/leak_survey/decibels_method.h"

using namespace Catch;
using namespace decibels_method;

TEST_CASE("DecibelsMethod - Leak Rate Estimate (bilinear interpolation)", "[CompressedAir][DecibelsMethod][LeakRateEstimate]") {
    // Reference data: pressureA=150, pressureB=125, decibelRatingA=20, decibelRatingB=30
    // firstFlowA=Q(pressureA,dBA)=1.04, secondFlowA=Q(pressureB,dBA)=1.20
    // firstFlowB=Q(pressureA,dBB)=1.85, secondFlowB=Q(pressureB,dBB)=1.65
    CHECK(calculate({1280, 130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65}).leak_rate_estimate == Approx(1.429).epsilon(0.001));

    // At corner (pressureA, decibelRatingA) -> result must equal firstFlowA
    CHECK(calculate({0, 150, 20, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65}).leak_rate_estimate == Approx(1.04));

    // At corner (pressureB, decibelRatingA) -> result must equal secondFlowA
    CHECK(calculate({0, 125, 20, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65}).leak_rate_estimate == Approx(1.20));

    // At corner (pressureA, decibelRatingB) -> result must equal firstFlowB
    CHECK(calculate({0, 150, 30, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65}).leak_rate_estimate == Approx(1.85));

    // At corner (pressureB, decibelRatingB) -> result must equal secondFlowB
    CHECK(calculate({0, 125, 30, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65}).leak_rate_estimate == Approx(1.65));
}

TEST_CASE("DecibelsMethod - Bilinear Interpolation at Center", "[CompressedAir][DecibelsMethod][LeakRateEstimate]") {
    // Grid: pressureA=90, pressureB=110, decibelRatingA=30, decibelRatingB=50
    // Measuring at center (P=100, L=40): result is average of all four corners
    // Q11=2.0, Q21=2.5, Q12=3.0, Q22=3.5 -> average = 2.75
    CHECK(calculate({8760, 100, 40, 30, 90, 2.0, 2.5, 50, 110, 3.0, 3.5}).leak_rate_estimate == Approx(2.75));
}

TEST_CASE("DecibelsMethod - Annual Consumption", "[CompressedAir][DecibelsMethod][AnnualConsumption]") {
    // annualConsumption = (leakRateEstimate * operatingTime * 60) / 1000
    CHECK(calculate({1280, 130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65}).annual_consumption == Approx(109.7472).epsilon(0.001));
    CHECK(calculate({8760, 100, 40, 30,  90, 2.0, 2.5, 50, 110, 3.0,  3.5}).annual_consumption  == Approx(1445.4));
    CHECK(calculate({0,    130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65}).annual_consumption == Approx(0.0));
}
