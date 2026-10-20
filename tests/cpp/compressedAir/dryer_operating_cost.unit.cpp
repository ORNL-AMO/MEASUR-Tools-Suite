#include "compressedAir/dryer_operating_cost.h"

#include "catch.hpp"

using namespace Catch;

namespace {

dryer_operating_cost::Input workbookInput(const dryer_operating_cost::DryerType dryerType,
                                          const double purgeRate, const double designDdc,
                                          const double cycleLength, const double heatingHours) {
    return {
        dryerType,
        1752.0,
        50.0,
        100.0,
        8736.0,
        0.08,
        0.2,
        0.25,
        0.0,
        heatingHours,
        purgeRate,
        0.0,
        designDdc,
        cycleLength,
        0.0,
        dryer_operating_cost::PurgeInputMode::PercentOfDryerCapacity,
    };
}

void validateOutput(const dryer_operating_cost::Result& actual,
                    const dryer_operating_cost::Result& expected) {
    CHECK(actual.water_removed == Approx(expected.water_removed).margin(0.01));
    CHECK(actual.total_cost_per_year == Approx(expected.total_cost_per_year).margin(0.02));
    CHECK(actual.heater_power == Approx(expected.heater_power).margin(0.001));
    CHECK(actual.heating_hours_per_day == Approx(expected.heating_hours_per_day));
    CHECK(actual.purge_rate == Approx(expected.purge_rate).margin(0.001));
    CHECK(actual.design_ddc_percentage == Approx(expected.design_ddc_percentage));
    CHECK(actual.purge_flow_rate == Approx(expected.purge_flow_rate).margin(0.001));
    CHECK(actual.motor_power == Approx(expected.motor_power).margin(0.001));
    CHECK(actual.regeneration_cycle_length == Approx(expected.regeneration_cycle_length));
}

} // namespace

TEST_CASE("Dryer operating cost matches the v2 workbook fixture", "[dryerOperatingCost]") {
    using dryer_operating_cost::DryerType;

    validateOutput(dryer_operating_cost::calculate(
                       workbookInput(DryerType::Heatless, 15.0, 16.33, 4.0, 0.0)),
                   {73.4048, 60020.8602, 0.0, 0.0, 15.0, 16.33, 465.8912, 0.0, 4.0});

    validateOutput(dryer_operating_cost::calculate(
                       workbookInput(DryerType::HeatedExternally, 7.0, 16.33, 4.0, 18.0)),
                   {73.4048, 38227.1610, 19.3755, 18.0, 7.0, 16.33, 217.6046, 0.0, 4.0});

    validateOutput(dryer_operating_cost::calculate(
                       workbookInput(DryerType::BlowerPurgeWithSweep, 7.0, 16.33, 4.0, 18.0)),
                   {73.4048, 51488.3255, 69.1983, 18.0, 7.0, 16.33, 217.6046, 15.6328, 4.0});

    validateOutput(dryer_operating_cost::calculate(
                       workbookInput(DryerType::BlowerPurgeWithoutSweep, 0.0, 16.33, 4.0, 18.0)),
                   {73.4048, 47203.6804, 69.1983, 18.0, 0.0, 16.33, 0.0, 20.8437, 4.0});

    validateOutput(dryer_operating_cost::calculate(
                       workbookInput(DryerType::HeatOfCompressionHC, 2.0, 16.33, 4.0, 3.0)),
                   {73.4048, 3336.4933, 3.0501, 3.0, 2.0, 16.33, 62.1727, 0.0, 4.0});

    validateOutput(dryer_operating_cost::calculate(
                       workbookInput(DryerType::HeatOfCompressionSP, 0.0, 4.0, 2.0, 0.0)),
                   {73.4048, 69.888, 0.0, 0.0, 0.0, 4.0, 0.0, 0.0, 2.0});

    validateOutput(dryer_operating_cost::calculate(
                       workbookInput(DryerType::Refrigerated, 0.0, 0.0, 0.0, 0.0)),
                   {64.0029, 8639.0886, 0.0, 0.0, 0.0, 0.0, 0.0, 13.0526, 0.0});
}

TEST_CASE("Direct purge flow resolves to the equivalent percentage", "[dryerOperatingCost]") {
    auto percentageInput = workbookInput(dryer_operating_cost::DryerType::HeatedExternally,
                                         7.0, 16.33, 4.0, 18.0);
    const auto percentageResult = dryer_operating_cost::calculate(percentageInput);

    auto directInput = percentageInput;
    directInput.purge_input_mode = dryer_operating_cost::PurgeInputMode::DirectFlow;
    directInput.purge_rate = 0.0;
    directInput.purge_flow_rate = percentageResult.purge_flow_rate;
    const auto directResult = dryer_operating_cost::calculate(directInput);

    CHECK(directResult.purge_rate == Approx(7.0));
    CHECK(directResult.purge_flow_rate == Approx(percentageResult.purge_flow_rate));
    CHECK(directResult.heater_power == Approx(percentageResult.heater_power));
    CHECK(directResult.total_cost_per_year == Approx(percentageResult.total_cost_per_year));
}

TEST_CASE("Manual heater and motor sizes override automatic sizing", "[dryerOperatingCost]") {
    auto heaterInput = workbookInput(dryer_operating_cost::DryerType::HeatedExternally,
                                     7.0, 16.33, 4.0, 18.0);
    heaterInput.heater_power = 15.0;
    const auto heaterResult = dryer_operating_cost::calculate(heaterInput);
    CHECK(heaterResult.heater_power == Approx(15.0));

    auto motorInput = workbookInput(dryer_operating_cost::DryerType::BlowerPurgeWithoutSweep,
                                    0.0, 16.33, 4.0, 18.0);
    motorInput.motor_power = 10.0;
    const auto motorResult = dryer_operating_cost::calculate(motorInput);
    CHECK(motorResult.motor_power == Approx(10.0));
}

TEST_CASE("Annual hours scale costs and decimal temperatures are not rounded", "[dryerOperatingCost]") {
    auto fullYearInput = workbookInput(dryer_operating_cost::DryerType::Heatless,
                                       15.0, 16.33, 4.0, 0.0);
    const auto fullYear = dryer_operating_cost::calculate(fullYearInput);

    auto halfYearInput = fullYearInput;
    halfYearInput.annual_operating_hours /= 2.0;
    const auto halfYear = dryer_operating_cost::calculate(halfYearInput);
    CHECK(halfYear.total_cost_per_year == Approx(fullYear.total_cost_per_year / 2.0));

    auto decimalInput = fullYearInput;
    decimalInput.temperature = 100.1;
    const auto firstTemperature = dryer_operating_cost::calculate(decimalInput);
    decimalInput.temperature = 100.4;
    const auto secondTemperature = dryer_operating_cost::calculate(decimalInput);
    CHECK(firstTemperature.water_removed != Approx(secondTemperature.water_removed));
}

TEST_CASE("Calculation does not enforce frontend validation ranges", "[dryerOperatingCost]") {
    auto input = workbookInput(dryer_operating_cost::DryerType::Heatless,
                               15.0, 16.33, 4.0, 0.0);
    input.flow_rate = 0.5;
    input.pressure = 10.0;
    input.temperature = 45.0;
    input.annual_operating_hours = 9000.0;
    input.cost_of_electricity = 0.0;
    CHECK_NOTHROW(dryer_operating_cost::calculate(input));
}
