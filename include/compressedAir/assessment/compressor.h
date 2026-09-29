#pragma once

/**
 * @ingroup compressor_modeling_overview
 * @file compressor.h
 * @brief Shared compressor assessment enums, result objects, and base utilities.
 * @details Compressor assessment models estimate compressor package power and
 *          airflow from a selected control strategy and measurement basis.
 *          All calculations use U.S. customary compressed-air assessment units.
 */

#include <vector>

/**
 * @ingroup compressor_modeling_overview
 * @namespace compressed_air::assessment
 * @brief Compressor assessment performance models and supporting calculations.
 */
namespace compressed_air::assessment {

/**
 * @enum CompressorType
 * @brief Compressor mechanical type.
 */
enum class CompressorType {
    Centrifugal   = 0, ///< Centrifugal compressor.
    Screw         = 1, ///< Rotary screw compressor.
    Reciprocating = 2  ///< Reciprocating compressor.
};

/**
 * @enum CompressorControl
 * @brief Compressor control strategy.
 */
enum class CompressorControl {
    LoadUnload                = 0, ///< Load/unload control.
    ModulationUnload          = 1, ///< Modulation with unloading.
    BlowOff                   = 2, ///< Blow-off control.
    ModulationWithoutUnload   = 3, ///< Modulation without unloading.
    StartStop                 = 4, ///< Start/stop control.
    VariableDisplacementUnload = 5, ///< Variable displacement with unloading.
    MultiStepUnloading        = 6, ///< Multi-step unloading.
    Vfd                       = 7  ///< Variable frequency drive control.
};

/**
 * @enum CompressorStage
 * @brief Compressor stage arrangement.
 */
enum class CompressorStage {
    Single   = 0, ///< Single-stage compressor.
    Two      = 1, ///< Two-stage compressor.
    Multiple = 2  ///< Multiple-stage compressor.
};

/**
 * @enum CompressorLubricant
 * @brief Compressor lubricant configuration.
 */
enum class CompressorLubricant {
    Injected = 0, ///< Lubricant-injected compressor.
    Free     = 1, ///< Oil-free compressor.
    None     = 2  ///< No lubricant selection.
};

/**
 * @enum CompressorInputBasis
 * @brief Measurement basis used to calculate performance.
 */
enum class CompressorInputBasis {
    PowerFraction    = 0, ///< Input is fraction of full-load power.
    CapacityFraction = 1, ///< Input is fraction of full-load airflow.
    MeasuredPower    = 2, ///< Input is measured package power @unitb{\kilo\watt}.
    MeasuredCapacity = 3, ///< Input is measured airflow @unitb{\acfm}.
    Electrical       = 4  ///< Input is voltage, current, and power factor.
};

/**
 * @struct CompressorPerformanceResult
 * @brief Standard compressor model result.
 */
struct CompressorPerformanceResult {
    double powerKw         = 0.0; ///< Calculated compressor package power @unitb{\kilo\watt}.
    double airflowAcfm     = 0.0; ///< Calculated compressor airflow @unitb{\acfm}.
    double powerFraction   = 0.0; ///< Calculated fraction of full-load power @unitb{\unitless}.
    double airflowFraction = 0.0; ///< Calculated fraction of full-load airflow @unitb{\unitless}.
};

/**
 * @struct CompressorBlowOffResult
 * @brief Compressor model result for blow-off controls.
 */
struct CompressorBlowOffResult {
    double powerKw              = 0.0; ///< Calculated compressor package power @unitb{\kilo\watt}.
    double airflowAcfm          = 0.0; ///< Calculated useful compressor airflow @unitb{\acfm}.
    double powerFraction        = 0.0; ///< Calculated fraction of full-load power @unitb{\unitless}.
    double airflowFraction      = 0.0; ///< Calculated fraction of full-load useful airflow @unitb{\unitless}.
    double blowOffAirflowAcfm   = 0.0; ///< Calculated blow-off airflow @unitb{\acfm}.
    double blowOffFraction      = 0.0; ///< Calculated fraction of full-load airflow blown off @unitb{\unitless}.
};

/**
 * @class CompressorModelBase
 * @brief Base utilities shared by compressor assessment control models.
 */
class CompressorModelBase {
  public:
    double adjustedFullLoadPowerKw() const { return full_load_power_adjusted_; }
    double adjustedFullLoadAirflowAcfm() const { return full_load_airflow_adjusted_; }
    double adjustedMaxPowerKw() const { return max_power_adjusted_; }
    double adjustedMaxAirflowAcfm() const { return max_airflow_adjusted_; }

  protected:
    CompressorModelBase(double full_load_power, double full_load_airflow)
        : full_load_power_(full_load_power), full_load_airflow_(full_load_airflow),
          full_load_airflow_raw_(full_load_airflow), full_load_power_raw_(full_load_power),
          full_load_power_adjusted_(full_load_power), full_load_airflow_adjusted_(full_load_airflow),
          max_airflow_adjusted_(0.0), max_power_adjusted_(0.0) {}

    static double roundDouble(double value);

    void applyPressureInletCorrection(CompressorType compressor_type, double capacity, double full_load_bhp,
                                      double poly_exponent, double rated_discharge_pressure,
                                      double rated_inlet_pressure, double efficiency, double full_load_pressure,
                                      double max_pressure, double inlet_pressure, bool pressure_adjustment,
                                      double atmospheric_pressure);

    double full_load_power_;
    double full_load_airflow_;
    const double full_load_airflow_raw_;
    const double full_load_power_raw_;

    double full_load_power_adjusted_;
    double full_load_airflow_adjusted_;
    double max_airflow_adjusted_;
    double max_power_adjusted_;

  private:
    void applyPressureInletCorrection(double& capacity_adjusted, double& power_adjusted, CompressorType compressor_type,
                                      double capacity, double full_load_bhp, double poly_exponent,
                                      double rated_discharge_pressure, double rated_inlet_pressure, double efficiency,
                                      double discharge_pressure, double inlet_pressure, bool pressure_adjustment,
                                      double atmospheric_pressure);

    static double pressureRatioCorrection(double poly_exponent, double rated_pressure_ratio,
                                          double operating_pressure, double pressure_ratio_base);
};

} // namespace compressed_air::assessment
