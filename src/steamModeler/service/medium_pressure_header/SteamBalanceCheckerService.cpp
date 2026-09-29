#include "steamModeler/service/medium_pressure_header/SteamBalanceCheckerService.h"

#include <steamModeler/service/medium_pressure_header/ReducedSteamException.h>
#include "steamModeler/util/SteamModelerLogger.h"

SteamReducerOutput
SteamBalanceCheckerService::check(const std::string& itemName, const PressureTurbine& highToLowTurbineInput,
                                  const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                  const Boiler& boiler, const std::shared_ptr<Turbine>& highToLowPressureTurbine,
                                  const std::shared_ptr<Turbine>&                highToLowPressureTurbineIdeal,
                                  const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
                                  const double neededMassFlow, const double availableMassFlow) const {
    Boiler boiler_               = boiler;
    boiler_                      = boiler_; // keep this or fix unused variable
    const std::string methodName = std::string("SteamBalanceCheckerService::") + std::string(__func__) + ": ";

    // calculateThermalResistance additional steam needed to meet minimum requirement
    const double additionalSteamNeeded    = neededMassFlow - availableMassFlow;
    const double absAdditionalSteamNeeded = fabs(additionalSteamNeeded);

    // if need more than .0001
    if (absAdditionalSteamNeeded > 1e-3) {
        SM_LOG(methodName << itemName << " additionalSteamNeeded=" << additionalSteamNeeded << " > " << 1e-3 << "; attempting to take steam needed from highToLowPressureTurbine");
        const SteamReducerOutput& steamReducerOutput = steamReducer.reduceSteamThroughHighToLowTurbine(
            additionalSteamNeeded, highToLowTurbineInput, highToLowPressureTurbine, highToLowPressureTurbineIdeal,
            highPressureHeaderOutput, lowPressureHeaderInput);
        SM_LOG(methodName << "steamReducerOutput=" << steamReducerOutput);

        const double remainingAdditionalSteamNeeded = steamReducerOutput.remainingAdditionalSteamNeeded;
        // if high to low turbine was reduced and more steam is available
        if (remainingAdditionalSteamNeeded < additionalSteamNeeded) {
            const std::shared_ptr<Turbine>& highToLowPressureTurbineUpdated =
                steamReducerOutput.highToLowPressureTurbineUpdated;
            const std::shared_ptr<Turbine>& highToLowPressureTurbineIdealUpdated =
                steamReducerOutput.highToLowPressureTurbineIdealUpdated;

            throw ReducedSteamException("Reduced steam from highToLowPressureTurbine for " + itemName,
                                        highToLowPressureTurbineUpdated, highToLowPressureTurbineIdealUpdated);
        }
        else {
            // steam can't be reduced from highToLowPressureTurbine...
            restarter.restartIfNotEnoughSteam(remainingAdditionalSteamNeeded, boiler);
            // return {remainingAdditionalSteamNeeded, highToLowPressureTurbine, highToLowPressureTurbineIdeal};
        }
    }

    return {0, highToLowPressureTurbine, highToLowPressureTurbineIdeal};
}

SteamReducerOutput
SteamBalanceCheckerService::check(const std::string& itemName, const PressureTurbine& highToLowTurbineInput,
                                  const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                  const Boiler& boiler, const std::shared_ptr<Turbine>& highToLowPressureTurbine,
                                  const std::shared_ptr<Turbine>&                highToLowPressureTurbineIdeal,
                                  const std::shared_ptr<Turbine>&                highToMediumPressureTurbine,
                                  const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
                                  const double                                   availableMassFlow) const {
    std::string itemName_        = itemName;
    itemName_                    = itemName_; // keep this or fix unused variable
    const std::string methodName = std::string("SteamBalanceCheckerService::") + std::string(__func__) + ": ";

    // calculateThermalResistance additional steam needed to meet minimum requirement
    SM_LOG("availableMassFlow: " << availableMassFlow);
    const double additionalSteamNeeded = highToMediumPressureTurbine->getMassFlow() - availableMassFlow;

    SM_LOG("additionalSteamNeeded: " << additionalSteamNeeded);
    const double absAdditionalSteamNeeded = fabs(additionalSteamNeeded);

    // if need more than .0001
    if (absAdditionalSteamNeeded > 1e-3) {
        SM_LOG(methodName << itemName << " additionalSteamNeeded=" << additionalSteamNeeded << " > " << 1e-3 << "; attempting to take steam needed from high to low turbine");
        const SteamReducerOutput& steamReducerOutput = steamReducer.reduceSteamThroughHighToLowTurbine(
            additionalSteamNeeded, highToLowTurbineInput, highToLowPressureTurbine, highToLowPressureTurbineIdeal,
            highPressureHeaderOutput, lowPressureHeaderInput);
        SM_LOG(methodName << "steamReducerOutput=" << steamReducerOutput);

        const double remainingAdditionalSteamNeeded = steamReducerOutput.remainingAdditionalSteamNeeded;

        restarter.restartIfNotEnoughSteam(remainingAdditionalSteamNeeded, boiler);
        return steamReducerOutput;
    }
    else {
        return {0, highToLowPressureTurbine, highToLowPressureTurbineIdeal};
    }
}

void SteamBalanceCheckerService::check(const std::shared_ptr<Turbine>& turbine, const double availableMassFlow,
                                       const Boiler& boiler) const {
    const std::string methodName = std::string("SteamBalanceCheckerService::") + std::string(__func__) + ": ";

    // check that enough mass flow is available for set amount
    const double highToLowPressureTurbineMassFlow = turbine->getMassFlow();
    if (highToLowPressureTurbineMassFlow > availableMassFlow) {
        SM_LOG(methodName << "highToLowPressureTurbineMassFlow=" << highToLowPressureTurbineMassFlow << " > availableMassFlow=" << availableMassFlow << ", not enough power out of turbine");
        restarter.restartIfNotEnoughSteam(turbine, availableMassFlow, boiler);
    }
}
