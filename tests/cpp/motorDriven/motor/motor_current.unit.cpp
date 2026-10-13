#include "motorDriven/motor/motor_current.h"

#include <array>

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Motor current retains original supplied-FLA goldens", "[motor_current]") {
    const auto frequency = Motor::LineFrequency::FREQ60;
    const auto efficiency_class = Motor::EfficiencyClass::ENERGY_EFFICIENT;
    CHECK(motor_current::calculate({100, 1500, frequency, efficiency_class, 0, 0.25, 460}, 113.8).current ==
          Approx(42.72830));
    CHECK(motor_current::calculate({500, 1785, frequency, efficiency_class, 0, 0.25, 2300}, 557.9).current ==
          Approx(197.4057226065));
    CHECK(motor_current::calculate({500, 1785, frequency, efficiency_class, 0, 0.5, 2300}, 557.9).current ==
          Approx(304.6652143255));
    CHECK(motor_current::calculate({500, 1785, frequency, efficiency_class, 0, 0.75, 2300}, 557.9).current ==
          Approx(426.5420335857));
}

TEST_CASE("Motor current preserves both legacy paths and interpolation boundaries", "[motor_current]") {
    struct Golden {
        motor_current::Input input;
        double full_load_amps;
        double current;
        double optimal_current;
        double estimated_fla;
    };
    // Captured from freshly built legacy MotorCurrent at base 363c011 before replacing the class.
    // Covers anchors, strict branch thresholds and adjacent loads, negative extrapolation, the cap,
    // voltage/FLA scaling, 50/60 Hz, specified baselines, and all three supported premium pole columns.
    const std::array<Golden, 29> goldens = {{
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, -0.1, 460},
         113.8, 32.8037658240359, 32.81364218772196, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0, 460},
         113.8, 33.32079190019643, 33.33082392703388, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.25, 460},
         113.8, 42.72830823335467, 42.7411726195374, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.250999, 460},
         113.8, 42.789155614647775, 42.80203832039999, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.251, 460},
         113.8, 42.80718085695348, 42.820068989638344, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.251001, 460},
         113.8, 42.807259749150035, 42.82014790558729, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.5, 460},
         113.8, 63.72861191330423, 63.747798946645176, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.75, 460},
         113.8, 87.44208444177028, 87.46841098707905, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 1, 460},
         113.8, 113.79999999999656, 113.83426223054711, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 1.25, 460},
         113.8, 142.36380000000074, 142.40666205041475, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 1.250999, 460},
         113.8, 142.48140607203064, 142.5243035305847, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 1.251, 460},
         113.8, 142.48248461595944, 142.5253823992349, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 1.251001, 460},
         113.8, 142.48260331824017, 142.5255011372538, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 1.5, 460},
         113.8, 173.13348444176913, 173.18561044667257, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 1.500001, 460},
         113.8, 173.13348444176913, 173.18561044667257, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 2, 460},
         113.8, 173.13348444176913, 173.18561044667257, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.25, 230},
         113.8, 42.72830823335467, 42.7411726195374, 227.66852446109476},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.25, 460},
         227.6, 85.45661646670933, 42.7411726195374, 113.83426223054738},
        {{100, 1500, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.25, 460},
         0, 0, 42.7411726195374, 113.83426223054738},
        {{500, 1785, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.25, 2300},
         557.9, 197.40572260650677, 197.42286478023064, 111.58968930241159},
        {{500, 1785, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.5, 2300},
         557.9, 304.66521432545727, 304.6916706204591, 111.58968930241159},
        {{500, 1785, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.75, 2300},
         557.9, 426.5420335857156, 426.57907333078305, 111.58968930241159},
        {{50, 1500, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::STANDARD, 0, 0.83, 400},
         70, 58.89825153021016, 50.80518976466062, 69.43869588315538},
        {{200, 1780, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.83, 2300},
         250, 209.68742444056252, 189.39019528960176, 45.160122452478994},
        {{200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 0.95, 0.83, 230},
         450, 377.4373639930088, 189.39019528960176, 454.5766800452733},
        {{200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 0.8, 0.83, 230},
         450, 377.4373639930088, 191.7152954476481, 536.7170257100602},
        {{200, 3600, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM, 0, 0.83, 230},
         450, 376.3832047200176, 182.1248801179472, 435.493374971657},
        {{200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM, 0, 0.83, 230},
         450, 377.437363993001, 187.91191229626423, 448.0762563554074},
        {{200, 1200, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM, 0, 0.83, 230},
         450, 378.20946540586624, 196.41191817410171, 467.38842500147217},
    }};
    for (const auto& golden : goldens) {
        INFO("load=" << golden.input.load_factor << ", rpm=" << golden.input.motor_rpm
             << ", voltage=" << golden.input.rated_voltage << ", FLA=" << golden.full_load_amps
             << ", class=" << static_cast<int>(golden.input.efficiency_class));
        const auto result = motor_current::calculate(golden.input, golden.full_load_amps);
        CHECK(result.current == Approx(golden.current).epsilon(1e-12).margin(1e-9));
        CHECK(result.estimated_fla == Approx(golden.estimated_fla).epsilon(1e-12).margin(1e-9));
        CHECK(motor_current::calculateOptimal(golden.input) == Approx(golden.optimal_current).epsilon(1e-12).margin(1e-9));
    }
}

TEST_CASE("Motor current calls have no retained load or FLA state", "[motor_current]") {
    const motor_current::Input input = {100, 1500, Motor::LineFrequency::FREQ60,
                                       Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0.25, 460};
    auto overloaded = input;
    overloaded.load_factor = 2;
    auto capped = input;
    capped.load_factor = 1.5;
    const auto first = motor_current::calculate(input, 113.8);
    const auto optimal = motor_current::calculateOptimal(input);
    CHECK(motor_current::calculate(overloaded, 113.8).current ==
          motor_current::calculate(capped, 113.8).current);
    CHECK(motor_current::calculateOptimal(overloaded) == motor_current::calculateOptimal(capped));
    CHECK(overloaded.load_factor == 2);
    CHECK(motor_current::calculate(input, 227.6).current == Approx(first.current * 2).epsilon(1e-12).margin(1e-9));
    CHECK(motor_current::calculate(input, 0).current == 0);
    CHECK(motor_current::calculate(input, 227.6).estimated_fla == first.estimated_fla);
    CHECK(motor_current::calculate(input, 113.8).current == first.current);
    CHECK(motor_current::calculateOptimal(input) == optimal);
    CHECK(input.load_factor == 0.25);
    CHECK(first.estimated_fla != 113.8);
}
