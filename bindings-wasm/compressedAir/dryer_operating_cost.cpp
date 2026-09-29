#include "compressedAir/dryer_operating_cost.h"

#include <emscripten/bind.h>

using namespace dryer_operating_cost;
using namespace emscripten;

EMSCRIPTEN_BINDINGS(dryer_operating_cost) {
    enum_<DryerType>("DryerType")
        .value("Heatless", DryerType::Heatless)
        .value("HeatedExternally", DryerType::HeatedExternally)
        .value("BlowerPurgeWithSweep", DryerType::BlowerPurgeWithSweep)
        .value("BlowerPurgeWithoutSweep", DryerType::BlowerPurgeWithoutSweep)
        .value("HeatOfCompressionHC", DryerType::HeatOfCompressionHC)
        .value("HeatOfCompressionSP", DryerType::HeatOfCompressionSP)
        .value("Refrigerated", DryerType::Refrigerated);

    enum_<PurgeInputMode>("PurgeInputMode")
        .value("PercentOfDryerCapacity", PurgeInputMode::PercentOfDryerCapacity)
        .value("DirectFlow", PurgeInputMode::DirectFlow);

    value_object<Input>("DryerOperatingCostInput")
        .field("dryerType", &Input::dryer_type)
        .field("flowRate", &Input::flow_rate)
        .field("pressure", &Input::pressure)
        .field("temperature", &Input::temperature)
        .field("annualOperatingHours", &Input::annual_operating_hours)
        .field("costOfElectricity", &Input::cost_of_electricity)
        .field("costOfCompressedAir", &Input::cost_of_compressed_air)
        .field("costOfCoolingWater", &Input::cost_of_cooling_water)
        .field("heaterPower", &Input::heater_power)
        .field("heatingHoursPerDay", &Input::heating_hours_per_day)
        .field("purgeRate", &Input::purge_rate)
        .field("purgeFlowRate", &Input::purge_flow_rate)
        .field("designDDCPercentage", &Input::design_ddc_percentage)
        .field("regenerationCycleLength", &Input::regeneration_cycle_length)
        .field("motorPower", &Input::motor_power)
        .field("purgeInputMode", &Input::purge_input_mode);

    value_object<Result>("DryerOperatingCostResult")
        .field("waterRemoved", &Result::water_removed)
        .field("totalCostPerYear", &Result::total_cost_per_year)
        .field("heaterPower", &Result::heater_power)
        .field("heatingHoursPerDay", &Result::heating_hours_per_day)
        .field("purgeRate", &Result::purge_rate)
        .field("designDDCPercentage", &Result::design_ddc_percentage)
        .field("purgeFlowRate", &Result::purge_flow_rate)
        .field("motorPower", &Result::motor_power)
        .field("regenerationCycleLength", &Result::regeneration_cycle_length);

    function("calculateDryerOperatingCost", &calculate);
}
