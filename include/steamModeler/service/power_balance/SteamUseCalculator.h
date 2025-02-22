#ifndef TOOLS_SUITE_STEAMUSECALCULATOR_H
#define TOOLS_SUITE_STEAMUSECALCULATOR_H

#include <steamModeler/Turbine.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>

class SteamUseCalculator {
public:
    double calc(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                const double deaeratorInletSteamMassFlow, const CondensingTurbine &condensingTurbineInput,
                const std::shared_ptr<Turbine> &condensingTurbine) const;

private:
    double calcProcessSteamUsage(const int headerCountInput,
                                 const HeaderWithHighestPressure &highPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const;
};

#endif //TOOLS_SUITE_STEAMUSECALCULATOR_H
