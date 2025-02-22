#ifndef TOOLS_SUITE_FLUIDPROPERTIESFACTORY_H
#define TOOLS_SUITE_FLUIDPROPERTIESFACTORY_H

#include <steamModeler/Boiler.h>
#include <steamModeler/Header.h>
#include <steamModeler/HeatLoss.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/service/EnergyFlowCalculator.h>
#include <steamModeler/service/MassFlowCalculator.h>

class FluidPropertiesFactory {
public:
    SteamSystemModelerTool::FluidProperties make(const Header &header) const;

    SteamSystemModelerTool::FluidProperties make(const SteamSystemModelerTool::FluidProperties &properties) const;

    SteamSystemModelerTool::FluidProperties make(const HeatLoss &heatLoss) const;

    SteamSystemModelerTool::FluidProperties
    makeWithSpecificVolume(const HeatLoss &heatLoss, const double specificVolume) const;

    SteamSystemModelerTool::FluidProperties
    makeWithMassFlow(const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput,
                     const double massFlow) const;

    SteamSystemModelerTool::FluidProperties
    makeWithVentedSteamAmount(const SteamSystemModelerTool::FluidProperties &makeupWater,
                              const double ventedSteamAmount) const;

    SteamSystemModelerTool::FluidProperties makeFromBlowdown(const Boiler &boiler) const;

    SteamSystemModelerTool::FluidProperties
    makeFromBlowdown(const Boiler &boiler, const double massFlow, const double energyFlow) const;

    SteamSystemModelerTool::FluidProperties
    make(const std::shared_ptr<HeaderNotHighestPressure> &notHighestPressureHeaderInput) const;

    SteamSystemModelerTool::FluidProperties
    make(const HeaderWithHighestPressure &highPressureHeaderInput, const Header &combinedCondensateHeader) const;

private:
    EnergyFlowCalculator energyFlowCalculator = EnergyFlowCalculator();
    MassFlowCalculator massFlowCalculator = MassFlowCalculator();

    SteamSystemModelerTool::SteamPropertiesOutput
    calcLowPressureCondensateSteamOutput(
            const std::shared_ptr<HeaderNotHighestPressure> &notHighestPressureHeaderInput) const;
};

#endif //TOOLS_SUITE_FLUIDPROPERTIESFACTORY_H
