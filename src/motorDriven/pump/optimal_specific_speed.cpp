#include "motorDriven/pump/optimal_specific_speed.h"

#include <cmath>

namespace optimal_specific_speed {

double calculate(const Input& input) {
    const double specific_speed = input.rpm * std::sqrt(input.flow_rate) /
                                  (std::pow((input.head / input.stage_count), 0.75));
    return specific_speed;
}

} // namespace optimal_specific_speed
