#ifndef TOOLS_SUITE_LOWPRESSUREHEADERCALCULATOR_H
#define TOOLS_SUITE_LOWPRESSUREHEADERCALCULATOR_H

#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/domain/HeaderFactory.h>
#include <steamModeler/domain/LowPressureFlashedSteamIntoHeaderCalculatorDomain.h>

class LowPressureHeaderCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    calc(const int headerCountInput, const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
         const PressureTurbine &highToLowTurbineInput, const PressureTurbine &mediumToLowTurbineInput,
         const BoilerInput &boilerInput, const std::shared_ptr<PrvWithoutDesuperheating> &lowPressurePrv,
         const std::shared_ptr<FlashTank> &blowdownFlashTank,
         const LowPressureFlashedSteamIntoHeaderCalculatorDomain &lowPressureFlashedSteamIntoHeaderCalculatorDomain,
         const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
         const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeaderFactory headerFactory = HeaderFactory();
};

#endif //TOOLS_SUITE_LOWPRESSUREHEADERCALCULATOR_H
