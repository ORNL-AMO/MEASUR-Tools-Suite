#include <emscripten/bind.h>

#include "compressedAir/leak_survey/compressed_air_leak_survey.h"

using namespace emscripten;
using namespace compressed_air_leak_survey;

EMSCRIPTEN_BINDINGS(compressed_air_leak_survey) {
    // ---- Input ----
    // Each field of Input is exposed as a camelCase JS property.
    // Nested sub-method input structs are registered as value_objects in their
    // respective binding files and are automatically converted by emscripten.
    //
    // CompressedAirLeakSurveyInput field units:
    //   hoursPerYear            [hr/yr]    - annual system operating time
    //   utilityType             [unitless] - 0 = compressed air, 1 = electricity
    //   utilityCost             [$/ft³ or $/kWh] - utility rate (depends on utilityType)
    //   measurementMethod       [unitless] - 0 = estimate, 1 = decibels, 2 = bag, 3 = orifice
    //   estimateMethodInput     [-]        - see EstimateMethodInput
    //   decibelsMethodInput     [-]        - see DecibelsMethodInput
    //   bagMethodInput          [-]        - see BagMethodInput
    //   orificeMethodInput      [-]        - see OrificeMethodInput
    //   compressorElectricityData [-]      - see CompressorElectricityData
    //   units                   [unitless] - number of identical leak points
    value_object<Input>("CompressedAirLeakSurveyInput")
        .field("hoursPerYear",             &Input::hours_per_year)
        .field("utilityType",              &Input::utility_type)
        .field("utilityCost",              &Input::utility_cost)
        .field("measurementMethod",        &Input::measurement_method)
        .field("estimateMethodInput",      &Input::estimate_input)
        .field("decibelsMethodInput",      &Input::decibels_input)
        .field("bagMethodInput",           &Input::bag_input)
        .field("orificeMethodInput",       &Input::orifice_input)
        .field("compressorElectricityData",&Input::compressor_electricity_data)
        .field("units",                    &Input::units);

    register_vector<Input>("CompressedAirLeakSurveyInputV");

    // ---- Result ----
    // calculateCompressedAirLeakSurvey(CompressedAirLeakSurveyInput[]) -> CompressedAirLeakSurveyResult
    //   annualTotalElectricity      [kWh]     - total annual electrical energy for all leaks
    //   annualTotalElectricityCost  [$/yr]    - total annual utility cost for all leaks
    //   totalFlowRate               [scfm]    - combined instantaneous flow rate of all leaks
    //   annualTotalFlowRate         [scf]     - combined annual air volume lost to leaks
    value_object<Result>("CompressedAirLeakSurveyResult")
        .field("annualTotalElectricity",     &Result::annual_total_electricity)
        .field("annualTotalElectricityCost", &Result::annual_total_electricity_cost)
        .field("totalFlowRate",              &Result::total_flow_rate)
        .field("annualTotalFlowRate",        &Result::annual_total_flow_rate);

    function("calculateCompressedAirLeakSurvey", optional_override([](val jsArray) {
        std::vector<Input> inputs;
        const unsigned length = jsArray["length"].as<unsigned>();
        inputs.reserve(length);
        for (unsigned i = 0; i < length; ++i) {
            inputs.push_back(jsArray[i].as<Input>());
        }
        return calculate(inputs);
    }));
}
