#ifndef TOOLS_SUITE_RETURNCONDENSATECALCULATOR_H
#define TOOLS_SUITE_RETURNCONDENSATECALCULATOR_H

#include <steamModeler/Header.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/domain/FlashTankFactory.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/domain/ReturnCondensateCalculationsDomain.h>

class ReturnCondensateCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    calc(const HeaderWithHighestPressure &highPressureHeaderInput, const Header &combinedCondensateHeader) const;

    ReturnCondensateCalculationsDomain
    flash(const HeaderWithHighestPressure &highPressureHeaderInput,
          const SteamSystemModelerTool::FluidProperties &returnCondensate) const;

private:
    FlashTankFactory flashTankFactory = FlashTankFactory();
    FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
};

#endif //TOOLS_SUITE_RETURNCONDENSATECALCULATOR_H
