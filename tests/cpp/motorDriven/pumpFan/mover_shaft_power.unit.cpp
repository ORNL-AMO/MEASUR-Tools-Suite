#include "motorDriven/pumpFan/mover_shaft_power.h"

#include <cmath>
#include <iterator>
#include <limits>

#include "catch.hpp"

namespace {

void checkNumber(double actual, double expected) {
    if (std::isnan(expected)) {
        CHECK(std::isnan(actual));
    } else if (expected == 0 || std::isinf(expected)) {
        CHECK(actual == expected);
        CHECK(std::signbit(actual) == std::signbit(expected));
    } else {
        CHECK(actual == Catch::Approx(expected).epsilon(1e-12));
    }
}

struct Fixture {
    mover_shaft_power::Input input;
    double power;
    double efficiency;
};

void checkFixtures(const Fixture* begin, const Fixture* end) {
    for (auto fixture = begin; fixture != end; ++fixture) {
        CAPTURE(fixture->input.motor_shaft_power, static_cast<int>(fixture->input.drive),
            fixture->input.specified_efficiency);
        const auto result = mover_shaft_power::calculate(fixture->input);
        checkNumber(result.mover_shaft_power, fixture->power);
        checkNumber(result.drive_efficiency, fixture->efficiency);
    }
}

} // namespace

// Captured at -O3 from unchanged MoverShaftPower at base 2a20eed before class removal.
TEST_CASE("Mover shaft power preserves captured duties and both outputs", "[mover_shaft_power]") {
    const Fixture fixtures[] = {
        {{50, Motor::Drive::V_BELT_DRIVE, 0}, 47.874006161154519, 0.95748012322309028},
        {{100, Motor::Drive::V_BELT_DRIVE, 0}, 95.908679491417715, 0.95908679491417725},
        {{150, Motor::Drive::V_BELT_DRIVE, 0}, 143.95256505385677, 0.9596837670257119},
        {{200, Motor::Drive::V_BELT_DRIVE, 0}, 191.98113755661001, 0.95990568778304997},
        {{250, Motor::Drive::V_BELT_DRIVE, 0}, 239.9970463698356, 0.95998818547934239},
        {{0.001, Motor::Drive::V_BELT_DRIVE, 0}, 0.00091561131281008804, 0.91561131281008801},
        {{1, Motor::Drive::V_BELT_DRIVE, 0}, 0.92300588014910112, 0.92300588014910112},
        {{10, Motor::Drive::V_BELT_DRIVE, 0}, 9.5002386060280521, 0.95002386060280508},
        {{600, Motor::Drive::V_BELT_DRIVE, 0}, 576.02217126524181, 0.9600369521087363},
        {{-50, Motor::Drive::V_BELT_DRIVE, 0}, 87826.47322736535, -1756.529464547307},
        {{50, Motor::Drive::N_V_BELT_DRIVE, 0}, 48.481432972253224, 0.96962865944506449},
        {{100, Motor::Drive::N_V_BELT_DRIVE, 0}, 97.077628208155517, 0.9707762820815552},
        {{150, Motor::Drive::N_V_BELT_DRIVE, 0}, 145.6804036098977, 0.97120269073265131},
        {{200, Motor::Drive::N_V_BELT_DRIVE, 0}, 194.27224111186428, 0.97136120555932148},
        {{250, Motor::Drive::N_V_BELT_DRIVE, 0}, 242.85503312131115, 0.97142013248524461},
        {{0.001, Motor::Drive::N_V_BELT_DRIVE, 0}, 0.00093972236629291997, 0.93972236629291994},
        {{1, Motor::Drive::N_V_BELT_DRIVE, 0}, 0.94500420010650077, 0.94500420010650077},
        {{10, Motor::Drive::N_V_BELT_DRIVE, 0}, 9.6430275757343225, 0.9643027575734322},
        {{600, Motor::Drive::N_V_BELT_DRIVE, 0}, 582.87297947517266, 0.97145496579195445},
        {{-50, Motor::Drive::N_V_BELT_DRIVE, 0}, 62718.909448118109, -1254.3781889623622},
        {{50, Motor::Drive::S_BELT_DRIVE, 0}, 49.392573188901288, 0.9878514637780258},
        {{100, Motor::Drive::S_BELT_DRIVE, 0}, 98.831051283262212, 0.98831051283262206},
        {{150, Motor::Drive::S_BELT_DRIVE, 0}, 148.27216144395908, 0.98848107629306048},
        {{200, Motor::Drive::S_BELT_DRIVE, 0}, 197.7088964447457, 0.98854448222372859},
        {{250, Motor::Drive::S_BELT_DRIVE, 0}, 247.14201324852445, 0.98856805299409778},
        {{0.001, Motor::Drive::S_BELT_DRIVE, 0}, 0.00097588894651716798, 0.97588894651716795},
        {{1, Motor::Drive::S_BELT_DRIVE, 0}, 0.97800168004260035, 0.97800168004260035},
        {{10, Motor::Drive::S_BELT_DRIVE, 0}, 9.8572110302937297, 0.98572110302937288},
        {{600, Motor::Drive::S_BELT_DRIVE, 0}, 593.14919179006904, 0.98858198631678185},
        {{-50, Motor::Drive::S_BELT_DRIVE, 0}, 25057.563779247241, -501.15127558494481},
        {{50, Motor::Drive::SPECIFIED, 1}, 50, 1},
        {{50, Motor::Drive::SPECIFIED, 0.97999999999999998}, 49, 0.97999999999999998},
        {{50, Motor::Drive::SPECIFIED, 0.95999999999999996}, 48, 0.95999999999999996},
        {{50, Motor::Drive::SPECIFIED, 0.93999999999999995}, 47, 0.93999999999999995},
        {{50, Motor::Drive::SPECIFIED, 0.92000000000000004}, 46, 0.92000000000000004},
        {{50, Motor::Drive::SPECIFIED, 0.90000000000000002}, 45, 0.90000000000000002},
        {{250, Motor::Drive::SPECIFIED, 1}, 250, 1},
        {{250, Motor::Drive::SPECIFIED, 0.97999999999999998}, 245, 0.97999999999999998},
        {{250, Motor::Drive::SPECIFIED, 0.95999999999999996}, 240, 0.95999999999999996},
        {{250, Motor::Drive::SPECIFIED, 0.93999999999999995}, 235, 0.93999999999999995},
        {{250, Motor::Drive::SPECIFIED, 0.92000000000000004}, 230, 0.92000000000000004},
        {{250, Motor::Drive::SPECIFIED, 0.90000000000000002}, 225, 0.90000000000000002},
        {{0, Motor::Drive::DIRECT_DRIVE, 0.10000000000000001}, 0, 1},
        {{50, Motor::Drive::DIRECT_DRIVE, 0.10000000000000001}, 50, 1},
        {{-50, Motor::Drive::DIRECT_DRIVE, 0.10000000000000001}, -50, 1},
        {{50, Motor::Drive::SPECIFIED, 0}, 0, 0},
        {{50, Motor::Drive::SPECIFIED, -0.5}, -25, -0.5},
        {{50, Motor::Drive::SPECIFIED, 1.5}, 75, 1.5},
    };
    checkFixtures(std::begin(fixtures), std::end(fixtures));
}

