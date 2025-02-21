#ifndef TOOLS_SUITE_HIGHTOMEDIUMPRVCALCULATOR_H
#define TOOLS_SUITE_HIGHTOMEDIUMPRVCALCULATOR_H

#include <steamModeler/PRV.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/Boiler.h>
#include "steamModeler/service/PrvCalculator.h"

class HighToMediumPrvCalculator {
public:
    const std::shared_ptr<PrvWithoutDesuperheating>
    calc(const HeaderWithHighestPressure &highPressureHeaderInput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const PressureTurbine &highToLowTurbineInput,
         const PressureTurbine &highToMediumTurbineInput,
         const CondensingTurbine &condensingTurbineInput,
         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
         const std::shared_ptr<Turbine> &condensingTurbine, const Boiler &boiler,
         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;

private:
    const PrvCalculator prvCalculator = PrvCalculator();
};

#endif //TOOLS_SUITE_HIGHTOMEDIUMPRVCALCULATOR_H
