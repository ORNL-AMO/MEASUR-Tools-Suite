#ifndef TOOLS_SUITE_STEAMMODELCALCULATIONSDOMAIN_H
#define TOOLS_SUITE_STEAMMODELCALCULATIONSDOMAIN_H

#include <memory>
#include <steamModeler/Boiler.h>
#include <steamModeler/Deaerator.h>
#include <steamModeler/domain/EnergyAndCostCalculationsDomain.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/LowPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/MakeupWaterAndCondensateHeaderCalculationsDomain.h>
#include <steamModeler/domain/MediumPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/PowerBalanceCheckerCalculationsDomain.h>
#include <steamModeler/domain/ProcessSteamUsageCalculationsDomain.h>

class SteamModelCalculationsDomain {
public:
    Boiler boiler;
    std::shared_ptr<FlashTank> blowdownFlashTank;
    HighPressureHeaderCalculationsDomain highPressureHeaderCalculationsDomain;
    std::shared_ptr<MediumPressureHeaderCalculationsDomain> mediumPressureHeaderCalculationsDomain;
    std::shared_ptr<LowPressureHeaderCalculationsDomain> lowPressureHeaderCalculationsDomain;
    MakeupWaterAndCondensateHeaderCalculationsDomain makeupWaterAndCondensateHeaderCalculationsDomain;
    Deaerator deaerator;
    PowerBalanceCheckerCalculationsDomain powerBalanceCheckerCalculationsDomain;
    ProcessSteamUsageCalculationsDomain processSteamUsageCalculationsDomain;
    EnergyAndCostCalculationsDomain energyAndCostCalculationsDomain;
};

#endif //TOOLS_SUITE_STEAMMODELCALCULATIONSDOMAIN_H
