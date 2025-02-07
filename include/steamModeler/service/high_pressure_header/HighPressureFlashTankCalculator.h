#ifndef TOOLS_SUITE_HIGHPRESSUREFLASHTANKCALCULATOR_H
#define TOOLS_SUITE_HIGHPRESSUREFLASHTANKCALCULATOR_H

#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/FlashTank.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/domain/FlashTankFactory.h>

class HighPressureFlashTankCalculator
{
public:
    const std::shared_ptr<FlashTank>
    calc(const int headerCountInput, const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
         const SteamSystemModelerTool::FluidProperties &highPressureCondensate) const;

private:
    const FlashTankFactory flashTankFactory = FlashTankFactory();
};

#endif //TOOLS_SUITE_HIGHPRESSUREFLASHTANKCALCULATOR_H
