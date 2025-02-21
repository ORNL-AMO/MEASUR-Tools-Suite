#ifndef TOOLS_SUITE_PRVWITHOUTDESUPERHEATINGFACTORY_H
#define TOOLS_SUITE_PRVWITHOUTDESUPERHEATINGFACTORY_H

#include <steamModeler/PRV.h>
#include <steamModeler/api/HeaderInput.h>

class PrvWithoutDesuperheatingFactory {
public:
    PrvWithoutDesuperheating
    make(const SteamSystemModelerTool::FluidProperties &remainingSteam, const double massFlow,
         const std::shared_ptr<HeaderNotHighestPressure> &headerNotHighestPressure) const;
};

#endif //TOOLS_SUITE_PRVWITHOUTDESUPERHEATINGFACTORY_H
