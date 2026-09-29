#include "steamModeler/service/power_balance/SteamProductionCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

double SteamProductionCalculator::calc(
    const int headerCountInput, const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>& lowPressureHeaderInput, const BoilerInput& boilerInput,
    const std::shared_ptr<FlashTank>& blowdownFlashTank, const Boiler& boiler,
    const HighPressureHeaderCalculationsDomain&                    highPressureHeaderCalculationsDomain,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>&    lowPressureHeaderCalculationsDomain) const {
    const std::string methodName = std::string("SteamProductionCalculator::") + std::string(__func__) + ": ";

    SM_LOG(methodName << "calculating steamProduction");

    const double boilerOutputMassFlow = boiler.getSteamProperties().massFlow;

    double flashTankAdditionalSteam = calcFlashTankAdditionalSteam(
        headerCountInput, boilerInput, mediumPressureHeaderInput, lowPressureHeaderInput, blowdownFlashTank,
        highPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain);
    double prvAdditionalSteam =
        calcPrvAdditionalSteam(headerCountInput, mediumPressureHeaderInput, lowPressureHeaderInput,
                               mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain);

    // steam production = steam produced by (boiler) + (flash tanks) + (PRV feedwater)
    const double steamProduction = boilerOutputMassFlow + flashTankAdditionalSteam + prvAdditionalSteam;

    SM_LOG(methodName << "boilerOutputMassFlow=" << boilerOutputMassFlow << ", flashTankAdditionalSteam=" << flashTankAdditionalSteam << ", prvAdditionalSteam=" << prvAdditionalSteam << ": steamProduction=" << steamProduction);

    return steamProduction;
}

/** Calc added steam from flash tanks (outletGasMassFlow). */
double SteamProductionCalculator::calcFlashTankAdditionalSteam(
    const int headerCountInput, const BoilerInput& boilerInput,
    const std::shared_ptr<HeaderNotHighestPressure>&            mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>&            lowPressureHeaderInput,
    const std::shared_ptr<FlashTank>&                           blowdownFlashTank,
    const HighPressureHeaderCalculationsDomain&                 highPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>& lowPressureHeaderCalculationsDomain) const {
    const std::string methodName = std::string("SteamProductionCalculator::") + std::string(__func__) + ": ";

    SM_LOG(methodName << "calculating flashTankAdditionalSteam");

    double flashTankAdditionalSteam = 0;

    if (headerCountInput > 1) {
        const std::shared_ptr<FlashTank>& highPressureCondensateFlashTank =
            highPressureHeaderCalculationsDomain.highPressureCondensateFlashTank;

        // steam added by blowdown flash tank
        if (boilerInput.isBlowdownFlashed()) {
            const SteamSystemModelerTool::FluidProperties& outletGasSaturatedProperties =
                blowdownFlashTank->getOutletGasSaturatedProperties();
            const double massFlow = outletGasSaturatedProperties.massFlow;
            SM_LOG(methodName << "boiler blowdown is flashed, adding blowdownFlashTank massFlow=" << massFlow);
            flashTankAdditionalSteam += massFlow;
        }
        else {
            SM_LOG(methodName << "blowdown is not flashed, not adding blowdownFlashTank massFlow");
        }

        // steam added by flash tank into low pressure header
        if (lowPressureHeaderInput->isFlashCondensate()) {
            if (headerCountInput == 2) {
                const SteamSystemModelerTool::FluidProperties& outletGasSaturatedProperties =
                    highPressureCondensateFlashTank->getOutletGasSaturatedProperties();
                const double massFlow = outletGasSaturatedProperties.massFlow;
                SM_LOG(methodName << "lowPressureHeader condensate is flashed and headerCountInput==2" << ", adding highPressureCondensateFlashTank massFlow=" << massFlow);
                flashTankAdditionalSteam += massFlow;
            }
            else if (headerCountInput == 3) {
                const LowPressureFlashedSteamIntoHeaderCalculatorDomain&
                    lowPressureFlashedSteamIntoHeaderCalculatorDomain =
                        lowPressureHeaderCalculationsDomain->lowPressureFlashedSteamIntoHeaderCalculatorDomain;
                const std::shared_ptr<FlashTank>& mediumPressureCondensateFlashTank =
                    lowPressureFlashedSteamIntoHeaderCalculatorDomain.mediumPressureCondensateFlashTank;
                const SteamSystemModelerTool::FluidProperties& outletGasSaturatedProperties =
                    mediumPressureCondensateFlashTank->getOutletGasSaturatedProperties();
                const double massFlow = outletGasSaturatedProperties.massFlow;
                SM_LOG(methodName << "lowPressureHeader condensate is flashed and headerCountInput==3" << ", adding mediumPressureCondensateFlashTank massFlow=" << massFlow);
                flashTankAdditionalSteam += massFlow;
            }
        }
        else {
            SM_LOG(methodName << "lowPressureHeader condensate is not flashed, not adding highPressureCondensateFlashTank massFlow");
        }

        if (headerCountInput == 3) {
            // steam added by flash tank into medium pressure header
            if (mediumPressureHeaderInput->isFlashCondensate()) {
                const SteamSystemModelerTool::FluidProperties& outletGasSaturatedProperties =
                    highPressureCondensateFlashTank->getOutletGasSaturatedProperties();
                const double massFlow = outletGasSaturatedProperties.massFlow;
                SM_LOG(methodName << "headerCountInput==3, adding highPressureCondensateFlashTank massFlow=" << massFlow);
                flashTankAdditionalSteam += massFlow;
            }
        }
    }
    else {
        SM_LOG(methodName << "headerCountInput=" << headerCountInput << " (not > 1), not adding boiler, medium, or high pressureCondensateFlashTank massFlow");
    }

    SM_LOG(methodName << "flashTankAdditionalSteam=" << flashTankAdditionalSteam);

    return flashTankAdditionalSteam;
}

