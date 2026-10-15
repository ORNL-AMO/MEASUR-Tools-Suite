#include "motorDriven/motor/motor_shaft_power.h"

#include <cmath>

#include "motorDriven/motor/motor_current.h"
#include "motorDriven/motor/motor_efficiency.h"
#include "motorDriven/motor/motor_power.h"
#include "motorDriven/motor/motor_power_factor.h"

namespace motor_shaft_power {

Result calculate(const Input& input) {
    double power_factor, efficiency, current, power, estimated_fla;

    if (input.load_estimation_method == Motor::LoadEstimationMethod::POWER) {
        double temp_load_fraction = 0.01;
        double power_e1 = 0, power_e2 = 0, lf1 = 0, lf2 = 0, eff1 = 0, eff2 = 0, pf1 = 0, pf2 = 0;
        while (true) {
            const auto motor_current_result = motor_current::calculate(
                {input.motor_rated_power, input.motor_rpm, input.line_frequency, input.efficiency_class,
                 input.specified_efficiency,
                 temp_load_fraction, input.rated_voltage},
                input.full_load_amps);
            current = motor_current_result.current;
            efficiency = motor_efficiency::calculate(
                             {input.line_frequency, input.motor_rpm, input.efficiency_class, input.motor_rated_power,
                              temp_load_fraction,
                              input.specified_efficiency})
                             .efficiency;
            power_factor = motor_power_factor::calculate(
                {input.line_frequency, input.motor_rpm, input.efficiency_class, input.specified_efficiency,
                 input.motor_rated_power,
                 temp_load_fraction, current, efficiency, input.rated_voltage});
            power = motor_power::calculate(input.rated_voltage, current, power_factor);
            if (power > input.motor_measured_power || temp_load_fraction > 1.5) {
                power_e2     = power;
                lf2          = temp_load_fraction;
                eff2         = efficiency;
                pf2          = power_factor;
                estimated_fla = motor_current_result.estimated_fla;
                break;
            }
            else {
                power_e1 = power;
                lf1      = temp_load_fraction;
                eff1     = efficiency;
                pf1      = power_factor;
                temp_load_fraction += 0.01;
            }
        }

        const double motor_power_diff         = power_e2 - power_e1;
        const double measured_motor_power_diff = input.motor_measured_power - power_e1;
        const double fractional_index         = lf1 + ((measured_motor_power_diff / motor_power_diff) / 100);
        efficiency                            = eff1 + 100 * (fractional_index - lf1) * (eff2 - eff1);
        const double adjpf1 =
            pf1 / ((((input.field_voltage / input.rated_voltage - 1) * (-2 * lf1 + 1)) + 1) *
                   (input.field_voltage / input.rated_voltage));
        const double adjpf2 =
            pf2 / ((((input.field_voltage / input.rated_voltage - 1) * (-2 * lf2 + 1)) + 1) *
                   (input.field_voltage / input.rated_voltage));
        power_factor = adjpf1 + 100 * (fractional_index - lf1) * (adjpf2 - adjpf1);

        current = input.motor_measured_power / (input.field_voltage * std::sqrt(3) * power_factor / 1000);
        // Convert mechanical output from kW to hp.
        const auto shaft_power = (input.motor_measured_power * efficiency) / 0.746;
        // Preserve measured electrical input power.
        power = input.motor_measured_power;
        return {shaft_power, current, power_factor, efficiency, power, estimated_fla, fractional_index};
    }
    else { // CURRENT path, including the legacy fallback for other enum values.
        double temp_load_fraction = 0.00;
        double power_e1, power_e2, lf1, lf2, eff1, eff2, current1, current2;
        while (true) {
            const auto motor_current_result = motor_current::calculate(
                {input.motor_rated_power, input.motor_rpm, input.line_frequency, input.efficiency_class,
                 input.specified_efficiency,
                 temp_load_fraction, input.rated_voltage},
                input.full_load_amps);
            current = motor_current_result.current;
            if (current > input.field_current || temp_load_fraction > 1.5) {
                efficiency = motor_efficiency::calculate(
                                 {input.line_frequency, input.motor_rpm, input.efficiency_class, input.motor_rated_power,
                              temp_load_fraction,
                                  input.specified_efficiency})
                                 .efficiency;
                power_factor = motor_power_factor::calculate(
                    {input.line_frequency, input.motor_rpm, input.efficiency_class, input.specified_efficiency,
                 input.motor_rated_power,
                     temp_load_fraction, current, efficiency, input.rated_voltage});
                power        = motor_power::calculate(input.rated_voltage, current, power_factor);
                current2     = current;
                power_e2     = power;
                lf2          = temp_load_fraction;
                eff2         = efficiency;
                estimated_fla = motor_current_result.estimated_fla;
                break;
            }
            temp_load_fraction += 0.01;
        }
        // Evaluate the point one load increment below the selected upper point.
        temp_load_fraction -= 0.01;
        current = motor_current::calculate(
                      {input.motor_rated_power, input.motor_rpm, input.line_frequency, input.efficiency_class,
                 input.specified_efficiency,
                       temp_load_fraction, input.rated_voltage},
                      input.full_load_amps)
                      .current;
        efficiency  = motor_efficiency::calculate(
                          {input.line_frequency, input.motor_rpm, input.efficiency_class, input.motor_rated_power,
                              temp_load_fraction,
                           input.specified_efficiency})
                          .efficiency;
        power_factor = motor_power_factor::calculate(
            {input.line_frequency, input.motor_rpm, input.efficiency_class, input.specified_efficiency,
                 input.motor_rated_power,
             temp_load_fraction, current, efficiency, input.rated_voltage});
        power    = motor_power::calculate(input.rated_voltage, current, power_factor);
        current1 = current;
        power_e1 = power;
        lf1      = temp_load_fraction;
        eff1     = efficiency;

        // Correct both endpoint currents after the unadjusted-current search.
        const double adjusted_current1         = ((input.field_voltage / input.rated_voltage - 1) * (1 - 2 * lf1) + 1) * current1;
        const double adjusted_current2         = ((input.field_voltage / input.rated_voltage - 1) * (1 - 2 * lf2) + 1) * current2;
        const double current_diff         = adjusted_current2 - adjusted_current1;
        const double measured_current_diff = input.field_current - adjusted_current1;
        const double fractional_index     = lf1 + (measured_current_diff / current_diff) / 100;

        current    = input.field_current;
        efficiency = eff1 + 100 * (fractional_index - lf1) * (eff2 - eff1);
        power      = power_e1 + 100 * (fractional_index - lf1) * (power_e2 - power_e1);

        power_factor = power / (current * input.field_voltage * std::sqrt(3) / 1000);
        // Convert mechanical output from kW to hp.
        const double shaft_power = (power * efficiency) / 0.746;
        return {shaft_power, current, power_factor, efficiency, power, estimated_fla, fractional_index};
    }
}

} // namespace motor_shaft_power
