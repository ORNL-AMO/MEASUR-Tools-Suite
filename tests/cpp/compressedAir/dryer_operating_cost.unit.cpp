#include "compressedAir/dryer_operating_cost.h"

#include "catch.hpp"

using namespace Catch;

auto validateDryerOutput = [](const DryerOperatingCost::Output& results,
                             const DryerOperatingCost::Output& expected) {
    CHECK(Approx(results.waterRemoved) == expected.waterRemoved);
    CHECK(Approx(results.totalCostPerYear) == expected.totalCostPerYear);
};

TEST_CASE("Compute operating cost of a desiccant dryer:", "[dryerOperatingCost]") {
    INFO("Compute operating cost of a desiccant dryer: ");
    const auto doc = DryerOperatingCost(1752, 50, 100,
        24, 7, 52,
        0.08, 0.2, 0.25);

    validateDryerOutput(doc.calculate(DryerOperatingCost::Heatless),
        {73.34, 60020.86, 0, 0, 15, 16.33});

    validateDryerOutput(doc.calculate(DryerOperatingCost::HeatedExternally),
        {73.34, 38193.08, 19.36, 18, 7, 16.33});

    validateDryerOutput(doc.calculate(DryerOperatingCost::BlowerPurgeWithSweep),
        {73.34, 51442.40, 69.14, 18, 7, 16.33});

    validateDryerOutput(doc.calculate(DryerOperatingCost::BlowerPurgeWithoutSweep),
        {73.34, 47161.58, 69.14, 18, 7, 16.33});

    validateDryerOutput(doc.calculate(DryerOperatingCost::HeatOfCompressionHC),
        {73.34, 3333.81, 3.05, 3, 2, 16.33});

    validateDryerOutput(doc.calculate(DryerOperatingCost::HeatOfCompressionSP),
        {73.34, 69.888, 0, 0, 0, 16.33});

    validateDryerOutput(doc.calculate(DryerOperatingCost::Refrigerated),
        {63.944, 8639.09, 0, 0, 0, 0});


    auto docNonDefault = DryerOperatingCost(1752, 50, 100,
        24, 7, 52,
        0.08, 0.2, 0.25,
        3.05, 3, 2, 16.33);
    validateDryerOutput(docNonDefault.calculate(DryerOperatingCost::HeatOfCompressionHC),
        {73.34, 3333.81, 3.05, 3, 2, 16.33});
}
