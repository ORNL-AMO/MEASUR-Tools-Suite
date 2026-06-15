#include "steamModeler/service/MassFlowCalculator.h"

#include <string>
#include "steamModeler/util/SteamModelerLogger.h"

double MassFlowCalculator::calcInitialMassFlow(const HeaderInput& headerInput) const {
    const std::string methodName = std::string("MassFlowCalculator::") + std::string(__func__) + ": ";

    double massFlow = 0;

    const HeaderWithHighestPressure&                 highPressureHeaderInput   = headerInput.getHighPressureHeader();
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput = headerInput.getMediumPressureHeader();
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput    = headerInput.getLowPressureHeader();

    const int headerCount = headerInput.getHeaderCount();
    if (headerCount > 2) {
        const double mediumProcessSteamUsage = mediumPressureHeaderInput->getProcessSteamUsage();
        massFlow = addToMassFlow("mediumPressureHeaderInput", mediumProcessSteamUsage, massFlow);
    }
    if (headerCount > 1) {
        const double lowProcessSteamUsage = lowPressureHeaderInput->getProcessSteamUsage();
        massFlow                          = addToMassFlow("lowProcessSteamUsage", lowProcessSteamUsage, massFlow);
    }
    if (headerCount > 0) {
        const double highProcessSteamUsage = highPressureHeaderInput.getProcessSteamUsage();
        massFlow                           = addToMassFlow("highProcessSteamUsage", highProcessSteamUsage, massFlow);
    }
    else {
        std::string msg = methodName + "headerCount=" + std::to_string(headerCount) + " not handled";
        SM_LOG(msg);
        throw std::out_of_range(msg);
    }

    SM_LOG(methodName << "massFlow=" << massFlow);

    return massFlow;
}

double MassFlowCalculator::addToMassFlow(const std::string& objectName, const double processSteamUsage,
                                         const double massFlow) const {
    std::string       objectName_ = objectName; // keep or fix unused variable
    const std::string methodName  = std::string("MassFlowCalculator::") + std::string(__func__) + ": ";

    double massFlowUpdated = massFlow;

    // handle NaN
    if (processSteamUsage > 0) {
        SM_LOG(methodName << "adding " << objectName << " processSteamUsage=" << processSteamUsage << " to massFlow=" << massFlow);
        massFlowUpdated += processSteamUsage;
    }
    else {
        SM_LOG(methodName << objectName << " processSteamUsage=" << processSteamUsage << ", not adding to massFlow=" << massFlow);
    }

    return massFlowUpdated;
}

double MassFlowCalculator::calc(const HeaderWithHighestPressure& header) const {
    const double processSteamUsage        = header.getProcessSteamUsage();
    const double condensationRecoveryRate = header.getCondensationRecoveryRate();
    return calc(processSteamUsage, condensationRecoveryRate);
}

double MassFlowCalculator::calc(const std::shared_ptr<HeaderNotHighestPressure>& header) const {
    const double processSteamUsage        = header->getProcessSteamUsage();
    const double condensationRecoveryRate = header->getCondensationRecoveryRate();
    return calc(processSteamUsage, condensationRecoveryRate);
}

double MassFlowCalculator::calc(const double processSteamUsage, const double condensationRecoveryRate) const {
    return processSteamUsage * (condensationRecoveryRate / 100);
}
