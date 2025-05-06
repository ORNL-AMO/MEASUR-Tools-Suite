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
     * @param style Pump::Style, style of pump being used.
     * @param pumpEfficiency double, pump efficiency at the specified operating conditions as %
     * @param rpm double, pump RPM to define its operating speed
     * @param kinematicViscosity double, kinematic viscosity of the fluid being pumped in centistokes
     * @param stageCount double, the number of pump stages
     * @param flowRate double, measured or required flow rate in gpm
     * @param head double, pump head in ft
    */
    PumpEfficiency(
        Pump::Style style,
        double pumpEfficiency,
        double rpm,
        double kinematicViscosity,
        double stageCount,
        double flowRate,
        double head
     ) :
     style(style),
     pumpEfficiency(pumpEfficiency),
     rpm(rpm),
     kinematicViscosity(kinematicViscosity),
     stageCount(stageCount),
     flowRate(flowRate),
     head(head)
    {};

    /**
     * Calculates pump efficiency
     */
    Output calculate();

private:
        Pump::Style style;
        double pumpEfficiency;
        double rpm;
        double kinematicViscosity;
        double stageCount;
        double flowRate;
        double head;
    };


#endif //TOOLS_SUITE_PUMPEFFICIENCY_H
