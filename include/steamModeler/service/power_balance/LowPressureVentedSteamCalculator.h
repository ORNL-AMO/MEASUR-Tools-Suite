#ifndef TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATOR_H
#define TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATOR_H

#include <steamModeler/Boiler.h>
#include <steamModeler/HeatExchanger.h>
#include <steamModeler/PRV.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/OperationsInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/domain/LowPressureVentedSteamCalculationsDomain.h>
#include <steamModeler/service/DeaeratorModeler.h>
#include <steamModeler/service/water_and_condensate/MakeupWaterAndCondensateHeaderCalculator.h>
#include <steamModeler/service/water_and_condensate/MakeupWaterMassFlowCalculator.h>
#include <steamModeler/service/water-and-condensate/MakeupWaterVolumeFlowCalculator.h>

class LowPressureVentedSteamCalculator {
public:
    LowPressureVentedSteamCalculationsDomain
    calc(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
             const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
             const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
             const CondensingTurbine &condensingTurbineInput, const OperationsInput &operationsInput,
             const BoilerInput &boilerInput, const Boiler &boiler,
             const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
             const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
             const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain,
             MakeupWaterAndCondensateHeaderCalculationsDomain &makeupWaterAndCondensateHeaderCalculationsDomain,
             const double deaeratorInletSteamMassFlow, const bool recalcMakeupWaterAndMassFlow) const;

private:
    const DeaeratorModeler deaeratorModeler = DeaeratorModeler();
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const MakeupWaterAndCondensateHeaderCalculator makeupWaterAndCondensateHeaderCalculator = MakeupWaterAndCondensateHeaderCalculator();
    const MakeupWaterMassFlowCalculator makeupWaterMassFlowCalculator = MakeupWaterMassFlowCalculator();
    const MakeupWaterVolumeFlowCalculator makeupWaterVolumeFlowCalculator = MakeupWaterVolumeFlowCalculator();

    double
    calcLowPressureVentedSteam(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                               const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput,
                               const double massFlow) const;
};

#endif //TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATOR_H
