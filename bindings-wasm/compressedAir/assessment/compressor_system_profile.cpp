#include <emscripten/bind.h>

#include "compressedAir/assessment/compressor_system_profile.h"

using namespace emscripten;
using namespace compressed_air::assessment;

EMSCRIPTEN_BINDINGS(compressor_system_profile_assessment)
{
    enum_<CompressorSystemControlMode>("CompressorSystemControlMode")
        .value("Cascading", CompressorSystemControlMode::Cascading)
        .value("IsentropicEfficiency", CompressorSystemControlMode::IsentropicEfficiency)
        .value("LoadSharing", CompressorSystemControlMode::LoadSharing)
        .value("TargetPressureSequencer", CompressorSystemControlMode::TargetPressureSequencer)
        .value("BaseTrim", CompressorSystemControlMode::BaseTrim);

    value_object<CompressorProfileCompressor>("CompressorProfileCompressor")
        .field("compressorId", &CompressorProfileCompressor::compressorId)
        .field("compressorType", &CompressorProfileCompressor::compressorType)
        .field("control", &CompressorProfileCompressor::control)
        .field("stage", &CompressorProfileCompressor::stage)
        .field("lubricant", &CompressorProfileCompressor::lubricant)
        .field("automaticShutdown", &CompressorProfileCompressor::automaticShutdown)
        .field("performancePoints", &CompressorProfileCompressor::performancePoints)
        .field("blowdownTimeSec", &CompressorProfileCompressor::blowdownTimeSec)
        .field("unloadSumpPressurePsig", &CompressorProfileCompressor::unloadSumpPressurePsig)
        .field("unloadPointCapacityPct", &CompressorProfileCompressor::unloadPointCapacityPct)
        .field("noLoadPowerFractionForModulation",
               &CompressorProfileCompressor::noLoadPowerFractionForModulation)
        .field("modulatingPressurePsig", &CompressorProfileCompressor::modulatingPressurePsig);

    value_object<CompressorProfileRow>("CompressorProfileRow")
        .field("compressorId", &CompressorProfileRow::compressorId)
        .field("dayTypeId", &CompressorProfileRow::dayTypeId)
        .field("timeIntervalHr", &CompressorProfileRow::timeIntervalHr)
        .field("operatingOrder", &CompressorProfileRow::operatingOrder)
        .field("powerKw", &CompressorProfileRow::powerKw)
        .field("airflowAcfm", &CompressorProfileRow::airflowAcfm)
        .field("powerFraction", &CompressorProfileRow::powerFraction)
        .field("airflowFraction", &CompressorProfileRow::airflowFraction)
        .field("systemPowerFraction", &CompressorProfileRow::systemPowerFraction)
        .field("systemAirflowFraction", &CompressorProfileRow::systemAirflowFraction)
        .field("powerFactor", &CompressorProfileRow::powerFactor)
        .field("amps", &CompressorProfileRow::amps)
        .field("volts", &CompressorProfileRow::volts);

    value_object<CompressorProfileTotal>("CompressorProfileTotal")
        .field("dayTypeId", &CompressorProfileTotal::dayTypeId)
        .field("timeIntervalHr", &CompressorProfileTotal::timeIntervalHr)
        .field("airflowAcfm", &CompressorProfileTotal::airflowAcfm)
        .field("powerKw", &CompressorProfileTotal::powerKw)
        .field("totalPowerKw", &CompressorProfileTotal::totalPowerKw)
        .field("airflowFraction", &CompressorProfileTotal::airflowFraction)
        .field("powerFraction", &CompressorProfileTotal::powerFraction)
        .field("auxiliaryPowerKw", &CompressorProfileTotal::auxiliaryPowerKw);

    value_object<CompressorRuntimeState>("CompressorRuntimeState")
        .field("compressorId", &CompressorRuntimeState::compressorId)
        .field("dayTypeId", &CompressorRuntimeState::dayTypeId)
        .field("timeIntervalHr", &CompressorRuntimeState::timeIntervalHr)
        .field("isCompressorOn", &CompressorRuntimeState::isCompressorOn)
        .field("automaticShutdownTimer", &CompressorRuntimeState::automaticShutdownTimer);

    value_object<CompressorTrimSelection>("CompressorTrimSelection")
        .field("dayTypeId", &CompressorTrimSelection::dayTypeId)
        .field("compressorId", &CompressorTrimSelection::compressorId);

    value_object<CompressorProfileOptions>("CompressorProfileOptions")
        .field("dayTypeId", &CompressorProfileOptions::dayTypeId)
        .field("inputBasis", &CompressorProfileOptions::inputBasis)
        .field("controlMode", &CompressorProfileOptions::controlMode)
        .field("atmosphericPressurePsia", &CompressorProfileOptions::atmosphericPressurePsia)
        .field("totalAirStorageFt3", &CompressorProfileOptions::totalAirStorageFt3)
        .field("additionalReceiverVolumeFt3", &CompressorProfileOptions::additionalReceiverVolumeFt3)
        .field("canShutdown", &CompressorProfileOptions::canShutdown);

    value_object<CompressorProfileSavingsInput>("CompressorProfileSavingsInput")
        .field("dayTypeId", &CompressorProfileSavingsInput::dayTypeId)
        .field("electricityCostPerKwh", &CompressorProfileSavingsInput::electricityCostPerKwh)
        .field("intervalHours", &CompressorProfileSavingsInput::intervalHours)
        .field("operatingDays", &CompressorProfileSavingsInput::operatingDays)
        .field("auxiliaryEnergyKwh", &CompressorProfileSavingsInput::auxiliaryEnergyKwh)
        .field("implementationCost", &CompressorProfileSavingsInput::implementationCost)
        .field("salvageValue", &CompressorProfileSavingsInput::salvageValue);

    value_object<CompressorProfileSavingsResult>("CompressorProfileSavingsResult")
        .field("baselineEnergyKwh", &CompressorProfileSavingsResult::baselineEnergyKwh)
        .field("baselineCost", &CompressorProfileSavingsResult::baselineCost)
        .field("adjustedEnergyKwh", &CompressorProfileSavingsResult::adjustedEnergyKwh)
        .field("adjustedCost", &CompressorProfileSavingsResult::adjustedCost)
        .field("energySavingsKwh", &CompressorProfileSavingsResult::energySavingsKwh)
        .field("costSavings", &CompressorProfileSavingsResult::costSavings)
        .field("percentSavings", &CompressorProfileSavingsResult::percentSavings)
        .field("implementationCost", &CompressorProfileSavingsResult::implementationCost)
        .field("salvageValue", &CompressorProfileSavingsResult::salvageValue)
        .field("paybackMonths", &CompressorProfileSavingsResult::paybackMonths);

    register_vector<CompressorProfileCompressor>("CompressorProfileCompressorV");
    register_vector<CompressorProfileRow>("CompressorProfileRowV");
    register_vector<CompressorProfileTotal>("CompressorProfileTotalV");
    register_vector<CompressorRuntimeState>("CompressorRuntimeStateV");
    register_vector<CompressorTrimSelection>("CompressorTrimSelectionV");

    function("calculateBaselineProfile", &calculateBaselineProfile);
    function("calculateProfileTotals", &calculateProfileTotals);
    function("reallocateProfileFlow", &reallocateProfileFlow);
    function("calculateProfileSavings", &calculateProfileSavings);
    function("calculateCompressorProfileRow", &calculateCompressorProfileRow);
    function("calculatePressureReducedAirflow", &calculatePressureReducedAirflow);
}
