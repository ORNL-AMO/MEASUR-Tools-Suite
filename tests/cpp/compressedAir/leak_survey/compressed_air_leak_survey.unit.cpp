#include "catch.hpp"

#include "compressedAir/leak_survey/compressed_air_leak_survey.h"

using namespace Catch;
using namespace compressed_air_leak_survey;

namespace {

// Default sub-method inputs shared across test cases (only the selected method matters)
const estimate_method::Input  kDefaultEstimate  = {0, 0.1};
const decibels_method::Input  kDefaultDecibels  = {0, 130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65};
const bag_method::Input       kDefaultBag       = {8760, 12, 8.68};
const orifice_method::Input   kDefaultOrifice   = {0.0, 250.0, 14.7, 1.0, 6.0, 6.2, 4};
const compressed_air_utils::CompressorElectricityData kDefaultElecData = {0.40, 0.16};

Input makeInput(int hours_per_year, int utility_type, double utility_cost,
                int measurement_method,
                const estimate_method::Input&  est,
                const decibels_method::Input&  deb,
                const bag_method::Input&       bag,
                const orifice_method::Input&   orf,
                const compressed_air_utils::CompressorElectricityData& elec,
                int units) {
    Input in;
    in.hours_per_year            = hours_per_year;
    in.utility_type              = utility_type;
    in.utility_cost              = utility_cost;
    in.measurement_method        = measurement_method;
    in.estimate_input            = est;
    in.decibels_input            = deb;
    in.bag_input                 = bag;
    in.orifice_input             = orf;
    in.compressor_electricity_data = elec;
    in.units                     = units;
    return in;
}

} // namespace

TEST_CASE("CompressedAirLeakSurvey - Estimate Method, Electricity (8640 hr)",
          "[CompressedAir][CompressedAirLeakSurvey][EstimateMethod]") {
    auto input = makeInput(8640, 1, 0.12, 0,
                           {8640, 0.1}, kDefaultDecibels, kDefaultBag, kDefaultOrifice,
                           {0.40, 0.16}, 1);
    auto result = calculate({input});
    CHECK(result.annual_total_electricity      == Approx(138.24));
    CHECK(result.annual_total_electricity_cost == Approx(16.5888));
    CHECK(result.total_flow_rate               == Approx(0.1));
    CHECK(result.annual_total_flow_rate        == Approx(51840));
}

TEST_CASE("CompressedAirLeakSurvey - Estimate Method, Electricity (3840 hr)",
          "[CompressedAir][CompressedAirLeakSurvey][EstimateMethod]") {
    auto input = makeInput(3840, 1, 0.12, 0,
                           {3840, 0.1}, kDefaultDecibels,
                           bag_method::Input{3840, 12, 8.68},
                           kDefaultOrifice,
                           {0.25, 0.16}, 1);
    auto result = calculate({input});
    CHECK(result.annual_total_electricity      == Approx(61.44));
    CHECK(result.annual_total_electricity_cost == Approx(7.3728));
    CHECK(result.total_flow_rate               == Approx(0.1));
    CHECK(result.annual_total_flow_rate        == Approx(23040));
}

TEST_CASE("CompressedAirLeakSurvey - Estimate Method, Electricity (large leak rate)",
          "[CompressedAir][CompressedAirLeakSurvey][EstimateMethod]") {
    auto input = makeInput(8760, 1, 0.12, 0,
                           {8760, 100}, kDefaultDecibels, kDefaultBag, kDefaultOrifice,
                           {0.25, 0.16}, 1);
    auto result = calculate({input});
    CHECK(result.annual_total_electricity      == Approx(140160.0));
    CHECK(result.annual_total_electricity_cost == Approx(16819.2));
    CHECK(result.total_flow_rate               == Approx(100));
    CHECK(result.annual_total_flow_rate        == Approx(52560000));
}

TEST_CASE("CompressedAirLeakSurvey - Decibels Method, Electricity",
          "[CompressedAir][CompressedAirLeakSurvey][DecibelsMethod]") {
    auto input = makeInput(8640, 1, 0.12, 1,
                           {8640, 0.1}, kDefaultDecibels,
                           bag_method::Input{15, 10, 12},
                           kDefaultOrifice,
                           {0.40, 0.16}, 1);
    auto result = calculate({input});
    CHECK(result.annual_total_electricity      == Approx(1975.4496));
    CHECK(result.annual_total_electricity_cost == Approx(237.053952));
    CHECK(result.total_flow_rate               == Approx(1.429));
    CHECK(result.annual_total_flow_rate        == Approx(740793.6));
}

TEST_CASE("CompressedAirLeakSurvey - Bag Method, Electricity",
          "[CompressedAir][CompressedAirLeakSurvey][BagMethod]") {
    auto input = makeInput(8640, 1, 0.12, 2,
                           {8640, 0.1}, kDefaultDecibels,
                           bag_method::Input{15, 10, 12},
                           kDefaultOrifice,
                           {0.40, 0.16}, 2);
    auto result = calculate({input});
    CHECK(result.annual_total_electricity      == Approx(0.3456));
    CHECK(result.annual_total_electricity_cost == Approx(0.041472));
    CHECK(result.total_flow_rate               == Approx(144.0));
    CHECK(result.annual_total_flow_rate        == Approx(129.6));
}

TEST_CASE("CompressedAirLeakSurvey - Orifice Method, Electricity",
          "[CompressedAir][CompressedAirLeakSurvey][OrificeMethod]") {
    auto input = makeInput(8640, 1, 0.12, 3,
                           {8640, 0.1}, kDefaultDecibels,
                           bag_method::Input{15, 10, 12},
                           orifice_method::Input{0.0, 550.0, 14.7, 1.0, 0.375, 100.0, 4},
                           {0.40, 0.16}, 1);
    auto result = calculate({input});
    CHECK(result.annual_total_electricity      == Approx(1790380.8424647334));
    CHECK(result.annual_total_electricity_cost == Approx(214845.701095768));
    CHECK(result.total_flow_rate               == Approx(1295.1250307181));
    CHECK(result.annual_total_flow_rate        == Approx(671392815.9242750406));
}
