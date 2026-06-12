#include "steamModeler/domain/HeaderFactory.h"
#include "steamModeler/util/SteamModelerLogger.h"

const Header HeaderFactory::make(const double& headerPressure, const Boiler& boiler) const {
    const std::string methodName = "HeaderFactory::" + std::string(__func__) + ": ";

    SM_LOG(methodName << "making header");

    std::vector<Inlet> inlets = inletFactory.make(boiler);

    const Header header = {headerPressure, inlets};
    SM_LOG(methodName << "header=" << header);

    return header;
}

const Header HeaderFactory::make(const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
                                 const std::shared_ptr<PrvWithoutDesuperheating>& prvWithoutDesuperheating,
                                 const PressureTurbine&                           highToMediumTurbineInput,
                                 const std::shared_ptr<Turbine>&                  highToMediumPressureTurbine,
                                 const std::shared_ptr<FlashTank>& highPressureCondensateFlashTank) const {
    const std::string methodName = "HeaderFactory::" + std::string(__func__) + ": ";

    SM_LOG(methodName << "making header");

    const double headerPressure = mediumPressureHeaderInput->getPressure();

    // High to medium PRV
    SM_LOG(methodName << "adding highToMediumPrv inlet");
    const Inlet        highToMediumPrvInlet = inletFactory.make(prvWithoutDesuperheating);
    std::vector<Inlet> inlets               = {highToMediumPrvInlet};

    // High to medium turbine
    const bool isUseTurbine = highToMediumTurbineInput.isUseTurbine();
    SM_LOG(methodName << "highToMediumTurbineInput.isUseTurbine=" << isUseTurbine);

    if (isUseTurbine) {
        SM_LOG(methodName << "isUseTurbine=true, adding highToMediumPressureTurbine inlet");

        Inlet highToMediumTurbineInlet = inletFactory.make(highToMediumPressureTurbine);
        SM_LOG(methodName << "highToMediumTurbineInlet=" << highToMediumTurbineInlet);
        inlets.push_back(highToMediumTurbineInlet);
    }
    else {
        SM_LOG(methodName << "isUseTurbine=false, skipping highToMediumPressureTurbine inlet");
    }

    // High pressure flashed condensate
    const bool isFlashCondensate = mediumPressureHeaderInput->isFlashCondensate();
    SM_LOG(methodName << "mediumPressureHeaderInput->isFlashCondensate=" << isFlashCondensate);

    if (isFlashCondensate) {
        SM_LOG(methodName << "isFlashCondensate=true, adding highPressureFlashedCondensate inlet");
        Inlet highPressureFlashedCondensateInlet = inletFactory.makeFromOutletGas(highPressureCondensateFlashTank);
        SM_LOG(methodName << "highPressureFlashedCondensateInlet=" << highPressureFlashedCondensateInlet);
        inlets.push_back(highPressureFlashedCondensateInlet);
    }
    else {
        SM_LOG(methodName << "isFlashCondensate=false, skipping highPressureFlashedCondensate inlet");
    }

    const Header header = {headerPressure, inlets};
    SM_LOG(methodName << "header=" << header);

    return header;
}

const Header HeaderFactory::make(const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                 const std::shared_ptr<FlashTank>&                highPressureCondensateFlashTank,
                                 const SteamSystemModelerTool::FluidProperties&   mediumPressureCondensate) const {
    const std::string methodName = "HeaderFactory::" + std::string(__func__) + ": ";

    SM_LOG(methodName << "making header");

    const double headerPressure = lowPressureHeaderInput->getPressure();

    Inlet highPressureFlashedCondensateInlet = inletFactory.makeFromOutletLiquid(highPressureCondensateFlashTank);
    SM_LOG(methodName << "highPressureFlashedCondensateInlet=" << highPressureFlashedCondensateInlet);

    Inlet mediumPressureCondensateInlet = inletFactory.makeWithEnthalpy(mediumPressureCondensate);
    SM_LOG(methodName << "mediumPressureCondensateInlet=" << mediumPressureCondensateInlet);

    std::vector<Inlet> inlets = {highPressureFlashedCondensateInlet, mediumPressureCondensateInlet};

    const Header header = {headerPressure, inlets};
    SM_LOG(methodName << "header=" << header);

    return header;
}

