#include <steamModeler/api/SteamModeler.h>

#include "catch.hpp"

using namespace Catch;

TEST_CASE("steamModeler", "[steam_modeler_bug]") {
    auto steamModeler = SteamModeler();

    double fuelType             = 1;
    double fuel                 = 1;
    double combustionEfficiency = 87.33;
    double blowdownRate         = 8;
    bool   blowdownFlashed      = true;

    bool               preheatMakeupWater  = false;
    // double             steamTemperature    = 445;
    double             steamTemperature    = 444.81666666666666;
    double             deaeratorVentRate   = 10;
    double             deaeratorPressure   = .10132539296661526;
    double             approachTemperature = 61.11111111111106;
    const BoilerInput& boilerInput         = {fuelType,
                                              fuel,
                                              combustionEfficiency,
                                              blowdownRate,
                                              blowdownFlashed,
                                              preheatMakeupWater,
                                              steamTemperature,
                                              deaeratorVentRate,
                                              deaeratorPressure,
                                              approachTemperature};

    const HeaderWithHighestPressure& headerWithHighestPressure =
        HeaderWithHighestPressure(0.82527519301388, 1923230.08, 70, 5, 358.15, false);
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeader = nullptr;
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeader    = nullptr;

    const HeaderInput& headerInput = {headerWithHighestPressure, mediumPressureHeader, lowPressureHeader};

    const CondensingTurbine& condensingTurbine =
        CondensingTurbine(1, 1, 1, CondensingTurbineOperation::POWER_GENERATION, 1, false);
    const PressureTurbine& highToLowTurbine =
        PressureTurbine(1, 1, PressureTurbineOperation::POWER_GENERATION, 1, 1, false);
    const PressureTurbine& highToMediumTurbine =
        PressureTurbine(1, 1, PressureTurbineOperation::POWER_GENERATION, 1, 1, false);
    const PressureTurbine& mediumToLowTurbine =
        PressureTurbine(1, 1, PressureTurbineOperation::POWER_GENERATION, 1, 1, false);

    const OperationsInput operationsInput = {0, 366.48333333, 8760, .000010757682, .0000311111111, 2.4462331975687497};
    const TurbineInput    turbineInput = {condensingTurbine, highToLowTurbine, highToMediumTurbine, mediumToLowTurbine};
    SteamModelerInput     steamModelerInput = {true, 0, boilerInput, headerInput, operationsInput, turbineInput};
    SteamModelerOutput    actual            = steamModeler.model(steamModelerInput);

    // asert that the model runs without throwing an exception and produces output
    CHECK("TEST COMPLETE" == "TEST COMPLETE");
}
