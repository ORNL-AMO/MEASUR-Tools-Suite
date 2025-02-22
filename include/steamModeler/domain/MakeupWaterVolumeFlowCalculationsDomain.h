#ifndef TOOLS_SUITE_MAKEUPWATERVOLUMEFLOWCALCULATIONSDOMAIN_H
#define TOOLS_SUITE_MAKEUPWATERVOLUMEFLOWCALCULATIONSDOMAIN_H

class MakeupWaterVolumeFlowCalculationsDomain {
public:
    double makeupWaterVolumeFlow;
    double makeupWaterVolumeFlowAnnual;

    friend std::ostream &operator<<(std::ostream &stream, const MakeupWaterVolumeFlowCalculationsDomain &domain) {
        stream << "MakeupWaterVolumeFlowCalculationsDomain["
               << "makeupWaterVolumeFlow=" << domain.makeupWaterVolumeFlow
               << ", makeupWaterVolumeFlowAnnual=" << domain.makeupWaterVolumeFlowAnnual
               << "]";
        return stream;
    }
};

#endif //TOOLS_SUITE_MAKEUPWATERVOLUMEFLOWCALCULATIONSDOMAIN_H
