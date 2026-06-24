#include "compressedAir/assessment/compressor_system_profile.h"

#include <algorithm>
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

CompressorProfileCompressor loadUnloadCompressor(const std::string& id, double airflow, double full_power,
                                                  double max_power, double no_load_power) {
    CompressorProfileCompressor compressor;
    compressor.compressorId                   = id;
    compressor.compressorType                 = CompressorType::Screw;
    compressor.control                        = CompressorControl::LoadUnload;
    compressor.stage                          = CompressorStage::Single;
    compressor.lubricant                      = CompressorLubricant::Injected;
    compressor.performancePoints.fullLoad     = point(175, airflow, full_power);
    compressor.performancePoints.maxFullFlow  = point(185, airflow, max_power);
    compressor.performancePoints.noLoad       = point(15, 0, no_load_power);
    compressor.performancePoints.unloadPoint  = point(0, 0, 0);
    compressor.blowdownTimeSec                = 40;
    compressor.unloadSumpPressurePsig         = 15;
    compressor.modulatingPressurePsig         = 0;
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

CompressorProfileCompressor baseTrimVariableDisplacementCompressor(const std::string& id,
                                                                    double modulating_pressure,
                                                                    double unload_pressure) {
    CompressorProfileCompressor compressor;
    compressor.compressorId                   = id;
    compressor.compressorType                 = CompressorType::Screw;
    compressor.control                        = CompressorControl::VariableDisplacementUnload;
    compressor.stage                          = CompressorStage::Single;
    compressor.lubricant                      = CompressorLubricant::Injected;
    compressor.automaticShutdown              = true;
    compressor.performancePoints.fullLoad     = point(100, 365, 63.8);
    compressor.performancePoints.maxFullFlow  = point(100, 365, 63.8);
    compressor.performancePoints.unloadPoint  = point(unload_pressure, 182, 45);
    compressor.performancePoints.noLoad       = point(15, 0, 35);
    compressor.blowdownTimeSec                = 40;
    compressor.unloadSumpPressurePsig         = 15;
    compressor.unloadPointCapacityPct         = 40;
    compressor.noLoadPowerFractionForModulation = 0.57;
    compressor.modulatingPressurePsig         = modulating_pressure;
    return compressor;
}

CompressorProfileCompressor baseTrimVfdCompressor() {
    CompressorProfileCompressor compressor;
    compressor.compressorId                  = "p8p62x1d2";
    compressor.compressorType                = CompressorType::Screw;
    compressor.control                       = CompressorControl::Vfd;
    compressor.stage                         = CompressorStage::Single;
    compressor.lubricant                     = CompressorLubricant::Injected;
    compressor.performancePoints.fullLoad    = point(115, 342, 66.9);
    compressor.performancePoints.midTurndown = point(117.4, 205, 45);
    compressor.performancePoints.turndown    = point(119.1, 109, 25.9);
    compressor.performancePoints.noLoad      = point(15, 0, 4.6);
    compressor.blowdownTimeSec               = 40;
    compressor.unloadSumpPressurePsig        = 15;
    compressor.noLoadPowerFractionForModulation = 0.65;
    compressor.modulatingPressurePsig        = 20;
    return compressor;
}

CompressorProfileRow baseTrimProfileRow(const std::string& compressor_id, int order,
                                         double power_factor, double amps) {
    CompressorProfileRow row;
    row.compressorId   = compressor_id;
    row.dayTypeId      = "hvb0u7041";
    row.timeIntervalHr = 11;
    row.operatingOrder = order;
    row.powerFactor    = power_factor;
    row.amps           = amps;
    row.volts          = 480;
    return row;
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

TEST_CASE("Compressor system profile caps measured-power capacity for modulation without unload",
          "[compressed-air][assessment][system-profile]") {
    CompressorProfileCompressor compressor = modulationCompressor("srocxit1z", 18, 4.6, 3);
    compressor.noLoadPowerFractionForModulation = 0.65;
    compressor.blowdownTimeSec = 40;
    compressor.unloadSumpPressurePsig = 15;

    CompressorProfileCompressorV compressors{compressor};
    CompressorProfileRowV rows{profileRow("srocxit1z", 1)};
    rows[0].dayTypeId = "cbpa0zvju";
    rows[0].powerKw = 5;

    CompressorProfileOptions options;
    options.dayTypeId = "cbpa0zvju";
    options.inputBasis = CompressorInputBasis::MeasuredPower;
    options.controlMode = CompressorSystemControlMode::Cascading;
    options.atmosphericPressurePsia = 14.7;
    options.totalAirStorageFt3 = 200.5208333339;
    options.canShutdown = true;

    const auto result = calculateBaselineProfile(compressors, rows, options);

    REQUIRE(result.size() == 1);
    CHECK(result[0].powerKw == Approx(5));
    CHECK(result[0].airflowAcfm == Approx(18));
    CHECK(result[0].powerFraction == Approx(1.0869565217));
    CHECK(result[0].airflowFraction == Approx(1));
}

TEST_CASE("Compressor system profile calculates desktop two-compressor measured-power load/unload row",
          "[compressed-air][assessment][system-profile]") {
    CompressorProfileCompressor modulation = modulationCompressor("srocxit1z", 18, 4.6, 3);
    modulation.noLoadPowerFractionForModulation = 0.65;
    modulation.blowdownTimeSec                  = 40;
    modulation.unloadSumpPressurePsig           = 15;

    CompressorProfileCompressorV compressors{
        modulation,
        loadUnloadCompressor("8sxdv5qti", 12, 4.6, 4.7, 1.7),
    };
    CompressorProfileRowV rows{profileRow("srocxit1z", 2), profileRow("8sxdv5qti", 1)};
    for (auto& row : rows) {
        row.dayTypeId = "cbpa0zvju";
        row.powerKw   = 5;
    }
    rows[0].airflowFraction = 0.5;

    CompressorProfileOptions options;
    options.dayTypeId               = "cbpa0zvju";
    options.inputBasis              = CompressorInputBasis::MeasuredPower;
    options.controlMode             = CompressorSystemControlMode::Cascading;
    options.atmosphericPressurePsia = 14.7;
    options.totalAirStorageFt3      = 200.52093668342548;
    options.canShutdown             = true;

    const auto result = calculateBaselineProfile(compressors, rows, options);

    REQUIRE(result.size() == 2);
    CHECK(result[0].airflowAcfm == Approx(18));
    CHECK(result[0].airflowFraction == Approx(1));
    CHECK(result[0].systemAirflowFraction == Approx(0.6));
    CHECK(result[0].systemPowerFraction == Approx(0.5434782609));

    CHECK(result[1].powerKw == Approx(5));
    CHECK(result[1].airflowAcfm == Approx(13.99).margin(0.01));
    CHECK(result[1].airflowFraction == Approx(1.1656).margin(0.0001));
    CHECK(result[1].systemAirflowFraction == Approx(13.99 / 30).margin(0.001));
    CHECK(result[1].systemPowerFraction == Approx(0.5434782609));
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

TEST_CASE("Compressor system profile reallocates desktop base-trim interval with electrical base input",
          "[compressed-air][assessment][system-profile]") {
    CompressorProfileCompressorV compressors{
        baseTrimVariableDisplacementCompressor("diagqi3k4", 15, 109),
        baseTrimVariableDisplacementCompressor("3qo7b7u3w", 16.7, 110),
        baseTrimVfdCompressor(),
    };
    CompressorProfileRowV rows{
        baseTrimProfileRow("diagqi3k4", 2, 0.87, 77),
        baseTrimProfileRow("3qo7b7u3w", 3, 0.87, 56),
        baseTrimProfileRow("p8p62x1d2", 1, 0.87, 79),
    };

    CompressorProfileTotal demand;
    demand.dayTypeId        = "hvb0u7041";
    demand.timeIntervalHr   = 11;
    demand.airflowAcfm      = 677.1060361264512;
    demand.powerKw          = 153.3360384;
    demand.totalPowerKw     = 153.3360384;
    demand.airflowFraction  = 0.6316287650433314;
    demand.powerFraction    = 0.7883600946015424;

    CompressorProfileOptions options;
    options.dayTypeId               = "hvb0u7041";
    options.inputBasis              = CompressorInputBasis::Electrical;
    options.controlMode             = CompressorSystemControlMode::BaseTrim;
    options.atmosphericPressurePsia = 14.7;
    options.totalAirStorageFt3      = 5000;
    options.canShutdown             = true;

    CompressorTrimSelection trim;
    trim.dayTypeId     = "hvb0u7041";
    trim.compressorId  = "p8p62x1d2";

    const auto result = reallocateProfileFlow(compressors, rows, CompressorProfileTotalV{demand},
                                              options, {}, CompressorTrimSelectionV{trim});

    REQUIRE(result.size() == 3);
    const auto trim_row = std::find_if(result.begin(), result.end(), [](const auto& row) {
        return row.compressorId == "p8p62x1d2";
    });
    const auto base_row = std::find_if(result.begin(), result.end(), [](const auto& row) {
        return row.compressorId == "diagqi3k4";
    });
    const auto unused_base_row = std::find_if(result.begin(), result.end(), [](const auto& row) {
        return row.compressorId == "3qo7b7u3w";
    });

    REQUIRE(base_row != result.end());
    REQUIRE(trim_row != result.end());
    REQUIRE(unused_base_row != result.end());

    CHECK(base_row->operatingOrder == 1);
    CHECK(base_row->powerKw == Approx(63.8).margin(0.001));
    CHECK(base_row->airflowAcfm == Approx(365).margin(0.001));
    CHECK(base_row->airflowFraction == Approx(1).margin(0.0001));
    CHECK(base_row->powerFraction == Approx(1).margin(0.0001));

    CHECK(trim_row->operatingOrder == 2);
    CHECK(trim_row->powerKw == Approx(62.658691).margin(0.001));
    CHECK(trim_row->airflowAcfm == Approx(312.106036).margin(0.001));
    CHECK(trim_row->airflowFraction == Approx(0.9125907).margin(0.0001));
    CHECK(trim_row->powerFraction == Approx(0.9366023).margin(0.0001));

    CHECK(unused_base_row->operatingOrder == 0);
    CHECK(unused_base_row->powerKw == Approx(0).margin(0.001));
    CHECK(unused_base_row->airflowAcfm == Approx(0).margin(0.001));
}

TEST_CASE("Compressor system profile allows selected base compressors below full load in base-trim mode",
          "[compressed-air][assessment][system-profile]") {
    CompressorProfileCompressorV compressors{
        baseTrimVariableDisplacementCompressor("diagqi3k4", 15, 109),
        baseTrimVariableDisplacementCompressor("3qo7b7u3w", 16.7, 110),
        baseTrimVfdCompressor(),
    };
    CompressorProfileRowV rows{
        baseTrimProfileRow("diagqi3k4", 2, 0.87, 77),
        baseTrimProfileRow("3qo7b7u3w", 3, 0.87, 56),
        baseTrimProfileRow("p8p62x1d2", 1, 0.87, 79),
    };

    CompressorProfileTotal demand;
    demand.dayTypeId      = "hvb0u7041";
    demand.timeIntervalHr = 11;
    demand.airflowAcfm    = 350;

    CompressorProfileOptions options;
    options.dayTypeId               = "hvb0u7041";
    options.inputBasis              = CompressorInputBasis::Electrical;
    options.controlMode             = CompressorSystemControlMode::BaseTrim;
    options.atmosphericPressurePsia = 14.7;
    options.totalAirStorageFt3      = 5000;
    options.canShutdown             = true;

    CompressorTrimSelection trim;
    trim.dayTypeId     = "hvb0u7041";
    trim.compressorId  = "p8p62x1d2";

    const auto result = reallocateProfileFlow(compressors, rows, CompressorProfileTotalV{demand},
                                              options, {}, CompressorTrimSelectionV{trim});

    REQUIRE(result.size() == 3);
    const auto base_row = std::find_if(result.begin(), result.end(), [](const auto& row) {
        return row.compressorId == "diagqi3k4";
    });
    const auto trim_row = std::find_if(result.begin(), result.end(), [](const auto& row) {
        return row.compressorId == "p8p62x1d2";
    });

    REQUIRE(base_row != result.end());
    REQUIRE(trim_row != result.end());
    CHECK(base_row->operatingOrder == 1);
    CHECK(base_row->airflowAcfm == Approx(350).margin(0.001));
    CHECK(base_row->airflowFraction == Approx(350.0 / 365.0).margin(0.0001));
    CHECK(trim_row->operatingOrder == 2);
    CHECK(trim_row->airflowAcfm == Approx(0).margin(0.001));
    CHECK(trim_row->airflowFraction == Approx(0).margin(0.0001));
}

TEST_CASE("Compressor system profile selects the smallest lowest-power base set in base-trim mode",
          "[compressed-air][assessment][system-profile]") {
    CompressorProfileCompressorV compressors{
        modulationCompressor("baseA", 8, 80, 40),
        modulationCompressor("baseB", 7, 7, 3.5),
        modulationCompressor("trim", 4, 4, 2),
    };

    CompressorProfileOptions options = profileOptions(CompressorSystemControlMode::BaseTrim);
    CompressorTrimSelection trim;
    trim.dayTypeId    = "weekday";
    trim.compressorId = "trim";

    auto calculate = [&](double airflow_demand) {
        CompressorProfileRowV rows{profileRow("baseA", 2), profileRow("baseB", 3), profileRow("trim", 1)};
        CompressorProfileTotal demand;
        demand.dayTypeId      = "weekday";
        demand.timeIntervalHr = 0;
        demand.airflowAcfm    = airflow_demand;
        return reallocateProfileFlow(compressors, rows, CompressorProfileTotalV{demand},
                                     options, {}, CompressorTrimSelectionV{trim});
    };

    SECTION("trim only") {
        const auto result = calculate(4);
        REQUIRE(result.size() == 3);
        CHECK(result[0].airflowAcfm == Approx(0));
        CHECK(result[1].airflowAcfm == Approx(0));
        CHECK(result[2].airflowAcfm == Approx(4));
    }

    SECTION("lowest-power single base plus trim remainder") {
        const auto result = calculate(10);
        REQUIRE(result.size() == 3);
        CHECK(result[0].airflowAcfm == Approx(0));
        CHECK(result[1].airflowAcfm == Approx(7));
        CHECK(result[1].operatingOrder == 1);
        CHECK(result[2].airflowAcfm == Approx(3));
        CHECK(result[2].operatingOrder == 2);
    }

    SECTION("selected base can be below full load") {
        const auto result = calculate(5);
        REQUIRE(result.size() == 3);
        CHECK(result[0].airflowAcfm == Approx(0));
        CHECK(result[1].airflowAcfm == Approx(5));
        CHECK(result[1].airflowFraction == Approx(5.0 / 7.0));
        CHECK(result[2].airflowAcfm == Approx(0));
    }

    SECTION("all selected bases plus trim remainder") {
        const auto result = calculate(16);
        REQUIRE(result.size() == 3);
        CHECK(result[0].airflowAcfm == Approx(8));
        CHECK(result[1].airflowAcfm == Approx(7));
        CHECK(result[2].airflowAcfm == Approx(1));
    }
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
