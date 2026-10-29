#include "motorDriven/motor/optimal_motor_shaft_power.h"

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
    optimal_motor_shaft_power::Input input;
    double power;
    double efficiency;
};

void checkFixtures(const Fixture* begin, const Fixture* end) {
    for (auto fixture = begin; fixture != end; ++fixture) {
        CAPTURE(fixture->input.mover_shaft_power, static_cast<int>(fixture->input.drive),
            fixture->input.specified_efficiency);
        const auto result = optimal_motor_shaft_power::calculate(fixture->input);
        checkNumber(result.motor_shaft_power, fixture->power);
        checkNumber(result.drive_efficiency, fixture->efficiency);
    }
}

} // namespace

// Both outputs captured at -O3 from unchanged OptimalMotorShaftPower at base 93427c3.
TEST_CASE("Optimal motor shaft power preserves captured duties for all five drives", "[optimal_motor_shaft_power]") {
    const Fixture fixtures[] = {
        {{0.001, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 0.001, 1},
        {{1, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 1, 1},
        {{10, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 10, 1},
        {{50, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 50, 1},
        {{100, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 100, 1},
        {{250, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 250, 1},
        {{600, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 600, 1},
        {{-50, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, -50, 1},
        {{0.001, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 0.0010904708209481637, 0.91703508318590365},
        {{1, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 1.0819590817354099, 0.92424937031449328},
        {{10, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 10.520327017292107, 0.95054079436534111},
        {{50, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 52.214537061836324, 0.95758772965441197},
        {{100, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 104.25740426439738, 0.95916449009606475},
        {{250, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 260.41741132953581, 0.95999725488264875},
        {{600, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 624.97626036074303, 0.9600364654709822},
        {{-50, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, -167416.22527577286, 0.00029865683518809811},
        {{0.001, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 0.0010646220149629741, 0.93930050848589541},
        {{1, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 1.0585422012395784, 0.94469544891925505},
        {{10, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 10.371662155208648, 0.96416561302838033},
        {{50, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 51.581812187025946, 0.96933391596846985},
        {{100, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 103.04100304599812, 0.97048744717051516},
        {{250, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 257.44100809252558, 0.97109625949782163},
        {{600, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 617.84018597195927, 0.97112491809853074},
        {{-50, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, -119597.30376840918, 0.00041806962552283858},
        {{0.001, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 0.0010258488059851896, 0.97480251881721958},
        {{1, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 1.0234168804958315, 0.97711892295103997},
        {{10, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 10.148664862083459, 0.98535128865680777},
        {{50, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 50.632724874810378, 0.98750363768936411},
        {{100, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 101.21640121839926, 0.98798217281234324},
        {{250, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 252.97640323701023, 0.98823446298182327},
        {{600, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 607.13607438878375, 0.98824633440540033},
        {{-50, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, -47868.921507363673, 0.0010445190412804372},
        {{0.001, Motor::Drive::SPECIFIED, 0.80000000000000004}, 0.00125, 0.80000000000000004},
        {{1, Motor::Drive::SPECIFIED, 0.80000000000000004}, 1.25, 0.80000000000000004},
        {{10, Motor::Drive::SPECIFIED, 0.80000000000000004}, 12.5, 0.80000000000000004},
        {{50, Motor::Drive::SPECIFIED, 0.80000000000000004}, 62.5, 0.80000000000000004},
        {{100, Motor::Drive::SPECIFIED, 0.80000000000000004}, 125, 0.80000000000000004},
        {{250, Motor::Drive::SPECIFIED, 0.80000000000000004}, 312.5, 0.80000000000000004},
        {{600, Motor::Drive::SPECIFIED, 0.80000000000000004}, 750, 0.80000000000000004},
        {{-50, Motor::Drive::SPECIFIED, 0.80000000000000004}, -62.5, 0.80000000000000004},
    };
    checkFixtures(std::begin(fixtures), std::end(fixtures));
}

TEST_CASE("Optimal motor shaft power preserves captured arithmetic boundaries", "[optimal_motor_shaft_power]") {
    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double inf = std::numeric_limits<double>::infinity();
    const Fixture fixtures[] = {
        {{0, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 0, 1},
        {{-0.0, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, -0.0, 1},
        {{4.9406564584124654e-324, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 4.9406564584124654e-324, 1},
        {{-4.9406564584124654e-324, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, -4.9406564584124654e-324, 1},
        {{1.7976931348623157e+308, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, 1.7976931348623157e+308, 1},
        {{-1.7976931348623157e+308, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, -1.7976931348623157e+308, 1},
        {{inf, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, inf, 1},
        {{-inf, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, -inf, 1},
        {{nan, Motor::Drive::DIRECT_DRIVE, 0.80000000000000004}, nan, 1},
        {{0, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 0, 0.91702709163232909},
        {{-0.0, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, -0.0, 0.91702709163232909},
        {{4.9406564584124654e-324, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, 4.9406564584124654e-324, 0.91702709163232909},
        {{-4.9406564584124654e-324, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, -4.9406564584124654e-324, 0.91702709163232909},
        {{1.7976931348623157e+308, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, inf, 0.9600364936752267},
        {{-1.7976931348623157e+308, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, -inf, 0},
        {{inf, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, inf, 0.9600364936752267},
        {{-inf, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, -inf, 0},
        {{nan, Motor::Drive::V_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{0, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 0, 0.93929451966385025},
        {{-0.0, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, -0.0, 0.93929451966385025},
        {{4.9406564584124654e-324, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, 4.9406564584124654e-324, 0.93929451966385025},
        {{-4.9406564584124654e-324, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, -4.9406564584124654e-324, 0.93929451966385025},
        {{1.7976931348623157e+308, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, inf, 0.97112493871247851},
        {{-1.7976931348623157e+308, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, -inf, 0},
        {{inf, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, inf, 0.97112493871247851},
        {{-inf, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, -inf, 0},
        {{nan, Motor::Drive::N_V_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{0, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 0, 0.97479993877276017},
        {{-0.0, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, -0.0, 0.97479993877276017},
        {{4.9406564584124654e-324, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, 4.9406564584124654e-324, 0.97479993877276017},
        {{-4.9406564584124654e-324, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, -4.9406564584124654e-324, 0.97479993877276017},
        {{1.7976931348623157e+308, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, inf, 0.9882463429442897},
        {{-1.7976931348623157e+308, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, -inf, 0},
        {{inf, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, inf, 0.9882463429442897},
        {{-inf, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, -inf, 0},
        {{nan, Motor::Drive::S_BELT_DRIVE, 0.80000000000000004}, nan, nan},
        {{0, Motor::Drive::SPECIFIED, 0.80000000000000004}, 0, 0.80000000000000004},
        {{-0.0, Motor::Drive::SPECIFIED, 0.80000000000000004}, -0.0, 0.80000000000000004},
        {{4.9406564584124654e-324, Motor::Drive::SPECIFIED, 0.80000000000000004}, 4.9406564584124654e-324, 0.80000000000000004},
        {{-4.9406564584124654e-324, Motor::Drive::SPECIFIED, 0.80000000000000004}, -4.9406564584124654e-324, 0.80000000000000004},
        {{1.7976931348623157e+308, Motor::Drive::SPECIFIED, 0.80000000000000004}, inf, 0.80000000000000004},
        {{-1.7976931348623157e+308, Motor::Drive::SPECIFIED, 0.80000000000000004}, -inf, 0.80000000000000004},
        {{inf, Motor::Drive::SPECIFIED, 0.80000000000000004}, inf, 0.80000000000000004},
        {{-inf, Motor::Drive::SPECIFIED, 0.80000000000000004}, -inf, 0.80000000000000004},
        {{nan, Motor::Drive::SPECIFIED, 0.80000000000000004}, nan, 0.80000000000000004},
        {{50, Motor::Drive::SPECIFIED, 0}, inf, 0},
        {{0, Motor::Drive::SPECIFIED, 0}, nan, 0},
        {{-0.0, Motor::Drive::SPECIFIED, 0}, nan, 0},
        {{-50, Motor::Drive::SPECIFIED, 0}, -inf, 0},
        {{50, Motor::Drive::SPECIFIED, -0.0}, -inf, -0.0},
        {{0, Motor::Drive::SPECIFIED, -0.0}, nan, -0.0},
        {{-0.0, Motor::Drive::SPECIFIED, -0.0}, nan, -0.0},
        {{-50, Motor::Drive::SPECIFIED, -0.0}, inf, -0.0},
        {{50, Motor::Drive::SPECIFIED, -0.5}, -100, -0.5},
        {{0, Motor::Drive::SPECIFIED, -0.5}, -0.0, -0.5},
        {{-0.0, Motor::Drive::SPECIFIED, -0.5}, 0, -0.5},
        {{-50, Motor::Drive::SPECIFIED, -0.5}, 100, -0.5},
        {{50, Motor::Drive::SPECIFIED, 1}, 50, 1},
        {{0, Motor::Drive::SPECIFIED, 1}, 0, 1},
        {{-0.0, Motor::Drive::SPECIFIED, 1}, -0.0, 1},
        {{-50, Motor::Drive::SPECIFIED, 1}, -50, 1},
        {{50, Motor::Drive::SPECIFIED, 1.5}, 33.333333333333336, 1.5},
        {{0, Motor::Drive::SPECIFIED, 1.5}, 0, 1.5},
        {{-0.0, Motor::Drive::SPECIFIED, 1.5}, -0.0, 1.5},
        {{-50, Motor::Drive::SPECIFIED, 1.5}, -33.333333333333336, 1.5},
        {{50, Motor::Drive::SPECIFIED, inf}, 0, inf},
        {{0, Motor::Drive::SPECIFIED, inf}, 0, inf},
        {{-0.0, Motor::Drive::SPECIFIED, inf}, -0.0, inf},
        {{-50, Motor::Drive::SPECIFIED, inf}, -0.0, inf},
        {{50, Motor::Drive::SPECIFIED, -inf}, -0.0, -inf},
        {{0, Motor::Drive::SPECIFIED, -inf}, -0.0, -inf},
        {{-0.0, Motor::Drive::SPECIFIED, -inf}, 0, -inf},
        {{-50, Motor::Drive::SPECIFIED, -inf}, 0, -inf},
        {{50, Motor::Drive::SPECIFIED, nan}, nan, nan},
        {{0, Motor::Drive::SPECIFIED, nan}, nan, nan},
        {{-0.0, Motor::Drive::SPECIFIED, nan}, nan, nan},
        {{-50, Motor::Drive::SPECIFIED, nan}, nan, nan},
        {{50, Motor::Drive::SPECIFIED, 4.9406564584124654e-324}, inf, 4.9406564584124654e-324},
        {{0, Motor::Drive::SPECIFIED, 4.9406564584124654e-324}, 0, 4.9406564584124654e-324},
        {{-0.0, Motor::Drive::SPECIFIED, 4.9406564584124654e-324}, -0.0, 4.9406564584124654e-324},
        {{-50, Motor::Drive::SPECIFIED, 4.9406564584124654e-324}, -inf, 4.9406564584124654e-324},
    };
    checkFixtures(std::begin(fixtures), std::end(fixtures));
}

TEST_CASE("Optimal motor shaft power retains V-belt fallback for unknown C++ drives", "[optimal_motor_shaft_power]") {
    const double inf = std::numeric_limits<double>::infinity();
    const double nan = std::numeric_limits<double>::quiet_NaN();
    for (double power : {0., -0., 1., 50., -50., 600., inf, -inf, nan}) {
        const auto expected = optimal_motor_shaft_power::calculate({power, Motor::Drive::V_BELT_DRIVE, 0.8});
        for (int drive : {-1, 99}) {
            const auto actual = optimal_motor_shaft_power::calculate({power, static_cast<Motor::Drive>(drive), nan});
            checkNumber(actual.motor_shaft_power, expected.motor_shaft_power);
            checkNumber(actual.drive_efficiency, expected.drive_efficiency);
        }
    }
}

TEST_CASE("Optimal motor shaft power is stateless and ignores inactive efficiency", "[optimal_motor_shaft_power]") {
    const double nan = std::numeric_limits<double>::quiet_NaN();
    for (auto drive : {Motor::Drive::DIRECT_DRIVE, Motor::Drive::V_BELT_DRIVE,
            Motor::Drive::N_V_BELT_DRIVE, Motor::Drive::S_BELT_DRIVE}) {
        optimal_motor_shaft_power::Input input{50, drive, 0.9};
        const auto before = input;
        const auto expected = optimal_motor_shaft_power::calculate(input);
        optimal_motor_shaft_power::calculate({250, Motor::Drive::SPECIFIED, 0.5});
        const auto repeated = optimal_motor_shaft_power::calculate(input);
        CHECK(input.mover_shaft_power == before.mover_shaft_power);
        CHECK(input.drive == before.drive);
        CHECK(input.specified_efficiency == before.specified_efficiency);
        CHECK(repeated.motor_shaft_power == expected.motor_shaft_power);
        CHECK(repeated.drive_efficiency == expected.drive_efficiency);
        const auto ignored = optimal_motor_shaft_power::calculate({50, drive, nan});
        CHECK(ignored.motor_shaft_power == expected.motor_shaft_power);
        CHECK(ignored.drive_efficiency == expected.drive_efficiency);
    }
}
