#ifndef TOOLS_SUITE_RESTARTERSERVICE_H
#define TOOLS_SUITE_RESTARTERSERVICE_H

#include <memory>
#include <steamModeler/Boiler.h>
#include <steamModeler/Turbine.h>

/**
 * Determines when to have the Steam Modeler move to the next iteration attempt for balancing the system.
 */
class RestarterService {
public:
    void restartIfNotEnoughSteam(const std::shared_ptr<Turbine> &turbine, const double availableMassFlow,
                                 const Boiler &boiler) const;

    void restartIfNotEnoughSteam(const double additionalSteamNeeded, const Boiler &boiler) const;

private:
    void logMessage(const std::string &message) const;
};

#endif //TOOLS_SUITE_RESTARTERSERVICE_H
