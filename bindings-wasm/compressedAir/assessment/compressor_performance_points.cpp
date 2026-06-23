#include <emscripten/bind.h>

#include "compressedAir/assessment/compressor_performance_points.h"

using namespace emscripten;
using namespace compressed_air::assessment;

EMSCRIPTEN_BINDINGS(compressor_performance_points_assessment)
{
    value_object<CompressorPerformancePoint>("CompressorPerformancePoint")
        .field("dischargePressurePsig", &CompressorPerformancePoint::dischargePressurePsig)
        .field("isDefaultPressure", &CompressorPerformancePoint::isDefaultPressure)
        .field("airflowAcfm", &CompressorPerformancePoint::airflowAcfm)
        .field("isDefaultAirflow", &CompressorPerformancePoint::isDefaultAirflow)
        .field("powerKw", &CompressorPerformancePoint::powerKw)
        .field("isDefaultPower", &CompressorPerformancePoint::isDefaultPower);

    value_object<CompressorPerformancePoints>("CompressorPerformancePoints")
        .field("fullLoad", &CompressorPerformancePoints::fullLoad)
        .field("maxFullFlow", &CompressorPerformancePoints::maxFullFlow)
        .field("midTurndown", &CompressorPerformancePoints::midTurndown)
        .field("turndown", &CompressorPerformancePoints::turndown)
        .field("unloadPoint", &CompressorPerformancePoints::unloadPoint)
        .field("noLoad", &CompressorPerformancePoints::noLoad)
        .field("blowoff", &CompressorPerformancePoints::blowoff);

    value_object<CompressorNameplateData>("CompressorNameplateData")
        .field("compressorType", &CompressorNameplateData::compressorType)
        .field("stage", &CompressorNameplateData::stage)
        .field("lubricant", &CompressorNameplateData::lubricant)
        .field("motorPowerHp", &CompressorNameplateData::motorPowerHp)
        .field("fullLoadOperatingPressurePsig", &CompressorNameplateData::fullLoadOperatingPressurePsig)
        .field("fullLoadRatedCapacityAcfm", &CompressorNameplateData::fullLoadRatedCapacityAcfm)
        .field("ratedLoadPowerKw", &CompressorNameplateData::ratedLoadPowerKw)
        .field("polytropicCompressorExponent", &CompressorNameplateData::polytropicCompressorExponent)
        .field("fullLoadAmps", &CompressorNameplateData::fullLoadAmps)
        .field("totalPackageInputPowerKw", &CompressorNameplateData::totalPackageInputPowerKw);

    value_object<CompressorControlsData>("CompressorControlsData")
        .field("control", &CompressorControlsData::control)
        .field("unloadPointCapacityPct", &CompressorControlsData::unloadPointCapacityPct)
        .field("numberOfUnloadSteps", &CompressorControlsData::numberOfUnloadSteps)
        .field("automaticShutdown", &CompressorControlsData::automaticShutdown)
        .field("unloadSumpPressurePsig", &CompressorControlsData::unloadSumpPressurePsig);

    value_object<CompressorDesignDetails>("CompressorDesignDetails")
        .field("blowdownTimeSec", &CompressorDesignDetails::blowdownTimeSec)
        .field("modulatingPressurePsig", &CompressorDesignDetails::modulatingPressurePsig)
        .field("inputPressurePsia", &CompressorDesignDetails::inputPressurePsia)
        .field("designEfficiencyPct", &CompressorDesignDetails::designEfficiencyPct)
        .field("serviceFactor", &CompressorDesignDetails::serviceFactor)
        .field("noLoadPowerFMPercent", &CompressorDesignDetails::noLoadPowerFMPercent)
        .field("noLoadPowerULPercent", &CompressorDesignDetails::noLoadPowerULPercent)
        .field("maxFullFlowPressurePsig", &CompressorDesignDetails::maxFullFlowPressurePsig);

    value_object<CentrifugalSpecifics>("CentrifugalSpecifics")
        .field("surgeAirflowAcfm", &CentrifugalSpecifics::surgeAirflowAcfm)
        .field("maxFullLoadPressurePsig", &CentrifugalSpecifics::maxFullLoadPressurePsig)
        .field("maxFullLoadCapacityAcfm", &CentrifugalSpecifics::maxFullLoadCapacityAcfm)
        .field("minFullLoadPressurePsig", &CentrifugalSpecifics::minFullLoadPressurePsig)
        .field("minFullLoadCapacityAcfm", &CentrifugalSpecifics::minFullLoadCapacityAcfm);

    value_object<CompressorPerformancePointInput>("CompressorPerformancePointInput")
        .field("nameplate", &CompressorPerformancePointInput::nameplate)
        .field("controls", &CompressorPerformancePointInput::controls)
        .field("design", &CompressorPerformancePointInput::design)
        .field("centrifugal", &CompressorPerformancePointInput::centrifugal)
        .field("points", &CompressorPerformancePointInput::points)
        .field("atmosphericPressurePsia", &CompressorPerformancePointInput::atmosphericPressurePsia);

    value_object<SequencerSetPointInput>("SequencerSetPointInput")
        .field("compressor", &SequencerSetPointInput::compressor)
        .field("targetPressurePsig", &SequencerSetPointInput::targetPressurePsig)
        .field("variancePsig", &SequencerSetPointInput::variancePsig);

    value_object<PressureReductionPointInput>("PressureReductionPointInput")
        .field("compressor", &PressureReductionPointInput::compressor)
        .field("pressureReductionPsig", &PressureReductionPointInput::pressureReductionPsig);

    value_object<CascadingSetPointInput>("CascadingSetPointInput")
        .field("compressor", &CascadingSetPointInput::compressor)
        .field("fullLoadPressurePsig", &CascadingSetPointInput::fullLoadPressurePsig)
        .field("maxFullFlowPressurePsig", &CascadingSetPointInput::maxFullFlowPressurePsig);

    function("generatePerformancePoints", &generatePerformancePoints);
    function("adjustPerformancePointsForSequencer", &adjustPerformancePointsForSequencer);
    function("reduceSystemPressurePerformancePoints", &reduceSystemPressurePerformancePoints);
    function("adjustCascadingSetPointPerformancePoints", &adjustCascadingSetPointPerformancePoints);
    function("calculatePressureAdjustedAirflow", &calculatePressureAdjustedAirflow);
    function("calculatePressureAdjustedPower", &calculatePressureAdjustedPower);
    function("calculateNoLoadPower", &calculateNoLoadPower);
    function("calculateNoLoadPowerWithoutUnloading", &calculateNoLoadPowerWithoutUnloading);
    function("calculateUnloadPointPower", &calculateUnloadPointPower);
    function("calculateUnloadPointAirflow", &calculateUnloadPointAirflow);
    function("calculateUnloadPointDischargePressure", &calculateUnloadPointDischargePressure);
    function("calculateCentrifugalUnloadPointAirflow", &calculateCentrifugalUnloadPointAirflow);
    function("calculateRatedSpecificPower", &calculateRatedSpecificPower);
    function("calculateRatedIsentropicEfficiency", &calculateRatedIsentropicEfficiency);
}
