#include <steamModeler/service/medium_pressure_header/MediumToLowPressureTurbineCalculator.h>
#include "steamModeler/util/SteamModelerLogger.h"

MediumToLowPressureTurbineCalculatorOutput MediumToLowPressureTurbineCalculator::calc(
    const PressureTurbine& highToLowTurbineInput, const std::shared_ptr<Turbine>& highToLowPressureTurbine,
    const std::shared_ptr<Turbine>& highToLowPressureTurbineIdeal, const PressureTurbine& mediumToLowTurbineInput,
    const SteamSystemModelerTool::FluidProperties&   highPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const SteamSystemModelerTool::FluidProperties&   mediumPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput, const Boiler& boiler) const {
    const std::string methodName = std::string("MediumToLowPressureTurbineCalculator::") + std::string(__func__) + ": ";

    MediumToLowPressureTurbineCalculatorOutput mediumToLowPressureTurbineCalculatorOutput;

    if (mediumToLowTurbineInput.isUseTurbine()) {
        SM_LOG(methodName << "medium to low turbine input provided and mediumToLowTurbineInput isUseTurbine," << " calculating mediumToLowPressureTurbine");

        double availableMassFlow = calcAvailableMassFlow(mediumPressureHeaderInput, mediumPressureHeaderOutput);
        SM_LOG(methodName << "availableMassFlow" << availableMassFlow);

        mediumToLowPressureTurbineCalculatorOutput =
            calc(availableMassFlow, highToLowTurbineInput, highToLowPressureTurbine, highToLowPressureTurbineIdeal,
                 highPressureHeaderOutput, mediumToLowTurbineInput, mediumPressureHeaderOutput, lowPressureHeaderInput,
                 boiler);
    }
    else {
        SM_LOG(methodName << "medium to low turbine input not provided and mediumToLowTurbineInput not isUseTurbine, skipping");
        const std::shared_ptr<Turbine> mediumToLowPressureTurbine      = nullptr;
        const std::shared_ptr<Turbine> mediumToLowPressureTurbineIdeal = nullptr;
        mediumToLowPressureTurbineCalculatorOutput = {mediumToLowPressureTurbine, mediumToLowPressureTurbineIdeal,
                                                      highToLowPressureTurbine, highToLowPressureTurbineIdeal};
    }

    return mediumToLowPressureTurbineCalculatorOutput;
}

MediumToLowPressureTurbineCalculatorOutput
MediumToLowPressureTurbineCalculator::calc(const double availableMassFlow, const PressureTurbine& highToLowTurbineInput,
                                           const std::shared_ptr<Turbine>&                highToLowPressureTurbine,
                                           const std::shared_ptr<Turbine>&                highToLowPressureTurbineIdeal,
                                           const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
                                           const PressureTurbine&                         mediumToLowTurbineInput,
                                           const SteamSystemModelerTool::FluidProperties& mediumPressureHeaderOutput,
                                           const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                           const Boiler&                                    boiler) const {
    const std::string methodName = std::string("MediumToLowPressureTurbineCalculator::") + std::string(__func__) + ": ";

    MediumToLowPressureTurbineCalculatorOutput mediumToLowPressureTurbineCalculatorOutput;

    const PressureTurbineOperation& pressureTurbineOperation = mediumToLowTurbineInput.getOperationType();
    SM_LOG(methodName << "pressureTurbineOperation=" << pressureTurbineOperation);

    switch (pressureTurbineOperation) {
        case PressureTurbineOperation::FLOW_RANGE:
            mediumToLowPressureTurbineCalculatorOutput =
                calcFlowRange(availableMassFlow, mediumToLowTurbineInput, mediumPressureHeaderOutput,
                              lowPressureHeaderInput, boiler, highToLowTurbineInput, highToLowPressureTurbine,
                              highToLowPressureTurbineIdeal, highPressureHeaderOutput);
            break;
        case PressureTurbineOperation::POWER_RANGE:
            mediumToLowPressureTurbineCalculatorOutput =
                calcPowerRange(availableMassFlow, mediumToLowTurbineInput, mediumPressureHeaderOutput,
                               lowPressureHeaderInput, boiler, highToLowTurbineInput, highToLowPressureTurbine,
                               highToLowPressureTurbineIdeal, highPressureHeaderOutput);
            break;
        case PressureTurbineOperation::POWER_GENERATION:
            mediumToLowPressureTurbineCalculatorOutput =
                calcPowerGeneration(availableMassFlow, mediumToLowTurbineInput, mediumPressureHeaderOutput,
                                    lowPressureHeaderInput, boiler, highToLowTurbineInput, highToLowPressureTurbine,
                                    highToLowPressureTurbineIdeal, highPressureHeaderOutput);
            break;
        case PressureTurbineOperation::STEAM_FLOW:
            mediumToLowPressureTurbineCalculatorOutput =
                calcSteamFlow(availableMassFlow, mediumToLowTurbineInput, mediumPressureHeaderOutput,
                              lowPressureHeaderInput, boiler, highToLowTurbineInput, highToLowPressureTurbine,
                              highToLowPressureTurbineIdeal, highPressureHeaderOutput);
            break;
        case PressureTurbineOperation::BALANCE_HEADER:
            mediumToLowPressureTurbineCalculatorOutput =
                calcBalanceHeader(availableMassFlow, mediumToLowTurbineInput, mediumPressureHeaderOutput,
                                  lowPressureHeaderInput, highToLowPressureTurbine, highToLowPressureTurbineIdeal);
            break;
        default:
            std::string msg = methodName + "PressureTurbineOperation enum not handled";
            SM_LOG(msg);
            throw std::invalid_argument(msg);
    }

    return mediumToLowPressureTurbineCalculatorOutput;
}

