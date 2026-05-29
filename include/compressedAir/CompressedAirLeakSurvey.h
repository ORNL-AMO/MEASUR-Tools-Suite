#pragma once

#include <cmath>
#include <exception>
#include <stdexcept>
#include <vector>

#include "compressedAir/bag_method.h"
#include "compressedAir/estimate_method.h"
#include "compressedAir/orifice_method.h"
#include "compressedAir/compressed_air_utils.h"

using compressed_air_utils::CompressorElectricityData;


class DecibelsMethodData {
  public:
    DecibelsMethodData(const double linePressure, const double decibels, const double decibelRatingA,
                       const double pressureA, const double firstFlowA, const double secondFlowA,
                       const double decibelRatingB, const double pressureB, const double firstFlowB,
                       const double secondFlowB)
        : linePressure(linePressure), decibels(decibels), decibelRatingA(decibelRatingA), pressureA(pressureA),
          firstFlowA(firstFlowA), secondFlowA(secondFlowA), decibelRatingB(decibelRatingB), pressureB(pressureB),
          firstFlowB(firstFlowB), secondFlowB(secondFlowB) {}

    double calculate() {
        const double denominator = (pressureB - pressureA) * (decibelRatingB - decibelRatingA);
        const double leakRateEstimate =
            ((pressureB - linePressure) * (decibelRatingB - decibels)) / denominator * firstFlowA +
            ((linePressure - pressureA) * (decibelRatingB - decibels)) / denominator * secondFlowA +
            ((pressureB - linePressure) * (decibels - decibelRatingA)) / denominator * firstFlowB +
            ((linePressure - pressureA) * (decibels - decibelRatingA)) / denominator * secondFlowB;

        return leakRateEstimate;
    }

  private:
    double linePressure;   // X
    double decibels;       // Y
    double decibelRatingA; // Y1
    double pressureA;      // X1
    double firstFlowA;     // Q11
    double secondFlowA;    // Q21
    double decibelRatingB; // Y2
    double pressureB;      // X2
    double firstFlowB;     // Q12
    double secondFlowB;    // Q22
};

class CompressedAirLeakSurveyInput {
  public:
    CompressedAirLeakSurveyInput(const int hoursPerYear, const int utilityType, const double utilityCost,
                                 const int measurementMethod, const estimate_method::Input estimateMethodInput,
                                 const DecibelsMethodData decibelsMethodData, const bag_method::Input bagMethodInput,
                                 const orifice_method::Input         orificeMethodInput,
                                 const CompressorElectricityData compressorElectricityData, const int units)
        : hoursPerYear(hoursPerYear), utilityType(utilityType), utilityCost(utilityCost),
          measurementMethod(measurementMethod), estimateMethodInput(estimateMethodInput),
          decibelsMethodData(decibelsMethodData), bagMethodInput(bagMethodInput),
          orificeMethodInput(orificeMethodInput), compressorElectricityData(compressorElectricityData), units(units) {}

    int                       getHoursPerYear() const { return hoursPerYear; } // operating time
    int                       getUtilityType() const { return utilityType; }
    int                       getMeasurementMethod() const { return measurementMethod; }
    int                       getUnits() const { return units; }
    double                    getUtilityCost() const { return utilityCost; }
    estimate_method::Input    getEstimateMethodInput() const { return estimateMethodInput; }
    DecibelsMethodData        getDecibelsMethodData() const { return decibelsMethodData; }
    bag_method::Input         getBagMethodInput() const { return bagMethodInput; }
    orifice_method::Input     getOrificeMethodInput() const { return orificeMethodInput; }
    CompressorElectricityData getCompressorElectricityData() const { return compressorElectricityData; }

  private:
    int                       hoursPerYear, utilityType;
    double                    utilityCost;
    int                       measurementMethod;
    estimate_method::Input    estimateMethodInput;
    DecibelsMethodData        decibelsMethodData;
    bag_method::Input         bagMethodInput;
    orifice_method::Input     orificeMethodInput;
    CompressorElectricityData compressorElectricityData;
    int                       units;
};

class CompressedAirLeakSurvey {
  public:
    struct Output {
        Output(double annualTotalElectricity, double annualTotalElectricityCost, double totalFlowRate,
               double annualTotalFlowRate)
            : annualTotalElectricity(annualTotalElectricity), annualTotalElectricityCost(annualTotalElectricityCost),
              totalFlowRate(totalFlowRate), annualTotalFlowRate(annualTotalFlowRate) {}

