#ifndef TOOLS_SUITE_LOWPRESSUREHEADERMODELER_H
#define TOOLS_SUITE_LOWPRESSUREHEADERMODELER_H

#include "LowPressureCondensateCalculator.h"
#include "LowPressureFlashedSteamIntoHeaderCalculator.h"
#include "LowPressureHeaderCalculator.h"
#include "LowPressurePrvCalculator.h"
#include <steamModeler/Boiler.h>
#include <steamModeler/FlashTank.h>
#include <steamModeler/Header.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/FlashTankFactory.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/domain/HeaderFactory.h>
#include <steamModeler/domain/HeatLossFactory.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/LowPressureFlashedSteamIntoHeaderCalculatorDomain.h>
#include <steamModeler/domain/LowPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/MediumPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/PrvWithDesuperheatingFactory.h>
#include <steamModeler/domain/PrvWithoutDesuperheatingFactory.h>

class LowPressureHeaderModeler {
public:
    std::shared_ptr<LowPressureHeaderCalculationsDomain>
    model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const PressureTurbine &highToLowTurbineInput, const PressureTurbine &mediumToLowTurbineInput,
          const CondensingTurbine &condensingTurbineInput, const BoilerInput &boilerInput, const Boiler &boiler,
          const std::shared_ptr<FlashTank> &blowdownFlashTank,
          const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
          const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const;

private:
    const FlashTankFactory flashTankFactory = FlashTankFactory();
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeatLossFactory heatLossFactory = HeatLossFactory();
    const LowPressureCondensateCalculator lowPressureCondensateCalculator = LowPressureCondensateCalculator();
    const LowPressureHeaderCalculator lowPressureHeaderCalculator = LowPressureHeaderCalculator();
    const LowPressurePrvCalculator lowPressurePrvCalculator = LowPressurePrvCalculator();
    const LowPressureFlashedSteamIntoHeaderCalculator lowPressureFlashedSteamIntoHeaderCalculator = LowPressureFlashedSteamIntoHeaderCalculator();
};

#endif //TOOLS_SUITE_LOWPRESSUREHEADERMODELER_H
