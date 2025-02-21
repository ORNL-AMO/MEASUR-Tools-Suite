/**
 * @file
 * @brief Implementations of Pneumatic Air Requirement of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_PNEUMATICAIRREQUIREMENT_H
#define TOOLS_SUITE_PNEUMATICAIRREQUIREMENT_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>

class PneumaticAirRequirement {
public:
    enum class PistonType {
        SingleActing,
        DoubleActing
    };

    /**
     * Constructor for PneumaticAirRequirement
     * This calculator computes the quantity of air required by a specific single acting or a double acting piston cylinder compressor.
     * The design specs of the compressor are entered in the calculator and the quantity of air needed is generated.
      * @param pistonType PistonType, type of Piston, single or double acting - in this case, must be double
      * @param cylinderDiameter double, Inner diameter of cylinder - inches
      * @param cylinderStroke double, Distance that the piston can travel inside a cylinder - inches
      * @param pistonRodDiameter double, Diameter of the piston rod (required only in case of a double acting cylinder) - inches
      * @param airPressure double, Pressure of the air coming out of the cylinder - psi
      * @param cyclesPerMin double, Number of cycles (1 cycle is a combination of 2 strokes of a piston) by the crankshaft in a minute - strokes
      */
    PneumaticAirRequirement(PistonType pistonType, double cylinderDiameter, double cylinderStroke,
                            double pistonRodDiameter, double airPressure, double cyclesPerMin) :
            pistonType(pistonType), cylinderDiameter(cylinderDiameter), cylinderStroke(cylinderStroke),
            pistonRodDiameter(pistonRodDiameter), airPressure(airPressure), cyclesPerMin(cyclesPerMin)
    {
        if (pistonType != PistonType::DoubleActing) {
            throw std::runtime_error("You must have a DoubleActing piston type to use piston rod diameter");
        }
    }

    /**
     * Constructor for PneumaticAirRequirement
     * This calculator computes the quantity of air required by a specific single acting or a double acting piston cylinder compressor.
     * The design specs of the compressor are entered in the calculator and the quantity of air needed is generated.
      * @param pistonType PistonType, type of Piston, single or double acting - in this case, must be single
      * @param cylinderDiameter double, Inner diameter of cylinder - inches
      * @param cylinderStroke double, Distance that the piston can travel inside a cylinder - inches
      * @param airPressure double, Pressure of the air coming out of the cylinder - psi
      * @param cyclesPerMin double, Number of cycles (1 cycle is a combination of 2 strokes of a piston) by the crankshaft in a minute - strokes
      */
    PneumaticAirRequirement(PistonType pistonType, double cylinderDiameter, double cylinderStroke, double airPressure, double cyclesPerMin) :
            pistonType(pistonType), cylinderDiameter(cylinderDiameter), cylinderStroke(cylinderStroke),
            airPressure(airPressure), cyclesPerMin(cyclesPerMin)
    {
        if (pistonType != PistonType::SingleActing) {
            throw std::runtime_error("You must have a SingleActing piston type if you do not use piston rod diameter");
        }
    }

    PneumaticAirRequirement() = default;

    class Output {
    public:
        /**
        * Constructor for PneumaticAirRequirement::Output
        * Used to hold return values
        * @param volumeAirIntakePiston const double, Volume of air intake in a piston - cubic feet
         * @param compressionRatio const double, The ratio of pressures - Air pressure with atmospheric pressure.
        * @param airRequirementPneumaticCylinder const double, Total cubic feet/min of air requirement for a Pneumatic cylinder - scfm
        */
        Output(const double volumeAirIntakePiston, const double compressionRatio,
               const double airRequirementPneumaticCylinder)
                : volumeAirIntakePiston(volumeAirIntakePiston),
                  compressionRatio(compressionRatio),
                  airRequirementPneumaticCylinder(airRequirementPneumaticCylinder)
        {}

        const double volumeAirIntakePiston, compressionRatio, airRequirementPneumaticCylinder;
    };

    /**
     * Calculates and returns an Output object
     * @return PneumaticAirRequirement::Output, const output
     */
    Output calculate() {
        auto const volumeAirIntakeSingle = (0.785 * std::pow(cylinderDiameter, 2) * cylinderStroke * cyclesPerMin) / 1728;
        auto const compressionRatio = (airPressure + 14.7) / 14.7;

        if (pistonType == PneumaticAirRequirement::PistonType::SingleActing) {
            return {volumeAirIntakeSingle, compressionRatio, volumeAirIntakeSingle * compressionRatio};
        }
        auto const volumeAirIntakeDouble = (2 * 1728 * volumeAirIntakeSingle - (0.785 * std::pow(pistonRodDiameter, 2)
                                                                                * cylinderStroke * cyclesPerMin)) / 1728;
        return {volumeAirIntakeDouble, compressionRatio, volumeAirIntakeDouble * compressionRatio};
    }

private:
    PistonType pistonType;
    double cylinderDiameter, cylinderStroke, pistonRodDiameter = 0, airPressure, cyclesPerMin;
};

#endif
