#include "motorDriven/motor/motor_efficiency.h"

#include <array>

#include "catch.hpp"

using namespace Catch;

namespace {

class MotorEfficiencyHarness {
  public:
    MotorEfficiencyHarness(const Motor::LineFrequency line_frequency, const double motor_rpm,
                           const Motor::EfficiencyClass efficiency_class, const double motor_rated_power)
        : line_frequency_(line_frequency), motor_rpm_(motor_rpm), efficiency_class_(efficiency_class),
          motor_rated_power_(motor_rated_power) {}

    double calculate(const double load_factor, const double specified_efficiency = -1.0) const {
        return motor_efficiency::calculate(
                   {line_frequency_, motor_rpm_, efficiency_class_, motor_rated_power_, load_factor,
                    specified_efficiency})
            .efficiency;
    }

    std::array<double, 5> calculate25intervals() const {
        return {{calculate(0.25), calculate(0.50), calculate(0.75), calculate(1.00), calculate(1.25)}};
    }

  private:
    Motor::LineFrequency line_frequency_;
    double motor_rpm_;
    Motor::EfficiencyClass efficiency_class_;
    double motor_rated_power_;
};

} // namespace

TEST_CASE("Calculate Motor Efficiency - 200 HP", "[MotorEfficiency]") {
    MotorEfficiencyHarness motorEff(Motor::LineFrequency::FREQ60, 1785,
                                     Motor::EfficiencyClass::ENERGY_EFFICIENT, 200);
    CHECK(motorEff.calculate(0) == Approx(0.0));
    CHECK(motorEff.calculate(0.25) == Approx(0.930393384));
    CHECK(motorEff.calculate(0.5) == Approx(0.949504131));
    CHECK(motorEff.calculate(0.75) == Approx(0.9569034));
    CHECK(motorEff.calculate(1) == Approx(0.956259245));
    CHECK(motorEff.calculate(1.25) == Approx(0.946696653));
}

TEST_CASE("Calculate Motor Efficiency - 100 HP", "[MotorEfficiency]") {
    MotorEfficiencyHarness motorEff(Motor::LineFrequency::FREQ60, 1785,
                                     Motor::EfficiencyClass::ENERGY_EFFICIENT, 100);
    CHECK(motorEff.calculate(0) == Approx(0.0));
    CHECK(motorEff.calculate(0.25) == Approx(0.921519665));
    CHECK(motorEff.calculate(0.5) == Approx(0.946047805));
    CHECK(motorEff.calculate(0.75) == Approx(0.951033931));
    CHECK(motorEff.calculate(1) == Approx(0.949413679));
    CHECK(motorEff.calculate(1.25) == Approx(0.939919542));
}

TEST_CASE("Calculate Motor Efficiencies", "[MotorEfficiency]") {
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1785, Motor::EfficiencyClass::ENERGY_EFFICIENT, 100)
              .calculate(0.5) == Approx(0.9460478053));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1985, Motor::EfficiencyClass::ENERGY_EFFICIENT, 100)
              .calculate(0.5) == Approx(0.936657639));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 2285, Motor::EfficiencyClass::ENERGY_EFFICIENT, 110)
              .calculate(0.5) == Approx(0.9382004043));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 2585, Motor::EfficiencyClass::ENERGY_EFFICIENT, 120)
              .calculate(0.5) == Approx(0.9395868071));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 2885, Motor::EfficiencyClass::ENERGY_EFFICIENT, 150)
              .calculate(0.5) == Approx(0.9404486692));

    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1285, Motor::EfficiencyClass::STANDARD, 100).calculate(0.5) ==
          Approx(0.9184557213));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::STANDARD, 120).calculate(0.5) ==
          Approx(0.9213249265));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::STANDARD, 150).calculate(0.1) ==
          Approx(0.780716097));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::STANDARD, 150).calculate(0.9) ==
          Approx(0.9350877877));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::STANDARD, 150).calculate(0.2) ==
          Approx(0.8671487126));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::STANDARD, 150).calculate(0.25) ==
          Approx(0.8867837736));

    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(0.25, .25) == Approx(0.2371623657));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(0.25, .35) == Approx(0.332027312));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(0.25, .55) == Approx(0.5217572046));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(0.25, .75) == Approx(0.7114870972));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(0.25, .85) == Approx(0.8063520435));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(0.25, .95) == Approx(0.9226247725));

    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(0.05, .25) == Approx(0.0689209016));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(0.15, .35) == Approx(0.2448123855));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(0.35, .55) == Approx(0.53252116));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(0.55, .85) == Approx(0.8441439051));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(0.75, .95) == Approx(0.95082302895));
    CHECK(
        MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150).calculate(1, .95) ==
        Approx(0.95));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(1.25, .95) == Approx(0.9405));
    CHECK(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1600, Motor::EfficiencyClass::SPECIFIED, 150)
              .calculate(1.5, .95) == Approx(0.9223230289));
}

