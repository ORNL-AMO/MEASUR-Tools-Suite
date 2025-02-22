#ifndef TOOLS_SUITE_COMPRESSEDAIRPRESSUREREDUCTION_H
#define TOOLS_SUITE_COMPRESSEDAIRPRESSUREREDUCTION_H

#include <exception>
#include <stdexcept>
#include <vector>

class CompressedAirPressureReductionInput
{
  public:
        /**
        * @param isBaseline boolean
        * @param hoursPerYear int
        * @param electricityCost double
        * @param compressorPower double, kWh
        * @param pressure double, barg
        * @param proposedPressure double, barg
        * @param atmosphericPressure double, bara
        * @param pressureRated double, barg
        */
    CompressedAirPressureReductionInput(const bool isBaseline, const int hoursPerYear,
                                        const double electricityCost, const double compressorPower,
                                        const double pressure, const double proposedPressure,
                                        const double atmosphericPressure, double const pressureRated)
        : isBaseline(isBaseline), hoursPerYear(hoursPerYear), electricityCost(electricityCost),
          compressorPower(compressorPower), pressure(pressure), proposedPressure(proposedPressure),
          pressureRated(pressureRated), atmosphericPressure(atmosphericPressure) {}

    bool getIsBaseline() const { return isBaseline; }
    int getHoursPerYear() const { return hoursPerYear; }
    double getElectricityCost() const { return electricityCost; }
    double getCompressorPower() const { return compressorPower; }
    double getPressure() const { return pressure; }
    double getProposedPressure() const { return proposedPressure; }
    double getAtmosphericPressure() const { return atmosphericPressure; }
    double getPressureRated() const { return pressureRated; }

  private:
    bool isBaseline;
    int hoursPerYear;
    double electricityCost, compressorPower, pressure, proposedPressure, pressureRated, atmosphericPressure;
};

class CompressedAirPressureReduction
{
  public:
    struct Output
    {
        Output(double energyUse, double energyCost)
            : energyUse(energyUse), energyCost(energyCost) {}

        Output() = default;
        double energyUse = 0, energyCost = 0;
    };

    CompressedAirPressureReduction(std::vector<CompressedAirPressureReductionInput> compressedAirPressureReductionInputVec) : compressedAirPressureReductionInputVec(compressedAirPressureReductionInputVec)
    {
    }

    CompressedAirPressureReduction::Output calculate();

    std::vector<CompressedAirPressureReductionInput> const &getCompressedAirPressureReductionInputVec()
    {
        return compressedAirPressureReductionInputVec;
    }
    void setCompressedAirPressureReductionInputVec(std::vector<CompressedAirPressureReductionInput> &compressedAirPressureReductionInputVec);

  private:
    std::vector<CompressedAirPressureReductionInput> compressedAirPressureReductionInputVec;
    CompressedAirPressureReduction::Output output;
};

#endif // TOOLS_SUITE_COMPRESSEDAIRPRESSUREREDUCTION_H