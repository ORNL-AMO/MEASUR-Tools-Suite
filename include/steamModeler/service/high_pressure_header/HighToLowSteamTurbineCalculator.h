#ifndef TOOLS_SUITE_HIGHTOLOWSTEAMTURBINECALCULATOR_H
#define TOOLS_SUITE_HIGHTOLOWSTEAMTURBINECALCULATOR_H

#include <steamModeler/Boiler.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/TurbineFactory.h>
#include <steamModeler/service/RestarterService.h>
#include <steamModeler/service/SteamBalanceException.h>
#include <steamModeler/service/medium_pressure_header/SteamBalanceCheckerService.h>

class HighToLowSteamTurbineCalculator {
public:
    std::shared_ptr<Turbine> calc(const int headerCountInput, const PressureTurbine &highToLowTurbineInput,
                                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                  const HeaderWithHighestPressure &highPressureHeaderInput,
                                  const CondensingTurbine &condensingTurbineInput,
                                  const std::shared_ptr<Turbine> &condensingTurbine,
                                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                  const Boiler &boiler, const bool isCalcIdeal) const;

private:
    RestarterService restarter = RestarterService();
    SteamBalanceCheckerService steamBalanceCheckerService = SteamBalanceCheckerService();
    TurbineFactory turbineFactory = TurbineFactory();

    std::shared_ptr<Turbine>
    calcHighToLowPressureTurbine(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                                 const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                 const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                 const Boiler &boiler, const bool isCalcIdeal) const;

    std::shared_ptr<Turbine>
    calcFlowRange(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                  const Boiler &boiler, const bool isCalcIdeal) const;

    std::shared_ptr<Turbine>
    calcPowerRange(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                   const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                   const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                   const Boiler &boiler, const bool isCalcIdeal) const;

    std::shared_ptr<Turbine>
    calcPowerGeneration(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                        const Boiler &boiler, const bool isCalcIdeal) const;

    std::shared_ptr<Turbine>
    calcSteamFlow(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                  const Boiler &boiler, const bool isCalcIdeal) const;

    std::shared_ptr<Turbine>
    calcBalanceHeader(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                      const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                      const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                      const bool isCalcIdeal) const;

    double calcAvailableMassFlow(const HeaderWithHighestPressure &highPressureHeaderInput,
                                 const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                 const CondensingTurbine &condensingTurbineInput,
                                 const std::shared_ptr<Turbine> &condensingTurbine) const;
};

#endif //TOOLS_SUITE_HIGHTOLOWSTEAMTURBINECALCULATOR_H
