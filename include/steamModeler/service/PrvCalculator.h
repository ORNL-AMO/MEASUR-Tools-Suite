#ifndef TOOLS_SUITE_PRVCALCULATOR_H
#define TOOLS_SUITE_PRVCALCULATOR_H

#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/PrvWithDesuperheatingFactory.h>
#include <steamModeler/domain/PrvWithoutDesuperheatingFactory.h>
#include <steamModeler/Boiler.h>

class PrvCalculator {
public:
    PrvWithDesuperheating
    calcHighToMediumPrvWithDesuperheating(const HeaderWithHighestPressure &highPressureHeaderInput,
                                          const PressureTurbine &highToLowTurbineInput,
                                          const PressureTurbine &highToMediumTurbineInput,
                                          const CondensingTurbine &condensingTurbineInput,
                                          const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                          const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
                                          const std::shared_ptr<Turbine> &condensingTurbine,
                                          const Boiler &boiler,
                                          const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const;

    PrvWithoutDesuperheating
    calcHighToMediumPrvWithoutDesuperheating(
            const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
            const HeaderWithHighestPressure &highPressureHeaderInput,
            const PressureTurbine &highToLowTurbineInput,
            const PressureTurbine &highToMediumTurbineInput,
            const CondensingTurbine &condensingTurbineInput,
            const std::shared_ptr<Turbine> &highToLowPressureTurbine,
            const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
            const std::shared_ptr<Turbine> &condensingTurbine,
            const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const;

private:
    const PrvWithDesuperheatingFactory prvWithDesuperheatingFactory = PrvWithDesuperheatingFactory();
    const PrvWithoutDesuperheatingFactory prvWithoutDesuperheatingFactory = PrvWithoutDesuperheatingFactory();

    double calcPrvMassFlow(const SteamSystemModelerTool::FluidProperties &highPressureHeader,
                           const HeaderWithHighestPressure &highPressureHeaderInput,
                           const PressureTurbine &highToLowTurbineInput,
                           const PressureTurbine &highToMediumTurbineInput,
                           const CondensingTurbine &condensingTurbineInput,
                           const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                           const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
                           const std::shared_ptr<Turbine> &condensingTurbine) const;

    double getTurbineMassFlow(const std::shared_ptr<Turbine> &turbine, const std::string &turbineName) const;
};

#endif //TOOLS_SUITE_PRVCALCULATOR_H
