#pragma once

/**
 * @ingroup steam_reduction_calculator
 * @file steam_reduction.h
 * @brief Declares structs, enums, and functions for the Steam Reduction Calculator.
 * @copybrief steam_reduction_calculator
 */

#include <vector>

#include "steamModeler/SteamProperties.h"

/**
 * @ingroup steam_reduction_calculator
 * @namespace steam_reduction
 * @brief Steam reduction calculations for treasure hunt measures.
 * @details Provides a function-based API for estimating annual steam use, energy use, and energy
 * cost for steam reduction measures identified during an energy treasure hunt. Supports four
 * measurement methods: flow meter, air mass flow, water mass flow, and offsheet.
 * @see steam_reduction_calculator
 */
namespace steam_reduction {

/**
 * @ingroup steam_reduction_calculator
 * @enum SteamMeasurementMethod
 * @brief Selects the measurement method used to determine steam use for a single measure.
 * @see steam_reduction_calculator
 */
enum class SteamMeasurementMethod {
    kFlowMeter    = 0, ///< Flow meter method — uses a direct steam or water flow meter reading
    kAirMassFlow  = 1, ///< Air mass flow method — derives steam use from air flow and temperature rise
    kWaterMassFlow = 2, ///< Water mass flow method — derives steam use from water flow and temperature rise
    kOffsheet     = 3  ///< Offsheet method — uses a directly supplied energy consumption value
};

/**
 * @ingroup steam_reduction_calculator
 * @enum UtilityType
 * @brief Selects the utility type used to calculate energy cost.
 * @see steam_reduction_calculator
 */
enum class UtilityType {
    kSteam      = 0, ///< Steam utility — energy cost is based on steam use @unitb{kg\per\hour}
    kNaturalGas = 1, ///< Natural gas utility — energy cost is based on energy use @unitb{kJ\per\year}
    kOther      = 2  ///< Other utility — energy cost is based on energy use @unitb{kJ\per\year}
};

/**
 * @ingroup steam_reduction_calculator
 * @struct FlowMeterMethodData
 * @brief Input data for the flow meter measurement method.
 * @details Used when steam or water use is measured with a flow meter. The flow rate is combined
 * with operating hours, units, and system efficiency to calculate steam use.
 * @see steam_reduction_flow_meter_formula
 */
struct FlowMeterMethodData {
    double flow_rate = 0.0; ///< Flow rate (water @unitb{m^3\per\minute}, steam @unitb{kg\per\hour})
};

/**
 * @ingroup steam_reduction_calculator
 * @struct MassFlowNameplateData
 * @brief Input data for nameplate-based mass flow measurement.
 * @details Used when the flow rate is taken directly from the equipment nameplate rather than
 * measured in the field.
 */
struct MassFlowNameplateData {
    double flow_rate = 0.0; ///< Nameplate flow rate (water @unitb{m^3\per\minute}, steam @unitb{kg\per\hour})
};

/**
 * @ingroup steam_reduction_calculator
 * @struct MassFlowMeasuredData
 * @brief Input data for field-measured mass flow.
 * @details Used when the flow rate is calculated from field measurements of duct area and
 * air velocity.
 */
struct MassFlowMeasuredData {
    double area_of_duct  = 0.0; ///< Cross-sectional area of the duct @unitb{m^2}
    double air_velocity  = 0.0; ///< Measured air velocity in the duct @unitb{m\per\minute}
};

/**
 * @ingroup steam_reduction_calculator
 * @struct MassFlowMethodData
 * @brief Input data for the air or water mass flow measurement method.
 * @details Aggregates all data needed for either the air mass flow or water mass flow method.
 * If @p is_nameplate is @c true, the nameplate flow rate is used; otherwise the flow rate is
 * derived from the measured duct area and air velocity.
 * @see steam_reduction_air_mass_flow_formula
 * @see steam_reduction_water_mass_flow_formula
 */
struct MassFlowMethodData {
    bool                 is_nameplate              = false; ///< True to use nameplate data; false to use measured data
    MassFlowMeasuredData mass_flow_measured_data;           ///< Field-measured duct area and air velocity
    MassFlowNameplateData mass_flow_nameplate_data;         ///< Nameplate flow rate data
    double               inlet_temperature         = 0.0;  ///< Inlet temperature @unitb{\degreeCelsius}
    double               outlet_temperature        = 0.0;  ///< Outlet temperature @unitb{\degreeCelsius}
};

/**
 * @ingroup steam_reduction_calculator
 * @struct OffsheetMethodData
 * @brief Input data for the offsheet (direct consumption) measurement method.
 * @details Used when the energy consumption is known directly from a report, bill, or other
 * source without requiring a flow-rate conversion.
 * @see steam_reduction_offsheet_formula
 */
struct OffsheetMethodData {
    double consumption = 0.0; ///< Total annual energy consumption (used directly as annual energy use) @unitb{kJ\per\year}
};

/**
 * @ingroup steam_reduction_calculator
 * @struct SteamReductionInput
 * @brief Input data for a single steam reduction measure.
 * @details Aggregates all parameters needed to evaluate one measure. The active measurement method
 * is selected via @ref SteamMeasurementMethod; only the corresponding method data struct is used
 * in the calculation. Steam properties are determined from the specified pressure and thermodynamic
 * variable.
 */
struct SteamReductionInput {
    int    hours_per_year      = 0;   ///< Annual operating hours @unitb{\hour\per\year}
    UtilityType utility_type   = UtilityType::kNaturalGas; ///< Utility type for energy cost calculation
    double utility_cost        = 0.0; ///< Utility cost rate (@unitb{\dollar\per\kg} for steam, @unitb{\dollar\per\kJ} for gas/other)
    SteamMeasurementMethod measurement_method = SteamMeasurementMethod::kFlowMeter; ///< Measurement method to apply
    double system_efficiency   = 1.0; ///< System efficiency @unitb{\unitless}
    double pressure            = 0.0; ///< Steam pressure @unitb{MPaa}
    FlowMeterMethodData  flow_meter_method_data;       ///< Data for the flow meter method
    MassFlowMethodData   air_mass_flow_method_data;    ///< Data for the air mass flow method
    MassFlowMethodData   water_mass_flow_method_data;  ///< Data for the water mass flow method
    OffsheetMethodData   offsheet_method_data;         ///< Data for the offsheet method
    int    units               = 1;   ///< Unit conversion factor @unitb{\unitless}
    double boiler_efficiency   = 1.0; ///< Boiler efficiency @unitb{\unitless}
    SteamProperties::ThermodynamicQuantity steam_variable_option =
        SteamProperties::ThermodynamicQuantity::TEMPERATURE; ///< Thermodynamic quantity type for steam property lookup
    double steam_variable      = 0.0; ///< Steam thermodynamic variable value (temperature @unitb{K}, enthalpy @unitb{kJ\per\kg}, entropy @unitb{kJ\per\kg\per\K}, or quality \unitless)
    double feed_water_temperature = 0.0; ///< Feedwater temperature @unitb{K}
};

/**
 * @ingroup steam_reduction_calculator
 * @struct SteamReductionOutput
 * @brief Output data for a steam reduction calculation.
 * @details Contains the accumulated annual steam use, energy use, and energy cost across all
 * measures passed to @ref steamReduction.
 */
struct SteamReductionOutput {
    double steam_use   = 0.0; ///< Annual steam use @unitb{kg\per\hour}
    double energy_use  = 0.0; ///< Annual energy use @unitb{kJ\per\year}
    double energy_cost = 0.0; ///< Annual energy cost @unitb{\dollar\per\year}
};

/**
 * @ingroup steam_reduction_calculator
 * @brief Calculates total annual steam use, energy use, and energy cost for a collection of steam
 * reduction measures.
 * @details Iterates over @p input_vec, dispatches each measure to the appropriate measurement
 * method helper, and accumulates the results.
 * @see steam_reduction_calculator
 * @see steam_reduction_energy_cost_formula
 *
 * @param[in] input_vec Vector of @ref SteamReductionInput structs, one per measure.
 * @return @ref SteamReductionOutput with summed annual steam use @unitb{kg\per\hour},
 *         energy use @unitb{kJ\per\year}, and energy cost @unitb{\dollar\per\year}.
 */
SteamReductionOutput steamReduction(const std::vector<SteamReductionInput>& input_vec);

/**
 * @ingroup steam_reduction_calculator
 * @brief Calculates steam use and energy use using the flow meter method.
 * @details Uses the directly measured steam or water flow rate along with operating hours, units,
 * system efficiency, and boiler efficiency to calculate annual steam use and energy use.
 * @see steam_reduction_flow_meter_formula
 *
 * @param[in] data              @ref FlowMeterMethodData with the flow rate.
 * @param[in] hours_per_year    Annual operating hours @unitb{\hour\per\year}.
 * @param[in] system_efficiency System efficiency @unitless.
 * @param[in] units             Unit conversion factor @unitless.
 * @param[in] boiler_efficiency Boiler efficiency @unitless.
 * @param[in] change_enthalpy   Enthalpy difference between steam and feedwater @unitb{kJ\per\kg}.
 * @return @ref SteamReductionOutput with steam use @unitb{kg\per\hour}
 *         and energy use @unitb{kJ\per\year}.
 */
SteamReductionOutput flowMeterReduction(const FlowMeterMethodData& data, int hours_per_year,
                                        double system_efficiency, int units, double boiler_efficiency,
                                        double change_enthalpy);

/**
 * @ingroup steam_reduction_calculator
 * @brief Calculates steam use and energy use using the air mass flow method.
 * @details Derives the heat flow rate from measured or nameplate air flow and the temperature
 * differential, then scales to annual energy use.
 * @see steam_reduction_air_mass_flow_formula
 *
 * @param[in] data              @ref MassFlowMethodData with air flow and temperature data.
 * @param[in] hours_per_year    Annual operating hours @unitb{\hour\per\year}.
 * @param[in] system_efficiency System efficiency @unitless.
 * @param[in] units             Unit conversion factor @unitless.
 * @param[in] boiler_efficiency Boiler efficiency @unitless.
 * @param[in] change_enthalpy   Enthalpy difference between steam and feedwater @unitb{kJ\per\kg}.
 * @return @ref SteamReductionOutput with steam use @unitb{kg\per\hour}
 *         and energy use @unitb{kJ\per\year}.
 */
SteamReductionOutput airMassFlowReduction(const MassFlowMethodData& data, int hours_per_year,
                                          double system_efficiency, int units, double boiler_efficiency,
                                          double change_enthalpy);

/**
 * @ingroup steam_reduction_calculator
 * @brief Calculates steam use and energy use using the water mass flow method.
 * @details Derives the heat flow rate from the nameplate water flow rate and the temperature
 * differential, then scales to annual energy use.
 * @see steam_reduction_water_mass_flow_formula
 *
 * @param[in] data              @ref MassFlowMethodData with water flow and temperature data (nameplate).
 * @param[in] hours_per_year    Annual operating hours @unitb{\hour\per\year}.
 * @param[in] system_efficiency System efficiency @unitless.
 * @param[in] units             Unit conversion factor @unitless.
 * @param[in] boiler_efficiency Boiler efficiency @unitless.
 * @param[in] change_enthalpy   Enthalpy difference between steam and feedwater @unitb{kJ\per\kg}.
 * @return @ref SteamReductionOutput with steam use @unitb{kg\per\hour}
 *         and energy use @unitb{kJ\per\year}.
 */
SteamReductionOutput waterMassFlowReduction(const MassFlowMethodData& data, int hours_per_year,
                                            double system_efficiency, int units, double boiler_efficiency,
                                            double change_enthalpy);

/**
 * @ingroup steam_reduction_calculator
 * @brief Calculates steam use and energy use using the offsheet (direct consumption) method.
 * @details Uses the supplied energy consumption value directly as annual energy use, then derives
 * steam use from the enthalpy difference and boiler efficiency.
 * @see steam_reduction_offsheet_formula
 *
 * @param[in] data              @ref OffsheetMethodData with the total annual energy consumption @unitb{kJ\per\year}.
 * @param[in] boiler_efficiency Boiler efficiency @unitless.
 * @param[in] change_enthalpy   Enthalpy difference between steam and feedwater @unitb{kJ\per\kg}.
 * @return @ref SteamReductionOutput with steam use @unitb{kg\per\hour}
 *         and energy use @unitb{kJ\per\year}.
 */
SteamReductionOutput offsheetReduction(const OffsheetMethodData& data, double boiler_efficiency,
                                       double change_enthalpy);

/**
 * @ingroup steam_reduction_calculator
 * @brief Calculates the enthalpy difference between steam at the given conditions and feedwater.
 * @details Computes steam enthalpy at the specified pressure and thermodynamic variable, and
 * feedwater enthalpy at atmospheric pressure and the given feedwater temperature. Returns the
 * difference.
 * @see steam_reduction_enthalpy_formula
 *
 * @param[in] pressure              Steam pressure @unitb{MPaa}.
 * @param[in] steam_variable_option Thermodynamic quantity type (temperature, enthalpy, entropy, or quality).
 * @param[in] steam_variable        Steam thermodynamic variable value.
 * @param[in] feed_water_temperature Feedwater temperature @unitb{K}.
 * @return Enthalpy difference @unitb{kJ\per\kg}.
 */
double calculateChangeEnthalpy(double pressure,
                                SteamProperties::ThermodynamicQuantity steam_variable_option,
                                double steam_variable, double feed_water_temperature);

} // namespace steam_reduction
