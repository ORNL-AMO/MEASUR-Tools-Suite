#include "databases/DB.h"

#include <emscripten/bind.h>

#include "databases/AtmosphereSpecificHeatData.h"
#include "databases/GasFlueGasMaterialData.h"
#include "databases/GasLoadChargeMaterialData.h"
#include "databases/LiquidLoadChargeMaterialData.h"
#include "databases/MotorData.h"
#include "databases/SolidLiquidFlueGasMaterialData.h"
#include "databases/SolidLoadChargeMaterialData.h"
#include "databases/WallLossesSurfaceData.h"
#include "motorDriven/motor/MotorData.h"
#include "processHeat/losses/atmosphere.h"
#include "processHeat/losses/gas_flue_gas_material.h"
#include "processHeat/losses/gas_load_charge_material.h"
#include "processHeat/losses/liquid_load_charge_material.h"
#include "processHeat/losses/solid_liquid_flue_gas_material.h"
#include "processHeat/losses/solid_load_charge_material.h"
#include "processHeat/losses/wall_losses.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(db_class) {
    class_<DefaultData>("DefaultData")
        .constructor<>()

        .function("getSolidLoadChargeMaterials", &DefaultData::getSolidLoadChargeMaterials)
        .function("getGasLoadChargeMaterials", &DefaultData::getGasLoadChargeMaterials)
        .function("getLiquidLoadChargeMaterials", &DefaultData::getLiquidLoadChargeMaterials)
        .function("getSolidLiquidFlueGasMaterials", &DefaultData::getSolidLiquidFlueGasMaterials)
        .function("getGasFlueGasMaterials", &DefaultData::getGasFlueGasMaterials)
        .function("getAtmosphereSpecificHeat", &DefaultData::getAtmosphereSpecificHeat)
        .function("getWallLossesSurface", &DefaultData::getWallLossesSurface)
        .function("getMotorData", &DefaultData::getMotorData);
}
