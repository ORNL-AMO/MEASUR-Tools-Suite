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
#include "databases/GasFlueGasMaterialData.h"
#include "databases/gas_load_charge_material_data.h"
#include "databases/lighting_data.h"
#include "databases/MotorData.h"
#include "databases/SolidLiquidFlueGasMaterialData.h"
#include "databases/SolidLoadChargeMaterialData.h"
#include "motorDriven/motor/MotorData.h"
#include "other/lighting_data.h"
#include "processHeat/losses/gas_flue_gas_material.h"
#include "processHeat/losses/solid_liquid_flue_gas_material.h"
#include "processHeat/losses/solid_load_charge_material.h"
#include "databases/liquid_load_charge_material_data.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(db_class) {

    class_<DefaultData>("DefaultData")
        .constructor<>()
        .function("getSolidLoadChargeMaterials", &DefaultData::getSolidLoadChargeMaterials)
        .function("getSolidLiquidFlueGasMaterials", &DefaultData::getSolidLiquidFlueGasMaterials)
        .function("getGasFlueGasMaterials", &DefaultData::getGasFlueGasMaterials)
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