const Header HeaderFactory::make(const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
                                 const SteamSystemModelerTool::FluidProperties&   highPressureCondensate,
                                 const SteamSystemModelerTool::FluidProperties&   mediumPressureCondensate) const {
    const std::string methodName = "HeaderFactory::" + std::string(__func__) + ": ";

    SM_LOG(methodName << "making header");

    const double headerPressure = lowPressureHeaderInput->getPressure();

    Inlet highPressureCondensateInlet = inletFactory.makeWithEnthalpy(highPressureCondensate);
    SM_LOG(methodName << "highPressureCondensateInlet=" << highPressureCondensateInlet);

    Inlet mediumPressureCondensateInlet = inletFactory.makeWithEnthalpy(mediumPressureCondensate);
    SM_LOG(methodName << "mediumPressureCondensateInlet=" << mediumPressureCondensateInlet);

    std::vector<Inlet> inlets = {highPressureCondensateInlet, mediumPressureCondensateInlet};

    const Header header = {headerPressure, inlets};
    SM_LOG(methodName << "header=" << header);

    return header;
}

const Header HeaderFactory::make(
    const double headerCountInput, const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput,
    const PressureTurbine& highToLowTurbineInput, const PressureTurbine& mediumToLowTurbineInput,
    const BoilerInput&                               boilerInput,
    const std::shared_ptr<PrvWithoutDesuperheating>& lowPressurePrvWithoutDesuperheating,
    const std::shared_ptr<Turbine>& highToLowPressureTurbine, const std::shared_ptr<FlashTank>& blowdownFlashTank,
    const LowPressureFlashedSteamIntoHeaderCalculatorDomain&       lowPressureFlashedSteamIntoHeaderCalculatorDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain) const {
    const std::string methodName = "HeaderFactory::" + std::string(__func__) + ": ";

    SM_LOG(methodName << "making header");

    // Low pressure PRV; PRV always exists
    const double headerPressure = lowPressureHeaderInput->getPressure();

    const Inlet        lowPrvInlet = inletFactory.make(lowPressurePrvWithoutDesuperheating);
    std::vector<Inlet> inlets      = {lowPrvInlet};

    // High to low pressure turbine
    const bool isUseTurbineHighToLow = highToLowTurbineInput.isUseTurbine();
    SM_LOG(methodName << "highToLowTurbineInput.isUseTurbine=" << isUseTurbineHighToLow);

    if (isUseTurbineHighToLow) {
        SM_LOG(methodName << "highToLowTurbineInput.isUseTurbine=true, adding highToLowPressureTurbine");
        const Inlet& inlet = inletFactory.make(highToLowPressureTurbine);
        SM_LOG(methodName << "highToLowPressureTurbineInlet=" << inlet);
        inlets.push_back(inlet);
    }
    else {
        SM_LOG(methodName << "highToLowTurbineInput.isUseTurbine=false, skipping highToLowPressureTurbine");
    }

    // Medium to low pressure turbine
    const bool isUseTurbineMediumToLow = mediumToLowTurbineInput.isUseTurbine();
    SM_LOG(methodName << "mediumToLowTurbineInput.isUseTurbine=" << isUseTurbineMediumToLow);

    if (headerCountInput == 3 && isUseTurbineMediumToLow) {
        SM_LOG(methodName << "mediumToLowTurbineInput.isUseTurbineMediumToLow=true, adding mediumToLowPressureTurbine");
        const std::shared_ptr<Turbine>& mediumToLowPressureTurbine =
            mediumPressureHeaderCalculationsDomain->mediumToLowPressureTurbine;
        const Inlet& inlet = inletFactory.make(mediumToLowPressureTurbine);
        SM_LOG(methodName << "mediumToLowPressureTurbineInlet=" << inlet);
        inlets.push_back(inlet);
    }
    else {
        SM_LOG(methodName << "mediumToLowTurbineInput.isUseTurbineMediumToLow=false, skipping mediumToLowPressureTurbine");
    }

    // Flashed condensate into header
    const bool isFlashCondensate = lowPressureHeaderInput->isFlashCondensate();
    SM_LOG(methodName << "lowPressureHeaderInput.isFlashCondensate=" << isFlashCondensate);

    if (isFlashCondensate) {
        // if medium pressure header exists, use medium pressure flash tank
        if (headerCountInput == 3) {
            SM_LOG(methodName << "lowPressureHeaderInput.isFlashCondensate=true & 3 headers, adding mediumPressureCondensateFlashTank");

            const std::shared_ptr<FlashTank>& mediumPressureCondensateFlashTank =
                lowPressureFlashedSteamIntoHeaderCalculatorDomain.mediumPressureCondensateFlashTank;
            const Inlet& inlet = inletFactory.makeFromOutletGas(mediumPressureCondensateFlashTank);
            SM_LOG(methodName << "mediumPressureCondensateFlashTankInlet=" << inlet);

            inlets.push_back(inlet);
        }
        else {
            SM_LOG(methodName << "lowPressureHeaderInput.isFlashCondensate=true & not 3 headers, adding highPressureCondensateFlashTank");

            // if only high and low header, high pressure flash tank
            const std::shared_ptr<FlashTank>& highPressureCondensateFlashTank =
                lowPressureFlashedSteamIntoHeaderCalculatorDomain.highPressureCondensateFlashTank;
            const Inlet& inlet = inletFactory.makeFromOutletGas(highPressureCondensateFlashTank);
            SM_LOG(methodName << "highPressureCondensateFlashTankInlet=" << inlet);

            inlets.push_back(inlet);
        }
    }

    // Blowdown flash tank outlet gas
    const bool isBlowdownFlashed = boilerInput.isBlowdownFlashed();
    SM_LOG(methodName << "boilerInput.isBlowdownFlashed=" << isFlashCondensate);

    if (isBlowdownFlashed) {
        SM_LOG(methodName << "boilerInput.isBlowdownFlashed=true, adding blowdownFlashTank");

        const Inlet& inlet = inletFactory.makeFromOutletGas(blowdownFlashTank);
        SM_LOG(methodName << "blowdownFlashTankInlet=" << inlet);

        inlets.push_back(inlet);
    }
    else {
        SM_LOG(methodName << "boilerInput.isBlowdownFlashed=false, skipping blowdownFlashTank");
    }

    const Header header = {headerPressure, inlets};
    SM_LOG(methodName << "header=" << header);

    return header;
}

