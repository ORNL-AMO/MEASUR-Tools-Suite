#include "steamModeler/domain/DeaeratorFactory.h"

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

    std::cout << methodName << "deaerator inputs: " << std::endl;
    std::cout << "deaeratorPressure=" << deaeratorPressure << std::endl;
    std::cout << "ventRate=" << ventRate << std::endl;
    std::cout << "waterPressure=" << waterPressure << std::endl;
    // std::cout << "waterQuantityType=" << waterQuantityType << std::endl;
    std::cout << "waterQuantityValue=" << waterQuantityValue << std::endl;
    std::cout << "steamPressure=" << steamPressure << std::endl;
    // std::cout << "steamQuantityType=" << steamQuantityType << std::endl;
    std::cout << "steamQuantityValue=" << steamQuantityValue << std::endl;

    const Deaerator& deaerator = {deaeratorPressure, ventRate,          feedwaterMassFlow,
                                  waterPressure,     waterQuantityType, waterQuantityValue,
                                  steamPressure,     steamQuantityType, steamQuantityValue};

    // std::cout << methodName << "deaerator=" << deaerator << std::endl;

    return deaerator;
}
