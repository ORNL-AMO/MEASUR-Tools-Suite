#include <emscripten/bind.h>

#include "motorDriven/motor/motor_efficiency.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(motor_efficiency) {
    value_object<motor_efficiency::Input>("MotorEfficiencyInput")
        .field("lineFrequency", &motor_efficiency::Input::line_frequency)
        .field("motorRpm", &motor_efficiency::Input::motor_rpm)
        .field("efficiencyClass", &motor_efficiency::Input::efficiency_class)
        .field("motorRatedPower", &motor_efficiency::Input::motor_rated_power)
        .field("loadFactor", &motor_efficiency::Input::load_factor)
        .field("specifiedEfficiency", &motor_efficiency::Input::specified_efficiency);

    function("calculateMotorEfficiency", optional_override([](const motor_efficiency::Input& input) {
                 return motor_efficiency::calculate(input).efficiency;
             }));
}
