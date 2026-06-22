#include <emscripten/bind.h>

#include "compressedAir/air_velocity.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(air_velocity) {
    value_object<air_velocity::Input>("AirVelocityInput")
        .field("airFlow", &air_velocity::Input::airflow)
        .field("pipePressure", &air_velocity::Input::pipe_pressure)
        .field("atmosphericPressure", &air_velocity::Input::atmospheric_pressure);

    function("calculateAirVelocity", &air_velocity::calculate);
}
