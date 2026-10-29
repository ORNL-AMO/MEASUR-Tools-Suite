#include "motorDriven/motor/optimal_motor_power.h"

#include <array>
#include <cmath>
#include <limits>

#include "catch.hpp"

namespace {

std::array<double, 5> values(const optimal_motor_power::Result& result) {
    return {result.power, result.efficiency, result.current, result.power_factor, result.load_factor};
}

optimal_motor_power::Input input() {
    return {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93, 460, 460, 75};
}

} // namespace

TEST_CASE("Optimal motor power preserves captured legacy operating points", "[optimal_motor_power]") {
    struct Golden {
        const char* label;
        optimal_motor_power::Input input;
        optimal_motor_power::Result expected;
    };
    // Captured from unchanged OptimalMotorPower.cpp at 80c6475 with freshly rebuilt native dependencies.
    // Threshold targets include exact model doubles and their immediate floating-point neighbors.
    const Golden goldens[] = {
        {"model-0", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD,
            0.93000000000000005, 460, 440, 5}, {6.0059541909542782, 0.6210503579294443, 33.733173985266198, 0.23362079919004058, 0.049999999999999996}},
        {"model-1", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD,
            0.93000000000000005, 460, 440, 75}, {60.282431074268679, 0.9281311155329639, 91.511874791208029, 0.86437062968212619, 0.75}},
        {"model-2", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD,
            0.93000000000000005, 460, 440, 100}, {80.266917705459079, 0.92939908660434745, 121.63052813530595, 0.86592582049937505, 0.99999999999999989}},
        {"model-3", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD,
            0.93000000000000005, 460, 440, 125}, {101.34711831497381, 0.92010509573830201, 155.32978633679519, 0.85613717609647233, 1.25}},
        {"model-4", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD,
            0.93000000000000005, 460, 440, 200}, {172.56151378609243, 0.85039775386798655, 271.28270027548871, 0.83465795790782005, 1.999999999999984}},
        {"model-5", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 5}, {5.0641798011607424, 0.73654572832209875, 35.626785902996154, 0.17097421091310899, 0.049999999999999996}},
        {"model-6", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 75}, {58.830708511102877, 0.95103393135985748, 85.566923791707794, 0.82698245347952171, 0.75000000000000011}},
        {"model-7", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 100}, {78.574810572051476, 0.9494136792298512, 108.88494648139289, 0.86798782991569101, 0.99999999999999989}},
        {"model-8", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 125}, {99.210619409153097, 0.93991954243757936, 133.11927104712686, 0.89642790151926444, 1.25}},
        {"model-9", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 200}, {167.24405672124848, 0.88025654879788018, 208.79067758890221, 0.96346895412415801, 2.0000000000000031}},
        {"model-10", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 460, 440, 5}, {4.9926574893293765, 0.7470971137058755, 32.747532503103606, 0.20005061347076861, 0.050000000000000003}},
        {"model-11", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 460, 440, 75}, {58.414765252906477, 0.95780578348239032, 88.838011372826003, 0.86280072936443097, 0.75000000000000011}},
        {"model-12", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 460, 440, 100}, {78.194807486161096, 0.95402754221503383, 118.07663504242322, 0.86896171547528989, 0.99999999999999989}},
        {"model-13", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 460, 440, 125}, {98.730817533034724, 0.94448726679285444, 150.79124273885458, 0.85913875254811556, 1.2499999999999998}},
        {"model-14", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 460, 440, 200}, {165.21946293185948, 0.89304878527378651, 263.35615642578904, 0.8231982282237752, 2.000000000000032}},
        {"model-15", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED,
            0.93000000000000005, 460, 480, 5}, {5.9943611150214142, 0.62225146740874571, 36.480672318907786, 0.19764152856998474, 0.050000000000000003}},
        {"model-16", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED,
            0.93000000000000005, 460, 480, 75}, {60.243479977110312, 0.92873120910774687, 87.617752459667273, 0.82702012447276174, 0.75000000000000011}},
        {"model-17", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED,
            0.93000000000000005, 460, 480, 100}, {81.025306831760062, 0.92069999999998142, 111.49465079069711, 0.87410738203459915, 0.99999999999999967}},
        {"model-18", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED,
            0.93000000000000005, 460, 480, 125}, {101.28163353969761, 0.92070000000000429, 136.30981249963665, 0.89372048429909923, 1.2500000000000002}},
        {"model-19", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED,
            0.93000000000000005, 460, 480, 200}, {157.58421240938009, 0.95250358806650381, 213.79487650396422, 0.88657105335363917, 1.9999999999999933}},
        {"model-20", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::STANDARD,
            0.93000000000000005, 460, 440, 5}, {6.0059541909542782, 0.6210503579294443, 33.733173985266198, 0.23362079919004058, 0.049999999999999996}},
        {"model-21", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::STANDARD,
            0.93000000000000005, 460, 440, 75}, {60.282431074268679, 0.9281311155329639, 91.511874791208029, 0.86437062968212619, 0.75}},
        {"model-22", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::STANDARD,
            0.93000000000000005, 460, 440, 100}, {80.266917705459079, 0.92939908660434745, 121.63052813530595, 0.86592582049937505, 0.99999999999999989}},
        {"model-23", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::STANDARD,
            0.93000000000000005, 460, 440, 125}, {101.34711831497381, 0.92010509573830201, 155.32978633679519, 0.85613717609647233, 1.25}},
        {"model-24", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::STANDARD,
            0.93000000000000005, 460, 440, 200}, {172.56151378609243, 0.85039775386798655, 271.28270027548871, 0.83465795790782005, 1.999999999999984}},
        {"model-25", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 5}, {5.0641798011607424, 0.73654572832209875, 35.626785902996154, 0.17097421091310899, 0.049999999999999996}},
        {"model-26", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 75}, {58.830708511102877, 0.95103393135985748, 85.566923791707794, 0.82698245347952171, 0.75000000000000011}},
        {"model-27", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 100}, {78.574810572051476, 0.9494136792298512, 108.88494648139289, 0.86798782991569101, 0.99999999999999989}},
        {"model-28", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 125}, {99.210619409153097, 0.93991954243757936, 133.11927104712686, 0.89642790151926444, 1.25}},
        {"model-29", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 200}, {167.24405672124848, 0.88025654879788018, 208.79067758890221, 0.96346895412415801, 2.0000000000000031}},
        {"model-30", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 460, 440, 5}, {4.9926574893293765, 0.7470971137058755, 32.747532503103606, 0.20005061347076861, 0.050000000000000003}},
        {"model-31", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 460, 440, 75}, {58.414765252906477, 0.95780578348239032, 88.838011372826003, 0.86280072936443097, 0.75000000000000011}},
        {"model-32", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 460, 440, 100}, {78.194807486161096, 0.95402754221503383, 118.07663504242322, 0.86896171547528989, 0.99999999999999989}},
        {"model-33", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 460, 440, 125}, {98.730817533034724, 0.94448726679285444, 150.79124273885458, 0.85913875254811556, 1.2499999999999998}},
        {"model-34", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 460, 440, 200}, {165.21946293185948, 0.89304878527378651, 263.35615642578904, 0.8231982282237752, 2.000000000000032}},
        {"model-35", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::SPECIFIED,
            0.93000000000000005, 460, 480, 5}, {5.9943611150214142, 0.62225146740874571, 36.480672318907786, 0.19764152856998474, 0.050000000000000003}},
        {"model-36", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::SPECIFIED,
            0.93000000000000005, 460, 480, 75}, {60.243479977110312, 0.92873120910774687, 87.617752459667273, 0.82702012447276174, 0.75000000000000011}},
        {"model-37", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::SPECIFIED,
            0.93000000000000005, 460, 480, 100}, {81.025306831760062, 0.92069999999998142, 111.49465079069711, 0.87410738203459915, 0.99999999999999967}},
        {"model-38", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::SPECIFIED,
            0.93000000000000005, 460, 480, 125}, {101.28163353969761, 0.92070000000000429, 136.30981249963665, 0.89372048429909923, 1.2500000000000002}},
        {"model-39", {100, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::SPECIFIED,
            0.93000000000000005, 460, 480, 200}, {157.58421240938009, 0.95250358806650381, 213.79487650396422, 0.88657105335363917, 1.9999999999999933}},
        {"example-40", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 460, 75}, {58.830708511102877, 0.95103393135985748, 87.468410987079082, 0.84417868597153456, 0.75000000000000011}},
        {"small-two-pole-41", {5, 3550, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 230, 220, 3}, {2.513519553474683, 0.89038495718332278, 7.7409335478548149, 0.85212953958021043, 0.59999999999999998}},
        {"large-six-pole-42", {600, 1180, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 575, 600, 590}, {458.66090461341133, 0.95961979644175188, 511.43671665024669, 0.86295458826825888, 0.98333333333333339}},
        {"50hz-six-pole-43", {50, 980, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::PREMIUM,
            0.93000000000000005, 400, 380, 25}, {19.814325573885945, 0.94123819306671452, 40.067048645802565, 0.75135938846585648, 0.5}},
        {"zero-target-44", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 460, 0}, {1.2706474296768975, 0, 33.330823927033883, 0.047847643525498577, 0}},
        {"negative-target-45", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 460, -1}, {-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN(), -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN(), -std::numeric_limits<double>::infinity()}},
        {"zero-field-voltage-46", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 0, 75}, {std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()}},
        {"zero-rated-voltage-47", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 0, 460, 75}, {std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()}},
        {"threshold-48", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 1}, {2.0293539039736666, 0.36760468370709593, 34.911324020552492, 0.069918098187046376, 0.0099999999999999985}},
        {"threshold-49", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 1.0000000000000002}, {2.0293539039736666, 0.36760468370709598, 34.911324020552492, 0.069918098187046376, 0.01}},
        {"threshold-50", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 1.0000000000000004}, {2.029353903973667, 0.36760468370709604, 34.911324020552492, 0.06991809818704639, 0.010000000000000004}},
        {"threshold-51", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 25.000000000000011}, {20.238309287096129, 0.92151966527614926, 43.670328546049078, 0.55742430958808764, 0.25000000000000006}},
        {"threshold-52", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 25.000000000000014}, {20.238309287096129, 0.92151966527614926, 43.670328546049078, 0.55742430958808764, 0.25000000000000006}},
        {"threshold-53", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 25.000000000000018}, {20.238309287096133, 0.92151966527614926, 43.670328546049085, 0.55742430958808764, 0.25000000000000011}},
        {"threshold-54", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 25.999999999999996}, {21.010212443805901, 0.92317010367585339, 44.440392662340145, 0.56865739530817039, 0.26000000000000001}},
        {"threshold-55", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 26}, {21.010212443805905, 0.92317010367585339, 44.440392662340152, 0.56865739530817039, 0.26000000000000006}},
        {"threshold-56", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 26.000000000000004}, {21.010212443805905, 0.92317010367585339, 44.440392662340152, 0.56865739530817039, 0.26000000000000006}},
        {"threshold-57", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 100.00000000000006}, {78.574810572051518, 0.9494136792298512, 108.88494648139293, 0.86798782991569112, 1.0000000000000004}},
        {"threshold-58", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 100.00000000000007}, {78.574810572051533, 0.9494136792298512, 108.88494648139296, 0.86798782991569101, 1.0000000000000007}},
        {"threshold-59", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 100.00000000000009}, {78.574810572051547, 0.9494136792298512, 108.88494648139297, 0.86798782991569112, 1.0000000000000009}},
        {"threshold-60", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 125.00000000000009}, {99.210619409153153, 0.93991954243757925, 133.11927104712692, 0.89642790151926455, 1.2500000000000007}},
        {"threshold-61", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 125.0000000000001}, {99.210619409153168, 0.93991954243757925, 133.11927104712694, 0.89642790151926455, 1.2500000000000009}},
        {"threshold-62", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 125.00000000000011}, {99.210619409153182, 0.93991954243757925, 133.11927104712697, 0.89642790151926444, 1.2500000000000011}},
        {"threshold-63", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 126.00000000000007}, {100.06216891159545, 0.93937600016490908, 134.10566771162084, 0.89747201377668628, 1.2600000000000007}},
        {"threshold-64", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 126.00000000000009}, {100.06216891159546, 0.93937600016490908, 134.10566771162087, 0.89747201377668617, 1.2600000000000009}},
        {"threshold-65", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 126.0000000000001}, {100.06216891159548, 0.93937600016490908, 134.1056677116209, 0.89747201377668628, 1.2600000000000011}},
        {"threshold-66", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 150.00000000000009}, {121.29403882048062, 0.92255152098295556, 158.12599214696183, 0.92264435537128153, 1.5000000000000007}},
        {"threshold-67", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 150.00000000000011}, {121.29403882048067, 0.92255152098295556, 158.12599214696192, 0.92264435537128142, 1.5000000000000011}},
        {"threshold-68", {100, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93000000000000005, 460, 480, 150.00000000000014}, {121.29403882048068, 0.92255152098295556, 158.12599214696192, 0.92264435537128153, 1.5000000000000013}},
    };
    for (const auto& golden : goldens) {
        INFO(golden.label);
        const auto actual = values(optimal_motor_power::calculate(golden.input));
        const auto expected = values(golden.expected);
        for (std::size_t i = 0; i < actual.size(); ++i) {
            INFO("result member " << i);
            if (std::isnan(expected[i])) {
                CHECK(std::isnan(actual[i]));
            } else if (std::isinf(expected[i])) {
                CHECK(actual[i] == expected[i]);
            } else {
                CHECK(actual[i] == Catch::Approx(expected[i]).epsilon(1e-11).margin(1e-9));
            }
        }
    }
}

