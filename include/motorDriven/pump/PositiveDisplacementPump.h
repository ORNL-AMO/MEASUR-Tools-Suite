#pragma once

/**
 * @file PositiveDisplacementPump.h
 * @brief Positive displacement pump power and annual energy calculation.
 *
 * @author Mark Root (mroot)
 * @bug No known bugs.
 */

/**
 * @class PositiveDisplacementPump
 * @brief Calculates positive displacement pump power from flow rate, differential pressure, and pump efficiency.
 */
class PositiveDisplacementPump {
  public:
    struct Output {
        /**
         * @param power Pump power @unit{\kW}.
         * @param energy Annual energy use @unit{\kWHour\per\year}.
         */
        Output(double power, double energy) : power(power), energy(energy) {}

        /**
         * @brief Default constructor.
         */
        Output() = default;

        double power  = 0; ///< Pump power @unit{\kW}.
        double energy = 0; ///< Annual energy use @unit{\kWHour\per\year}.
    };

    /**
     * @brief Constructor.
     * @param flowRate Volumetric flow rate @unit{\gallons\per\minute}.
     * @param differentialPressure Pump differential pressure @unit{\PSI}.
     * @param pumpEfficiency Pump efficiency as a fraction, dimensionless.
     * @param operatingHours Annual operating hours @unit{\hour\per\year}.
     */
    PositiveDisplacementPump(double flowRate, double differentialPressure, double pumpEfficiency,
                             double operatingHours)
        : flowRate(flowRate), differentialPressure(differentialPressure), pumpEfficiency(pumpEfficiency),
          operatingHours(operatingHours) {}

    /**
     * @brief Calculates pump power and annual energy.
     * @return PositiveDisplacementPump::Output.
     */
    Output calculate() const;

  private:
    double flowRate;
    double differentialPressure;
    double pumpEfficiency;
    double operatingHours;
};
