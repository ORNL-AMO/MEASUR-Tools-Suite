

#include "processHeat/losses/auxiliary_power_used.h"

#include <cmath>
#include "physics/constants.h"

namespace auxiliary_power_used {

double calculatePowerUsed(double motor_phase, double supply_voltage, double avg_current, double power_factor,
                    double operating_time) {
              // Convert percent inputs to fractions
              const double ot_frac = operating_time / 100.0;
              // Electrical power in kW
              const double electrical_kw = std::pow(motor_phase, 0.5) * supply_voltage * avg_current * power_factor * ot_frac / 1000.0;
              // Convert kW to BTU/hr using constant
              const double btu_per_hr = electrical_kw * physics::conversions::kKilowattToBtuPerHour;
              return btu_per_hr;
}
} // namespace auxiliary_power_used