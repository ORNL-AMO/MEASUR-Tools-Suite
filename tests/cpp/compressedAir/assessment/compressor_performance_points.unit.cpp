#include "compressedAir/assessment/compressor_performance_points.h"

#include <cmath>

#include "catch.hpp"

using namespace Catch;
using namespace compressed_air::assessment;

namespace {

CompressorPerformancePoint defaultPoint() { return {}; }

CompressorPerformancePointInput screwModulationWithUnloadInput() {
    CompressorPerformancePointInput input;
    input.nameplate.compressorType               = CompressorType::Screw;
    input.nameplate.stage                        = CompressorStage::Single;
    input.nameplate.lubricant                    = CompressorLubricant::Injected;
    input.nameplate.fullLoadOperatingPressurePsig = 100;
    input.nameplate.fullLoadRatedCapacityAcfm    = 1048;
    input.nameplate.totalPackageInputPowerKw     = 166.5;
    input.controls.control                       = CompressorControl::ModulationUnload;
    input.controls.unloadPointCapacityPct        = 90;
    input.controls.unloadSumpPressurePsig        = 15;
    input.design.inputPressurePsia               = 14.5;
    input.design.designEfficiencyPct             = 75;
    input.design.maxFullFlowPressurePsig         = 110;
    input.design.modulatingPressurePsig          = 5;
    input.design.noLoadPowerFMPercent            = 70;
    input.design.noLoadPowerULPercent            = 25;
    input.points.fullLoad                        = defaultPoint();
    input.points.maxFullFlow                     = defaultPoint();
    input.points.unloadPoint                     = defaultPoint();
    input.points.noLoad                          = defaultPoint();
    input.atmosphericPressurePsia                = 14.7;
    return input;
}

} // namespace

TEST_CASE("Compressor performance point generation ports Desktop defaults",
          "[compressed-air][assessment][performance-points]") {
    const auto points = generatePerformancePoints(screwModulationWithUnloadInput());

    CHECK(points.fullLoad.dischargePressurePsig == Approx(100));
    CHECK(points.fullLoad.airflowAcfm == Approx(1048));
    CHECK(points.fullLoad.powerKw == Approx(166.5));

    CHECK(points.maxFullFlow.dischargePressurePsig == Approx(110));
    CHECK(points.maxFullFlow.airflowAcfm == Approx(1040));
    CHECK(points.maxFullFlow.powerKw == Approx(175.6));

    CHECK(points.unloadPoint.airflowAcfm == Approx(943));
    CHECK(points.unloadPoint.dischargePressurePsig == Approx(110.5));
    CHECK(points.unloadPoint.powerKw == Approx(170.3));

    CHECK(points.noLoad.dischargePressurePsig == Approx(15));
    CHECK(points.noLoad.airflowAcfm == Approx(0));
    CHECK(points.noLoad.powerKw == Approx(41.6));
}

TEST_CASE("VFD performance points preserve Desktop turndown defaults",
          "[compressed-air][assessment][performance-points]") {
    CompressorPerformancePointInput input;
    input.nameplate.compressorType               = CompressorType::Screw;
    input.nameplate.lubricant                    = CompressorLubricant::Injected;
    input.nameplate.fullLoadOperatingPressurePsig = 100;
    input.nameplate.fullLoadRatedCapacityAcfm    = 1009;
    input.nameplate.totalPackageInputPowerKw     = 174.4;
    input.controls.control                       = CompressorControl::Vfd;
    input.controls.unloadPointCapacityPct        = 20;
    input.design.inputPressurePsia               = 14.5;
    input.design.designEfficiencyPct             = 75;
    input.design.noLoadPowerULPercent            = 25;
    input.atmosphericPressurePsia                = 14.7;

    const auto points = generatePerformancePoints(input);

    CHECK(points.midTurndown.airflowAcfm == Approx(605));
    CHECK(points.midTurndown.dischargePressurePsig == Approx(102.4));
    CHECK(points.midTurndown.powerKw == Approx(115));
    CHECK(points.turndown.airflowAcfm == Approx(202));
    CHECK(points.turndown.dischargePressurePsig == Approx(104.8));
    CHECK(points.turndown.powerKw == Approx(55.8));
}

TEST_CASE("Performance point scalar helpers expose Desktop formulas",
          "[compressed-air][assessment][performance-points]") {
    CHECK(calculateUnloadPointPower(70, 90, 1, 175.6) == Approx(170.3));
    CHECK(calculateUnloadPointAirflow(1048, 90) == Approx(943.2));
    CHECK(calculateUnloadPointDischargePressure(110, 5, 1048, 943.2) == Approx(110.5));
    CHECK(calculateRatedSpecificPower(166.5, 1048) == Approx(15.8874));
    CHECK(calculateRatedIsentropicEfficiency(15.8874, 100) == Approx(83.6711));
}

TEST_CASE("Pressure-adjusted power guards invalid pressure bases",
          "[compressed-air][assessment][performance-points]") {
    CHECK(calculatePressureAdjustedPower(CompressorType::Screw, 0, 100, 100, 166.5, 14.7) == Approx(0));
    CHECK(calculatePressureAdjustedPower(CompressorType::Reciprocating, 14.5, 100, 100, 166.5, 0) == Approx(0));

    auto input = screwModulationWithUnloadInput();
    input.design.inputPressurePsia = 0;

    const auto points = generatePerformancePoints(input);

    CHECK(std::isfinite(points.fullLoad.powerKw));
    CHECK(std::isfinite(points.maxFullFlow.powerKw));
    CHECK(std::isfinite(points.unloadPoint.powerKw));
    CHECK(points.fullLoad.powerKw == Approx(0));
    CHECK(points.maxFullFlow.powerKw == Approx(0));
    CHECK(points.unloadPoint.powerKw == Approx(0));
}

TEST_CASE("No-load power guards invalid design efficiency",
          "[compressed-air][assessment][performance-points]") {
    CHECK(calculateNoLoadPower(10, 166.5, 0) == Approx(0));

    auto input = screwModulationWithUnloadInput();
    input.design.designEfficiencyPct  = 0;
    input.design.noLoadPowerULPercent = 10;

    const auto points = generatePerformancePoints(input);

    CHECK(std::isfinite(points.noLoad.powerKw));
    CHECK(points.noLoad.powerKw == Approx(0));
}