TEST_CASE("Calculate Motor25 Efficiencies", "[MotorEfficiency25]") {
    const std::vector<std::vector<double>> expected {
        // ENERGY_EFFICIENT
        {0.9215196653, 0.9460478053, 0.9510339314, 0.9494136792, 0.9399195424},
        {0.9241840076, 0.9475057386, 0.9529291531, 0.9518554564, 0.9423369019},
        {0.9353383999, 0.9516372151, 0.9584322705, 0.9578040944, 0.9482260535},
        {0.9045636369, 0.9366576390, 0.9445673713, 0.9436768567, 0.9342400881},
        {0.9045636369, 0.9366576390, 0.9445673713, 0.9436768567, 0.9342400881},

        // STANDARD
        {0.8509115247, 0.9036358682, 0.9142885586, 0.9138935683, 0.9047546326},
        {0.8731490357, 0.9184557213, 0.9281311155, 0.9293990866, 0.9201050957},
        {0.8867837736, 0.9242760124, 0.9338556716, 0.9347855116, 0.9254376565},
        {0.9071879002, 0.9326659464, 0.9416871700, 0.9424751293, 0.933050378},
        {0.8476517473, 0.9070133723, 0.9196222911, 0.9189355966, 0.9097462406},
    };

    std::size_t unitTestNumber = 0;
    auto const  compare        = [&unitTestNumber, &expected](const std::array<double, 5>& results) {
        INFO("Unit test Number " + std::to_string(unitTestNumber));
        CHECK(expected.at(unitTestNumber).at(0) == Approx(results.at(0)));
        CHECK(expected.at(unitTestNumber).at(1) == Approx(results.at(1)));
        CHECK(expected.at(unitTestNumber).at(2) == Approx(results.at(2)));
        CHECK(expected.at(unitTestNumber).at(3) == Approx(results.at(3)));
        CHECK(expected.at(unitTestNumber).at(4) == Approx(results.at(4)));
        unitTestNumber++;
    };

    compare(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT, 100)
                .calculate25intervals());
    compare(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT, 120)
                .calculate25intervals());
    compare(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT, 290)
                .calculate25intervals());
    compare(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 2400, Motor::EfficiencyClass::ENERGY_EFFICIENT, 100)
                .calculate25intervals());
    compare(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 3880, Motor::EfficiencyClass::ENERGY_EFFICIENT, 100)
                .calculate25intervals());

    compare(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::STANDARD, 50)
                .calculate25intervals());
    compare(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::STANDARD, 100)
                .calculate25intervals());
    compare(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::STANDARD, 150)
                .calculate25intervals());
    compare(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::STANDARD, 250)
                .calculate25intervals());
    compare(MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 3200, Motor::EfficiencyClass::STANDARD, 125)
                .calculate25intervals());
}

TEST_CASE("MotorEfficiency25 Premium", "[MotorEfficiency][PREMIUM]") {
    auto results = MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::PREMIUM, 200)
                       .calculate25intervals();
    CHECK(results[0] == Approx(0.9351618364));
    CHECK(results[1] == Approx(0.9635434578));
    CHECK(results[2] == Approx(0.9645106139));
    CHECK(results[3] == Approx(0.9612112999));
    CHECK(results[4] == Approx(0.9515991869));

    results = MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::PREMIUM, 7.5)
                  .calculate25intervals();
    CHECK(results[0] == Approx(0.8630684058));
    CHECK(results[1] == Approx(0.9145841785));
    CHECK(results[2] == Approx(0.921334108));
    CHECK(results[3] == Approx(0.9153351555));
    CHECK(results[4] == Approx(0.9061818039));

    results =
        MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::PREMIUM, 10).calculate25intervals();
    CHECK(results[0] == Approx(0.8716755415));
    CHECK(results[1] == Approx(0.9191159795));
    CHECK(results[2] == Approx(0.924712152));
    CHECK(results[3] == Approx(0.9187215894));
    CHECK(results[4] == Approx(0.9095343735));

    results = MotorEfficiencyHarness(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::PREMIUM, 8.75)
                  .calculate25intervals();
    CHECK(results[0] == Approx(0.867531194));
    CHECK(results[1] == Approx(0.9173686836));
    CHECK(results[2] == Approx(0.9233015806));
    CHECK(results[3] == Approx(0.9170659857));
    CHECK(results[4] == Approx(0.9078953258));
}

