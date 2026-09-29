#include "steamModeler/service/high_pressure_header/HighPressureCondensateCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

const SteamSystemModelerTool::FluidProperties
HighPressureCondensateCalculator::calc(const HeaderWithHighestPressure& highPressureHeaderInput,
                                       const Boiler&                    boiler) const {
    const std::string methodName = std::string("HighPressureCondensateCalculator::") + std::string(__func__) + ": ";

    // has same properties as blowdown with updated mass and energy flows
    SM_LOG(methodName << "calculating highPressureCondensate");
    double massFlow   = massFlowCalculator.calc(highPressureHeaderInput);
    double energyFlow = energyFlowCalculator.calc(massFlow, boiler);
    SM_LOG(methodName << "massFlow=" << massFlow << ", energyFlow=" <<energyFlow);

    return fluidPropertiesFactory.makeFromBlowdown(boiler, massFlow, energyFlow);
}
