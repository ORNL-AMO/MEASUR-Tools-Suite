#include "steamModeler/api/BoilerInput.h"

BoilerInput::BoilerInput(const double fuelType, const double fuel, const double combustionEfficiency,
                         const double blowdownRate, const bool blowdownFlashed, const bool preheatMakeupWater,
                         const double steamTemperature, const double deaeratorVentRate, const double deaeratorPressure,
                         const double approachTemperature, const bool sendBlowdownToDeaerator)
    : fuelType(fuelType), fuel(fuel), combustionEfficiency(combustionEfficiency), blowdownRate(blowdownRate),
      blowdownFlashed(blowdownFlashed), preheatMakeupWater(preheatMakeupWater), steamTemperature(steamTemperature),
      deaeratorVentRate(deaeratorVentRate), deaeratorPressure(deaeratorPressure),
      approachTemperature(approachTemperature), sendBlowdownToDeaerator(sendBlowdownToDeaerator) {}

std::ostream& operator<<(std::ostream& stream, const BoilerInput& bi) {
    return stream << "BoilerInput[" << "fuelType=" << bi.fuelType << ", fuel=" << bi.fuel
                  << ", combustionEfficiency=" << bi.combustionEfficiency << ", blowdownRate=" << bi.blowdownRate
                  << ", blowdownFlashed=" << bi.blowdownFlashed << ", preheatMakeupWater=" << bi.preheatMakeupWater
                  << ", steamTemperature=" << bi.steamTemperature << ", deaeratorVentRate=" << bi.deaeratorVentRate
                  << ", deaeratorPressure=" << bi.deaeratorPressure
                  << ", approachTemperature=" << bi.approachTemperature
                  << ", sendBlowdownToDeaerator=" << bi.sendBlowdownToDeaerator << "]";
}

double BoilerInput::getFuelType() const { return fuelType; }

double BoilerInput::getFuel() const { return fuel; }

double BoilerInput::getCombustionEfficiency() const { return combustionEfficiency; }

double BoilerInput::getBlowdownRate() const { return blowdownRate; }

bool BoilerInput::isBlowdownFlashed() const { return blowdownFlashed; }

bool BoilerInput::isPreheatMakeupWater() const { return preheatMakeupWater; }

double BoilerInput::getSteamTemperature() const { return steamTemperature; }

double BoilerInput::getDeaeratorVentRate() const { return deaeratorVentRate; }

double BoilerInput::getDeaeratorPressure() const { return deaeratorPressure; }

double BoilerInput::getApproachTemperature() const { return approachTemperature; }

bool BoilerInput::isSendBlowdownToDeaerator() const { return sendBlowdownToDeaerator; };
