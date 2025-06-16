/**
 * @file
 * @brief Implementations of Bag Method of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_BAGMETHOD_H
#define TOOLS_SUITE_BAGMETHOD_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>

class BagMethod {
public:
    struct Output {
        Output(const double flowRate, const double annualConsumption)
                : flowRate(flowRate), annualConsumption(annualConsumption)
        {}

        const double flowRate, annualConsumption;
    };

    /**
     * Constructor for BagMethod - The bag method estimates the air flow using a trash bag by counting the time it
     * takes to fill it. This is the second most accurate means of measuring compressed air consumption.
     * @param operatingTime double, operating time of the system per year - hours
     * @param bagFillTime double, time that it takes for the bag to fill with air - seconds
     * @param bagVolume double, volume of the bag filler - cubic feet
     * @param numberOfUnits int, number of trash bags
     * @returns flowRate in ft3, annualConsumption in ?
     */
    BagMethod(double operatingTime, double bagFillTime, double bagVolume, int numberOfUnits)
            : operatingTime(operatingTime), bagFillTime(bagFillTime),
              bagVolume(bagVolume), numberOfUnits(numberOfUnits)
    {}

    /**
     * @return BagMethod::Output, flowRate and annual consumption
     */
    Output calculate() {
        auto const flowRate = bagVolume / (bagFillTime / 60);
        return {flowRate, (flowRate * operatingTime * numberOfUnits * 60) / 1000 };
    }

private:
    double operatingTime, bagFillTime, bagVolume, numberOfUnits;
};

#endif
