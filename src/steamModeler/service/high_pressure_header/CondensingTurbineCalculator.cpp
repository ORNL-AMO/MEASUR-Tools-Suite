#include "steamModeler/service/high_pressure_header/CondensingTurbineCalculator.h"
#include "steamModeler/util/SteamModelerLogger.h"

const std::shared_ptr<Turbine>
CondensingTurbineCalculator::calc(const CondensingTurbine&                       condensingTurbineInput,
                                  const SteamSystemModelerTool::FluidProperties& highPressureHeaderOutput,
                                  const bool                                     isCalcIdeal) const {
    const std::string methodName = std::string("CondensingTurbineCalculator::") + std::string(__func__) + ": ";

    std::shared_ptr<Turbine> condensingTurbinePtr = nullptr;
    if (condensingTurbineInput.isUseTurbine()) {
        SM_LOG(methodName << "condensingTurbineInput isUseTurbine, calculating condensingTurbine");
        const Turbine condensingTurbine =
            turbineFactory.make(highPressureHeaderOutput, condensingTurbineInput, isCalcIdeal);
        condensingTurbinePtr = std::make_shared<Turbine>(condensingTurbine);
    }
    else {
        SM_LOG(methodName << "condensingTurbineInput not isUseTurbine, skipping");
    }

    return condensingTurbinePtr;
}
