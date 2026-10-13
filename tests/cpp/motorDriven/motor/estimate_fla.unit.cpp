#include "motorDriven/motor/estimate_fla.h"

#include <array>

#include "catch.hpp"

using namespace Catch;

namespace {

estimate_fla::Result calculate(const double motor_rated_power, const double motor_rpm,
                               const Motor::LineFrequency line_frequency,
                               const Motor::EfficiencyClass efficiency_class, const double specified_efficiency,
                               const double rated_voltage) {
    return estimate_fla::calculate(
        {motor_rated_power, motor_rpm, line_frequency, efficiency_class, specified_efficiency, rated_voltage});
}

} // namespace

TEST_CASE("Estimate full-load motor current", "[estimate_fla][EstimateFLA]") {
    auto unitTestNumber = 0;
    const std::array<std::array<double, 6>, 9> expected = {
        {{{18.8775576, 23.6212730421, 34.0613092325, 46.5048449789, 60.381474681, 75.5372248259}},
         {{48.6495840124, 63.249248253, 96.1954123714, 132.4400532659, 172.6294043084, 215.9593847898}},
         {{49.55811480809, 56.11300070569, 78.49438625307, 102.84658002297, 129.16907799852, 159.7821494841}},
         {{28.6566235624, 39.6191308792, 61.8010643593, 86.8044256422, 113.8781958, 142.6893793376}},
         {{53.3464740091, 75.2070177891, 119.291789, 167.65708225, 219.981424828, 275.6367253}},
         {{66.1147879039, 93.2122073949, 148.887425814, 209.314953096, 274.6608259936, 344.15001497}},
         {{66.1147879039, 93.2122073949, 148.887425814, 209.314953096, 274.6608259936, 344.15001497}},
         {{88.3024614572, 116.2594022102, 179.8542042707, 249.6685871227, 326.1945449939, 408.0693757874}},
         {{494.2117767987, 618.953071161, 849.5097896611, 1130.1225205859, 1439.4257134111, 1780.5696074895}}}};

    const auto compare = [&unitTestNumber, &expected](const estimate_fla::Result& result) {
        const std::array<double, 6>& results = result.partial_load_currents;
        for (std::size_t i = 0; i < results.size(); ++i) {
            INFO("index is " + std::to_string(i) + " and the unit test number is " +
                 std::to_string(unitTestNumber));
            CHECK(expected.at(unitTestNumber).at(i) == Approx(results[i]));
        }
        ++unitTestNumber;
    };

    compare(calculate(50, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100));
    compare(calculate(150, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100));
    compare(calculate(100, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100));
    compare(calculate(100, 2900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100));
    compare(calculate(200, 2200, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .965, 100));
    compare(calculate(250, 2800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .985, 110));
    compare(calculate(250, 2800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 98.5, 110));
    compare(calculate(290, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 93.5, 110));
    compare(calculate(1200, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 65.5, 210));

    CHECK(calculate(50, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).estimated_fla ==
          Approx(277.7547835326));
    CHECK(calculate(150, 2400, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 110).estimated_fla ==
          Approx(707.6948056564));
    CHECK(calculate(75, 2000, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 110).estimated_fla ==
          Approx(348.9439377969));
    CHECK(calculate(175, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 220).estimated_fla ==
          Approx(460.3700518143));
    CHECK(calculate(100, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .80, 220).estimated_fla ==
          Approx(312.5479443728));
    CHECK(calculate(125, 1900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .90, 220).estimated_fla ==
          Approx(302.2156478756));
    CHECK(calculate(90, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .95, 120).estimated_fla ==
          Approx(432.5925070407));
    CHECK(calculate(150, 2900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .55, 600).estimated_fla ==
          Approx(218.1935995715));
    CHECK(calculate(200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .94, 460).estimated_fla ==
          Approx(228.3902237064));
    CHECK(calculate(200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .95, 460).estimated_fla ==
          Approx(227.288340026));
}

TEST_CASE("Estimate premium full-load current and ordered anchors", "[estimate_fla]") {
    // Captured from the legacy EstimateFLA implementation at the PR base e6d6df7.
    // Exercise each supported premium pole column at 200 hp and 230 V.
    const std::array<double, 3> motor_rpms = {{3600, 1780, 1200}};
    const std::array<double, 3> expected_fla = {{435.49337497165698, 448.07625635540739, 467.38842500147217}};
    const std::array<std::array<double, 6>, 3> expected_anchors = {{
        {{52.804540263371869, 74.443008140618474, 118.07993301142717, 165.95389507103832,
          217.74668748582849, 272.8365994197431}},
        {{61.767914923517779, 80.892507178588289, 124.30911651250761, 171.6912306970269,
          224.0381281777037, 280.2716983503073}},
        {{77.606732740709717, 94.116538455169888, 132.97868398283219, 179.88325053357315,
          233.69421250073609, 293.05254247592308}},
    }};

    for (std::size_t pole_index = 0; pole_index < motor_rpms.size(); ++pole_index) {
        INFO("premium pole count: " << 2 * (pole_index + 1));
        const auto result = calculate(200, motor_rpms[pole_index], Motor::LineFrequency::FREQ60,
                                      Motor::EfficiencyClass::PREMIUM, 0, 230);
        CHECK(result.estimated_fla == Approx(expected_fla[pole_index]).margin(1e-9));
        for (std::size_t interval = 0; interval < result.partial_load_currents.size(); ++interval) {
            INFO("interval index: " << interval);
            CHECK(result.partial_load_currents[interval] == Approx(expected_anchors[pole_index][interval]).margin(1e-9));
        }
    }
}
