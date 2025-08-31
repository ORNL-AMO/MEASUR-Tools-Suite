#ifndef TOOLS_SUITE_DB_H
#define TOOLS_SUITE_DB_H

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "motorDriven/motor/MotorData.h"
#include "processHeat/losses/Atmosphere.h"
#include "processHeat/losses/GasFlueGasMaterial.h"
#include "processHeat/losses/GasLoadChargeMaterial.h"
#include "processHeat/losses/SolidLiquidFlueGasMaterial.h"
#include "processHeat/losses/LiquidLoadChargeMaterial.h"
#include "processHeat/losses/SolidLoadChargeMaterial.h"
#include "processHeat/losses/WallLosses.h"
#include "compressedAir/compressors_data.h"
#include "other/lighting_data.h"

class SolidLoadChargeMaterial;
class LiquidLoadChargeMaterial;
class GasLoadChargeMaterial;
class GasCompositions;
class SolidLiquidFlueGasMaterial;
class Atmosphere;
class WallLosses;
class MotorData;
class CompressorsData;
class LightingData;

class DefaultData
{
public:
    DefaultData() = default;

    virtual ~DefaultData() = default;

    std::vector<SolidLoadChargeMaterial> getSolidLoadChargeMaterials() {
        std::vector<SolidLoadChargeMaterial> material = get_default_solid_load_charge_materials();
        auto size = (int)material.size();
        for(auto i = 0; i < size; i++) {
            (material[i]).setID(i+1);
        }
        return material;
    }

    std::vector<GasLoadChargeMaterial> getGasLoadChargeMaterials() {
        std::vector<GasLoadChargeMaterial> material = get_default_gas_load_charge_materials();
        auto size = (int)material.size();
        for(auto i = 0; i < size; i++) {
            (material[i]).setID(i+1);
        }
        return material;
    }

    std::vector<LiquidLoadChargeMaterial> getLiquidLoadChargeMaterials() {
        std::vector<LiquidLoadChargeMaterial> material = get_default_liquid_load_charge_materials();
        auto size = (int)material.size();
        for(auto i = 0; i < size; i++) {
            (material[i]).setID(i+1);
        }
        return material;
    }

    std::vector<SolidLiquidFlueGasMaterial> getSolidLiquidFlueGasMaterials() {
        std::vector<SolidLiquidFlueGasMaterial> material = get_default_solid_liquid_flue_gas_materials();
        auto size = (int)material.size();
        for(auto i = 0; i < size; i++) {
            (material[i]).setID(i+1);
        }
        return material;
    }

    std::vector<GasCompositions> getGasFlueGasMaterials() {
        std::vector<GasCompositions> material = get_default_gas_flue_gas_materials();
        auto size = (int)material.size();
        for(auto i = 0; i < size; i++) {
            (material[i]).setID(i+1);
        }
        return material;
    }

    std::vector<Atmosphere> getAtmosphereSpecificHeat() {
        std::vector<Atmosphere> specificHeat = get_default_atmosphere_specific_heat();
        auto size = (int)specificHeat.size();
        for(auto i = 0; i < size; i++) {
            (specificHeat[i]).setID(i+1);
        }
        return specificHeat;
    }

    std::vector<WallLosses> getWallLossesSurface() {
        std::vector<WallLosses> wallLossesSurface = get_default_wall_losses_surface();
        auto size = (int)wallLossesSurface.size();
        for(auto i = 0; i < size; i++) {
            (wallLossesSurface[i]).setID(i+1);
        }
        return wallLossesSurface;
    }

    std::vector<MotorData> getMotorData() {
        std::vector<MotorData> motorData = get_default_motor_data();
        auto size = (int)motorData.size();
        for(auto i = 0; i < size; i++) {
            motorData.at(i).id = i + 1;
        }
        return motorData;
    }

    std::vector<CompressorsData> getCompressorData() {
        std::vector<CompressorsData> compressorData = get_default_compressor_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).setID(i + 1);
        }
        return compressorData;
    }

    std::vector<LightingData> getLightingData() {
        std::vector<LightingData> lightingData = get_default_lighting_data();
        auto size = (int)lightingData.size();
        for(auto i = 0; i < size; i++) {
            lightingData.at(i).setID(i + 1);
        }
        return lightingData;
    }

private:
    std::vector<SolidLoadChargeMaterial> get_default_solid_load_charge_materials();
    std::vector<GasLoadChargeMaterial> get_default_gas_load_charge_materials();
    std::vector<LiquidLoadChargeMaterial> get_default_liquid_load_charge_materials();
    std::vector<SolidLiquidFlueGasMaterial> get_default_solid_liquid_flue_gas_materials();
    std::vector<GasCompositions> get_default_gas_flue_gas_materials();
    std::vector<Atmosphere> get_default_atmosphere_specific_heat();
    std::vector<WallLosses> get_default_wall_losses_surface();
    std::vector<MotorData> get_default_motor_data();
    std::vector<CompressorsData> get_default_compressor_data();
    std::vector<LightingData> get_default_lighting_data();
};

#endif //TOOLS_SUITE_DB_H
