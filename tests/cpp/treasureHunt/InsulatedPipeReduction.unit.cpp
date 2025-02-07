#include <vector>
#include "catch.hpp"
#include "treasureHunt/InsulatedPipeReduction.h"

TEST_CASE("Reynolds Number", "[InsulationServices][util]")
{
    double diameter = 0.1778;
    double windVel = 0.89408;
    double kinVis = 0.0000159;
    double result = InsulatedPipeReduction::calculateReynoldsNumber(diameter, windVel, kinVis);
    CHECK(result == Approx(9997.9511949686));
}

TEST_CASE("Reynolds Number 2", "[InsulationServices][util]")
{
    double diameter = 0.13335;
    double windVel = 0.44704;
    double kinVis = 0.0000149;
    double result = InsulatedPipeReduction::calculateReynoldsNumber(diameter, windVel, kinVis);
    CHECK(result == Approx(4000.8579865772));
}

TEST_CASE("Rayleigh Number", "[InsulationServices][util]")
{
    double expCoefficient = 0.003329819;
    double surfaceTemperature = 300.817;
    double ambientTemperature = 299.817;
    double diameter = 0.177799;
    double kinematicViscosity = .0000159;
    double alpha = .0000225;
    double result = InsulatedPipeReduction::calculateRayleighNumber(expCoefficient, surfaceTemperature, ambientTemperature, diameter, kinematicViscosity, alpha);
    CHECK(result == Approx(513213.3371527603));
}

TEST_CASE("Rayleigh Number 2", "[InsulationServices][util]")
{
    double expCoefficient = 0.0034577;
    double surfaceTemperature = 289.71;
    double ambientTemperature = 288.71;
    double diameter = 0.133335;
    double kinematicViscosity = 0.0000149;
    double alpha = 0.0000209;
    double result = InsulatedPipeReduction::calculateRayleighNumber(expCoefficient, surfaceTemperature, ambientTemperature, diameter, kinematicViscosity, alpha);
    CHECK(result == Approx(258200.0122627911));
}

TEST_CASE("Radiative Heat Transfer Coefficient", "[InsulationServices][util]")
{
    double emissivity = 0.1;
    double surfaceTemperature = 300.817;
    double ambientTemperature = 299.817;
    double result = InsulatedPipeReduction::calculateRadiativeHeatTransferCoefficient(emissivity, surfaceTemperature, ambientTemperature);
    CHECK(result == Approx(0.6143453478));
}

TEST_CASE("Radiative Heat Transfer Coefficient 2", "[InsulationServices][util]")
{
    double emissivity = 0.8;
    double surfaceTemperature = 289.71;
    double ambientTemperature = 288.75;
    double result = InsulatedPipeReduction::calculateRadiativeHeatTransferCoefficient(emissivity, surfaceTemperature, ambientTemperature);
    CHECK(result == Approx(4.390286024));
}

TEST_CASE("Convective Heat Transfer Coefficient", "[InsulationServices][util]")
{
    double nusselt = 32.8;
    double airConductivity = 0.02534;
    double diameter = 0.13335;
    double result = InsulatedPipeReduction::calculateConvectiveHeatTransferCoefficient(nusselt, airConductivity, diameter);
    CHECK(result == Approx(6.2328608924));
}

TEST_CASE("Convective Heat Transfer Coefficient 2", "[InsulationServices][util]")
{
    double nusselt = 12.06;
    double airConductivity = 0.0263;
    double diameter = 0.177799;
    double result = InsulatedPipeReduction::calculateConvectiveHeatTransferCoefficient(nusselt, airConductivity, diameter);
    CHECK(result == Approx(1.7839132954));
}

TEST_CASE("Convective Heat Transfer Coefficient 3", "[InsulationServices][util]")
{
    double nusselt = 53.5;
    double airConductivity = 0.0263;
    double diameter = 0.177799;
    double result = InsulatedPipeReduction::calculateConvectiveHeatTransferCoefficient(nusselt, airConductivity, diameter);
    CHECK(result == Approx(7.9137115507));
}

TEST_CASE("Nusselt - Forced", "[InsulationServices][util]")
{
    double reynolds = 9975;
    double prandtl = 0.707;
    double result = InsulatedPipeReduction::calculateNusseltForcedConvection(reynolds, prandtl);
    CHECK(result == Approx(53.4659543621));
}

TEST_CASE("Nusselt - Forced 2", "[InsulationServices][util]")
{
    double reynolds = 4000.09;
    double prandtl = 0.71;
    double result = InsulatedPipeReduction::calculateNusseltForcedConvection(reynolds, prandtl);
    CHECK(result == Approx(32.7247843626));
}

TEST_CASE("Nusselt - Free", "[InsulationServices][util]")
{
    double reynolds = 511466;
    double prandtl = 0.707;
    double result = InsulatedPipeReduction::calculateNusseltFreeConvection(reynolds, prandtl);
    CHECK(result == Approx(12.0557933229));
}

