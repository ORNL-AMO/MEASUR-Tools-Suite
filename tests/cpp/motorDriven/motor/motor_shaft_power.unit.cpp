#include "motorDriven/motor/motor_shaft_power.h"

#include <array>
#include <cmath>
#include <limits>
#include <stdexcept>

#include "catch.hpp"

namespace {

std::array<double, 7> values(const motor_shaft_power::Result& result) {
    return {result.shaft_power, result.current, result.power_factor, result.efficiency,
            result.power, result.estimated_fla, result.load_factor};
}

void checkResult(const motor_shaft_power::Result& actual, const motor_shaft_power::Result& expected) {
    const auto actual_values = values(actual);
    const auto expected_values = values(expected);
    for (std::size_t i = 0; i < actual_values.size(); ++i) {
        INFO("result member " << i);
        if (std::isnan(expected_values[i])) {
            CHECK(std::isnan(actual_values[i]));
        } else if (std::isinf(expected_values[i])) {
            CHECK(actual_values[i] == expected_values[i]);
        } else {
            CHECK(actual_values[i] == Catch::Approx(expected_values[i]).epsilon(1e-11).margin(1e-9));
        }
    }
}

motor_shaft_power::Input input() {
    return {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT,
            0.93, 460, 120, 460, Motor::LoadEstimationMethod::POWER, 90};
}

} // namespace

