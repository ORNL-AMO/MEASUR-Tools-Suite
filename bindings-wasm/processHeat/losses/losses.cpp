#include <emscripten/bind.h>

#include "physics/gas_composition.h"
#include "processHeat/losses/atmosphere_heat_loss.h"
#include "processHeat/losses/auxiliary_power_used.h"
#include "processHeat/losses/energy_input_electric_arc_furnace.h"
#include "processHeat/losses/energy_input_exhaust_gas_heat_loss.h"
#include "processHeat/losses/exhaust_gas_heat_loss_electric_arc_furnace.h"
#include "processHeat/losses/fixture_heat_loss.h"
#include "processHeat/losses/gas_cooling_heat_loss.h"
#include "processHeat/losses/gas_flue_gas_material.h"
#include "processHeat/losses/gas_load_charge_material_heat_required.h"
#include "processHeat/losses/leakage_heat_loss.h"
#include "processHeat/losses/liquid_cooling_heat_loss.h"
#include "processHeat/losses/liquid_load_charge_material_heat_required.h"
#include "processHeat/losses/load_charge_material.h"
#include "processHeat/losses/opening_heat_loss.h"
#include "processHeat/losses/slag_other_material_heat_loss.h"
#include "processHeat/losses/solid_liquid_flue_gas_material.h"
#include "processHeat/losses/solid_load_charge_material_heat_required.h"
#include "processHeat/losses/wall_heat_loss.h"
#include "processHeat/losses/water_cooling_heat_loss.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(losses_enums) {
    enum_<LoadChargeMaterial::ThermicReactionType>("ThermicReactionType")
        .value("ENDOTHERMIC", LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC)
        .value("EXOTHERMIC", LoadChargeMaterial::ThermicReactionType::EXOTHERMIC)
        .value("NONE", LoadChargeMaterial::ThermicReactionType::NONE);
}

// Bindings for the atmosphere_heat_loss namespace
EMSCRIPTEN_BINDINGS(atmosphere_heat_loss) {
    using namespace atmosphere_heat_loss;
    function("atmosphereTotalHeatLoss", &totalHeatLoss);
}

// auxiliaryPowerLoss
// getPowerUsed()
EMSCRIPTEN_BINDINGS(auxiliary_power_used) {
    // motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime
    using namespace auxiliary_power_used;
    function("auxiliaryCalculatePowerUsed", &calculatePowerUsed);
}

// Bindings for the fixture_heat_loss namespace
EMSCRIPTEN_BINDINGS(fixture_heat_loss) {
    using namespace fixture_heat_loss;
    function("fixtureTotalHeatLoss", &totalHeatLoss);
}

// energyInputEAF
EMSCRIPTEN_BINDINGS(energy_input_electric_arc_furnace) {
    using namespace energy_input_electric_arc_furnace;
    // Parameters for energyInputEAFTotalChemicalEnergyInput:
    //   natural_gas_heat_input (MMBtu/hr), coal_carbon_injection (lb/hr), coal_heating_value (Btu/lb),
    //   electrode_use (lb/hr), electrode_heating_value (Btu/lb), other_fuels (MMBtu/hr)
    function("energyInputEAFTotalChemicalEnergyInput", &totalChemicalEnergyInput);
    // double total_chemical_energy_input, double electricity_input
    function("energyInputEAFTotalHeatDelivered", &totalHeatDelivered);
}

// energyInputExhaustGasLosses
EMSCRIPTEN_BINDINGS(energyInputExhaustGasLosses) {
    using namespace energy_input_exhaust_gas_heat_loss;
    // Parameters for EnergyInputExhaustGasResult:
    //   available_heat (%), heat_delivered (Btu/hr), exhaust_gas_losses (Btu/hr)
    value_object<EnergyInputExhaustGasResult>("EnergyInputExhaustGasLossesResult")
        .field("available_heat", &EnergyInputExhaustGasResult::available_heat)
        .field("heat_delivered", &EnergyInputExhaustGasResult::heat_delivered)
        .field("exhaust_gas_losses", &EnergyInputExhaustGasResult::exhaust_gas_losses);

    // Parameters for energyInputExhaustGasLossesCalculate:
    //   excess_air (%), combustion_air_temp (°F), exhaust_gas_temp (°F), total_heat_input (Btu/hr)
    function("energyInputExhaustGasHeatLossCalculate", &calculate);
    // parameters for availableHeat:
    //    excess_air (%), combustion_air_temp (°F), exhaust_gas_temp (°F), total_heat_input (Btu/hr)
    function("energyInputAvailableHeat", &availableHeat);
    // parameters for heatDelivered:
    //   available_heat (%), total_heat_input (Btu/hr)
    function("energyInputHeatDelivered", &heatDelivered);
    // parameters for totalHeatLoss:
    //   heat_delivered (Btu/hr), available_heat (%)
    function("energyInputTotalHeatLoss", &totalHeatLoss);
}

