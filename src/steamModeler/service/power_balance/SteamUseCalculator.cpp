#include "steamModeler/service/power_balance/SteamUseCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

double SteamUseCalculator::calc(const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
                                const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
                                const double                                     deaeratorInletSteamMassFlow,
                                const CondensingTurbine&                         condensingTurbineInput,
                                const std::shared_ptr<Turbine>&                  condensingTurbine) const {
    const std::string methodName = std::string("SteamUseCalculator::") + std::string(__func__) + ": ";

    SM_LOG(methodName << "calculating steamUse");

    // steam use = steam used by (header process usage) + (deaerator) + (condensing turbine)
    // steam used by condensing turbine
    double processSteamUsage = calcProcessSteamUsage(headerCountInput, highPressureHeaderInput, lowPressureHeaderInput,
                                                     mediumPressureHeaderInput);
    const double condensingTurbineMassFlow =
        condensingTurbineInput.isUseTurbine() ? condensingTurbine->getMassFlow() : 0;

    const double steamUse = processSteamUsage + deaeratorInletSteamMassFlow + condensingTurbineMassFlow;
    SM_LOG(methodName << "processSteamUsage=" << processSteamUsage << " + deaeratorInletSteamMassFlow=" << deaeratorInletSteamMassFlow << " + condensingTurbineMassFlow=" << condensingTurbineMassFlow << ": steamUse=" << steamUse);

    return steamUse;
}

/** Calc amount of steam used by the system. */
double SteamUseCalculator::calcProcessSteamUsage(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput) const {
    const std::string methodName = std::string("SteamUseCalculator::") + std::string(__func__) + ": ";

    SM_LOG(methodName << "calculating steamUse");

    double processSteamUsage = highPressureHeaderInput.getProcessSteamUsage();

    SM_LOG(methodName << "highPressureHeaderInput processSteamUsage=" << processSteamUsage);

    if (headerCountInput > 1) {
        // steam used by low pressure header
        const double lowPressureProcessSteamUsage = lowPressureHeaderInput->getProcessSteamUsage();
        SM_LOG(methodName << "headerCountInput > 1, adding lowPressureProcessSteamUsage=" << lowPressureProcessSteamUsage);

        processSteamUsage += lowPressureProcessSteamUsage;

        if (headerCountInput == 3) {
            const double mediumPressureProcessSteamUsage = mediumPressureHeaderInput->getProcessSteamUsage();
            SM_LOG(methodName << "headerCountInput == 3, adding mediumPressureProcessSteamUsage=" << mediumPressureProcessSteamUsage);
            // steam used by medium pressure header
            processSteamUsage += mediumPressureProcessSteamUsage;
        }
    }
    else {
        SM_LOG(methodName << "headerCountInput=" << headerCountInput << " (not > 1), not adding low or medium pressureProcessSteamUsage");
    }

    SM_LOG(methodName << "processSteamUsage=" << processSteamUsage);

    return processSteamUsage;
}
