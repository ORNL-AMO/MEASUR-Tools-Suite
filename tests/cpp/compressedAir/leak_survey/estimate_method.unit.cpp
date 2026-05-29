#include "catch.hpp"

#include "compressedAir/leak_survey/estimate_method.h"

using namespace Catch;
using namespace estimate_method;

TEST_CASE("EstimateMethod - Annual Consumption", "[CompressedAir][EstimateMethod][AnnualConsumption]") {
    // annualConsumption = (leakRateEstimate * operatingTime * 60) / 1000
    CHECK(calculate({1280, 0.1  }).annual_consumption == Approx(7.68));
    CHECK(calculate({1280, 1.429}).annual_consumption == Approx(109.7472));
    CHECK(calculate({8760, 0.5  }).annual_consumption == Approx(262.8));
    CHECK(calculate({4380, 2.0  }).annual_consumption == Approx(525.6));
}
