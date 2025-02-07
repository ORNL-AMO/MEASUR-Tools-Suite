#ifndef TOOLS_SUITE_COMBINEDCONDENSATECALCULATOR_H
#define TOOLS_SUITE_COMBINEDCONDENSATECALCULATOR_H

#include <steamModeler/Header.h>
#include <steamModeler/domain/HeaderFactory.h>
#include <steamModeler/domain/HighPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/LowPressureHeaderCalculationsDomain.h>
#include <steamModeler/domain/MediumPressureHeaderCalculationsDomain.h>

class CombinedCondensateCalculator {
public:
    Header calc(const int headerCountInput,
                const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    const HeaderFactory headerFactory = HeaderFactory();
};

#endif //TOOLS_SUITE_COMBINEDCONDENSATECALCULATOR_H
