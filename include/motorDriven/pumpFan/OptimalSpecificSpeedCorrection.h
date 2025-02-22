/**
 * @brief Header file for OptimalSpecificSpeedCorrection class
 *
 * This contains the prototypes of Optimal Specific Speed Correction calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_OPTIMALSPECIFICSPEEDCORRECTION_H
#define TOOLS_SUITE_OPTIMALSPECIFICSPEEDCORRECTION_H

#include "motorDriven/pump/PumpResult.h"

class OptimalSpecificSpeedCorrection {
public:
    /**
     * Constructor
     * @param style Pump::Style, type of pump speed from either fixed or not fixed.
     * @param specificSpeed double, specific speed in rpm*sqrt(gpm)/((ft/s)^(3/2))
     */
    OptimalSpecificSpeedCorrection(
        const Pump::Style style,
        const double specificSpeed
    ):
        specificSpeed(specificSpeed),
        style(style)
    {};

    /**
     * Calculates the optimal specific speed correction
     * @return double, optimal specific speed correction as %
     */
    double calculate();

private:
    const double specificSpeed;
    const Pump::Style style;
};


#endif //TOOLS_SUITE_OPTIMALSPECIFICSPEEDCORRECTION_H
