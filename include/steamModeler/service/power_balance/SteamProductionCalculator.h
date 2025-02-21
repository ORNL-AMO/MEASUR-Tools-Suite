#ifndef TOOLS_SUITE_STEAMPRODUCTIONCALCULATOR_H
#define TOOLS_SUITE_STEAMPRODUCTIONCALCULATOR_H

#include <memory>
#include <steamModeler/Boiler.h>
#include <steamModeler/FlashTank.h>
#include <steamModeler/PRV.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/LowPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/MediumPressureHeaderCalculationsDomain.h>

class SteamProductionCalculator {
public:
    double calc(const int headerCountInput,
                    const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                    const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                    const BoilerInput &boilerInput,
                    const std::shared_ptr<FlashTank> &blowdownFlashTank,
                    const Boiler &boiler,
                    const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                    const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                    const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    double calcFlashTankAdditionalSteam(const int headerCountInput, const BoilerInput &boilerInput,
                                            const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                            const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                            const std::shared_ptr<FlashTank> &blowdownFlashTank,
                                            const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                                            const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    double calcPrvAdditionalSteam(const int headerCountInput,
                                      const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                      const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                      const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                                      const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    double
    addPrvMassFlow(double prvAdditionalSteam, const std::shared_ptr<PrvWithoutDesuperheating> &prv) const;
};

#endif //TOOLS_SUITE_STEAMPRODUCTIONCALCULATOR_H
