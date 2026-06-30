#include "steam/steam_leak_survey.h"

#include "catch.hpp"

using namespace Catch;

auto validateSteamLeaks = [](SteamLeakSurvey::SteamLeakSurveyResults const& results,
                             const SteamLeakSurvey::SteamLeakSurveyResults& expected) {
    CHECK(Approx(results.leakRate) == expected.leakRate);
    CHECK(Approx(results.steamLoss) == expected.steamLoss);
    CHECK(Approx(results.energyLoss) == expected.energyLoss);
    CHECK(Approx(results.leakCost) == expected.leakCost);
    CHECK(Approx(results.steamUnitCost) == expected.steamUnitCost);
    CHECK(Approx(results.steamSpecificEnthalpy) == expected.steamSpecificEnthalpy);
    CHECK(Approx(results.isentropicEnthalpy) == expected.isentropicEnthalpy);
};

TEST_CASE("Steam Leak of a boiler system:", "[steamLeakSurvey]") {
    INFO("Estimate Steam Leak from Plume Length: ");
    CHECK(QuantifySteamLeakByPlumeLength::estimate(300, 8, 80) == Approx(447.426));

    const auto steamLeakElectric = SteamLeakSurvey(8760, 500, 300, 0.1, 200, 400, 70, 80, 75);
    INFO("Cost of Steam (Electricity): ");
    CHECK(Approx(steamLeakElectric.costOfSteam()) == 0.059492);
    CHECK(Approx(steamLeakElectric.costOfSteam(90)) == 0.058548);

    const auto steamLeakNaturalGas = SteamLeakSurvey(8760, 500, 300, 0.1, 200, 400, 70, 80, 75, SteamLeakSurvey::UtilityType::natural_gas, 15.50, 1.038, 0);
    INFO("Cost of Steam (Natural Gas): ");
    CHECK(Approx(steamLeakNaturalGas.costOfSteam()) == 0.03266);

    const auto steamLeak = SteamLeakSurvey(8760, 500, 300, 0.1, 200, 400, 70, 80, 75, 15.50, 1.038);
    const auto steamUnitCost = steamLeak.costOfSteam();
    const auto prvResult = steamLeak.estimateMethodPRVCalc(500);
    const auto steamSpecificEnthalpy = prvResult.steamSpecificEnthalpy;
    const auto isentropicEnthalpy = prvResult.isentropicEnthalpy;

    INFO("Estimate Method (PRV): ");
    validateSteamLeaks(prvResult,
             {500, 4380, 5291.35, 137405.72, steamUnitCost, steamSpecificEnthalpy, isentropicEnthalpy});
    INFO("Passed");

    INFO("Estimate Method (Backpressure Turbine): ");
    validateSteamLeaks(steamLeak.estimateMethodTurbineCalc(90, 500),
             {500, 4380, 5291.35, 133436.27, steamUnitCost, steamSpecificEnthalpy, isentropicEnthalpy});
    INFO("Passed");

    INFO("Orifice Method: ");
    validateSteamLeaks(steamLeak.orificeMethodCalc(90, 0.25, 0.8748, 14.70),
             {482.71, 4228.58, 5108.42, 128823.25, steamUnitCost, steamSpecificEnthalpy, isentropicEnthalpy});
    INFO("Passed");

    INFO("Plume Method: ");
    validateSteamLeaks(steamLeak.plumeMethodCalc(90, 8, 80),
             {447.426, 3919.45, 4734.97, 119405.69, steamUnitCost, steamSpecificEnthalpy, isentropicEnthalpy});
    INFO("Passed");
}
