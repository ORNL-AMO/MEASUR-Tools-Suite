#include <string>

#include <emscripten/bind.h>
#include "processHeat/o2_enrichment.h"

using namespace emscripten;
using namespace o2_enrichment;
EMSCRIPTEN_BINDINGS(o2_enrichment_class) {
    value_object<O2EnrichmentResults>("O2EnrichmentResults")
        .field("excessAir", &O2EnrichmentResults::excess_air)
        .field("excessAirEnriched", &O2EnrichmentResults::excess_air_enriched)
        .field("heatInput", &O2EnrichmentResults::heat_input)
        .field("heatInputEnriched", &O2EnrichmentResults::heat_input_enriched)
        .field("airSpecificHeat", &O2EnrichmentResults::air_specific_heat)
        .field("enrichedAirSpecificHeat", &O2EnrichmentResults::enriched_air_specific_heat)
        .field("airCorrection", &O2EnrichmentResults::air_correction)
        .field("enrichedAirCorrection", &O2EnrichmentResults::enriched_air_correction)
        .field("combustionAirCorrection", &O2EnrichmentResults::combustion_air_correction)
        .field("combustionAirCorrectionEnriched", &O2EnrichmentResults::combustion_air_correction_enriched)
        .field("stdAvailableHeat", &O2EnrichmentResults::std_available_heat)
        .field("stdAvailableHeatEnriched", &O2EnrichmentResults::std_available_heat_enriched)
        .field("availableHeat", &O2EnrichmentResults::available_heat)
        .field("availableHeatEnriched", &O2EnrichmentResults::available_heat_enriched)
        .field("fuelConsumptionEnriched", &O2EnrichmentResults::fuel_consumption_enriched)
        .field("fuelSavingsEnriched", &O2EnrichmentResults::fuel_savings_enriched);

    // Parameters for calculateO2Enrichment:
    //   o2_comb_air (percent)
    //   o2_comb_air_enriched (percent)
    //   flue_gas_temp (°F)
    //   flue_gas_temp_enriched (°F)
    //   o2_flue_gas (percent)
    //   o2_flue_gas_enriched (percent)
    //   comb_air_temp (°F)
    //   comb_air_temp_enriched (°F)
    //   fuel_consumption (MMBtu/hr)
    function("calculateO2Enrichment", &calculateO2Enrichment);
}
