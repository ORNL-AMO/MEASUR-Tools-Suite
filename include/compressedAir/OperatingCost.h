/**
 * @file
 * @brief Implementations of Operating Cost of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_OPERATINGCOST_H
#define TOOLS_SUITE_OPERATINGCOST_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>

class OperatingCost {
public:
    /**
     * Constructor for OperatingCost - This finds the cost of operation of the compressor
     * in both fully and partially loaded instances.
     * @param motorBhp double, Brake Horse Power is the input power required at the compressor input shaft for a specific speed,
     * capacity and pressure condition. It is generally shown on the compressor panel. - bhp
     * @param bhpUnloaded double, Brake horse power in the unloaded condition. - %
     * @param annualOperatingHours double, Time for which the compressor operates in a year - hours
     * @param runTimeLoaded double, Percentage of time the compressor runs in loaded condition - %
     * @param efficiencyLoaded double, Percentage of efficiency in loaded condition - %
     * @param efficiencyUnloaded double, Percentage of efficiency in un-loaded condition - %
     * @param costOfElectricity double, Cost of electricity per kWh - $
     */
    OperatingCost(double motorBhp, double bhpUnloaded, double annualOperatingHours, double runTimeLoaded,
                  double efficiencyLoaded, double efficiencyUnloaded, double costOfElectricity)
            : motorBhp(motorBhp), bhpUnloaded(bhpUnloaded), annualOperatingHours(annualOperatingHours),
              runTimeLoaded(runTimeLoaded), efficiencyLoaded(efficiencyLoaded), efficiencyUnloaded(efficiencyUnloaded),
              costOfElectricity(costOfElectricity)
    {}

    struct Output {
        Output(const double runTimeUnloaded, const double costForLoaded, const double costForUnloaded,
               const double totalAnnualCost)
                : runTimeUnloaded(runTimeUnloaded), costForLoaded(costForLoaded),
                  costForUnloaded(costForUnloaded), totalAnnualCost(totalAnnualCost)
        {}

        const double runTimeUnloaded, costForLoaded, costForUnloaded, totalAnnualCost;
    };

    Output calculate() {
        auto const runTimeUnloaded = 100 - runTimeLoaded;
        auto const costForLoaded = (motorBhp * 0.746 * annualOperatingHours * costOfElectricity * (runTimeLoaded / 100))
                                   / (efficiencyLoaded / 100);
        auto const costForUnloaded = (motorBhp * 0.746 * annualOperatingHours * costOfElectricity * (bhpUnloaded / 100) * (runTimeUnloaded / 100))
                                     / (efficiencyUnloaded / 100);
        return {runTimeUnloaded, costForLoaded, costForUnloaded, costForLoaded + costForUnloaded};
    }

private:
    double motorBhp, bhpUnloaded, annualOperatingHours, runTimeLoaded, efficiencyLoaded;
    double efficiencyUnloaded, costOfElectricity;
};

#endif
