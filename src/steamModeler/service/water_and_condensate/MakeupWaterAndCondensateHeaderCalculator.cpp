#include "steamModeler/service/water_and_condensate/MakeupWaterAndCondensateHeaderCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

SteamSystemModelerTool::FluidProperties MakeupWaterAndCondensateHeaderCalculator::calc(
    const BoilerInput& boilerInput, const CondensingTurbine& condensingTurbineInput,
    const SteamSystemModelerTool::FluidProperties& returnCondensate,
    const std::shared_ptr<HeatExchanger::Output>&  heatExchangerOutput,
    const SteamSystemModelerTool::FluidProperties& makeupWaterAndMassFlow,
    const HighPressureHeaderCalculationsDomain&    highPressureHeaderCalculationsDomain) const {
    SteamSystemModelerTool::FluidProperties headerResult =
        makeHeaderResult(boilerInput, condensingTurbineInput, returnCondensate, heatExchangerOutput,
                         makeupWaterAndMassFlow, highPressureHeaderCalculationsDomain);

    SteamSystemModelerTool::SteamPropertiesOutput steamPropertiesOutput = calcSteamProperties(headerResult);

    updateHeaderWithSteam(headerResult, steamPropertiesOutput);

    return headerResult;
}

SteamSystemModelerTool::FluidProperties MakeupWaterAndCondensateHeaderCalculator::makeHeaderResult(
    const BoilerInput& boilerInput, const CondensingTurbine& condensingTurbineInput,
    const SteamSystemModelerTool::FluidProperties& returnCondensate,
    const std::shared_ptr<HeatExchanger::Output>&  heatExchangerOutput,
    const SteamSystemModelerTool::FluidProperties& makeupWaterAndMassFlow,
    const HighPressureHeaderCalculationsDomain&    highPressureHeaderCalculationsDomain) const {
    const std::string methodName =
        std::string("MakeupWaterAndCondensateHeaderCalculator::") + std::string(__func__) + ": ";

    const std::shared_ptr<Turbine>& condensingTurbine       = highPressureHeaderCalculationsDomain.condensingTurbine;
    const double                    boilerDeaeratorPressure = boilerInput.getDeaeratorPressure();

    const Header& makeupWaterAndCondensateHeader =
        headerFactory.make(boilerDeaeratorPressure, returnCondensate, boilerInput, heatExchangerOutput,
                           makeupWaterAndMassFlow, condensingTurbineInput, condensingTurbine);
    SM_LOG(methodName << "makeupWaterAndCondensateHeader=" << makeupWaterAndCondensateHeader);

    const SteamSystemModelerTool::FluidProperties& fluidProperties =
        fluidPropertiesFactory.make(makeupWaterAndCondensateHeader);
    SM_LOG(methodName << "makeupWaterAndCondensateHeader as FluidProperties=" << fluidProperties);

    return fluidProperties;
}

SteamSystemModelerTool::SteamPropertiesOutput MakeupWaterAndCondensateHeaderCalculator::calcSteamProperties(
    const SteamSystemModelerTool::FluidProperties& fluidProperties) const {
    const std::string methodName =
        std::string("MakeupWaterAndCondensateHeaderCalculator::") + std::string(__func__) + ": ";

    const double pressure         = fluidProperties.pressure;
    const double specificEnthalpy = fluidProperties.specificEnthalpy;

    SteamProperties steamProperties = {pressure, SteamProperties::ThermodynamicQuantity::ENTHALPY, specificEnthalpy};
    const SteamSystemModelerTool::SteamPropertiesOutput& steamPropertiesOutput = steamProperties.calculate();
    SM_LOG(methodName << "pressure=" << pressure << ", specificEnthalpy=" << specificEnthalpy << ", ThermodynamicQuantity=ENTHALPY" << "; result steamPropertiesOutput=" << steamPropertiesOutput);

    return steamPropertiesOutput;
}

void MakeupWaterAndCondensateHeaderCalculator::updateHeaderWithSteam(
    SteamSystemModelerTool::FluidProperties&             headerResult,
    const SteamSystemModelerTool::SteamPropertiesOutput& steamPropertiesOutput) const {
    const double specificVolume = steamPropertiesOutput.specificVolume;
    headerResult.specificVolume = specificVolume;
}
