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
     * @param heightOfBag double, height of the bag - inches
     * @param diameterOfBag double, diameter of the bag - inches
     * @param numberOfUnits int, number of trash bags
     */
    BagMethod(double operatingTime, double bagFillTime, double heightOfBag, double diameterOfBag, int numberOfUnits)
            : operatingTime(operatingTime), bagFillTime(bagFillTime),
              heightOfBag(heightOfBag), diameterOfBag(diameterOfBag), numberOfUnits(numberOfUnits)
    {}

    /**
     * @return BagMethod::Output, flowRate and annual consumption
     */
    Output calculate() {
        auto const flowRate = (0.0273 * std::pow(diameterOfBag, 2) * heightOfBag) / bagFillTime;
        return {flowRate, (flowRate * operatingTime * numberOfUnits * 60) / 1000 };
    }

private:
    double operatingTime, bagFillTime, heightOfBag, diameterOfBag, numberOfUnits;
};

#endif
