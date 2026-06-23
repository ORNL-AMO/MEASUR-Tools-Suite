#pragma once

/**
 * @ingroup compressor_catalog_units
 * @file compressor_catalog.h
 * @brief Compressor default catalog record declarations.
 */

#include <string>
#include <utility>

namespace compressed_air::assessment {

/**
 * @struct CompressorCatalogRecord
 * @brief One default compressor catalog record used by assessment workflows.
 */
struct CompressorCatalogRecord {
    int         id                         = 0;   ///< Sequential catalog record ID @unitb{\unitless}.
    int         compressorTypeId           = 0;   ///< Compressor type identifier @unitb{\unitless}.
    std::string model                      = "";  ///< Compressor model name.
    double      horsepower                 = 0.0; ///< Rated motor size @unitb{\hp}.
    double      ratedCapacityAcfm          = 0.0; ///< Rated compressor capacity @unitb{\acfm}.
    double      ratedPressurePsig          = 0.0; ///< Rated discharge pressure @unitb{\psig}.
    double      maxFullFlowPressurePsig    = 0.0; ///< Maximum full-flow pressure @unitb{\psig}.
    int         controlTypeId              = 0;   ///< Control type identifier @unitb{\unitless}.
    double      unloadPointPercent         = 0.0; ///< Unload point @unitb{\percent}.
    double      minUnloadSumpPressurePsig  = 0.0; ///< Minimum unload sump pressure @unitb{\psig}.
    double      blowdownTimeSec            = 0.0; ///< Blowdown time @unitb{\second}.
    double      unloadSteps                = 0.0; ///< Unload steps @unitb{\unitless}.
    double      modulatingPressureRangePsig = 0.0; ///< Modulating pressure range @unitb{\psig}.
    double      fullLoadBhpPowerKw         = 0.0; ///< Full-load brake horsepower equivalent power @unitb{\kilo\watt}.
    double      totalPackageInputPowerKw   = 0.0; ///< Total package input power @unitb{\kilo\watt}.
    double      specificPackagePower       = 0.0; ///< Specific package power @unitb{\kilo\watt\per\acfm}.
    double      noLoadPowerFullyModulating = 0.0; ///< No-load fully modulating power fraction @unitb{\unitless}.
    double      noLoadPowerUnload          = 0.0; ///< No-load unload power fraction @unitb{\unitless}.
    double      maxSurgePressurePsig       = 0.0; ///< Maximum surge pressure @unitb{\psig}.
    double      maxSurgePressureFlowAcfm   = 0.0; ///< Flow at maximum surge pressure @unitb{\acfm}.
    double      minStonewallPressurePsig   = 0.0; ///< Minimum stonewall pressure @unitb{\psig}.
    double      minStonewallPressureFlowAcfm = 0.0; ///< Flow at minimum stonewall pressure @unitb{\acfm}.
    double      designSurgeFlowAcfm        = 0.0; ///< Design surge flow @unitb{\acfm}.
    double      designInletTemperatureF    = 0.0; ///< Design inlet temperature @unitb{\degreeFahrenheit}.
    double      designInletPressurePsia    = 0.0; ///< Design inlet pressure @unitb{\psia}.
    double      fullLoadAmps               = 0.0; ///< Full-load current @unitb{\ampere}.
    double      fullLoadEfficiencyPercent  = 0.0; ///< Full-load efficiency @unitb{\percent}.

    CompressorCatalogRecord() = default;

    CompressorCatalogRecord(int compressor_type_id, std::string model_name, double hp, double rated_capacity,
                            double rated_pressure, double max_full_flow_pressure, int control_type_id,
                            double unload_point, double min_unload_sump_pressure, double blowdown_time,
                            double unload_step_count, double modulating_pressure_range, double full_load_bhp_power,
                            double total_package_input_power, double specific_package_power_value,
                            double no_load_power_fully_modulating_value, double no_load_power_unload_value,
                            double max_surge_pressure, double max_surge_pressure_flow,
                            double min_stonewall_pressure, double min_stonewall_pressure_flow,
                            double design_surge_flow, double design_inlet_temperature,
                            double design_inlet_pressure, double full_load_current, double full_load_efficiency)
        : compressorTypeId(compressor_type_id), model(std::move(model_name)), horsepower(hp),
          ratedCapacityAcfm(rated_capacity), ratedPressurePsig(rated_pressure),
          maxFullFlowPressurePsig(max_full_flow_pressure), controlTypeId(control_type_id),
          unloadPointPercent(unload_point), minUnloadSumpPressurePsig(min_unload_sump_pressure),
          blowdownTimeSec(blowdown_time), unloadSteps(unload_step_count),
          modulatingPressureRangePsig(modulating_pressure_range), fullLoadBhpPowerKw(full_load_bhp_power),
          totalPackageInputPowerKw(total_package_input_power), specificPackagePower(specific_package_power_value),
          noLoadPowerFullyModulating(no_load_power_fully_modulating_value),
          noLoadPowerUnload(no_load_power_unload_value), maxSurgePressurePsig(max_surge_pressure),
          maxSurgePressureFlowAcfm(max_surge_pressure_flow), minStonewallPressurePsig(min_stonewall_pressure),
          minStonewallPressureFlowAcfm(min_stonewall_pressure_flow), designSurgeFlowAcfm(design_surge_flow),
          designInletTemperatureF(design_inlet_temperature), designInletPressurePsia(design_inlet_pressure),
          fullLoadAmps(full_load_current), fullLoadEfficiencyPercent(full_load_efficiency) {}
};

} // namespace compressed_air::assessment
