#pragma once

/**
 * @file
 * @brief Implementations of Bag Method of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#include <cmath>
#include <functional>
#include <stdexcept>
#include <vector>

class BagMethod {
  public:
    struct Output {
        Output(const double flowRate, const double annualConsumption)
            : flowRate(flowRate), annualConsumption(annualConsumption) {}

        const double flowRate, annualConsumption;
    };

    /**
     * Constructor for BagMethod - The bag method estimates the air flow using a trash bag by counting the time it
     * takes to fill it. This is the second most accurate means of measuring compressed air consumption.
     * @param operatingTime double, operating time of the system per year - hours
     * @param bagFillTime double, time that it takes for the bag to fill with air - seconds
     * @param bagVolume double, volume of the bag filler - cubic feet
     * @param numberOfUnits int, number of trash bags
     * @returns flowRate in scfm, annualConsumption in kscfm
     */
    BagMethod(double operatingTime, double bagFillTime, double bagVolume, int numberOfUnits)
        : operatingTime(operatingTime), bagFillTime(bagFillTime), bagVolume(bagVolume), numberOfUnits(numberOfUnits) {}

    /**
     * @return BagMethod::Output,
     * @param flowRate in scfm
     * @param annualConsumption in kscf
     */
    Output calculate() {
        auto const flowRate = bagVolume / (bagFillTime / 60);
        return {flowRate, (flowRate * operatingTime * numberOfUnits * 60) / 1000};
    }

  private:
    double operatingTime, bagFillTime, bagVolume, numberOfUnits;
};

