#include <steamModeler/service/medium_pressure_header/MediumPressureHeaderCalculator.h>
#include "steamModeler/util/SteamModelerLogger.h"

MediumPressureHeaderCalculatorOutput
MediumPressureHeaderCalculator::calc(const Boiler& boiler, const PressureTurbine& highToLowTurbineInput,
                                     const std::shared_ptr<Turbine>&                  highToLowPressureTurbine,
                                     const std::shared_ptr<Turbine>&                  highToLowPressureTurbineIdeal,
                                     const SteamSystemModelerTool::FluidProperties&   highPressureHeaderOutput,
                                     const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
                                     const std::shared_ptr<PrvWithoutDesuperheating>& highToMediumPressurePrv,
                                     const PressureTurbine&                           highToMediumTurbineInput,
                                     const std::shared_ptr<Turbine>&                  highToMediumPressureTurbine,
                                     const std::shared_ptr<FlashTank>&                highPressureCondensateFlashTank,
                                     const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput) const {
    const std::string methodName = std::string("MediumPressureHeaderCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated      = highToLowPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated = highToLowPressureTurbineIdeal;

    SM_LOG(methodName << "calculating mediumPressureHeaderOutput");
    // 3B1 & 3B2. Calculate medium pressure header
    const Header mediumPressureHeader =
        headerFactory.make(mediumPressureHeaderInput, highToMediumPressurePrv, highToMediumTurbineInput,
                           highToMediumPressureTurbine, highPressureCondensateFlashTank);
    SM_LOG(methodName << "mediumPressureHeader=" << mediumPressureHeader);

    const SteamSystemModelerTool::FluidProperties& mediumPressureHeaderOutput =
        fluidPropertiesFactory.make(mediumPressureHeader);
    SM_LOG(methodName << "mediumPressureHeaderOutput=" << mediumPressureHeaderOutput);

    // 3B3. Check that medium pressure header has enough steam to be processed
    const double mediumPressureHeaderMassFlow               = mediumPressureHeader.getInletMassFlow();
    const double mediumPressureHeaderInputProcessSteamUsage = mediumPressureHeaderInput->getProcessSteamUsage();

    if (mediumPressureHeaderMassFlow < mediumPressureHeaderInputProcessSteamUsage) {
        SM_LOG(methodName << "mediumPressureHeaderMassFlow=" << mediumPressureHeaderMassFlow << " < mediumPressureHeaderInputProcessSteamUsage=" << mediumPressureHeaderInputProcessSteamUsage << "; attempt to adjust medium to low turbine");

        const SteamReducerOutput& steamReducerOutput = steamBalanceCheckerService.check(
            "mediumPressureHeader", highToLowTurbineInput, lowPressureHeaderInput, boiler, highToLowPressureTurbine,
            highToLowPressureTurbineIdeal, highPressureHeaderOutput, mediumPressureHeaderInputProcessSteamUsage,
            mediumPressureHeaderMassFlow);
        SM_LOG(methodName << "steamReducerOutput=" << steamReducerOutput);

        highToLowPressureTurbineUpdated      = steamReducerOutput.highToLowPressureTurbineUpdated;
        highToLowPressureTurbineIdealUpdated = steamReducerOutput.highToLowPressureTurbineIdealUpdated;
    }

    return {mediumPressureHeaderOutput, highToLowPressureTurbineUpdated, highToLowPressureTurbineIdealUpdated};
}
