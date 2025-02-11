#ifndef TOOLS_SUITE_STEAMMODELEROUTPUTFACTORY_H
#define TOOLS_SUITE_STEAMMODELEROUTPUTFACTORY_H

#include <steamModeler/api/SteamModelerOutput.h>
#include <steamModeler/domain/SteamModelCalculationsDomain.h>
#include <steamModeler/service/SteamModelCalculator.h>

class SteamModelerOutputFactory {
public:
    SteamModelerOutput make(const SteamModelCalculationsDomain &domain) const;
};

#endif //TOOLS_SUITE_STEAMMODELEROUTPUTFACTORY_H
