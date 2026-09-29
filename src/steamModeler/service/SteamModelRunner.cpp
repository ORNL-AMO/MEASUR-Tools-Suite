#include "steamModeler/service/SteamModelRunner.h"

#include <cmath>
#include <limits>

SteamModelCalculationsDomain SteamModelRunner::run(const bool isBaselineCalc, const double baselinePowerDemand,
                                                   const HeaderInput& headerInput, const BoilerInput& boilerInput,
                                                   const TurbineInput&    turbineInput,
                                                   const OperationsInput& operationsInput) const {
    const std::string methodName = std::string("SteamModelRunner::") + std::string(__func__) + ": ";

    // adjust max iterations as desired; mainly to prevent runaway modeling from unexpected issues
    const int maxIterationCount = 25;

    double initialMassFlow = massFlowCalculator.calcInitialMassFlow(headerInput);

    // Track previous iteration values to enable the secant method for faster convergence.
    // The simple fixed-point update (S_new = S_old + balance) converges at ~0.54x/iteration,
    // requiring many more iterations than the secant method (~super-linear convergence).
    double prevMassFlow = std::numeric_limits<double>::quiet_NaN();
    double prevBalance  = std::numeric_limits<double>::quiet_NaN();

    int iterationCount = 0;
    while (iterationCount < maxIterationCount) {
        iterationCount++;
        logSection(methodName + "iterationCount=" + std::to_string(iterationCount));

        try {
            return steamModelCalculator.calc(isBaselineCalc, baselinePowerDemand, headerInput, boilerInput,
                                             turbineInput, operationsInput, initialMassFlow);
        } catch (const SteamBalanceException& e) {
            const double currentMassFlow = initialMassFlow;
            initialMassFlow = handleSteamBalanceException(e, iterationCount, initialMassFlow,
                                                          prevMassFlow, prevBalance);
            prevMassFlow = currentMassFlow;
            prevBalance  = e.getAdditionalSteamNeeded();
        }
    }

    std::string msg =
        methodName + "ran " + std::to_string(maxIterationCount) + " times and did not balance system, aborting";
    SM_LOG(msg);
    throw std::logic_error(msg);
}

double SteamModelRunner::handleSteamBalanceException([[maybe_unused]] const SteamBalanceException& e,
                                                     [[maybe_unused]] const int iterationCount,
                                                     [[maybe_unused]] const double initialMassFlow,
                                                     [[maybe_unused]] const double prevMassFlow,
                                                     [[maybe_unused]] const double prevBalance) const {
    const std::string methodName = std::string("SteamModelRunner::") + std::string(__func__) + ": ";

    const double balance       = e.getAdditionalSteamNeeded();
    const double simpleStep    = e.getAdjustedInitialSteam(); // initialMassFlow + balance

    double nextMassFlow = simpleStep;

    // Apply the secant method when two prior data points are available.
    // Solves g(S) = 0 where g(S) = steamBalance = steamUse(S) - steamProduction(S).
    // Secant update: S_next = S - g(S) * (S - S_prev) / (g(S) - g_prev)
    if (!std::isnan(prevBalance) && !std::isnan(prevMassFlow)) {
        const double denominator = balance - prevBalance;
        if (std::abs(denominator) > 1e-12) {
            const double secantEstimate = initialMassFlow - balance * (initialMassFlow - prevMassFlow) / denominator;
            if (secantEstimate > 0 && !std::isnan(secantEstimate)) {
                nextMassFlow = secantEstimate;
            }
        }
    }

    SM_LOG(methodName << e);
    SM_LOG(methodName << "iterationCount=" << iterationCount
           << " with initialMassFlow=" << initialMassFlow
           << " failed; trying again with initialMassFlow=" << nextMassFlow);
    return nextMassFlow;
}

void SteamModelRunner::logSection([[maybe_unused]] const std::string& message) const {
    SM_LOG("-------- ");
    SM_LOG("-------- " << message);
    SM_LOG("-------- ");
}
