#ifndef TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATOR_H
#define TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATOR_H

#include <steamModeler/FlashTank.h>
#include <steamModeler/PRV.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/domain/HeaderFactory.h>
#include <steamModeler/service/RestarterService.h>
#include <steamModeler/service/SteamReducer.h>
#include <steamModeler/service/medium_pressure_header/ReducedSteamException.h>
#include "SteamBalanceCheckerService.h"

class MediumPressureHeaderCalculatorOutput {
public:
    SteamSystemModelerTool::FluidProperties mediumPressureHeaderOutput;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated;

    friend std::ostream &operator<<(std::ostream &stream, const MediumPressureHeaderCalculatorOutput &domain) {
        stream << "MediumPressureHeaderCalculatorOutput["
               << "mediumPressureHeaderOutput=" << domain.mediumPressureHeaderOutput
               << ", highToLowPressureTurbineUpdated=" << domain.highToLowPressureTurbineUpdated
               << ", highToLowPressureTurbineIdealUpdated=" << domain.highToLowPressureTurbineIdealUpdated
               << "]";
        return stream;
    }
};

class MediumPressureHeaderCalculator {
public:
    MediumPressureHeaderCalculatorOutput
    calc(const Boiler &boiler, const PressureTurbine &highToLowTurbineInput,
         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const std::shared_ptr<PrvWithoutDesuperheating> &highToMediumPressurePrv,
         const PressureTurbine &highToMediumTurbineInput,
         const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
         const std::shared_ptr<FlashTank> &highPressureCondensateFlashTank,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeaderFactory headerFactory = HeaderFactory();
    const SteamBalanceCheckerService steamBalanceCheckerService = SteamBalanceCheckerService();
};

#endif //TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATOR_H
