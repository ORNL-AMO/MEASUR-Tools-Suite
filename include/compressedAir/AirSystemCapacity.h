/**
 * @file
 * @brief Implementations of Air System Capacity of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_AIRSYSTEMCAPACITY_H
#define TOOLS_SUITE_AIRSYSTEMCAPACITY_H

#include "PipeData.h"

class AirSystemCapacity {
public:
    struct Output {
        Output(const double totalPipeVolume, std::vector<double> receiverCapacities,
               const double totalReceiverVol, const double totalCapacityOfCompressedAirSystem,
               PipeData pipeLengths)
                : totalPipeVolume(totalPipeVolume), totalReceiverVol(totalReceiverVol),
                  totalCapacityOfCompressedAirSystem(totalCapacityOfCompressedAirSystem),
                  receiverCapacities(std::move(receiverCapacities)), pipeLengths(pipeLengths)
        {}

        const double totalPipeVolume, totalReceiverVol, totalCapacityOfCompressedAirSystem;
        const std::vector<double> receiverCapacities;
        const PipeData pipeLengths;
    };

    /**
     * Constructor for AirSystemCapacity - This is used to find the total air quantity that the
     * compressed air system can contain at any instant of time, including the air in the pipes and receivers.
     * @param pipeLengths AirSystemCapacity::PipeLengths, Object containing the lengths of the various pipe sizes in your system - ft
     * @param receivers std::vector<double>, a vector containing the number of gallons in each receiver
     */
    AirSystemCapacity(PipeData pipeLengths, std::vector<double> receivers)
            : pipeLengths(pipeLengths), receivers(std::move(receivers))
    {}

    Output calculate() {

        auto totalReceiverVol = 0.0;
        for (auto & gallons : receivers) {
            gallons /= 7.480515625;
            totalReceiverVol += gallons;
        }

        return {pipeLengths.totalPipeVolume, receivers, totalReceiverVol,
                pipeLengths.totalPipeVolume + totalReceiverVol, pipeLengths};
    }

private:
    PipeData pipeLengths;
    std::vector<double> receivers;
};

#endif
