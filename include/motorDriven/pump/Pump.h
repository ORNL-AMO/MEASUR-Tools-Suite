#ifndef TOOLS_SUITE_PUMP_H
#define TOOLS_SUITE_PUMP_H

#include <string>
#include "motorDriven/motor/MotorData.h"

namespace Pump {
    enum class SpecificSpeed {
        FIXED_SPEED,
        NOT_FIXED_SPEED
    };

    enum class Style {
        END_SUCTION_SLURRY,
        END_SUCTION_SEWAGE,
        END_SUCTION_STOCK,
        END_SUCTION_SUBMERSIBLE_SEWAGE,
        API_DOUBLE_SUCTION,
        MULTISTAGE_BOILER_FEED,
        END_SUCTION_ANSI_API,
        AXIAL_FLOW,
        DOUBLE_SUCTION,
        VERTICAL_TURBINE,
        LARGE_END_SUCTION,
        SPECIFIED_OPTIMAL_EFFICIENCY
    };

    struct FieldData {
        /**
         * Constructor
         * @param flowRate double, rate of flow. Units are gpm
         * @param head double, pump head measured in feet
         * @param loadEstimationMethod LoadEstimationMethod, classification of load estimation method
         * @param motorPower double, power output of the pump's motor in hp.
         * @param motorAmps double, current measured from the pump's motor in amps
         * @param voltage double, the measured bus voltage in volts
         */
        FieldData(const double flowRate, const double head, const Motor::LoadEstimationMethod loadEstimationMethod, const double motorPower,
                  const double motorAmps, const double voltage)
                : flowRate(flowRate), head(head), loadEstimationMethod(loadEstimationMethod),  motorPower(motorPower),
                  motorAmps(motorAmps), voltage(voltage)
        {}

        const double flowRate, head;
        const Motor::LoadEstimationMethod loadEstimationMethod;
        const double motorPower, motorAmps, voltage;
    };

    struct Input {
        /**
         * Constructor
         * @param style Style, classification of style of pump being used.
         * @param pumpEfficiency double, pump % efficiency at the specified operating conditions
         * @param rpm double, pump RPM to define its operating speed
         * @param drive Drive, type of drive the pump uses from either direct or belt drive.
         * @param kviscosity double, kinematic viscosity of the fluid being pumped in centistokes.
         * @param specificGravity double, specific gravity- unitless
         * @param stageCount int, the number of pump stages
         * @param speed Speed, type of pump speed from either fixed or not fixed.
         */
        Input(const Style style, double pumpEfficiency, const double rpm, const Motor::Drive drive,
              const double kviscosity,
              const double specificGravity, const int stageCount, const SpecificSpeed speed, double specifiedEfficiency)
                : style(style), pumpEfficiency(pumpEfficiency), rpm(rpm), drive(drive),
                  kviscosity(kviscosity),
                  specificGravity(specificGravity), stageCount(stageCount), speed(speed), specifiedEfficiency(specifiedEfficiency) {
            /**
             * Convert percent values to fractions for proper calculation
             */
            //   this->specifiedEfficiency = Conversion(specifiedEfficiency).percentToFraction();
            //   this->pumpEfficiency = Conversion(pumpEfficiency).percentToFraction();
            //   this->specifiedEfficiency = specifiedEfficiency / 100.0;
            //   this->pumpEfficiency = pumpEfficiency / 100.0;
        };

        const Style style;
        double pumpEfficiency, rpm;
        const Motor::Drive drive;
        const double kviscosity, specificGravity;
        const int stageCount;
        const SpecificSpeed speed;
        double specifiedEfficiency;

    };
}

#endif //TOOLS_SUITE_PUMP_H