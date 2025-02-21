#ifndef TOOLS_SUITE_CONDENSINGTURBINECALCULATOR_H
#define TOOLS_SUITE_CONDENSINGTURBINECALCULATOR_H

#include <steamModeler/SteamSystemModelerTool.h>
#include <steamModeler/Turbine.h>
#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/domain/TurbineFactory.h>

class CondensingTurbineCalculator {
public:
    const std::shared_ptr<Turbine> calc(const CondensingTurbine &condensingTurbineInput,
                                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                        const bool isCalcIdeal) const;

private:
    TurbineFactory turbineFactory = TurbineFactory();

    const std::shared_ptr<Turbine> make(const CondensingTurbine &condensingTurbineInput,
                                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                        const bool isCalcIdeal) const;
};

#endif //TOOLS_SUITE_CONDENSINGTURBINECALCULATOR_H
