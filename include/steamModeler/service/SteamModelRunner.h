#ifndef TOOLS_SUITE_STEAMMODELRUNNER_H
#define TOOLS_SUITE_STEAMMODELRUNNER_H

#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/OperationsInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/SteamModelCalculationsDomain.h>
#include <steamModeler/service/SteamBalanceException.h>
#include <steamModeler/service/SteamModelCalculator.h>

/**
 * Runs the Steam Model.
 */
class SteamModelRunner {
public:
    /**
     * Repeatedly run the Steam Model algorithm until the system balances.
     * @param isBaselineCalc true if this is a baseline calc run.
     * @param baselinePowerDemand Amount of the baseline power demand.
     * @param headerInput All of the headers input data.
     * @param boilerInput The boiler input data.
     * @param turbineInput All of the turbines input data.
     * @param operationsInput The operational input data.
     * @return The Steam Modeler processing results.
     * @throws std::logic_error when unable to attain balanced steam model.
     */
    SteamModelCalculationsDomain
    run(const bool isBaselineCalc, const double baselinePowerDemand, const HeaderInput &headerInput,
        const BoilerInput &boilerInput, const TurbineInput &turbineInput, const OperationsInput &operationsInput) const;

private:
    const SteamModelCalculator steamModelCalculator = SteamModelCalculator();
    const MassFlowCalculator massFlowCalculator = MassFlowCalculator();

    double
    handleSteamBalanceException(const SteamBalanceException &e, const int iterationCount, const double initialMassFlow) const;

    void logSection(const std::string &message) const;
};

#endif //TOOLS_SUITE_STEAMMODELRUNNER_H
