#include "compressedAir/estimate_method.h"

namespace estimate_method {

Result calculate(const Input& input) {
    const double annual_consumption =
        (input.leak_rate_estimate * input.operating_time * 60.0) / 1000.0;
    return {annual_consumption};
}

} // namespace estimate_method
