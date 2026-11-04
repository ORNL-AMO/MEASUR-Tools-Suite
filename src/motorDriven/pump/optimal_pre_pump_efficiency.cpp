#include "motorDriven/pump/optimal_pre_pump_efficiency.h"

#include <limits>

namespace {

// HI 20.3-2020, engineering reference 2026-09-23; C/H digitized by engineering.

constexpr double curve_a_x[] = {100.0, 500.0, 2000.0, 7000.0, 10000.0, 80000.0};
constexpr double curve_a_y[] = {39.0, 62.5, 75.5, 82.0, 83.2, 88.5};
const pchip::Interpolator curve_a(curve_a_x, curve_a_y);

constexpr double curve_b_x[] = {100.0, 110.0, 400.0, 1000.0, 2000.0, 4000.0, 10000.0, 25000.0, 52000.0};
constexpr double curve_b_y[] = {40.5, 42.0, 62.0, 72.0, 78.0, 82.0, 85.7, 88.0, 89.35};
const pchip::Interpolator curve_b(curve_b_x, curve_b_y);

constexpr double curve_c_x[] = {100.0, 300.0, 700.0, 1000.0, 2000.0, 5000.0, 10000.0, 30000.0, 100000.0};
constexpr double curve_c_y[] = {41.5, 60.0, 71.0, 74.5, 79.3, 84.2, 86.8, 88.8, 89.9};
const pchip::Interpolator curve_c(curve_c_x, curve_c_y);

constexpr double curve_d_x[] = {400.0, 450.0, 1000.0, 2000.0, 4000.0, 10000.0, 22000.0};
constexpr double curve_d_y[] = {66.5, 68.0, 75.5, 80.56, 83.69, 86.7, 88.4};
const pchip::Interpolator curve_d(curve_d_x, curve_d_y);

constexpr double curve_e_x[] = {100.0, 400.0, 1000.0, 2000.0, 4000.0};
constexpr double curve_e_y[] = {55.0, 72.0, 79.5, 83.0, 85.18};
const pchip::Interpolator curve_e(curve_e_x, curve_e_y);

constexpr double curve_f_x[] = {100.0, 200.0, 400.0, 1000.0, 2250.0, 5000.0};
constexpr double curve_f_y[] = {59.5, 67.0, 74.0, 80.9, 84.36, 86.4};
const pchip::Interpolator curve_f(curve_f_x, curve_f_y);

constexpr double curve_g_x[] = {101.0, 400.0, 700.0, 1000.0, 2000.0, 3000.0, 5000.0, 12000.0, 20000.0, 35000.0, 50000.0, 65000.0, 80000.0, 100000.0};
constexpr double curve_g_y[] = {69.5, 77.7, 80.4, 81.9, 84.5, 85.6, 86.8, 88.3, 89.0, 89.5, 89.86, 90.1, 90.2, 90.31};
const pchip::Interpolator curve_g(curve_g_x, curve_g_y);

constexpr double curve_h_x[] = {300.0, 500.0, 700.0, 1000.0, 1300.0};
constexpr double curve_h_y[] = {67.5, 73.5, 77.5, 81.0, 86.5};
const pchip::Interpolator curve_h(curve_h_x, curve_h_y);

constexpr double curve_j_x[] = {200.0, 1000.0, 4000.0, 10000.0, 25400.0, 60000.0, 100000.0};
constexpr double curve_j_y[] = {78.0, 84.0, 88.15, 89.96, 90.84, 90.95, 91.0};
const pchip::Interpolator curve_j(curve_j_x, curve_j_y);

constexpr double curve_v_x[] = {200.0, 1000.0, 4000.0, 10000.0, 20000.0, 40000.0};
constexpr double curve_v_y[] = {75.0, 82.5, 87.0, 89.0, 89.85, 90.13};
const pchip::Interpolator curve_v(curve_v_x, curve_v_y);

const pchip::Interpolator* selectCurve(Pump::Style style) {
    switch (style) {

        case Pump::Style::END_SUCTION_SLURRY: return &curve_a;

        case Pump::Style::END_SUCTION_SEWAGE: return &curve_b;

        case Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE: return &curve_c;

        case Pump::Style::END_SUCTION_STOCK: return &curve_d;

        case Pump::Style::MULTISTAGE_BOILER_FEED: return &curve_e;

        case Pump::Style::END_SUCTION_ANSI_API: return &curve_f;

        case Pump::Style::LARGE_END_SUCTION: return &curve_g;

        case Pump::Style::API_DOUBLE_SUCTION: return &curve_h;

        case Pump::Style::DOUBLE_SUCTION: return &curve_j;

        case Pump::Style::AXIAL_FLOW:

        case Pump::Style::VERTICAL_TURBINE: return &curve_v;

        default: return nullptr;
    }
}
} // namespace

namespace optimal_pre_pump_efficiency {

double calculate(const Input& input) {
    const auto* curve = selectCurve(input.style);
    return curve ? curve->evaluate(input.flow_rate) : std::numeric_limits<double>::quiet_NaN();
}

pchip::Range flowLimits(Pump::Style style) {
    const auto* curve = selectCurve(style);
    const double nan = std::numeric_limits<double>::quiet_NaN();
    return curve ? pchip::Range{curve->minimum(), curve->maximum()} : pchip::Range{nan, nan};
}

} // namespace optimal_pre_pump_efficiency
