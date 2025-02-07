#ifndef TOOLS_SUITE_STEAMMODELEROUPUT_H
#define TOOLS_SUITE_STEAMMODELEROUPUT_H

#include <steamModeler/Boiler.h>
#include <steamModeler/Deaerator.h>
#include <steamModeler/domain/EnergyAndCostCalculationsDomain.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/LowPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/MakeupWaterAndCondensateHeaderCalculationsDomain.h>
#include <steamModeler/domain/MediumPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/PowerBalanceCheckerCalculationsDomain.h>
#include <steamModeler/domain/ProcessSteamUsageCalculationsDomain.h>

/**
 * Steam Modeler output data; holds all of the resulting output data.
 */
class SteamModelerOutput {
public:
    const Boiler boiler;
    const std::shared_ptr<FlashTank> blowdownFlashTank;
    const HighPressureHeaderCalculationsDomain highPressureHeaderCalculationsDomain;
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain> mediumPressureHeaderCalculationsDomain;
    const std::shared_ptr<LowPressureHeaderCalculationsDomain> lowPressureHeaderCalculationsDomain;
    const MakeupWaterAndCondensateHeaderCalculationsDomain makeupWaterAndCondensateHeaderCalculationsDomain;
    const Deaerator deaerator;
    const PowerBalanceCheckerCalculationsDomain powerBalanceCheckerCalculationsDomain;
    const ProcessSteamUsageCalculationsDomain processSteamUsageCalculationsDomain;
    const EnergyAndCostCalculationsDomain energyAndCostCalculationsDomain;

    friend std::ostream &operator<<(std::ostream &stream, const SteamModelerOutput &domain) {
        stream << "SteamModelerOutput["
               << "boiler=" << domain.boiler
               << ", blowdownFlashTank=" << domain.blowdownFlashTank
               << ", highPressureHeaderCalculationsDomain=" << domain.highPressureHeaderCalculationsDomain
               << ", mediumPressureHeaderCalculationsDomain=" << domain.mediumPressureHeaderCalculationsDomain
               << ", lowPressureHeaderCalculationsDomain=" << domain.lowPressureHeaderCalculationsDomain
               << ", makeupWaterAndCondensateHeaderCalculationsDomain=" << domain.makeupWaterAndCondensateHeaderCalculationsDomain
               << ", deaerator=" << domain.deaerator
               << ", powerBalanceCheckerCalculationsDomain=" << domain.powerBalanceCheckerCalculationsDomain
               << ", processSteamUsageCalculationsDomain=" << domain.processSteamUsageCalculationsDomain
               << ", energyAndCostCalculationsDomain=" << domain.energyAndCostCalculationsDomain
               << "]";

        return stream;
    }
};

#endif //TOOLS_SUITE_STEAMMODELEROUPUT_H
