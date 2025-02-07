#include "treasureHunt/InsulatedPipeReduction.h"
#include "treasureHunt/InsulationFluidProperties.h"
#include <cmath>
#include <vector>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

InsulatedPipeOutput InsulatedPipeReduction::calculate()
{
    InsulatedPipeInput input = this->_insulatedPipeInput;
    this->validateInput(input);

    // if -1, then no insulation was provided
    if (this->_insulatedPipeInput.getInsulationThickness() <= 0)
    {
        return InsulatedPipeReduction::calculateNoInsulation(input);
    }
    else
    {
        return InsulatedPipeReduction::calculateInsulation(input);
    }
}

//check if emissivity values are out of expected range and throw error
void InsulatedPipeReduction::validateInput(InsulatedPipeInput input)
{
    if (input.getPipeEmissivity() < 0.0 || input.getPipeEmissivity() > 1.0)
    {
        throw "ERROR : Pipe - pipe emissivity out of acceptable range";
    }
    if (input.getJacketEmissivity() < 0.0 || input.getJacketEmissivity() > 1.0)
    {
        throw "ERROR : Pipe - jacket emissivity out of acceptable range";
    }
    if (input.getPipeMaterialCoefficients().size() != 5)
    {
        throw "ERROR : Pipe - expected exactly 5 pipe material coefficients, received " + std::to_string(input.getPipeMaterialCoefficients().size());
    }
    if (input.getInsulationMaterialCoefficients().size() != 5)
    {
        throw "ERROR : Pipe - expected exactly 5 insulation material coefficients, received " + std::to_string(input.getInsulationMaterialCoefficients().size());
    }
}

InsulatedPipeOutput InsulatedPipeReduction::calculateInsulation(InsulatedPipeInput input)
{
    double innerPipeDiameter;
    double outerInsulationDiameter;
    double surfaceTemperature;
    double interfaceTemperature;
    double heatLength;
    double annualHeatLoss;
    innerPipeDiameter = input.getPipeDiameter() - input.getPipeThickness();
    outerInsulationDiameter = input.getPipeDiameter() + (2.0 * input.getInsulationThickness());
    surfaceTemperature = input.getAmbientTemperature() + 1.0;
    interfaceTemperature = input.getPipeTemperature() - 1.0;

    //start iteration
    heatLength = InsulatedPipeReduction::insulationRecursive(input, innerPipeDiameter, outerInsulationDiameter, surfaceTemperature, interfaceTemperature, 0, 0);
    annualHeatLoss = heatLength * input.getPipeLength() * input.getOperatingHours() / input.getSystemEfficiency();
    return InsulatedPipeOutput(heatLength, annualHeatLoss);
}

double InsulatedPipeReduction::insulationRecursive(InsulatedPipeInput input, double innerPipeDiameter, double insulationOuterDiameter, double surfaceTemperature, double interfaceTemperature, double heatLength, int i)
{
    double filmTemperature;
    filmTemperature = (surfaceTemperature + input.getAmbientTemperature()) / 2.0;

    //step 1: establish air properties
    InsulationFluidProperties airProperties = InsulatedPipeReduction::calculateAirProperties(filmTemperature);

    //step 2: air film resistance
    double insReynolds = calculateReynoldsNumber(insulationOuterDiameter, input.getWindVelocity(), airProperties.getKinViscosity());
    double insRayleigh = calculateRayleighNumber(airProperties.getExpansionCoefficient(), surfaceTemperature, input.getAmbientTemperature(),
                                        insulationOuterDiameter, airProperties.getKinViscosity(), airProperties.getAlpha());
    double insHeatRadiation = calculateRadiativeHeatTransferCoefficient(input.getJacketEmissivity(), surfaceTemperature, input.getAmbientTemperature());
    double insNusseltForced = calculateNusseltForcedConvection(insReynolds, airProperties.getPrandtl());
    double insNusseltFree = calculateNusseltFreeConvection(insRayleigh, airProperties.getPrandtl());
    double insNusseltCombined = calculateNusseltNumber(insNusseltForced, insNusseltFree);
    double insConvectionCombined = calculateConvectiveHeatTransferCoefficient(insNusseltCombined, airProperties.getConductivity(), insulationOuterDiameter);
    double insHeatAir = insHeatRadiation + insConvectionCombined;

    //step 3: pipe resistance
    double kPipe = this->propertyFit(input.getPipeMaterialCoefficients(), input.getPipeTemperature());
    double pipeResistance = calculateThermalResistance(insulationOuterDiameter, input.getPipeDiameter(), innerPipeDiameter, kPipe);

    //step 4: insulation resistance
    double insulationTemperature = (surfaceTemperature + interfaceTemperature) / 2.0;
    double kInsulation = this->propertyFit(input.getInsulationMaterialCoefficients(), insulationTemperature);
    double insulationResistance = calculateThermalResistance(insulationOuterDiameter, insulationOuterDiameter, input.getPipeDiameter(), kInsulation);

    //step 5: overall resistance
    double overallResistance = insulationResistance + pipeResistance + (1.0 / insHeatAir);
    double heatFlow = (input.getPipeTemperature() - input.getAmbientTemperature()) / overallResistance;

    //step 6: rewriting interfaceTemp & surfaceTemp
    interfaceTemperature = input.getPipeTemperature() - (heatFlow * pipeResistance);
    surfaceTemperature = interfaceTemperature - (heatFlow * insulationResistance);
    double heatLengthNew = heatFlow * M_PI * insulationOuterDiameter;

    if (std::fabs(heatLengthNew - heatLength) < 0.0001)
    {
        return (heatLength + heatLengthNew) / 2.0;
    }
    else if (i > 30)
    {
        throw "ERROR : Pipe, Insulation - recursion limit exceeded";
    }
    else
    {
        i = i + 1;
        return InsulatedPipeReduction::insulationRecursive(input, innerPipeDiameter, insulationOuterDiameter, surfaceTemperature, interfaceTemperature, heatLengthNew, i);
    }
}

