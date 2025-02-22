#ifndef TOOLS_SUITE_HIGHPRESSUREHEADERMODELER_H
#define TOOLS_SUITE_HIGHPRESSUREHEADERMODELER_H

#include "CondensingTurbineCalculator.h"
#include "HighPressureCondensateCalculator.h"
#include "HighPressureFlashTankCalculator.h"
#include "HighPressureHeaderCalculator.h"
#include "HighToLowSteamTurbineCalculator.h"
#include "HighToMediumSteamTurbineCalculator.h"
#include <steamModeler/Boiler.h>
#include <steamModeler/FlashTank.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/HeatLossFactory.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>

class HighPressureHeaderModeler {
public:
    HighPressureHeaderCalculationsDomain
    model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const PressureTurbine &highToMediumTurbineInput, const PressureTurbine &highToLowTurbineInput,
          const CondensingTurbine &condensingTurbineInput, const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcHighToMediumSteamTurbine(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                 const PressureTurbine &highToMediumTurbineInput,
                                 const PressureTurbine &highToLowTurbineInput,
                                 const CondensingTurbine &condensingTurbineInput, const Boiler &boiler,
                                 const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                 const std::shared_ptr<Turbine> &condensingTurbine,
                                 const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                 const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal) const;

private:
    const CondensingTurbineCalculator condensingTurbineCalculator = CondensingTurbineCalculator();
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeatLossFactory heatLossFactory = HeatLossFactory();
    const HighPressureCondensateCalculator highPressureCondensateCalculator = HighPressureCondensateCalculator();
    const HighPressureFlashTankCalculator highPressureFlashTankCalculator = HighPressureFlashTankCalculator();
    const HighPressureHeaderCalculator highPressureHeaderCalculator = HighPressureHeaderCalculator();
    const HighToLowSteamTurbineCalculator highToLowSteamTurbineCalculator = HighToLowSteamTurbineCalculator();
    const HighToMediumSteamTurbineCalculator highToMediumSteamTurbineCalculator = HighToMediumSteamTurbineCalculator();
};

#endif //TOOLS_SUITE_HIGHPRESSUREHEADERMODELER_H
