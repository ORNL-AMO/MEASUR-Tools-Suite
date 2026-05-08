#include <emscripten/bind.h>

#include "steamModeler/SteamProperties.h"
#include "treasureHunt/steam_reduction.h"

using namespace emscripten;
using namespace steam_reduction;

EMSCRIPTEN_BINDINGS(steamReduction_module) {
    // Enums
    enum_<SteamMeasurementMethod>("SteamMeasurementMethod")
        .value("FlowMeter",    SteamMeasurementMethod::kFlowMeter)
        .value("AirMassFlow",  SteamMeasurementMethod::kAirMassFlow)
        .value("WaterMassFlow", SteamMeasurementMethod::kWaterMassFlow)
        .value("Offsheet",     SteamMeasurementMethod::kOffsheet);

    enum_<UtilityType>("SteamUtilityType")
        .value("Steam",      UtilityType::kSteam)
        .value("NaturalGas", UtilityType::kNaturalGas)
        .value("Other",      UtilityType::kOther);

    // Input structs
    // FlowMeterMethodData:
    //   flowRate (m3/min for water, kg/hr for steam)
    value_object<FlowMeterMethodData>("SteamFlowMeterMethodData")
        .field("flowRate", &FlowMeterMethodData::flow_rate);

    // MassFlowNameplateData:
    //   flowRate (m3/min or kg/hr)
    value_object<MassFlowNameplateData>("SteamMassFlowNameplateData")
        .field("flowRate", &MassFlowNameplateData::flow_rate);

    // MassFlowMeasuredData:
    //   areaOfDuct (m2)
    //   airVelocity (m/min)
    value_object<MassFlowMeasuredData>("SteamMassFlowMeasuredData")
        .field("areaOfDuct",  &MassFlowMeasuredData::area_of_duct)
        .field("airVelocity", &MassFlowMeasuredData::air_velocity);

    // MassFlowMethodData:
    //   isNameplate (bool)
    //   massFlowMeasuredData (SteamMassFlowMeasuredData)
    //   massFlowNameplateData (SteamMassFlowNameplateData)
    //   inletTemperature (°C)
    //   outletTemperature (°C)
    value_object<MassFlowMethodData>("SteamMassFlowMethodData")
        .field("isNameplate",           &MassFlowMethodData::is_nameplate)
        .field("massFlowMeasuredData",  &MassFlowMethodData::mass_flow_measured_data)
        .field("massFlowNameplateData", &MassFlowMethodData::mass_flow_nameplate_data)
        .field("inletTemperature",      &MassFlowMethodData::inlet_temperature)
        .field("outletTemperature",     &MassFlowMethodData::outlet_temperature);

    // OffsheetMethodData:
    //   consumption (kJ/hr)
    value_object<OffsheetMethodData>("SteamOffsheetMethodData")
        .field("consumption", &OffsheetMethodData::consumption);

    // SteamReductionInput:
    //   hoursPerYear (hr/yr)
    //   utilityType (SteamUtilityType)
    //   utilityCost ($/kg for steam, $/kJ for gas/other)
    //   measurementMethod (SteamMeasurementMethod)
    //   systemEfficiency (unitless)
    //   pressure (MPaa)
    //   flowMeterMethodData (SteamFlowMeterMethodData)
    //   airMassFlowMethodData (SteamMassFlowMethodData)
    //   waterMassFlowMethodData (SteamMassFlowMethodData)
    //   offsheetMethodData (SteamOffsheetMethodData)
    //   units (unitless conversion factor)
    //   boilerEfficiency (unitless)
    //   steamVariableOption (ThermodynamicQuantity)
    //   steamVariable (depends on steamVariableOption: K, kJ/kg, kJ/kg-K, or unitless quality)
    //   feedWaterTemperature (K)
    value_object<SteamReductionInput>("SteamReductionInput")
        .field("hoursPerYear",           &SteamReductionInput::hours_per_year)
        .field("utilityType",            &SteamReductionInput::utility_type)
        .field("utilityCost",            &SteamReductionInput::utility_cost)
        .field("measurementMethod",      &SteamReductionInput::measurement_method)
        .field("systemEfficiency",       &SteamReductionInput::system_efficiency)
        .field("pressure",               &SteamReductionInput::pressure)
        .field("flowMeterMethodData",    &SteamReductionInput::flow_meter_method_data)
        .field("airMassFlowMethodData",  &SteamReductionInput::air_mass_flow_method_data)
        .field("waterMassFlowMethodData",&SteamReductionInput::water_mass_flow_method_data)
        .field("offsheetMethodData",     &SteamReductionInput::offsheet_method_data)
        .field("units",                  &SteamReductionInput::units)
        .field("boilerEfficiency",       &SteamReductionInput::boiler_efficiency)
        .field("steamVariableOption",    &SteamReductionInput::steam_variable_option)
        .field("steamVariable",          &SteamReductionInput::steam_variable)
        .field("feedWaterTemperature",   &SteamReductionInput::feed_water_temperature);

    register_vector<SteamReductionInput>("SteamReductionInputV");

    // SteamReductionOutput:
    //   steamUse (kg/hr)
    //   energyUse (kJ/yr)
    //   energyCost ($/yr)
    value_object<SteamReductionOutput>("SteamReductionOutput")
        .field("steamUse",   &SteamReductionOutput::steam_use)
        .field("energyUse",  &SteamReductionOutput::energy_use)
        .field("energyCost", &SteamReductionOutput::energy_cost);

    // steamReduction(input_vec: SteamReductionInputV) -> SteamReductionOutput
    //   input_vec: vector of SteamReductionInput structs, one per measure
    //   returns: SteamReductionOutput with total annual steam use, energy use, and energy cost
    function("steamReduction", &steamReduction);
}
