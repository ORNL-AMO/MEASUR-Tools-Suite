#pragma once

#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/domain/FlashTankFactory.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/domain/ReturnCondensateCalculationsDomain.h>
#include <steamModeler/Header.h>
#include <steamModeler/SteamSystemModelerTool.h>

class ReturnCondensateCalculator {
  public:
    SteamSystemModelerTool::FluidProperties calc(const HeaderWithHighestPressure& highPressureHeaderInput,
                                                 const Header&                    combinedCondensateHeader) const;

    ReturnCondensateCalculationsDomain flash(const HeaderWithHighestPressure&               highPressureHeaderInput,
                                             const SteamSystemModelerTool::FluidProperties& returnCondensate) const;

  private:
    FlashTankFactory       flashTankFactory       = FlashTankFactory();
    FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
};

