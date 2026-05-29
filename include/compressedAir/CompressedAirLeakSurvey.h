#pragma once

#include <cmath>
#include <exception>
#include <stdexcept>
#include <vector>

#include "compressedAir/bag_method.h"
#include "compressedAir/decibels_method.h"
#include "compressedAir/estimate_method.h"
#include "compressedAir/orifice_method.h"
#include "compressedAir/compressed_air_utils.h"

using compressed_air_utils::CompressorElectricityData;


class CompressedAirLeakSurveyInput {
  public:
    CompressedAirLeakSurveyInput(const int hoursPerYear, const int utilityType, const double utilityCost,
                                 const int measurementMethod, const estimate_method::Input estimateMethodInput,
                                 const decibels_method::Input decibelsMethodInput, const bag_method::Input bagMethodInput,
                                 const orifice_method::Input         orificeMethodInput,
                                 const CompressorElectricityData compressorElectricityData, const int units)
        : hoursPerYear(hoursPerYear), utilityType(utilityType), utilityCost(utilityCost),
          measurementMethod(measurementMethod), estimateMethodInput(estimateMethodInput),
          decibelsMethodInput(decibelsMethodInput), bagMethodInput(bagMethodInput),
          orificeMethodInput(orificeMethodInput), compressorElectricityData(compressorElectricityData), units(units) {}

    int                       getHoursPerYear() const { return hoursPerYear; } // operating time
    int                       getUtilityType() const { return utilityType; }
    int                       getMeasurementMethod() const { return measurementMethod; }
    int                       getUnits() const { return units; }
    double                    getUtilityCost() const { return utilityCost; }
    estimate_method::Input    getEstimateMethodInput() const { return estimateMethodInput; }
    decibels_method::Input    getDecibelsMethodInput() const { return decibelsMethodInput; }
    bag_method::Input         getBagMethodInput() const { return bagMethodInput; }
    orifice_method::Input     getOrificeMethodInput() const { return orificeMethodInput; }
    CompressorElectricityData getCompressorElectricityData() const { return compressorElectricityData; }

  private:
    int                       hoursPerYear, utilityType;
    double                    utilityCost;
    int                       measurementMethod;
    estimate_method::Input    estimateMethodInput;
    decibels_method::Input    decibelsMethodInput;
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
                auto debResult         = decibels_method::calculate(compressedAirLeakSurveyInput.getDecibelsMethodInput());
                tmpTotalFlowRate       = debResult.leak_rate_estimate * compressedAirLeakSurveyInput.getUnits();
                tmpAnnualTotalFlowRate = compressedAirLeakSurveyInput.getHoursPerYear() * tmpTotalFlowRate * 60;
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
