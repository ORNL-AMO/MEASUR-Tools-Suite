/**
 * @brief
 *
 * @author Mark Root (mroot)
 * @bug No known bugs.
 *
 */

#include "motorDriven/pumpFan/PumpEfficiency.h"

#include "motorDriven/pumpFan/OptimalDeviationFactor.h"
#include "motorDriven/pumpFan/OptimalPumpEfficiency.h"

PumpEfficiency::Output PumpEfficiency::calculate() {

    OptimalPumpEfficiency pef(style, pumpEfficiency, rpm, kinematicViscosity, stageCount, flowRate, head);
    double                average = pef.calculate();
    double                odf     = OptimalDeviationFactor(flowRate).calculate();
    double                max     = average * odf;

    return {average, max};
}
