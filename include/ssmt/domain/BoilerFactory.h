#ifndef TOOLS_SUITE_BOILERFACTORY_H
#define TOOLS_SUITE_BOILERFACTORY_H

#include <ssmt/Boiler.h>
#include <ssmt/api/BoilerInput.h>
#include <ssmt/api/HeaderInput.h>

class BoilerFactory {
public:
    Boiler make(const HeaderInput &headerInput, const BoilerInput &boilerInput, double massFlow) const;
};


#endif //TOOLS_SUITE_BOILERFACTORY_H
