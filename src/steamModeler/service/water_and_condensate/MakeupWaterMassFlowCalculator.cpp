#include "steamModeler/service/water_and_condensate/MakeupWaterMassFlowCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

SteamSystemModelerTool::FluidProperties MakeupWaterMassFlowCalculator::calc(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const CondensingTurbine& condensingTurbineInput, const BoilerInput& boilerInput, const Boiler& boiler,
    const SteamSystemModelerTool::FluidProperties&                 returnCondensate,
    const SteamSystemModelerTool::SteamPropertiesOutput&           makeupWaterOutput,
    const HighPressureHeaderCalculationsDomain&                    highPressureHeaderCalculationsDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>&    lowPressureHeaderCalculationsDomain,
    const double                                                   lowPressureVentedSteam) const {
    const std::string methodName = std::string("MakeupWaterMassFlowCalculator::") + std::string(__func__) + ": ";

    SM_LOG(methodName << "calculating inletHeaderFlow");
    const double inletHeaderFlow =
        calcInletHeaderFlow(headerCountInput, highPressureHeaderInput, lowPressureHeaderInput,
                            highPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain);

    SM_LOG(methodName << "calculating makeupWaterMassFlow");
    const double makeupWaterMassFlow = calcMakeupWaterMassFlow(
        headerCountInput, mediumPressureHeaderInput, lowPressureHeaderInput, condensingTurbineInput, boilerInput,
        boiler, returnCondensate, inletHeaderFlow, highPressureHeaderCalculationsDomain,
        mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain, lowPressureVentedSteam);

    SM_LOG(methodName << "calculating energyFlow");
    const double energyFlow = calcMakeupWaterEnergyFlow(makeupWaterMassFlow, makeupWaterOutput);

    return {makeupWaterMassFlow, energyFlow, makeupWaterOutput};
}

double MakeupWaterMassFlowCalculator::calcInletHeaderFlow(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>&            lowPressureHeaderInput,
    const HighPressureHeaderCalculationsDomain&                 highPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>& lowPressureHeaderCalculationsDomain) const {
    const std::string methodName = std::string("MakeupWaterMassFlowCalculator::") + std::string(__func__) + ": ";

    if (headerCountInput == 1) {
        SM_LOG(methodName << "only 1 header, calculating inletHeaderFlow from high pressure");
        const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput =
            highPressureHeaderCalculationsDomain.highPressureHeaderOutput;
        return calcInletHeaderFlow(highPressureHeaderOutput, highPressureHeaderInput);
    }
    else {
        SM_LOG(methodName << "multiple headers, calculating inletHeaderFlow from low pressure");
        const SteamSystemModelerTool::FluidProperties& lowPressureHeaderOutput =
            lowPressureHeaderCalculationsDomain->lowPressureHeaderOutput;
        return calcInletHeaderFlow(lowPressureHeaderOutput, lowPressureHeaderInput);
    }
}

double MakeupWaterMassFlowCalculator::calcInletHeaderFlow(
    const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
    const HeaderWithHighestPressure&               highPressureHeaderInput) const {
    const std::string methodName = std::string("MakeupWaterMassFlowCalculator::") + std::string(__func__) + ": ";

    const double massFlow          = highPressureHeaderOutput.massFlow;
    const double processSteamUsage = highPressureHeaderInput.getProcessSteamUsage();
    const double result            = massFlow - processSteamUsage;

    SM_LOG(methodName << "massFlow=" << massFlow << " - processSteamUsage=" << processSteamUsage << ": result=" << result);

    return result;
}

double MakeupWaterMassFlowCalculator::calcInletHeaderFlow(
    const SteamSystemModelerTool::FluidProperties&   lowPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput) const {
    const std::string methodName = std::string("MakeupWaterMassFlowCalculator::") + std::string(__func__) + ": ";

    const double massFlow          = lowPressureHeaderOutput.massFlow;
    const double processSteamUsage = lowPressureHeaderInput->getProcessSteamUsage();
    const double result            = massFlow - processSteamUsage;

    SM_LOG(methodName << "massFlow=" << massFlow << " - processSteamUsage=" << processSteamUsage << ": result=" << result);

    return result;
}