MediumToLowPressureTurbineCalculatorOutput MediumToLowPressureTurbineCalculator::calcFlowRange(
    const double availableMassFlow, const PressureTurbine& mediumToLowTurbineInput,
    const SteamSystemModelerTool::FluidProperties&   mediumPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput, const Boiler& boiler,
    const PressureTurbine& highToLowTurbineInput, const std::shared_ptr<Turbine>& highToLowPressureTurbine,
    const std::shared_ptr<Turbine>&                highToLowPressureTurbineIdeal,
    const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput) const {
    const std::string methodName = std::string("MediumToLowPressureTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> mediumToLowPressureTurbine           = nullptr;
    std::shared_ptr<Turbine> mediumToLowPressureTurbineIdeal      = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated      = highToLowPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated = highToLowPressureTurbineIdeal;

    const double mediumToLowTurbineInputOperationValue1 = mediumToLowTurbineInput.getOperationValue1();
    const double mediumToLowTurbineInputOperationValue2 = mediumToLowTurbineInput.getOperationValue2();

    // if minimum amount needed is greater than available amount
    if (mediumToLowTurbineInputOperationValue1 > availableMassFlow) {
        SM_LOG(methodName << "mediumToLowTurbineInputOperationValue1=" << mediumToLowTurbineInputOperationValue1 << " > availableMassFlow=" << availableMassFlow << ", calculating mediumToLowPressureTurbine with amount needed (mediumToLowTurbineInputOperationValue1)" << " instead of amount available");
        // calculateThermalResistance turbine with amount needed
        mediumToLowPressureTurbine =
            turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput, false);
        mediumToLowPressureTurbineIdeal =
            turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput, true);

        const double              neededMassFlow     = mediumToLowPressureTurbine->getMassFlow();
        const SteamReducerOutput& steamReducerOutput = steamBalanceCheckerService.check(
            "mediumToLowPressureTurbine", highToLowTurbineInput, lowPressureHeaderInput, boiler,
            highToLowPressureTurbine, highToLowPressureTurbineIdeal, highPressureHeaderOutput, neededMassFlow,
            availableMassFlow);
        SM_LOG(methodName << "steamReducerOutput=" << steamReducerOutput);
        highToLowPressureTurbineUpdated      = steamReducerOutput.highToLowPressureTurbineUpdated;
        highToLowPressureTurbineIdealUpdated = steamReducerOutput.highToLowPressureTurbineIdealUpdated;
    }
    else if (mediumToLowTurbineInputOperationValue2 < availableMassFlow) {
        SM_LOG(methodName << "mediumToLowTurbineInputOperationValue2=" << mediumToLowTurbineInputOperationValue2 << " < availableMassFlow=" << availableMassFlow << ", calculating mediumToLowPressureTurbine with max amount allowed (mediumToLowTurbineInputOperationValue2)" << " instead of the greater amount available");
        mediumToLowPressureTurbine =
            turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               mediumToLowTurbineInputOperationValue2, lowPressureHeaderInput, false);
        mediumToLowPressureTurbineIdeal =
            turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               mediumToLowTurbineInputOperationValue2, lowPressureHeaderInput, true);
    }
    else {
        SM_LOG(methodName << "availableMassFlow=" << availableMassFlow << " is between needed and max amounts," << " calculating mediumToLowPressureTurbine with availableMassFlow");
        mediumToLowPressureTurbine = turbineFactory.makePtrWithMassFlow(
            mediumPressureHeaderOutput, mediumToLowTurbineInput, availableMassFlow, lowPressureHeaderInput, false);
        mediumToLowPressureTurbineIdeal = turbineFactory.makePtrWithMassFlow(
            mediumPressureHeaderOutput, mediumToLowTurbineInput, availableMassFlow, lowPressureHeaderInput, true);
    }

    SM_LOG(methodName << "mediumToLowPressureTurbine=" << mediumToLowPressureTurbine);
    SM_LOG(methodName << "mediumToLowPressureTurbineIdeal=" << mediumToLowPressureTurbineIdeal);

    return {mediumToLowPressureTurbine, mediumToLowPressureTurbineIdeal, highToLowPressureTurbineUpdated,
            highToLowPressureTurbineIdealUpdated};
}

