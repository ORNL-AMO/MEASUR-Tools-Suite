#pragma once

#include <steamModeler/util/SteamModelerLogger.h>

#include <steamModeler/domain/SteamModelCalculationsDomain.h>
#include <steamModeler/domain/SteamModelerOutputFactory.h>
#include <steamModeler/service/SteamModelRunner.h>

#include "SteamModelerInput.h"
#include "SteamModelerOutput.h"

/**
 * The entry-point into the Steam Modeler.
 * Use one of the model methods to initiate the system balancing.
 */
class SteamModeler {
  public:
    /**
     * Entry into the Steam Modeler using a SteamModelerInput object.
     * @param steamModelerInput The object containing the Steam Modeler data for processing.
     * @return The Steam Modeler processing results.
     */
    SteamModelerOutput model(const SteamModelerInput& steamModelerInput);

  private:
    /**
     * Entry into the Steam Modeler using individual data objects.
     * @param isBaselineCalc true if this is the baseline calc run.
     * @param baselinePowerDemand Amount of the baseline power demand.
     * @param headerInput All of the headers input data.
     * @param boilerInput The boiler input data.
     * @param turbineInput All of the turbines input data.
     * @param operationsInput The operational input data.
     * @return The Steam Modeler processing results.
     */
    SteamModelerOutput modeler(const bool isBaselineCalc, const double baselinePowerDemand,
                               const HeaderInput& headerInput, const BoilerInput& boilerInput,
                               const TurbineInput& turbineInput, const OperationsInput& operationsInput);

    SteamModelRunner          steamModelRunner          = SteamModelRunner();
    SteamModelerOutputFactory steamModelerOutputFactory = SteamModelerOutputFactory();

    SteamModelCalculationsDomain runModel(const bool isBaselineCalc, const double baselinePowerDemand,
                                          const HeaderInput& headerInput, const BoilerInput& boilerInput,
                                          const TurbineInput&    turbineInput,
                                          const OperationsInput& operationsInput) const;

    SteamModelerOutput makeOutput(const SteamModelCalculationsDomain& steamModelCalculationsDomain) const;

    void logSection([[maybe_unused]] const std::string& message) const;

    void logException([[maybe_unused]] const std::exception& e,
                      [[maybe_unused]] const std::string& message) const;

    void logInputData([[maybe_unused]] const bool isBaselineCalc,
                      [[maybe_unused]] const double baselinePowerDemand,
                      [[maybe_unused]] const HeaderInput& headerInput,
                      [[maybe_unused]] const BoilerInput& boilerInput,
                      [[maybe_unused]] const TurbineInput& turbineInput,
                      [[maybe_unused]] const OperationsInput& operationsInput);
};

