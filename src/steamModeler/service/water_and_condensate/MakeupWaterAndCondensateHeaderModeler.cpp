#include "steamModeler/service/water_and_condensate/MakeupWaterAndCondensateHeaderModeler.h"
#include "steamModeler/util/SteamModelerLogger.h"

MakeupWaterAndCondensateHeaderCalculationsDomain MakeupWaterAndCondensateHeaderModeler::model(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput, const BoilerInput& boilerInput,
    const OperationsInput& operationsInput, const CondensingTurbine& condensingTurbineInput, const Boiler& boiler,
    const std::shared_ptr<FlashTank>&                              blowdownFlashTank,
    const HighPressureHeaderCalculationsDomain&                    highPressureHeaderCalculationsDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>&    lowPressureHeaderCalculationsDomain) const {
    const std::string methodName =
        std::string("MakeupWaterAndCondensateHeaderModeler::") + std::string(__func__) + ": ";

    // 5A. Calculate Combined Return Condensate
    SM_LOG(methodName << "calculating combinedCondensateHeader");
    const Header& combinedCondensateHeader =
        combinedCondensateCalculator.calc(headerCountInput, highPressureHeaderCalculationsDomain,
                                          mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain);
    SM_LOG(methodName << "combinedCondensateHeader=" << combinedCondensateHeader);

    SM_LOG(methodName << "calculating combinedCondensate");
    const SteamSystemModelerTool::FluidProperties& combinedCondensate =
        fluidPropertiesFactory.make(combinedCondensateHeader);
    SM_LOG(methodName << "combinedCondensate=" << combinedCondensate);

    // 5B. Calculate return condensate
    SM_LOG(methodName << "calculating returnCondensate");
    const SteamSystemModelerTool::FluidProperties& returnCondensate =
        returnCondensateCalculator.calc(highPressureHeaderInput, combinedCondensateHeader);
    SM_LOG(methodName << "returnCondensate=" << returnCondensate);

    // 5C. Flash return condensate if selected
    SM_LOG(methodName << "calculating flash returnCondensate");
    const ReturnCondensateCalculationsDomain& returnCondensateCalculationsDomain =
        returnCondensateCalculator.flash(highPressureHeaderInput, returnCondensate);
    const SteamSystemModelerTool::FluidProperties returnCondensateFlashed =
        returnCondensateCalculationsDomain.returnCondensateFlashed;
    SM_LOG(methodName << "returnCondensateCalculationsDomain=" << returnCondensateCalculationsDomain);

    // 5D. Calculate Makeup Water
    SM_LOG(methodName << "calculating makeupWaterOnly");
    const SteamSystemModelerTool::SteamPropertiesOutput& makeupWaterOnly = makeupWaterCalculator.calc(operationsInput);
    SM_LOG(methodName << "makeupWaterOnly=" << makeupWaterOnly);

    // 5E. Calculate makeup water mass flow
    SM_LOG(methodName << "calculating makeupWater");
    const double                                   lowPressureVentedSteam = 0; // don't have a value yet
    const SteamSystemModelerTool::FluidProperties& makeupWater            = makeupWaterMassFlowCalculator.calc(
        headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput, lowPressureHeaderInput,
        condensingTurbineInput, boilerInput, boiler, returnCondensateFlashed, makeupWaterOnly,
        highPressureHeaderCalculationsDomain, mediumPressureHeaderCalculationsDomain,
        lowPressureHeaderCalculationsDomain, lowPressureVentedSteam);
    SM_LOG(methodName << "makeupWater=" << makeupWater);

    SM_LOG(methodName << "calculating makeupWaterVolumeFlow");
    const MakeupWaterVolumeFlowCalculationsDomain& makeupWaterVolumeFlowCalculationsDomain =
        makeupWaterVolumeFlowCalculator.calc(makeupWater, operationsInput);
    SM_LOG(methodName << "makeupWaterVolumeFlowCalculationsDomain=" << makeupWaterVolumeFlowCalculationsDomain);

    // 5F. Run heat exchange if pre heating makeup water
    SM_LOG(methodName << "calculating heatExchangerOutput");
    std::shared_ptr<HeatExchanger::Output> heatExchangerOutput =
        heatExchangerCalculator.calc(boilerInput, boiler, makeupWater, blowdownFlashTank);
    SM_LOG(methodName << "heatExchangerOutput=" << heatExchangerOutput);

    // 5G. Calculate makeup water and condensate combined
    SM_LOG(methodName << "calculating makeupWaterAndCondensateHeaderOutput");
    const SteamSystemModelerTool::FluidProperties& makeupWaterAndCondensateHeaderOutput =
        makeupWaterAndCondensateHeaderCalculator.calc(boilerInput, condensingTurbineInput, returnCondensateFlashed,
                                                      heatExchangerOutput, makeupWater,
                                                      highPressureHeaderCalculationsDomain);
    SM_LOG(methodName << "makeupWaterAndCondensateHeaderOutput=" << makeupWaterAndCondensateHeaderOutput);

    return {combinedCondensate,
            returnCondensateFlashed,
            returnCondensateCalculationsDomain,
            makeupWater,
            makeupWaterVolumeFlowCalculationsDomain,
            heatExchangerOutput,
            makeupWaterAndCondensateHeaderOutput};
}