MediumToLowPressureTurbineCalculatorOutput MediumToLowPressureTurbineCalculator::calcPowerRange(
    const double availableMassFlow, const PressureTurbine& mediumToLowTurbineInput,
    const SteamSystemModelerTool::FluidProperties&   mediumPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput, const Boiler& boiler,
    const PressureTurbine& highToLowTurbineInput, const std::shared_ptr<Turbine>& highToLowPressureTurbine,
    const std::shared_ptr<Turbine>&                highToLowPressureTurbineIdeal,
    const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput) const {
    const std::string methodName = std::string("MediumToLowPressureTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> mediumToLowPressureTurbine           = nullptr;
    std::shared_ptr<Turbine> mediumToLowPressureTurbineIdeal      = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated      = highToLowPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated = highToLowPressureTurbineIdeal;

    const double mediumToLowTurbineInputOperationValue1 = mediumToLowTurbineInput.getOperationValue1();
    const double mediumToLowTurbineInputOperationValue2 = mediumToLowTurbineInput.getOperationValue2();

    SM_LOG(methodName << "calculating mediumToLowPressureTurbine with availableMassFlow=" << availableMassFlow);
    mediumToLowPressureTurbine = turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                                                    availableMassFlow, lowPressureHeaderInput, false);
    mediumToLowPressureTurbineIdeal = turbineFactory.makePtrWithMassFlow(
        mediumPressureHeaderOutput, mediumToLowTurbineInput, availableMassFlow, lowPressureHeaderInput, true);
    // check that power out is in range
    const double mediumToLowPressureTurbinePowerOut = mediumToLowPressureTurbine->getPowerOut();
    if (mediumToLowTurbineInputOperationValue1 > mediumToLowPressureTurbinePowerOut) {
        SM_LOG(methodName << "mediumToLowTurbineInputOperationValue1=" << mediumToLowTurbineInputOperationValue1 << " > mediumToLowPressureTurbinePowerOut=" << mediumToLowPressureTurbinePowerOut << "; not enough power out of turbine," << " calculating mediumToLowPressureTurbine with amount needed instead of amount available");
        // calculateThermalResistance minimum mass flow needed
        mediumToLowPressureTurbine =
            turbineFactory.makePtrWithPowerOut(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput, false);
        mediumToLowPressureTurbineIdeal =
            turbineFactory.makePtrWithPowerOut(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput, true);
        const double              neededMassFlow     = mediumToLowPressureTurbine->getMassFlow();
        const SteamReducerOutput& steamReducerOutput = steamBalanceCheckerService.check(
            "mediumToLowPressureTurbine", highToLowTurbineInput, lowPressureHeaderInput, boiler,
            highToLowPressureTurbine, highToLowPressureTurbineIdeal, highPressureHeaderOutput, neededMassFlow,
            availableMassFlow);
        SM_LOG(methodName << "steamReducerOutput=" << steamReducerOutput);
        highToLowPressureTurbineUpdated      = steamReducerOutput.highToLowPressureTurbineUpdated;
        highToLowPressureTurbineIdealUpdated = steamReducerOutput.highToLowPressureTurbineIdealUpdated;
    }
    else if (mediumToLowTurbineInputOperationValue2 < mediumToLowPressureTurbinePowerOut) {
        SM_LOG(methodName << "mediumToLowTurbineInputOperationValue2=" << mediumToLowTurbineInputOperationValue2 << " < mediumToLowPressureTurbinePowerOut=" << mediumToLowPressureTurbinePowerOut << " not enough power out of turbine," << " calculating mediumToLowPressureTurbine with amount needed instead of amount available");
        // if power out with available mass flow is greater than max, calculateThermalResistance turbine with max power
        // out
        mediumToLowPressureTurbine =
            turbineFactory.makePtrWithPowerOut(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               mediumToLowTurbineInputOperationValue2, lowPressureHeaderInput, false);
        mediumToLowPressureTurbineIdeal =
            turbineFactory.makePtrWithPowerOut(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               mediumToLowTurbineInputOperationValue2, lowPressureHeaderInput, true);
    }

    SM_LOG(methodName << "mediumToLowPressureTurbine=" << mediumToLowPressureTurbine);
    SM_LOG(methodName << "mediumToLowPressureTurbineIdeal=" << mediumToLowPressureTurbineIdeal);

    return {mediumToLowPressureTurbine, mediumToLowPressureTurbineIdeal, highToLowPressureTurbineUpdated,
            highToLowPressureTurbineIdealUpdated};
}