TEST_CASE("Optimal motor power is stateless and preserves input data", "[optimal_motor_power]") {
    auto data = input();
    const auto first = values(optimal_motor_power::calculate(data));
    auto other = data;
    other.field_voltage = 480;
    other.optimal_motor_shaft_power = 120;
    optimal_motor_power::calculate(other);
    CHECK(values(optimal_motor_power::calculate(data)) == first);
    CHECK(data.motor_rated_power == 100);
    CHECK(data.motor_rpm == 1780);
    CHECK(data.line_frequency == Motor::LineFrequency::FREQ60);
    CHECK(data.efficiency_class == Motor::EfficiencyClass::ENERGY_EFFICIENT);
    CHECK(data.specified_efficiency == 0.93);
    CHECK(data.rated_voltage == 460);
    CHECK(data.field_voltage == 460);
    CHECK(data.optimal_motor_shaft_power == 75);
    // The specified value is inactive for modeled efficiency classes.
    data.specified_efficiency = -1;
    CHECK(values(optimal_motor_power::calculate(data)) == first);
}

TEST_CASE("Optimal motor power propagates specified-efficiency dependency errors", "[optimal_motor_power]") {
    auto data = input();
    data.efficiency_class = Motor::EfficiencyClass::SPECIFIED;
    data.specified_efficiency = -1;
    CHECK_THROWS_WITH(optimal_motor_power::calculate(data),
                      "An efficiency must be specified if EfficiencyClass::SPECIFIED is used");
}
