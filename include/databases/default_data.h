#pragma once

#include <vector>

#include "compressedAir/assessment/compressor_catalog.h"
#include "motorDriven/motor/MotorData.h"
#include "other/lighting_data.h"
#include "processHeat/losses/solid_liquid_flue_gas_material.h"

class MotorData;
class LightingData;

class DefaultData {
public:
    using CompressorCatalogRecord = compressed_air::assessment::CompressorCatalogRecord;

    DefaultData() = default;

    virtual ~DefaultData() = default;

    std::vector<MotorData> getMotorData() {
        std::vector<MotorData> motorData = get_default_motor_data();
        auto size = (int)motorData.size();
        for (auto i = 0; i < size; i++) {
            motorData.at(i).id = i + 1;
        }
        return motorData;
    }

    std::vector<CompressorCatalogRecord> getCompressorType1Data() {
        std::vector<CompressorCatalogRecord> compressorData = compressors_type1_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).id = i + 1;
        }
        return compressorData;
    }

    std::vector<CompressorCatalogRecord> getCompressorType1_GT100kWData() {
        std::vector<CompressorCatalogRecord> compressorData = compressors_type1_GT_100kW_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).id = i + 1;
        }
        return compressorData;
    }

    std::vector<CompressorCatalogRecord> getCompressorType2Data() {
        std::vector<CompressorCatalogRecord> compressorData = compressors_type2_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).id = i + 1;
        }
        return compressorData;
    }

    std::vector<CompressorCatalogRecord> getCompressorType3Data() {
        std::vector<CompressorCatalogRecord> compressorData = compressors_type3_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).id = i + 1;
        }
        return compressorData;
    }

    std::vector<CompressorCatalogRecord> getCompressorType4Data() {
        std::vector<CompressorCatalogRecord> compressorData = compressors_type4_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).id = i + 1;
        }
        return compressorData;
    }

    std::vector<CompressorCatalogRecord> getCompressorType5Data() {
        std::vector<CompressorCatalogRecord> compressorData = compressors_type5_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).id = i + 1;
        }
        return compressorData;
    }

    std::vector<CompressorCatalogRecord> getCompressorType6Data() {
        std::vector<CompressorCatalogRecord> compressorData = compressors_type6_data();
        auto size = (int)compressorData.size();
        for(auto i = 0; i < size; i++) {
            compressorData.at(i).id = i + 1;
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
    std::vector<MotorData>                get_default_motor_data();
    std::vector<CompressorCatalogRecord>  compressors_type1_data();
    std::vector<CompressorCatalogRecord>  compressors_type1_GT_100kW_data();
    std::vector<CompressorCatalogRecord>  compressors_type2_data();
    std::vector<CompressorCatalogRecord>  compressors_type3_data();
    std::vector<CompressorCatalogRecord>  compressors_type4_data();
    std::vector<CompressorCatalogRecord>  compressors_type5_data();
    std::vector<CompressorCatalogRecord>  compressors_type6_data();
    std::vector<LightingData>             get_default_lighting_data();
};
