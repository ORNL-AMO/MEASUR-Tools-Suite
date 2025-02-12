/**
 * @file
 * @brief Implementations of Air Velocity of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_AIRVELOCITY_H
#define TOOLS_SUITE_AIRVELOCITY_H

#include "PipeData.h"

class AirVelocity {
public:
    /**
     * Constructor for AirVelocity - This calculator finds the velocity of compressed air
     * through all the different piping involved in the system.
     * @attention Constraints - For main and branch lines, recommended maximum velocity is 20 fps,
     * and it should not exceed 30fps. For line drops, feed lines or branch lines, the recommended velocity is
     * 30 fps with an upper limit of 50 fps.
     * @param airFlow double, Volumetric flow rate of air in the compressor system, referenced to the compressor inlet conditions - scfm
     * @param pipePressure double, Pressure of air flowing through the pipe - psig
     * @param atmosphericPressure double, Generally it will be 14.7 - psia
     */
    AirVelocity(double airFlow, double pipePressure, double atmosphericPressure)
            : airFlow(airFlow), pipePressure(pipePressure), atmosphericPressure(atmosphericPressure)
    {}

    PipeData calculate() {
        auto const compressedAirVelocity = [this](const double traverseArea) {
            return (airFlow * atmosphericPressure / (pipePressure + atmosphericPressure)) * (144 / traverseArea) * (1.0 / 60);
        };

        return PipeData(compressedAirVelocity);
    }

private:
    double airFlow, pipePressure, atmosphericPressure;
};

#endif
