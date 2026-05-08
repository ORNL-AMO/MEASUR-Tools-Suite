#pragma once

#include <vector>

/**
 * @ingroup natural_gas_reduction_calculator
 * @file natural_gas_reduction.h
 * @brief Declares structs, enums, and functions for the Natural Gas Reduction Calculator.
 * @copybrief natural_gas_reduction_calculator
 */

/**
 * @ingroup natural_gas_reduction_calculator
 * @namespace natural_gas_reduction
 * @brief Natural gas reduction calculations for treasure hunt measures.
 * @details Provides a function-based API for estimating annual natural gas energy use and cost savings
 * for natural gas reduction measures identified during an energy treasure hunt or efficiency
 * assessment. Supports four measurement methods: flow meter, air mass flow, water mass flow, and other.
 * @see natural_gas_reduction_calculator
 */
namespace natural_gas_reduction {

/**
 * @ingroup natural_gas_reduction_calculator
 * @struct FlowMeterMethodData
 * @brief Input data for the flow meter measurement method.
 * @details Used when natural gas flow is measured directly by a flow meter. The flow rate is
 * combined with operating hours and units to calculate annual energy use.
 * @see natural_gas_reduction_flow_meter_formula
 */
struct FlowMeterMethodData {
    double flow_rate = 0.0; ///< Gas flow rate measured by the flow meter @unitb{\cubic\foot\per\minute}
};

/**
 * @ingroup natural_gas_reduction_calculator
 * @struct NaturalGasOtherMethodData
 * @brief Input data for the other (direct consumption) measurement method.
 * @details Used when annual natural gas consumption is known directly from a report, bill, or
 * other source without requiring a flow-rate conversion.
 * @see natural_gas_reduction_other_formula
 */
struct NaturalGasOtherMethodData {
    double consumption = 0.0; ///< Annual natural gas consumption @unitb{MMBtu\per\year}
};

/**
 * @ingroup natural_gas_reduction_calculator
 * @struct AirMassFlowMeasuredData
 * @brief Measured air duct data used to derive the air flow rate.
 * @details Used when air mass flow is determined by direct measurements of duct area and
 * air velocity rather than nameplate specifications.
 * @see natural_gas_reduction_air_mass_flow_formula
 */
struct AirMassFlowMeasuredData {
    double area_of_duct = 0.0; ///< Cross-sectional area of the duct @unitb{\square\foot}
    double air_velocity = 0.0; ///< Air velocity measured in the duct @unitb{\foot\per\minute}
};

/**
 * @ingroup natural_gas_reduction_calculator
 * @struct AirMassFlowNameplateData
 * @brief Nameplate air flow data used as the air flow rate.
 * @details Used when the air flow rate is taken directly from the equipment nameplate
 * rather than being derived from duct measurements.
 * @see natural_gas_reduction_air_mass_flow_formula
 */
struct AirMassFlowNameplateData {
    double air_flow = 0.0; ///< Nameplate air flow rate @unitb{\cubic\foot\per\minute}
};

/**
 * @ingroup natural_gas_reduction_calculator
 * @struct AirMassFlowData
 * @brief Input data for the air mass flow measurement method.
 * @details Aggregates parameters for calculating heat transfer via air mass flow. The flow rate
 * is taken either from nameplate data or from direct duct measurements, selected by @ref is_nameplate.
 * @see natural_gas_reduction_air_mass_flow_formula
 */
struct AirMassFlowData {
    bool                     is_nameplate       = false; ///< True if using nameplate data; false for measured data
    AirMassFlowMeasuredData  measured_data;              ///< Measured air duct data (used when @ref is_nameplate is false)
    AirMassFlowNameplateData nameplate_data;             ///< Nameplate air flow data (used when @ref is_nameplate is true)
    double                   inlet_temperature  = 0.0;   ///< Inlet air temperature @unitb{\degree F}
    double                   outlet_temperature = 0.0;   ///< Outlet air temperature @unitb{\degree F}
    double                   system_efficiency  = 100.0; ///< System efficiency @unitb{\percent}
};

/**
 * @ingroup natural_gas_reduction_calculator
 * @struct WaterMassFlowData
 * @brief Input data for the water mass flow measurement method.
 * @details Used when natural gas energy use is estimated from the heat transferred to a water
 * stream, calculated from the water flow rate and temperature differential.
 * @see natural_gas_reduction_water_mass_flow_formula
 */
struct WaterMassFlowData {
    double water_flow         = 0.0;   ///< Water flow rate @unitb{\gallon\per\minute}
    double inlet_temperature  = 0.0;   ///< Inlet water temperature @unitb{\degree F}
    double outlet_temperature = 0.0;   ///< Outlet water temperature @unitb{\degree F}
    double system_efficiency  = 100.0; ///< System efficiency @unitb{\percent}
};

/**
 * @ingroup natural_gas_reduction_calculator
 * @enum NaturalGasMeasurementMethod
 * @brief Selects the measurement method used to determine natural gas energy use for a single measure.
 * @see natural_gas_reduction_calculator
 */
enum class NaturalGasMeasurementMethod {
    FlowMeter    = 0, ///< Flow meter method — uses a direct gas flow rate measurement
    AirMassFlow  = 1, ///< Air mass flow method — uses heat transferred to an air stream
    WaterMassFlow = 2, ///< Water mass flow method — uses heat transferred to a water stream
    Other        = 3  ///< Other method — uses a directly supplied annual consumption value
};

/**
 * @ingroup natural_gas_reduction_calculator
 * @struct NaturalGasReductionInput
 * @brief Input data for a single natural gas reduction measure.
 * @details Aggregates all parameters needed to evaluate one measure. The active measurement method
 * is selected via @ref NaturalGasMeasurementMethod; only the corresponding method data struct is
 * used in the calculation.
 */
struct NaturalGasReductionInput {
    int                         operating_hours      = 0;                                          ///< Annual operating hours @unitb{\hour\per\year}
    double                      fuel_cost            = 0.0;                                        ///< Natural gas fuel cost rate @unitb{\dollar\per MMBtu}
    NaturalGasMeasurementMethod measurement_method   = NaturalGasMeasurementMethod::FlowMeter;    ///< Measurement method to apply
    FlowMeterMethodData         flow_meter_method_data;                                            ///< Data for the flow meter method
    NaturalGasOtherMethodData   other_method_data;                                                 ///< Data for the other method
    AirMassFlowData             air_mass_flow_data;                                                ///< Data for the air mass flow method
    WaterMassFlowData           water_mass_flow_data;                                              ///< Data for the water mass flow method
    int                         units                = 1;                                          ///< Unit conversion multiplier applied to flow rates
};

/**
 * @ingroup natural_gas_reduction_calculator
 * @struct NaturalGasReductionOutput
 * @brief Output data for a natural gas reduction calculation.
 * @details Contains the accumulated annual energy use, energy cost, heat flow, and total flow
 * across all measures passed to @ref naturalGasReduction, or the individual result from a
 * single-method helper function.
 */
struct NaturalGasReductionOutput {
    double energy_use  = 0.0; ///< Annual natural gas energy use @unitb{MMBtu\per\year}
    double energy_cost = 0.0; ///< Annual natural gas energy cost @unitb{\dollar\per\year}
    double heat_flow   = 0.0; ///< Heat flow rate @unitb{MMBtu\per\hour}
    double total_flow  = 0.0; ///< Total gas or fluid flow @unitb{\cubic\foot\per\minute}
};

/**
 * @ingroup natural_gas_reduction_calculator
 * @brief Calculates total annual natural gas energy use and cost for a collection of reduction measures.
 * @details Iterates over @p input_vec, dispatches each measure to the appropriate single-method
 * helper (flow meter, air mass flow, water mass flow, or other), and accumulates the results.
 * @see natural_gas_reduction_calculator
 *
 * @param[in] input_vec  Vector of @ref NaturalGasReductionInput structs, one per measure.
 * @return @ref NaturalGasReductionOutput with the summed annual energy use @unitb{MMBtu\per\year},
 *         energy cost @unitb{\dollar\per\year}, heat flow @unitb{MMBtu\per\hour}, and
 *         total flow @unitb{\cubic\foot\per\minute} across all measures.
 */
NaturalGasReductionOutput naturalGasReduction(const std::vector<NaturalGasReductionInput>& input_vec);

/**
 * @ingroup natural_gas_reduction_calculator
 * @brief Calculates annual natural gas energy use and cost using the flow meter method.
 * @details Multiplies the flow rate by the unit conversion factor and annual operating hours,
 * then applies the Btu content of natural gas (1.03 MMBtu per thousand cubic feet) to obtain
 * annual energy use. Energy cost is derived from the fuel cost rate.
 * @see natural_gas_reduction_flow_meter_formula
 *
 * @param[in] data            @ref FlowMeterMethodData with the measured gas flow rate.
 * @param[in] operating_hours Annual operating hours @unitb{\hour\per\year}.
 * @param[in] fuel_cost       Natural gas fuel cost rate @unitb{\dollar\per MMBtu}.
 * @param[in] units           Unit conversion multiplier applied to the flow rate.
 * @return @ref NaturalGasReductionOutput with annual energy use @unitb{MMBtu\per\year}
 *         and annual energy cost @unitb{\dollar\per\year}.
 */
NaturalGasReductionOutput flowMeterMethodReduction(const FlowMeterMethodData& data, int operating_hours,
                                                   double fuel_cost, int units);

/**
 * @ingroup natural_gas_reduction_calculator
 * @brief Calculates annual natural gas energy use and cost using the air mass flow method.
 * @details Determines the air flow rate from either nameplate or measured duct data, then
 * calculates the heat transferred to the air stream from the temperature differential. The
 * annual energy use accounts for operating hours and system efficiency.
 * @see natural_gas_reduction_air_mass_flow_formula
 *
 * @param[in] data            @ref AirMassFlowData with air flow and temperature parameters.
 * @param[in] operating_hours Annual operating hours @unitb{\hour\per\year}.
 * @param[in] fuel_cost       Natural gas fuel cost rate @unitb{\dollar\per MMBtu}.
 * @param[in] units           Unit conversion multiplier applied to the flow rate.
 * @return @ref NaturalGasReductionOutput with annual energy use @unitb{MMBtu\per\year},
 *         annual energy cost @unitb{\dollar\per\year}, heat flow @unitb{MMBtu\per\hour},
 *         and total flow @unitb{\cubic\foot\per\minute}.
 */
NaturalGasReductionOutput airMassFlowMethodReduction(const AirMassFlowData& data, int operating_hours,
                                                     double fuel_cost, int units);

/**
 * @ingroup natural_gas_reduction_calculator
 * @brief Calculates annual natural gas energy use and cost using the water mass flow method.
 * @details Calculates the heat transferred to a water stream from the water flow rate and
 * temperature differential. The annual energy use accounts for operating hours and system efficiency.
 * @see natural_gas_reduction_water_mass_flow_formula
 *
 * @param[in] data            @ref WaterMassFlowData with water flow and temperature parameters.
 * @param[in] operating_hours Annual operating hours @unitb{\hour\per\year}.
 * @param[in] fuel_cost       Natural gas fuel cost rate @unitb{\dollar\per MMBtu}.
 * @param[in] units           Unit conversion multiplier applied to the flow rate.
 * @return @ref NaturalGasReductionOutput with annual energy use @unitb{MMBtu\per\year},
 *         annual energy cost @unitb{\dollar\per\year}, heat flow @unitb{MMBtu\per\hour},
 *         and total flow @unitb{\gallon\per\minute}.
 */
NaturalGasReductionOutput waterMassFlowMethodReduction(const WaterMassFlowData& data, int operating_hours,
                                                       double fuel_cost, int units);

/**
 * @ingroup natural_gas_reduction_calculator
 * @brief Calculates annual natural gas energy use and cost using a directly supplied consumption value.
 * @details Uses the consumption field directly as the annual energy use without any flow-rate
 * conversion. Energy cost is derived using the fuel cost rate.
 * @see natural_gas_reduction_other_formula
 *
 * @param[in] data       @ref NaturalGasOtherMethodData with the annual gas consumption @unitb{MMBtu\per\year}.
 * @param[in] fuel_cost  Natural gas fuel cost rate @unitb{\dollar\per MMBtu}.
 * @return @ref NaturalGasReductionOutput with annual energy use @unitb{MMBtu\per\year}
 *         and annual energy cost @unitb{\dollar\per\year}.
 */
NaturalGasReductionOutput otherMethodReduction(const NaturalGasOtherMethodData& data, double fuel_cost);

} // namespace natural_gas_reduction
