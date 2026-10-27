#include "motorDriven/pump/pump_result.h"

#include "motorDriven/motor/motor_shaft_power.h"
#include "motorDriven/motor/optimal_motor_power.h"
#include "motorDriven/motor/OptimalMotorShaftPower.h"
#include "motorDriven/pumpFan/mover_efficiency.h"
#include "motorDriven/pumpFan/MoverShaftPower.h"
#include "motorDriven/pumpFan/OptimalPumpShaftPower.h"
#include "physics/constants.h"

namespace pump_result {

Result calculateExisting(const ExistingInput& input) {
    const auto& system = input.system;
    const auto motorOutput =
        motor_shaft_power::calculate({system.motor_rated_power, input.measured_motor_power, system.motor_rated_speed,
                        system.line_frequency, system.motor_efficiency_class, system.specified_motor_efficiency,
                        system.motor_rated_voltage, input.motor_full_load_amps, system.operating_voltage,
                        input.load_estimation_method, input.measured_motor_current});

    const auto moverOutput = MoverShaftPower(motorOutput.shaft_power, system.drive,
                                              system.specified_drive_efficiency)
                                 .calculate();

    double pumpEfficiency;
    if (system.pump_style == Pump::Style::POSITIVE_DISPLACEMENT) {
        const auto hydraulicPower = system.flow_rate * system.differential_pressure /
                                    physics::conversions::kPumpGpmPsiPerHp;
        pumpEfficiency = hydraulicPower / moverOutput.moverShaftPower;
    } else {
        pumpEfficiency = mover_efficiency::calculatePump({system.specific_gravity, system.flow_rate,
            system.head, moverOutput.moverShaftPower});
    }

    const auto annualEnergy = motorOutput.power * system.operating_hours / 1000.0;
    const auto annualCost = annualEnergy * system.unit_cost;

    return {
        pumpEfficiency,
        system.motor_rated_power,
        motorOutput.shaft_power,
        moverOutput.moverShaftPower,
        motorOutput.efficiency,
        motorOutput.power_factor,
        motorOutput.current,
        motorOutput.power,
        annualEnergy,
        annualCost,
        motorOutput.load_factor,
        moverOutput.driveEfficiency,
        motorOutput.estimated_fla,
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
    const auto motorOutput = optimal_motor_power::calculate({
        system.motor_rated_power, system.motor_rated_speed, system.line_frequency,
        system.motor_efficiency_class, system.specified_motor_efficiency,
        system.motor_rated_voltage, system.operating_voltage, motorShaftOutput.motorShaftPower});

    const auto annualEnergy = motorOutput.power * system.operating_hours / 1000.0;
    const auto annualCost = annualEnergy * system.unit_cost;

    return {
        input.pump_efficiency,
        system.motor_rated_power,
        motorShaftOutput.motorShaftPower,
        moverShaftPower,
        motorOutput.efficiency,
        motorOutput.power_factor,
        motorOutput.current,
        motorOutput.power,
        annualEnergy,
        annualCost,
        motorOutput.load_factor,
        motorShaftOutput.driveEfficiency,
        0.0,
    };
}

} // namespace pump_result
