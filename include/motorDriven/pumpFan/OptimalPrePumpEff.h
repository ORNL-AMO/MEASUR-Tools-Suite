/**
 * @brief Header file for OptimalPrePumpEff class
 *
 * This contains the prototypes of OptimalPrePumpEff calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#ifndef TOOLS_SUITE_OPTIMALPREPUMPEFF_H
#define TOOLS_SUITE_OPTIMALPREPUMPEFF_H

#include "motorDriven/pump/PumpResult.h"

class OptimalPrePumpEff {
public:
    /**
     * Constructor
     * @param style Pump::Style, style of pump being used.
     * @param flowRate double, measured or required flow rate in gpm
     */
    OptimalPrePumpEff(
        const Pump::Style style,
        const double flowRate
    ) :
        style(style),
        flowRate(flowRate)
    {};

    /**
     * Calculates the optimal prepump efficiency
     * @return double, optimal prepump efficiency as %
     */
    double calculate();

private:
    const Pump::Style style;
    const double flowRate;
};


#endif //TOOLS_SUITE_OPTIMALPREPUMPEFF_H
