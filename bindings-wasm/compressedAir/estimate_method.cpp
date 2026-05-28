#include <emscripten/bind.h>

#include "compressedAir/estimate_method.h"

using namespace emscripten;
using namespace estimate_method;

EMSCRIPTEN_BINDINGS(estimate_method) {
    // calculateEstimateMethod(EstimateMethodInput) -> EstimateMethodResult
    //   operatingTime    [hr]   - annual system operating time
    //   leakRateEstimate [scfm] - estimated leak rate from visual/audible assessment
    //   -> annualConsumption [kscf]
    value_object<Input>("EstimateMethodInput")
        .field("operatingTime",    &Input::operating_time)
        .field("leakRateEstimate", &Input::leak_rate_estimate);

    value_object<Result>("EstimateMethodResult")
        .field("annualConsumption", &Result::annual_consumption);

    function("calculateEstimateMethod", &calculate);
}
