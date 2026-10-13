#include <emscripten/bind.h>

#include <array>

#include "motorDriven/motor/estimate_fla.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(estimate_fla) {
    value_array<std::array<double, 6>>("EstimateFLAPartialLoadCurrents")
        .element(emscripten::index<0>())
        .element(emscripten::index<1>())
        .element(emscripten::index<2>())
        .element(emscripten::index<3>())
        .element(emscripten::index<4>())
        .element(emscripten::index<5>());

    value_object<estimate_fla::Input>("EstimateFLAInput")
        .field("motorRatedPower", &estimate_fla::Input::motor_rated_power)
        .field("motorRpm", &estimate_fla::Input::motor_rpm)
        .field("lineFrequency", &estimate_fla::Input::line_frequency)
        .field("efficiencyClass", &estimate_fla::Input::efficiency_class)
        .field("specifiedEfficiency", &estimate_fla::Input::specified_efficiency)
        .field("ratedVoltage", &estimate_fla::Input::rated_voltage);

    value_object<estimate_fla::Result>("EstimateFLAOutput")
        .field("estimatedFLA", &estimate_fla::Result::estimated_fla)
        .field("partialLoadCurrents", &estimate_fla::Result::partial_load_currents);

    function("calculateEstimateFLA", &estimate_fla::calculate);
}
