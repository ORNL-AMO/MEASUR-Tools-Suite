#ifndef TOOLS_SUITE_FLASHTANKFACTORY_H
#define TOOLS_SUITE_FLASHTANKFACTORY_H

#include <steamModeler/Boiler.h>
#include <steamModeler/FlashTank.h>
#include <steamModeler/Header.h>
#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/HeaderInput.h>

class FlashTankFactory {
public:
    std::shared_ptr<FlashTank>
    make(const HeaderInput &headerInput, const BoilerInput &boilerInput, const Boiler &boiler) const;

    FlashTank make(const double pressure, const Boiler &boiler) const;

    FlashTank make(const double pressure, const SteamSystemModelerTool::FluidProperties &condensate) const;

    FlashTank make(const std::shared_ptr<Header> &header,
                   const std::shared_ptr<HeaderNotHighestPressure> &headerNotHighestPressure) const;

    FlashTank
    make(const SteamSystemModelerTool::FluidProperties &properties) const;
};

#endif //TOOLS_SUITE_FLASHTANKFACTORY_H
