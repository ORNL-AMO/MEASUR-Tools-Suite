#include "steamModeler/service/SteamReducer.h"
#include "steamModeler/util/SteamModelerLogger.h"

SteamReducerOutput SteamReducer::reduceSteamThroughHighToLowTurbine(
    const double additionalSteamNeeded, const PressureTurbine& highToLowTurbineInput,
    const std::shared_ptr<Turbine>&                  highToLowPressureTurbine,
    const std::shared_ptr<Turbine>&                  highToLowPressureTurbineIdeal,
    const SteamSystemModelerTool::FluidProperties&   highPressureHeaderOutput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput) const {
    const std::string methodName = std::string("SteamReducer::") + std::string(__func__) + ": ";

    SteamReducerOutput steamReducerOutput;

    // if the turbine is in use
    if (highToLowTurbineInput.isUseTurbine()) {
        const PressureTurbineOperation& pressureTurbineOperation = highToLowTurbineInput.getOperationType();
        SM_LOG(methodName << "pressureTurbineOperation=" << pressureTurbineOperation);

        switch (pressureTurbineOperation) {
            case PressureTurbineOperation::FLOW_RANGE:
                steamReducerOutput =
                    reduceFlowRange(additionalSteamNeeded, highToLowTurbineInput, highToLowPressureTurbine,
                                    highToLowPressureTurbineIdeal, highPressureHeaderOutput, lowPressureHeaderInput);
                break;
            case PressureTurbineOperation::POWER_RANGE:
                steamReducerOutput =
                    reducePowerRange(additionalSteamNeeded, highToLowTurbineInput, highToLowPressureTurbine,
                                     highToLowPressureTurbineIdeal, highPressureHeaderOutput, lowPressureHeaderInput);
                break;
            case PressureTurbineOperation::POWER_GENERATION:
                SM_LOG(methodName << "pressureTurbineOperation is POWER_GENERATION," << " skipping reducing as fixed steam cannot reduce steam through turbine");
                steamReducerOutput = {additionalSteamNeeded, highToLowPressureTurbine, highToLowPressureTurbineIdeal};
                break;
            case PressureTurbineOperation::STEAM_FLOW:
                SM_LOG(methodName << "pressureTurbineOperation is STEAM_FLOW," << " skipping reducing as fixed steam cannot reduce steam through turbine");
                steamReducerOutput = {additionalSteamNeeded, highToLowPressureTurbine, highToLowPressureTurbineIdeal};
                break;
            case PressureTurbineOperation::BALANCE_HEADER:
                steamReducerOutput = reduceBalanceHeader(additionalSteamNeeded, highToLowTurbineInput,
                                                         highToLowPressureTurbine, highToLowPressureTurbineIdeal,
                                                         highPressureHeaderOutput, lowPressureHeaderInput);
                break;
            default:
                std::string msg = methodName + "PressureTurbineOperation enum not handled";
                SM_LOG(msg);
                throw std::invalid_argument(msg);
        }
    }
    else {
        SM_LOG(methodName << "high to low turbine not provided, skipping reducing");
        steamReducerOutput = {additionalSteamNeeded, highToLowPressureTurbine, highToLowPressureTurbineIdeal};
    }

    SM_LOG(methodName << "remainingAdditionalSteamNeeded=" << steamReducerOutput.remainingAdditionalSteamNeeded);

    return steamReducerOutput;
}

SteamReducerOutput
SteamReducer::reduceBalanceHeader(const double additionalSteamNeeded, const PressureTurbine& highToLowTurbineInput,
                                  const std::shared_ptr<Turbine>&                  highToLowPressureTurbine,
                                  const std::shared_ptr<Turbine>&                  highToLowPressureTurbineIdeal,
                                  const SteamSystemModelerTool::FluidProperties&   highPressureHeaderOutput,
                                  const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput) const {
    const std::string methodName = std::string("SteamReducer::") + std::string(__func__) + ": ";

    double                   remainingAdditionalSteamNeeded       = additionalSteamNeeded;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated      = highToLowPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated = highToLowPressureTurbineIdeal;

    // balance header, all steam is available to be taken
    const double availableSteam = highToLowPressureTurbine->getMassFlow();
    const double remainingSteam = availableSteam - additionalSteamNeeded;
    SM_LOG(methodName << "availableSteam=" << availableSteam << " - additionalSteamNeeded=" << additionalSteamNeeded << "; resulting remainingSteam=" << remainingSteam);

    double massFlow = remainingSteam;
    // if all steam can be taken,
    if (remainingSteam >= 0) {
        // all additional steam needed was taken from turbine, no additional steam needed
        remainingAdditionalSteamNeeded = 0;
    }
    else {
        // take all steam from turbine
        massFlow = 0;
        // steam still needed = needed steam - amount taken (which is everything)
        remainingAdditionalSteamNeeded = additionalSteamNeeded - availableSteam;
    }

    SM_LOG(methodName << "remainingAdditionalSteamNeeded=" << remainingAdditionalSteamNeeded);

    SM_LOG(methodName << "calculating highToLowPressureTurbine with massFlow=" << massFlow);
    highToLowPressureTurbineUpdated = turbineFactory.makePtrWithMassFlow(
        highPressureHeaderOutput, highToLowTurbineInput, massFlow, lowPressureHeaderInput, false);
    SM_LOG(methodName << "highToLowPressureTurbineUpdated=" << highToLowPressureTurbineUpdated);

    SM_LOG(methodName << "calculating highToLowPressureTurbineIdeal with massFlow=" << massFlow);
    highToLowPressureTurbineIdealUpdated = turbineFactory.makePtrWithMassFlow(
        highPressureHeaderOutput, highToLowTurbineInput, massFlow, lowPressureHeaderInput, true);
    SM_LOG(methodName << "highToLowPressureTurbineIdealUpdated=" << highToLowPressureTurbineIdealUpdated);

    return {remainingAdditionalSteamNeeded, highToLowPressureTurbineUpdated, highToLowPressureTurbineIdealUpdated};
}

