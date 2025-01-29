#ifndef TOOLS_SUITE_MAKEUPWATERCALCULATOR_H
#define TOOLS_SUITE_MAKEUPWATERCALCULATOR_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/OperationsInput.h>

class MakeupWaterCalculator {
public:
    SteamSystemModelerTool::SteamPropertiesOutput calc(const OperationsInput &operationsInput) const;
};

#endif //TOOLS_SUITE_MAKEUPWATERCALCULATOR_H
