#ifndef TOOLS_SUITE_TURBINCALCULATOR_H
#define TOOLS_SUITE_TURBINCALCULATOR_H

#include <steamModeler/Header.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/TurbineFactory.h>

class TurbineCalculator {
public:
    Turbine calc(const SteamSystemModelerTool::FluidProperties &headerProperties,
                 const HeaderWithHighestPressure &highPressureHeaderInput, const int headerCountInput,
                 const double connectedHeaderProcessSteamUsage,
                 const std::shared_ptr<HeaderNotHighestPressure> &headerWithNotHighPressure,
                 const PressureTurbine &pressureTurbine) const;

    Turbine calc(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                 const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                 const PressureTurbine &mediumToLowTurbineInput,
                 const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

private:
    const TurbineFactory turbineFactory = TurbineFactory();

    Turbine::TurbineProperty determineTurbineProperty(const PressureTurbine &pressureTurbine) const;

    double calcMassFlowOrPowerOut(const SteamSystemModelerTool::FluidProperties &headerProperties,
                                  const HeaderWithHighestPressure &highPressureHeaderInput, const int headerCountInput,
                                  const double connectedHeaderProcessSteamUsage) const;

    double adjustMassFlowOrPowerOut(const double massFlowOrPowerOut, const PressureTurbine &pressureTurbine) const;

    double calcMassFlowOrPowerOut(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                  const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput) const;
};

#endif //TOOLS_SUITE_TURBINCALCULATOR_H
