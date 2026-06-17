#include "catch.hpp"

#include "compressedAir/pipe_sizing.h"

using namespace Catch;
using namespace pipe_sizing;

TEST_CASE("PipeSizing - Cross-Sectional Area and Diameter", "[CompressedAir][PipeSizing]") {
    CHECK(calculate({1000, 90, 25, 14.5}).cross_sectional_area == Approx(13.3205741627));
    CHECK(calculate({1000, 90, 25, 14.5}).pipe_diameter        == Approx(4.1325124540));

    CHECK(calculate({1400, 90, 25, 14.5}).cross_sectional_area == Approx(18.6488038278));
    CHECK(calculate({1400, 90, 25, 14.5}).pipe_diameter        == Approx(4.8896546766));

    CHECK(calculate({1400, 110, 25, 14.5}).cross_sectional_area == Approx(15.6530120482));
    CHECK(calculate({1400, 110, 25, 14.5}).pipe_diameter        == Approx(4.4797281351));

    CHECK(calculate({1400, 110, 30, 14.5}).cross_sectional_area == Approx(13.0441767068));
    CHECK(calculate({1400, 110, 30, 14.5}).pipe_diameter        == Approx(4.0894135851));

    CHECK(calculate({1400, 110, 30, 11.5}).cross_sectional_area == Approx(10.6008230453));
    CHECK(calculate({1400, 110, 30, 11.5}).pipe_diameter        == Approx(3.6865700558));
}
