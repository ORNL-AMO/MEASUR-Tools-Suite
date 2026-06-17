#include "steamModeler/service/SteamModelCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

SteamModelCalculationsDomain SteamModelCalculator::calc(const bool isBaselineCalc, const double baselinePowerDemand,
                                                        const HeaderInput& headerInput, const BoilerInput& boilerInput,
                                                        const TurbineInput&    turbineInput,
                                                        const OperationsInput& operationsInput,
                                                        const double           initialMassFlow) const {
    const std::string methodName = "SteamModelCalculator::" + std::string(__func__) + ": ";

    const HeaderWithHighestPressure&                 highPressureHeaderInput   = headerInput.getHighPressureHeader();
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput = headerInput.getMediumPressureHeader();
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput    = headerInput.getLowPressureHeader();
    const int                                        headerCountInput          = headerInput.getHeaderCount();

    const PressureTurbine&   highToLowTurbineInput    = turbineInput.getHighToLowTurbine();
    const PressureTurbine&   highToMediumTurbineInput = turbineInput.getHighToMediumTurbine();
    const CondensingTurbine& condensingTurbineInput   = turbineInput.getCondensingTurbine();
    const PressureTurbine&   mediumToLowTurbineInput  = turbineInput.getMediumToLowTurbine();

    SM_LOG(methodName << "calculating boiler");
    const Boiler& boiler = boilerFactory.make(headerInput, boilerInput, initialMassFlow);
    SM_LOG(methodName << "boiler=" << boiler);

    SM_LOG(methodName << "calculating blowdownFlashTank");
    const std::shared_ptr<FlashTank>& blowdownFlashTank = flashTankFactory.make(headerInput, boilerInput, boiler);
    SM_LOG(methodName << "blowdownFlashTank=" << blowdownFlashTank);

    SM_LOG(methodName << "running highPressureHeaderModeler");
    HighPressureHeaderCalculationsDomain highPressureHeaderCalculationsDomain = highPressureHeaderModeler.model(
        headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput, lowPressureHeaderInput,
        highToMediumTurbineInput, highToLowTurbineInput, condensingTurbineInput, boiler);
    SM_LOG(methodName << "highPressureHeaderCalculationsDomain=" << highPressureHeaderCalculationsDomain);

    SM_LOG(methodName << "running mediumPressureHeaderModeler");
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain =
        mediumPressureHeaderModeler.model(headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput,
                                          lowPressureHeaderInput, highToMediumTurbineInput, highToLowTurbineInput,
                                          mediumToLowTurbineInput, condensingTurbineInput, boiler,
                                          highPressureHeaderCalculationsDomain);
    SM_LOG(methodName << "mediumPressureHeaderCalculationsDomain=" << mediumPressureHeaderCalculationsDomain);

    SM_LOG(methodName << "running lowPressureHeaderModeler");
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>& lowPressureHeaderCalculationsDomain =
        lowPressureHeaderModeler.model(headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput,
                                       lowPressureHeaderInput, highToLowTurbineInput, mediumToLowTurbineInput,
                                       condensingTurbineInput, boilerInput, boiler, blowdownFlashTank,
                                       highPressureHeaderCalculationsDomain, mediumPressureHeaderCalculationsDomain);
    SM_LOG(methodName << "lowPressureHeaderCalculationsDomain=" << lowPressureHeaderCalculationsDomain);

    SM_LOG(methodName << "running makeupWaterAndCondensateHeaderModeler");
    MakeupWaterAndCondensateHeaderCalculationsDomain makeupWaterAndCondensateHeaderCalculationsDomain =
        makeupWaterAndCondensateHeaderModeler.model(
            headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput, lowPressureHeaderInput, boilerInput,
            operationsInput, condensingTurbineInput, boiler, blowdownFlashTank, highPressureHeaderCalculationsDomain,
            mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain);
    SM_LOG(methodName << "makeupWaterAndCondensateHeaderCalculationsDomain=" << makeupWaterAndCondensateHeaderCalculationsDomain);

    SM_LOG(methodName << "running deaeratorModeler");
    Deaerator deaerator =
        deaeratorModeler.model(headerCountInput, boilerInput, boiler, highPressureHeaderCalculationsDomain,
                               mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain,
                               makeupWaterAndCondensateHeaderCalculationsDomain);
    SM_LOG(methodName << "deaerator=" << deaerator);

    SM_LOG(methodName << "running powerBalanceChecker");
    const double deaeratorInletSteamMassFlow = deaerator.getInletSteamProperties().massFlow;
    const PowerBalanceCheckerCalculationsDomain& powerBalanceCheckerCalculationsDomain = powerBalanceChecker.check(
        headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput, lowPressureHeaderInput,
        highToLowTurbineInput, highToMediumTurbineInput, mediumToLowTurbineInput, boilerInput, condensingTurbineInput,
        operationsInput, boiler, blowdownFlashTank, deaeratorInletSteamMassFlow, highPressureHeaderCalculationsDomain,
        mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain,
        makeupWaterAndCondensateHeaderCalculationsDomain);
    SM_LOG(methodName << "powerBalanceCheckerCalculationsDomain=" << powerBalanceCheckerCalculationsDomain);

    const std::shared_ptr<LowPressureVentedSteamCalculationsDomain>& lowPressureVentedSteamCalculationsDomain =
        powerBalanceCheckerCalculationsDomain.lowPressureVentedSteamCalculationsDomain;
    if (lowPressureVentedSteamCalculationsDomain != nullptr) {
        deaerator = lowPressureVentedSteamCalculationsDomain->deaerator;
    }

    SM_LOG(methodName << "running processSteamUsageCalculator");
    const ProcessSteamUsageCalculationsDomain& processSteamUsageCalculationsDomain =
        processSteamUsageModeler.model(headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput,
                                       lowPressureHeaderInput, highPressureHeaderCalculationsDomain,
                                       mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain);
    SM_LOG(methodName << "processSteamUsageCalculationsDomain=" << processSteamUsageCalculationsDomain);

    SM_LOG(methodName << "running energyAndCostCalculator");
    const MakeupWaterVolumeFlowCalculationsDomain& makeupWaterVolumeFlowCalculationsDomain =
        makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterVolumeFlowCalculationsDomain;
    const double makeupWaterVolumeFlowAnnual = makeupWaterVolumeFlowCalculationsDomain.makeupWaterVolumeFlowAnnual;
    const EnergyAndCostCalculationsDomain& energyAndCostCalculationsDomain = energyAndCostCalculator.calc(
        isBaselineCalc, baselinePowerDemand, operationsInput, boiler, highPressureHeaderCalculationsDomain,
        mediumPressureHeaderCalculationsDomain, makeupWaterVolumeFlowAnnual);
    SM_LOG(methodName << "energyAndCostCalculationsDomain=" << energyAndCostCalculationsDomain);

    return {boiler,
            blowdownFlashTank,
            highPressureHeaderCalculationsDomain,
            mediumPressureHeaderCalculationsDomain,
            lowPressureHeaderCalculationsDomain,
            makeupWaterAndCondensateHeaderCalculationsDomain,
            deaerator,
            powerBalanceCheckerCalculationsDomain,
            processSteamUsageCalculationsDomain,
            energyAndCostCalculationsDomain};
}
