#ifndef TOOLS_SUITE_MEDIUMPRESSUREHEADERMODELER_H
#define TOOLS_SUITE_MEDIUMPRESSUREHEADERMODELER_H

#include <memory>
#include "HighToMediumPrvCalculator.h"
#include "MediumPressureCondensateCalculator.h"
#include "MediumPressureHeaderCalculator.h"
#include "MediumToLowPressureTurbineCalculator.h"
#include <steamModeler/Boiler.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/FluidPropertiesFactory.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/MediumPressureHeaderCalculationsDomain.h>
#include <steamModeler/service/high_pressure_header/HighPressureHeaderModeler.h>
#include <steamModeler/service/medium_pressure_header/ReducedSteamException.h>
#include <steamModeler/service/medium_pressure_header/UnableToBalanceException.h>

class MediumPressureHeaderModeler {
public:
    std::shared_ptr<MediumPressureHeaderCalculationsDomain>
    model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const PressureTurbine &highToMediumTurbineInput, const PressureTurbine &highToLowTurbineInput,
          const PressureTurbine &mediumToLowTurbineInput, const CondensingTurbine &condensingTurbineInput,
          const Boiler &boiler, HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeatLossFactory heatLossFactory = HeatLossFactory();
    const HighPressureHeaderModeler highPressureHeaderModeler = HighPressureHeaderModeler();
    const HighToMediumPrvCalculator highToMediumPrvCalculator = HighToMediumPrvCalculator();
    const MediumPressureCondensateCalculator mediumPressureCondensateCalculator = MediumPressureCondensateCalculator();
    const MediumPressureHeaderCalculator mediumPressureHeaderCalculator = MediumPressureHeaderCalculator();
    const MediumToLowPressureTurbineCalculator mediumToLowPressureTurbineCalculator =
            MediumToLowPressureTurbineCalculator();

    std::shared_ptr<MediumPressureHeaderCalculationsDomain>
    modelIteration(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                   const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                   const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                   const PressureTurbine &highToMediumTurbineInput, const PressureTurbine &highToLowTurbineInput,
                   const PressureTurbine &mediumToLowTurbineInput, const CondensingTurbine &condensingTurbineInput,
                   const Boiler &boiler,
                   const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const;
};

#endif //TOOLS_SUITE_MEDIUMPRESSUREHEADERMODELER_H
