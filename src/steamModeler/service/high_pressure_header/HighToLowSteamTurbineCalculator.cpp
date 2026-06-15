#include "steamModeler/service/high_pressure_header/HighToLowSteamTurbineCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

std::shared_ptr<Turbine>
HighToLowSteamTurbineCalculator::calc(const int headerCountInput, const PressureTurbine& highToLowTurbineInput,
                                      const SteamSystemModelerTool::FluidProperties&   highPressureHeaderOutput,
                                      const HeaderWithHighestPressure&                 highPressureHeaderInput,
                                      const CondensingTurbine&                         condensingTurbineInput,
                                      const std::shared_ptr<Turbine>&                  condensingTurbine,
                                      const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                      const Boiler& boiler, const bool isCalcIdeal) const {
    const std::string methodName = std::string("HighToLowSteamTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> highToLowPressureTurbine = nullptr;

    if (headerCountInput > 1 && highToLowTurbineInput.isUseTurbine()) {
        SM_LOG(methodName << "low turbine provided and highToLowTurbineInput isUseTurbine, calculating highToLowPressureTurbine");

        // value for inletMassFlow into turbine calculation; mass flow in header - processSteamUsage
        const double availableMassFlow = calcAvailableMassFlow(highPressureHeaderInput, highPressureHeaderOutput,
                                                               condensingTurbineInput, condensingTurbine);
        SM_LOG(methodName << "availableMassFlow=" << availableMassFlow);
        highToLowPressureTurbine =
            calcHighToLowPressureTurbine(availableMassFlow, highToLowTurbineInput, highPressureHeaderOutput,
                                         lowPressureHeaderInput, boiler, isCalcIdeal);
        SM_LOG(methodName << "highToLowPressureTurbine=" << *highToLowPressureTurbine);
    }
    else {
        SM_LOG(methodName << "low turbine not provided and highToLowTurbineInput not isUseTurbine, skipping");
        SM_LOG(methodName << "highToLowPressureTurbine=null");
    }

    return highToLowPressureTurbine;
}

std::shared_ptr<Turbine> HighToLowSteamTurbineCalculator::calcHighToLowPressureTurbine(
    const double availableMassFlow, const PressureTurbine& highToLowTurbineInput,
    const SteamSystemModelerTool::FluidProperties&   highPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput, const Boiler& boiler,
    const bool isCalcIdeal) const {
    const std::string methodName = std::string("HighToLowSteamTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> highToLowPressureTurbine = nullptr;

    const PressureTurbineOperation& pressureTurbineOperation = highToLowTurbineInput.getOperationType();
    SM_LOG(methodName << "pressureTurbineOperation=" << pressureTurbineOperation);

    switch (pressureTurbineOperation) {
        case PressureTurbineOperation::FLOW_RANGE:
            highToLowPressureTurbine = calcFlowRange(availableMassFlow, highToLowTurbineInput, highPressureHeaderOutput,
                                                     lowPressureHeaderInput, boiler, isCalcIdeal);
            break;
        case PressureTurbineOperation::POWER_RANGE:
            highToLowPressureTurbine =
                calcPowerRange(availableMassFlow, highToLowTurbineInput, highPressureHeaderOutput,
                               lowPressureHeaderInput, boiler, isCalcIdeal);
            break;
        case PressureTurbineOperation::POWER_GENERATION:
            highToLowPressureTurbine =
                calcPowerGeneration(availableMassFlow, highToLowTurbineInput, highPressureHeaderOutput,
                                    lowPressureHeaderInput, boiler, isCalcIdeal);
            break;
        case PressureTurbineOperation::STEAM_FLOW:
            highToLowPressureTurbine = calcSteamFlow(availableMassFlow, highToLowTurbineInput, highPressureHeaderOutput,
                                                     lowPressureHeaderInput, boiler, isCalcIdeal);
            break;
        case PressureTurbineOperation::BALANCE_HEADER:
            highToLowPressureTurbine = calcBalanceHeader(availableMassFlow, highToLowTurbineInput,
                                                         highPressureHeaderOutput, lowPressureHeaderInput, isCalcIdeal);
            break;
        default:
            std::string msg = methodName + "PressureTurbineOperation enum not handled";
            SM_LOG(msg);
            throw std::invalid_argument(msg);
    }

    return highToLowPressureTurbine;
}

std::shared_ptr<Turbine>
HighToLowSteamTurbineCalculator::calcFlowRange(const double                                   availableMassFlow,
                                               const PressureTurbine&                         highToLowTurbineInput,
                                               const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
                                               const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                               const Boiler& boiler, const bool isCalcIdeal) const {
    const std::string methodName = std::string("HighToLowSteamTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> highToLowPressureTurbine = nullptr;

    const double highToLowTurbineInputOperationValue1 = highToLowTurbineInput.getOperationValue1();
    const double highToLowTurbineInputOperationValue2 = highToLowTurbineInput.getOperationValue2();

    // if less steam available then minimum needed
    if (highToLowTurbineInputOperationValue1 > availableMassFlow) {
        SM_LOG(methodName << "highToLowTurbineInputOperationValue1=" << highToLowTurbineInputOperationValue1 << " > availableMassFlow=" << availableMassFlow << ", calculating highToLowPressureTurbine with amount needed (highToLowTurbineInputOperationValue1)" << " instead of amount available");
        highToLowPressureTurbine = turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToLowTurbineInput,
                                                                      highToLowTurbineInputOperationValue1,
                                                                      lowPressureHeaderInput, isCalcIdeal);
        restarter.restartIfNotEnoughSteam(highToLowPressureTurbine, availableMassFlow, boiler);
    }
    else if (highToLowTurbineInputOperationValue2 < availableMassFlow) {
        SM_LOG(methodName << "highToLowTurbineInputOperationValue2=" << highToLowTurbineInputOperationValue2 << " < availableMassFlow=" << availableMassFlow << ", calculating highToLowPressureTurbine with max amount allowed (highToLowTurbineInputOperationValue2)" << " instead of amount available");
        highToLowPressureTurbine = turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToLowTurbineInput,
                                                                      highToLowTurbineInputOperationValue2,
                                                                      lowPressureHeaderInput, isCalcIdeal);
    }
    else {
        SM_LOG(methodName << "availableMassFlow=" << availableMassFlow << " is between needed and max amounts," << " calculating highToLowPressureTurbine with availableMassFlow");
        highToLowPressureTurbine = turbineFactory.makePtrWithMassFlow(
            highPressureHeaderOutput, highToLowTurbineInput, availableMassFlow, lowPressureHeaderInput, isCalcIdeal);
    }

    return highToLowPressureTurbine;
}

std::shared_ptr<Turbine>
HighToLowSteamTurbineCalculator::calcPowerRange(const double                                   availableMassFlow,
                                                const PressureTurbine&                         highToLowTurbineInput,
                                                const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
                                                const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                                const Boiler& boiler, const bool isCalcIdeal) const {
    const std::string methodName = std::string("HighToLowSteamTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> highToLowPressureTurbine = nullptr;

    const double highToLowTurbineInputOperationValue1 = highToLowTurbineInput.getOperationValue1();
    const double highToLowTurbineInputOperationValue2 = highToLowTurbineInput.getOperationValue2();

    SM_LOG(methodName << "calculating highToLowPressureTurbine with availableMassFlow=" << availableMassFlow);
    highToLowPressureTurbine = turbineFactory.makePtrWithMassFlow(
        highPressureHeaderOutput, highToLowTurbineInput, availableMassFlow, lowPressureHeaderInput, isCalcIdeal);

    // check that power out is in range
    const double highToLowPressureTurbinePowerOut = highToLowPressureTurbine->getPowerOut();
    if (highToLowTurbineInputOperationValue1 > highToLowPressureTurbinePowerOut) {
        SM_LOG(methodName << "highToLowTurbineInputOperationValue1=" << highToLowTurbineInputOperationValue1 << " > highToLowPressureTurbinePowerOut=" << highToLowPressureTurbinePowerOut << " not enough power out of turbine," << " calculating highToLowPressureTurbine with amount needed instead of amount available");
        double currentSteamAvailable = highToLowPressureTurbine->getMassFlow();
        highToLowPressureTurbine = turbineFactory.makePtrWithPowerOut(highPressureHeaderOutput, highToLowTurbineInput,
                                                                      highToLowTurbineInputOperationValue1,
                                                                      lowPressureHeaderInput, isCalcIdeal);
        restarter.restartIfNotEnoughSteam(highToLowPressureTurbine, currentSteamAvailable, boiler);
    }
    else if (highToLowTurbineInputOperationValue2 < highToLowPressureTurbinePowerOut) {
        SM_LOG(methodName << "highToLowTurbineInputOperationValue2=" << highToLowTurbineInputOperationValue2 << " < highToLowPressureTurbinePowerOut=" << highToLowPressureTurbinePowerOut << ", calculating highToLowPressureTurbine with max amount allowed (highToLowTurbineInputOperationValue2)" << " instead of amount available");
        // calculateThermalResistance turbine with max power out value
        highToLowPressureTurbine = turbineFactory.makePtrWithPowerOut(highPressureHeaderOutput, highToLowTurbineInput,
                                                                      highToLowTurbineInputOperationValue2,
                                                                      lowPressureHeaderInput, isCalcIdeal);
    }

    return highToLowPressureTurbine;
}

std::shared_ptr<Turbine> HighToLowSteamTurbineCalculator::calcPowerGeneration(
    const double availableMassFlow, const PressureTurbine& highToLowTurbineInput,
    const SteamSystemModelerTool::FluidProperties&   highPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput, const Boiler& boiler,
    const bool isCalcIdeal) const {
    const std::string methodName = std::string("HighToLowSteamTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> highToLowPressureTurbine = nullptr;

    const double highToLowTurbineInputOperationValue1 = highToLowTurbineInput.getOperationValue1();

    SM_LOG(methodName << "calculating highToLowPressureTurbine with power out (highToLowTurbineInputOperationValue1)=" << highToLowTurbineInputOperationValue1);
    highToLowPressureTurbine =
        turbineFactory.makePtrWithPowerOut(highPressureHeaderOutput, highToLowTurbineInput,
                                           highToLowTurbineInputOperationValue1, lowPressureHeaderInput, isCalcIdeal);
    steamBalanceCheckerService.check(highToLowPressureTurbine, availableMassFlow, boiler);

    return highToLowPressureTurbine;
}

std::shared_ptr<Turbine>
HighToLowSteamTurbineCalculator::calcSteamFlow(const double                                   availableMassFlow,
                                               const PressureTurbine&                         highToLowTurbineInput,
                                               const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
                                               const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                               const Boiler& boiler, const bool isCalcIdeal) const {
    const std::string methodName = std::string("HighToLowSteamTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> highToLowPressureTurbine = nullptr;

    const double highToLowTurbineInputOperationValue1 = highToLowTurbineInput.getOperationValue1();

    SM_LOG(methodName << "calculating highToLowPressureTurbine with mass flow (highToLowTurbineInputOperationValue1)=" << highToLowTurbineInputOperationValue1);
    highToLowPressureTurbine =
        turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToLowTurbineInput,
                                           highToLowTurbineInputOperationValue1, lowPressureHeaderInput, isCalcIdeal);
    steamBalanceCheckerService.check(highToLowPressureTurbine, availableMassFlow, boiler);

    return highToLowPressureTurbine;
}

std::shared_ptr<Turbine> HighToLowSteamTurbineCalculator::calcBalanceHeader(
    const double availableMassFlow, const PressureTurbine& highToLowTurbineInput,
    const SteamSystemModelerTool::FluidProperties&   highPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput, const bool isCalcIdeal) const {
    const std::string methodName = std::string("HighToLowSteamTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> highToLowPressureTurbine = nullptr;

    SM_LOG(methodName << "calculating highToLowPressureTurbine with availableMassFlow=" << availableMassFlow);
    highToLowPressureTurbine = turbineFactory.makePtrWithMassFlow(
        highPressureHeaderOutput, highToLowTurbineInput, availableMassFlow, lowPressureHeaderInput, isCalcIdeal);

    return highToLowPressureTurbine;
}

double HighToLowSteamTurbineCalculator::calcAvailableMassFlow(
    const HeaderWithHighestPressure&               highPressureHeaderInput,
    const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
    const CondensingTurbine& condensingTurbineInput, const std::shared_ptr<Turbine>& condensingTurbine) const {
    const std::string methodName = std::string("HighToLowSteamTurbineCalculator::") + std::string(__func__) + ": ";

    const double highPressureHeaderOutputMassFlow         = highPressureHeaderOutput.massFlow;
    const double highPressureHeaderInputProcessSteamUsage = highPressureHeaderInput.getProcessSteamUsage();
    double       availableMassFlow = highPressureHeaderOutputMassFlow - highPressureHeaderInputProcessSteamUsage;
    SM_LOG(methodName << "highPressureHeaderOutputMassFlow=" << highPressureHeaderOutputMassFlow << " - highPressureHeaderInputProcessSteamUsage=" << highPressureHeaderInputProcessSteamUsage << " = availableMassFlow=" << availableMassFlow);

    // remove steam that goes through condensing turbine
    if (condensingTurbineInput.isUseTurbine()) {
        const double condensingTurbineMassFlow = condensingTurbine->getMassFlow();
        availableMassFlow -= condensingTurbineMassFlow;
        SM_LOG(methodName << "subtracting condensingTurbineMassFlow=" << condensingTurbineMassFlow << " = availableMassFlow=" << availableMassFlow);
    }

    return availableMassFlow;
}
