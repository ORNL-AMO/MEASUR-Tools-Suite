#include "catch.hpp"

#include "compressedAir/operating_cost.h"

using namespace Catch;
using namespace operating_cost;

TEST_CASE("OperatingCost - Run Time Unloaded", "[CompressedAir][OperatingCost]") {
    CHECK(calculateOperatingCost({215, 25, 6800, 85, 95, 90, 0.05}).run_time_unloaded == Approx(15.0));
    CHECK(calculateOperatingCost({255, 35, 6000, 89, 93, 90, 0.09}).run_time_unloaded == Approx(11.0));
}

TEST_CASE("OperatingCost - Loaded Cost", "[CompressedAir][OperatingCost]") {
    CHECK(calculateOperatingCost({215, 25, 6800, 85, 95, 90, 0.05}).cost_for_loaded == Approx(48792.3263157895));
    CHECK(calculateOperatingCost({255, 25, 6800, 85, 95, 90, 0.05}).cost_for_loaded == Approx(57869.9684210526));
    CHECK(calculateOperatingCost({255, 35, 6800, 85, 95, 90, 0.05}).cost_for_loaded == Approx(57869.9684210526));
    CHECK(calculateOperatingCost({255, 35, 6000, 85, 95, 90, 0.05}).cost_for_loaded == Approx(51061.7368421053));
    CHECK(calculateOperatingCost({255, 35, 6000, 89, 93, 90, 0.05}).cost_for_loaded == Approx(54614.419354838));
    CHECK(calculateOperatingCost({255, 35, 6000, 89, 93, 90, 0.09}).cost_for_loaded == Approx(98305.9548387097));
}

TEST_CASE("OperatingCost - Unloaded Cost", "[CompressedAir][OperatingCost]") {
    CHECK(calculateOperatingCost({215, 25, 6800, 85, 95, 90, 0.05}).cost_for_unloaded == Approx(2272.1916666667));
    CHECK(calculateOperatingCost({255, 25, 6800, 85, 95, 90, 0.05}).cost_for_unloaded == Approx(2694.925));
    CHECK(calculateOperatingCost({255, 35, 6800, 85, 95, 90, 0.05}).cost_for_unloaded == Approx(3772.895));
    CHECK(calculateOperatingCost({255, 35, 6000, 85, 95, 90, 0.05}).cost_for_unloaded == Approx(3329.025));
    CHECK(calculateOperatingCost({255, 35, 6000, 89, 93, 90, 0.05}).cost_for_unloaded == Approx(2441.285));
    CHECK(calculateOperatingCost({255, 35, 6000, 89, 93, 90, 0.09}).cost_for_unloaded == Approx(4394.313));
}

TEST_CASE("OperatingCost - Total Annual Cost", "[CompressedAir][OperatingCost]") {
    CHECK(calculateOperatingCost({215, 25, 6800, 85, 95, 90, 0.05}).total_annual_cost == Approx(51064.5179824561));
    CHECK(calculateOperatingCost({255, 25, 6800, 85, 95, 90, 0.05}).total_annual_cost == Approx(60564.893421));
    CHECK(calculateOperatingCost({255, 35, 6800, 85, 95, 90, 0.05}).total_annual_cost == Approx(61642.8634210526));
    CHECK(calculateOperatingCost({255, 35, 6000, 85, 95, 90, 0.05}).total_annual_cost == Approx(54390.7618421053));
    CHECK(calculateOperatingCost({255, 35, 6000, 89, 93, 90, 0.05}).total_annual_cost == Approx(57055.704354838));
    CHECK(calculateOperatingCost({255, 35, 6000, 89, 93, 90, 0.09}).total_annual_cost == Approx(102700.2678387097));
}