/** Calc added steam from PRVs (outletMassFlow - inletMassFlow). */
double SteamProductionCalculator::calcPrvAdditionalSteam(
    const int headerCountInput, const std::shared_ptr<HeaderNotHighestPressure>& mediumPressureHeaderInput,
    const std::shared_ptr<HeaderNotHighestPressure>&               lowPressureHeaderInput,
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain>& mediumPressureHeaderCalculationsDomain,
    const std::shared_ptr<LowPressureHeaderCalculationsDomain>&    lowPressureHeaderCalculationsDomain) const {
    const std::string methodName = std::string("SteamProductionCalculator::") + std::string(__func__) + ": ";

    SM_LOG(methodName << "calculating prvAdditionalSteam");

    double prvAdditionalSteam = 0;

    if (headerCountInput > 1) {
        // steam added by desuperheating feedwater
        if (lowPressureHeaderInput->isDesuperheatSteamIntoNextHighest()) {
            SM_LOG(methodName << "headerCountInput > 1 and lowPressureHeader isDesuperheatSteamIntoNextHighest is true" << ", adding lowPressurePrv massFlow");
            const std::shared_ptr<PrvWithoutDesuperheating>& lowPressurePrv =
                lowPressureHeaderCalculationsDomain->lowPressurePrv;
            prvAdditionalSteam = addPrvMassFlow(prvAdditionalSteam, lowPressurePrv);
        }
        else {
            SM_LOG(methodName << "headerCountInput not > 1 or lowPressureHeader isDesuperheatSteamIntoNextHighest is false" << ", not adding lowPressurePrv massFlow");
        }

        if (headerCountInput == 3) {
            // steam added by desuperheating feedwater
            if (mediumPressureHeaderInput->isDesuperheatSteamIntoNextHighest()) {
                SM_LOG(methodName << "headerCountInput == 3 and mediumPressureHeader isDesuperheatSteamIntoNextHighest is true" << ", adding highToMediumPressurePrv massFlow");
                const std::shared_ptr<PrvWithoutDesuperheating>& highToMediumPressurePrv =
                    mediumPressureHeaderCalculationsDomain->highToMediumPressurePrv;
                prvAdditionalSteam = addPrvMassFlow(prvAdditionalSteam, highToMediumPressurePrv);
            }
            else {
                SM_LOG(methodName << "headerCountInput not == 3 or mediumPressureHeader isDesuperheatSteamIntoNextHighest is false" << ", not adding highToMediumPressurePrv massFlow");
            }
        }
    }
    else {
        SM_LOG(methodName << "headerCountInput=" << headerCountInput << " (not > 1), no PRVs to calc additional steam for");
    }

    SM_LOG(methodName << "prvAdditionalSteam=" << prvAdditionalSteam);

    return prvAdditionalSteam;
}

double SteamProductionCalculator::addPrvMassFlow(double                                           prvAdditionalSteam,
                                                 const std::shared_ptr<PrvWithoutDesuperheating>& prv) const {
    const std::string methodName = std::string("SteamProductionCalculator::") + std::string(__func__) + ": ";

    const double outletMassFlow = prv->getOutletMassFlow();
    const double inletMassFlow  = prv->getInletMassFlow();
    const double diff           = outletMassFlow - inletMassFlow;
    const double result         = prvAdditionalSteam + diff;

    SM_LOG(methodName << "outletMassFlow=" << outletMassFlow << ", inletMassFlow=" << inletMassFlow << ", diff=" << diff << ": result=" << result);

    return result;
}
