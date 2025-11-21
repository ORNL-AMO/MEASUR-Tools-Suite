#pragma once

#include <steamModeler/api/OperationsInput.h>
#include <steamModeler/domain/MakeupWaterVolumeFlowCalculationsDomain.h>
#include <steamModeler/SteamSystemModelerTool.h>

class MakeupWaterVolumeFlowCalculator {
  public:
    MakeupWaterVolumeFlowCalculationsDomain calc(const SteamSystemModelerTool::FluidProperties& makeupWaterAndMassFlow,
                                                 const OperationsInput&                         operationsInput) const;

  private:
    double calcMakeupWaterVolumeFlow(const SteamSystemModelerTool::FluidProperties& makeupWaterAndMassFlow) const;

    double calcMakeupWaterVolumeFlowAnnual(const double makeupWaterVolumeFlow,
                                           const double operatingHoursPerYear) const;
};

