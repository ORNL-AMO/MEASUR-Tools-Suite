#include "steamModeler/service/high_pressure_header/HighPressureHeaderModeler.h"
#include "steamModeler/util/SteamModelerLogger.h"

HighPressureHeaderCalculationsDomain
HighPressureHeaderModeler::model(const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                 const PressureTurbine&                           highToMediumTurbineInput,
                                 const PressureTurbine&                           highToLowTurbineInput,
                                 const CondensingTurbine& condensingTurbineInput, const Boiler& boiler) const {
    const std::string methodName = std::string("HighPressureHeaderModeler::") + std::string(__func__) + ": ";

    // 2A. Calculate High Pressure Header
    SM_LOG(methodName << "calculating high pressure header");
    const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutputOriginal =
        highPressureHeaderCalculator.calc(highPressureHeaderInput, boiler);
    SM_LOG(methodName << "highPressureHeaderOutputOriginal=" << highPressureHeaderOutputOriginal);

    // 2B. Calculate Heat Loss of steam in high pressure header
    SM_LOG(methodName << "calculating highPressureHeader heat loss");
    const HeatLoss& heatLoss = heatLossFactory.make(highPressureHeaderInput, highPressureHeaderOutputOriginal);
    SM_LOG(methodName << "highPressureHeader heatLoss=" << heatLoss);

    SM_LOG(methodName << "updating highPressureHeader with heat loss");
    const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput = fluidPropertiesFactory.make(heatLoss);
    SM_LOG(methodName << "highPressureHeaderOutput=" << highPressureHeaderOutput);

    // 2C. Calculate High Pressure Condensate
    SM_LOG(methodName << "calculating high pressure condensate");
    const SteamSystemModelerTool::FluidProperties& highPressureCondensate =
        highPressureCondensateCalculator.calc(highPressureHeaderInput, boiler);
    SM_LOG(methodName << "highPressureCondensate=" << highPressureCondensate);

    // 2D. Calculate High Pressure Flash Tank if 3 header and on
    SM_LOG(methodName << "calculating high pressure flash tank");
    const std::shared_ptr<FlashTank>& highPressureCondensateFlashTank = highPressureFlashTankCalculator.calc(
        headerCountInput, mediumPressureHeaderInput, lowPressureHeaderInput, highPressureCondensate);
    SM_LOG(methodName << "highPressureCondensateFlashTank=" << highPressureCondensateFlashTank);

    // 2E. Calculate condensing turbine
    SM_LOG(methodName << "calculating condensing turbine");
    const std::shared_ptr<Turbine>& condensingTurbine =
        condensingTurbineCalculator.calc(condensingTurbineInput, highPressureHeaderOutput, false);
    SM_LOG(methodName << "condensingTurbine=" << condensingTurbine);
    const std::shared_ptr<Turbine>& condensingTurbineIdeal =
        condensingTurbineCalculator.calc(condensingTurbineInput, highPressureHeaderOutput, true);
    SM_LOG(methodName << "condensingTurbineIdeal=" << condensingTurbineIdeal);

    // 2F. Calculate high to low steam turbine if in use
    SM_LOG(methodName << "calculating highToLowPressureTurbine");
    const std::shared_ptr<Turbine>& highToLowPressureTurbine = highToLowSteamTurbineCalculator.calc(
        headerCountInput, highToLowTurbineInput, highPressureHeaderOutput, highPressureHeaderInput,
        condensingTurbineInput, condensingTurbine, lowPressureHeaderInput, boiler, false);
    SM_LOG(methodName << "highToLowPressureTurbine=" << highToLowPressureTurbine);
    const std::shared_ptr<Turbine>& highToLowPressureTurbineIdeal = highToLowSteamTurbineCalculator.calc(
        headerCountInput, highToLowTurbineInput, highPressureHeaderOutput, highPressureHeaderInput,
        condensingTurbineInput, condensingTurbine, lowPressureHeaderInput, boiler, true);
    SM_LOG(methodName << "highToLowPressureTurbineIdeal=" << highToLowPressureTurbineIdeal);

    // 2G. Calculate high to medium steam turbine if in use
    const HighToMediumSteamTurbineCalculationsDomain& highToMediumSteamTurbineCalculationsDomain =
        calcHighToMediumSteamTurbine(headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput,
                                     lowPressureHeaderInput, highToMediumTurbineInput, highToLowTurbineInput,
                                     condensingTurbineInput, boiler, highPressureHeaderOutput, condensingTurbine,
                                     highToLowPressureTurbine, highToLowPressureTurbineIdeal);
    const std::shared_ptr<Turbine>& highToMediumPressureTurbine =
        highToMediumSteamTurbineCalculationsDomain.highToMediumPressureTurbine;
    const std::shared_ptr<Turbine>& highToMediumPressureTurbineIdeal =
        highToMediumSteamTurbineCalculationsDomain.highToMediumPressureTurbineIdeal;

    const std::shared_ptr<Turbine>& highToLowPressureTurbineUpdated =
        highToMediumSteamTurbineCalculationsDomain.highToLowPressureTurbineUpdated;
    const std::shared_ptr<Turbine>& highToLowPressureTurbineIdealUpdated =
        highToMediumSteamTurbineCalculationsDomain.highToLowPressureTurbineIdealUpdated;

    return {highPressureHeaderOutput,
            heatLoss,
            highPressureCondensate,
            highPressureCondensateFlashTank,
            condensingTurbine,
            condensingTurbineIdeal,
            highToMediumPressureTurbine,
            highToMediumPressureTurbineIdeal,
            highToLowPressureTurbineUpdated,
            highToLowPressureTurbineIdealUpdated};
}

HighToMediumSteamTurbineCalculationsDomain HighPressureHeaderModeler::calcHighToMediumSteamTurbine(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const PressureTurbine& highToMediumTurbineInput, const PressureTurbine& highToLowTurbineInput,
    const CondensingTurbine& condensingTurbineInput, const Boiler& boiler,
    const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
    const std::shared_ptr<Turbine>& condensingTurbine, const std::shared_ptr<Turbine>& highToLowPressureTurbine,
    const std::shared_ptr<Turbine>& highToLowPressureTurbineIdeal) const {
    const std::string methodName = std::string("HighPressureHeaderModeler::") + std::string(__func__) + ": ";

    SM_LOG(methodName << "calculating high to medium steam turbine");
    const HighToMediumSteamTurbineCalculationsDomain& highToMediumSteamTurbineCalculationsDomain =
        highToMediumSteamTurbineCalculator.calc(
            headerCountInput, highPressureHeaderOutput, highPressureHeaderInput, condensingTurbineInput,
            condensingTurbine, highToLowTurbineInput, highToLowPressureTurbine, highToLowPressureTurbineIdeal,
            highToMediumTurbineInput, mediumPressureHeaderInput, lowPressureHeaderInput, boiler);
    SM_LOG(methodName << "highToMediumSteamTurbineCalculationsDomain=" << highToMediumSteamTurbineCalculationsDomain);

    return highToMediumSteamTurbineCalculationsDomain;
}
