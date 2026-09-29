#include "steamModeler/service/low_pressure_header/LowPressureHeaderModeler.h"
#include "steamModeler/util/SteamModelerLogger.h"

std::shared_ptr<LowPressureHeaderCalculationsDomain> LowPressureHeaderModeler::model(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const PressureTurbine& highToLowTurbineInput, const PressureTurbine& mediumToLowTurbineInput,
    const CondensingTurbine& condensingTurbineInput, const BoilerInput& boilerInput, const Boiler& boiler,
    const std::shared_ptr<FlashTank>&                              blowdownFlashTank,
    const HighPressureHeaderCalculationsDomain&                    highPressureHeaderCalculationsDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain) const {
    const std::string methodName = std::string("LowPressureHeaderModeler::") + std::string(__func__) + ": ";

    // if low pressure header exists
    if (headerCountInput > 1) {
        SM_LOG(methodName << "low pressure header provided, processing");

        // 4A. Calculate to low pressure PRV
        SM_LOG(methodName << "calculating low pressure PRV");
        const std::shared_ptr<PrvWithoutDesuperheating>& lowPressurePrv = lowPressurePrvCalculator.calc(
            headerCountInput, highPressureHeaderInput, highToLowTurbineInput, condensingTurbineInput,
            mediumPressureHeaderInput, mediumToLowTurbineInput, lowPressureHeaderInput, boiler,
            highPressureHeaderCalculationsDomain, mediumPressureHeaderCalculationsDomain);

        // 4B. Calculate flashed steam into low pressure header if selected
        SM_LOG(methodName << "calculating condensateFlashTank");
        LowPressureFlashedSteamIntoHeaderCalculatorDomain lowPressureFlashedSteamIntoHeaderCalculatorDomain =
            lowPressureFlashedSteamIntoHeaderCalculator.calc(
                headerCountInput, lowPressureHeaderInput, mediumPressureHeaderInput,
                highPressureHeaderCalculationsDomain, mediumPressureHeaderCalculationsDomain);
        SM_LOG(methodName << "lowPressureFlashedSteamIntoHeaderCalculatorDomain=" << lowPressureFlashedSteamIntoHeaderCalculatorDomain);

        // 4C. Model Low Pressure Header
        SM_LOG(methodName << "calculating lowPressureHeader");
        const SteamSystemModelerTool::FluidProperties& lowPressureHeaderOutput = lowPressureHeaderCalculator.calc(
            headerCountInput, lowPressureHeaderInput, highToLowTurbineInput, mediumToLowTurbineInput, boilerInput,
            lowPressurePrv, blowdownFlashTank, lowPressureFlashedSteamIntoHeaderCalculatorDomain,
            highPressureHeaderCalculationsDomain, mediumPressureHeaderCalculationsDomain);
        SM_LOG(methodName << "lowPressureHeaderOutput=" << lowPressureHeaderOutput);

        // 4D. Calculate Heat Loss for Remaining Steam in Low Pressure Header
        SM_LOG(methodName << "calculating lowPressureHeader heat loss");
        const HeatLoss& heatLoss = heatLossFactory.make(lowPressureHeaderInput, lowPressureHeaderOutput);
        SM_LOG(methodName << "lowPressureHeader heatLoss=" << heatLoss);

        SM_LOG(methodName << "updating lowPressureHeader with heat loss");
        const SteamSystemModelerTool::FluidProperties& lowPressureHeaderOutputUpdated =
            fluidPropertiesFactory.makeWithSpecificVolume(heatLoss, lowPressureHeaderOutput.specificVolume);
        SM_LOG(methodName << "lowPressureHeaderOutput=" << lowPressureHeaderOutputUpdated);

        // 4E. Calculate Low Pressure Condensate
        SM_LOG(methodName << "calculating lowPressureCondensate");
        const SteamSystemModelerTool::FluidProperties lowPressureCondensate =
            lowPressureCondensateCalculator.calc(lowPressureHeaderInput);
        SM_LOG(methodName << "lowPressureCondensate=" << lowPressureCondensate);

        const LowPressureHeaderCalculationsDomain domain = {lowPressurePrv, lowPressureHeaderOutputUpdated, heatLoss,
                                                            lowPressureCondensate,
                                                            lowPressureFlashedSteamIntoHeaderCalculatorDomain};
        return std::make_shared<LowPressureHeaderCalculationsDomain>(domain);
    }
    else {
        SM_LOG(methodName << "medium pressure header not provided, skipping");
        return nullptr;
    }
}