const Header HeaderFactory::make(
    const int headerCountInput, const double headerPressure,
    const std::shared_ptr<FlashTank>&                              highPressureCondensateFlashTank,
    const HighPressureHeaderCalculationsDomain&                    highPressureHeaderCalculationsDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>&    lowPressureHeaderCalculationsDomain) const {
    const std::string methodName = "HeaderFactory::" + std::string(__func__) + ": ";

    SM_LOG(methodName << "making header");

    std::vector<Inlet> inlets = {};

    const bool isFlashTankNull = isMediumPressureCondensateFlashTankNull(lowPressureHeaderCalculationsDomain);
    if (highPressureCondensateFlashTank == nullptr && isFlashTankNull) {
        SM_LOG(methodName << "highPressureCondensateFlashTank not specified & mediumPressureCondensateFlashTank not specified" << ", adding highPressureCondensate");
        const SteamSystemModelerTool::FluidProperties& highPressureCondensate =
            highPressureHeaderCalculationsDomain.highPressureCondensate;
        const Inlet& inlet = inletFactory.makeWithEnthalpy(highPressureCondensate);
        SM_LOG(methodName << "highPressureCondensateInlet=" << inlet);

        inlets.push_back(inlet);
    }
    else if (isFlashTankNull) {
        SM_LOG(methodName << "highPressureCondensateFlashTank specified & mediumPressureCondensateFlashTank not specified" << ", adding highPressureCondensateFlashTank");
        const Inlet& inlet = inletFactory.makeFromOutletLiquid(highPressureCondensateFlashTank);
        SM_LOG(methodName << "highPressureCondensateFlashTankInlet=" << inlet);

        inlets.push_back(inlet);
    }

    if (headerCountInput > 1) {
        SM_LOG(methodName << "lowPressureHeader specified, adding lowPressureCondensate");

        const SteamSystemModelerTool::FluidProperties& lowPressureCondensate =
            lowPressureHeaderCalculationsDomain->lowPressureCondensate;
        const Inlet& inlet = inletFactory.makeWithEnthalpy(lowPressureCondensate);
        SM_LOG(methodName << "lowPressureCondensateInlet=" << inlet);

        inlets.push_back(inlet);
    }
    else {
        SM_LOG(methodName << "lowPressureHeader not exists, skipping lowPressureCondensate");
    }

    if (headerCountInput == 3) {
        if (isFlashTankNull) {
            SM_LOG(methodName << "mediumPressureHeader specified & mediumPressureCondensateFlashTank not specified" << ", adding mediumPressureCondensate");

            const SteamSystemModelerTool::FluidProperties& mediumPressureCondensate =
                mediumPressureHeaderCalculationsDomain->mediumPressureCondensate;
            const Inlet& inlet = inletFactory.makeWithEnthalpy(mediumPressureCondensate);
            SM_LOG(methodName << "mediumPressureCondensateInlet=" << inlet);

            inlets.push_back(inlet);
        }
        else {
            SM_LOG(methodName << "mediumPressureHeader specified & mediumPressureCondensateFlashTank specified" << ", adding mediumPressureCondensateFlashTank");

            const LowPressureFlashedSteamIntoHeaderCalculatorDomain& lowPressureFlashedSteamIntoHeaderCalculatorDomain =
                lowPressureHeaderCalculationsDomain->lowPressureFlashedSteamIntoHeaderCalculatorDomain;
            const std::shared_ptr<FlashTank>& mediumPressureCondensateFlashTank =
                lowPressureFlashedSteamIntoHeaderCalculatorDomain.mediumPressureCondensateFlashTank;
            const Inlet& inlet = inletFactory.makeFromOutletLiquid(mediumPressureCondensateFlashTank);
            SM_LOG(methodName << "mediumPressureCondensateFlashTankInlet=" << inlet);

            inlets.push_back(inlet);
        }
    }

    const Header header = {headerPressure, inlets};
    SM_LOG(methodName << "header=" << header);

    return header;
}