        Output()                      = default;
        double annualTotalElectricity = 0, annualTotalElectricityCost = 0, totalFlowRate = 0, annualTotalFlowRate = 0;
    };

    CompressedAirLeakSurvey(std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec)
        : compressedAirLeakSurveyInputVec(compressedAirLeakSurveyInputVec) {}

    CompressedAirLeakSurvey::Output calculate() {
        double annualTotalElectricity = 0, annualTotalElectricityCost = 0, totalFlowRate = 0, annualTotalFlowRate = 0;

        for (auto& compressedAirLeakSurveyInput : compressedAirLeakSurveyInputVec) {
            double tmpAnnualTotalElectricity = 0, tmpAnnualTotalElectricityCost = 0, tmpTotalFlowRate = 0,
                   tmpAnnualTotalFlowRate = 0;

            // estimate method
            if (compressedAirLeakSurveyInput.getMeasurementMethod() == 0) {
                auto estResult         = estimate_method::calculate(compressedAirLeakSurveyInput.getEstimateMethodInput());
                tmpTotalFlowRate       = compressedAirLeakSurveyInput.getEstimateMethodInput().leak_rate_estimate *
                                         compressedAirLeakSurveyInput.getUnits();
                tmpAnnualTotalFlowRate = estResult.annual_consumption * 1000.0 * compressedAirLeakSurveyInput.getUnits();
            }
            // decibels method
            else if (compressedAirLeakSurveyInput.getMeasurementMethod() == 1) {
                DecibelsMethodData decibelsMethodData = compressedAirLeakSurveyInput.getDecibelsMethodData();
                tmpTotalFlowRate       = decibelsMethodData.calculate() * compressedAirLeakSurveyInput.getUnits();
                tmpAnnualTotalFlowRate = (compressedAirLeakSurveyInput.getHoursPerYear() * tmpTotalFlowRate * 60);
            }
            // bag method
            else if (compressedAirLeakSurveyInput.getMeasurementMethod() == 2) {
                auto bagResult         = bag_method::calculate(compressedAirLeakSurveyInput.getBagMethodInput());
                tmpTotalFlowRate       = bagResult.flow_rate * compressedAirLeakSurveyInput.getUnits();
                tmpAnnualTotalFlowRate = bagResult.annual_consumption * compressedAirLeakSurveyInput.getUnits();
            }
            // orifice method
            else if (compressedAirLeakSurveyInput.getMeasurementMethod() == 3) {
                auto orfResult         = orifice_method::calculate(compressedAirLeakSurveyInput.getOrificeMethodInput());
                tmpTotalFlowRate       = orfResult.leak_rate_estimate * compressedAirLeakSurveyInput.getUnits();
                tmpAnnualTotalFlowRate = (compressedAirLeakSurveyInput.getHoursPerYear() * tmpTotalFlowRate * 60);
            }

            // compressed air
            if (compressedAirLeakSurveyInput.getUtilityType() == 0) {
                tmpAnnualTotalElectricityCost = compressedAirLeakSurveyInput.getUtilityCost() * tmpAnnualTotalFlowRate;
            }
            // electricity
            else if (compressedAirLeakSurveyInput.getUtilityType() == 1) {
                const CompressorElectricityData& ced = compressedAirLeakSurveyInput.getCompressorElectricityData();
                tmpAnnualTotalElectricity     = (ced.compressor_specific_power / 60.0) * tmpAnnualTotalFlowRate;
                tmpAnnualTotalElectricityCost = tmpAnnualTotalElectricity * compressedAirLeakSurveyInput.getUtilityCost();
            }
            annualTotalElectricity += tmpAnnualTotalElectricity;
            annualTotalElectricityCost += tmpAnnualTotalElectricityCost;
            totalFlowRate += tmpTotalFlowRate;
            annualTotalFlowRate += tmpAnnualTotalFlowRate;
        }

        return CompressedAirLeakSurvey::Output(annualTotalElectricity, annualTotalElectricityCost, totalFlowRate,
                                               annualTotalFlowRate);
    }
    std::vector<CompressedAirLeakSurveyInput> const& getCompressedAirLeakSurveyInputVec() const {
        return compressedAirLeakSurveyInputVec;
    }

  private:
    std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec;
    CompressedAirLeakSurvey::Output           output;
};