SteamReducerOutput
SteamReducer::reducePowerRange(const double additionalSteamNeeded, const PressureTurbine& highToLowTurbineInput,
                               const std::shared_ptr<Turbine>&                  highToLowPressureTurbine,
                               const std::shared_ptr<Turbine>&                  highToLowPressureTurbineIdeal,
                               const SteamSystemModelerTool::FluidProperties&   highPressureHeaderOutput,
                               const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput) const {
    const std::string methodName = std::string("SteamReducer::") + std::string(__func__) + ": ";

    double                   remainingAdditionalSteamNeeded       = additionalSteamNeeded;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated      = highToLowPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated = highToLowPressureTurbineIdeal;

    // if current power out is greater than the minimum amount needed there is steam available
    const double highToLowPressureTurbinePowerOut     = highToLowPressureTurbine->getPowerOut();
    const double highToLowTurbineInputOperationValue1 = highToLowTurbineInput.getOperationValue1();

    if (highToLowPressureTurbinePowerOut > highToLowTurbineInputOperationValue1) {
        // calculateThermalResistance amount of steam taken when reducing power out to minimum
        const double previousMassFlow = highToLowPressureTurbine->getMassFlow();

        // calculateThermalResistance header using minimum power out needed
        SM_LOG(methodName << "calculating highToLowPressureTurbine with minimum power out needed (highToLowTurbineInputOperationValue1)=" << highToLowTurbineInputOperationValue1);
        highToLowPressureTurbineUpdated =
            turbineFactory.makePtrWithPowerOut(highPressureHeaderOutput, highToLowTurbineInput,
                                               highToLowTurbineInputOperationValue1, lowPressureHeaderInput, false);
        SM_LOG(methodName << "highToLowPressureTurbineUpdated=" << highToLowPressureTurbineUpdated);

        SM_LOG(methodName << "calculating highToLowPressureTurbineIdeal with minimum power out needed (highToLowTurbineInputOperationValue1)=" << highToLowTurbineInputOperationValue1);
        highToLowPressureTurbineIdealUpdated =
            turbineFactory.makePtrWithPowerOut(highPressureHeaderOutput, highToLowTurbineInput,
                                               highToLowTurbineInputOperationValue1, lowPressureHeaderInput, true);
        SM_LOG(methodName << "highToLowPressureTurbineIdealUpdated=" << highToLowPressureTurbineIdealUpdated);

        // amount reduced = previous mass flow - mass flow at min need
        const double highToLowPressureTurbineMassFlow = highToLowPressureTurbineUpdated->getMassFlow();
        const double massFlowReduction                = previousMassFlow - highToLowPressureTurbineMassFlow;

        // amount of steam take = needed steam - amount reduced
        const double newSteamNeed = additionalSteamNeeded - massFlowReduction;

        // if excess amount of steam was taken than needed when reducing, put excess steam taken back into turbine
        if (newSteamNeed < 0) {
            const double massFlow = highToLowPressureTurbineMassFlow + fabs(newSteamNeed);
            SM_LOG(methodName << "calculating highToLowPressureTurbine, returning excess steam amount, with mass flow=" << massFlow);
            highToLowPressureTurbineUpdated = turbineFactory.makePtrWithMassFlow(
                highPressureHeaderOutput, highToLowTurbineInput, massFlow, lowPressureHeaderInput, false);
            SM_LOG(methodName << "highToLowPressureTurbineUpdated=" << highToLowPressureTurbineUpdated);

            SM_LOG(methodName << "calculating highToLowPressureTurbineIdeal, returning excess steam amount, with mass flow=" << massFlow);
            highToLowPressureTurbineIdealUpdated = turbineFactory.makePtrWithMassFlow(
                highPressureHeaderOutput, highToLowTurbineInput, massFlow, lowPressureHeaderInput, true);
            SM_LOG(methodName << "highToLowPressureTurbineIdealUpdated=" << highToLowPressureTurbineIdealUpdated);

            remainingAdditionalSteamNeeded = 0;
        }
        else {
            // return new steam need
            remainingAdditionalSteamNeeded = newSteamNeed;
        }
    }
    else {
        // no steam available from turbine
        remainingAdditionalSteamNeeded = additionalSteamNeeded;
    }

    return {remainingAdditionalSteamNeeded, highToLowPressureTurbineUpdated, highToLowPressureTurbineIdealUpdated};
}