TEST_CASE("Motor shaft power preserves captured legacy operating points", "[motor_shaft_power]") {
    struct Golden {
        const char* label;
        motor_shaft_power::Input input;
        motor_shaft_power::Result expected;
    };
    // Captured before refactoring from unchanged MotorShaftPower.cpp and freshly built dependencies at ba430c6.
    // Threshold rows use the exact model value and its immediately adjacent representable doubles.
    // Nonfinite and extrapolated outputs deliberately describe legacy behavior, not valid operating points.
    const Golden goldens[] = {
        {"model-0-0-0", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0.93000000000000005, 460, 120, 480, Motor::LoadEstimationMethod::POWER, 90},
         {74.644607922920201, 89.863398811275957, 0.8030943031685952, 0.92808129184164112, 60, 116.56258946300228, 0.74644642141526696}},
        {"model-0-0-1", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0.93000000000000005, 460, 120, 440, Motor::LoadEstimationMethod::CURRENT, 90},
         {71.339144770383754, 90, 0.83649539013900343, 0.92757142430217854, 57.374559634308994, 116.56258946300228, 0.71338955600985521}},
        {"model-0-1-0", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 480, Motor::LoadEstimationMethod::POWER, 90},
         {76.493234440657758, 91.630818602681927, 0.78760382968564824, 0.95106588154551153, 60, 113.83426223054738, 0.76493238593601842}},
        {"model-0-1-1", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 440, Motor::LoadEstimationMethod::CURRENT, 90},
         {71.339014714031478, 90, 0.81599448272544661, 0.95087383841616413, 55.968418549943777, 113.83426223054738, 0.71338955600985521}},
        {"model-0-2-0", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM, 0.93000000000000005, 460, 120, 480, Motor::LoadEstimationMethod::POWER, 90},
         {77.017698935465646, 92.132939790830818, 0.78331141731228637, 0.95758672343095619, 60, 113.15677524898257, 0.77017696785812872}},
        {"model-0-2-1", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::PREMIUM, 0.93000000000000005, 460, 120, 440, Motor::LoadEstimationMethod::CURRENT, 90},
         {71.338860763353495, 90, 0.80981175160887242, 0.95813147926442011, 55.544349894775415, 113.15677524898257, 0.71338955600981968}},
        {"model-0-3-0", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 0.93000000000000005, 460, 120, 480, Motor::LoadEstimationMethod::POWER, 90},
         {74.699243269373611, 89.915432895686962, 0.80262955228640176, 0.92876059131587863, 60, 116.48727331091592, 0.74699220976001868}},
        {"model-0-3-1", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 0.93000000000000005, 460, 120, 440, Motor::LoadEstimationMethod::CURRENT, 90},
         {71.338914372092688, 90, 0.83524808873403389, 0.92895359477917383, 57.289008213840923, 116.48727331091592, 0.71338955600985521}},
        {"model-1-0-0", {100, 60, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::STANDARD, 0.93000000000000005, 460, 120, 480, Motor::LoadEstimationMethod::POWER, 90},
         {74.644607922920201, 89.863398811275957, 0.8030943031685952, 0.92808129184164112, 60, 116.56258946300228, 0.74644642141526696}},
        {"model-1-0-1", {100, 60, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::STANDARD, 0.93000000000000005, 460, 120, 440, Motor::LoadEstimationMethod::CURRENT, 90},
         {71.339144770383754, 90, 0.83649539013900343, 0.92757142430217854, 57.374559634308994, 116.56258946300228, 0.71338955600985521}},
        {"model-1-1-0", {100, 60, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 480, Motor::LoadEstimationMethod::POWER, 90},
         {76.493234440657758, 91.630818602681927, 0.78760382968564824, 0.95106588154551153, 60, 113.83426223054738, 0.76493238593601842}},
        {"model-1-1-1", {100, 60, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 440, Motor::LoadEstimationMethod::CURRENT, 90},
         {71.339014714031478, 90, 0.81599448272544661, 0.95087383841616413, 55.968418549943777, 113.83426223054738, 0.71338955600985521}},
        {"model-1-2-0", {100, 60, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::PREMIUM, 0.93000000000000005, 460, 120, 480, Motor::LoadEstimationMethod::POWER, 90},
         {77.017698935465646, 92.132939790830818, 0.78331141731228637, 0.95758672343095619, 60, 113.15677524898257, 0.77017696785812872}},
        {"model-1-2-1", {100, 60, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::PREMIUM, 0.93000000000000005, 460, 120, 440, Motor::LoadEstimationMethod::CURRENT, 90},
         {71.338860763353495, 90, 0.80981175160887242, 0.95813147926442011, 55.544349894775415, 113.15677524898257, 0.71338955600981968}},
        {"model-1-3-0", {100, 60, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::SPECIFIED, 0.93000000000000005, 460, 120, 480, Motor::LoadEstimationMethod::POWER, 90},
         {74.699243269373611, 89.915432895686962, 0.80262955228640176, 0.92876059131587863, 60, 116.48727331091592, 0.74699220976001868}},
        {"model-1-3-1", {100, 60, 1480, Motor::LineFrequency::FREQ50, Motor::EfficiencyClass::SPECIFIED, 0.93000000000000005, 460, 120, 440, Motor::LoadEstimationMethod::CURRENT, 90},
         {71.338914372092688, 90, 0.83524808873403389, 0.92895359477917383, 57.289008213840923, 116.48727331091592, 0.71338955600985521}},
        {"equal-voltage-0", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::POWER, 90},
         {76.493234440657758, 93.791604894800983, 0.80291361828477603, 0.95106588154551153, 60, 113.83426223054738, 0.76493238593601842}},
        {"zero-measurement-0", {100, 0, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::POWER, 0},
         {0, std::numeric_limits<double>::quiet_NaN(), 0, 0, 0, 113.83426223054738, 0}},
        {"negative-measurement-0", {100, -1, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::POWER, -1},
         {0.2428199790902581, 35.298254168503597, -0.035557262261625915, -0.18114370440133254, -1, 113.83426223054738, -0.0049276767252961927}},
        {"overload-0", {100, 200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::POWER, 400},
         {227.91049396334964, 295.34526466035413, 0.84992680163020951, 0.85010614248329419, 200, 113.83426223054738, 2.3564301470947129}},
        {"zero-fla-0", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 0, 460, Motor::LoadEstimationMethod::POWER, 90},
         {std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), 60, 113.83426223054738, std::numeric_limits<double>::quiet_NaN()}},
        {"changed-fla-0", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 150, 460, Motor::LoadEstimationMethod::POWER, 90},
         {76.493234440657758, 117.23950611852244, 0.64233089462770454, 0.95106588154551153, 60, 113.83426223054738, 0.76493238593601853}},
        {"equal-voltage-1", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::CURRENT, 90},
         {72.904840344592401, 90, 0.79758057323954124, 0.95095431838560962, 57.192033145604931, 113.83426223054738, 0.7290484497988714}},
        {"zero-measurement-1", {100, 0, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::CURRENT, 0},
         {89445.593949695671, 0, -std::numeric_limits<double>::infinity(), -359.21278021572539, -185.75734706989095, 113.83426223054738, -2.465090266600408}},
        {"negative-measurement-1", {100, -1, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::CURRENT, -1},
         {94627.324837368695, -1, 239.82665319246789, -369.43623031433799, -191.08029623573532, 113.83426223054738, -2.5352484812219203}},
        {"overload-1", {100, 200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::CURRENT, 400},
         {284.45778510815813, 400, 0.84762803303895107, 0.78554829408642524, 270.1368067223367, 113.83426223054738, 3.1196159947455349}},
        {"zero-fla-1", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 0, 460, Motor::LoadEstimationMethod::CURRENT, 90},
         {std::numeric_limits<double>::quiet_NaN(), 90, std::numeric_limits<double>::quiet_NaN(), -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN(), 113.83426223054738, std::numeric_limits<double>::infinity()}},
        {"changed-fla-1", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 150, 460, Motor::LoadEstimationMethod::CURRENT, 90},
         {55.03145177691691, 90, 0.60392163347360273, 0.94799979184840477, 43.305350252803535, 113.83426223054738, 0.55031461669948045}},
        {"threshold-0-0--1", {100, 20.238309287096126, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::POWER, 90},
         {25.000000000000007, 45.056212548352967, 0.56376886511769575, 0.92151966527614926, 20.238309287096126, 113.83426223054738, 0.25}},
        {"threshold-0-0-0", {100, 20.238309287096129, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::POWER, 90},
         {25.000000000000014, 45.056212548352967, 0.56376886511769586, 0.92151966527614926, 20.238309287096129, 113.83426223054738, 0.25000000000000006}},
        {"threshold-0-0-1", {100, 20.238309287096133, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::POWER, 90},
         {25.000000000000018, 45.056212548352967, 0.56376886511769597, 0.92151966527614926, 20.238309287096133, 113.83426223054738, 0.25000000000000011}},
        {"threshold-0-1--1", {100, 2.0293539039736657, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::POWER, 90},
         {0.99999999999999956, 35.29825416850359, 0.072158268985246049, 0.36760468370709593, 2.0293539039736657, 113.83426223054738, 0.0099999999999999985}},
        {"threshold-0-1-0", {100, 2.0293539039736661, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::POWER, 90},
         {1, 35.298254168503597, 0.072158268985246063, 0.36760468370709598, 2.0293539039736661, 113.83426223054738, 0.01}},
        {"threshold-0-1-1", {100, 2.0293539039736666, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::POWER, 90},
         {1.0000000000000004, 35.298254168503597, 0.072158268985246077, 0.36760468370709609, 2.0293539039736666, 113.83426223054738, 0.010000000000000005}},
        {"threshold-1-0--1", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::CURRENT, 45.05621254835296},
         {25.000000000000004, 45.05621254835296, 0.56376886511769575, 0.92151966527614926, 20.238309287096122, 113.83426223054738, 0.24999999999999994}},
        {"threshold-1-0-0", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::CURRENT, 45.056212548352967},
         {25.000000000000014, 45.056212548352967, 0.56376886511769586, 0.92151966527614926, 20.238309287096129, 113.83426223054738, 0.25000000000000006}},
        {"threshold-1-0-1", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::CURRENT, 45.056212548352974},
         {25.000000000000018, 45.056212548352974, 0.56376886511769597, 0.92151966527614926, 20.238309287096136, 113.83426223054738, 0.25000000000000017}},
        {"threshold-1-1--1", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::CURRENT, 35.136160175954004},
         {-1.234506643718559e-13, 35.136160175954004, 0.045389176668293313, -7.2478166224933955e-14, 1.2706474296768595, 113.83426223054738, -4.9786563760534364e-16}},
        {"threshold-1-1-0", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::CURRENT, 35.136160175954011},
         {0, 35.136160175954011, 0.045389176668294652, 0, 1.2706474296768973, 113.83426223054738, 0}},
        {"threshold-1-1-1", {100, 60, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0.93000000000000005, 460, 120, 460, Motor::LoadEstimationMethod::CURRENT, 35.136160175954018},
         {2.7446726534186946e-14, 35.136160175954018, 0.045389176668295832, 1.611403566110342e-14, 1.2706474296769306, 113.83426223054738, 4.3835229460631506e-16}},
    };
    for (const auto& golden : goldens) {
        INFO(golden.label);
        checkResult(motor_shaft_power::calculate(golden.input), golden.expected);
    }
}

