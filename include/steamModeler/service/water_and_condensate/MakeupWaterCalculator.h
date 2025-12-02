#pragma once

#include <steamModeler/api/OperationsInput.h>
#include <steamModeler/SteamSystemModelerTool.h>

class MakeupWaterCalculator {
  public:
    SteamSystemModelerTool::SteamPropertiesOutput calc(const OperationsInput& operationsInput) const;
};

