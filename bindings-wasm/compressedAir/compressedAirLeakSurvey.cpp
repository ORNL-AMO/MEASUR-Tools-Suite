#include "compressedAir/CompressedAirLeakSurvey.h"
#include "compressedAir/orifice_method.h"
#include "compressedAir/decibels_method.h"
#include "compressedAir/estimate_method.h"
#include "compressedAir/bag_method.h"

#include <emscripten/bind.h>

#include "vector"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(compressedAirLeakSurvey_class) {


    class_<CompressedAirLeakSurveyInput>("CompressedAirLeakSurveyInput")
        .constructor<int, int, double, int, estimate_method::Input, decibels_method::Input, bag_method::Input,
                     orifice_method::Input, CompressorElectricityData, int>();

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
