/**
 * @file
 * @brief Implementations of Pipe Sizing of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_PIPESIZING_H
#define TOOLS_SUITE_PIPESIZING_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>

class PipeSizing {
public:
    struct Output {
        Output(const double crossSectionalArea, const double pipeDiameter)
                : crossSectionalArea(crossSectionalArea), pipeDiameter(pipeDiameter)
        {}
        const double crossSectionalArea, pipeDiameter;
    };

    /**
     * Constructor for PipeSizing - This calculator finds the velocity of compressed air
     * through all the different piping involved in the system.
     * @param airflow double, volumetric flow velocity - cfm
     * @param airlinePressure double, Pressure through the pipe  - psi
     * @param designVelocity double, The air flow velocity that is meant to flow through the pipe.
     * @attention Constraints: 20 fps is recommended for a header, but it should never exceed 30 fps - ft/sc
     * @param atmosphericPressure double, generally it will be 14.7 - psia
     */
    PipeSizing(double airflow, double airlinePressure, double designVelocity, double atmosphericPressure)
            : airflow(airflow),  airlinePressure(airlinePressure),  designVelocity(designVelocity),
              atmosphericPressure(atmosphericPressure)
    {}

    /**
     * calculateReynoldsNumber() will calculateThermalResistance and return the cross sectional area and the pipe diameter.
     * @return PipeSizing::Output
     */
    Output calculate() {
        auto const crossSectionalArea = (144 * airflow * atmosphericPressure) / (designVelocity * 60 * (airlinePressure + atmosphericPressure));
        return {crossSectionalArea, std::sqrt(crossSectionalArea / 0.78)};
    }

private:
    double airflow, airlinePressure, designVelocity, atmosphericPressure;
};

#endif
