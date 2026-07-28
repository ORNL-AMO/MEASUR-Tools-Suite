#include <vector>

#include <emscripten/bind.h>

#include "compressedAir/assessment/compressor_catalog.h"

using namespace emscripten;
using namespace compressed_air::assessment;

EMSCRIPTEN_BINDINGS(compressor_catalog_assessment)
{
    value_object<CompressorCatalogRecord>("CompressorCatalogRecord")
        .field("id", &CompressorCatalogRecord::id)
        .field("compressorTypeId", &CompressorCatalogRecord::compressorTypeId)
        .field("model", &CompressorCatalogRecord::model)
        .field("horsepower", &CompressorCatalogRecord::horsepower)
        .field("ratedCapacityAcfm", &CompressorCatalogRecord::ratedCapacityAcfm)
        .field("ratedPressurePsig", &CompressorCatalogRecord::ratedPressurePsig)
        .field("maxFullFlowPressurePsig", &CompressorCatalogRecord::maxFullFlowPressurePsig)
        .field("controlTypeId", &CompressorCatalogRecord::controlTypeId)
        .field("unloadPointPercent", &CompressorCatalogRecord::unloadPointPercent)
        .field("minUnloadSumpPressurePsig", &CompressorCatalogRecord::minUnloadSumpPressurePsig)
        .field("blowdownTimeSec", &CompressorCatalogRecord::blowdownTimeSec)
        .field("unloadSteps", &CompressorCatalogRecord::unloadSteps)
        .field("modulatingPressureRangePsig", &CompressorCatalogRecord::modulatingPressureRangePsig)
        .field("fullLoadBhpPowerKw", &CompressorCatalogRecord::fullLoadBhpPowerKw)
        .field("totalPackageInputPowerKw", &CompressorCatalogRecord::totalPackageInputPowerKw)
        .field("specificPackagePower", &CompressorCatalogRecord::specificPackagePower)
        .field("noLoadPowerFullyModulating", &CompressorCatalogRecord::noLoadPowerFullyModulating)
        .field("noLoadPowerUnload", &CompressorCatalogRecord::noLoadPowerUnload)
        .field("maxSurgePressurePsig", &CompressorCatalogRecord::maxSurgePressurePsig)
        .field("maxSurgePressureFlowAcfm", &CompressorCatalogRecord::maxSurgePressureFlowAcfm)
        .field("minStonewallPressurePsig", &CompressorCatalogRecord::minStonewallPressurePsig)
        .field("minStonewallPressureFlowAcfm", &CompressorCatalogRecord::minStonewallPressureFlowAcfm)
        .field("designSurgeFlowAcfm", &CompressorCatalogRecord::designSurgeFlowAcfm)
        .field("designInletTemperatureF", &CompressorCatalogRecord::designInletTemperatureF)
        .field("designInletPressurePsia", &CompressorCatalogRecord::designInletPressurePsia)
        .field("fullLoadAmps", &CompressorCatalogRecord::fullLoadAmps)
        .field("fullLoadEfficiencyPercent", &CompressorCatalogRecord::fullLoadEfficiencyPercent);

    register_vector<CompressorCatalogRecord>("CompressorCatalogRecordV");
}
