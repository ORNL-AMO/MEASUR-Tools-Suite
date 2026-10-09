#include "motorDriven/motor/EstimateFLA.h"

#include <array>

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Estimate full-load motor current", "[EstimateFLA]") {
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

    const auto compare = [&unitTestNumber, &expected](const std::array<double, 6>& results) {
        for (std::size_t i = 0; i < results.size(); ++i) {
            INFO("index is " + std::to_string(i) + " and the unit test number is " +
                 std::to_string(unitTestNumber));
            CHECK(expected.at(unitTestNumber).at(i) == Approx(results[i]));
        }
        ++unitTestNumber;
    };

    compare(EstimateFLA(50, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
    compare(EstimateFLA(150, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
    compare(EstimateFLA(100, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
    compare(EstimateFLA(100, 2900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
    compare(EstimateFLA(200, 2200, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .965, 100).calculate());
    compare(EstimateFLA(250, 2800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .985, 110).calculate());
    compare(EstimateFLA(250, 2800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 98.5, 110).calculate());
    compare(EstimateFLA(290, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 93.5, 110).calculate());
    compare(EstimateFLA(1200, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 65.5, 210).calculate());

    auto estimate = EstimateFLA(50, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100);
    estimate.calculate();
    CHECK(estimate.getEstimatedFLA() == Approx(277.7547835326));

    estimate = EstimateFLA(150, 2400, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 110);
    estimate.calculate();
    CHECK(estimate.getEstimatedFLA() == Approx(707.6948056564));

    estimate = EstimateFLA(75, 2000, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 110);
    estimate.calculate();
    CHECK(estimate.getEstimatedFLA() == Approx(348.9439377969));

    estimate = EstimateFLA(175, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 220);
    estimate.calculate();
    CHECK(estimate.getEstimatedFLA() == Approx(460.3700518143));

    estimate = EstimateFLA(100, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .80, 220);
    estimate.calculate();
    CHECK(estimate.getEstimatedFLA() == Approx(312.5479443728));

    estimate = EstimateFLA(125, 1900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .90, 220);
    estimate.calculate();
    CHECK(estimate.getEstimatedFLA() == Approx(302.2156478756));

    estimate = EstimateFLA(90, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .95, 120);
    estimate.calculate();
    CHECK(estimate.getEstimatedFLA() == Approx(432.5925070407));

    estimate = EstimateFLA(150, 2900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .55, 600);
    estimate.calculate();
    CHECK(estimate.getEstimatedFLA() == Approx(218.1935995715));

    estimate = EstimateFLA(200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .94, 460);
    estimate.calculate();
    CHECK(estimate.getEstimatedFLA() == Approx(228.3902237064));

    estimate = EstimateFLA(200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .95, 460);
    estimate.calculate();
    CHECK(estimate.getEstimatedFLA() == Approx(227.288340026));
}
