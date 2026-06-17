#pragma once

/**
 * @file
 * @brief Implementations of Fan Affinity Laws for a motor driven fan system
 *      Compute annual baseline and changed energy based on current and changed state of motor Control
 *      at a desired flow rate by percent or by volume.
 *      Also allows changing fan size.
 *      Motor Control types for fan system supported:
 *          a. ON/OFF
 *          b. Two Speed
 *          c. VSD
 *          d. None (for fan size change)
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#include <stdexcept>
#include <cmath>

class FanAffinityLaws {
public:
    enum MotorControlType {
        OnOff,
        TwoSpeed,
        VSD,
        None
    };

    enum FlowMode {
        Percent,
        Volume
    };

    /**
     * @brief Output struct for FanAffinityLaws
     * @var annualEnergyBaseline double, Baseline energy consumption in kWh
     * @var annualEnergyNew double, Energy consumption in kWh
     * @var annualCostSavings double, Cost savings in $ based on change in energy consumption and electricity cost
     */
    struct Output {
        Output(const double annualEnergyBaseline, const double annualEnergyNew, const double annualCostSavings)
            : annualEnergyBaseline(annualEnergyBaseline), annualEnergyNew(annualEnergyNew), annualCostSavings(annualCostSavings) {}

        const double annualEnergyBaseline, annualEnergyNew, annualCostSavings;
    };

    /**
     * @brief Input struct for FanAffinityLaws.
     * Use this struct to create input object and then use that object to create FanAffinityLaws object.
     * @var electricityCost double, electric usage rate in $/kWh
     * @var driveEfficiency double, Efficiency of the drive percentage (1 - 100)
     * @var motorEfficiency double, Efficiency of the motor percentage (1 - 100)
     * @var flowPercentBaseline double, Flow rate change by percent (0 - 100)
     * @var operatingHours double, Hours for which the fan system operates per year - hours (1 - 8760 hours)
     * @var motorPower double, Motor Power in kW
     * @var ratedFlow double, Flow Rate in CFM
     * @var motorControlTypeCurrent MotorControlType enum, current motor control for the fan system
     * @var motorControlTypeNew MotorControlType enum, changed motor control for the fan system
     * @var flowMode FlowMode enum, mode for flow change - by percent or by volume
     * @var desiredFlowRate double, Desired flow rate based on flow mode
     *          If flow mode is volume desired flow rate is flow volume in CFM
     *          If flow mode is percentage desired flow rate is flow percentage (0 - 100)
     */
    struct Input {
        double electricityCost;
        double driveEfficiency, motorEfficiency, flowPercentBaseline;
        double operatingHours, motorPower, ratedFlow;
        MotorControlType motorControlTypeCurrent, motorControlTypeNew;
        FlowMode flowMode;
        double desiredFlowRate;
    };

    /**
     * Constructor for FanAffinityLaws. Use this constructor with input object.
     * @param input Input struct containing all necessary input parameters for FanAffinityLaws
     */
    FanAffinityLaws(const Input& input) : FanAffinityLaws(input.electricityCost, input.driveEfficiency, input.motorEfficiency, input.flowPercentBaseline,
        input.operatingHours, input.motorPower, input.ratedFlow,
        input.motorControlTypeCurrent, input.motorControlTypeNew,
        input.flowMode, input.desiredFlowRate) {}

    /**
     * Constructor for FanAffinityLaws - Use this constructor when fan size is not changing.
     * @param electricityCost double, electric usage rate in $/kWh
     * @param driveEfficiency double, Efficiency of the drive percentage (1 - 100)
     * @param motorEfficiency double, Efficiency of the motor percentage (1 - 100)
     * @param flowPercentBaseline double, Flow rate change by percent (0 - 100)
     * @param operatingHours double, Hours for which the fan system operates per year - hours (1 - 8760 hours)
     * @param motorPower double, Motor Power in kW
     * @param ratedFlow double, Flow Rate in CFM
     * @param motorControlTypeCurrent MotorControlType enum, current motor control for the fan system
     * @param motorControlTypeNew MotorControlType enum, changed motor control for the fan system
     * @param flowMode FlowMode enum, mode for flow change - by percent or by volume
     * @param desiredFlowRate double, Desired flow rate based on flow mode
     *          If flow mode is volume desired flow rate is flow volume in CFM
     *          If flow mode is percentage desired flow rate is flow percentage (0 - 100)
     */
    FanAffinityLaws(const double electricityCost,
        const double driveEfficiency, const double motorEfficiency, const double flowPercentBaseline,
        const double operatingHours, const double motorPower, const double ratedFlow,
        const MotorControlType motorControlTypeCurrent, const MotorControlType motorControlTypeNew,
        const FlowMode flowMode, const double desiredFlowRate) : electricityCost(electricityCost),
            driveEfficiency(driveEfficiency/100), motorEfficiency(motorEfficiency/100), flowPercentBaseline(flowPercentBaseline/100),
            operatingHours(operatingHours), motorPower(motorPower), ratedFlow(ratedFlow),
            motorControlTypeCurrent(motorControlTypeCurrent), motorControlTypeNew(motorControlTypeNew) {
        if (electricityCost <= 0) {
            throw std::invalid_argument("Electricity cost must be greater than 0.");
        }
        if (driveEfficiency <= 0 || driveEfficiency > 100) {
            throw std::invalid_argument("Drive efficiency must be between 0 and 100.");
        }
        if (motorEfficiency <= 0 || motorEfficiency > 100) {
            throw std::invalid_argument("Motor efficiency must be between 0 and 100.");
        }
        if (flowPercentBaseline < 0 || flowPercentBaseline > 100) {
            throw std::invalid_argument("Flow percent baseline must be between 0 and 100.");
        }
        if (operatingHours <= 0 || operatingHours > 8760) {
            throw std::invalid_argument("Operating hours must be between 1 and 8760.");
        }
        if (motorPower <= 0) {
            throw std::invalid_argument("Motor power must be greater than 0.");
        }
        if (ratedFlow <= 0) {
            throw std::invalid_argument("Rated flow must be greater than 0.");
        }

        if (flowMode == Percent) {
            if (desiredFlowRate < 0 || desiredFlowRate > 100) {
                throw std::invalid_argument("Desired flow rate percentage must be between 0 and 100.");
            }
            desiredFlowPercent = desiredFlowRate / 100.0;
            desiredFlowVolume = desiredFlowRate * ratedFlow / 100.0;
        } else if (flowMode == Volume) {
            if (desiredFlowRate < 0) {
                throw std::invalid_argument("Desired flow rate volume must be greater than or equal to 0.");
            }
            desiredFlowVolume = desiredFlowRate;
            desiredFlowPercent = desiredFlowRate / ratedFlow;
        }
    }

    /**
     * @brief Compute annual baseline and changed energy based on current and changed state of motor Control
     *      at a desired flow rate by percent or by volume.
     * @return Output struct containing annual energy baseline and changed annual energy in kWh
     */
    Output calculate() const { return compute(0.0); }

    /**
     * @brief Compute annual baseline and changed energy based on current and changed state of motor Control
     *      at a desired flow rate by percent or by volume with changing fan size.
     * @param fanDiameterCurrent double, Current fan diameter in inches
     * @param fanDiameter double, Changed fan diameter in inches
     * @return Output struct containing annual energy baseline and changed annual energy in kWh
     */
    Output changeFanSize(const double fanDiameterCurrent, const double fanDiameter) const {
        if (fanDiameterCurrent <= 0 || fanDiameter <= 0) {
            throw std::invalid_argument("Fan diameters must be greater than 0.");
        }

        return compute(fanDiameter / fanDiameterCurrent);
    }

