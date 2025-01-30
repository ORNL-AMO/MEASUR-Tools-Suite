#ifndef TOOLS_SUITE_NUSSELTNUMBER_H
#define TOOLS_SUITE_NUSSELTNUMBER_H

class NusseltNumber
{
public:
    NusseltNumber(double a, double b)
        : _a(a), _b(b) {}

    double calculate();
    double calculateForcedConvection();
    double calculateFreeConvection();

private:
    double _a;
    double _b;
};

#endif //TOOLS_SUITE_NUSSELTNUMBER_H