MediumToLowPressureTurbineCalculatorOutput MediumToLowPressureTurbineCalculator::calcPowerGeneration(
    const double availableMassFlow, const PressureTurbine& mediumToLowTurbineInput,
    const SteamSystemModelerTool::FluidProperties&   mediumPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput, const Boiler& boiler,
    const PressureTurbine& highToLowTurbineInput, const std::shared_ptr<Turbine>& highToLowPressureTurbine,
    const std::shared_ptr<Turbine>&                highToLowPressureTurbineIdeal,
    const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput) const {
    const std::string methodName = std::string("MediumToLowPressureTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> mediumToLowPressureTurbine           = nullptr;
    std::shared_ptr<Turbine> mediumToLowPressureTurbineIdeal      = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated      = highToLowPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated = highToLowPressureTurbineIdeal;

    const double mediumToLowTurbineInputOperationValue1 = mediumToLowTurbineInput.getOperationValue1();

    // calculateThermalResistance turbine with set amount of power out
    mediumToLowPressureTurbine =
        turbineFactory.makePtrWithPowerOut(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                           mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput, false);
    mediumToLowPressureTurbineIdeal =
        turbineFactory.makePtrWithPowerOut(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                           mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput, true);

    // check enough available steam for set power out
    const double mediumToLowPressureTurbineMassFlow = mediumToLowPressureTurbine->getMassFlow();
    if (mediumToLowPressureTurbineMassFlow > availableMassFlow) {
        const double              neededMassFlow     = mediumToLowPressureTurbine->getMassFlow();
        const SteamReducerOutput& steamReducerOutput = steamBalanceCheckerService.check(
            "mediumToLowPressureTurbine", highToLowTurbineInput, lowPressureHeaderInput, boiler,
            highToLowPressureTurbine, highToLowPressureTurbineIdeal, highPressureHeaderOutput, neededMassFlow,
            availableMassFlow);
        SM_LOG(methodName << "steamReducerOutput=" << steamReducerOutput);
        highToLowPressureTurbineUpdated      = steamReducerOutput.highToLowPressureTurbineUpdated;
        highToLowPressureTurbineIdealUpdated = steamReducerOutput.highToLowPressureTurbineIdealUpdated;
    }

    SM_LOG(methodName << "mediumToLowPressureTurbine=" << mediumToLowPressureTurbine);
    SM_LOG(methodName << "mediumToLowPressureTurbineIdeal=" << mediumToLowPressureTurbineIdeal);

    return {mediumToLowPressureTurbine, mediumToLowPressureTurbineIdeal, highToLowPressureTurbineUpdated,
            highToLowPressureTurbineIdealUpdated};
}

MediumToLowPressureTurbineCalculatorOutput MediumToLowPressureTurbineCalculator::calcSteamFlow(
    const double availableMassFlow, const PressureTurbine& mediumToLowTurbineInput,
    const SteamSystemModelerTool::FluidProperties&   mediumPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput, const Boiler& boiler,
    const PressureTurbine& highToLowTurbineInput, const std::shared_ptr<Turbine>& highToLowPressureTurbine,
    const std::shared_ptr<Turbine>&                highToLowPressureTurbineIdeal,
    const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput) const {
    const std::string methodName = std::string("MediumToLowPressureTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> mediumToLowPressureTurbine           = nullptr;
    std::shared_ptr<Turbine> mediumToLowPressureTurbineIdeal      = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated      = highToLowPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated = highToLowPressureTurbineIdeal;

    const double mediumToLowTurbineInputOperationValue1 = mediumToLowTurbineInput.getOperationValue1();

    // calculateThermalResistance turbine with set mass flow
    mediumToLowPressureTurbine =
        turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                           mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput, false);
    mediumToLowPressureTurbineIdeal =
        turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                           mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput, true);

    // check enough available steam for set mass flow
    const double mediumToLowPressureTurbineMassFlow = mediumToLowPressureTurbine->getMassFlow();
    if (mediumToLowPressureTurbineMassFlow > availableMassFlow) {
        const double              neededMassFlow     = mediumToLowPressureTurbine->getMassFlow();
        const SteamReducerOutput& steamReducerOutput = steamBalanceCheckerService.check(
            "mediumToLowPressureTurbine", highToLowTurbineInput, lowPressureHeaderInput, boiler,
            highToLowPressureTurbine, highToLowPressureTurbineIdeal, highPressureHeaderOutput, neededMassFlow,
            availableMassFlow);
        SM_LOG(methodName << "steamReducerOutput=" << steamReducerOutput);
        highToLowPressureTurbineUpdated      = steamReducerOutput.highToLowPressureTurbineUpdated;
        highToLowPressureTurbineIdealUpdated = steamReducerOutput.highToLowPressureTurbineIdealUpdated;
    }

    SM_LOG(methodName << "mediumToLowPressureTurbine=" << mediumToLowPressureTurbine);
    SM_LOG(methodName << "mediumToLowPressureTurbineIdeal=" << mediumToLowPressureTurbineIdeal);

    return {mediumToLowPressureTurbine, mediumToLowPressureTurbineIdeal, highToLowPressureTurbineUpdated,
            highToLowPressureTurbineIdealUpdated};
}

