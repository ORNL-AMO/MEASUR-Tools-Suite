#include "steamModeler/service/high_pressure_header/HighPressureFlashTankCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

const std::shared_ptr<FlashTank>
HighPressureFlashTankCalculator::calc(const int                                        headerCountInput,
                                      const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
                                      const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                      const SteamSystemModelerTool::FluidProperties&   highPressureCondensate) const {
    const std::string methodName = std::string("HighPressureFlashTankCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<FlashTank> highPressureCondensateFlashTank = nullptr;
    if (headerCountInput == 3 && mediumPressureHeaderInput->isFlashCondensate()) {
        SM_LOG(methodName << "mediumPressureHeaderInput isUseTurbine, calculating highPressureCondensateFlashTank");
        const double     pressure       = mediumPressureHeaderInput->getPressure();
        const FlashTank& flashTank      = flashTankFactory.make(pressure, highPressureCondensate);
        highPressureCondensateFlashTank = std::make_shared<FlashTank>(flashTank);
    }
    else if (headerCountInput == 2 && lowPressureHeaderInput->isFlashCondensate()) {
        SM_LOG(methodName << "lowPressureHeaderInput isFlashed, calculating highPressureCondensateFlashTank");
        const double     pressure       = lowPressureHeaderInput->getPressure();
        const FlashTank& flashTank      = flashTankFactory.make(pressure, highPressureCondensate);
        highPressureCondensateFlashTank = std::make_shared<FlashTank>(flashTank);
    }
    else {
        SM_LOG(methodName << "mediumPressureHeaderInput not provided or mediumPressureHeaderInput not isFlashCondensate, skipping");
    }

    return highPressureCondensateFlashTank;
}
