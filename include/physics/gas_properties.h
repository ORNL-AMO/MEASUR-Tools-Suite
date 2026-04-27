#pragma once
#include <functional>
namespace gas_properties {

class GasProperties {
  public:
    std::function<double(double t)> specific_heat;
    double                          molecular_weight;
    double                          specific_weight;
    double                          composition_percent;
    double                          composition_by_volume;
    double                          o2_generated;
    double                          heating_value;
    double                          heating_value_volume;
    double                          h2o_generated;
    double                          co2_generated;
    double                          composition_weight;
    double                          composition_weight_fraction = 0;

    GasProperties(std::function<double(double t)> specific_heat, double molecular_weight, double specific_weight,
                  double composition_percent, double composition_by_volume, double o2_generated, double heating_value,
                  double heating_value_volume, double h2o_generated, double co2_generated)
        : specific_heat(std::move(specific_heat)), molecular_weight(molecular_weight), specific_weight(specific_weight),
          composition_percent(composition_percent), composition_by_volume(composition_by_volume),
          o2_generated(o2_generated), heating_value(heating_value), heating_value_volume(heating_value_volume),
          h2o_generated(h2o_generated), co2_generated(co2_generated),
          composition_weight(composition_by_volume * specific_weight) {};

    void setCompositionWeightFraction(double total_weight) {
        composition_weight_fraction = composition_weight / total_weight;
    }
};
} // namespace gas_properties