#ifndef TOOLS_SUITE_CONVECTIVEHEATTRANSFERCOEFFICIENT_H
#define TOOLS_SUITE_CONVECTIVEHEATTRANSFERCOEFFICIENT_H

class ConvectiveHeatTransferCoefficient
{
public:
    ConvectiveHeatTransferCoefficient(double nusselt, double airConductivity, double diameter)
        : _nusselt(nusselt), _airConductivity(airConductivity), _diameter(diameter) {}

    double calculate();

private:
    double _nusselt;
    double _airConductivity;
    double _diameter;
};

#endif //TOOLS_SUITE_CONVECTIVEHEATTRANSFERCOEFFICIENT_H