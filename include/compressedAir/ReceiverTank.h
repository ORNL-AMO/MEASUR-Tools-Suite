/**
 * @file
 * @brief Implementations of Receiver Tank of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_RECEIVERTANK_H
#define TOOLS_SUITE_RECEIVERTANK_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>

class ReceiverTank {
public:
    enum class Method {
        General,
        DedicatedStorage,
        MeteredStorage,
        BridgingCompressorReactionDelay
    };

    ReceiverTank() = default;

    /**
     * Constructor for ReceiverTank - This is required when we need to order a receiver tank to meet our compressed air requirements.
     * This calculator computes the quantity of compressed air that is actually available for use. When air receivers
     * are installed, the system’s pressure profile and lack of storage limit the effectiveness of compressed air energy
     * storage. Hence this calculator proves useful in such a context.
     * @param method ReceiverTank::Method, Calculation Method, in this case it must be General
     * @param airDemand const double, Amount of air needed, which comes out of the receiver tank - cubic ft
     * @param allowablePressureDrop const double, This decides the pressure drop inside the receiver tank that we can tolerate - psi
     * @param atmosphericPressure const double, This is generally 14.7 psi. In case the receiver tank is at higher altitude location, the respective atmospheric pressure at that location can be given - psi
     */
    ReceiverTank(Method method, double airDemand, double allowablePressureDrop, double atmosphericPressure)
            : method(method), airDemand(airDemand), allowablePressureDrop(allowablePressureDrop),
              atmosphericPressure(atmosphericPressure)
    {
        if (method != ReceiverTank::Method::General) {
            throw std::runtime_error("Calculation method must be set to General to use this constructor");
        }
    }

    /**
     * Constructor for ReceiverTank - This is required when we need to order a receiver tank to meet our compressed air requirements.
     * This calculator computes the quantity of compressed air that is actually available for use. When air receivers
     * are installed, the system’s pressure profile and lack of storage limit the effectiveness of compressed air energy
     * storage. Hence this calculator proves useful in such a context.
     * @param method ReceiverTank::Method, Calculation Method, in this case it must be DedicatedStorageMethod OR BridgingCompressorReactionDelay due to a C++ overloading limitation
     * @param lengthOfDemandOrDistanceToCompressorRoom const double, Time duration for which the compressed air is needed OR Distance of the event, that is removing the air, from the compressor room - minutes OR feet
     * @param airFlowRequirementOrSpeedOfAir const double, The quantity of air needed OR Flow rate of air from the tank - cfm OR ft/sec
     * @param atmosphericPressure const double, This is generally 14.7 psi. In case the receiver tank is at higher altitude location, the respective atmospheric pressure at that location can be given - psi
     * @param initialTankPressureOrAirDemand const double, Tank pressure before release of air OR Amount of air needed, which comes out of the receiver tank - psi OR cubic ft
     * @param finalTankPressureOrAllowablePressureDrop const double, Tank pressure after release of air OR This decides the pressure drop inside the receiver tank that we can tolerate - psi
     */
    ReceiverTank(Method method, double lengthOfDemandOrDistanceToCompressorRoom, double airFlowRequirementOrSpeedOfAir,
                 double atmosphericPressure, double initialTankPressureOrAirDemand, double finalTankPressureOrAllowablePressureDrop)
            : method(method), atmosphericPressure(atmosphericPressure),
              lengthOfDemandOrDistanceToCompressorRoom(lengthOfDemandOrDistanceToCompressorRoom),
              airFlowRequirementOrSpeedOfAir(airFlowRequirementOrSpeedOfAir),
              initialTankPressureOrAirDemand(initialTankPressureOrAirDemand),
              finalTankPressureOrAllowablePressureDrop(finalTankPressureOrAllowablePressureDrop)
    {
        if (method != ReceiverTank::Method::DedicatedStorage && method != ReceiverTank::Method::BridgingCompressorReactionDelay) {
            throw std::runtime_error("Calculation method must be set to DedicatedStorage or BridgingCompressorReactionDelay to use this constructor");
        }
    }

    /**
     * Constructor for ReceiverTank - This is required when we need to order a receiver tank to meet our compressed air requirements.
     * This calculator computes the quantity of compressed air that is actually available for use. When air receivers
     * are installed, the system’s pressure profile and lack of storage limit the effectiveness of compressed air energy
     * storage. Hence this calculator proves useful in such a context.
     * @param method ReceiverTank::Method, Calculation Method, in this case it must be MeteredStorage
     * @param lengthOfDemand const double, Time duration for which the compressed air is needed - minutes
     * @param airFlowRequirement const double, The quantity of air needed - cfm
     * @param atmosphericPressure const double, This is generally 14.7 psi. In case the receiver tank is at higher altitude location, the respective atmospheric pressure at that location can be given - psi
     * @param initialTankPressure const double, Tank pressure before release of air - psi
     * @param finalTankPressure const double, Tank pressure after release of air - psi
     * @param meteredFlowControl const double, Rate of flow through the metering valve (needle valve) - cfm
     */
    ReceiverTank(Method method, double lengthOfDemand, double airFlowRequirement, double atmosphericPressure,
                 double initialTankPressure, double finalTankPressure, double meteredFlowControl)
            : method(method), atmosphericPressure(atmosphericPressure), lengthOfDemandOrDistanceToCompressorRoom(lengthOfDemand),
              airFlowRequirementOrSpeedOfAir(airFlowRequirement), initialTankPressureOrAirDemand(initialTankPressure),
              finalTankPressureOrAllowablePressureDrop(finalTankPressure), meteredFlowControl(meteredFlowControl)
    {
        if (method != ReceiverTank::Method::MeteredStorage) {
            throw std::runtime_error("Calculation method must be set to MeteredStorage to use this constructor");
        }
    }

    /**
     * Calculates and returns receiver tank usable air capacity
     * @param tankSize double, Quantity of air it can hold - gallons
     * @param airPressureIn double, Pressure of air entering the Tank - psi
     * @param airPressureOut double, a.	Pressure of air leaving the Tank - psi
     * @return double, usable air storage capacity - scf
     */
    double calculateUsableCapacity(const double tankSize, const double airPressureIn, const double airPressureOut) {
        return (tankSize / 7.48) * (airPressureIn - airPressureOut) / 14.7;
    }

    /**
     * Calculates and returns receiver tank usable air capacity
     * @return double, receiver size - gallons
     */
    double calculateSize() {
        if (method == ReceiverTank::Method::General) {
            return airDemand * (atmosphericPressure / allowablePressureDrop) * 7.48;
        } else if (method == ReceiverTank::Method::DedicatedStorage) {
            return 7.48 * (lengthOfDemandOrDistanceToCompressorRoom * airFlowRequirementOrSpeedOfAir * atmosphericPressure)
                   / (initialTankPressureOrAirDemand - finalTankPressureOrAllowablePressureDrop);
        } else if (method == ReceiverTank::Method::MeteredStorage) {
            return (7.48 * lengthOfDemandOrDistanceToCompressorRoom * (airFlowRequirementOrSpeedOfAir - meteredFlowControl) * atmosphericPressure)
                   / (initialTankPressureOrAirDemand - finalTankPressureOrAllowablePressureDrop);
        }
        // method must be BridgingCompressorReactionDelay
        return (lengthOfDemandOrDistanceToCompressorRoom / airFlowRequirementOrSpeedOfAir) * (initialTankPressureOrAirDemand / 60)
               * (atmosphericPressure / finalTankPressureOrAllowablePressureDrop) * 7.48;
    }

private:
    Method method;
    double airDemand, allowablePressureDrop, atmosphericPressure;

    double lengthOfDemandOrDistanceToCompressorRoom, airFlowRequirementOrSpeedOfAir, initialTankPressureOrAirDemand;
    double finalTankPressureOrAllowablePressureDrop;

    double meteredFlowControl;
};

#endif
