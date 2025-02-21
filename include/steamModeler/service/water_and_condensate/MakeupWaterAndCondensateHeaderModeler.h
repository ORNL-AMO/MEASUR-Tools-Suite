#ifndef TOOLS_SUITE_WATERANDCONDENSATEMODELER_H
#define TOOLS_SUITE_WATERANDCONDENSATEMODELER_H

#include "CombinedCondensateCalculator.h"
#include "MakeupWaterCalculator.h"
#include "MakeupWaterMassFlowCalculator.h"
#include "ReturnCondensateCalculator.h"
#include "HeatExchangerCalculator.h"
#include "MakeupWaterAndCondensateHeaderCalculator.h"
#include "MakeupWaterAndCondensateHeaderModeler.h"
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/api/OperationsInput.h>
#include <steamModeler/domain/FlashTankFactory.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/domain/HeaderFactory.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/LowPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/MakeupWaterAndCondensateHeaderCalculationsDomain.h>
#include <steamModeler/domain/MediumPressureHeaderCalculationsDomain.h>
#include <steamModeler/service/water-and-condensate/MakeupWaterVolumeFlowCalculator.h>

class MakeupWaterAndCondensateHeaderModeler {
public:
    MakeupWaterAndCondensateHeaderCalculationsDomain
    model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
              const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
              const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
              const BoilerInput &boilerInput, const OperationsInput &operationsInput,
              const CondensingTurbine &condensingTurbineInput, const Boiler &boiler,
              const std::shared_ptr<FlashTank> &blowdownFlashTank,
              const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
              const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
              const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    CombinedCondensateCalculator combinedCondensateCalculator = CombinedCondensateCalculator();
    FlashTankFactory flashTankFactory = FlashTankFactory();
    FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    HeaderFactory headerFactory = HeaderFactory();
    HeatExchangerCalculator heatExchangerCalculator = HeatExchangerCalculator();
    MakeupWaterCalculator makeupWaterCalculator = MakeupWaterCalculator();
    MakeupWaterAndCondensateHeaderCalculator makeupWaterAndCondensateHeaderCalculator = MakeupWaterAndCondensateHeaderCalculator();
    MakeupWaterMassFlowCalculator makeupWaterMassFlowCalculator = MakeupWaterMassFlowCalculator();
    MakeupWaterVolumeFlowCalculator makeupWaterVolumeFlowCalculator = MakeupWaterVolumeFlowCalculator();
    ReturnCondensateCalculator returnCondensateCalculator = ReturnCondensateCalculator();
};

#endif //TOOLS_SUITE_WATERANDCONDENSATEMODELER_H
