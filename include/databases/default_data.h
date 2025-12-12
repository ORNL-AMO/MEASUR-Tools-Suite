#pragma once

#include <vector>

#include "motorDriven/motor/MotorData.h"
#include "processHeat/losses/solid_liquid_flue_gas_material.h"
#include "compressedAir/compressors_data.h"
#include "other/lighting_data.h"

class SolidLiquidFlueGasMaterial;
class MotorData;
class CompressorsData;
class LightingData;

class DefaultData {
public:
    DefaultData() = default;

    virtual ~DefaultData() = default;

    std::vector<SolidLiquidFlueGasMaterial> getSolidLiquidFlueGasMaterials() {
        std::vector<SolidLiquidFlueGasMaterial> material = get_default_solid_liquid_flue_gas_materials();
        auto size = (int)material.size();
        for (auto i = 0; i < size; i++) {
            (material[i]).setID(i + 1);
        }
        return material;
    }

    std::vector<MotorData> getMotorData() {
        std::vector<MotorData> motorData = get_default_motor_data();
        auto size = (int)motorData.size();
        for (auto i = 0; i < size; i++) {
            motorData.at(i).id = i + 1;
        }
        return motorData;
    }

    std::vector<CompressorsData> getCompressorType1Data() {
        std::vector<CompressorsData> compressorData = compressors_type1_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).setID(i + 1);
        }
        return compressorData;
    }

    std::vector<CompressorsData> getCompressorType1_GT100kWData() {
        std::vector<CompressorsData> compressorData = compressors_type1_GT_100kW_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).setID(i + 1);
        }
        return compressorData;
    }

    std::vector<CompressorsData> getCompressorType2Data() {
        std::vector<CompressorsData> compressorData = compressors_type2_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).setID(i + 1);
        }
        return compressorData;
    }

    std::vector<CompressorsData> getCompressorType3Data() {
        std::vector<CompressorsData> compressorData = compressors_type3_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).setID(i + 1);
        }
        return compressorData;
    }

    std::vector<CompressorsData> getCompressorType4Data() {
        std::vector<CompressorsData> compressorData = compressors_type4_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).setID(i + 1);
        }
        return compressorData;
    }

    std::vector<CompressorsData> getCompressorType5Data() {
        std::vector<CompressorsData> compressorData = compressors_type5_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).setID(i + 1);
        }
        return compressorData;
    }

    std::vector<CompressorsData> getCompressorType6Data() {
        std::vector<CompressorsData> compressorData = compressors_type6_data();
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
    std::vector<SolidLiquidFlueGasMaterial> get_default_solid_liquid_flue_gas_materials();
    std::vector<MotorData>                  get_default_motor_data();
    std::vector<CompressorsData>            compressors_type1_data();
    std::vector<CompressorsData>            compressors_type1_GT_100kW_data();
    std::vector<CompressorsData>            compressors_type2_data();
    std::vector<CompressorsData>            compressors_type3_data();
    std::vector<CompressorsData>            compressors_type4_data();
    std::vector<CompressorsData>            compressors_type5_data();
    std::vector<CompressorsData>            compressors_type6_data();
    std::vector<LightingData>               get_default_lighting_data();
};
