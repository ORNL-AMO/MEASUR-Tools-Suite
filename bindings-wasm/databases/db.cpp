#include "databases/DB.h"
#include "databases/MotorData.h"
#include "databases/AtmosphereSpecificHeatData.h"
#include "databases/GasFlueGasMaterialData.h"
#include "databases/GasLoadChargeMaterialData.h"
#include "databases/LiquidLoadChargeMaterialData.h"
#include "databases/SolidLoadChargeMaterialData.h"
#include "databases/SolidLiquidFlueGasMaterialData.h"
#include "databases/WallLossesSurfaceData.h"
#include <processHeat/losses/SolidLoadChargeMaterial.h>
#include <processHeat/losses/LiquidLoadChargeMaterial.h>
#include <processHeat/losses/GasLoadChargeMaterial.h>
#include <processHeat/losses/GasFlueGasMaterial.h>
#include <processHeat/losses/SolidLiquidFlueGasMaterial.h>
#include <processHeat/losses/Atmosphere.h>
#include <processHeat/losses/wall_losses.h>
#include <motorDriven/motor/MotorData.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(db_class)
{
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
