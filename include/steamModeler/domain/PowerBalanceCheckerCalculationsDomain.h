#ifndef TOOLS_SUITE_POWERBALANCECHECKERCALCULATIONSDOMAIN_H
#define TOOLS_SUITE_POWERBALANCECHECKERCALCULATIONSDOMAIN_H

#include <memory>
#include <steamModeler/SteamSystemModelerTool.h>
#include "LowPressureVentedSteamCalculationsDomain.h"

class PowerBalanceCheckerCalculationsDomain {
public:
    double steamBalance;
    std::shared_ptr<LowPressureVentedSteamCalculationsDomain> lowPressureVentedSteamCalculationsDomain;
    std::shared_ptr<SteamSystemModelerTool::FluidProperties> lowPressureVentedSteam;

    friend std::ostream &operator<<(std::ostream &stream, const PowerBalanceCheckerCalculationsDomain &domain) {
        stream << "PowerBalanceCheckerCalculationsDomain["
               << "steamBalance=" << domain.steamBalance
               << ", lowPressureVentedSteamCalculationsDomain=" << domain.lowPressureVentedSteamCalculationsDomain
               << ", lowPressureVentedSteam=" << domain.lowPressureVentedSteam
               << "]";
        return stream;
    }
};

#endif //TOOLS_SUITE_POWERBALANCECHECKERCALCULATIONSDOMAIN_H
