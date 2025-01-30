#ifndef TOOLS_SUITE_INSULATEDPIPEOUTPUT_H
#define TOOLS_SUITE_INSULATEDPIPEOUTPUT_H

class InsulatedPipeOutput
{
public:
    InsulatedPipeOutput();
    InsulatedPipeOutput(double heatLength, double annualHeatLoss) : _heatLength(heatLength), _annualHeatLoss(annualHeatLoss) {}

    double getHeatLength();
    double getAnnualHeatLoss();
    void setHeatLength(double heatLength);
    void setAnnualHeatLoss(double annualHeatLoss);

private:
    double _heatLength;
    double _annualHeatLoss;
};

#endif