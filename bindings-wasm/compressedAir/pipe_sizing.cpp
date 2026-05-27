#include <emscripten/bind.h>
#include "compressedAir/pipe_sizing.h"

using namespace emscripten;
using namespace pipe_sizing;

EMSCRIPTEN_BINDINGS(pipe_sizing) {
    // ---- Pipe Sizing ----
    value_object<Input>("PipeSizingInput")
        // airflow: volumetric free-air flow rate [ft³/min (cfm)]
        .field("airflow",             &Input::airflow)
        // airlinePressure: operating gauge pressure in the pipe [psig]
        .field("airlinePressure",     &Input::airline_pressure)
        // designVelocity: maximum allowable compressed-air velocity [ft/s]
        .field("designVelocity",      &Input::design_velocity)
        // atmosphericPressure: local atmospheric pressure [psia], default 14.7
        .field("atmosphericPressure", &Input::atmospheric_pressure);

    value_object<Result>("PipeSizingResult")
        // crossSectionalArea: minimum required internal pipe area [in²]
        .field("crossSectionalArea", &Result::cross_sectional_area)
        // pipeDiameter: minimum required internal pipe diameter [in]
        .field("pipeDiameter",       &Result::pipe_diameter);

    function("calculatePipeSize", &calculate);
}
