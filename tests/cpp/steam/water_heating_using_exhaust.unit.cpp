#include <steam/water_heating_using_exhaust.h>
#include "catch.hpp"

using namespace Catch;
using namespace water_heating_using_exhaust;
TEST_CASE("Calculate water heating using exhaust results", "[steam]") {
    WaterHeatingUsingExhaustResults results = waterHeatingUsingExhaust(0.69, 6000000, 0.7, 190, 170, 0.73, 0.88, 5);
    CHECK(results.recovered_heat == Approx(1302000));
    CHECK(results.hot_water_flow == Approx(7810.437912));
    CHECK(results.tons_refrigeration == Approx(79.205));
    CHECK(results.capacity_chiller == Approx(69.7004));
    CHECK(results.electrical_energy == Approx(167280.96));
}