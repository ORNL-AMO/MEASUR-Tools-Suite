#include "steamModeler/domain/DeaeratorFactory.h"
#include "steamModeler/util/SteamModelerLogger.h"

const Deaerator
DeaeratorFactory::make(const BoilerInput& boilerInput, const double feedwaterMassFlow,
                       const SteamSystemModelerTool::FluidProperties& makeupWaterAndCondensateHeaderOutput,
                       const SteamSystemModelerTool::FluidProperties& inletHeaderOutput) const {
    const std::string methodName = std::string("DeaeratorFactory::") + std::string(__func__) + ": ";

    double                                 deaeratorPressure  = boilerInput.getDeaeratorPressure();
    double                                 ventRate           = boilerInput.getDeaeratorVentRate();
    double                                 waterPressure      = makeupWaterAndCondensateHeaderOutput.pressure;
    SteamProperties::ThermodynamicQuantity waterQuantityType  = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    double                                 waterQuantityValue = makeupWaterAndCondensateHeaderOutput.specificEnthalpy;
    double                                 steamPressure      = inletHeaderOutput.pressure;
    SteamProperties::ThermodynamicQuantity steamQuantityType  = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    double                                 steamQuantityValue = inletHeaderOutput.specificEnthalpy;

    SM_LOG(methodName << "deaerator inputs: "
           << "deaeratorPressure=" << deaeratorPressure
           << ", ventRate=" << ventRate
           << ", waterPressure=" << waterPressure
           << ", waterQuantityValue=" << waterQuantityValue
           << ", steamPressure=" << steamPressure
           << ", steamQuantityValue=" << steamQuantityValue);

    const Deaerator& deaerator = {deaeratorPressure, ventRate,          feedwaterMassFlow,
                                  waterPressure,     waterQuantityType, waterQuantityValue,
                                  steamPressure,     steamQuantityType, steamQuantityValue};

    SM_LOG(methodName << "deaerator=" << deaerator);

    return deaerator;
}
