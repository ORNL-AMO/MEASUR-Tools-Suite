#include <emscripten/bind.h>

#include "compressedAir/assessment/compressor_eem.h"

using namespace emscripten;
namespace eem = compressed_air::assessment::compressor_eem;

EMSCRIPTEN_BINDINGS(compressor_eem_assessment)
{
    value_object<eem::ReduceAirLeaksResult>("ReduceAirLeaksResult")
        .field("reducedLeakAirflowAcfm", &eem::ReduceAirLeaksResult::reducedLeakAirflowAcfm)
        .field("adjustedUseAirflowAcfm", &eem::ReduceAirLeaksResult::adjustedUseAirflowAcfm)
        .field("adjustedUseFraction", &eem::ReduceAirLeaksResult::adjustedUseFraction);

    value_object<eem::ImproveEndUseEfficiencyResult>("ImproveEndUseEfficiencyResult")
        .field("reducedAirflowAcfm", &eem::ImproveEndUseEfficiencyResult::reducedAirflowAcfm)
        .field("reducedAirflowFraction", &eem::ImproveEndUseEfficiencyResult::reducedAirflowFraction);

    value_object<eem::ReduceSystemAirPressureResult>("ReduceSystemAirPressureResult")
        .field("adjustedFullLoadPressurePsig", &eem::ReduceSystemAirPressureResult::adjustedFullLoadPressurePsig)
        .field("adjustedFullLoadPowerKw", &eem::ReduceSystemAirPressureResult::adjustedFullLoadPowerKw)
        .field("adjustedUseAirflowAcfm", &eem::ReduceSystemAirPressureResult::adjustedUseAirflowAcfm)
        .field("adjustedUseFraction", &eem::ReduceSystemAirPressureResult::adjustedUseFraction);

    value_object<eem::AdjustCascadingSetPointResult>("AdjustCascadingSetPointResult")
        .field("adjustedFullLoadPowerKw", &eem::AdjustCascadingSetPointResult::adjustedFullLoadPowerKw)
        .field("adjustedUseAirflowAcfm", &eem::AdjustCascadingSetPointResult::adjustedUseAirflowAcfm)
        .field("adjustedUseFraction", &eem::AdjustCascadingSetPointResult::adjustedUseFraction);

    value_object<eem::PressureReductionSavingResult>("PressureReductionSavingResult")
        .field("powerSavingsKw", &eem::PressureReductionSavingResult::powerSavingsKw)
        .field("energySavingsKwh", &eem::PressureReductionSavingResult::energySavingsKwh)
        .field("costSavings", &eem::PressureReductionSavingResult::costSavings);

    function("reduceAirLeaks", &eem::reduceAirLeaks);
    function("improveEndUseEfficiency", &eem::improveEndUseEfficiency);
    function("reduceSystemAirPressure", &eem::reduceSystemAirPressure);
    function("adjustCascadingSetPoint", &eem::adjustCascadingSetPoint);
    function("pressureReductionSaving", &eem::pressureReductionSaving);
    function("adjustedPower", &eem::adjustedPower);
}
