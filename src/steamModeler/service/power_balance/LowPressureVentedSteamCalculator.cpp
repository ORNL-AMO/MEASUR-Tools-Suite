#include "steamModeler/service/power_balance/LowPressureVentedSteamCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

LowPressureVentedSteamCalculationsDomain LowPressureVentedSteamCalculator::calc(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const CondensingTurbine& condensingTurbineInput, const OperationsInput& operationsInput,
    const BoilerInput& boilerInput, const Boiler& boiler,
    const HighPressureHeaderCalculationsDomain&                    highPressureHeaderCalculationsDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>&    lowPressureHeaderCalculationsDomain,
    MakeupWaterAndCondensateHeaderCalculationsDomain&              makeupWaterAndCondensateHeaderCalculationsDomain,
    const double deaeratorInletSteamMassFlow, const bool recalcMakeupWaterAndMassFlow) const {
    const std::string methodName = std::string("LowPressureVentedSteamCalculator::") + std::string(__func__) + ": ";

    // TODO check requ'd things?? or push to called methods?
    if (lowPressureHeaderCalculationsDomain == nullptr) {
        std::string msg = methodName + "lowPressureHeaderCalculationsDomain is null";
        SM_LOG(msg);
        throw std::invalid_argument(msg);
    }

    const SteamSystemModelerTool::FluidProperties& lowPressureHeaderOutput =
        lowPressureHeaderCalculationsDomain->lowPressureHeaderOutput;

    double lowPressureVentedSteam =
        calcLowPressureVentedSteam(lowPressureHeaderInput, lowPressureHeaderOutput, deaeratorInletSteamMassFlow);

    // 5E. Calculate makeup water mass flow
    SteamSystemModelerTool::FluidProperties makeupWaterUpdated =
        makeupWaterAndCondensateHeaderCalculationsDomain.makeupWater;
    const SteamSystemModelerTool::FluidProperties& returnCondensate =
        makeupWaterAndCondensateHeaderCalculationsDomain.returnCondensateCalculationsDomain.returnCondensateFlashed;

    if (recalcMakeupWaterAndMassFlow) {
        SM_LOG(methodName << "recalculating makeupWater");
        makeupWaterUpdated = makeupWaterMassFlowCalculator.calc(
            headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput, lowPressureHeaderInput,
            condensingTurbineInput, boilerInput, boiler, returnCondensate, makeupWaterUpdated,
            highPressureHeaderCalculationsDomain, mediumPressureHeaderCalculationsDomain,
            lowPressureHeaderCalculationsDomain, lowPressureVentedSteam);
        // prior step used the lowPressureVentedSteam, so pass 0 for it
        makeupWaterUpdated = fluidPropertiesFactory.makeWithVentedSteamAmount(makeupWaterUpdated, 0);
    }
    else {
        SM_LOG(methodName << "updating makeupWater with new lowPressureVentedSteam");
        makeupWaterUpdated =
            fluidPropertiesFactory.makeWithVentedSteamAmount(makeupWaterUpdated, lowPressureVentedSteam);
    }
    SM_LOG(methodName << "makeupWaterUpdated=" << makeupWaterUpdated);

    makeupWaterAndCondensateHeaderCalculationsDomain.makeupWater = makeupWaterUpdated;

    const MakeupWaterVolumeFlowCalculationsDomain& makeupWaterVolumeFlowCalculationsDomain =
        makeupWaterVolumeFlowCalculator.calc(makeupWaterUpdated, operationsInput);
    SM_LOG(methodName << "makeupWaterVolumeFlowCalculationsDomain=" << makeupWaterVolumeFlowCalculationsDomain);
    makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterVolumeFlowCalculationsDomain =
        makeupWaterVolumeFlowCalculationsDomain;

    // 5G. Calculate makeup water and condensate combined
    SM_LOG(methodName << "calculating makeupWaterAndCondensateHeaderOutput");
    const std::shared_ptr<HeatExchanger::Output>& heatExchangerOutput =
        makeupWaterAndCondensateHeaderCalculationsDomain.heatExchangerOutput;
    const SteamSystemModelerTool::FluidProperties& makeupWaterAndCondensateHeaderOutputUpdated =
        makeupWaterAndCondensateHeaderCalculator.calc(boilerInput, condensingTurbineInput, returnCondensate,
                                                      heatExchangerOutput, makeupWaterUpdated,
                                                      highPressureHeaderCalculationsDomain);
    SM_LOG(methodName << "makeupWaterAndCondensateHeaderOutputUpdated=" << makeupWaterAndCondensateHeaderOutputUpdated);
    makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterAndCondensateHeaderOutput =
        makeupWaterAndCondensateHeaderOutputUpdated;

    // 6. Calculate Deaerator
    SM_LOG(methodName << "running deaeratorModeler");
    const Deaerator& deaerator =
        deaeratorModeler.model(headerCountInput, boilerInput, boiler, highPressureHeaderCalculationsDomain,
                               mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain,
                               makeupWaterAndCondensateHeaderCalculationsDomain);
    SM_LOG(methodName << "deaerator=" << deaerator);

    return {lowPressureVentedSteam, makeupWaterUpdated, makeupWaterAndCondensateHeaderOutputUpdated,
            makeupWaterVolumeFlowCalculationsDomain, deaerator};
}

double LowPressureVentedSteamCalculator::calcLowPressureVentedSteam(
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const SteamSystemModelerTool::FluidProperties&   lowPressureHeaderOutput,
    const double                                     deaeratorInletSteamMassFlow) const {
    const std::string methodName = std::string("LowPressureVentedSteamCalculator::") + std::string(__func__) + ": ";

    const double lowPressureProcessSteamUsage = lowPressureHeaderInput->getProcessSteamUsage();
    const double lowPressureVentedSteam =
        lowPressureHeaderOutput.massFlow - (lowPressureProcessSteamUsage + deaeratorInletSteamMassFlow);

    SM_LOG(methodName << "lowPressureHeaderOutput.massFlow=" << lowPressureHeaderOutput.massFlow << " - (lowPressureProcessSteamUsage=" << lowPressureProcessSteamUsage << " + deaeratorInletSteamMassFlow=" << deaeratorInletSteamMassFlow << "); resulting lowPressureVentedSteam=" << lowPressureVentedSteam);

    return lowPressureVentedSteam;
}
