#include "motorDriven/pump/optimal_pre_pump_efficiency.h"

#include <cmath>

namespace {

// Baseline/amplitudes are percentage points; decay coefficients are inverse US gpm.
struct EfficiencyCurve {
    double baseline_efficiency_percent;
    double first_exponential_amplitude_percent;
    double first_flow_decay_coefficient;
    double second_exponential_amplitude_percent;
    double second_flow_decay_coefficient;
};

constexpr EfficiencyCurve double_suction_low_flow{
    90.190375, -7.8068742, 0.00033366482, -8.1364684, 0.0026659434};
constexpr EfficiencyCurve double_suction_high_flow{
    91.0, -3.6664629, 0.0001264433, -14.697275, 0.00072855045};
constexpr EfficiencyCurve vertical_turbine_low_flow{
    87.456119, -9.3556039, 0.00067139092, -9.4309496, 0.0039344122};
constexpr EfficiencyCurve vertical_turbine_middle_flow{
    89.899894, -5.9800814, 0.00019480643, -7.0638099, 0.0010440162};
constexpr EfficiencyCurve vertical_turbine_high_flow{
    90.124016, -1.7332611, 0.00014953651, -3.3197451, 0.00015232542};
constexpr EfficiencyCurve large_end_suction{
    90.379274, -3.000737, 0.000034054964, -4.818246, 0.00019083831};
constexpr EfficiencyCurve ansi_api_low_flow{
    84.655455, -18.706336, 0.0016056629, -20.655962, 0.0081197589};
constexpr EfficiencyCurve ansi_api_high_flow{
    87.748473, -7.6842423, 0.0003739105, -17.336122, 0.0024096967};
constexpr EfficiencyCurve boiler_feed_low_flow{
    84.286574, -17.836167, 0.0013236525, -26.951966, 0.0068256307};
constexpr EfficiencyCurve boiler_feed_high_flow{
    87.129684, -7.8144274, 0.00034998448, -19.605637, 0.0022387671};
constexpr EfficiencyCurve api_double_suction_and_stock_low_flow{
    87.199887, -10.580842, 0.00027878405, -23.785033, 0.0018831236};
constexpr EfficiencyCurve api_double_suction_and_stock_high_flow{
    90.158464, -4.8350009, 0.000048652395, -7.2881572, 0.00027630687};
constexpr EfficiencyCurve sewage_low_flow{
    83.528143, -23.543231, 0.00071315587, -37.584938, 0.005809375};
constexpr EfficiencyCurve sewage_high_flow{
    89.704526, -6.9708815, 0.000057096295, -13.868089, 0.00046766436};
constexpr EfficiencyCurve slurry_low_flow{
    79.096487, -32.006283, 0.00084199445, -23.100062, 0.0064912714};
constexpr EfficiencyCurve slurry_high_flow{
    85.957484, -15.256678, 0.00017627657, -24.920847, 0.0012055457};

constexpr double double_suction_flow_threshold = 9000.0;
constexpr double vertical_turbine_lower_flow_threshold = 2550.0;
constexpr double vertical_turbine_upper_flow_threshold = 7220.0;
constexpr double ansi_api_flow_threshold = 1030.0;
constexpr double boiler_feed_flow_threshold = 890.0;
constexpr double api_double_suction_and_stock_flow_threshold = 4440.0;
constexpr double sewage_flow_threshold = 2170.0;
constexpr double slurry_flow_threshold = 1690.0;
constexpr double unsupported_style_efficiency_percent = 0.0;

double evaluate_curve(const EfficiencyCurve& curve, double flow_rate) {
    const double first_exponential_decay = std::exp(-curve.first_flow_decay_coefficient * flow_rate);
    const double second_exponential_decay = std::exp(-curve.second_flow_decay_coefficient * flow_rate);
    const double exponential_adjustment_percent =
        curve.first_exponential_amplitude_percent * first_exponential_decay +
        curve.second_exponential_amplitude_percent * second_exponential_decay;
    return curve.baseline_efficiency_percent + exponential_adjustment_percent;
}

const EfficiencyCurve* select_curve(Pump::Style style, double flow_rate) {
    switch (style) {
        case Pump::Style::DOUBLE_SUCTION:
            if (flow_rate < double_suction_flow_threshold) {
                return &double_suction_low_flow;
            }
            return &double_suction_high_flow;
        case Pump::Style::VERTICAL_TURBINE:
        case Pump::Style::AXIAL_FLOW:
            if (flow_rate < vertical_turbine_lower_flow_threshold) {
                return &vertical_turbine_low_flow;
            }
            if (flow_rate < vertical_turbine_upper_flow_threshold) {
                return &vertical_turbine_middle_flow;
            }
            return &vertical_turbine_high_flow;
        case Pump::Style::LARGE_END_SUCTION:
            return &large_end_suction;
        case Pump::Style::END_SUCTION_ANSI_API:
            if (flow_rate < ansi_api_flow_threshold) {
                return &ansi_api_low_flow;
            }
            return &ansi_api_high_flow;
        case Pump::Style::MULTISTAGE_BOILER_FEED:
            if (flow_rate < boiler_feed_flow_threshold) {
                return &boiler_feed_low_flow;
            }
            return &boiler_feed_high_flow;
        case Pump::Style::API_DOUBLE_SUCTION:
        case Pump::Style::END_SUCTION_STOCK:
            if (flow_rate < api_double_suction_and_stock_flow_threshold) {
                return &api_double_suction_and_stock_low_flow;
            }
            return &api_double_suction_and_stock_high_flow;
        case Pump::Style::END_SUCTION_SEWAGE:
        case Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE:
            if (flow_rate < sewage_flow_threshold) {
                return &sewage_low_flow;
            }
            return &sewage_high_flow;
        case Pump::Style::END_SUCTION_SLURRY:
            if (flow_rate < slurry_flow_threshold) {
                return &slurry_low_flow;
            }
            return &slurry_high_flow;
        case Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY:
        case Pump::Style::POSITIVE_DISPLACEMENT:
            return nullptr;
    }
    return nullptr;
}

} // namespace

namespace optimal_pre_pump_efficiency {

double calculate(const Input& input) {
    const EfficiencyCurve* selected_curve = select_curve(input.style, input.flow_rate);
    if (selected_curve == nullptr) {
        return unsupported_style_efficiency_percent;
    }
    return evaluate_curve(*selected_curve, input.flow_rate);
}

} // namespace optimal_pre_pump_efficiency
