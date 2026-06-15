#include "steamModeler/service/power_balance/PowerBalanceChecker.h"
#include "steamModeler/util/SteamModelerLogger.h"

// 7. Check system steam balance

PowerBalanceCheckerCalculationsDomain PowerBalanceChecker::check(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const PressureTurbine& highToLowTurbineInput, const PressureTurbine& highToMediumTurbineInput,
    const PressureTurbine& mediumToLowTurbineInput, const BoilerInput& boilerInput,
    const CondensingTurbine& condensingTurbineInput, const OperationsInput& operationsInput, const Boiler& boiler,
    const std::shared_ptr<FlashTank>& blowdownFlashTank, const double deaeratorInletSteamMassFlow,
    const HighPressureHeaderCalculationsDomain&                    highPressureHeaderCalculationsDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>&    lowPressureHeaderCalculationsDomain,
    MakeupWaterAndCondensateHeaderCalculationsDomain& makeupWaterAndCondensateHeaderCalculationsDomain) const {
    const std::string methodName = std::string("PowerBalanceChecker::") + std::string(__func__) + ": ";

    SM_LOG(methodName << "calculating steamBalance");
    double steamBalance = steamBalanceCalculator.calc(
        headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput, lowPressureHeaderInput, boilerInput,
        condensingTurbineInput, boiler, blowdownFlashTank, deaeratorInletSteamMassFlow,
        highPressureHeaderCalculationsDomain, mediumPressureHeaderCalculationsDomain,
        lowPressureHeaderCalculationsDomain);
    SM_LOG(methodName << "steamBalance=" << steamBalance);

    std::shared_ptr<LowPressureVentedSteamCalculationsDomain> lowPressureVentedSteamCalculationsDomainPtr = nullptr;
    std::shared_ptr<SteamSystemModelerTool::FluidProperties>  lowPressureVentedSteamPtr                   = nullptr;

    // TODO refactor this
    if (headerCountInput > 1 && steamBalance < 0) {
        SM_LOG(methodName << "headerCountInput > 1 and steamBalance < 0 so calculating lowPressureVentedSteam");

        double deaeratorInletSteamMassFlowUpdated = deaeratorInletSteamMassFlow;

        const bool isVentingOnlyOption = isVentingOnlyExcessSteamOption(
            headerCountInput, highToLowTurbineInput, highToMediumTurbineInput, mediumToLowTurbineInput);
        if (isVentingOnlyOption) {
            const bool                               recalcMakeupWaterAndMassFlow = false;
            LowPressureVentedSteamCalculationsDomain lowPressureVentedSteamCalculationsDomain =
                lowPressureVentedSteamCalculator.calc(
                    headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput, lowPressureHeaderInput,
                    condensingTurbineInput, operationsInput, boilerInput, boiler, highPressureHeaderCalculationsDomain,
                    mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain,
                    makeupWaterAndCondensateHeaderCalculationsDomain, deaeratorInletSteamMassFlowUpdated,
                    recalcMakeupWaterAndMassFlow);
            SM_LOG(methodName << "lowPressureVentedSteamCalculationsDomain=" << lowPressureVentedSteamCalculationsDomain);
            lowPressureVentedSteamCalculationsDomainPtr =
                std::make_shared<LowPressureVentedSteamCalculationsDomain>(lowPressureVentedSteamCalculationsDomain);
            const double lowPressureVentedSteam = lowPressureVentedSteamCalculationsDomain.lowPressureVentedSteam;
            deaeratorInletSteamMassFlowUpdated =
                lowPressureVentedSteamCalculationsDomain.deaerator.getInletSteamProperties().massFlow;

            steamBalance += lowPressureVentedSteam;
            SM_LOG(methodName << "updated steamBalance=" << steamBalance << " (added lowPressureVentedSteam=" << lowPressureVentedSteam << " to it)");
        }

        // Steam balance will be positive, vented steam amount ends up negative.
        // If it gets it close enough to zero then venting the steam will result in a balanced system.
        const double absSteamBalance = fabs(steamBalance);
        if (absSteamBalance < 1e-2) {
            SM_LOG(methodName << "steamBalance < " << 1e-2 << " so calculating lowPressureVentedSteam again" << " with recalcMakeupWaterAndMassFlow");
            const bool                               recalcMakeupWaterAndMassFlow = true;
            LowPressureVentedSteamCalculationsDomain lowPressureVentedSteamCalculationsDomain =
                lowPressureVentedSteamCalculator.calc(
                    headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput, lowPressureHeaderInput,
                    condensingTurbineInput, operationsInput, boilerInput, boiler, highPressureHeaderCalculationsDomain,
                    mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain,
                    makeupWaterAndCondensateHeaderCalculationsDomain, deaeratorInletSteamMassFlowUpdated,
                    recalcMakeupWaterAndMassFlow);
            SM_LOG(methodName << "lowPressureVentedSteamCalculationsDomain=" << lowPressureVentedSteamCalculationsDomain);
            lowPressureVentedSteamCalculationsDomainPtr =
                std::make_shared<LowPressureVentedSteamCalculationsDomain>(lowPressureVentedSteamCalculationsDomain);

            SM_LOG(methodName << "calculating final lowPressureVentedSteam" << " from lowPressureHeaderOutput and lowPressureVentedSteam");
            const SteamSystemModelerTool::FluidProperties& lowPressureHeaderOutput =
                lowPressureHeaderCalculationsDomain->lowPressureHeaderOutput;
            const double lowPressureVentedSteamAmount = lowPressureVentedSteamCalculationsDomain.lowPressureVentedSteam;
            SteamSystemModelerTool::FluidProperties lowPressureVentedSteam =
                fluidPropertiesFactory.makeWithMassFlow(lowPressureHeaderOutput, lowPressureVentedSteamAmount);
            lowPressureVentedSteamPtr =
                std::make_shared<SteamSystemModelerTool::FluidProperties>(lowPressureVentedSteam);
        }
    }
    else {
        SM_LOG(methodName << "condition not true (headerCountInput > 1 and steamBalance < 0)" << ", so skip calculating lowPressureVentedSteam");
    }

    restarter.restartIfNotEnoughSteam(steamBalance, boiler);

    return {steamBalance, lowPressureVentedSteamCalculationsDomainPtr, lowPressureVentedSteamPtr};
}

/** If nowhere else to put excess steam, must vent it. */
bool PowerBalanceChecker::isVentingOnlyExcessSteamOption(const int              headerCountInput,
                                                         const PressureTurbine& highToLowTurbineInput,
                                                         const PressureTurbine& highToMediumTurbineInput,
                                                         const PressureTurbine& mediumToLowTurbineInput) const {
    const std::string methodName   = std::string("PowerBalanceChecker::") + std::string(__func__) + ": ";
    bool              isOnlyOption = false;

    if (headerCountInput > 1) {
        if (highToLowTurbineInput.isUseTurbine() &&
            highToLowTurbineInput.getOperationType() != PressureTurbineOperation::BALANCE_HEADER) {
            isOnlyOption = true;
        }
        if (headerCountInput == 3) {
            if (highToMediumTurbineInput.isUseTurbine() &&
                highToMediumTurbineInput.getOperationType() != PressureTurbineOperation::BALANCE_HEADER) {
                isOnlyOption = true;
            }
            if (mediumToLowTurbineInput.isUseTurbine() &&
                mediumToLowTurbineInput.getOperationType() != PressureTurbineOperation::BALANCE_HEADER) {
                isOnlyOption = true;
            }
        }
    }

    SM_LOG(methodName << "isOnlyOption=" << isOnlyOption);

    return isOnlyOption;
}