// exhaustGasEAF
EMSCRIPTEN_BINDINGS(exhaust_gas_heat_loss_electric_arc_furnace) {
    // Parameters for exhaustGasEAFTotalHeatLoss:
    //   off_gas_temp (°F),
    //   co_percent (%),
    //   h2_percent (%),
    //   combustible_gases_percent (%),
    //   volume_flow_rate (ft³/min),
    //   dust_loading (lb/ft³)
    using namespace exhaust_gas_heat_loss_electric_arc_furnace;
    function("exhaustGasEAFTotalHeatLoss", &totalHeatLoss);
}

EMSCRIPTEN_BINDINGS(gas_composition) {
    using namespace gas_composition;

    class_<GasComposition>("GasCompositions")
        .constructor<std::string, double, double, double, double, double, double, double, double, double, double,
                     double>()
        .property("heatingValue", &GasComposition::heating_value)
        .property("heatingValueVolume", &GasComposition::heating_value_volume)
        .property("specificGravity", &GasComposition::specific_gravity)
        .function("calculateExcessAir", &GasComposition::excessAirFromO2)
        .function("calculateO2", &GasComposition::o2PercentageFromExcessAir);

    register_vector<GasComposition>("GasCompositionsV");
}

EMSCRIPTEN_BINDINGS(gas_flue_gas_material) {
    using namespace gas_flue_gas_material;
    value_object<ProcessHeatProperties>("ProcessHeatProperties")
        .field("stoichAir", &ProcessHeatProperties::stoich_air)
        .field("excessAir", &ProcessHeatProperties::excess_air)
        .field("availableHeat", &ProcessHeatProperties::available_heat)
        .field("specificHeat", &ProcessHeatProperties::specific_heat)
        .field("density", &ProcessHeatProperties::total_generated)
        .field("flueGasO2", &ProcessHeatProperties::flue_gas_o2);
    function("gasFlueGasMaterialTotalHeatLoss", &totalHeatLoss);
    function("gasFlueGasMaterialProcessHeatProperties", &processHeatProperties);
}

EMSCRIPTEN_BINDINGS(solid_liquid_flue_gas_material) {

    // register_vector<SolidLiquidFlueGasMaterial>("SolidLiquidFlueGasMaterialV");
    using namespace solid_liquid_flue_gas_material;
    // Parameters for calculateExcessAirFromFlueGasO2:
    //   flue_gas_o2 (percent, e.g., 5 for 5%)
    //   excess_air (fraction, e.g., 0.2 for 20%)
    function("calculateExcessAirFromFlueGasO2", &calculateExcessAirFromFlueGasO2);
    // Parameters for calculateFlueGasO2:
    //   excess_air (fraction, e.g., 0.2 for 20%)
    //   carbon (percent, e.g., 85 for 85%)
    //   hydrogen (percent)
    //   sulphur (percent)
    //   inert_ash (percent)
    //   o2 (percent)
    //   moisture (percent)
    //   nitrogen (percent)
    function("calculateFlueGasO2", &calculateFlueGasO2);
    // Parameters for solidLiquidFlueGasMaterialTotalHeatLoss:
    //   flue_gas_temp (°F)
    //   excess_air (fraction, e.g., 0.2 for 20%)
    //   carbon (percent)
    //   hydrogen (percent)
    //   sulphur (percent)
    //   inert_ash (percent)
    //   o2 (percent)
    //   moisture (percent)
    //   nitrogen (percent)
    //   combustion_air_temp (°F)
    //   fuel_temp (°F)
    //   ambient_air_temp (°F)
    //   heating_value_fuel (Btu/lb)
    function("solidLiquidFlueGasMaterialTotalHeatLoss", &totalHeatLoss);
    // Parameters for calculateHeatingValueFuel:
    //   carbon (percent)
    //   hydrogen (percent)
    //   sulphur (percent)
    //   inert_ash (percent)
    //   o2 (percent)
    //   moisture (percent)
    //   nitrogen (percent)
    function("calculateHeatingValueFuel", &calculateHeatingValueFuel);
}

// gasCoolingLosses
EMSCRIPTEN_BINDINGS(gas_cooling_heat_loss) {
    // double flow_rate, double initial_temperature, double final_temperature, double specific_heat, double
    // correction_factor, double gas_density
    using namespace gas_cooling_heat_loss;
    function("gasCoolingTotalHeatLoss", &totalHeatLoss);
}