double MakeupWaterMassFlowCalculator::calcMakeupWaterMassFlow(
    const int headerCountInput, const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const CondensingTurbine& condensingTurbineInput, const BoilerInput& boilerInput, const Boiler& boiler,
    const SteamSystemModelerTool::FluidProperties& returnCondensate, const double inletHeaderFlow,
    const HighPressureHeaderCalculationsDomain&                    highPressureHeaderCalculationsDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>&    lowPressureHeaderCalculationsDomain,
    const double                                                   lowPressureVentedSteam) const {
    const std::string methodName = std::string("MakeupWaterMassFlowCalculator::") + std::string(__func__) + ": ";

    double makeupWaterMassFlow = calcMakeupWaterMassFlow(boilerInput, boiler);

    if (headerCountInput > 1) {
        SM_LOG(methodName << "multiple headers, adjusting makeupWaterMassFlow");

        if (headerCountInput == 3 && mediumPressureHeaderInput->isDesuperheatSteamIntoNextHighest()) {
            SM_LOG(methodName << "mediumPressureHeaderInput.isDesuperheatSteamIntoNextHighest," << " adding highToMediumPressurePrv feedwaterMassFlow to makeupWaterMassFlow");
            const std::shared_ptr<PrvWithoutDesuperheating>& highToMediumPressurePrv =
                mediumPressureHeaderCalculationsDomain->highToMediumPressurePrv;
            makeupWaterMassFlow =
                addPrvFeedwaterMassFlowToMakeupWaterMassFlow(highToMediumPressurePrv, makeupWaterMassFlow);
        }
        else {
            SM_LOG(methodName << "not 3 headers and not mediumPressureHeaderInput.isDesuperheatSteamIntoNextHighest," << " skipping highToMediumPressurePrv feedwaterMassFlow");
        }

        if (lowPressureHeaderInput->isDesuperheatSteamIntoNextHighest()) {
            SM_LOG(methodName << "lowPressureHeaderInput.isDesuperheatSteamIntoNextHighest," << " adding lowPressurePrv feedwaterMassFlow to makeupWaterMassFlow");
            const std::shared_ptr<PrvWithoutDesuperheating>& lowPressurePrv =
                lowPressureHeaderCalculationsDomain->lowPressurePrv;
            makeupWaterMassFlow = addPrvFeedwaterMassFlowToMakeupWaterMassFlow(lowPressurePrv, makeupWaterMassFlow);
        }
        else {
            SM_LOG(methodName << "not lowPressureHeaderInput.isDesuperheatSteamIntoNextHighest," << " skipping lowPressurePrv feedwaterMassFlow");
        }

        if (condensingTurbineInput.isUseTurbine()) {
            SM_LOG(methodName << "condensingTurbine exists, subtracting its mass flow from makeupWaterMassFlow");
            const std::shared_ptr<Turbine>& condensingTurbine = highPressureHeaderCalculationsDomain.condensingTurbine;
            const double                    massFlow          = condensingTurbine->getMassFlow();
            makeupWaterMassFlow -= massFlow;
            SM_LOG(methodName << "massFlow=" << massFlow << ": result=" << makeupWaterMassFlow);
        }
        else {
            SM_LOG(methodName << "not condensingTurbineInput.isUseTurbine," << " skipping condensingTurbine massFlow");
        }
    }

    const double returnCondensateMassFlow = returnCondensate.massFlow;
    const double result = makeupWaterMassFlow - returnCondensateMassFlow - inletHeaderFlow + lowPressureVentedSteam;
    SM_LOG(methodName << "makeupWaterMassFlow=" << makeupWaterMassFlow << " - returnCondensateMassFlow=" << returnCondensateMassFlow << " - inletHeaderFlow=" << inletHeaderFlow << " + lowPressureVentedSteam=" << lowPressureVentedSteam << ": result=" << result);

    return result;
}

double MakeupWaterMassFlowCalculator::calcMakeupWaterMassFlow(const BoilerInput& boilerInput,
                                                              const Boiler&      boiler) const {
    const std::string methodName = std::string("MakeupWaterMassFlowCalculator::") + std::string(__func__) + ": ";

    const double massFlow          = boiler.getFeedwaterProperties().massFlow;
    const double deaeratorVentRate = boilerInput.getDeaeratorVentRate();
    const double result            = massFlow * (1 + deaeratorVentRate / 100);

    SM_LOG(methodName << "massFlow=" << massFlow << " * (1 + deaeratorVentRate=" << deaeratorVentRate << " / 100): result=" << result);

    return result;
}

double MakeupWaterMassFlowCalculator::addPrvFeedwaterMassFlowToMakeupWaterMassFlow(
    const std::shared_ptr<PrvWithoutDesuperheating>& prv, double makeupWaterMassFlow) const {
    const std::string methodName = std::string("MakeupWaterMassFlowCalculator::") + std::string(__func__) + ": ";

    const double feedwaterMassFlow = getFeedwaterMassFlow(prv);
    const double result            = makeupWaterMassFlow + feedwaterMassFlow;

    SM_LOG(methodName << "makeupWaterMassFlow=" << makeupWaterMassFlow << " + feedwaterMassFlow=" << feedwaterMassFlow << ": result=" << result);

    return result;
}

double MakeupWaterMassFlowCalculator::getFeedwaterMassFlow(const std::shared_ptr<PrvWithoutDesuperheating>& prv) const {
    double massFlow = 0;

    if (prv != nullptr) {
        if (prv->isWithDesuperheating()) {
            std::shared_ptr<PrvWithDesuperheating> with = std::static_pointer_cast<PrvWithDesuperheating>(prv);
            massFlow                                    = with->getFeedwaterMassFlow();
        }
    }

    return massFlow;
}

double MakeupWaterMassFlowCalculator::calcMakeupWaterEnergyFlow(
    double massFlow, const SteamSystemModelerTool::SteamPropertiesOutput& makeupWater) const {
    const std::string methodName = std::string("MakeupWaterMassFlowCalculator::") + std::string(__func__) + ": ";

    const double specificEnthalpy = makeupWater.specificEnthalpy;
    const double result           = massFlow * specificEnthalpy;

    SM_LOG(methodName << "massFlow=" << massFlow << " * specificEnthalpy=" << specificEnthalpy << ": result=" << result);

    return result;
}
