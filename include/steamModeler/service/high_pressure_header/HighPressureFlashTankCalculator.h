#pragma once

#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/domain/FlashTankFactory.h>
#include <steamModeler/FlashTank.h>
#include <steamModeler/SteamSystemModelerTool.h>

class HighPressureFlashTankCalculator {
  public:
    const std::shared_ptr<FlashTank> calc(const int                                        headerCountInput,
                                          const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
                                          const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                          const SteamSystemModelerTool::FluidProperties& highPressureCondensate) const;

  private:
    const FlashTankFactory flashTankFactory = FlashTankFactory();
};

