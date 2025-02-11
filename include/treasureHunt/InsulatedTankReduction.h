#ifndef TOOLS_SUITE_INSULATEDTANKCALCULATOR_H
#define TOOLS_SUITE_INSULATEDTANKCALCULATOR_H

#include <vector>
#include "InsulationFluidProperties.h"

class InsulatedTankOutput
{
public:
    InsulatedTankOutput();
    InsulatedTankOutput(double heatLoss, double annualHeatLoss) : _heatLoss(heatLoss), _annualHeatLoss(annualHeatLoss) {}

    double getHeatLoss()
    {
        return this->_heatLoss;
    }

    double getAnnualHeatLoss()
    {
        return this->_annualHeatLoss;
    }

    void setHeatLoss(double heatLoss)
    {
        this->_heatLoss = heatLoss;
    }

    void setAnnualHeatLoss(double annualHeatLoss)
    {
        this->_annualHeatLoss = annualHeatLoss;
    }

private:
    double _heatLoss;
    double _annualHeatLoss;
};

class InsulatedTankInput
{
public:
    InsulatedTankInput(
            int operatingHours,
            double tankHeight,
            double tankDiameter,
            double tankThickness,
            double tankEmissivity,
            double tankConductivity,
            double tankTemperature,
            double ambientTemperature,
            double systemEfficiency,
            double insulationThickness,
            double insulationConductivity,
            double jacketEmissivity,
            double surfaceTemperature)
            : _operatingHours(operatingHours),
              _tankHeight(tankHeight),
              _tankDiameter(tankDiameter),
              _tankThickness(tankThickness),
              _tankEmissivity(tankEmissivity),
              _tankConductivity(tankConductivity),
              _tankTemperature(tankTemperature),
              _ambientTemperature(ambientTemperature),
              _systemEfficiency(systemEfficiency),
              _insulationThickness(insulationThickness),
              _insulationConductivity(insulationConductivity),
              _jacketEmissivity(jacketEmissivity),
              _surfaceTemperature(surfaceTemperature){}

    int getOperatingHours()
    {
        return this->_operatingHours;
    }

    double getTankHeight()
    {
        return this->_tankHeight;
    }

    double getTankDiameter()
    {
        return this->_tankDiameter;
    }

    double getTankThickness()
    {
        return this->_tankThickness;
    }

    double getTankEmissivity()
    {
        return this->_tankEmissivity;
    }

    double getTankConductivity()
    {
        return this->_tankConductivity;
    }

    double getTankTemperature()
    {
        return this->_tankTemperature;
    }

    double getAmbientTemperature()
    {
        return this->_ambientTemperature;
    }

    double getSystemEfficiency()
    {
        return this->_systemEfficiency;
    }

    double getInsulationThickness()
    {
        return this->_insulationThickness;
    }

    double getInsulationConductivity()
    {
        return this->_insulationConductivity;
    }

    double getJacketEmissivity()
    {
        return this->_jacketEmissivity;
    }

    double getSurfaceTemperature()
    {
        return this->_surfaceTemperature;
    }

private:
    // InsulationFluidProperties _airProperties;
    int _operatingHours;
    double _tankHeight;
    double _tankDiameter;
    double _tankThickness;
    double _tankEmissivity;
    double _tankConductivity;
    double _tankTemperature;
    double _ambientTemperature;
    double _systemEfficiency;
    double _insulationThickness;
    double _insulationConductivity;
    double _jacketEmissivity;
    double _surfaceTemperature;
};

class InsulatedTankReduction
{
public:
    InsulatedTankReduction();
    InsulatedTankReduction(InsulatedTankInput insulatedTankInput) : _insulatedTankInput(insulatedTankInput) {}

    InsulatedTankOutput calculate();
    InsulatedTankOutput calculateNoInsulation(InsulatedTankInput input);
    InsulatedTankOutput calculateInsulation(InsulatedTankInput input);
    InsulationFluidProperties calculateAirProperties(double temp);
    double insulationRecursive();
    double noInsulationRecursive();
    double calculateAirProperty(int property, double temp);
    double lookupAirPropertyCoefficient(int property, int n);

private:
    void validateInput(InsulatedTankInput input);
    double propertyFit(std::vector<double> coefficients, double temp);

    InsulatedTankInput _insulatedTankInput;
    const double _airPropertiesArray[4][5] = {
        {-1.82109557e-14, 5.27958269e-11, -3.22287031e-8, 8.06185737e-6, 2.38303755e-1},  // specificHeat
        {5.53240532e-12, -2.97098117e-8, 5.96315645e-5, -5.57665211e-2, 2.43046430e1},     // density
        {-6.67800412e-13, 2.42855319e-9, 7.21312269e-8, 3.56111381e-3, -5.82727939e-1},      // kinViscosity
        {-1.63898601e-15, 7.98394765e-12, -1.80852621e-8, 3.85957991e-5, -1.49489778e-3}, // thermCond
    };
};

#endif