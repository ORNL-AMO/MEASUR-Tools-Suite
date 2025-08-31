#ifndef TOOLS_SUITE_DEAERATORFACTORY_H
#define TOOLS_SUITE_DEAERATORFACTORY_H

#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/Deaerator.h>
#include <steamModeler/Header.h>

class DeaeratorFactory {
  public:
    const Deaerator make(const BoilerInput& boilerInput, const double feedwaterMassFlow,
                         const SteamSystemModelerTool::FluidProperties& makeupWaterAndCondensateHeaderOutput,
                         const SteamSystemModelerTool::FluidProperties& inletHeaderOutput) const;
};

#endif // TOOLS_SUITE_DEAERATORFACTORY_H
