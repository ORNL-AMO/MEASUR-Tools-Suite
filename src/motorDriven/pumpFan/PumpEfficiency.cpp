/**
 * @brief
 *
 * @author Mark Root (mroot)
 * @bug No known bugs.
 *
 */

#include "motorDriven/pumpFan/PumpEfficiency.h"

#include "motorDriven/pump/optimal_deviation_factor.h"
#include "motorDriven/pumpFan/OptimalPumpEfficiency.h"

PumpEfficiency::Output PumpEfficiency::calculate() {

    OptimalPumpEfficiency optimal_pump_efficiency(style, pumpEfficiency, rpm, kinematicViscosity,
                                                 stageCount, flowRate, head);
    const double average_efficiency = optimal_pump_efficiency.calculate();
    const double deviation_factor = optimal_deviation_factor::calculate(flowRate);
    const double maximum_efficiency = average_efficiency * deviation_factor;

    return {average_efficiency, maximum_efficiency};
}
