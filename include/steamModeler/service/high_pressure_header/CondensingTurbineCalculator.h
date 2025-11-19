#pragma once

#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/TurbineFactory.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>

class CondensingTurbineCalculator {
  public:
    const std::shared_ptr<Turbine> calc(const CondensingTurbine&                       condensingTurbineInput,
                                        const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
                                        const bool                                     isCalcIdeal) const;

  private:
    TurbineFactory turbineFactory = TurbineFactory();

    const std::shared_ptr<Turbine> make(const CondensingTurbine&                       condensingTurbineInput,
                                        const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
                                        const bool                                     isCalcIdeal) const;
};

