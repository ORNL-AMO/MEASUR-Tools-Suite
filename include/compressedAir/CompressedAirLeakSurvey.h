#ifndef TOOLS_SUITE_COMPRESSEDAIRLEAKSURVEY_H
#define TOOLS_SUITE_COMPRESSEDAIRLEAKSURVEY_H

#include <exception>
#include <stdexcept>
#include <vector>
#include "treasureHunt/CompressedAirReduction.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// BagMethodData implemented in CompressedAirReduction.h

class EstimateMethodData
{
  public:
    EstimateMethodData(const double leakRateEstimate) : leakRateEstimate(leakRateEstimate) {}

    double getLeakRateEstimate() const {return leakRateEstimate; }

  private:
    double leakRateEstimate;
};

class DecibelsMethodData
{
  public:
    DecibelsMethodData(const double linePressure, const double decibels, const double decibelRatingA, 
		  const double pressureA, const double firstFlowA, const double secondFlowA, const double decibelRatingB, const double pressureB,
		  const double firstFlowB, const double secondFlowB)
		  : linePressure(linePressure), decibels(decibels), decibelRatingA(decibelRatingA), 
		    pressureA(pressureA), firstFlowA(firstFlowA), secondFlowA(secondFlowA), decibelRatingB(decibelRatingB),
		    pressureB(pressureB), firstFlowB(firstFlowB), secondFlowB(secondFlowB) {}

    double calculate()
    {
        const double denominator = (pressureB - pressureA) * (decibelRatingB - decibelRatingA);
        const double leakRateEstimate = ((pressureB - linePressure) * (decibelRatingB - decibels)) / denominator * firstFlowA + ((linePressure - pressureA) * (decibelRatingB - decibels)) / denominator * secondFlowA + ((pressureB - linePressure) * (decibels - decibelRatingA)) / denominator * firstFlowB + ((linePressure - pressureA) * (decibels - decibelRatingA)) / denominator * secondFlowB;

        return leakRateEstimate;
    }

  private:
    double linePressure; // X
    double decibels; // Y
    double decibelRatingA; // Y1
    double pressureA; // X1
    double firstFlowA; // Q11
    double secondFlowA; // Q21
    double decibelRatingB; // Y2
    double pressureB; // X2
    double firstFlowB; // Q12
    double secondFlowB; // Q22
};

class OrificeMethodData
{
  public:
    OrificeMethodData(const double airTemp, const double atmPressure, const double dischargeCoef, const double diameter, 
                      const double supplyPressure, const int numOrifices)
			: airTemp(airTemp), atmPressure(atmPressure), dischargeCoef(dischargeCoef), diameter(diameter),
			  supplyPressure(supplyPressure), numOrifices(numOrifices) {}

    double calculate()
    {
        const double caPressurePSIA = atmPressure + supplyPressure;

        //convert to rankine for density calcs
        const double airTempRankine = airTemp + 459.67;

        const double caDensity = caPressurePSIA * 144 / (53.34 * airTempRankine);
        const double standardDensity = atmPressure * 144 / (53.34 * airTempRankine);
        const double sonicDensity = caDensity * std::pow((2 / 2.4), (1 / .4));

        const double leakVelocity = std::pow(((2 * 1.4) / (1.4 + 1)) * 53.34 * airTempRankine * 32.2, 0.5);
        const double leakRateLBMmin = sonicDensity * (diameter * diameter) * (M_PI / (4 * 144)) * leakVelocity * 60 * dischargeCoef;
        const double leakRateScfm = leakRateLBMmin / standardDensity;
        const double leakRateEstimate = leakRateScfm * numOrifices;
        return leakRateEstimate;
    }

  private:
    double airTemp, atmPressure, dischargeCoef, diameter, supplyPressure;
    int numOrifices;
};

class CompressedAirLeakSurveyInput
{
  public:
    CompressedAirLeakSurveyInput(const int hoursPerYear, const int utilityType, const double utilityCost, const int measurementMethod,
                                const EstimateMethodData estimateMethodData, const DecibelsMethodData decibelsMethodData, 
                                const BagMethodData bagMethodData, const OrificeMethodData orificeMethodData,  
                                const CompressorElectricityData compressorElectricityData, const int units)
        : hoursPerYear(hoursPerYear), utilityType(utilityType), utilityCost(utilityCost), measurementMethod(measurementMethod),
          estimateMethodData(estimateMethodData), decibelsMethodData(decibelsMethodData), bagMethodData(bagMethodData), 
          orificeMethodData(orificeMethodData), compressorElectricityData(compressorElectricityData), units(units) {}

    int getHoursPerYear() const { return hoursPerYear; } // operating time
    int getUtilityType() const { return utilityType; }
    int getMeasurementMethod() const { return measurementMethod; }
    int getUnits() const { return units; }
    double getUtilityCost() const { return utilityCost; }
    EstimateMethodData getEstimateMethodData() const { return estimateMethodData; }
    DecibelsMethodData getDecibelsMethodData() const { return decibelsMethodData; }
    BagMethodData getBagMethodData() const { return bagMethodData; }
    OrificeMethodData getOrificeMethodData() const { return orificeMethodData; }
    CompressorElectricityData getCompressorElectricityData() const { return compressorElectricityData; }

