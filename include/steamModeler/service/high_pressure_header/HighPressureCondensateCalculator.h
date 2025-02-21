#ifndef TOOLS_SUITE_HIGHPRESSURECONDENSATECALCULATOR_H
#define TOOLS_SUITE_HIGHPRESSURECONDENSATECALCULATOR_H

#include <steamModeler/Boiler.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/service/EnergyFlowCalculator.h>
#include <steamModeler/service/MassFlowCalculator.h>

class HighPressureCondensateCalculator {
public:
    const SteamSystemModelerTool::FluidProperties
    calc(const HeaderWithHighestPressure &highPressureHeaderInput, const Boiler &boiler) const;

private:
    const EnergyFlowCalculator energyFlowCalculator = EnergyFlowCalculator();
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const MassFlowCalculator massFlowCalculator = MassFlowCalculator();
};

#endif //TOOLS_SUITE_HIGHPRESSURECONDENSATECALCULATOR_H
