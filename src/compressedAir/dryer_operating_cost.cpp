#include "compressedAir/dryer_operating_cost.h"

#include <algorithm>

#include "physics/constants.h"
#include "physics/gas_constants.h"
#include "steamModeler/SaturatedProperties.h"

namespace dryer_operating_cost {
namespace {

constexpr double kMpaPerPsi = 0.00689476;
constexpr double kDesiccantPackingDensity = 0.5784;
constexpr double kHorsepowerToKilowatts = 0.7457;
constexpr double kBlowerRegenerationFactor = 0.25;

bool usesPurgeAir(const DryerType dryerType) {
    return dryerType == DryerType::Heatless || dryerType == DryerType::HeatedExternally ||
           dryerType == DryerType::BlowerPurgeWithSweep || dryerType == DryerType::HeatOfCompressionHC;
}

bool usesHeater(const DryerType dryerType) {
    return dryerType == DryerType::HeatedExternally || dryerType == DryerType::BlowerPurgeWithSweep ||
           dryerType == DryerType::BlowerPurgeWithoutSweep || dryerType == DryerType::HeatOfCompressionHC;
}

bool usesMotor(const DryerType dryerType) {
    return dryerType == DryerType::BlowerPurgeWithSweep ||
           dryerType == DryerType::BlowerPurgeWithoutSweep || dryerType == DryerType::Refrigerated;
}

bool usesDesiccant(const DryerType dryerType) {
    return dryerType != DryerType::Refrigerated;
}

double saturationPressurePsia(const double temperatureFahrenheit) {
    const auto temperatureKelvin = physics::conversions::fahrenheitToKelvin(temperatureFahrenheit);
    return SaturatedPressure(temperatureKelvin).calculate() / kMpaPerPsi;
}

} // namespace

Result calculate(const Input& input) {
    auto saturationPressure = saturationPressurePsia(input.temperature);
    if (input.dryer_type == DryerType::Refrigerated) {
        saturationPressure -= saturationPressurePsia(40.0);
    }

    const auto waterRemoved = input.flow_rate * 60.0 * gas_constants::kH2OMw * saturationPressure /
                              ((input.pressure + physics::us::kAtmosphericPressurePsi) * 379.0);

    double theoreticalDryerSize = 0.0;
    if (input.dryer_type == DryerType::Heatless) {
        theoreticalDryerSize = input.flow_rate * 114.7 /
                               (input.pressure + physics::us::kAtmosphericPressurePsi);
    } else if (usesDesiccant(input.dryer_type)) {
        const auto designDdcFraction = input.design_ddc_percentage / 100.0;
        const auto desiccantRequired = waterRemoved * input.regeneration_cycle_length / designDdcFraction;
        theoreticalDryerSize = desiccantRequired / kDesiccantPackingDensity;
    }

    double purgeFlowRate = 0.0;
    double effectivePurgeRate = 0.0;
    if (usesPurgeAir(input.dryer_type)) {
        if (input.purge_input_mode == PurgeInputMode::DirectFlow) {
            purgeFlowRate = input.purge_flow_rate;
            effectivePurgeRate = theoreticalDryerSize == 0.0
                                     ? 0.0
                                     : purgeFlowRate / theoreticalDryerSize * 100.0;
        } else {
            effectivePurgeRate = input.purge_rate;
            purgeFlowRate = theoreticalDryerSize * effectivePurgeRate / 100.0;
        }
    }

    double regenerationHeatingAirflow = 0.0;
    if (input.dryer_type == DryerType::HeatedExternally) {
        regenerationHeatingAirflow = purgeFlowRate;
    } else if (input.dryer_type == DryerType::BlowerPurgeWithSweep ||
               input.dryer_type == DryerType::BlowerPurgeWithoutSweep) {
        regenerationHeatingAirflow = theoreticalDryerSize * kBlowerRegenerationFactor;
    }

    double heaterPower = 0.0;
    if (input.dryer_type == DryerType::HeatOfCompressionHC) {
        heaterPower = input.flow_rate * 0.02 * 1.08 * 275.0 / 3412.0;
    } else if (usesHeater(input.dryer_type)) {
        heaterPower = input.heater_power;
        if (heaterPower == 0.0) {
            heaterPower = regenerationHeatingAirflow * 60.0 * 0.0764 * 0.241 *
                          (375.0 - input.temperature) / 3412.0;
        }
    }
    const auto heatingHoursPerDay = usesHeater(input.dryer_type) ? input.heating_hours_per_day : 0.0;

    double motorPower = 0.0;
    if (usesMotor(input.dryer_type)) {
        motorPower = input.motor_power;
        if (motorPower == 0.0) {
            if (input.dryer_type == DryerType::BlowerPurgeWithSweep) {
                motorPower = (regenerationHeatingAirflow / 50.0 * 0.75) / kHorsepowerToKilowatts;
            } else if (input.dryer_type == DryerType::BlowerPurgeWithoutSweep) {
                motorPower = (regenerationHeatingAirflow / 50.0) / kHorsepowerToKilowatts;
            } else {
                motorPower = (input.flow_rate / 180.0) / kHorsepowerToKilowatts;
            }
        }
    }

    const auto heaterCost = heaterPower * heatingHoursPerDay * input.annual_operating_hours / 24.0 *
                            input.cost_of_electricity;
    const auto motorCost = motorPower * kHorsepowerToKilowatts * input.annual_operating_hours *
                           input.cost_of_electricity;

    double purgeCost = 0.0;
    if (usesPurgeAir(input.dryer_type)) {
        const auto electricityEquivalentAirRate =
            (1000.0 / 60.0 / 4.5) * kHorsepowerToKilowatts / 0.9 * input.cost_of_electricity;
        const auto airRate = std::max(input.cost_of_compressed_air, electricityEquivalentAirRate);
        auto purgeDutyFactor = 1.0;
        if (input.dryer_type == DryerType::BlowerPurgeWithSweep) {
            purgeDutyFactor = 0.25;
        } else if (input.dryer_type == DryerType::HeatOfCompressionHC) {
            purgeDutyFactor = 0.375;
        }
        purgeCost = purgeFlowRate * 60.0 * input.annual_operating_hours * airRate / 1000.0 *
                    purgeDutyFactor;
    }

    const auto controlsCost = usesDesiccant(input.dryer_type)
                                  ? 100.0 * (input.annual_operating_hours / 1000.0) *
                                        input.cost_of_electricity
                                  : 0.0;
    const auto coolingWaterCost = input.dryer_type == DryerType::Refrigerated
                                      ? (input.flow_rate / 1000.0 * 8.0 * 60.0 *
                                         input.annual_operating_hours * input.cost_of_cooling_water) /
                                            1000.0
                                      : 0.0;
    const auto totalCostPerYear = heaterCost + motorCost + purgeCost + controlsCost + coolingWaterCost;

    return {
        waterRemoved,
        totalCostPerYear,
        heaterPower,
        heatingHoursPerDay,
        effectivePurgeRate,
        usesDesiccant(input.dryer_type) ? input.design_ddc_percentage : 0.0,
        purgeFlowRate,
        motorPower,
        usesDesiccant(input.dryer_type) ? input.regeneration_cycle_length : 0.0,
    };
}

} // namespace dryer_operating_cost
