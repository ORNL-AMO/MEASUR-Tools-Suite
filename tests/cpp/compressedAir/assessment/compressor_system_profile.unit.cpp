#include "compressedAir/assessment/compressor_system_profile.h"

#include <limits>

#include "catch.hpp"

using namespace Catch;
using namespace compressed_air::assessment;

namespace {

CompressorPerformancePoint point(double pressure, double airflow, double power) {
    return {pressure, false, airflow, false, power, false};
}

CompressorProfileCompressor modulationCompressor(const std::string& id, double airflow, double full_power,
                                                  double no_load_power) {
    CompressorProfileCompressor compressor;
    compressor.compressorId                                 = id;
    compressor.compressorType                               = CompressorType::Screw;
    compressor.control                                      = CompressorControl::ModulationWithoutUnload;
    compressor.stage                                        = CompressorStage::Single;
    compressor.lubricant                                    = CompressorLubricant::Injected;
    compressor.performancePoints.fullLoad                   = point(100, airflow, full_power);
    compressor.performancePoints.noLoad                     = point(105, 0, no_load_power);
    compressor.performancePoints.maxFullFlow                = point(110, airflow, full_power);
    compressor.modulatingPressurePsig                       = 5;
    return compressor;
}

CompressorProfileRow profileRow(const std::string& compressor_id, int order) {
    CompressorProfileRow row;
    row.compressorId   = compressor_id;
    row.dayTypeId      = "weekday";
    row.timeIntervalHr = 0;
    row.operatingOrder = order;
    return row;
}

CompressorProfileOptions profileOptions(CompressorSystemControlMode mode) {
    CompressorProfileOptions options;
    options.dayTypeId               = "weekday";
    options.inputBasis              = CompressorInputBasis::MeasuredCapacity;
    options.controlMode             = mode;
    options.atmosphericPressurePsia = 14.7;
    options.totalAirStorageFt3      = 140;
    options.canShutdown             = true;
    return options;
}

} // namespace

TEST_CASE("Compressor system profile calculates baseline interval rows",
          "[compressed-air][assessment][system-profile]") {
    CompressorProfileCompressorV compressors{modulationCompressor("a", 1000, 100, 50)};
    CompressorProfileRowV        rows{profileRow("a", 1)};
    rows[0].airflowAcfm = 500;

    const auto result = calculateBaselineProfile(compressors, rows, profileOptions(CompressorSystemControlMode::Cascading));

    REQUIRE(result.size() == 1);
    CHECK(result[0].airflowAcfm == Approx(500));
    CHECK(result[0].powerKw == Approx(75));
    CHECK(result[0].airflowFraction == Approx(0.5));
    CHECK(result[0].powerFraction == Approx(0.75));
    CHECK(result[0].systemAirflowFraction == Approx(0.5));
    CHECK(result[0].systemPowerFraction == Approx(0.75));
}

TEST_CASE("Compressor system profile reallocates ordered compressor flow",
          "[compressed-air][assessment][system-profile]") {
    CompressorProfileCompressorV compressors{modulationCompressor("a", 1000, 100, 50),
                                             modulationCompressor("b", 500, 60, 30)};
    CompressorProfileRowV        rows{profileRow("a", 1), profileRow("b", 2)};

    CompressorProfileTotal demand;
    demand.dayTypeId      = "weekday";
    demand.timeIntervalHr = 0;
    demand.airflowAcfm    = 1200;

    const auto result = reallocateProfileFlow(compressors, rows, CompressorProfileTotalV{demand},
                                              profileOptions(CompressorSystemControlMode::Cascading));

    REQUIRE(result.size() == 2);
    CHECK(result[0].airflowAcfm == Approx(1000));
    CHECK(result[0].powerKw == Approx(100));
    CHECK(result[0].operatingOrder == 1);
    CHECK(result[1].airflowAcfm == Approx(200));
    CHECK(result[1].powerKw == Approx(42));
    CHECK(result[1].operatingOrder == 2);

    const auto totals = calculateProfileTotals(compressors, result);
    REQUIRE(totals.size() == 1);
    CHECK(totals[0].airflowAcfm == Approx(1200));
    CHECK(totals[0].powerKw == Approx(142));
    CHECK(totals[0].airflowFraction == Approx(0.8));
    CHECK(totals[0].powerFraction == Approx(0.8875));
}