SteamReducerOutput
SteamReducer::reduceFlowRange(const double additionalSteamNeeded, const PressureTurbine& highToLowTurbineInput,
                              const std::shared_ptr<Turbine>&                  highToLowPressureTurbine,
                              const std::shared_ptr<Turbine>&                  highToLowPressureTurbineIdeal,
                              const SteamSystemModelerTool::FluidProperties&   highPressureHeaderOutput,
                              const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput) const {
    const std::string methodName = std::string("SteamReducer::") + std::string(__func__) + ": ";

    double                   remainingAdditionalSteamNeeded       = additionalSteamNeeded;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated      = highToLowPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated = highToLowPressureTurbineIdeal;

    const double highToLowPressureTurbineMassFlow     = highToLowPressureTurbine->getMassFlow();
    const double highToLowTurbineInputOperationValue1 = highToLowTurbineInput.getOperationValue1();

    // if current mass flow is greater than minimum needed
    if (highToLowPressureTurbineMassFlow > highToLowTurbineInputOperationValue1) {
        // calculateThermalResistance amount of steam that can be taken
        const double currentMassFlow = highToLowPressureTurbineMassFlow;

        // calculateThermalResistance turbine at minimum value
        SM_LOG(methodName << "calculating highToLowPressureTurbine with amount needed (highToLowTurbineInputOperationValue1)=" << highToLowTurbineInputOperationValue1);
        highToLowPressureTurbineUpdated =
            turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToLowTurbineInput,
                                               highToLowTurbineInputOperationValue1, lowPressureHeaderInput, false);
        SM_LOG(methodName << "highToLowPressureTurbineUpdated=" << highToLowPressureTurbineIdealUpdated);

        SM_LOG(methodName << "calculating highToLowPressureTurbineIdeal with amount needed (highToLowTurbineInputOperationValue1)=" << highToLowTurbineInputOperationValue1);
        highToLowPressureTurbineIdealUpdated =
            turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToLowTurbineInput,
                                               highToLowTurbineInputOperationValue1, lowPressureHeaderInput, true);
        SM_LOG(methodName << "highToLowPressureTurbineIdealUpdated=" << highToLowPressureTurbineIdealUpdated);

        // calculateThermalResistance amount of mass flow reduced
        const double massFlowReduction = currentMassFlow - highToLowPressureTurbineUpdated->getMassFlow();

        // calculateThermalResistance new steam need
        double newSteamNeed = additionalSteamNeeded - massFlowReduction;

        // if more steam taken than needed when reducing, put excess steam taken back into turbine
        if (newSteamNeed < 0) {
            const double massFlow = highToLowPressureTurbineUpdated->getMassFlow() + fabs(newSteamNeed);
            SM_LOG(methodName << "calculating highToLowPressureTurbine, returning excess steam amount, with mass flow=" << massFlow);
            highToLowPressureTurbineUpdated = turbineFactory.makePtrWithMassFlow(
                highPressureHeaderOutput, highToLowTurbineInput, massFlow, lowPressureHeaderInput, false);
            SM_LOG(methodName << "highToLowPressureTurbineUpdated=" << highToLowPressureTurbineUpdated);

            SM_LOG(methodName << "calculating highToLowPressureTurbineIdeal, returning excess steam amount, with mass flow=" << massFlow);
            highToLowPressureTurbineIdealUpdated = turbineFactory.makePtrWithMassFlow(
                highPressureHeaderOutput, highToLowTurbineInput, massFlow, lowPressureHeaderInput, true);
            SM_LOG(methodName << "highToLowPressureTurbineIdealUpdated=" << highToLowPressureTurbineIdealUpdated);

            remainingAdditionalSteamNeeded = 0;
        }
        else {
            remainingAdditionalSteamNeeded = newSteamNeed;
        }
    }

    return {remainingAdditionalSteamNeeded, highToLowPressureTurbineUpdated, highToLowPressureTurbineIdealUpdated};
}
