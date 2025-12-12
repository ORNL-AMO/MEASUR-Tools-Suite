#include "databases/default_data.h"

#include <emscripten/bind.h>

#include "compressedAir/compressors_data.h"
#include "databases/compressors_type1_data.h"
#include "databases/compressors_type1_GT_100kW_data.h"
#include "databases/compressors_type2_data.h"
#include "databases/compressors_type3_data.h"
#include "databases/compressors_type4_data.h"
#include "databases/compressors_type5_data.h"
#include "databases/compressors_type6_data.h"
#include "databases/gas_load_charge_material_data.h"
#include "databases/lighting_data.h"
#include "databases/MotorData.h"
#include "databases/SolidLiquidFlueGasMaterialData.h"
#include "motorDriven/motor/MotorData.h"
#include "other/lighting_data.h"
#include "processHeat/losses/solid_liquid_flue_gas_material.h"
#include "databases/liquid_load_charge_material_data.h"
#include "databases/solid_load_charge_material_data.h"
#include "databases/gas_flue_gas_material_data.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(db_class) {

    class_<DefaultData>("DefaultData")
        .constructor<>()
        .function("getSolidLiquidFlueGasMaterials", &DefaultData::getSolidLiquidFlueGasMaterials)
        .function("getMotorData", &DefaultData::getMotorData)
        .function("getCompressorType1Data", &DefaultData::getCompressorType1Data)
        .function("getCompressorType1_GT100kWData", &DefaultData::getCompressorType1_GT100kWData)
        .function("getCompressorType2Data", &DefaultData::getCompressorType2Data)
        .function("getCompressorType3Data", &DefaultData::getCompressorType3Data)
        .function("getCompressorType4Data", &DefaultData::getCompressorType4Data)
        .function("getCompressorType5Data", &DefaultData::getCompressorType5Data)
        .function("getCompressorType6Data", &DefaultData::getCompressorType6Data)
        .function("getLightingData", &DefaultData::getLightingData);
}

EMSCRIPTEN_BINDINGS(gas_load_charge_material_data) {
    using namespace gas_load_charge_material_data;
    value_object<GasLoadChargeMaterial>("GasLoadChargeMaterial")
        .field("substance", &GasLoadChargeMaterial::substance)
        .field("specificHeatVapor", &GasLoadChargeMaterial::specific_heat_vapor);

    register_vector<GasLoadChargeMaterial>("GasLoadChargeMaterialV");
    function("getDefaultGasLoadChargeMaterials", &get_default_gas_load_charge_materials);
}

EMSCRIPTEN_BINDINGS(liquid_load_charge_material_data) {
    using namespace liquid_load_charge_material_data;
    value_object<LiquidLoadChargeMaterial>("LiquidLoadChargeMaterial")
        .field("substance", &LiquidLoadChargeMaterial::substance)
        .field("specificHeat", &LiquidLoadChargeMaterial::specific_heat)
        .field("latentHeat", &LiquidLoadChargeMaterial::latent_heat)
        .field("vaporSpecificHeat", &LiquidLoadChargeMaterial::vapor_specific_heat)
        .field("boilingPoint", &LiquidLoadChargeMaterial::boiling_point);

    register_vector<LiquidLoadChargeMaterial>("LiquidLoadChargeMaterialV");
    function("getDefaultLiquidLoadChargeMaterials", &get_default_liquid_load_charge_materials);
}

EMSCRIPTEN_BINDINGS(solid_load_charge_material_data) {
    using namespace solid_load_charge_material_data;
    value_object<SolidLoadChargeMaterial>("SolidLoadChargeMaterial")
        .field("substance", &SolidLoadChargeMaterial::substance)
        .field("specificHeatSolid", &SolidLoadChargeMaterial::specific_heat_solid)
        .field("latentHeat", &SolidLoadChargeMaterial::latent_heat)
        .field("specificHeatLiquid", &SolidLoadChargeMaterial::specific_heat_liquid)
        .field("meltingPoint", &SolidLoadChargeMaterial::melting_point);

    register_vector<SolidLoadChargeMaterial>("SolidLoadChargeMaterialV");
    function("getDefaultSolidLoadChargeMaterials", &get_default_solid_load_charge_materials);
}

EMSCRIPTEN_BINDINGS(gas_flue_gas_material_data) {
    using namespace gas_flue_gas_material_data;
    value_object<GasFlueGasMaterial>("GasFlueGasMaterial")
        .field("substance", &GasFlueGasMaterial::substance)
        .field("ch4", &GasFlueGasMaterial::ch4)
        .field("c2h6", &GasFlueGasMaterial::c2h6)
        .field("n2", &GasFlueGasMaterial::n2)
        .field("h2", &GasFlueGasMaterial::h2)
        .field("c3h8", &GasFlueGasMaterial::c3h8)
        .field("c4h10_cnh2n", &GasFlueGasMaterial::c4h10_cnh2n)
        .field("h2o", &GasFlueGasMaterial::h2o)
        .field("co", &GasFlueGasMaterial::co)
        .field("co2", &GasFlueGasMaterial::co2)
        .field("so2", &GasFlueGasMaterial::so2)
        .field("o2", &GasFlueGasMaterial::o2)
        .field("heatingValue", &GasFlueGasMaterial::heating_value)
        .field("heatingValueVolume", &GasFlueGasMaterial::heating_value_volume)
        .field("specificGravity", &GasFlueGasMaterial::specific_gravity);

    register_vector<GasFlueGasMaterial>("GasFlueGasMaterialV");
    function("getDefaultGasFlueGasMaterials", &get_default_gas_flue_gas_materials);
}