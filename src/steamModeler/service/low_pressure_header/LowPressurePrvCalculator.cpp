#include "steamModeler/service/low_pressure_header/LowPressurePrvCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

std::shared_ptr<PrvWithoutDesuperheating> LowPressurePrvCalculator::calc(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const PressureTurbine& highToLowTurbineInput, const CondensingTurbine& condensingTurbineInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const PressureTurbine&                           mediumToLowTurbineInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput, const Boiler& boiler,
    const HighPressureHeaderCalculationsDomain&                    highPressureHeaderCalculationsDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain) const {
    const std::string methodName = std::string("LowPressurePrvCalculator::") + std::string(__func__) + ": ";

    const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput =
        highPressureHeaderCalculationsDomain.highPressureHeaderOutput;
    const std::shared_ptr<Turbine>& highToLowPressureTurbine =
        highPressureHeaderCalculationsDomain.highToLowPressureTurbine;
    const std::shared_ptr<Turbine>& condensingTurbine = highPressureHeaderCalculationsDomain.condensingTurbine;

    const SteamSystemModelerTool::FluidProperties& headerOutput =
        determineHeader(headerCountInput, mediumPressureHeaderCalculationsDomain, highPressureHeaderOutput);

    double prvMassFlow =
        calcPrvMassFlow(headerCountInput, highPressureHeaderInput, highPressureHeaderOutput, highToLowTurbineInput,
                        highToLowPressureTurbine, condensingTurbineInput, condensingTurbine, mediumPressureHeaderInput,
                        mediumToLowTurbineInput, mediumPressureHeaderCalculationsDomain);
    SM_LOG(methodName << "prvMassFlow=" << prvMassFlow);

    return makePrv(lowPressureHeaderInput, boiler, headerOutput, prvMassFlow);
}

std::shared_ptr<PrvWithoutDesuperheating>
LowPressurePrvCalculator::makePrv(const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                  const Boiler& boiler, const SteamSystemModelerTool::FluidProperties& headerOutput,
                                  double prvMassFlow) const {
    const std::string methodName = std::string("LowPressurePrvCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<PrvWithoutDesuperheating> prvPtr;

    if (lowPressureHeaderInput->isDesuperheatSteamIntoNextHighest()) {
        SM_LOG(methodName << "lowPressureHeaderInput->isDesuperheatSteamIntoNextHighest," << " making PrvWithDesuperheating");
        double                       feedwaterPressure = boiler.getFeedwaterProperties().pressure;
        const PrvWithDesuperheating& prv =
            prvWithDesuperheatingFactory.make(headerOutput, prvMassFlow, lowPressureHeaderInput, feedwaterPressure);
        SM_LOG(methodName << "lowPressurePrv=" << prv);
        prvPtr = std::make_shared<PrvWithDesuperheating>(prv);
    }
    else {
        SM_LOG(methodName << "lowPressureHeaderInput-> not isDesuperheatSteamIntoNextHighest," << " making PrvWithoutDesuperheating");
        const PrvWithoutDesuperheating& prv =
            prvWithoutDesuperheatingFactory.make(headerOutput, prvMassFlow, lowPressureHeaderInput);
        SM_LOG(methodName << "lowPressurePrv=" << prv);
        prvPtr = std::make_shared<PrvWithoutDesuperheating>(prv);
    }

    return prvPtr;
}

SteamSystemModelerTool::FluidProperties LowPressurePrvCalculator::determineHeader(
    const int                                                      headerCountInput,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain,
    const SteamSystemModelerTool::FluidProperties&                 highPressureHeaderOutput) const {
    if (headerCountInput == 2) {
        return highPressureHeaderOutput;
    }
    else {
        return mediumPressureHeaderCalculationsDomain->mediumPressureHeaderOutput;
    }
}

double LowPressurePrvCalculator::calcPrvMassFlow(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const SteamSystemModelerTool::FluidProperties& highPressureHeader, const PressureTurbine& highToLowTurbineInput,
    const std::shared_ptr<Turbine>& highToLowPressureTurbine, const CondensingTurbine& condensingTurbineInput,
    const std::shared_ptr<Turbine>&                                condensingTurbine,
    const std::shared_ptr<HeaderNotHighestPressure>&               mediumPressureHeaderInput,
    const PressureTurbine&                                         mediumToLowTurbineInput,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain) const {
    const std::string methodName = std::string("LowPressurePrvCalculator::") + std::string(__func__) + ": ";

    SM_LOG(methodName << "calculating low pressure PRV mass flow");

    double prvMassFlow = 0;

    // either medium to low or high to low
    if (headerCountInput == 2) {
        SM_LOG(methodName << "2 headers exist, subtracting high pressure header process steam usage from its mass flow");
        // if 2 headers, next highest is high pressure
        prvMassFlow = highPressureHeader.massFlow - highPressureHeaderInput.getProcessSteamUsage();
        SM_LOG(methodName << "prvMassFlow=" << prvMassFlow);

        if (highToLowTurbineInput.isUseTurbine()) {
            SM_LOG(methodName << "using highToLowPressureTurbine, subtracting its massFlow from prvMassFlow");
            prvMassFlow = prvMassFlow - highToLowPressureTurbine->getMassFlow();
            SM_LOG(methodName << "updated prvMassFlow=" << prvMassFlow);
        }

        if (condensingTurbineInput.isUseTurbine()) {
            SM_LOG(methodName << "using condensingTurbine, subtracting its massFlow from prvMassFlow");
            prvMassFlow = prvMassFlow - condensingTurbine->getMassFlow();
            SM_LOG(methodName << "updated prvMassFlow=" << prvMassFlow);
        }
    }
    else if (headerCountInput == 3) {
        SM_LOG(methodName << "3 headers exist, subtracting medium pressure header process steam usage from its mass flow");

        // if 3 headers, next highest is medium pressure
        const SteamSystemModelerTool::FluidProperties& mediumPressureHeaderOutput =
            mediumPressureHeaderCalculationsDomain->mediumPressureHeaderOutput;
        prvMassFlow = mediumPressureHeaderOutput.massFlow - mediumPressureHeaderInput->getProcessSteamUsage();
        SM_LOG(methodName << "prvMassFlow=" << prvMassFlow);

        if (mediumToLowTurbineInput.isUseTurbine()) {
            SM_LOG(methodName << "using mediumToLowPressureTurbine, subtracting its massFlow from prvMassFlow");
            const std::shared_ptr<Turbine>& mediumToLowPressureTurbine =
                mediumPressureHeaderCalculationsDomain->mediumToLowPressureTurbine;
            prvMassFlow = prvMassFlow - mediumToLowPressureTurbine->getMassFlow();
            SM_LOG(methodName << "updated prvMassFlow=" << prvMassFlow);
        }
    }

    return fmax(prvMassFlow, 0);
}
