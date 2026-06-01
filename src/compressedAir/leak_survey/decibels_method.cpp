#include "compressedAir/leak_survey/decibels_method.h"

namespace decibels_method {

Result calculate(const Input& input) {
    const double denominator = (input.pressure_b - input.pressure_a) *
                               (input.decibel_rating_b - input.decibel_rating_a);

    const double leak_rate_estimate =
        ((input.pressure_b - input.line_pressure) * (input.decibel_rating_b - input.decibels)) / denominator *
            input.first_flow_a +
        ((input.line_pressure - input.pressure_a) * (input.decibel_rating_b - input.decibels)) / denominator *
            input.second_flow_a +
        ((input.pressure_b - input.line_pressure) * (input.decibels - input.decibel_rating_a)) / denominator *
            input.first_flow_b +
        ((input.line_pressure - input.pressure_a) * (input.decibels - input.decibel_rating_a)) / denominator *
            input.second_flow_b;

    const double annual_consumption = (leak_rate_estimate * input.operating_time * 60.0) / 1000.0;

    return {leak_rate_estimate, annual_consumption};
}

} // namespace decibels_method
