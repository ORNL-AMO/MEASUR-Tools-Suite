#pragma once

#include <steamModeler/Boiler.h>
#include <steamModeler/SteamSystemModelerTool.h>

class EnergyFlowCalculator {
  public:
    double calc(const double massFlow, const Boiler& boiler) const;

    double calc(const double                                         massFlow,
                const SteamSystemModelerTool::SteamPropertiesOutput& steamPropertiesOutput) const;

    double calc(const double massFlow, const double specificEnthalpy) const;
};

