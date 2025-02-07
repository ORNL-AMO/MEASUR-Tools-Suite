#ifndef TOOLS_SUITE_INSULATEDPIPECALCULATOR_H
#define TOOLS_SUITE_INSULATEDPIPECALCULATOR_H

#include <vector>
#include "InsulationFluidProperties.h"

class InsulatedPipeInput
{
public:
    /**
        Outline of expected input units:
            pipeLength: meters (m)
            diameter: millimeters (mm)
            pipeTemperature: Kelvin (K)
            ambientTemperature: Kelvin (K)
            windVelocity: meters/second (m/s)
            systemEfficiency: fraction (0-1.0)
            insulationThickness: meters (m)
    */
    InsulatedPipeInput(
            int operatingHours,
            double pipeLength,
            double pipeDiameter,
            double pipeThickness,
            double pipeTemperature,
            double ambientTemperature,
            double windVelocity,
            double systemEfficiency,
            double insulationThickness,
            double pipeEmissivity,
            double jacketEmissivity,
            std::vector<double> pipeMaterialCoefficients,
            std::vector<double> insulationMaterialCoefficients)
            : _operatingHours(operatingHours),
              _pipeLength(pipeLength),
              _pipeDiameter(pipeDiameter),
              _pipeThickness(pipeThickness),
              _pipeTemperature(pipeTemperature),
              _ambientTemperature(ambientTemperature),
              _windVelocity(windVelocity),
              _systemEfficiency(systemEfficiency),
              _insulationThickness(insulationThickness),
              _pipeEmissivity(pipeEmissivity),
              _jacketEmissivity(jacketEmissivity),
              _pipeMaterialCoefficients(pipeMaterialCoefficients),
              _insulationMaterialCoefficients(insulationMaterialCoefficients) {}

    int getOperatingHours()
    {
        return this->_operatingHours;
    }

    double getPipeLength()
    {
        return this->_pipeLength;
    }

    double getPipeDiameter()
    {
        return this->_pipeDiameter;
    }

    double getPipeThickness()
    {
        return this->_pipeThickness;
    }

    double getPipeTemperature()
    {
        return this->_pipeTemperature;
    }

    double getAmbientTemperature()
    {
        return this->_ambientTemperature;
    }

    double getWindVelocity()
    {
        return this->_windVelocity;
    }

    double getSystemEfficiency()
    {
        return this->_systemEfficiency;
    }

    double getInsulationThickness()
    {
        return this->_insulationThickness;
    }

    double getPipeEmissivity()
    {
        return this->_pipeEmissivity;
    }

    double getJacketEmissivity()
    {
        return this->_jacketEmissivity;
    }

    std::vector<double> getPipeMaterialCoefficients()
    {
        return this->_pipeMaterialCoefficients;
    }

    std::vector<double> getInsulationMaterialCoefficients()
    {
        return this->_insulationMaterialCoefficients;
    }

private:
    InsulationFluidProperties _airProperties;
    int _operatingHours;
    double _pipeLength;
    double _pipeDiameter;
    double _pipeThickness;
    double _pipeTemperature;
    double _ambientTemperature;
    double _windVelocity;
    double _systemEfficiency;
    double _insulationThickness;
    double _pipeEmissivity;
    double _jacketEmissivity;
    std::vector<double> _pipeMaterialCoefficients;
    std::vector<double> _insulationMaterialCoefficients;
};

class InsulatedPipeOutput
{
public:
    InsulatedPipeOutput();
    InsulatedPipeOutput(double heatLength, double annualHeatLoss) : _heatLength(heatLength), _annualHeatLoss(annualHeatLoss) {}

    double getHeatLength()
    {
        return this->_heatLength;
    }

    double getAnnualHeatLoss()
    {
        return this->_annualHeatLoss;
    }

    void setHeatLength(double heatLength)
    {
        this->_heatLength = heatLength;
    }

    void setAnnualHeatLoss(double annualHeatLoss)
    {
        this->_annualHeatLoss = annualHeatLoss;
    }

private:
    double _heatLength;
    double _annualHeatLoss;
};

class InsulatedPipeReduction
{
public:
    InsulatedPipeReduction();
    InsulatedPipeReduction(InsulatedPipeInput insulatedPipeInput) : _insulatedPipeInput(insulatedPipeInput) {}

    InsulatedPipeOutput calculate();
    InsulationFluidProperties calculateAirProperties(double temp);
    InsulatedPipeOutput calculateNoInsulation(InsulatedPipeInput input);
    InsulatedPipeOutput calculateInsulation(InsulatedPipeInput input);
    double insulationRecursive(InsulatedPipeInput input, double innerPipeDiameter, double insulationOuterDiameter, double surfaceTemperature, double interfaceTemperature, double heatLength, int i);
    double noInsulationRecursive(InsulatedPipeInput input, double innerPipeDiameter, double insulationOuterDiameter, double surfaceTemperature, double interfaceTemperature, double heatLength, int i);
    double calculateAirProperty(int property, double temp);
    double lookupAirPropertyCoefficient(int property, int n);
    const double *lookupAirProperty(int property);

    static double calculateThermalResistance(double diameterA, double diameterB, double diameterC, double thermalConductivity);
    static double calculateReynoldsNumber(double diameter, double windVelocity, double kinematicViscosity);
    static double calculateRayleighNumber(double expCoefficient, double surfaceTemperature, double ambientTemperature, double diameter, double kinematicViscosity, double alpha);
    static double calculateNusseltNumber(double a, double b);
    static double calculateNusseltForcedConvection(double a, double b);
    static double calculateNusseltFreeConvection(double a, double b);
    static double calculateRadiativeHeatTransferCoefficient(double emissivity, double surfaceTemperature, double ambientTemperature);
    static double calculateConvectiveHeatTransferCoefficient(double nusselt, double airConductivity, double diameter);

private:
    void validateInput(InsulatedPipeInput input);
    double propertyFit(std::vector<double> coefficients, double temp);

    InsulatedPipeInput _insulatedPipeInput;
    const double _airPropertiesArray[6][5] = {
        {3.03724e-13, -1.1132e-9, 1.44382e-6, -0.000565339, 1.07223839},     // specificHeat
        {-1.586e-10, 5.115e-7, -7.246e-4, 7.978e-1, -1.850},                 // viscosity
        {2.25852e-11, -8.32093e-8, 0.000172673, 0.01063728, -0.76108359},    // kinViscosity
        {3.17176E-11, -5.90229E-08, 4.58531E-06, 0.088867888, 0.520072239},  // thermCond
        {1.35569E-10, -3.80588E-07, 0.000446483, -0.035935528, 2.254489164}, // Alpha
        {-2.08438E-13, -1.72787E-11, 8.00624E-07, -0.000694606, 0.845781218} // Prandtl
    };
};

#endif