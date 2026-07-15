#include "steamModeler/service/medium_pressure_header/MediumPressureHeaderModeler.h"
#include "steamModeler/util/SteamModelerLogger.h"

std::shared_ptr<MediumPressureHeaderCalculationsDomain> MediumPressureHeaderModeler::model(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const PressureTurbine& highToMediumTurbineInput, const PressureTurbine& highToLowTurbineInput,
    const PressureTurbine& mediumToLowTurbineInput, const CondensingTurbine& condensingTurbineInput,
    const Boiler& boiler, HighPressureHeaderCalculationsDomain& highPressureHeaderCalculationsDomain) const {
    const std::string methodName = std::string("MediumPressureHeaderModeler::") + std::string(__func__) + ": ";

    std::shared_ptr<MediumPressureHeaderCalculationsDomain> mediumPressureHeaderCalculationsDomain = nullptr;

    // adjust max iterations as desired; mainly to prevent runaway modeling from unexpected issues
    const int maxIterationCount = 25;

    int  iterationCount                 = 0;
    bool isMediumPressureHeaderBalanced = false;
    while (!isMediumPressureHeaderBalanced && iterationCount < maxIterationCount) {
        iterationCount++;
        SM_LOG(methodName << "running mediumPressureHeaderModeler iterationCount=" << iterationCount);

        try {
            mediumPressureHeaderCalculationsDomain = modelIteration(
                headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput, lowPressureHeaderInput,
                highToMediumTurbineInput, highToLowTurbineInput, mediumToLowTurbineInput, condensingTurbineInput,
                boiler, highPressureHeaderCalculationsDomain);
            // no exception means it is balanced (or not in use!)
            isMediumPressureHeaderBalanced = true;

            if (mediumPressureHeaderCalculationsDomain != nullptr) {
                highPressureHeaderCalculationsDomain.highToLowPressureTurbine =
                    mediumPressureHeaderCalculationsDomain->highToLowPressureTurbineUpdated;
                highPressureHeaderCalculationsDomain.highToLowPressureTurbineIdeal =
                    mediumPressureHeaderCalculationsDomain->highToLowPressureTurbineIdealUpdated;
            }
        } catch (const ReducedSteamException& e) {
            // TODO extract methods
            SM_LOG(methodName << "ReducedSteamException: " << actionMessage << "; rerunning MediumPressureHeaderModeler with updated highToLowPressureTurbine");
            const std::shared_ptr<Turbine>& highToLowPressureTurbine      = e.getHighToLowPressureTurbineUpdated();
            const std::shared_ptr<Turbine>& highToLowPressureTurbineIdeal = e.getHighToLowPressureTurbineIdealUpdated();

            highPressureHeaderCalculationsDomain.highToLowPressureTurbine      = highToLowPressureTurbine;
            highPressureHeaderCalculationsDomain.highToLowPressureTurbineIdeal = highToLowPressureTurbineIdeal;

            // 2G. Calculate high to medium steam turbine if in use
            const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput =
                highPressureHeaderCalculationsDomain.highPressureHeaderOutput;
            const std::shared_ptr<Turbine>& condensingTurbine = highPressureHeaderCalculationsDomain.condensingTurbine;
            const HighToMediumSteamTurbineCalculationsDomain& highToMediumSteamTurbineCalculationsDomain =
                highPressureHeaderModeler.calcHighToMediumSteamTurbine(
                    headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput, lowPressureHeaderInput,
                    highToMediumTurbineInput, highToLowTurbineInput, condensingTurbineInput, boiler,
                    highPressureHeaderOutput, condensingTurbine, highToLowPressureTurbine,
                    highToLowPressureTurbineIdeal);
            const std::shared_ptr<Turbine>& highToMediumPressureTurbine =
                highToMediumSteamTurbineCalculationsDomain.highToMediumPressureTurbine;
            const std::shared_ptr<Turbine>& highToMediumPressureTurbineIdeal =
                highToMediumSteamTurbineCalculationsDomain.highToMediumPressureTurbineIdeal;

            const std::shared_ptr<Turbine>& highToLowPressureTurbineUpdated =
                highToMediumSteamTurbineCalculationsDomain.highToLowPressureTurbineUpdated;
            const std::shared_ptr<Turbine>& highToLowPressureTurbineIdealUpdated =
                highToMediumSteamTurbineCalculationsDomain.highToLowPressureTurbineIdealUpdated;

            highPressureHeaderCalculationsDomain.highToMediumPressureTurbine      = highToMediumPressureTurbine;
            highPressureHeaderCalculationsDomain.highToMediumPressureTurbineIdeal = highToMediumPressureTurbineIdeal;

            highPressureHeaderCalculationsDomain.highToLowPressureTurbine      = highToLowPressureTurbineUpdated;
            highPressureHeaderCalculationsDomain.highToLowPressureTurbineIdeal = highToLowPressureTurbineIdealUpdated;
        }
    }

    if (!isMediumPressureHeaderBalanced) {
        const std::string msg = "Could not reduce enough steam from highToLowPressureTurbine to balance system in " +
                                std::to_string(iterationCount) + " attempts";
        SM_LOG(methodName << msg);
        throw UnableToBalanceException(msg);
    }

    return mediumPressureHeaderCalculationsDomain;
}

