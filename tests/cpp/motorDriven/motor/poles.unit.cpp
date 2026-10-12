#include "motorDriven/motor/poles.h"

#include <array>

#include "catch.hpp"

namespace {

struct PoleCase {
    double               motor_rpm;
    Motor::LineFrequency line_frequency;
    int                  expected_poles;
};

} // namespace

TEST_CASE("Classify motor pole counts in nominal speed bands", "[poles]") {
    constexpr std::array<PoleCase, 24> cases {{
        {3240, Motor::LineFrequency::FREQ60, 2},
        {3600, Motor::LineFrequency::FREQ60, 2},
        {1620, Motor::LineFrequency::FREQ60, 4},
        {1800, Motor::LineFrequency::FREQ60, 4},
        {1080, Motor::LineFrequency::FREQ60, 6},
        {1200, Motor::LineFrequency::FREQ60, 6},
        {810, Motor::LineFrequency::FREQ60, 8},
        {900, Motor::LineFrequency::FREQ60, 8},
        {648, Motor::LineFrequency::FREQ60, 10},
        {720, Motor::LineFrequency::FREQ60, 10},
        {540, Motor::LineFrequency::FREQ60, 12},
        {600, Motor::LineFrequency::FREQ60, 12},
        {2700, Motor::LineFrequency::FREQ50, 2},
        {3000, Motor::LineFrequency::FREQ50, 2},
        {1350, Motor::LineFrequency::FREQ50, 4},
        {1500, Motor::LineFrequency::FREQ50, 4},
        {900, Motor::LineFrequency::FREQ50, 6},
        {1000, Motor::LineFrequency::FREQ50, 6},
        {675, Motor::LineFrequency::FREQ50, 8},
        {750, Motor::LineFrequency::FREQ50, 8},
        {540, Motor::LineFrequency::FREQ50, 10},
        {600, Motor::LineFrequency::FREQ50, 10},
        {450, Motor::LineFrequency::FREQ50, 12},
        {500, Motor::LineFrequency::FREQ50, 12},
    }};

    for (const auto& test_case : cases) {
        CAPTURE(test_case.motor_rpm, test_case.expected_poles);
        CHECK(poles::calculate(test_case.motor_rpm, test_case.line_frequency) == test_case.expected_poles);
    }
}

TEST_CASE("Preserve legacy pole-count fallback behavior", "[poles]") {
    constexpr std::array<PoleCase, 7> cases {{
        {4000, Motor::LineFrequency::FREQ60, 2},
        {4000, Motor::LineFrequency::FREQ50, 2},
        {2400, Motor::LineFrequency::FREQ60, 2},
        {1500, Motor::LineFrequency::FREQ60, 4},
        {1050, Motor::LineFrequency::FREQ60, 6},
        {800, Motor::LineFrequency::FREQ50, 8},
        {400, Motor::LineFrequency::FREQ50, 12},
    }};

    for (const auto& test_case : cases) {
        CAPTURE(test_case.motor_rpm, test_case.expected_poles);
        CHECK(poles::calculate(test_case.motor_rpm, test_case.line_frequency) == test_case.expected_poles);
    }
}