private:
    const double electricityCost;
    const double driveEfficiency, motorEfficiency, flowPercentBaseline;
    const double operatingHours, motorPower, ratedFlow;
    const MotorControlType motorControlTypeCurrent, motorControlTypeNew;
    double desiredFlowPercent = 0, desiredFlowVolume = 0;

    Output compute(const double fanDiameterRatio) const {
        const double powerBaseline = motorPower / motorEfficiency / driveEfficiency;

        double powerCurrent = powerBaseline;
        if (motorControlTypeCurrent == VSD) {
            powerCurrent *= std::pow(flowPercentBaseline, 3);
        }
        else if (motorControlTypeCurrent == TwoSpeed) {
            powerCurrent = powerBaseline * get50PercentTimeFactor(flowPercentBaseline);
        }

        double powerNew = powerBaseline;
        if (motorControlTypeNew == TwoSpeed) {
            powerNew = powerBaseline * get50PercentTimeFactor(desiredFlowPercent);
        }

        if (fanDiameterRatio != 0) {
            if (motorControlTypeNew == VSD) {
                const auto fanRatedFlow   = ratedFlow * std::pow(fanDiameterRatio, 3);
                const auto newFlowPercent = desiredFlowVolume / fanRatedFlow;
                powerNew                  = powerBaseline * std::pow(newFlowPercent, 3) * std::pow(fanDiameterRatio, 5);
            }
            else if (motorControlTypeNew == TwoSpeed) {
                powerNew *= std::pow(fanDiameterRatio, 5);
            }
            else {
                powerNew = powerBaseline * std::pow(fanDiameterRatio, 5);
            }
        }
        else if (motorControlTypeNew == VSD) {
            powerNew = powerBaseline * std::pow(desiredFlowPercent, 3);
        }

        return {powerCurrent * operatingHours, powerNew * operatingHours,
            (powerCurrent - powerNew) * operatingHours * electricityCost};
    }

    static double get50PercentTimeFactor(const double flowPercent) {
        const double timeAbove50Percent = (flowPercent - 0.5) / 0.5 < 0 ? 0 : (flowPercent - 0.5) / 0.5;
        const double timeAt0Percent     = (0.5 - flowPercent) / 0.5 < 0 ? 0 : (0.5 - flowPercent) / 0.5;
        const double timeAt50Percent    = 1 - timeAbove50Percent - timeAt0Percent;

        return timeAbove50Percent + timeAt50Percent * 0.125;
    }
};