#ifndef TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATOR_H
#define TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATOR_H

#include <steamModeler/Boiler.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/domain/HeaderFactory.h>

class HighPressureHeaderCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    calc(const HeaderWithHighestPressure &highPressureHeaderInput, const Boiler &boiler) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeaderFactory headerFactory = HeaderFactory();
};

#endif //TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATOR_H
