#include "motorDriven/pump/optimal_deviation_factor.h"

#include <cmath>

namespace optimal_deviation_factor {
namespace {

constexpr double base_multiplier = 1.0; ///< Unitless multiplier before applying the deviation.
constexpr double baseline_deviation_percent = 0.10805906; ///< Constant deviation in percentage points.
constexpr double first_exponential_amplitude_percent = 18.077243; ///< First exponential's percentage-point scale.
constexpr double first_log_flow_decay_coefficient = 0.78231304; ///< Unitless decay coefficient for log10(US gpm).
constexpr double second_exponential_amplitude_percent = 30.525232; ///< Second exponential's percentage-point scale.
constexpr double second_log_flow_decay_coefficient = 0.80684022; ///< Unitless decay coefficient for log10(US gpm).
constexpr double percentage_points_per_fraction = 100.0; ///< Percentage-point divisor for conversion to a fraction.

} // namespace

double calculate(double flow_rate) {
    const double logarithmic_flow_rate = std::log10(flow_rate);
    const double first_exponential_decay = std::exp(-first_log_flow_decay_coefficient * logarithmic_flow_rate);
    const double second_exponential_decay = std::exp(-second_log_flow_decay_coefficient * logarithmic_flow_rate);
    const double total_deviation_percent = baseline_deviation_percent +
                                           first_exponential_amplitude_percent * first_exponential_decay +
                                           second_exponential_amplitude_percent * second_exponential_decay;
    const double deviation_fraction = total_deviation_percent / percentage_points_per_fraction;

    return base_multiplier + deviation_fraction;
}

} // namespace optimal_deviation_factor
