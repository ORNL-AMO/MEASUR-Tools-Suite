#pragma once

#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/PRV.h>

class PrvWithoutDesuperheatingFactory {
  public:
    PrvWithoutDesuperheating make(const SteamSystemModelerTool::FluidProperties& remainingSteam, const double massFlow,
                                  const std::shared_ptr<HeaderNotHighestPressure>& headerNotHighestPressure) const;
};

