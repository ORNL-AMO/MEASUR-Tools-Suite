#ifndef TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATOR_H
#define TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATOR_H

#include <memory>
#include <steamModeler/Boiler.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/HighToMediumSteamTurbineCalculationsDomain.h>
#include <steamModeler/domain/TurbineFactory.h>
#include <steamModeler/service/RestarterService.h>
#include <steamModeler/service/SteamBalanceException.h>
#include <steamModeler/service/SteamReducer.h>
#include <steamModeler/service/medium_pressure_header/SteamBalanceCheckerService.h>

class HighToMediumSteamTurbineCalculator {
public:
    HighToMediumSteamTurbineCalculationsDomain
    calc(const int headerCountInput, const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const HeaderWithHighestPressure &highPressureHeaderInput, const CondensingTurbine &condensingTurbineInput,
         const std::shared_ptr<Turbine> &condensingTurbine, const PressureTurbine &highToLowTurbineInput,
         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal, const PressureTurbine &highToMediumTurbineInput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler) const;

private:
    TurbineFactory turbineFactory = TurbineFactory();
    SteamBalanceCheckerService steamBalanceCheckerService = SteamBalanceCheckerService();

    HighToMediumSteamTurbineCalculationsDomain
    calc(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal, const PressureTurbine &highToMediumTurbineInput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcFlowRange(const double availableMassFlow,
                  const PressureTurbine &highToLowTurbineInput,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                  const PressureTurbine &highToMediumTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                  const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcPowerRange(const double availableMassFlow,
                   const PressureTurbine &highToLowTurbineInput,
                   const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                   const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                   const PressureTurbine &highToMediumTurbineInput,
                   const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                   const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                   const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                   const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcPowerGeneration(const double availableMassFlow,
                        const PressureTurbine &highToLowTurbineInput,
                        const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                        const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                        const PressureTurbine &highToMediumTurbineInput,
                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                        const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                        const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcSteamFlow(const double availableMassFlow,
                  const PressureTurbine &highToLowTurbineInput,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                  const PressureTurbine &highToMediumTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                  const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcBalanceHeader(const double availableMassFlow,
                      const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                      const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                      const PressureTurbine &highToMediumTurbineInput,
                      const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                      const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const;

    double calcAvailableMassFlow(const HeaderWithHighestPressure &highPressureHeaderInput,
                                 const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                 const CondensingTurbine &condensingTurbineInput,
                                 const std::shared_ptr<Turbine> &condensingTurbine,
                                 const PressureTurbine &highToLowTurbineInput,
                                 const std::shared_ptr<Turbine> &highToLowPressureTurbine) const;
};

#endif //TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATOR_H
