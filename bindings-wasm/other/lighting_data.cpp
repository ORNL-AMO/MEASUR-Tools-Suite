#include "other/lighting_data.h"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(ligting_data_class)
{
        class_<LightingData>("LightingData")
                .constructor<std::string, std::string, int, double, int, int, int, double, double, double>()
                .function("setID", &LightingData::setID)
                .function("ID", &LightingData::ID)
                .function("category", &LightingData::category)
                .function("type", &LightingData::type)
                .function("lampsPerFixture", &LightingData::lampsPerFixture)
                .function("lampWattage", &LightingData::lampWattage)
                .function("lampOutput", &LightingData::lampOutput)
                .function("lampLife", &LightingData::lampLife)
                .function("lampCRI", &LightingData::lampCRI)
                .function("coefficientOfUtilization", &LightingData::coefficientOfUtilization)
                .function("ballastFactor", &LightingData::ballastFactor)
                .function("lumenDegradationFactor", &LightingData::lumenDegradationFactor);

        register_vector<LightingData>("LightingDataV");
}