#ifndef TOOLS_SUITE_LOWPRESSURECONDENSATECALCULATOR_H
#define TOOLS_SUITE_LOWPRESSURECONDENSATECALCULATOR_H

#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>

class LowPressureCondensateCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    calc(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
};

#endif //TOOLS_SUITE_LOWPRESSURECONDENSATECALCULATOR_H
