#include "steamModeler/service/low_pressure_header/LowPressureFlashedSteamIntoHeaderCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

LowPressureFlashedSteamIntoHeaderCalculatorDomain LowPressureFlashedSteamIntoHeaderCalculator::calc(
    const int headerCountInput, const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>&               mediumPressureHeaderInput,
    const HighPressureHeaderCalculationsDomain&                    highPressureHeaderCalculationsDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain) const {
    const std::string methodName =
        std::string("LowPressureFlashedSteamIntoHeaderCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<FlashTank> mediumPressureCondensateFlashTank = nullptr;
    std::shared_ptr<FlashTank> highPressureCondensateFlashTank =
        (mediumPressureHeaderCalculationsDomain == nullptr)
            ? nullptr
            : mediumPressureHeaderCalculationsDomain->highPressureCondensateFlashTank;

    SM_LOG(methodName << "calculating flashedSteamIntoLowPressureHeader");
    if (lowPressureHeaderInput->isFlashCondensate()) {
        SM_LOG(methodName << "lowPressureHeaderInput isFlashCondensate, processing");
        const SteamSystemModelerTool::FluidProperties& highPressureCondensate =
            highPressureHeaderCalculationsDomain.highPressureCondensate;
        if (headerCountInput == 3) {
            SM_LOG(methodName << "medium pressure header provided");
            SM_LOG(methodName << "calculating mediumPressureCondensateFlashTank");
            const SteamSystemModelerTool::FluidProperties& mediumPressureCondensate =
                mediumPressureHeaderCalculationsDomain->mediumPressureCondensate;
            highPressureCondensateFlashTank   = mediumPressureHeaderCalculationsDomain->highPressureCondensateFlashTank;
            mediumPressureCondensateFlashTank = makeMediumPressureCondensateFlashTank(
                lowPressureHeaderInput, mediumPressureHeaderInput, mediumPressureCondensate, highPressureCondensate,
                highPressureCondensateFlashTank);
        }
        else {
            SM_LOG(methodName << "medium pressure header not provided");
            SM_LOG(methodName << "calculating highPressureCondensateFlashTank with lowPressureHeaderInput pressure");
            highPressureCondensateFlashTank =
                makeHighPressureCondensateFlashTank(lowPressureHeaderInput, highPressureCondensate);
        }
    }
    else {
        SM_LOG(methodName << "lowPressureHeaderInput not isFlashCondensate, skipping");
    }

    return {mediumPressureCondensateFlashTank, highPressureCondensateFlashTank};
}

std::shared_ptr<FlashTank> LowPressureFlashedSteamIntoHeaderCalculator::makeMediumPressureCondensateFlashTank(
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const SteamSystemModelerTool::FluidProperties&   mediumPressureCondensate,
    const SteamSystemModelerTool::FluidProperties&   highPressureCondensate,
    const std::shared_ptr<FlashTank>&                highPressureCondensateFlashTank) const {
    const std::string methodName =
        std::string("LowPressureFlashedSteamIntoHeaderCalculator::") + std::string(__func__) + ": ";

    // 4B. Calculate Medium Pressure Flash Tank
    // mix inlet condensate using header calculateThermalResistance
    SM_LOG(methodName << "calculating highAndMediumPressureMixHeader");
    std::shared_ptr<Header> highAndMediumPressureMixHeader =
        makeHighAndMediumPressureMixHeader(lowPressureHeaderInput, mediumPressureHeaderInput, mediumPressureCondensate,
                                           highPressureCondensate, highPressureCondensateFlashTank);
    SM_LOG(methodName << "highAndMediumPressureMixHeader=" << *highAndMediumPressureMixHeader);

    // run the mixed condensate through the flash tank
    SM_LOG(methodName << "calculating mediumPressureCondensateFlashTank");
    const FlashTank& flashTank = flashTankFactory.make(highAndMediumPressureMixHeader, lowPressureHeaderInput);
    SM_LOG(methodName << "mediumPressureCondensateFlashTank=" << flashTank);

    return std::make_shared<FlashTank>(flashTank);
}

std::shared_ptr<Header> LowPressureFlashedSteamIntoHeaderCalculator::makeHighAndMediumPressureMixHeader(
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const SteamSystemModelerTool::FluidProperties&   mediumPressureCondensate,
    const SteamSystemModelerTool::FluidProperties&   highPressureCondensate,
    const std::shared_ptr<FlashTank>&                highPressureCondensateFlashTank) const {
    const std::string methodName =
        std::string("LowPressureFlashedSteamIntoHeaderCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Header> highAndMediumPressureMixHeader;

    if (mediumPressureHeaderInput->isFlashCondensate()) {
        SM_LOG(methodName << "mediumPressureHeaderInput isFlashCondensate," << " calculating highAndMediumPressureMixHeader with flash tank" << " (highPressureCondensateFlashTank)");
        // if high pressure condensate has been flashed into medium pressure header,
        // inlets will be leftover condensate from flash tank and medium pressure condensate
        const Header& header =
            headerFactory.make(lowPressureHeaderInput, highPressureCondensateFlashTank, mediumPressureCondensate);
        highAndMediumPressureMixHeader = std::make_shared<Header>(header);
    }
    else {
        SM_LOG(methodName << "mediumPressureHeaderInput not isFlashCondensate," << " calculating highAndMediumPressureMixHeader without flash tank");
        // if not, inlets will be high pressure condensate and medium pressure condensate
        const Header& header =
            headerFactory.make(lowPressureHeaderInput, highPressureCondensate, mediumPressureCondensate);
        highAndMediumPressureMixHeader = std::make_shared<Header>(header);
    }

    return highAndMediumPressureMixHeader;
}

// if two headers, flashing into low pressure header
std::shared_ptr<FlashTank> LowPressureFlashedSteamIntoHeaderCalculator::makeHighPressureCondensateFlashTank(
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const SteamSystemModelerTool::FluidProperties&   highPressureCondensate) const {
    const std::string methodName =
        std::string("LowPressureFlashedSteamIntoHeaderCalculator::") + std::string(__func__) + ": ";

    const double pressure = lowPressureHeaderInput->getPressure();

    const FlashTank& flashTank = flashTankFactory.make(pressure, highPressureCondensate);
    SM_LOG(methodName << "highPressureCondensateFlashTank=" << flashTank);

    return std::make_shared<FlashTank>(flashTank);
}
