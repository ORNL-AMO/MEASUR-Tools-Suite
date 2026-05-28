#include "compressedAir/CompressedAirLeakSurvey.h"

#include <emscripten/bind.h>

#include "vector"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(compressedAirLeakSurvey_class) {

    class_<DecibelsMethodData>("DecibelsMethodData")
        .constructor<double, double, double, double, double, double, double, double, double, double>();

    class_<OrificeMethodData>("OrificeMethodData").constructor<double, double, double, double, double, int>();

    class_<CompressedAirLeakSurveyInput>("CompressedAirLeakSurveyInput")
        .constructor<int, int, double, int, estimate_method::Input, DecibelsMethodData, bag_method::Input,
                     OrificeMethodData, CompressorElectricityData, int>();

    register_vector<CompressedAirLeakSurveyInput>("CompressedAirLeakSurveyInputV");

    class_<CompressedAirLeakSurvey::Output>("CompressedAirLeakSurveyOutput")
        .property("annualTotalElectricity", &CompressedAirLeakSurvey::Output::annualTotalElectricity)
        .property("annualTotalElectricityCost", &CompressedAirLeakSurvey::Output::annualTotalElectricityCost)
        .property("totalFlowRate", &CompressedAirLeakSurvey::Output::totalFlowRate)
        .property("annualTotalFlowRate", &CompressedAirLeakSurvey::Output::annualTotalFlowRate);

    class_<CompressedAirLeakSurvey>("CompressedAirLeakSurvey")
        .constructor<std::vector<CompressedAirLeakSurveyInput>>()
        .function("calculate", &CompressedAirLeakSurvey::calculate);
}