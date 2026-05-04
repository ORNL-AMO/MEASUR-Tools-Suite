#pragma once

#include <vector>

/**
 * @ingroup electricity_reduction_calculator
 * @file electricity_reduction.h
 * @brief Declares structs, enums, and functions for the Electricity Reduction Calculator.
 * @copybrief electricity_reduction_calculator
 */

/**
 * @ingroup electricity_reduction_calculator
 * @namespace electricity_reduction
 * @brief Electricity reduction calculations for treasure hunt measures.
 * @details Provides a function-based API for estimating annual electricity use and cost savings
 * for electricity reduction measures identified during an energy treasure hunt or efficiency
 * assessment. Supports four measurement methods: multimeter, nameplate, power meter, and other.
 * @see electricity_reduction_calculator
 */
namespace electricity_reduction {

/**
 * @ingroup electricity_reduction_calculator
 * @struct MultimeterData
 * @brief Input data for the multimeter measurement method.
 * @details Used when electrical power is measured with a clamp-on ammeter or multimeter.
 * The supply voltage, average current, and power factor are combined with the number of phases
 * to calculate total power draw.
 * @see electricity_reduction_multimeter_formula
 */
struct MultimeterData {
    int    number_of_phases  = 1;   ///< Number of electrical phases (1 or 3)
    double supply_voltage    = 0.0; ///< Supply voltage @unitb{\volt}
    double average_current   = 0.0; ///< Average current measured by the meter @unitb{\ampere}
    double power_factor      = 0.0; ///< Power factor of the load (dimensionless, 0–1)
};

/**
 * @ingroup electricity_reduction_calculator
 * @struct NameplateData
 * @brief Input data for the nameplate measurement method.
 * @details Used when power draw is estimated from motor nameplate information rather than
 * direct measurement. The rated motor power is adjusted for load factor, speed ratio, and
 * combined motor-and-drive efficiency to obtain an operating power estimate.
 * @see electricity_reduction_nameplate_formula
 */
struct NameplateData {
    double rated_motor_power          = 0.0;   ///< Rated motor power from the nameplate @unitb{\kilo\watt}
    bool   variable_speed_motor       = false;  ///< Whether the motor is driven by a variable-speed drive
    double operational_frequency      = 0.0;   ///< Actual operating frequency @unitb{\hertz}
    double line_frequency             = 0.0;   ///< Nominal line frequency @unitb{\hertz}
    double motor_and_drive_efficiency = 0.0;   ///< Combined motor and drive efficiency (percent, 0–100)
    double load_factor                = 0.0;   ///< Motor load factor (dimensionless, 0–1)
};

/**
 * @ingroup electricity_reduction_calculator
 * @struct PowerMeterData
 * @brief Input data for the power meter measurement method.
 * @details Used when a power meter provides a direct reading of the electrical power drawn
 * by the load. The power reading is combined with operating hours to calculate annual
 * energy use.
 * @see electricity_reduction_power_meter_formula
 */
struct PowerMeterData {
    double power = 0.0; ///< Direct power reading from the power meter @unitb{\kilo\watt}
};

/**
 * @ingroup electricity_reduction_calculator
 * @struct ElectricityOtherMethodData
 * @brief Input data for the other (direct energy) measurement method.
 * @details Used when annual energy consumption is known directly from a utility bill, report,
 * or other source without requiring a power-to-energy conversion.
 * @see electricity_reduction_other_formula
 */
struct ElectricityOtherMethodData {
    double energy = 0.0; ///< Annual energy consumption @unitb{\kilo\watt\hour\per\year}
};

/**
 * @ingroup electricity_reduction_calculator
 * @enum ElectricityReductionMeasurementMethod
 * @brief Selects the measurement method used to determine electricity use for a single measure.
 * @see electricity_reduction_calculator
 */
enum class ElectricityReductionMeasurementMethod {
    Multimeter = 0, ///< Multimeter method — uses voltage, current, and power factor
    Nameplate  = 1, ///< Nameplate method — uses rated motor power, load factor, and efficiency
    PowerMeter = 2, ///< Power meter method — uses a direct power reading
    Other      = 3  ///< Other method — uses a directly supplied annual energy value
};

/**
 * @ingroup electricity_reduction_calculator
 * @struct ElectricityReductionInput
 * @brief Input data for a single electricity reduction measure.
 * @details Aggregates all parameters needed to evaluate one measure. The active measurement method
 * is selected via @ref ElectricityReductionMeasurementMethod; only the corresponding method data
 * struct is used in the calculation. The @p units field is a quantity multiplier (e.g., number of
 * identical loads).
 */
struct ElectricityReductionInput {
    int    operating_hours   = 0;                                                                      ///< Annual operating hours @unitb{\hour\per\year}
    double electricity_cost  = 0.0;                                                                    ///< Electricity cost rate @unitb{\dollar\per\kilo\watt\hour}
    ElectricityReductionMeasurementMethod measurement_method = ElectricityReductionMeasurementMethod::Multimeter; ///< Measurement method to apply
    MultimeterData             multimeter_data;                                                        ///< Data for the multimeter method
    NameplateData              nameplate_data;                                                         ///< Data for the nameplate method
    PowerMeterData             power_meter_data;                                                       ///< Data for the power meter method
    ElectricityOtherMethodData other_method_data;                                                      ///< Data for the other method
    int    units             = 1;                                                                      ///< Quantity multiplier (number of identical loads)
};

/**
 * @ingroup electricity_reduction_calculator
 * @struct ElectricityReductionOutput
 * @brief Output data for an electricity reduction calculation.
 * @details Contains the accumulated annual energy use, annual energy cost, and total power across
 * all measures passed to @ref electricityReduction, or the individual result from a single-method
 * helper function.
 */
struct ElectricityReductionOutput {
    double energy_use  = 0.0; ///< Annual energy use @unitb{\kilo\watt\hour\per\year}
    double energy_cost = 0.0; ///< Annual energy cost @unitb{\dollar\per\year}
    double power       = 0.0; ///< Total power draw @unitb{\kilo\watt}
};

/**
 * @ingroup electricity_reduction_calculator
 * @brief Calculates total annual electricity use, cost, and power for a collection of measures.
 * @details Iterates over @p input_vec, dispatches each measure to the appropriate single-method
 * helper (multimeter, nameplate, power meter, or other), and accumulates the results.
 * @see electricity_reduction_calculator
 * @see electricity_reduction_energy_cost_formula
 *
 * @param[in] input_vec  Vector of @ref ElectricityReductionInput structs, one per measure.
 * @return @ref ElectricityReductionOutput with the summed annual energy use
 *         @unitb{\kilo\watt\hour\per\year}, annual energy cost @unitb{\dollar\per\year},
 *         and total power @unitb{\kilo\watt} across all measures.
 */
ElectricityReductionOutput electricityReduction(const std::vector<ElectricityReductionInput>& input_vec);

/**
 * @ingroup electricity_reduction_calculator
 * @brief Calculates annual energy use and cost using the multimeter measurement method.
 * @details Computes total power from the supply voltage, average current, power factor, and number
 * of phases, then scales to annual energy use using the operating hours. Energy cost is then derived
 * using @ref electricity_reduction_energy_cost_formula.
 * @see electricity_reduction_multimeter_formula
 *
 * @param[in] data            @ref MultimeterData with voltage @unitb{\volt}, current @unitb{\ampere},
 *                            power factor, and number of phases.
 * @param[in] operating_hours Annual operating hours @unitb{\hour\per\year}.
 * @param[in] electricity_cost Electricity cost rate @unitb{\dollar\per\kilo\watt\hour}.
 * @param[in] units           Quantity multiplier (number of identical loads).
 * @return @ref ElectricityReductionOutput with annual energy use @unitb{\kilo\watt\hour\per\year},
 *         annual energy cost @unitb{\dollar\per\year}, and power @unitb{\kilo\watt}.
 */
ElectricityReductionOutput multimeterReduction(const MultimeterData& data, int operating_hours,
                                               double electricity_cost, int units);

/**
 * @ingroup electricity_reduction_calculator
 * @brief Calculates annual energy use and cost using the nameplate measurement method.
 * @details Estimates power from the rated motor power, load factor, frequency ratio, and
 * motor-and-drive efficiency. Energy use is then scaled to annual use by multiplying by the
 * operating hours and the units multiplier. Energy cost is then derived using
 * @ref electricity_reduction_energy_cost_formula.
 * @see electricity_reduction_nameplate_formula
 *
 * @param[in] data            @ref NameplateData with rated motor power @unitb{\kilo\watt}, load
 *                            factor, operational and line frequencies @unitb{\hertz}, and
 *                            motor-and-drive efficiency (percent).
 * @param[in] operating_hours Annual operating hours @unitb{\hour\per\year}.
 * @param[in] electricity_cost Electricity cost rate @unitb{\dollar\per\kilo\watt\hour}.
 * @param[in] units           Quantity multiplier (number of identical loads).
 * @return @ref ElectricityReductionOutput with annual energy use @unitb{\kilo\watt\hour\per\year},
 *         annual energy cost @unitb{\dollar\per\year}, and power @unitb{\kilo\watt}.
 */
ElectricityReductionOutput nameplateReduction(const NameplateData& data, int operating_hours,
                                              double electricity_cost, int units);

/**
 * @ingroup electricity_reduction_calculator
 * @brief Calculates annual energy use and cost using the power meter measurement method.
 * @details Multiplies the direct power reading by the units multiplier and then by the annual
 * operating hours to obtain annual energy use. Energy cost is then derived using
 * @ref electricity_reduction_energy_cost_formula.
 * @see electricity_reduction_power_meter_formula
 *
 * @param[in] data            @ref PowerMeterData with the direct power reading @unitb{\kilo\watt}.
 * @param[in] operating_hours Annual operating hours @unitb{\hour\per\year}.
 * @param[in] electricity_cost Electricity cost rate @unitb{\dollar\per\kilo\watt\hour}.
 * @param[in] units           Quantity multiplier (number of identical loads).
 * @return @ref ElectricityReductionOutput with annual energy use @unitb{\kilo\watt\hour\per\year},
 *         annual energy cost @unitb{\dollar\per\year}, and power @unitb{\kilo\watt}.
 */
ElectricityReductionOutput powerMeterReduction(const PowerMeterData& data, int operating_hours,
                                               double electricity_cost, int units);

/**
 * @ingroup electricity_reduction_calculator
 * @brief Calculates annual energy cost using a directly supplied energy consumption value.
 * @details Uses the energy field directly as the annual energy use without any power-to-energy
 * conversion. Energy cost is then derived using @ref electricity_reduction_energy_cost_formula.
 * @see electricity_reduction_other_formula
 *
 * @param[in] data             @ref ElectricityOtherMethodData with the annual energy consumption
 *                             @unitb{\kilo\watt\hour\per\year}.
 * @param[in] electricity_cost Electricity cost rate @unitb{\dollar\per\kilo\watt\hour}.
 * @return @ref ElectricityReductionOutput with annual energy use @unitb{\kilo\watt\hour\per\year},
 *         annual energy cost @unitb{\dollar\per\year}, and power @unitb{\kilo\watt}.
 */
ElectricityReductionOutput otherReduction(const ElectricityOtherMethodData& data, double electricity_cost);

} // namespace electricity_reduction