// gasLoadChargeMaterial
EMSCRIPTEN_BINDINGS(gas_load_charge_material_heat_required) {
    using namespace gas_load_charge_material_heat_required;
    // Parameters for gasLoadChargeMaterialTotalHeatRequired:
    //   thermic_reaction_type (enum: ENDOTHERMIC, EXOTHERMIC, NONE)
    //   specific_heat_gas (Btu/lb°F)
    //   feed_rate (lb/hr)
    //   percent_vapor (% of total)
    //   initial_temperature (°F)
    //   discharge_temperature (°F)
    //   specific_heat_vapor (Btu/lb°F)
    //   percent_reacted (% of total)
    //   reaction_heat (Btu/lb)
    //   additional_heat (Btu/hr)
    function("gasLoadChargeMaterialTotalHeatRequired", &totalHeatRequired);
}

// leakageHeatLoss
EMSCRIPTEN_BINDINGS(leakage_heat_loss) {
    using namespace leakage_heat_loss;
    function("leakageTotalHeatLoss", &totalHeatLoss);
}

// liquidCoolingLosses
EMSCRIPTEN_BINDINGS(liquid_cooling_heat_loss) {
    // double flow_rate, double density, double initial_temperature, double outlet_temperature, double specific_heat,
    // double correction_factor
    using namespace liquid_cooling_heat_loss;
    function("liquidCoolingTotalHeatLoss", &totalHeatLoss);
}

// liquidLoadChargeMaterial
EMSCRIPTEN_BINDINGS(liquidLoadChargeMaterial) {
    using namespace liquid_load_charge_material_heat_required;
    // Parameters for liquidLoadChargeMaterialTotalHeatRequired:
    //   thermic_reaction_type (enum: ENDOTHERMIC, EXOTHERMIC, NONE)
    //   specific_heat_liquid (Btu/lb°F)
    //   vaporizing_temperature (°F)
    //   latent_heat (Btu/lb)
    //   specific_heat_vapor (Btu/lb°F)
    //   charge_feed_rate (lb/hr)
    //   initial_temperature (°F)
    //   discharge_temperature (°F)
    //   percent_vaporized (% of total)
    //   percent_reacted (% of total)
    //   reaction_heat (Btu/lb)
    //   additional_heat (Btu/hr)
    function("liquidLoadChargeMaterialTotalHeatRequired", &totalHeatRequired);
}

// openingLossesCircular
// openingLossesQuad
// viewFactorCalculation
EMSCRIPTEN_BINDINGS(openingLosses) {
    using namespace opening_heat_loss;
    function("openingTotalHeatLossQuad", &totalHeatLossQuad);
    function("openingTotalHeatLossCircular", &totalHeatLossCircular);
    function("calculateViewFactorCircular", &calculateViewFactorCircular);
    function("calculateViewFactorQuad", &calculateViewFactorQuad);
}

// slagOtherMaterialLosses
EMSCRIPTEN_BINDINGS(slagOtherMaterialLosses) {
    using namespace slag_other_material_heat_loss;
    function("slagOtherMaterialTotalHeatLoss", &totalHeatLoss);
}

// solidLoadChargeMaterial
EMSCRIPTEN_BINDINGS(solid_load_charge_material_heat_required) {
    using namespace solid_load_charge_material_heat_required;
    // Parameters for solidLoadChargeMaterialTotalHeatRequired:
    //   thermic_reaction_type (enum: ENDOTHERMIC, EXOTHERMIC, NONE)
    //   specific_heat_solid (Btu/lb°F)
    //   latent_heat (Btu/lb)
    //   specific_heat_liquid (Btu/lb°F)
    //   melting_point (°F)
    //   charge_feed_rate (lb/hr)
    //   water_content_charged (% of total)
    //   water_content_discharged (% of total)
    //   initial_temperature (°F)
    //   discharge_temperature (°F)
    //   water_vapor_discharge_temperature (°F)
    //   charge_melted (% of dry charge)
    //   charge_reacted (% of dry charge)
    //   reaction_heat (Btu/lb)
    //   additional_heat (Btu/hr)
    function("solidLoadChargeMaterialTotalHeatRequired", &totalHeatRequired);
}

// Bindings for the wall_heat_loss namespace
EMSCRIPTEN_BINDINGS(wall_heat_loss) {
    using namespace wall_heat_loss;
    function("wallTotalHeatLoss", &totalHeatLoss);
    function("wallConvectiveHeatLoss", &convectiveHeatLoss);
    function("wallRadiativeHeatLoss", &radiativeHeatLoss);
}

// waterCoolingLosses
EMSCRIPTEN_BINDINGS(water_cooling_heat_loss) {
    using namespace water_cooling_heat_loss;
    function("waterCoolingTotalHeatLoss", &totalHeatLoss);
}
