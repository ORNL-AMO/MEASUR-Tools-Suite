#ifndef TOOLS_SUITE_MEDIUMPRESSURECONDENSATECALCULATOR_H
#define TOOLS_SUITE_MEDIUMPRESSURECONDENSATECALCULATOR_H

#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/api/HeaderInput.h>
#include "steamModeler/service/EnergyFlowCalculator.h"
#include "steamModeler/service/MassFlowCalculator.h"

class MediumPressureCondensateCalculator {
public:
    const SteamSystemModelerTool::FluidProperties
    calc(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const;

private:
    const EnergyFlowCalculator energyFlowCalculator = EnergyFlowCalculator();
    const MassFlowCalculator massFlowCalculator = MassFlowCalculator();
};

#endif //TOOLS_SUITE_MEDIUMPRESSURECONDENSATECALCULATOR_H
