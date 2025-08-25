#ifndef TOOLS_SUITE_BOILERFACTORY_H
#define TOOLS_SUITE_BOILERFACTORY_H

#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/HeaderInput.h>
#include <steamModeler/Boiler.h>

class BoilerFactory {
  public:
    Boiler make(const HeaderInput& headerInput, const BoilerInput& boilerInput, double massFlow) const;
};

#endif // TOOLS_SUITE_BOILERFACTORY_H
