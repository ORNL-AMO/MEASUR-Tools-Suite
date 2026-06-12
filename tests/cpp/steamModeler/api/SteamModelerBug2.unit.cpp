#include <steamModeler/api/SteamModeler.h>

#include "catch.hpp"

using namespace Catch;

static const BoilerInput makeBoilerInput() {

    const double fuelType              = 1;
    const double fuel                  = 1;
    const double combustionEfficiency  = 77.62;
    const double blowdownRate          = 5.764;
    const bool   blowdownFlashed       = false;
    const bool   preheatMakeupWater    = false;
    const double steamQuality          = 0;
    const double pressureOrTemperature = 0;
    const double saturatedPressure     = 10;
    const double steamTemperature      = 457.15;
    const double deaeratorVentRate     = 0;
    const double deaeratorPressure     = 0.17132499999999998;
    const double approachTemperature   = 0;
    const double blowdownConductivity  = 4060;
    const double feedwaterConductivity = 234;
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

static const HeaderInput makeHeaderInput() {
    // high pressure header
    const double                     hp_pressure                    = 1.101325;
    const double                     hp_processSteamUsage           = 25000;
    const double                     hp_condensationRecoveryRate    = 50;
    const double                     hp_heatLoss                    = 0.1;
    const double                     hp_condensateReturnTemperature = 353.15;
    const bool                       hp_flashCondensateReturn       = false;
    const HeaderWithHighestPressure& headerWithHighestPressure =
        HeaderWithHighestPressure(hp_pressure, hp_processSteamUsage, hp_condensationRecoveryRate, hp_heatLoss,
                                  hp_condensateReturnTemperature, hp_flashCondensateReturn);

    return {headerWithHighestPressure, nullptr, nullptr};
}

static const OperationsInput makeOperationsInput() {
    const double sitePowerImport        = 0;
    const double makeUpWaterTemperature = 290.5388888888889;
    const double operatingHoursPerYear  = 4464;
    const double fuelCosts              = 0.00000399;
    const double electricityCosts       = 0.0000183333364906032;
    const double makeUpWaterCosts       = 0.0006;

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

static const SteamModelerInput makeSteamModelerInput() {
    const bool             isBaselineCalc      = true;
    const double           baselinePowerDemand = 0;
    const BoilerInput&     boilerInput         = makeBoilerInput();
    const HeaderInput&     headerInput         = makeHeaderInput();
    const OperationsInput& operationsInput     = makeOperationsInput();
    const TurbineInput&    turbineInput        = makeTurbineInput();

    return {isBaselineCalc, baselinePowerDemand, boilerInput, headerInput, operationsInput, turbineInput};
}

TEST_CASE("steamModelerBug2", "[steam modeler bug #2]") {
    auto steamModeler = SteamModeler();

    SteamModelerInput  steamModelerInput = makeSteamModelerInput();
    SteamModelerOutput actual            = steamModeler.model(steamModelerInput);

    // TODO add asserts
}

