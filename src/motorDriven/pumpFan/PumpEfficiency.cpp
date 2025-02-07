/**
 * @brief 
 *
 * @author Mark Root (mroot)
 * @bug No known bugs.
 *
 */

#include "motorDriven/pumpFan/PumpEfficiency.h"
#include "motorDriven/pumpFan/OptimalPrePumpEff.h"
#include "motorDriven/pumpFan/OptimalDeviationFactor.h"

PumpEfficiency::Output PumpEfficiency::calculate() {

    OptimalPrePumpEff pef(style, flow);
    double average = pef.calculate();
    double odf = OptimalDeviationFactor(flow).calculate();
    double max = average * odf;

    return {average, max};
}