const Header HeaderFactory::make(
    const int headerCountInput, const HighPressureHeaderCalculationsDomain& highPressureHeaderCalculationsDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>&    lowPressureHeaderCalculationsDomain) const {
    const double lowHeaderPressure = determineLowHeaderPressure(headerCountInput, highPressureHeaderCalculationsDomain,
                                                                lowPressureHeaderCalculationsDomain);

    const std::shared_ptr<FlashTank>& highPressureCondensateFlashTank = selectHighPressureCondensateFlashTank(
        mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain);

    return make(headerCountInput, lowHeaderPressure, highPressureCondensateFlashTank,
                highPressureHeaderCalculationsDomain, mediumPressureHeaderCalculationsDomain,
                lowPressureHeaderCalculationsDomain);
}

/** Pressure from lowest pressure condensate. */
double HeaderFactory::determineLowHeaderPressure(
    const int headerCountInput, const HighPressureHeaderCalculationsDomain& highPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>& lowPressureHeaderCalculationsDomain) const {
    double pressure = 0;

    if (headerCountInput == 1) {
        const SteamSystemModelerTool::FluidProperties& highPressureCondensate =
            highPressureHeaderCalculationsDomain.highPressureCondensate;
        pressure = highPressureCondensate.pressure;
    }
    else {
        const SteamSystemModelerTool::FluidProperties& lowPressureCondensate =
            lowPressureHeaderCalculationsDomain->lowPressureCondensate;
        pressure = lowPressureCondensate.pressure;
    }

    return pressure;
}

