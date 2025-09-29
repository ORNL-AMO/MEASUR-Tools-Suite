#pragma once

#include <vector>

#include "motorDriven/motor/MotorData.h"
#include "processHeat/losses/gas_flue_gas_material.h"
#include "processHeat/losses/gas_load_charge_material.h"
#include "processHeat/losses/liquid_load_charge_material.h"
#include "processHeat/losses/solid_liquid_flue_gas_material.h"
#include "processHeat/losses/solid_load_charge_material.h"
#include "compressedAir/compressors_data.h"
#include "other/lighting_data.h"

class SolidLoadChargeMaterial;
class LiquidLoadChargeMaterial;
class GasLoadChargeMaterial;
class GasCompositions;
class SolidLiquidFlueGasMaterial;
class WallLosses;
class MotorData;
class CompressorsData;
class LightingData;

class DefaultData {
  public:
    DefaultData() = default;

    virtual ~DefaultData() = default;

    std::vector<SolidLoadChargeMaterial> getSolidLoadChargeMaterials() {
        std::vector<SolidLoadChargeMaterial> material = get_default_solid_load_charge_materials();
        auto                                 size     = (int)material.size();
        for (auto i = 0; i < size; i++) {
            (material[i]).setID(i + 1);
        }
        return material;
    }

    std::vector<GasLoadChargeMaterial> getGasLoadChargeMaterials() {
        std::vector<GasLoadChargeMaterial> material = get_default_gas_load_charge_materials();
        auto                               size     = (int)material.size();
        for (auto i = 0; i < size; i++) {
            (material[i]).setID(i + 1);
        }
        return material;
    }

    std::vector<LiquidLoadChargeMaterial> getLiquidLoadChargeMaterials() {
        std::vector<LiquidLoadChargeMaterial> material = get_default_liquid_load_charge_materials();
        auto                                  size     = (int)material.size();
        for (auto i = 0; i < size; i++) {
            (material[i]).setID(i + 1);
        }
        return material;
    }

    std::vector<SolidLiquidFlueGasMaterial> getSolidLiquidFlueGasMaterials() {
        std::vector<SolidLiquidFlueGasMaterial> material = get_default_solid_liquid_flue_gas_materials();
        auto                                    size     = (int)material.size();
        for (auto i = 0; i < size; i++) {
            (material[i]).setID(i + 1);
        }
        return material;
    }

    std::vector<GasCompositions> getGasFlueGasMaterials() {
        std::vector<GasCompositions> material = get_default_gas_flue_gas_materials();
        auto                         size     = (int)material.size();
        for (auto i = 0; i < size; i++) {
            (material[i]).setID(i + 1);
        }
        return material;
    }

    std::vector<MotorData> getMotorData() {
        std::vector<MotorData> motorData = get_default_motor_data();
        auto                   size      = (int)motorData.size();
        for (auto i = 0; i < size; i++) {
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
    std::vector<SolidLoadChargeMaterial>    get_default_solid_load_charge_materials();
    std::vector<GasLoadChargeMaterial>      get_default_gas_load_charge_materials();
    std::vector<LiquidLoadChargeMaterial>   get_default_liquid_load_charge_materials();
    std::vector<SolidLiquidFlueGasMaterial> get_default_solid_liquid_flue_gas_materials();
    std::vector<GasCompositions>            get_default_gas_flue_gas_materials();
    std::vector<MotorData>                  get_default_motor_data();
    std::vector<CompressorsData>            get_default_compressor_data();
    std::vector<LightingData>               get_default_lighting_data();
};