TEST_CASE("Nusselt - Free 2", "[InsulationServices][util]")
{
    double reynolds = 257651.95;
    double prandtl = 0.71;
    double result = InsulatedPipeReduction::calculateNusseltFreeConvection(reynolds, prandtl);
    CHECK(result == Approx(10.0034601706));
}

TEST_CASE("Nusselt - Combined", "[InsulationServices][util]")
{
    double reynolds = 53.5;
    double prandtl = 12.06;
    double result = InsulatedPipeReduction::calculateNusseltNumber(reynolds, prandtl);
    CHECK(result == Approx(53.5345022804));
}

TEST_CASE("Nusselt - Combined 2", "[InsulationServices][util]")
{
    double reynolds = 32.7;
    double prandtl = 10.00;
    double result = InsulatedPipeReduction::calculateNusseltNumber(reynolds, prandtl);
    CHECK(result == Approx(32.7712651627));
}

TEST_CASE("Thermal Resistance", "[InsulationServices][util]")
{
    double diameter_a = 0.177799;
    double diameter_b = 0.177799;
    double diameter_c = 0.025399;
    double thermalConductivity = 0.05056;
    double result = InsulatedPipeReduction::calculateThermalResistance(diameter_a, diameter_b, diameter_c, thermalConductivity);
    CHECK(result == Approx(3.4215474554));
}

TEST_CASE("Thermal Resistance 2", "[InsulationServices][util]")
{
    double diameter_a = 0.177799;
    double diameter_b = 0.025399;
    double diameter_c = 0.0220208;
    double thermalConductivity = 57.60;
    double result = InsulatedPipeReduction::calculateThermalResistance(diameter_a, diameter_b, diameter_c, thermalConductivity);
    CHECK(result == Approx(0.00022));
}

TEST_CASE("Thermal Resistance 3", "[InsulationServices][util]")
{
    double diameter_a = 0.03175;
    double diameter_b = 0.03175;
    double diameter_c = 0.0282;
    double thermalConductivity = 17.98;
    double result = InsulatedPipeReduction::calculateThermalResistance(diameter_a, diameter_b, diameter_c, thermalConductivity);
    CHECK(result == Approx(0.00010));
}

TEST_CASE("Insulated Pipe", "[InsulatedPipeReduction][util]")
{
    int operatingHours = 8640;        //hrs
    double pipeLength = 15.24;            //m
    double pipeDiameter = .025399;    //m
    double pipeThickness = 0.0033782; //m
    double pipeTemperature = 422.039;
    double ambientTemperature = 299.817;
    double windVelocity = 0.89408;
    double systemEfficiency = 0.9;
    double insulationThickness = 0.0762;
    double pipeEmissivity = 0.8000;
    double jacketEmissivity = 0.1;
    std::vector<double> pipeMaterialCoefficients = {0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1};
    std::vector<double> insulationMaterialCoefficients = {1.57526e-12, -2.02822e-09, 8.6328e-07, 0, 0.006729488};

    InsulatedPipeInput input(
        operatingHours,
        pipeLength,
        pipeDiameter,
        pipeThickness,
        pipeTemperature,
        ambientTemperature,
        windVelocity,
        systemEfficiency,
        insulationThickness,
        pipeEmissivity,
        jacketEmissivity,
        pipeMaterialCoefficients,
        insulationMaterialCoefficients);

    InsulatedPipeReduction calculator(input);
    InsulatedPipeOutput output = calculator.calculate();
    CHECK(output.getHeatLength() == Approx(19.3858771378));
    CHECK(output.getAnnualHeatLoss() == Approx(2836231.3687633672));
}

TEST_CASE("Non-Insulated Pipe", "[InsulatedPipeReduction][util]")
{
    int operatingHours = 8640;        //hrs
    double pipeLength = 15.24;            //m
    double diameter = .025399;        //m
    double pipeThickness = 0.0033782; //m
    double pipeTemperature = 422.039;
    double ambientTemperature = 299.817;
    double windVelocity = 0.89408;
    double systemEfficiency = 0.9;
    double insulationThickness = 0;
    double pipeEmissivity = 0.8000;
    double jacketEmissivity = 0.1;
    std::vector<double> pipeMaterialCoefficients = {0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1};
    std::vector<double> insulationMaterialCoefficients = {1.57526e-12, -2.02822e-09, 8.6328e-07, 0, 0.006729488};

    InsulatedPipeInput input(
        operatingHours,
        pipeLength,
        diameter,
        pipeThickness,
        pipeTemperature,
        ambientTemperature,
        windVelocity,
        systemEfficiency,
        insulationThickness,
        pipeEmissivity,
        jacketEmissivity,
        pipeMaterialCoefficients,
        insulationMaterialCoefficients);

    InsulatedPipeReduction calculator(input);
    InsulatedPipeOutput output = calculator.calculate();
    CHECK(output.getHeatLength() == Approx(278.8984025085));
    CHECK(output.getAnnualHeatLoss() == Approx(40803938.64));
}