  private:
    int hoursPerYear, utilityType;
    double utilityCost;
    int measurementMethod;
    EstimateMethodData estimateMethodData;
    DecibelsMethodData decibelsMethodData;
    BagMethodData bagMethodData;
    OrificeMethodData orificeMethodData;
    CompressorElectricityData compressorElectricityData;
    int units;
};

class CompressedAirLeakSurvey
{
  public:
    struct Output
    {
        Output(double annualTotalElectricity, double annualTotalElectricityCost, double totalFlowRate, double annualTotalFlowRate)
            : annualTotalElectricity(annualTotalElectricity), annualTotalElectricityCost(annualTotalElectricityCost), 
              totalFlowRate(totalFlowRate), annualTotalFlowRate(annualTotalFlowRate) {}

        Output() = default;
        double annualTotalElectricity = 0, annualTotalElectricityCost = 0, totalFlowRate = 0, annualTotalFlowRate = 0;
    };

    CompressedAirLeakSurvey(std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec) : compressedAirLeakSurveyInputVec(compressedAirLeakSurveyInputVec)
    {
    }

    CompressedAirLeakSurvey::Output calculate()
    {
        double annualTotalElectricity = 0, annualTotalElectricityCost = 0, totalFlowRate = 0, annualTotalFlowRate = 0;

        for (auto &compressedAirLeakSurveyInput : compressedAirLeakSurveyInputVec)
        {
            double tmpAnnualTotalElectricity = 0, tmpAnnualTotalElectricityCost = 0, tmpTotalFlowRate = 0, tmpAnnualTotalFlowRate = 0;

            // estimate method
            if (compressedAirLeakSurveyInput.getMeasurementMethod() == 0)
            {
                EstimateMethodData estimateMethodData = compressedAirLeakSurveyInput.getEstimateMethodData();
                tmpTotalFlowRate = estimateMethodData.getLeakRateEstimate() * compressedAirLeakSurveyInput.getUnits();
                tmpAnnualTotalFlowRate = (compressedAirLeakSurveyInput.getHoursPerYear() * tmpTotalFlowRate * 60);
            }
                // decibels method
            else if (compressedAirLeakSurveyInput.getMeasurementMethod() == 1)
            {
                DecibelsMethodData decibelsMethodData = compressedAirLeakSurveyInput.getDecibelsMethodData();
                tmpTotalFlowRate = decibelsMethodData.calculate() * compressedAirLeakSurveyInput.getUnits();
                tmpAnnualTotalFlowRate = (compressedAirLeakSurveyInput.getHoursPerYear() * tmpTotalFlowRate * 60);
            }
                // bag method
            else if (compressedAirLeakSurveyInput.getMeasurementMethod() == 2)
            {
                BagMethodData bagMethodData = compressedAirLeakSurveyInput.getBagMethodData();
                tmpTotalFlowRate = ((60.0 / bagMethodData.getFillTime()) * M_PI * bagMethodData.getHeight() * pow((bagMethodData.getDiameter() / 2.0), 2.0) * (1.0 / pow(12.0, 3.0))) * compressedAirLeakSurveyInput.getUnits();
                tmpAnnualTotalFlowRate = tmpTotalFlowRate * 60.0 * compressedAirLeakSurveyInput.getHoursPerYear();
            }
                // orifice method
            else if (compressedAirLeakSurveyInput.getMeasurementMethod() == 3)
            {
                OrificeMethodData orificeMethodData = compressedAirLeakSurveyInput.getOrificeMethodData();
                tmpTotalFlowRate = orificeMethodData.calculate() * compressedAirLeakSurveyInput.getUnits();
                tmpAnnualTotalFlowRate = (compressedAirLeakSurveyInput.getHoursPerYear() * tmpTotalFlowRate * 60);
            }

            // compressed air
            if (compressedAirLeakSurveyInput.getUtilityType() == 0)
            {
                tmpAnnualTotalElectricityCost = compressedAirLeakSurveyInput.getUtilityCost() * tmpAnnualTotalFlowRate;
            }
                // electricity
            else if (compressedAirLeakSurveyInput.getUtilityType() == 1)
            {
                CompressorElectricityData compressorElectricityData = compressedAirLeakSurveyInput.getCompressorElectricityData();
                double electricityCalculation = compressorElectricityData.calculate();
                tmpAnnualTotalElectricity = electricityCalculation * tmpAnnualTotalFlowRate;
                tmpAnnualTotalElectricityCost = tmpAnnualTotalElectricity * compressedAirLeakSurveyInput.getUtilityCost();
            }
            annualTotalElectricity += tmpAnnualTotalElectricity;
            annualTotalElectricityCost += tmpAnnualTotalElectricityCost;
            totalFlowRate += tmpTotalFlowRate;
            annualTotalFlowRate += tmpAnnualTotalFlowRate;
        }

        return CompressedAirLeakSurvey::Output(annualTotalElectricity, annualTotalElectricityCost, totalFlowRate, annualTotalFlowRate);
    }
    std::vector<CompressedAirLeakSurveyInput> const &getCompressedAirLeakSurveyInputVec() const
    {
        return compressedAirLeakSurveyInputVec;
    }
    void setCompressedAirReductionInputVec(std::vector<CompressedAirReductionInput> &compressedAirReductionInputVec);

  private:
    std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec;
    CompressedAirLeakSurvey::Output output;
};

#endif