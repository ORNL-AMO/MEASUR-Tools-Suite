#pragma once

#include <iostream>

/**
 * Steam Modeler boiler input data.
 */

class BoilerInput {
  public:
    BoilerInput(double fuelType, double fuel, double combustionEfficiency, double blowdownRate, bool blowdownFlashed,
                bool preheatMakeupWater, double steamTemperature, double deaeratorVentRate, double deaeratorPressure,
                double approachTemperature, bool sendBlowdownToDeaerator);

    friend std::ostream& operator<<(std::ostream& stream, const BoilerInput& bi);

    double getFuelType() const;

    double getFuel() const;

    double getCombustionEfficiency() const;

    double getBlowdownRate() const;

    bool isBlowdownFlashed() const;

    bool isPreheatMakeupWater() const;

    double getSteamTemperature() const;

    double getDeaeratorVentRate() const;

    double getDeaeratorPressure() const;

    double getApproachTemperature() const;

    bool isSendBlowdownToDeaerator() const;

  private:
    double fuelType;
    double fuel;
    double combustionEfficiency;
    double blowdownRate;
    bool   blowdownFlashed;
    bool   preheatMakeupWater;
    double steamTemperature;
    double deaeratorVentRate;
    double deaeratorPressure;
    double approachTemperature;
    bool   sendBlowdownToDeaerator = false;
};

