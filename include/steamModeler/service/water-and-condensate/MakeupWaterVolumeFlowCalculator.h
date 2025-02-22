#ifndef TOOLS_SUITE_MAKEUPWATERVOLUMEFLOWCALCULATOR_H
#define TOOLS_SUITE_MAKEUPWATERVOLUMEFLOWCALCULATOR_H

#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/api/OperationsInput.h>
#include <steamModeler/domain/MakeupWaterVolumeFlowCalculationsDomain.h>

class MakeupWaterVolumeFlowCalculator {
public:
    MakeupWaterVolumeFlowCalculationsDomain
    calc(const SteamSystemModelerTool::FluidProperties &makeupWaterAndMassFlow,
         const OperationsInput &operationsInput) const;

private:
    double calcMakeupWaterVolumeFlow(const SteamSystemModelerTool::FluidProperties &makeupWaterAndMassFlow) const;

    double
    calcMakeupWaterVolumeFlowAnnual(const double makeupWaterVolumeFlow, const double operatingHoursPerYear) const;
};

#endif //TOOLS_SUITE_MAKEUPWATERVOLUMEFLOWCALCULATOR_H
