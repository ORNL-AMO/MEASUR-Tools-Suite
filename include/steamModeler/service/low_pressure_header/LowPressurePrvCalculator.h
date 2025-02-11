#ifndef TOOLS_SUITE_LOWPRESSUREPRVCALCULATOR_H
#define TOOLS_SUITE_LOWPRESSUREPRVCALCULATOR_H

#include <steamModeler/Turbine.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/MediumPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/PrvWithDesuperheatingFactory.h>
#include <steamModeler/domain/PrvWithoutDesuperheatingFactory.h>
#include <steamModeler/Boiler.h>

class LowPressurePrvCalculator {
public:
    std::shared_ptr<PrvWithoutDesuperheating>
    calc(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
         const PressureTurbine &highToLowTurbineInput, const CondensingTurbine &condensingTurbineInput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const PressureTurbine &mediumToLowTurbineInput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler,
         const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
         const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const ;

private:
    const PrvWithDesuperheatingFactory prvWithDesuperheatingFactory = PrvWithDesuperheatingFactory();
    const PrvWithoutDesuperheatingFactory prvWithoutDesuperheatingFactory = PrvWithoutDesuperheatingFactory();

    double calcPrvMassFlow(const int headerCountInput,
                           const HeaderWithHighestPressure &highPressureHeaderInput,
                           const SteamSystemModelerTool::FluidProperties &highPressureHeader,
                           const PressureTurbine &highToLowTurbineInput,
                           const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                           const CondensingTurbine &condensingTurbineInput,
                           const std::shared_ptr<Turbine> &condensingTurbine,
                           const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                           const PressureTurbine &mediumToLowTurbineInput,
                           const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const;

    SteamSystemModelerTool::FluidProperties determineHeader(const int headerCountInput,
                                                            const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                                                            const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;

    std::shared_ptr<PrvWithoutDesuperheating>
    makePrv(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler,
            const SteamSystemModelerTool::FluidProperties &headerOutput, double prvMassFlow) const;
};

#endif //TOOLS_SUITE_LOWPRESSUREPRVCALCULATOR_H
