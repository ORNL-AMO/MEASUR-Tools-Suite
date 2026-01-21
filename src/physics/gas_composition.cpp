#include "physics/gas_composition.h"

#include <cmath>
#include <iostream>
#include <string>

#include "physics/gas_constants.h"
#include "processHeat/process_heat.h"
namespace gas_composition {

void GasComposition::setTotalCompositionWeight() {
    total_composition_weight = 0.0;
    for (auto* g : getConstituents()) {
        total_composition_weight += g->composition_weight;
    }
    for (auto* g : getConstituents()) {
        g->setCompositionWeightFraction(total_composition_weight);
    }
};

void GasComposition::setHeatingValue() {
    heating_value = 0.0;
    for (auto* g : getConstituents()) {
        heating_value += g->heating_value * g->composition_weight_fraction;
    }
};

void GasComposition::setHeatingValueVolume() {
    heating_value_volume = 0.0;
    for (auto* g : getConstituents()) {
        heating_value_volume += g->heating_value_volume * g->composition_by_volume;
    }
};

void GasComposition::setSpecificGravity() {
    double molecular_weight_mixture = 0.0;
    for (auto* g : getConstituents()) {
        molecular_weight_mixture += g->molecular_weight * g->composition_by_volume;
    }
    specific_gravity = molecular_weight_mixture / (22.4 * 1.205);
};

void GasComposition::setStoichometricAir() {
    double o2_required = 0.0;
    for (auto* g : getConstituents()) {
        o2_required += g->o2_generated * g->composition_by_volume;
    }
    double kDryAirO2VolumeFraction = 0.209; // Volume fraction of O2 in dry air
    stoichometric_air              = o2_required * (1 + (1 - kDryAirO2VolumeFraction) / kDryAirO2VolumeFraction);
}

double GasComposition::excessAirFromO2(double flue_gas_o2_percentage) {
    double excess_air = estimateExcessAirFromO2(flue_gas_o2_percentage);
    if (excess_air == 0)
        return 0;

    for (auto i = 0; i < 100; i++) {
        auto       components = getMassFlueGasComponents(excess_air);
        auto const calculated_flue_gas_o2_fraction =
            components.mO2 / (components.mH2O + components.mCO2 + components.mN2 + components.mO2 + components.mSO2);
        auto const error =
            std::fabs((flue_gas_o2_percentage - calculated_flue_gas_o2_fraction) / flue_gas_o2_percentage);
        if (error < 0.02)
            break;
        if (calculated_flue_gas_o2_fraction > flue_gas_o2_percentage) {
            excess_air -= (excess_air * 0.01);
        }
        else {
            excess_air += (excess_air * 0.01);
        }
    }
    return excess_air;
}

double GasComposition::o2PercentageFromExcessAir(double excess_air) {
    auto components = getMassFlueGasComponents(excess_air);
    return components.mO2 / (components.mH2O + components.mCO2 + components.mN2 + components.mO2 + components.mSO2);
}

// TODO: address magic numbers?
double GasComposition::estimateExcessAirFromO2(double flue_gas_o2_percentage) {
    return process_heat::calculateExcessAir(flue_gas_o2_percentage);
}

double GasComposition::calculateEnthalpyAtSaturation(double partial_pressure_water_vapor) {
    return 1096.7 * pow(partial_pressure_water_vapor * 29.926, 0.013);
}

double GasComposition::calculateSaturationTemperature(double partial_pressure_water_vapor) {
    return 36.009 * log(partial_pressure_water_vapor * 29.926) + 81.054;
}

double GasComposition::adjustedFlueGasO2ForCalcError(double excess_air, double calculated_flue_gas_o2_percent) {
    double adjusted_flue_gas_o2_for_calc_error = calculated_flue_gas_o2_percent;
    if (adjusted_flue_gas_o2_for_calc_error > 0) {
        for (auto i = 0; i < 100; i++) {
            adjusted_flue_gas_o2_for_calc_error = std::round(adjusted_flue_gas_o2_for_calc_error * 1000) / 1000.0;
            double excess_air_new               = excessAirFromO2(adjusted_flue_gas_o2_for_calc_error);
            if (fabs(1 - excess_air_new / excess_air) < 0.02)
                break;
            if (excess_air_new > excess_air) {
                adjusted_flue_gas_o2_for_calc_error *= 0.99;
            }
            else {
                adjusted_flue_gas_o2_for_calc_error *= 1.01;
            }
        }
    }
    return adjusted_flue_gas_o2_for_calc_error;
}

GasFlueGasComponents GasComposition::getMassFlueGasComponents(double excess_air) {
    GasFlueGasComponents components;
    components.mH2O = 0;
    components.mCO2 = 0;
    components.mO2  = 0;
    components.mN2  = 0;
    components.mSO2 = 0;

    for (auto* c : getConstituents()) {
        components.mH2O += (c->h2o_generated * c->composition_weight_fraction) / c->molecular_weight;
        components.mCO2 += (c->co2_generated * c->composition_weight_fraction) / c->molecular_weight;
        components.mO2 += (c->o2_generated * c->composition_weight_fraction) / c->molecular_weight;
    }
    components.mO2 *= excess_air;

    auto const& N2 = n2;
    for (auto* c : getConstituents()) {
        components.mN2 += ((c->o2_generated * c->composition_weight_fraction) / c->molecular_weight);
    }

    components.mN2 =
        ((1 - 0.231) / 0.231) * components.mN2 + components.mO2 * (1 - 0.231) / 0.231 + n2.composition_weight_fraction;

    // from previous code, so2 generated is always zero... this calculation would always be zero than.
    //  for (auto* c : constituents) {
    //      components.mSO2 += c->so2_generated * c->composition_weight_fraction / c->molecular_weight;
    //  }

    return components;
}
}; // namespace gas_composition