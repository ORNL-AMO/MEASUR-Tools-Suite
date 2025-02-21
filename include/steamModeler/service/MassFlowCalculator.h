#ifndef TOOLS_SUITE_MASSFLOWCALCULATOR_H
#define TOOLS_SUITE_MASSFLOWCALCULATOR_H

#include <steamModeler/api/HeaderInput.h>

class MassFlowCalculator {
public:
    double calcInitialMassFlow(const HeaderInput &headerInput) const;

    double calc(const HeaderWithHighestPressure &header) const;

    double calc(const std::shared_ptr<HeaderNotHighestPressure> &header) const;

    double calc(const double processSteamUsage, const double condensationRecoveryRate) const;

    double addToMassFlow(const std::string &objectName, double massFlow, const double mediumProcessSteamUsage) const;
};

#endif //TOOLS_SUITE_MASSFLOWCALCULATOR_H
