#include "catch.hpp"

#include "compressedAir/leak_survey/bag_method.h"

using namespace Catch;
using namespace bag_method;

TEST_CASE("BagMethod - Flow Rate", "[CompressedAir][BagMethod][FlowRate]") {
    // flowRate = (bagVolume * 60) / bagFillTime
    CHECK(calculate({8760, 12, 8.68}).flow_rate == Approx(43.4));
    CHECK(calculate({8760, 10, 12.0}).flow_rate == Approx(72.0));
    CHECK(calculate({8760,  6, 10.0}).flow_rate == Approx(100.0));
    CHECK(calculate({8760, 30,  5.0}).flow_rate == Approx(10.0));
}

TEST_CASE("BagMethod - Annual Consumption", "[CompressedAir][BagMethod][AnnualConsumption]") {
    // annualConsumption = (flowRate * operatingTime * numberOfUnits * 60) / 1000
    CHECK(calculate({8760, 12, 8.68}).annual_consumption == Approx(22811.04));
    CHECK(calculate({15,   10, 12.0}).annual_consumption == Approx(64.8));
    CHECK(calculate({8640, 10, 12.0}).annual_consumption == Approx(37324.8));
}
