#ifndef TOOLS_SUITE_HEATEXCHANGERCALCULATOR_H
#define TOOLS_SUITE_HEATEXCHANGERCALCULATOR_H

#include <memory>
#include <steamModeler/FlashTank.h>
#include <steamModeler/HeatExchanger.h>
#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>

class HeatExchangerCalculator {
public:
    std::shared_ptr<HeatExchanger::Output> calc(const BoilerInput &boilerInput, const Boiler &boiler,
                                                const SteamSystemModelerTool::FluidProperties &makeupWaterAndMassFlow,
                                                const std::shared_ptr<FlashTank> &blowdownFlashTank) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
};

#endif //TOOLS_SUITE_HEATEXCHANGERCALCULATOR_H
