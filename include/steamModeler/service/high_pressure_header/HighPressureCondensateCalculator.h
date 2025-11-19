#pragma once

#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/Boiler.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/service/EnergyFlowCalculator.h>
#include <steamModeler/service/MassFlowCalculator.h>
#include <steamModeler/SteamSystemModelerTool.h>

class HighPressureCondensateCalculator {
  public:
    const SteamSystemModelerTool::FluidProperties calc(const HeaderWithHighestPressure& highPressureHeaderInput,
                                                       const Boiler&                    boiler) const;

  private:
    const EnergyFlowCalculator   energyFlowCalculator   = EnergyFlowCalculator();
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const MassFlowCalculator     massFlowCalculator     = MassFlowCalculator();
};

