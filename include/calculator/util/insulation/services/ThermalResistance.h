#ifndef TOOLS_SUITE_THERMALRESISTANCE_H
#define TOOLS_SUITE_THERMALRESISTANCE_H

class ThermalResistance
{
public:
    ThermalResistance(double diameterA, double diameterB, double diameterC, double thermalConductivity)
        : _diameterA(diameterA), _diameterB(diameterB), _diameterC(diameterC), _thermalConductivity(thermalConductivity) {}

    double calculate();

private:
    double _diameterA;
    double _diameterB;
    double _diameterC;
    double _thermalConductivity;
};

#endif //TOOLS_SUITE_THERMALRESISTANCE_H