TEST_CASE("Compressor system profile selects least-power load-sharing combination",
          "[compressed-air][assessment][system-profile]") {
    CompressorProfileCompressorV compressors{modulationCompressor("a", 1000, 100, 50),
                                             modulationCompressor("b", 500, 60, 30)};
    CompressorProfileRowV        rows{profileRow("a", 1), profileRow("b", 2)};

    CompressorProfileTotal demand;
    demand.dayTypeId      = "weekday";
    demand.timeIntervalHr = 0;
    demand.airflowAcfm    = 750;

    const auto result = reallocateProfileFlow(compressors, rows, CompressorProfileTotalV{demand},
                                              profileOptions(CompressorSystemControlMode::LoadSharing));

    REQUIRE(result.size() == 2);
    CHECK(result[0].airflowAcfm == Approx(750));
    CHECK(result[0].powerKw == Approx(87.5));
    CHECK(result[0].operatingOrder == 1);
    CHECK(result[1].airflowAcfm == Approx(0));
    CHECK(result[1].powerKw == Approx(0));
    CHECK(result[1].operatingOrder == 0);
}

TEST_CASE("Compressor system profile guards oversized load-sharing combinations",
          "[compressed-air][assessment][system-profile]") {
    CompressorProfileCompressorV compressors;
    CompressorProfileRowV rows;
    for (std::size_t i = 0; i < std::numeric_limits<std::size_t>::digits; ++i) {
        const std::string id = "c" + std::to_string(i);
        compressors.push_back(modulationCompressor(id, 100, 10, 5));
        rows.push_back(profileRow(id, static_cast<int>(i + 1)));
    }

    CompressorProfileTotal demand;
    demand.dayTypeId      = "weekday";
    demand.timeIntervalHr = 0;
    demand.airflowAcfm    = 500;

    const auto result = reallocateProfileFlow(compressors, rows, CompressorProfileTotalV{demand},
                                              profileOptions(CompressorSystemControlMode::LoadSharing));

    REQUIRE(result.size() == rows.size());
    for (const auto& row : result) {
        CHECK(row.airflowAcfm == Approx(0));
        CHECK(row.powerKw == Approx(0));
        CHECK(row.operatingOrder == 0);
    }
}

TEST_CASE("Compressor profile savings calculate energy cost and payback",
          "[compressed-air][assessment][system-profile]") {
    CompressorProfileRow baseline_a = profileRow("a", 1);
    CompressorProfileRow baseline_b = profileRow("b", 2);
    baseline_a.powerKw = 100;
    baseline_b.powerKw = 42;
    CompressorProfileRow adjusted_a = profileRow("a", 1);
    CompressorProfileRow adjusted_b = profileRow("b", 0);
    adjusted_a.powerKw = 87.5;

    CompressorProfileSavingsInput input;
    input.dayTypeId              = "weekday";
    input.electricityCostPerKwh  = 0.1;
    input.intervalHours          = 1;
    input.operatingDays          = 10;
    input.implementationCost     = 100;

    const auto savings = calculateProfileSavings({baseline_a, baseline_b}, {adjusted_a, adjusted_b}, input);

    CHECK(savings.baselineEnergyKwh == Approx(1420));
    CHECK(savings.adjustedEnergyKwh == Approx(875));
    CHECK(savings.energySavingsKwh == Approx(545));
    CHECK(savings.costSavings == Approx(54.5));
    CHECK(savings.percentSavings == Approx(38.3803));
    CHECK(savings.paybackMonths == Approx(22.0183));
}

TEST_CASE("Compressor system profile pressure-reduced airflow uses atmospheric pressure",
          "[compressed-air][assessment][system-profile]") {
    CHECK(calculatePressureReducedAirflow(1000, 95, 12.2, 100, 12.2) == Approx(973.262));
    CHECK(calculatePressureReducedAirflow(1000, 95, 12.2, -12.2, 12.2) == Approx(1000));
}
