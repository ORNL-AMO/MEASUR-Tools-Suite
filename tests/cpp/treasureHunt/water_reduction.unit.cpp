#include "treasureHunt/water_reduction.h"

#include <iostream>

#include "catch.hpp"

using namespace Catch;
using namespace water_reduction;

TEST_CASE("Water Reduction Metered Flow Data", "[WaterReduction][util]") {
    std::vector<WaterReductionInput> waterReductionInputVec = {
        WaterReductionInput{
            8640,
            0.005,
            WaterReductionMeasurementMethod::Metered,
            MeteredFlowMethodData{100},
            VolumeMeterMethodData{5942, 4235, 15},
            BucketMethodData{10, 20},
            WaterOtherMethodData{15000}
        }
    };

    WaterReductionOutput testOutput = waterReduction(waterReductionInputVec);

    CHECK(testOutput.water_use == Approx(51840000.0));
    CHECK(testOutput.water_cost == Approx(259200.0));
}

TEST_CASE("Water Reduction VolumeMeterData", "[WaterReduction][util]") {
    std::vector<WaterReductionInput> waterReductionInputVec = {
        WaterReductionInput{
            8640,
            0.005,
            WaterReductionMeasurementMethod::Volume,
            MeteredFlowMethodData{100},
            VolumeMeterMethodData{5942, 4235, 15},
            BucketMethodData{10, 20},
            WaterOtherMethodData{15000}
        }
    };

    WaterReductionOutput testOutput = waterReduction(waterReductionInputVec);

    CHECK(testOutput.water_use == Approx(58993920.0));
    CHECK(testOutput.water_cost == Approx(294969.6));
}

TEST_CASE("Water Reduction BucketMethodData", "[WaterReduction][util]") {
    std::vector<WaterReductionInput> waterReductionInputVec = {
        WaterReductionInput{
            8640,
            0.005,
            WaterReductionMeasurementMethod::Bucket,
            MeteredFlowMethodData{100},
            VolumeMeterMethodData{5942, 4235, 15},
            BucketMethodData{10, 20},
            WaterOtherMethodData{15000}
        }
    };

    WaterReductionOutput testOutput = waterReduction(waterReductionInputVec);

    CHECK(testOutput.water_use == Approx(15552000.0));
    CHECK(testOutput.water_cost == Approx(77760.0));
}

TEST_CASE("Water Reduction WaterOtherMethodData", "[WaterReduction][util]") {
    std::vector<WaterReductionInput> waterReductionInputVec = {
        WaterReductionInput{
            8640,
            0.005,
            WaterReductionMeasurementMethod::Other,
            MeteredFlowMethodData{100},
            VolumeMeterMethodData{5942, 4235, 15},
            BucketMethodData{10, 20},
            WaterOtherMethodData{15000}
        }
    };

    WaterReductionOutput testOutput = waterReduction(waterReductionInputVec);

    CHECK(testOutput.water_use == Approx(15000.0));
    CHECK(testOutput.water_cost == Approx(75.0));
}