MediumToLowPressureTurbineCalculatorOutput MediumToLowPressureTurbineCalculator::calcBalanceHeader(
    const double availableMassFlow, const PressureTurbine& mediumToLowTurbineInput,
    const SteamSystemModelerTool::FluidProperties&   mediumPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const std::shared_ptr<Turbine>&                  highToLowPressureTurbine,
    const std::shared_ptr<Turbine>&                  highToLowPressureTurbineIdeal) const {
    const std::string methodName = std::string("MediumToLowPressureTurbineCalculator::") + std::string(__func__) + ": ";

    // balance header send through what is available
    std::shared_ptr<Turbine> mediumToLowPressureTurbine = turbineFactory.makePtrWithMassFlow(
        mediumPressureHeaderOutput, mediumToLowTurbineInput, availableMassFlow, lowPressureHeaderInput, false);
    std::shared_ptr<Turbine> mediumToLowPressureTurbineIdeal = turbineFactory.makePtrWithMassFlow(
        mediumPressureHeaderOutput, mediumToLowTurbineInput, availableMassFlow, lowPressureHeaderInput, true);

    SM_LOG(methodName << "mediumToLowPressureTurbine=" << mediumToLowPressureTurbine);
    SM_LOG(methodName << "mediumToLowPressureTurbineIdeal=" << mediumToLowPressureTurbineIdeal);

    return {mediumToLowPressureTurbine, mediumToLowPressureTurbineIdeal, highToLowPressureTurbine,
            highToLowPressureTurbineIdeal};
}

double MediumToLowPressureTurbineCalculator::calcAvailableMassFlow(
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const SteamSystemModelerTool::FluidProperties&   mediumPressureHeaderOutput) const {
    return mediumPressureHeaderOutput.massFlow - mediumPressureHeaderInput->getProcessSteamUsage();
}
