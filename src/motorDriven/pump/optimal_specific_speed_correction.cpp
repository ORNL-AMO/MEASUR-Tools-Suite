#include "motorDriven/pump/optimal_specific_speed_correction.h"

namespace {

// HI 20.3-2020 correction values are percentage points, not fractions.

constexpr double vertical_x[] = {1717.2, 2146.5, 2575.8, 3005.1, 3434.4, 3863.7, 4293.0, 4722.3, 5151.6, 5580.9, 6010.2, 6439.5, 6868.8, 7727.4, 8586.0, 9444.6, 10303.2, 11161.8, 12020.4, 12879.0, 13737.6, 14596.2, 15454.8, 16313.4, 17172.0};
constexpr double vertical_y[] = {4.59, 2.97, 1.755, 1.08, 0.54, 0.135, 0.0, 0.0, 0.0, 0.135, 0.27, 0.45, 0.675, 1.215, 1.755, 2.43, 3.105, 3.78, 4.455, 5.13, 5.805, 6.48, 7.155, 7.83, 8.505};
const pchip::Interpolator vertical(vertical_x, vertical_y);

constexpr double nonvertical_x[] = {630.0, 1350.0, 2160.0, 3600.0, 6300.0};
constexpr double nonvertical_y[] = {13.014, 2.7, 0.0, 1.62, 7.695};
const pchip::Interpolator nonvertical(nonvertical_x, nonvertical_y);

const pchip::Interpolator& selectCurve(Pump::Style style) {
    return style == Pump::Style::VERTICAL_TURBINE ? vertical : nonvertical;
}
} // namespace

namespace optimal_specific_speed_correction {

double calculate(const Input& input) {
    return selectCurve(input.style).evaluate(input.specific_speed) / 100.0;
}

pchip::Range speedLimits(Pump::Style style) {
    const auto& curve = selectCurve(style);
    return {curve.minimum(), curve.maximum()};
}

} // namespace optimal_specific_speed_correction
