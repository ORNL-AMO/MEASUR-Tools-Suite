#ifndef TOOLS_SUITE_HEADERFACTORY_H
#define TOOLS_SUITE_HEADERFACTORY_H

#include <memory>
#include <steamModeler/Boiler.h>
#include <steamModeler/FlashTank.h>
#include <steamModeler/Header.h>
#include <steamModeler/HeatExchanger.h>
#include <steamModeler/PRV.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>
#include "InletFactory.h"
#include "HighPressureHeaderCalculationsDomain.h"
#include "LowPressureFlashedSteamIntoHeaderCalculatorDomain.h"
#include "LowPressureHeaderCalculationsDomain.h"
#include "MediumPressureHeaderCalculationsDomain.h"

class HeaderFactory {
public:
    const Header make(const double &headerPressure, const Boiler &boiler) const;

    const Header make(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                      const std::shared_ptr<PrvWithoutDesuperheating> &prvWithoutDesuperheating,
                      const PressureTurbine &highToMediumTurbineInput,
                      const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
                      const std::shared_ptr<FlashTank> &highPressureCondensateFlashTank) const;

    const Header make(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                      const std::shared_ptr<FlashTank> &highPressureCondensateFlashTank,
                      const SteamSystemModelerTool::FluidProperties &mediumPressureCondensate) const;

    const Header make(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                      const SteamSystemModelerTool::FluidProperties &highPressureCondensate,
                      const SteamSystemModelerTool::FluidProperties &mediumPressureCondensate) const;

    const Header
    make(const double headerCountInput, const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
         const PressureTurbine &highToLowTurbineInput, const PressureTurbine &mediumToLowTurbineInput,
         const BoilerInput &boilerInput,
         const std::shared_ptr<PrvWithoutDesuperheating> &lowPressurePrvWithoutDesuperheating,
         const std::shared_ptr<Turbine> &highToLowPressureTurbine, const std::shared_ptr<FlashTank> &blowdownFlashTank,
         const LowPressureFlashedSteamIntoHeaderCalculatorDomain &lowPressureFlashedSteamIntoHeaderCalculatorDomain,
         const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const;

    const Header make(const int headerCountInput, const double headerPressure,
                      const std::shared_ptr<FlashTank> &highPressureCondensateFlashTank,
                      const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                      const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                      const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    const Header make(const double headerPressure, const SteamSystemModelerTool::FluidProperties &returnCondensate,
                      const BoilerInput &boilerInput, const std::shared_ptr<HeatExchanger::Output> &heatExchangerOutput,
                      const SteamSystemModelerTool::FluidProperties &makeupWater,
                      const CondensingTurbine &condensingTurbineInput,
                      const std::shared_ptr<Turbine> &condensingTurbine) const;

    const Header
    make(const int headerCountInput, const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
         const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
         const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    double determineLowHeaderPressure(const int headerCountInput,
                                      const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                                      const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    const std::shared_ptr<FlashTank>
    selectHighPressureCondensateFlashTank(
            const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
            const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    const InletFactory inletFactory = InletFactory();

    bool isMediumPressureCondensateFlashTankNull(
            const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;
};

#endif //TOOLS_SUITE_HEADERFACTORY_H