/** @return selected one, possibly null. */
const std::shared_ptr<FlashTank> HeaderFactory::selectHighPressureCondensateFlashTank(
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>&    lowPressureHeaderCalculationsDomain) const {
    std::shared_ptr<FlashTank> flashTank = nullptr;

    if (lowPressureHeaderCalculationsDomain == nullptr) {
        if (mediumPressureHeaderCalculationsDomain != nullptr) {
            flashTank = mediumPressureHeaderCalculationsDomain->highPressureCondensateFlashTank;
        }
    }
    else {
        const LowPressureFlashedSteamIntoHeaderCalculatorDomain& lowPressureFlashedSteamIntoHeaderCalculatorDomain =
            lowPressureHeaderCalculationsDomain->lowPressureFlashedSteamIntoHeaderCalculatorDomain;
        flashTank = lowPressureFlashedSteamIntoHeaderCalculatorDomain.highPressureCondensateFlashTank;
    }

    return flashTank;
}

bool HeaderFactory::isMediumPressureCondensateFlashTankNull(
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>& lowPressureHeaderCalculationsDomain) const {
    bool isNull = false;

    if (lowPressureHeaderCalculationsDomain == nullptr) {
        isNull = true;
    }
    else {
        const LowPressureFlashedSteamIntoHeaderCalculatorDomain& lowPressureFlashedSteamIntoHeaderCalculatorDomain =
            lowPressureHeaderCalculationsDomain->lowPressureFlashedSteamIntoHeaderCalculatorDomain;
        if (lowPressureFlashedSteamIntoHeaderCalculatorDomain.mediumPressureCondensateFlashTank == nullptr) {
            isNull = true;
        }
    }

    return isNull;
}

const Header HeaderFactory::make(const double                                   headerPressure,
                                 const SteamSystemModelerTool::FluidProperties& returnCondensate,
                                 const BoilerInput&                             boilerInput,
                                 const std::shared_ptr<HeatExchanger::Output>&  heatExchangerOutput,
                                 const SteamSystemModelerTool::FluidProperties& makeupWater,
                                 const CondensingTurbine&                       condensingTurbineInput,
                                 const std::shared_ptr<Turbine>&                condensingTurbine) const {
    const std::string methodName = "HeaderFactory::" + std::string(__func__) + ": ";

    SM_LOG(methodName << "making header");

    SM_LOG(methodName << "adding returnCondensate inlet");
    const Inlet& returnCondensateInlet = inletFactory.makeWithEnthalpy(returnCondensate);

    std::vector<Inlet> inlets = {returnCondensateInlet};

    // makeup water
    const bool isPreheatMakeupWater = boilerInput.isPreheatMakeupWater();
    SM_LOG(methodName << "boilerInput.isPreheatMakeupWater=" << isPreheatMakeupWater);

    if (isPreheatMakeupWater) {
        SM_LOG(methodName << "isPreheatMakeupWater is true, adding heatExchangerOutput inlet");

        const Inlet& makeupWaterInlet = inletFactory.makeWithTemperature(heatExchangerOutput);
        inlets.push_back(makeupWaterInlet);
    }
    else {
        SM_LOG(methodName << "isPreheatMakeupWater is false, adding makeupWater inlet");

        const Inlet& makeupWaterInlet = inletFactory.makeWithEnthalpy(makeupWater);
        inlets.push_back(makeupWaterInlet);
    }

    const bool isUseTurbine = condensingTurbineInput.isUseTurbine();
    SM_LOG(methodName << "condensingTurbineInput.isUseTurbine=" << isUseTurbine);
    if (isUseTurbine) {
        SM_LOG(methodName << "isUseTurbine=true, adding condensingTurbine inlet");

        const double condenserPressure      = condensingTurbineInput.getCondenserPressure();
        const Inlet& condensingTurbineInlet = inletFactory.make(condensingTurbine, condenserPressure);
        inlets.push_back(condensingTurbineInlet);
    }
    else {
        SM_LOG(methodName << "isUseTurbine=false, skipping condensingTurbine");
    }

    const Header header = {headerPressure, inlets};
    SM_LOG(methodName << "header=" << header);

    return header;
}
