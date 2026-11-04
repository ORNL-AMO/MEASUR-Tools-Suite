#include "motorDriven/pump/optimal_deviation_factor.h"

namespace {

// HI 20.3-2020 positive relative deviation, interpolated against raw US gpm.

constexpr double positive_x[] = {35.0, 100.0, 1000.0, 10000.0, 100000.0};
constexpr double positive_y[] = {8.0, 6.5, 3.7, 2.0, 1.0};
const pchip::Interpolator positive(positive_x, positive_y);

 } // namespace

namespace optimal_deviation_factor {

double calculate(double flow_rate) {
    return 1.0 + positive.evaluate(flow_rate) / 100.0;
}

pchip::Range flowLimits() {
    return {positive.minimum(), positive.maximum()};
}

} // namespace optimal_deviation_factor
