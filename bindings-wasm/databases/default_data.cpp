#include "databases/default_data.h"

#include <emscripten/bind.h>

#include "databases/SolidLoadChargeMaterialData.h"
#include "databases/GasLoadChargeMaterialData.h"
#include "databases/LiquidLoadChargeMaterialData.h"
#include "databases/SolidLiquidFlueGasMaterialData.h"
#include "databases/GasFlueGasMaterialData.h"
#include "databases/MotorData.h"
#include "databases/compressors_data.h"
#include "databases/lighting_data.h"
#include "processHeat/losses/solid_load_charge_material.h"
#include "processHeat/losses/gas_load_charge_material.h"
#include "processHeat/losses/liquid_load_charge_material.h"
#include "processHeat/losses/solid_liquid_flue_gas_material.h"
#include "processHeat/losses/gas_flue_gas_material.h"
#include "motorDriven/motor/MotorData.h"
#include "compressedAir/compressors_data.h"
#include "other/lighting_data.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(db_class) {
    class_<DefaultData>("DefaultData")
        .constructor<>()
        .function("getSolidLoadChargeMaterials", &DefaultData::getSolidLoadChargeMaterials)
        .function("getGasLoadChargeMaterials", &DefaultData::getGasLoadChargeMaterials)
        .function("getLiquidLoadChargeMaterials", &DefaultData::getLiquidLoadChargeMaterials)
        .function("getSolidLiquidFlueGasMaterials", &DefaultData::getSolidLiquidFlueGasMaterials)
        .function("getGasFlueGasMaterials", &DefaultData::getGasFlueGasMaterials)
        .function("getMotorData", &DefaultData::getMotorData)
        .function("getCompressorData", &DefaultData::getCompressorData)
        .function("getLightingData", &DefaultData::getLightingData);
}
