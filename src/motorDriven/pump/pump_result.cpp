#include "motorDriven/pump/pump_result.h"

#include "motorDriven/motor/MotorShaftPower.h"
#include "motorDriven/motor/OptimalMotorPower.h"
#include "motorDriven/motor/OptimalMotorShaftPower.h"
#include "motorDriven/pumpFan/MoverEfficiency.h"
#include "motorDriven/pumpFan/MoverShaftPower.h"
#include "motorDriven/pumpFan/OptimalPumpShaftPower.h"
#include "physics/constants.h"

namespace pump_result {

Result calculateExisting(const ExistingInput& input) {
    const auto& system = input.system;
    const auto motorOutput =
        MotorShaftPower(system.motor_rated_power, input.measured_motor_power, system.motor_rated_speed,
                        system.line_frequency, system.motor_efficiency_class, system.specified_motor_efficiency,
                        system.motor_rated_voltage, input.motor_full_load_amps, system.operating_voltage,
                        input.load_estimation_method, input.measured_motor_current)
            .calculate();

    const auto moverOutput = MoverShaftPower(motorOutput.shaftPower, system.drive,
                                              system.specified_drive_efficiency)
                                 .calculate();

    double pumpEfficiency;
    if (system.pump_style == Pump::Style::POSITIVE_DISPLACEMENT) {
        const auto hydraulicPower = system.flow_rate * system.differential_pressure /
                                    physics::conversions::kPumpGpmPsiPerHp;
        pumpEfficiency = hydraulicPower / moverOutput.moverShaftPower;
    } else {
        pumpEfficiency = MoverEfficiency(system.specific_gravity, system.flow_rate, system.head,
                                         moverOutput.moverShaftPower)
                             .calculate();
    }

    const auto annualEnergy = motorOutput.power * system.operating_hours / 1000.0;
    const auto annualCost = annualEnergy * system.unit_cost;

    return {
        pumpEfficiency,
        system.motor_rated_power,
        motorOutput.shaftPower,
        moverOutput.moverShaftPower,
        motorOutput.efficiency,
        motorOutput.powerFactor,
        motorOutput.current,
        motorOutput.power,
        annualEnergy,
        annualCost,
        motorOutput.loadFactor,
        moverOutput.driveEfficiency,
        motorOutput.estimatedFLA,
    };
}

Result calculateModified(const ModifiedInput& input) {
    const auto& system = input.system;
    double moverShaftPower;
    if (system.pump_style == Pump::Style::POSITIVE_DISPLACEMENT) {
        moverShaftPower = system.flow_rate * system.differential_pressure /
                          (physics::conversions::kPumpGpmPsiPerHp * input.pump_efficiency);
    } else {
        moverShaftPower = OptimalPumpShaftPower(system.flow_rate, system.head, system.specific_gravity,
                                                input.pump_efficiency)
                              .calculate();
    }

    const auto motorShaftOutput =
        OptimalMotorShaftPower(moverShaftPower, system.drive, system.specified_drive_efficiency).calculate();
    const auto motorOutput =
        OptimalMotorPower(system.motor_rated_power, system.motor_rated_speed, system.line_frequency,
                          system.motor_efficiency_class, system.specified_motor_efficiency,
                          system.motor_rated_voltage, system.operating_voltage, motorShaftOutput.motorShaftPower)
            .calculate();

    const auto annualEnergy = motorOutput.power * system.operating_hours / 1000.0;
    const auto annualCost = annualEnergy * system.unit_cost;

    return {
        input.pump_efficiency,
        system.motor_rated_power,
        motorShaftOutput.motorShaftPower,
        moverShaftPower,
        motorOutput.efficiency,
        motorOutput.powerFactor,
        motorOutput.current,
        motorOutput.power,
        annualEnergy,
        annualCost,
        motorOutput.loadFactor,
        motorShaftOutput.driveEfficiency,
        0.0,
    };
}

} // namespace pump_result
