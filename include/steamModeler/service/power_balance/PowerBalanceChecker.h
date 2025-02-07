#ifndef TOOLS_SUITE_POWERBALANCECHECKER_H
#define TOOLS_SUITE_POWERBALANCECHECKER_H

#include "SteamBalanceCalculator.h"
#include "LowPressureVentedSteamCalculator.h"
#include <steamModeler/Boiler.h>
#include <steamModeler/Deaerator.h>
#include <steamModeler/FlashTank.h>
#include <steamModeler/PRV.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/OperationsInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/domain/PowerBalanceCheckerCalculationsDomain.h>
#include <steamModeler/service/DeaeratorModeler.h>
#include <steamModeler/service/RestarterService.h>
#include "steamModeler/service/water_and_condensate/MakeupWaterAndCondensateHeaderCalculator.h"
#include "steamModeler/service/water_and_condensate/MakeupWaterMassFlowCalculator.h"

class PowerBalanceChecker {
public:
    PowerBalanceCheckerCalculationsDomain
    check(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const PressureTurbine &highToLowTurbineInput, const PressureTurbine &highToMediumTurbineInput,
          const PressureTurbine &mediumToLowTurbineInput, const BoilerInput &boilerInput,
          const CondensingTurbine &condensingTurbineInput, const OperationsInput &operationsInput, const Boiler &boiler,
          const std::shared_ptr<FlashTank> &blowdownFlashTank, const double deaeratorInletSteamMassFlow,
          const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
          const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
          const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain,
          MakeupWaterAndCondensateHeaderCalculationsDomain &makeupWaterAndCondensateHeaderCalculationsDomain) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const RestarterService restarter = RestarterService();
    const LowPressureVentedSteamCalculator lowPressureVentedSteamCalculator = LowPressureVentedSteamCalculator();
    const SteamBalanceCalculator steamBalanceCalculator = SteamBalanceCalculator();

    bool
    isVentingOnlyExcessSteamOption(const int headerCountInput, const PressureTurbine &highToLowTurbineInput,
                                   const PressureTurbine &highToMediumTurbineInput,
                                   const PressureTurbine &mediumToLowTurbineInput) const;
};

#endif //TOOLS_SUITE_POWERBALANCECHECKER_H
