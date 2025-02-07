#ifndef TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATIONSDOMAIN_H
#define TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATIONSDOMAIN_H

#include <memory>
#include <steamModeler/FlashTank.h>
#include <steamModeler/HeatLoss.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>

class HighPressureHeaderCalculationsDomain {
public:
    SteamSystemModelerTool::FluidProperties highPressureHeaderOutput;
    HeatLoss highPressureHeaderHeatLoss;
    SteamSystemModelerTool::FluidProperties highPressureCondensate;
    std::shared_ptr<FlashTank> highPressureCondensateFlashTank;
    std::shared_ptr<Turbine> condensingTurbine;
    std::shared_ptr<Turbine> condensingTurbineIdeal;
    std::shared_ptr<Turbine> highToMediumPressureTurbine;
    std::shared_ptr<Turbine> highToMediumPressureTurbineIdeal;
    std::shared_ptr<Turbine> highToLowPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdeal;

    friend std::ostream &operator<<(std::ostream &stream, const HighPressureHeaderCalculationsDomain &domain) {
        stream << "HighPressureHeaderCalculationsDomain["
                << "highPressureHeaderOutput=" << domain.highPressureHeaderOutput
               << ", highPressureHeaderHeatLoss=" << domain.highPressureHeaderHeatLoss
               << ", highPressureCondensate=" << domain.highPressureCondensate
               << ", highPressureCondensateFlashTank=" << domain.highPressureCondensateFlashTank
               << ", condensingTurbine=" << domain.condensingTurbine
               << ", condensingTurbineIdeal=" << domain.condensingTurbineIdeal
               << ", highToMediumPressureTurbine=" << domain.highToMediumPressureTurbine
               << ", highToMediumPressureTurbineIdeal=" << domain.highToMediumPressureTurbineIdeal
               << ", highToLowPressureTurbine=" << domain.highToLowPressureTurbine
               << ", highToLowPressureTurbineIdeal=" << domain.highToLowPressureTurbineIdeal
                << "]";

        return stream;
    }
};

#endif //TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATIONSDOMAIN_H
