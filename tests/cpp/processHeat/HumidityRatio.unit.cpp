#include "catch.hpp"
#include "processHeat/HumidityRatio.h"

TEST_CASE( "Calculate the Humidity Ratio Using Relative Humidity", "[Humidity Ratio][HumidityRatio][Calculator]") {
    CHECK( HumidityRatio(0.8, 120, 30, 85).getHumidityRatioUsingRH() == Approx(0.028113629));
}

TEST_CASE( "Calculate the Humidity Ratio Using RWet Bulb Temperature", "[Humidity Ratio][HumidityRatio][Calculator]") {
CHECK( HumidityRatio(0.8, 120, 30, 85).getHumidityRatioUsingWBT() == Approx(0.0245794342));
}