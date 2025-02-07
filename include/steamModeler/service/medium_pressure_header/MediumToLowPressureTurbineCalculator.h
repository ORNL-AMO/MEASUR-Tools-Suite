#ifndef TOOLS_SUITE_MEDIUMTOLOWPRESSURETURBINECALCULATOR_H
#define TOOLS_SUITE_MEDIUMTOLOWPRESSURETURBINECALCULATOR_H

#include "SteamBalanceCheckerService.h"
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>
#include "steamModeler/domain/TurbineFactory.h"
#include <steamModeler/service/RestarterService.h>
#include <steamModeler/service/SteamReducer.h>
#include "steamModeler/service/TurbineCalculator.h"
#include <steamModeler/service/medium_pressure_header/ReducedSteamException.h>

//TODO extract this as separate class
class MediumToLowPressureTurbineCalculatorOutput {
public:
    std::shared_ptr<Turbine> mediumToLowPressureTurbine;
    std::shared_ptr<Turbine> mediumToLowPressureTurbineIdeal;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated;

    friend std::ostream &operator<<(std::ostream &stream, const MediumToLowPressureTurbineCalculatorOutput &domain) {
        stream << "MediumToLowPressureTurbineCalculatorOutput["
               << "mediumToLowPressureTurbine=" << domain.mediumToLowPressureTurbine
               << ", mediumToLowPressureTurbineIdeal=" << domain.mediumToLowPressureTurbineIdeal
               << ", highToLowPressureTurbineUpdated=" << domain.highToLowPressureTurbineUpdated
               << ", highToLowPressureTurbineIdealUpdated=" << domain.highToLowPressureTurbineIdealUpdated
               << "]";
        return stream;
    }
};

class MediumToLowPressureTurbineCalculator {
public:
    MediumToLowPressureTurbineCalculatorOutput
    calc(const PressureTurbine &highToLowTurbineInput, const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal, const PressureTurbine &mediumToLowTurbineInput,
         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler) const;

private:
    const SteamBalanceCheckerService steamBalanceCheckerService = SteamBalanceCheckerService();
    const TurbineFactory turbineFactory = TurbineFactory();


    MediumToLowPressureTurbineCalculatorOutput
    calc(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const PressureTurbine &mediumToLowTurbineInput,
         const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler) const;

    MediumToLowPressureTurbineCalculatorOutput
    calcFlowRange(const double availableMassFlow, const PressureTurbine &mediumToLowTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler,
                  const PressureTurbine &highToLowTurbineInput,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;

    MediumToLowPressureTurbineCalculatorOutput
    calcPowerRange(const double availableMassFlow,
                   const PressureTurbine &mediumToLowTurbineInput,
                   const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                   const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                   const Boiler &boiler,
                   const PressureTurbine &highToLowTurbineInput,
                   const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                   const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                   const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;

    MediumToLowPressureTurbineCalculatorOutput
    calcPowerGeneration(const double availableMassFlow,
                        const PressureTurbine &mediumToLowTurbineInput,
                        const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                        const Boiler &boiler,
                        const PressureTurbine &highToLowTurbineInput,
                        const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                        const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;

    MediumToLowPressureTurbineCalculatorOutput
    calcSteamFlow(const double availableMassFlow,
                  const PressureTurbine &mediumToLowTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                  const Boiler &boiler,
                  const PressureTurbine &highToLowTurbineInput,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;

    MediumToLowPressureTurbineCalculatorOutput
    calcBalanceHeader(const double availableMassFlow,
                      const PressureTurbine &mediumToLowTurbineInput,
                      const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                      const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                      const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                      const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal) const;

    double calcAvailableMassFlow(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                 const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput) const;
};

#endif //TOOLS_SUITE_MEDIUMTOLOWPRESSURETURBINECALCULATOR_H
