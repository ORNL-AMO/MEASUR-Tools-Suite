#ifndef TOOLS_SUITE_DEAERATORMODELER_H
#define TOOLS_SUITE_DEAERATORMODELER_H

#include <steamModeler/Boiler.h>
#include <steamModeler/PRV.h>
#include <steamModeler/domain/DeaeratorFactory.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/LowPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/MediumPressureHeaderCalculationsDomain.h>
#include <steamModeler/service/water_and_condensate/MakeupWaterAndCondensateHeaderModeler.h>

class DeaeratorModeler {
public:
    Deaerator
    model(const int headerCountInput, const BoilerInput &boilerInput, const Boiler &boiler,
          const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
          const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
          const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain,
          const MakeupWaterAndCondensateHeaderCalculationsDomain &makeupWaterAndCondensateHeaderCalculationsDomain) const;

private:
    DeaeratorFactory deaeratorFactory = DeaeratorFactory();

    double getFeedwaterMassFlow(const std::shared_ptr<PrvWithoutDesuperheating> &prv) const;

    double calcFeedwaterMassFlow(const int headerCountInput, const Boiler &boiler,
                                 const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                                 const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    Deaerator makeDeaerator(const int headerCountInput, const BoilerInput &boilerInput,
                            const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                            const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain,
                            const MakeupWaterAndCondensateHeaderCalculationsDomain &makeupWaterAndCondensateHeaderCalculationsDomain,
                            const double feedwaterMassFlow) const;
};

#endif //TOOLS_SUITE_DEAERATORMODELER_H
