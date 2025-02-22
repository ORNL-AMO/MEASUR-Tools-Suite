#ifndef TOOLS_SUITE_RETURNCONDENSATECALCULATIONSDOMAIN_H
#define TOOLS_SUITE_RETURNCONDENSATECALCULATIONSDOMAIN_H

#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/FlashTank.h>

class ReturnCondensateCalculationsDomain {
public:
    std::shared_ptr<FlashTank> condensateFlashTank;
    SteamSystemModelerTool::FluidProperties returnCondensateFlashed;

    friend std::ostream &operator<<(std::ostream &stream, const ReturnCondensateCalculationsDomain &domain) {
        stream << "ReturnCondensateCalculationsDomain["
               << "condensateFlashTank=" << domain.condensateFlashTank
               << ", returnCondensateFlashed=" << domain.returnCondensateFlashed
               << "]";
        return stream;
    }
};

#endif //TOOLS_SUITE_RETURNCONDENSATECALCULATIONSDOMAIN_H
