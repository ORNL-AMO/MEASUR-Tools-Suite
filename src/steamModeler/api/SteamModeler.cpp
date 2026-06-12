#include "steamModeler/api/SteamModeler.h"

SteamModelerOutput SteamModeler::model(const SteamModelerInput& steamModelerInput) {
    const bool             isBaselineCalc      = steamModelerInput.isBaselineCalc();
    const double           baselinePowerDemand = steamModelerInput.getBaselinePowerDemand();
    const HeaderInput&     headerInput         = steamModelerInput.getHeaderInput();
    const BoilerInput&     boilerInput         = steamModelerInput.getBoilerInput();
    const TurbineInput&    turbineInput        = steamModelerInput.getTurbineInput();
    const OperationsInput& operationsInput     = steamModelerInput.getOperationsInput();

    return modeler(isBaselineCalc, baselinePowerDemand, headerInput, boilerInput, turbineInput, operationsInput);
}

SteamModelerOutput SteamModeler::modeler(const bool isBaselineCalc, const double baselinePowerDemand,
                                         const HeaderInput& headerInput, const BoilerInput& boilerInput,
                                         const TurbineInput& turbineInput, const OperationsInput& operationsInput) {
    const std::string methodName = "SteamModeler::" + std::string(__func__) + ": ";

    logInputData(isBaselineCalc, baselinePowerDemand, headerInput, boilerInput, turbineInput, operationsInput);

    logSection(methodName + "running calculations: begin");
    const SteamModelCalculationsDomain& steamModelCalculationsDomain =
        runModel(isBaselineCalc, baselinePowerDemand, headerInput, boilerInput, turbineInput, operationsInput);
    logSection(methodName + "running calculations: end");

    logSection(methodName + "populating output from calculations results: begin");
    const SteamModelerOutput& steamModelerOutput = makeOutput(steamModelCalculationsDomain);
    logSection(methodName + "populating output from calculations results: end");

    SM_LOG(methodName << "steamModelerOutput=" << steamModelerOutput);

    return steamModelerOutput;
}

void SteamModeler::logInputData([[maybe_unused]] const bool isBaselineCalc,
                                [[maybe_unused]] const double baselinePowerDemand,
                                [[maybe_unused]] const HeaderInput& headerInput,
                                [[maybe_unused]] const BoilerInput& boilerInput,
                                [[maybe_unused]] const TurbineInput& turbineInput,
                                [[maybe_unused]] const OperationsInput& operationsInput) {
    logSection("SteamModeler::logInputData:");
    SM_LOG("isBaselineCalc=" << isBaselineCalc
           << ", baselinePowerDemand=" << baselinePowerDemand
           << ", headerInput=" << headerInput
           << ", boilerInput=" << boilerInput
           << ", turbineInput=" << turbineInput
           << ", operationsInput=" << operationsInput);
}

SteamModelCalculationsDomain SteamModeler::runModel(const bool isBaselineCalc, const double baselinePowerDemand,
                                                    const HeaderInput& headerInput, const BoilerInput& boilerInput,
                                                    const TurbineInput&    turbineInput,
                                                    const OperationsInput& operationsInput) const {
    try {
        return steamModelRunner.run(isBaselineCalc, baselinePowerDemand, headerInput, boilerInput, turbineInput,
                                    operationsInput);
    } catch (std::exception& e) {
        logException(e, "SteamModeler::runModel: exception running the steam model: ");
        throw;
    }
}

SteamModelerOutput SteamModeler::makeOutput(const SteamModelCalculationsDomain& steamModelCalculationsDomain) const {
    try {
        return steamModelerOutputFactory.make(steamModelCalculationsDomain);
    } catch (std::exception& e) {
        logException(e, "SteamModeler::runModel: exception making steam model output: ");
        throw;
    }
}

void SteamModeler::logSection([[maybe_unused]] const std::string& message) const {
    SM_LOG("======== ");
    SM_LOG("======== " << message);
    SM_LOG("======== ");
}

void SteamModeler::logException([[maybe_unused]] const std::exception& e,
                                [[maybe_unused]] const std::string& message) const {
    SM_LOG("================================ ");
    SM_LOG(message);
    SM_LOG(e.what());
    SM_LOG("================================ ");
}
