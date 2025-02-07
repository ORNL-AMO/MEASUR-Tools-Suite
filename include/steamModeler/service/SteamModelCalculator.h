#ifndef TOOLS_SUITE_STEAMMODELCALCULATOR_H
#define TOOLS_SUITE_STEAMMODELCALCULATOR_H

#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/api/OperationsInput.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/BoilerFactory.h>
#include <steamModeler/domain/EnergyAndCostCalculationsDomain.h>
#include <steamModeler/domain/FlashTankFactory.h>
#include <steamModeler/domain/SteamModelCalculationsDomain.h>
#include <steamModeler/service/energy_and_cost/EnergyAndCostCalculator.h>
#include <steamModeler/service/high_pressure_header/HighPressureHeaderModeler.h>
#include <steamModeler/service/low_pressure_header/LowPressureHeaderModeler.h>
#include <steamModeler/service/medium_pressure_header/MediumPressureHeaderModeler.h>
#include <steamModeler/service/power_balance/PowerBalanceChecker.h>
#include <steamModeler/service/process_steam_usage/ProcessSteamUsageModeler.h>
#include <steamModeler/service/water_and_condensate/MakeupWaterAndCondensateHeaderModeler.h>

/**
 * Run one iteration of the Steam Modeler algorithm.
 */
class SteamModelCalculator {
public:
    SteamModelCalculationsDomain
    calc(const bool isBaselineCalc, const double baselinePowerDemand, const HeaderInput &headerInput,
         const BoilerInput &boilerInput, const TurbineInput &turbineInput, const OperationsInput &operationsInput,
         const double initialMassFlow) const;

private:
    const BoilerFactory boilerFactory = BoilerFactory();
    const DeaeratorModeler deaeratorModeler = DeaeratorModeler();
    const EnergyAndCostCalculator energyAndCostCalculator = EnergyAndCostCalculator();
    const FlashTankFactory flashTankFactory = FlashTankFactory();
    const HighPressureHeaderModeler highPressureHeaderModeler = HighPressureHeaderModeler();
    const LowPressureHeaderModeler lowPressureHeaderModeler = LowPressureHeaderModeler();
    const MakeupWaterAndCondensateHeaderModeler makeupWaterAndCondensateHeaderModeler = MakeupWaterAndCondensateHeaderModeler();
    const MediumPressureHeaderModeler mediumPressureHeaderModeler = MediumPressureHeaderModeler();
    const PowerBalanceChecker powerBalanceChecker = PowerBalanceChecker();
    const ProcessSteamUsageModeler processSteamUsageModeler = ProcessSteamUsageModeler();
};

#endif //TOOLS_SUITE_STEAMMODELCALCULATOR_H
