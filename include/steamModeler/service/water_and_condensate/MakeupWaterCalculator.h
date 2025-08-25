#ifndef TOOLS_SUITE_MAKEUPWATERCALCULATOR_H
#define TOOLS_SUITE_MAKEUPWATERCALCULATOR_H

#include <steamModeler/api/OperationsInput.h>
#include <steamModeler/SteamSystemModelerTool.h>

class MakeupWaterCalculator {
  public:
    SteamSystemModelerTool::SteamPropertiesOutput calc(const OperationsInput& operationsInput) const;
};

#endif // TOOLS_SUITE_MAKEUPWATERCALCULATOR_H
