#include <emscripten/bind.h>

#include "compressedAir/decibels_method.h"

using namespace emscripten;
using namespace decibels_method;

EMSCRIPTEN_BINDINGS(decibels_method) {
    // ---- Decibels Method ----
    // calculateDecibelsMethod(DecibelsMethodInput) -> DecibelsMethodResult
    //   operatingTime   [hr]     - annual system operating time
    //   linePressure    [psig]   - measured compressed air line pressure
    //   decibels        [dB]     - measured ultrasonic decibel level at the leak
    //   decibelRatingA  [dB]     - lower reference decibel rating (point A)
    //   pressureA       [psig]   - lower reference pressure (point A)
    //   firstFlowA      [scfm]   - flow rate at (pressureA, decibelRatingA)
    //   secondFlowA     [scfm]   - flow rate at (pressureB, decibelRatingA)
    //   decibelRatingB  [dB]     - upper reference decibel rating (point B)
    //   pressureB       [psig]   - upper reference pressure (point B)
    //   firstFlowB      [scfm]   - flow rate at (pressureA, decibelRatingB)
    //   secondFlowB     [scfm]   - flow rate at (pressureB, decibelRatingB)
    //   -> leakRateEstimate  [scfm]  - estimated compressed air leak flow rate
    //   -> annualConsumption [kscf]  - estimated annual air loss from the leak
    value_object<Input>("DecibelsMethodInput")
        .field("operatingTime",  &Input::operating_time)
        .field("linePressure",   &Input::line_pressure)
        .field("decibels",       &Input::decibels)
        .field("decibelRatingA", &Input::decibel_rating_a)
        .field("pressureA",      &Input::pressure_a)
        .field("firstFlowA",     &Input::first_flow_a)
        .field("secondFlowA",    &Input::second_flow_a)
        .field("decibelRatingB", &Input::decibel_rating_b)
        .field("pressureB",      &Input::pressure_b)
        .field("firstFlowB",     &Input::first_flow_b)
        .field("secondFlowB",    &Input::second_flow_b);

    value_object<Result>("DecibelsMethodResult")
        .field("leakRateEstimate", &Result::leak_rate_estimate)
        .field("annualConsumption", &Result::annual_consumption);

    function("calculateDecibelsMethod", &calculate);
}
