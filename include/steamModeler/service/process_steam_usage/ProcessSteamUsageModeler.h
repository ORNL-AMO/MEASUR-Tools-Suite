#ifndef TOOLS_SUITE_PROCESSSTEAMUSAGEMODELER_H
#define TOOLS_SUITE_PROCESSSTEAMUSAGEMODELER_H

#include <memory>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/LowPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/MediumPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/ProcessSteamUsageCalculationsDomain.h>

class ProcessSteamUsageModeler {
public:
    ProcessSteamUsageCalculationsDomain
    model(const double headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
          const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
          const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    ProcessSteamUsage
    calc(const HeaderWithHighestPressure &highPressureHeaderInput,
         const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const;

    ProcessSteamUsage
    calc(const std::shared_ptr<HeaderNotHighestPressure> &headerInput,
         const SteamSystemModelerTool::FluidProperties &headerOutput,
         const SteamSystemModelerTool::FluidProperties &pressureCondensate) const;
};

#endif //TOOLS_SUITE_PROCESSSTEAMUSAGEMODELER_H