TEST_CASE("Motor shaft power has no retained state and ignores the inactive measurement", "[motor_shaft_power]") {
    for (const auto mode : {Motor::LoadEstimationMethod::POWER, Motor::LoadEstimationMethod::CURRENT}) {
        auto data = input();
        data.load_estimation_method = mode;
        const auto first = motor_shaft_power::calculate(data);
        auto other = data;
        other.field_voltage = 480;
        other.full_load_amps = 150;
        motor_shaft_power::calculate(other);
        CHECK(values(motor_shaft_power::calculate(data)) == values(first));
        if (mode == Motor::LoadEstimationMethod::POWER) {
            data.field_current = std::numeric_limits<double>::quiet_NaN();
        } else {
            data.motor_measured_power = std::numeric_limits<double>::quiet_NaN();
        }
        CHECK(values(motor_shaft_power::calculate(data)) == values(first));
        CHECK(data.motor_rated_power == 100);
        CHECK(data.field_voltage == 460);
        CHECK(data.full_load_amps == 120);
        CHECK(data.load_estimation_method == mode);
    }
}

TEST_CASE("Motor shaft power propagates specified-efficiency dependency errors", "[motor_shaft_power]") {
    for (const auto mode : {Motor::LoadEstimationMethod::POWER, Motor::LoadEstimationMethod::CURRENT}) {
        auto data = input();
        data.load_estimation_method = mode;
        data.efficiency_class = Motor::EfficiencyClass::SPECIFIED;
        data.specified_efficiency = -1;
        CHECK_THROWS_WITH(motor_shaft_power::calculate(data),
                          "An efficiency must be specified if EfficiencyClass::SPECIFIED is used");
    }
}