TEST_CASE("Motor efficiency stateless contract", "[motor_efficiency]") {
    const motor_efficiency::Input input {
        Motor::LineFrequency::FREQ60,
        1785,
        Motor::EfficiencyClass::ENERGY_EFFICIENT,
        200,
        0.25,
        -1,
    };
    const motor_efficiency::Result result = motor_efficiency::calculate(input);
    const double expected_zero_load_loss = ((1 / result.efficiency) - 1) * 200 * 0.746 * 0.25 * 0.8;

    CHECK(result.efficiency == Approx(0.930393384));
    CHECK(result.zero_load_power_loss == Approx(expected_zero_load_loss));
    CHECK(motor_efficiency::calculate({Motor::LineFrequency::FREQ60, 1785,
                                       Motor::EfficiencyClass::ENERGY_EFFICIENT, 200, 0.2509})
              .efficiency == Approx(0.93057926520254541));
    CHECK(motor_efficiency::calculate({Motor::LineFrequency::FREQ60, 1785,
                                       Motor::EfficiencyClass::ENERGY_EFFICIENT, 200, 0.251})
              .efficiency == Approx(0.930502527405909));
    CHECK(motor_efficiency::calculate({Motor::LineFrequency::FREQ60, 1785,
                                       Motor::EfficiencyClass::ENERGY_EFFICIENT, 200, 1.2509})
              .efficiency == Approx(0.94664094482320715));
    CHECK(motor_efficiency::calculate({Motor::LineFrequency::FREQ60, 1785,
                                       Motor::EfficiencyClass::ENERGY_EFFICIENT, 200, 1.251})
              .efficiency == Approx(0.94664049403956907));
    CHECK(motor_efficiency::calculate(
              {Motor::LineFrequency::FREQ60, 1785, Motor::EfficiencyClass::ENERGY_EFFICIENT, 200, 2.0})
              .efficiency ==
          Approx(motor_efficiency::calculate(
                     {Motor::LineFrequency::FREQ60, 1785, Motor::EfficiencyClass::ENERGY_EFFICIENT, 200, 1.5})
                     .efficiency));
    CHECK_THROWS_AS(motor_efficiency::calculate(
                        {Motor::LineFrequency::FREQ60, 1785, Motor::EfficiencyClass::SPECIFIED, 200, 1.0}),
                    std::runtime_error);
}

TEST_CASE("Motor efficiency pole selection", "[motor_efficiency][poles]") {
    const std::array<std::array<double, 2>, 6> equivalent_speeds {{
        {{2850, 3420}},
        {{1425, 1710}},
        {{950, 1140}},
        {{710, 855}},
        {{570, 684}},
        {{475, 570}},
    }};

    for (const auto& speeds : equivalent_speeds) {
        const double efficiency_50_hz =
            motor_efficiency::calculate({Motor::LineFrequency::FREQ50, speeds[0],
                                         Motor::EfficiencyClass::ENERGY_EFFICIENT, 100, 1})
                .efficiency;
        const double efficiency_60_hz =
            motor_efficiency::calculate({Motor::LineFrequency::FREQ60, speeds[1],
                                         Motor::EfficiencyClass::ENERGY_EFFICIENT, 100, 1})
                .efficiency;

        CHECK(efficiency_50_hz == Approx(efficiency_60_hz));
    }

    const double premium_six_pole =
        motor_efficiency::calculate(
            {Motor::LineFrequency::FREQ60, 1140, Motor::EfficiencyClass::PREMIUM, 200, 1})
            .efficiency;
    for (const double capped_speed : {855.0, 684.0, 570.0}) {
        CHECK(motor_efficiency::calculate(
                  {Motor::LineFrequency::FREQ60, capped_speed, Motor::EfficiencyClass::PREMIUM, 200, 1})
                  .efficiency == Approx(premium_six_pole));
    }
}
