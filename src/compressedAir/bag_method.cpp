#include "compressedAir/bag_method.h"

namespace bag_method {

Result calculate(const Input& input) {
    const double flow_rate = input.bag_volume / (input.bag_fill_time / 60);
    const double annual_consumption =
        (flow_rate * input.operating_time * input.number_of_units * 60.0) / 1000.0;
    return {flow_rate, annual_consumption};
}

} // namespace bag_method
