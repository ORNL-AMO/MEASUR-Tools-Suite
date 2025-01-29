#ifndef TOOLS_SUITE_REYNOLDSNUMBER_H
#define TOOLS_SUITE_REYNOLDSNUMBER_H

class ReynoldsNumber
{
public:
    ReynoldsNumber(double diameter, double windVelocity, double kinematicViscosity)
        : _diameter(diameter), _windVelocity(windVelocity), _kinematicViscosity(kinematicViscosity) {}

    double calculate();

private:
    double _diameter;
    double _windVelocity;
    double _kinematicViscosity;
};

#endif //TOOLS_SUITE_REYNOLDSNUMBER_H