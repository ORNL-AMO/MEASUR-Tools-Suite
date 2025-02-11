#ifndef TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATOR_H
#define TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATOR_H

#include <steamModeler/HeatExchanger.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/HeaderFactory.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>

class MakeupWaterAndCondensateHeaderCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    calc(const BoilerInput &boilerInput, const CondensingTurbine &condensingTurbineInput,
         const SteamSystemModelerTool::FluidProperties &returnCondensate,
         const std::shared_ptr<HeatExchanger::Output> &heatExchangerOutput,
         const SteamSystemModelerTool::FluidProperties &makeupWaterAndMassFlow,
         const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeaderFactory headerFactory = HeaderFactory();

    SteamSystemModelerTool::FluidProperties
    makeHeaderResult(const BoilerInput &boilerInput, const CondensingTurbine &condensingTurbineInput,
                     const SteamSystemModelerTool::FluidProperties &returnCondensate,
                     const std::shared_ptr<HeatExchanger::Output> &heatExchangerOutput,
                     const SteamSystemModelerTool::FluidProperties &makeupWaterAndMassFlow,
                     const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const;

    SteamSystemModelerTool::SteamPropertiesOutput
    calcSteamProperties(const SteamSystemModelerTool::FluidProperties &fluidProperties) const;

    void updateHeaderWithSteam(SteamSystemModelerTool::FluidProperties &headerResult,
                               const SteamSystemModelerTool::SteamPropertiesOutput &steamPropertiesOutput) const;
};

#endif //TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATOR_H
