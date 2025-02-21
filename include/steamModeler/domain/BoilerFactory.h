#ifndef TOOLS_SUITE_BOILERFACTORY_H
#define TOOLS_SUITE_BOILERFACTORY_H

#include <steamModeler/Boiler.h>
#include <steamModeler/api/BoilerInput.h>
#include <steamModeler/api/HeaderInput.h>

class BoilerFactory {
public:
    Boiler make(const HeaderInput &headerInput, const BoilerInput &boilerInput, double massFlow) const;
};


#endif //TOOLS_SUITE_BOILERFACTORY_H
