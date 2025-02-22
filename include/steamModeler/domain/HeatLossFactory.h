#ifndef TOOLS_SUITE_HEATLOSSFACTORY_H
#define TOOLS_SUITE_HEATLOSSFACTORY_H

#include <steamModeler/api/HeaderInput.h>
#include "steamModeler/Header.h"
#include "steamModeler/HeatLoss.h"

class HeatLossFactory {
public:
    const HeatLoss make(const HeaderWithHighestPressure &highestPressureHeaderInput,
                        const SteamSystemModelerTool::FluidProperties &headerOutput) const;

    const HeatLoss make(const std::shared_ptr<HeaderNotHighestPressure> &notHighestPressureHeaderInput,
                        const SteamSystemModelerTool::FluidProperties &headerOutput) const;

    const HeatLoss
    make(const SteamSystemModelerTool::FluidProperties &headerOutput, const double percentHeatLoss) const;
};

#endif //TOOLS_SUITE_HEATLOSSFACTORY_H
