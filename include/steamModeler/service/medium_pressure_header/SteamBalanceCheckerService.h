#ifndef TOOLS_SUITE_STEAMBALANCECHECKERSERVICE_H
#define TOOLS_SUITE_STEAMBALANCECHECKERSERVICE_H

#include <steamModeler/Boiler.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/service/RestarterService.h>
#include <steamModeler/service/SteamReducer.h>

class SteamBalanceCheckerService {
public:
    SteamReducerOutput
    check(const std::string &itemName, const PressureTurbine &highToLowTurbineInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler,
          const std::shared_ptr<Turbine> &highToLowPressureTurbine,
          const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
          const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput, const double neededMassFlow,
          const double availableMassFlow) const;


    SteamReducerOutput
    check(const std::string &itemName, const PressureTurbine &highToLowTurbineInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const Boiler &boiler, const std::shared_ptr<Turbine> &highToLowPressureTurbine,
          const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
          const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
          const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
          const double availableMassFlow) const;

    void check(const std::shared_ptr<Turbine> &turbine, const double availableMassFlow, const Boiler &boiler) const;

private:
    const RestarterService restarter = RestarterService();
    const SteamReducer steamReducer = SteamReducer();
};

#endif //TOOLS_SUITE_STEAMBALANCECHECKERSERVICE_H
