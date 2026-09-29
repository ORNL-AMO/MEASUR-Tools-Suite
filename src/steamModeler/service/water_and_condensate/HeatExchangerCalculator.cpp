#include "steamModeler/service/water_and_condensate/HeatExchangerCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

std::shared_ptr<HeatExchanger::Output>
HeatExchangerCalculator::calc(const BoilerInput& boilerInput, const Boiler& boiler,
                              const SteamSystemModelerTool::FluidProperties& makeupWaterAndMassFlow,
                              const std::shared_ptr<FlashTank>&              blowdownFlashTank) const {
    const std::string methodName = std::string("HeatExchangerCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<HeatExchanger::Output> heatExchangerOutput = nullptr;

    const bool isPreheatMakeupWater = boilerInput.isPreheatMakeupWater();
    SM_LOG(methodName << "boilerInput.isPreheatMakeupWater=" << isPreheatMakeupWater);

    if (isPreheatMakeupWater) {
        SM_LOG(methodName << "isPreheatMakeupWater is true, calculating heatExchangerOutput");
        SteamSystemModelerTool::FluidProperties coldInlet    = fluidPropertiesFactory.make(makeupWaterAndMassFlow);
        const double                            approachTemp = boilerInput.getApproachTemperature();

        SteamSystemModelerTool::FluidProperties hotInlet;
        if (boilerInput.isBlowdownFlashed()) {
            SM_LOG(methodName << "boilerInput isBlowdownFlashed is true, calculating hotInlet from blowdownFlashTank");
            const SteamSystemModelerTool::FluidProperties& outletLiquidSaturatedProperties =
                blowdownFlashTank->getOutletLiquidSaturatedProperties();
            hotInlet = fluidPropertiesFactory.make(outletLiquidSaturatedProperties);
        }
        else {
            SM_LOG(methodName << "boilerInput not isBlowdownFlashed is false, calculating hotInlet from boiler blowdown");
            const SteamSystemModelerTool::FluidProperties& blowdownProperties = boiler.getBlowdownProperties();
            hotInlet = fluidPropertiesFactory.make(blowdownProperties);
        }

        SM_LOG(methodName << "calculating heatExchanger");
        HeatExchanger                heatExchanger = {hotInlet, coldInlet, approachTemp};
        const HeatExchanger::Output& output        = heatExchanger.calculate();
        heatExchangerOutput                        = std::make_shared<HeatExchanger::Output>(output);
    }
    else {
        SM_LOG(methodName << "isPreheatMakeupWater is false, skipping heat exchanger");
    }

    return heatExchangerOutput;
}