TEST_CASE("Mover shaft power preserves captured arithmetic boundaries", "[mover_shaft_power]") {
    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double inf = std::numeric_limits<double>::infinity();
    const Fixture fixtures[] = {
        {{0, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 0, 1},
        {{-0.0, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, -0.0, 1},
        {{inf, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, inf, 1},
        {{-inf, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, -inf, 1},
        {{nan, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, nan, 1},
        {{1.7976931348623157e+308, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 1.7976931348623157e+308, 1},
        {{-1.7976931348623157e+308, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, -1.7976931348623157e+308, 1},
        {{4.9406564584124654e-324, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 4.9406564584124654e-324, 1},
        {{-4.9406564584124654e-324, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, -4.9406564584124654e-324, 1},
        {{0, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 0, nan},
        {{-0.0, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 0, nan},
        {{inf, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{-inf, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{nan, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{1.7976931348623157e+308, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 1.725851924113813e+308, 0.96003700000000003},
        {{-1.7976931348623157e+308, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, inf, -inf},
        {{4.9406564584124654e-324, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 4.9406564584124654e-324, 1},
        {{-4.9406564584124654e-324, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, -4.9406564584124654e-324, 1},
        {{0, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 0, nan},
        {{-0.0, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 0, nan},
        {{inf, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{-inf, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{nan, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{1.7976931348623157e+308, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 1.7463779843276708e+308, 0.97145499999999996},
        {{-1.7976931348623157e+308, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, inf, -inf},
        {{4.9406564584124654e-324, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 4.9406564584124654e-324, 1},
        {{-4.9406564584124654e-324, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, -4.9406564584124654e-324, 1},
        {{0, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 0, nan},
        {{-0.0, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 0, nan},
        {{inf, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{-inf, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{nan, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{1.7976931348623157e+308, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 1.7771670746484577e+308, 0.98858199999999996},
        {{-1.7976931348623157e+308, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, inf, -inf},
        {{4.9406564584124654e-324, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 4.9406564584124654e-324, 1},
        {{-4.9406564584124654e-324, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, -4.9406564584124654e-324, 1},
        {{0, Motor::Drive::SPECIFIED, 0.80000000000000004}, 0, 0.80000000000000004},
        {{-0.0, Motor::Drive::SPECIFIED, 0.80000000000000004}, -0.0, 0.80000000000000004},
        {{inf, Motor::Drive::SPECIFIED, 0.80000000000000004}, inf, 0.80000000000000004},
        {{-inf, Motor::Drive::SPECIFIED, 0.80000000000000004}, -inf, 0.80000000000000004},
        {{nan, Motor::Drive::SPECIFIED, 0.80000000000000004}, nan, 0.80000000000000004},
        {{1.7976931348623157e+308, Motor::Drive::SPECIFIED, 0.80000000000000004}, 1.4381545078898526e+308, 0.80000000000000004},
        {{-1.7976931348623157e+308, Motor::Drive::SPECIFIED, 0.80000000000000004}, -1.4381545078898526e+308, 0.80000000000000004},
        {{4.9406564584124654e-324, Motor::Drive::SPECIFIED, 0.80000000000000004}, 4.9406564584124654e-324, 0.80000000000000004},
        {{-4.9406564584124654e-324, Motor::Drive::SPECIFIED, 0.80000000000000004}, -4.9406564584124654e-324, 0.80000000000000004},
        {{50, Motor::Drive::SPECIFIED, 0}, 0, 0},
        {{50, Motor::Drive::SPECIFIED, -0.0}, -0.0, -0.0},
        {{50, Motor::Drive::SPECIFIED, -0.5}, -25, -0.5},
        {{50, Motor::Drive::SPECIFIED, 1.5}, 75, 1.5},
        {{50, Motor::Drive::SPECIFIED, inf}, inf, inf},
        {{50, Motor::Drive::SPECIFIED, -inf}, -inf, -inf},
        {{50, Motor::Drive::SPECIFIED, nan}, nan, nan},
        {{50, Motor::Drive::SPECIFIED, 4.9406564584124654e-324}, 2.4703282292062327e-322, 4.9406564584124654e-324},
    };
    checkFixtures(std::begin(fixtures), std::end(fixtures));
}

TEST_CASE("Mover shaft power retains V-belt fallback for unknown C++ drives", "[mover_shaft_power]") {
    const double inf = std::numeric_limits<double>::infinity();
    const double nan = std::numeric_limits<double>::quiet_NaN();
    for (double power : {0., -0., 1., 50., -50., 600., inf, -inf, nan}) {
        const auto expected = mover_shaft_power::calculate({power, Motor::Drive::V_BELT_DRIVE, 0.8});
        for (int drive : {-1, 99}) {
            const auto actual = mover_shaft_power::calculate({power, static_cast<Motor::Drive>(drive), nan});
            checkNumber(actual.mover_shaft_power, expected.mover_shaft_power);
            checkNumber(actual.drive_efficiency, expected.drive_efficiency);
        }
    }
}

TEST_CASE("Mover shaft power is stateless and ignores inactive efficiency", "[mover_shaft_power]") {
    const double nan = std::numeric_limits<double>::quiet_NaN();
    for (auto drive : {Motor::Drive::DIRECT_DRIVE, Motor::Drive::V_BELT_DRIVE,
            Motor::Drive::N_V_BELT_DRIVE, Motor::Drive::S_BELT_DRIVE}) {
        mover_shaft_power::Input input{50, drive, 0.9};
        const auto before = input;
        const auto expected = mover_shaft_power::calculate(input);
        mover_shaft_power::calculate({250, Motor::Drive::SPECIFIED, 0.5});
        const auto repeated = mover_shaft_power::calculate(input);
        CHECK(input.motor_shaft_power == before.motor_shaft_power);
        CHECK(input.drive == before.drive);
        CHECK(input.specified_efficiency == before.specified_efficiency);
        CHECK(repeated.mover_shaft_power == expected.mover_shaft_power);
        CHECK(repeated.drive_efficiency == expected.drive_efficiency);
        const auto ignored = mover_shaft_power::calculate({50, drive, nan});
        CHECK(ignored.mover_shaft_power == expected.mover_shaft_power);
        CHECK(ignored.drive_efficiency == expected.drive_efficiency);
    }
}
