#include "catch.hpp"

#include "compressedAir/bag_method.h"

using namespace Catch;
using namespace bag_method;

TEST_CASE("BagMethod - Flow Rate", "[CompressedAir][BagMethod][FlowRate]") {
    // flowRate = (bagVolume * 60) / bagFillTime
    CHECK(calculate({8760, 12, 8.68, 1}).flow_rate == Approx(43.4));
    CHECK(calculate({8760, 10, 12.0, 1}).flow_rate == Approx(72.0));
    CHECK(calculate({8760,  6, 10.0, 1}).flow_rate == Approx(100.0));
    CHECK(calculate({8760, 30,  5.0, 1}).flow_rate == Approx(10.0));
}

TEST_CASE("BagMethod - Annual Consumption", "[CompressedAir][BagMethod][AnnualConsumption]") {
    // annualConsumption = (flowRate * operatingTime * numberOfUnits * 60) / 1000
    CHECK(calculate({8760, 12, 8.68, 1}).annual_consumption == Approx(22811.04));
    CHECK(calculate({15,   10, 12.0, 1}).annual_consumption == Approx(64.8));
    CHECK(calculate({8640, 10, 12.0, 1}).annual_consumption == Approx(37324.8));
}

TEST_CASE("BagMethod - Number of Units Multiplier", "[CompressedAir][BagMethod][NumberOfUnits]") {
    auto single = calculate({8760, 10, 12.0, 1});
    auto multi  = calculate({8760, 10, 12.0, 3});
    CHECK(single.flow_rate == Approx(72.0));
    CHECK(multi.flow_rate  == Approx(72.0)); // flow rate is per-unit, not scaled
    CHECK(multi.annual_consumption == Approx(single.annual_consumption * 3));
}
