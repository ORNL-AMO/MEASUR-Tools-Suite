#include "motorDriven/pump/optimal_specific_speed_correction.h"

#include <cmath>

namespace {
struct PolynomialCurve {
    double constant;
    double linear;
    double quadratic;
    double cubic;
    double quartic;
    double quintic;
    double sextic;
};

constexpr PolynomialCurve nonvertical_low_speed{
    14.884085, -0.021342141, 0.0000121172, -0.0000000031885957,
    1.4907927E-13, 1.2855352E-16, -2.3798184E-20};
constexpr PolynomialCurve nonvertical_high_speed{
    6.5703317, -0.010048327, 0.0000061475098, -0.0000000019659725,
    3.5079978E-13, -3.2272033E-17, 1.1881188E-21};
constexpr PolynomialCurve vertical_low_speed{
    14.788539, -0.022490348, 0.000017226359, -0.0000000075690542,
    1.8893534E-12, -2.4834106E-16, 1.3345507E-20};
constexpr PolynomialCurve vertical_high_speed{
    4.0559384, -0.0026632249, 0.0000006761157, -0.000000000087766773,
    6.5103425E-15, -2.5380141E-19, 4.007753E-24};
constexpr double nonvertical_speed_threshold = 2530;
constexpr double vertical_speed_threshold = 4550;
constexpr double percentage_points_per_fraction = 100;

double evaluateCorrection(const PolynomialCurve& curve, double specific_speed) {
    const double correction_percent =
        curve.constant + (curve.linear * specific_speed) + (curve.quadratic * std::pow(specific_speed, 2)) +
        (curve.cubic * std::pow(specific_speed, 3)) + (curve.quartic * std::pow(specific_speed, 4)) +
        (curve.quintic * std::pow(specific_speed, 5)) + (curve.sextic * std::pow(specific_speed, 6));
    const double nonnegative_correction_percent = std::fmax(correction_percent, 0);
    return nonnegative_correction_percent / percentage_points_per_fraction;
}
} // namespace

namespace optimal_specific_speed_correction {

double calculate(const Input& input) {
    if (input.style == Pump::Style::VERTICAL_TURBINE) {
        if (input.specific_speed < vertical_speed_threshold) {
            return evaluateCorrection(vertical_low_speed, input.specific_speed);
        }
        return evaluateCorrection(vertical_high_speed, input.specific_speed);
    }
    if (input.specific_speed < nonvertical_speed_threshold) {
        return evaluateCorrection(nonvertical_low_speed, input.specific_speed);
    }
    return evaluateCorrection(nonvertical_high_speed, input.specific_speed);
}

} // namespace optimal_specific_speed_correction
