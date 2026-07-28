#include <steamModeler/api/SteamModeler.h>

#include "catch.hpp"

//FROM ISSUE 364
// This test is to be used to investigate a bug in the steam modeler where the specific enthalpy of a header with 0 mass flow

using namespace Catch;

static const BoilerInput makeBoilerInput() {

    const double fuelType              = 1;
    const double fuel                  = 1;
    const double combustionEfficiency  = 85.1;
    const double blowdownRate          = 7.631;
    const bool   blowdownFlashed       = false;
    const bool   preheatMakeupWater    = false;
    const double steamTemperature      = 451.2055555555555;
    const double deaeratorVentRate     = 0;
    const double deaeratorPressure     = 0.17027299297111664;
    const double approachTemperature   = 0;
    return {fuelType,
            fuel,
            combustionEfficiency,
            blowdownRate,
            blowdownFlashed,
            preheatMakeupWater,
            steamTemperature,
            deaeratorVentRate,
            deaeratorPressure,
            approachTemperature};
}

static const HeaderInput makeHeaderInput(int headerCount) {
    // high pressure header
    const double                     hp_pressure                    = 0.9562756330224326;
    const double                     hp_processSteamUsage           = 5443.104;
    const double                     hp_condensationRecoveryRate    = 45;
    const double                     hp_heatLoss                    = 0;
    const double                     hp_condensateReturnTemperature = 355.3722222222222;
    const bool                       hp_flashCondensateReturn       = false;
    const HeaderWithHighestPressure& headerWithHighestPressure =
        HeaderWithHighestPressure(hp_pressure, hp_processSteamUsage, hp_condensationRecoveryRate, hp_heatLoss,
                                  hp_condensateReturnTemperature, hp_flashCondensateReturn);

    // medium pressure header
    const double                                     mp_pressure                        = 0.20474679297336734;
    const double                                     mp_processSteamUsage               = 5443.104;
    const double                                     mp_condensationRecoveryRate        = 0;
    const double                                     mp_heatLoss                        = 0;
    const bool                                       mp_flashCondensateIntoHeader       = false;
    const bool                                       mp_desuperheatSteamIntoNextHighest = false;
    const double                                     mp_desuperheatSteamTemperature     = 255.3722222222222;
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeader = std::make_shared<HeaderNotHighestPressure>(
        mp_pressure, mp_processSteamUsage, mp_condensationRecoveryRate, mp_heatLoss, mp_flashCondensateIntoHeader,
        mp_desuperheatSteamIntoNextHighest, mp_desuperheatSteamTemperature);

    // low pressure header
    const double                                     lp_pressure                        = 0.17096246897116166;
    const double                                     lp_processSteamUsage               = 0;
    const double                                     lp_condensationRecoveryRate        = 0;
    const double                                     lp_heatLoss                        = 0;
    const bool                                       lp_flashCondensateIntoHeader       = false;
    const bool                                       lp_desuperheatSteamIntoNextHighest = false;
    const double                                     lp_desuperheatSteamTemperature     = 255.3722222222222;
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeader = std::make_shared<HeaderNotHighestPressure>(
        lp_pressure, lp_processSteamUsage, lp_condensationRecoveryRate, lp_heatLoss, lp_flashCondensateIntoHeader,
        lp_desuperheatSteamIntoNextHighest, lp_desuperheatSteamTemperature);
    if (headerCount == 2) {
        return {headerWithHighestPressure, nullptr, mediumPressureHeader};
    }
    else {
        return {headerWithHighestPressure, mediumPressureHeader, lowPressureHeader};
    }
}

static const OperationsInput makeOperationsInput() {
    const double sitePowerImport        = 0;
    const double makeUpWaterTemperature = 290.5388888888889;
    const double operatingHoursPerYear  = 8760;
    const double fuelCosts              = 0.000007240346520577029;
    const double electricityCosts       = 0.000036111117329975996;
    const double makeUpWaterCosts       = 1.8993970507343751;

    return {sitePowerImport, makeUpWaterTemperature, operatingHoursPerYear,
            fuelCosts,       electricityCosts,       makeUpWaterCosts};
}

static const TurbineInput makeTurbineInput() {
    const CondensingTurbine& condensingTurbine =
        CondensingTurbine(1, 1, 1, CondensingTurbineOperation::POWER_GENERATION, 1, false);
    const PressureTurbine& highToLowTurbine =
        PressureTurbine(1, 1, PressureTurbineOperation::POWER_GENERATION, 1, 1, false);
    const PressureTurbine& highToMediumTurbine =
        PressureTurbine(1, 1, PressureTurbineOperation::POWER_GENERATION, 1, 1, false);
    const PressureTurbine& mediumToLowTurbine =
        PressureTurbine(1, 1, PressureTurbineOperation::POWER_GENERATION, 1, 1, false);

    return {condensingTurbine, highToLowTurbine, highToMediumTurbine, mediumToLowTurbine};
}

static const SteamModelerInput makeSteamModelerInput(int headerCount) {
    const bool             isBaselineCalc      = true;
    const double           baselinePowerDemand = 0;
    const BoilerInput&     boilerInput         = makeBoilerInput();
    const HeaderInput&     headerInput         = makeHeaderInput(headerCount);
    const OperationsInput& operationsInput     = makeOperationsInput();
    const TurbineInput&    turbineInput        = makeTurbineInput();

    return {isBaselineCalc, baselinePowerDemand, boilerInput, headerInput, operationsInput, turbineInput};
}

TEST_CASE("steamModelerBug", "[steam modeler bug 3 header]") {
    auto steamModeler = SteamModeler();

    SteamModelerInput  steamModelerInput = makeSteamModelerInput(3);
    SteamModelerOutput actual            = steamModeler.model(steamModelerInput);

    // TODO add asserts
}

TEST_CASE("steamModelerBug", "[steam modeler bug 2 header]") {
    auto steamModeler = SteamModeler();

    SteamModelerInput  steamModelerInput = makeSteamModelerInput(2);
    SteamModelerOutput actual            = steamModeler.model(steamModelerInput);

    // TODO add asserts
}