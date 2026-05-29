#include "motorDriven/fans/fan_affinity_laws.h"

#include "catch.hpp"

using namespace Catch;

auto validateFALOutput = [](const FanAffinityLaws::Output& results,
                             const FanAffinityLaws::Output& expected) {
    CHECK(Approx(results.annualEnergyBaseline) == expected.annualEnergyBaseline);
    CHECK(Approx(results.annualEnergyNew) == expected.annualEnergyNew);
    CHECK(Approx(results.annualCostSavings) == expected.annualCostSavings);
};

TEST_CASE("Compute annual energy and cost savings", "[fanAffinityLaws]") {
    INFO("Test Case #1 for VSD: ");
    validateFALOutput(FanAffinityLaws(0.07, 95, 93, 0,
        6240, 2, 8000,
        FanAffinityLaws::OnOff, FanAffinityLaws::VSD,
        FanAffinityLaws::Volume, 5000).calculate(),
        FanAffinityLaws::Output(14125.64, 3448.64, 747.39));

    INFO("Test Case #2 for Two-Speed: ");
    validateFALOutput(FanAffinityLaws(0.07, 97, 96, 100,
        6240, 10, 30000,
        FanAffinityLaws::OnOff, FanAffinityLaws::TwoSpeed,
        FanAffinityLaws::Percent, 55).calculate(),
        FanAffinityLaws::Output(67010.3, 14239.7, 3693.94));

    INFO("Test Case #3 for Change Fan Size: ");
    validateFALOutput(FanAffinityLaws(0.05, 90, 92, 100,
        8760, 5, 15000,
        FanAffinityLaws::OnOff, FanAffinityLaws::None,
        FanAffinityLaws::Volume, 0).changeFanSize(20, 18),
        FanAffinityLaws::Output(52898.55, 31236.06, 1083.12));

    INFO("Test Case #4 for VSD + Change Fan Size: ");
    validateFALOutput(FanAffinityLaws(0.08, 96, 97, 91,
        4380, 20, 60000,
        FanAffinityLaws::OnOff, FanAffinityLaws::VSD,
        FanAffinityLaws::Percent, 75).changeFanSize(36, 40),
        FanAffinityLaws::Output(94072.16, 26038.44, 5442.7));

    INFO("Test Case #5 for Two-Speed + Change Fan Size: ");
    validateFALOutput(FanAffinityLaws(0.08, 96, 97, 0,
        4380, 20, 60000,
        FanAffinityLaws::OnOff, FanAffinityLaws::TwoSpeed,
        FanAffinityLaws::Volume, 40000).changeFanSize(36, 38),
        FanAffinityLaws::Output(94072.16, 51363.6, 3416.69));

    INFO("Test Case #6 for VSD: ");
    validateFALOutput(FanAffinityLaws(0.07, 95, 93, 88,
        6240, 2, 8000,
        FanAffinityLaws::VSD, FanAffinityLaws::VSD,
        FanAffinityLaws::Volume, 5000).calculate(),
        FanAffinityLaws::Output(9626.23, 3448.64, 432.431));

    INFO("Test Case #7 for Two-Speed: ");
    validateFALOutput(FanAffinityLaws(0.07, 97, 96, 90,
        6240, 10, 30000,
        FanAffinityLaws::TwoSpeed, FanAffinityLaws::TwoSpeed,
        FanAffinityLaws::Percent, 55).calculate(),
        FanAffinityLaws::Output(55283.5, 14239.7, 2873.07));

    INFO("Test Case #8 for VSD: ");
    validateFALOutput(FanAffinityLaws(0.07, 95, 93, 100,
        8760, 25, 80000,
        FanAffinityLaws::OnOff, FanAffinityLaws::VSD,
        FanAffinityLaws::Percent, 75).calculate(),
        FanAffinityLaws::Output(247877.76, 104573.43, 10031.3));

    INFO("Test Case #9 for Two-Speed: ");
    validateFALOutput(FanAffinityLaws(0.07, 95, 93, 100,
        8760, 25, 80000,
        FanAffinityLaws::OnOff, FanAffinityLaws::TwoSpeed,
        FanAffinityLaws::Percent, 75).calculate(),
        FanAffinityLaws::Output(247877.76, 139431.24, 7591.26));

    INFO("Test Case# 10 for Change Fan Size: ");
    validateFALOutput(FanAffinityLaws(0.07, 95, 93, 100,
        8760, 25, 80000,
        FanAffinityLaws::OnOff, FanAffinityLaws::None,
        FanAffinityLaws::Percent, 75).changeFanSize(36, 32.75),
        FanAffinityLaws::Output(247877.76, 154447.75, 6540.1));

    INFO("Test Case # 11 for VSD + Change Fan Size: ");
    validateFALOutput(FanAffinityLaws(0.07, 95, 93, 100,
        8760, 25, 80000,
        FanAffinityLaws::OnOff, FanAffinityLaws::VSD,
        FanAffinityLaws::Percent, 75).changeFanSize(36, 40),
        FanAffinityLaws::Output(247877.76, 68610.63, 12548.7));

    INFO("Test Case # 12 for Two-Speed + Change Fan Size: ");
    validateFALOutput(FanAffinityLaws(0.07, 95, 93, 100,
        8760, 25, 80000,
        FanAffinityLaws::OnOff, FanAffinityLaws::TwoSpeed,
        FanAffinityLaws::Percent, 75).changeFanSize(36, 40),
        FanAffinityLaws::Output(247877.76, 236128.03, 822.481));

    INFO("Test Case # 13 for Two-Speed + Change Fan Size with input object: ");
    constexpr auto input = FanAffinityLaws::Input(0.07, 95, 93, 100,
        8760, 25, 80000,
        FanAffinityLaws::OnOff, FanAffinityLaws::TwoSpeed,
        FanAffinityLaws::Percent, 75);
    validateFALOutput(FanAffinityLaws(input).changeFanSize(36, 40),
        FanAffinityLaws::Output(247877.76, 236128.03, 822.481));
}