std::shared_ptr<MediumPressureHeaderCalculationsDomain> MediumPressureHeaderModeler::modelIteration(
    const int headerCountInput, const HeaderWithHighestPressure& highPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const PressureTurbine& highToMediumTurbineInput, const PressureTurbine& highToLowTurbineInput,
    const PressureTurbine& mediumToLowTurbineInput, const CondensingTurbine& condensingTurbineInput,
    const Boiler& boiler, const HighPressureHeaderCalculationsDomain& highPressureHeaderCalculationsDomain) const {
    const std::string methodName = std::string("MediumPressureHeaderModeler::") + std::string(__func__) + ": ";

    // if medium pressure header exists
    if (headerCountInput == 3) {
        SM_LOG(methodName << "medium pressure header provided, processing");

        // TODO move these/trace ptrs for NPE elim, into highToMediumPrvCalculator.calc and
        // mediumPressureHeaderCalculator.calc
        const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput =
            highPressureHeaderCalculationsDomain.highPressureHeaderOutput;
        const std::shared_ptr<FlashTank>& highPressureCondensateFlashTank =
            highPressureHeaderCalculationsDomain.highPressureCondensateFlashTank;
        const std::shared_ptr<Turbine>& condensingTurbine = highPressureHeaderCalculationsDomain.condensingTurbine;
        const std::shared_ptr<Turbine>& highToMediumPressureTurbine =
            highPressureHeaderCalculationsDomain.highToMediumPressureTurbine;
        const std::shared_ptr<Turbine>& highToLowPressureTurbine =
            highPressureHeaderCalculationsDomain.highToLowPressureTurbine;
        const std::shared_ptr<Turbine>& highToLowPressureTurbineIdeal =
            highPressureHeaderCalculationsDomain.highToLowPressureTurbineIdeal;

        // 3A. Calculate High to Medium PRV
        SM_LOG(methodName << "calculating high to medium pressure PRV");
        const std::shared_ptr<PrvWithoutDesuperheating>& highToMediumPressurePrv = highToMediumPrvCalculator.calc(
            highPressureHeaderInput, mediumPressureHeaderInput, highToLowTurbineInput, highToMediumTurbineInput,
            condensingTurbineInput, highToLowPressureTurbine, highToMediumPressureTurbine, condensingTurbine, boiler,
            highPressureHeaderOutput);
        SM_LOG(methodName << "highToMediumPressurePrv=" << highToMediumPressurePrv);

        // 3B. Model Medium Pressure Header
        // 3B1. Calculate inlets for medium pressure header
        SM_LOG(methodName << "calculating medium pressure header");
        const MediumPressureHeaderCalculatorOutput& mediumPressureHeaderCalculatorOutput =
            mediumPressureHeaderCalculator.calc(
                boiler, highToLowTurbineInput, highToLowPressureTurbine, highToLowPressureTurbineIdeal,
                highPressureHeaderOutput, mediumPressureHeaderInput, highToMediumPressurePrv, highToMediumTurbineInput,
                highToMediumPressureTurbine, highPressureCondensateFlashTank, lowPressureHeaderInput);
        SM_LOG(methodName << "mediumPressureHeaderCalculatorOutput=" << mediumPressureHeaderCalculatorOutput);

        const SteamSystemModelerTool::FluidProperties& mediumPressureHeaderOutputOriginal =
            mediumPressureHeaderCalculatorOutput.mediumPressureHeaderOutput;
        std::shared_ptr<Turbine> highToLowPressureTurbineUpdated =
            mediumPressureHeaderCalculatorOutput.highToLowPressureTurbineUpdated;
        std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated =
            mediumPressureHeaderCalculatorOutput.highToLowPressureTurbineIdealUpdated;

        // 3C. Calculate Heat Loss for Remaining Steam in Medium Pressure Header
        SM_LOG(methodName << "calculating mediumPressureHeader heat loss");
        const HeatLoss& heatLoss = heatLossFactory.make(mediumPressureHeaderInput, mediumPressureHeaderOutputOriginal);
        SM_LOG(methodName << "mediumPressureHeader heatLoss=" << heatLoss);

        SM_LOG(methodName << "updating mediumPressureHeader with heat loss");
        const SteamSystemModelerTool::FluidProperties& mediumPressureHeaderOutput =
            fluidPropertiesFactory.makeWithSpecificVolume(heatLoss, mediumPressureHeaderOutputOriginal.specificVolume);
        SM_LOG(methodName << "mediumPressureHeaderOutput=" << mediumPressureHeaderOutput);

        // 3D. Calculate Medium Pressure Condensate
        SM_LOG(methodName << "calculating medium pressure condensate");
        const SteamSystemModelerTool::FluidProperties& mediumPressureCondensate =
            mediumPressureCondensateCalculator.calc(mediumPressureHeaderInput);
        SM_LOG(methodName << "mediumPressureCondensate=" << mediumPressureCondensate);

        // 3E. Calculate medium to low steam turbine if in use
        SM_LOG(methodName << "calculating medium to low pressure turbine");
        const MediumToLowPressureTurbineCalculatorOutput mediumToLowPressureTurbineCalculatorOutput =
            mediumToLowPressureTurbineCalculator.calc(highToLowTurbineInput, highToLowPressureTurbineUpdated,
                                                      highToLowPressureTurbineIdealUpdated, mediumToLowTurbineInput,
                                                      highPressureHeaderOutput, mediumPressureHeaderInput,
                                                      mediumPressureHeaderOutput, lowPressureHeaderInput, boiler);
        SM_LOG(methodName << "mediumToLowPressureTurbineCalculatorOutput=" << mediumToLowPressureTurbineCalculatorOutput);
        const std::shared_ptr<Turbine>& mediumToLowPressureTurbine =
            mediumToLowPressureTurbineCalculatorOutput.mediumToLowPressureTurbine;
        const std::shared_ptr<Turbine>& mediumToLowPressureTurbineIdeal =
            mediumToLowPressureTurbineCalculatorOutput.mediumToLowPressureTurbineIdeal;
        highToLowPressureTurbineUpdated = mediumToLowPressureTurbineCalculatorOutput.highToLowPressureTurbineUpdated;
        highToLowPressureTurbineIdealUpdated =
            mediumToLowPressureTurbineCalculatorOutput.highToLowPressureTurbineIdealUpdated;

        const MediumPressureHeaderCalculationsDomain& domain = {
            highToMediumPressurePrv,         highPressureCondensateFlashTank, heatLoss,
            mediumPressureHeaderOutput,      mediumPressureCondensate,        mediumToLowPressureTurbine,
            mediumToLowPressureTurbineIdeal, highToLowPressureTurbineUpdated, highToLowPressureTurbineIdealUpdated};
        return std::make_shared<MediumPressureHeaderCalculationsDomain>(domain);
    }
    else {
        SM_LOG(methodName << "medium pressure header not provided, skipping");
        return nullptr;
    }
}
