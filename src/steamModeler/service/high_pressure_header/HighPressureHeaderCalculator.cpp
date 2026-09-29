#include <steamModeler/Header.h>
#include <steamModeler/service/high_pressure_header/HighPressureHeaderCalculator.h>
#include "steamModeler/util/SteamModelerLogger.h"

SteamSystemModelerTool::FluidProperties
HighPressureHeaderCalculator::calc(const HeaderWithHighestPressure& highPressureHeaderInput,
                                   const Boiler&                    boiler) const {
    const std::string methodName = std::string("HighPressureHeaderCalculator::") + std::string(__func__) + ": ";

    const double headerPressure     = highPressureHeaderInput.getPressure();
    Header       highPressureHeader = headerFactory.make(headerPressure, boiler);
    SM_LOG(methodName << "highPressureHeader=" << highPressureHeader);

    return fluidPropertiesFactory.make(highPressureHeader);
}