InsulatedPipeOutput InsulatedPipeReduction::calculateNoInsulation(InsulatedPipeInput input)
{
    double innerPipeDiameter;
    double insulationOuterDiameter;
    double surfaceTemperature;
    double interfaceTemperature;
    double heatLength;
    double annualHeatLoss;
    innerPipeDiameter = input.getPipeDiameter() - input.getPipeThickness();
    insulationOuterDiameter = input.getPipeDiameter() + (2.0 * input.getInsulationThickness());
    surfaceTemperature = input.getAmbientTemperature() + 1.0;
    interfaceTemperature = input.getPipeTemperature() - 1.0;

    //start iteration
    heatLength = InsulatedPipeReduction::noInsulationRecursive(input, innerPipeDiameter, insulationOuterDiameter, surfaceTemperature, interfaceTemperature, 0.0, 0);
    annualHeatLoss = heatLength * input.getPipeLength() * input.getOperatingHours() / input.getSystemEfficiency();
    return InsulatedPipeOutput(heatLength, annualHeatLoss);
}

double InsulatedPipeReduction::noInsulationRecursive(InsulatedPipeInput input, double innerPipeDiameter, double insulationOuterDiameter, double surfaceTemperature, double interfaceTemperature, double heatLength, int i)
{
    double filmTemperature;
    filmTemperature = (surfaceTemperature + input.getAmbientTemperature()) / 2.0;
    //step 1: establish air properties
    InsulationFluidProperties airProperties = InsulatedPipeReduction::calculateAirProperties(filmTemperature);

    //step 2: air film resistance
    double bareReynolds = calculateReynoldsNumber(input.getPipeDiameter(), input.getWindVelocity(), airProperties.getKinViscosity());
    double bareRayleigh = calculateRayleighNumber(airProperties.getExpansionCoefficient(), surfaceTemperature, input.getAmbientTemperature(),
                                                                input.getPipeDiameter(), airProperties.getKinViscosity(), airProperties.getAlpha());
    double bareRadiativeHeatTransferCoefficient = calculateRadiativeHeatTransferCoefficient(input.getPipeEmissivity(), surfaceTemperature, input.getAmbientTemperature());
    double bareNusseltForced = calculateNusseltForcedConvection(bareReynolds, airProperties.getPrandtl());
    double bareNusseltFree = calculateNusseltFreeConvection(bareRayleigh, airProperties.getPrandtl());
    double bareNusseltCombined = calculateNusseltNumber(bareNusseltForced, bareNusseltFree);
    double bareConvection = calculateConvectiveHeatTransferCoefficient(bareNusseltCombined, airProperties.getConductivity(), input.getPipeDiameter());
    double bareHeatTransferAir = bareRadiativeHeatTransferCoefficient + bareConvection;

    //step 3: pipe resistance
    double kPipe = this->propertyFit(input.getPipeMaterialCoefficients(), input.getPipeTemperature());
    double pipeResistance = calculateThermalResistance(input.getPipeDiameter(), input.getPipeDiameter(), innerPipeDiameter, kPipe);

    //step 4: overall resistance
    double overallResistance = pipeResistance + 1 / bareHeatTransferAir;
    double heatFlow = (input.getPipeTemperature() - input.getAmbientTemperature()) / overallResistance;

    //step 5: rewriting interfaceTemperature && surfaceTemperature;
    interfaceTemperature = input.getPipeTemperature() - heatFlow * pipeResistance;
    surfaceTemperature = interfaceTemperature - (heatFlow * 0);
    double heatLengthNew = heatFlow * M_PI * input.getPipeDiameter();

    if (std::fabs(heatLengthNew - heatLength) < 0.0001)
    {
        return (heatLength + heatLengthNew) / 2.0;
    }
    else if (i > 30)
    {
        throw "ERROR : Pipe, No Insulation - recursion limit exceeded";
    }
    else
    {
        return InsulatedPipeReduction::noInsulationRecursive(input, innerPipeDiameter, insulationOuterDiameter, surfaceTemperature, interfaceTemperature, heatLengthNew, i++);
    }
}

