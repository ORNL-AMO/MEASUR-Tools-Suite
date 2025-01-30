#ifndef TOOLS_SUITE_RAYLEIGHNUMBER_H
#define TOOLS_SUITE_RAYLEIGHNUMBER_H

class RayleighNumber
{
public:
    RayleighNumber(double expCoefficient, double surfaceTemperature,
                   double ambientTemperature, double diameter, double kinematicViscosity, double alpha)
        : _expCoefficient(expCoefficient), _surfaceTemperature(surfaceTemperature),
          _ambientTemperature(ambientTemperature), _diameter(diameter),
          _kinematicViscosity(kinematicViscosity), _alpha(alpha) {}

    double calculate();

private:
    double _expCoefficient;
    double _surfaceTemperature;
    double _ambientTemperature;
    double _diameter;
    double _kinematicViscosity;
    double _alpha;
};

#endif //TOOLS_SUITE_RAYLEIGHNUMBER_H