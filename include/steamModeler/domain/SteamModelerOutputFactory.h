#pragma once

#include <steamModeler/api/SteamModelerOutput.h>
#include <steamModeler/domain/SteamModelCalculationsDomain.h>
#include <steamModeler/service/SteamModelCalculator.h>

class SteamModelerOutputFactory {
  public:
    SteamModelerOutput make(const SteamModelCalculationsDomain& domain) const;
};