InsulationFluidProperties InsulatedPipeReduction::calculateAirProperties(double temp)
{
    double airConductivity = this->calculateAirProperty(3, temp) / 1e3;
    double airViscosity = this->calculateAirProperty(1, temp) / 1e7;
    double airPrandtl = this->calculateAirProperty(5, temp);
    double airExpansionCoefficient = 1.0 / temp;
    double airDensity = 29.0 / 0.0820575 / temp;
    double airKinViscosity = this->calculateAirProperty(2, temp) / 1e6;
    double airSpecificHeat = this->calculateAirProperty(0, temp);
    double airAlpha = this->calculateAirProperty(4, temp) / 1e6;
    return InsulationFluidProperties(airConductivity, airViscosity, airPrandtl, airExpansionCoefficient, airDensity, airKinViscosity, airSpecificHeat, airAlpha, 0, 0);
}

double InsulatedPipeReduction::calculateAirProperty(int property, double temp)
{
    std::vector<double> coefficients = {
            InsulatedPipeReduction::lookupAirPropertyCoefficient(property, 0),
            InsulatedPipeReduction::lookupAirPropertyCoefficient(property, 1),
            InsulatedPipeReduction::lookupAirPropertyCoefficient(property, 2),
            InsulatedPipeReduction::lookupAirPropertyCoefficient(property, 3),
            InsulatedPipeReduction::lookupAirPropertyCoefficient(property, 4)};
    return this->propertyFit(coefficients, temp);
}

double InsulatedPipeReduction::propertyFit(std::vector<double> coefficients, double temp)
{
    double property;
    double order4 = coefficients.at(0) * std::pow(temp, 4);
    double order3 = coefficients.at(1) * std::pow(temp, 3);
    double order2 = coefficients.at(2) * std::pow(temp, 2);
    double order1 = coefficients.at(3) * temp;
    double order0 = coefficients.at(4);
    property = order4 + order3 + order2 + order1 + order0;
    return property;
}

double InsulatedPipeReduction::lookupAirPropertyCoefficient(int property, int n)
{
    return this->_airPropertiesArray[property][n];
}

const double *InsulatedPipeReduction::lookupAirProperty(int property)
{
    return this->_airPropertiesArray[property];
}

double InsulatedPipeReduction::calculateThermalResistance(double diameterA, double diameterB, double diameterC, double thermalConductivity) {
    return diameterA * std::log(diameterB / diameterC) / (2.0 * thermalConductivity);
}

double InsulatedPipeReduction::calculateReynoldsNumber(double diameter, double windVelocity, double kinematicViscosity) {
    return diameter * windVelocity / kinematicViscosity;
}

double InsulatedPipeReduction::calculateRayleighNumber(double expCoefficient, double surfaceTemperature, double ambientTemperature, double diameter, double kinematicViscosity, double alpha) {
    double g = 9.81;
    double absTempDifference = std::fabs(surfaceTemperature - ambientTemperature);
    double diameterCubed = std::pow(diameter, 3);
    double kinVisAlpha = kinematicViscosity * alpha;
    double coeff = g * expCoefficient;
    double result = coeff * absTempDifference * diameterCubed / kinVisAlpha;
    return result;
}

double InsulatedPipeReduction::calculateNusseltNumber(double a, double b)
{
    double powa = std::pow(a, 4);
    double powb = std::pow(b, 4);
    double sum = powa + powb;
    double result = std::pow(sum, 1.0 / 4.0);
    return result;
}

double InsulatedPipeReduction::calculateNusseltForcedConvection(double a, double b)
{
    double step1 = std::pow(a, 1.0 / 2.0);
    double step2 = step1 * 0.62;
    double step3 = step2 * std::pow(b, 1.0 / 3.0);

    double step4 = std::pow(a / 282000.0, 5.0 / 8.0);
    double step5 = step4 + 1.0;
    double step6 = std::pow(step5, 4.0 / 5.0);

    double step7 = std::pow(0.4 / b, 2.0 / 3.0);
    double step8 = step7 + 1.0;
    double step9 = std::pow(step8, 1.0 / 4.0);

    double step10 = step3 * step6 / step9;
    double step11 = step10 + 0.3;

    return step11;
}

double InsulatedPipeReduction::calculateNusseltFreeConvection(double a, double b)
{
    double step1 = std::pow(a, 1.0 / 6.0);
    double step2 = step1 * 0.387;

    double step3 = std::pow(0.559 / b, 9.0 / 16.0);
    double step4 = step3 + 1.0;
    double step5 = std::pow(step4, 8.0 / 27.0);

    double step6 = step2 / step5;
    double step7 = step6 + 0.6;
    double step8 = std::pow(step7, 2);
    return step8;
}

double InsulatedPipeReduction::calculateRadiativeHeatTransferCoefficient(double emissivity, double surfaceTemperature, double ambientTemperature) {
    double c = 0.00000005670373;
    return c * emissivity * (std::pow(surfaceTemperature, 4) - std::pow(ambientTemperature, 4)) / (surfaceTemperature - ambientTemperature);
}

double InsulatedPipeReduction::calculateConvectiveHeatTransferCoefficient(double nusselt, double airConductivity, double diameter){
    return nusselt * airConductivity / diameter;
}