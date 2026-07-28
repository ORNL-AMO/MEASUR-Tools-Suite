#include <emscripten/bind.h>

#include "compressedAir/assessment/compressor.h"

using namespace emscripten;
using namespace compressed_air::assessment;

EMSCRIPTEN_BINDINGS(compressor_assessment_shared)
{
    enum_<CompressorType>("CompressorType")
        .value("Centrifugal", CompressorType::Centrifugal)
        .value("Screw", CompressorType::Screw)
        .value("Reciprocating", CompressorType::Reciprocating);

    enum_<CompressorControl>("CompressorControl")
        .value("LoadUnload", CompressorControl::LoadUnload)
        .value("ModulationUnload", CompressorControl::ModulationUnload)
        .value("BlowOff", CompressorControl::BlowOff)
        .value("ModulationWithoutUnload", CompressorControl::ModulationWithoutUnload)
        .value("StartStop", CompressorControl::StartStop)
        .value("VariableDisplacementUnload", CompressorControl::VariableDisplacementUnload)
        .value("MultiStepUnloading", CompressorControl::MultiStepUnloading)
        .value("Vfd", CompressorControl::Vfd);

    enum_<CompressorStage>("CompressorStage")
        .value("Single", CompressorStage::Single)
        .value("Two", CompressorStage::Two)
        .value("Multiple", CompressorStage::Multiple);

    enum_<CompressorLubricant>("CompressorLubricant")
        .value("Injected", CompressorLubricant::Injected)
        .value("Free", CompressorLubricant::Free)
        .value("None", CompressorLubricant::None);

    enum_<CompressorInputBasis>("CompressorInputBasis")
        .value("PowerFraction", CompressorInputBasis::PowerFraction)
        .value("CapacityFraction", CompressorInputBasis::CapacityFraction)
        .value("MeasuredPower", CompressorInputBasis::MeasuredPower)
        .value("MeasuredCapacity", CompressorInputBasis::MeasuredCapacity)
        .value("Electrical", CompressorInputBasis::Electrical);

    value_object<CompressorPerformanceResult>("CompressorPerformanceResult")
        .field("powerKw", &CompressorPerformanceResult::powerKw)
        .field("airflowAcfm", &CompressorPerformanceResult::airflowAcfm)
        .field("powerFraction", &CompressorPerformanceResult::powerFraction)
        .field("airflowFraction", &CompressorPerformanceResult::airflowFraction);

    value_object<CompressorBlowOffResult>("CompressorBlowOffResult")
        .field("powerKw", &CompressorBlowOffResult::powerKw)
        .field("airflowAcfm", &CompressorBlowOffResult::airflowAcfm)
        .field("powerFraction", &CompressorBlowOffResult::powerFraction)
        .field("airflowFraction", &CompressorBlowOffResult::airflowFraction)
        .field("blowOffAirflowAcfm", &CompressorBlowOffResult::blowOffAirflowAcfm)
        .field("blowOffFraction", &CompressorBlowOffResult::blowOffFraction);
}
