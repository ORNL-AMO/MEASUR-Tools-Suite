#ifndef TOOLS_SUITE_PRVWITHDESUPERHEATINGFACTORY_H
#define TOOLS_SUITE_PRVWITHDESUPERHEATINGFACTORY_H

#include <steamModeler/PRV.h>
#include <steamModeler/SteamProperties.h>
#include <steamModeler/api/HeaderInput.h>

class PrvWithDesuperheatingFactory {
public:
    PrvWithDesuperheating make(const SteamSystemModelerTool::FluidProperties &remainingSteam, const double massFlow,
                               const std::shared_ptr<HeaderNotHighestPressure> &headerNotHighestPressure,
                               const double feedwaterPressure) const;
};

#endif //TOOLS_SUITE_PRVWITHDESUPERHEATINGFACTORY_H
