#ifndef TOOLS_SUITE_STEAMBALANCECALCULATOR_H
#define TOOLS_SUITE_STEAMBALANCECALCULATOR_H

#include <steamModeler/Boiler.h>
#include <steamModeler/FlashTank.h>
#include <steamModeler/PRV.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/LowPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/MediumPressureHeaderCalculationsDomain.h>
#include "SteamProductionCalculator.h"
#include "SteamUseCalculator.h"

class SteamBalanceCalculator {
public:
    double calc(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                    const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                    const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                    const BoilerInput &boilerInput, const CondensingTurbine &condensingTurbineInput,
                    const Boiler &boiler, const std::shared_ptr<FlashTank> &blowdownFlashTank,
                    const double deaeratorInletSteamMassFlow,
                    const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                    const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                    const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    const SteamUseCalculator steamUseCalculator = SteamUseCalculator();
    const SteamProductionCalculator steamProductionCalculator = SteamProductionCalculator();
};

#endif //TOOLS_SUITE_STEAMBALANCECALCULATOR_H
