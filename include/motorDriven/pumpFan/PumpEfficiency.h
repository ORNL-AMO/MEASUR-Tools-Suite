/**
 * @brief TODO
 *
 * @author Mark Root (mroot)
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_PUMPEFFICIENCY_H
#define TOOLS_SUITE_PUMPEFFICIENCY_H

#include "motorDriven/pump/PumpResult.h"

class PumpEfficiency {
public:
    struct Output {
	    /**
	     * @param average
	     * @param max
	     */
        Output(const double average, const double max)
                : average(average), max(max)
        {}

        const double average, max;
    };
    /**
     * Constructor
     * @param style Pump::Style
     * @param flow double
    */
    PumpEfficiency(
        Pump::Style style,
        double flow
     ) :
        style(style),
        flow(flow)
    {};

    /**
     * Calculates pump efficiency
     */
    Output calculate();

private:
        Pump::Style style;
        double flow;
};


#endif //TOOLS_SUITE_PUMPEFFICIENCY_H
