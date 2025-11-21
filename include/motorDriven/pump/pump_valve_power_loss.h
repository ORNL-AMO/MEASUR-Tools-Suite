#pragma once

/**
 * @file pump_valve-power-loss.h
 *
 * @author Omer Aziz (omerb)
 *
 * @ingroup electrical power loss from a pump valve
 *
 * @brief Calculate the electrical power loss for a pump throttled valve compared to wide-open.
 */

/**
 * @class PumpValvePowerLoss
 *
 * @ingroup electrical power loss from a pump valve
 *
 * @brief Calculate the electrical power loss for a pump throttled valve compared to wide-open.
 */
class PumpValvePowerLoss {
public:
    struct Output {
       /**
        *
        * @param[in] pressure_drop          @unit{\PSI}.
        * @param[in] head_loss              @unit{\feet}.
        * @param[in] power_loss_frictional  @unit{\hp}.
        * @param[in] power_loss_electrical  @unit{\kW}.
        * @param[in] annual_energy_loss     @unit{\kWHour}.
        */
        Output(double pressure_drop, double head_loss, double power_loss_frictional, double power_loss_electrical, double annual_energy_loss) :
                pressure_drop(pressure_drop), head_loss(head_loss), power_loss_frictional(power_loss_frictional),
                power_loss_electrical(power_loss_electrical), annual_energy_loss(annual_energy_loss) {}

        /**
         * @brief Default constructor.
         */
        Output() = default;

        double pressure_drop = 0, head_loss = 0, power_loss_frictional = 0, power_loss_electrical = 0, annual_energy_loss = 0;
    };

    /**
     * @brief Default constructor.
     */
    PumpValvePowerLoss() = default;

    /**
     * @brief Calculate the electrical power loss for a pump throttled valve compared to wide-open.
     * @details Calculates pressure drop, head loss, frictional power loss, electrical power loss and annual energy loss.
     * @param[in] operating_hours Number of hours the valve participates in the pumping system in a year. 8760 if it runs year-round @unit{\hours}.
     * @param[in] pump_efficiency The hydraulic efficiency of the pump, or how effectively it pumps fluid. 0.85 (85%) is typical. Fractional value should range from 0.01 – 1 @unit{\percentage}.
     * @param[in] motor_efficiency The electrical efficiency of the motor driving the pump. If the motor hasn’t been through rewind, this is the efficiency listed on the nameplate.
     * 0.95 (95%) can be used as a default if unknown. Value should range from 1 – 100% @unit{\percentage}.
     * @param[in] specific_gravity Density of the working fluid relative to water, with water itself as 1.
     * A fluid which is twice as dense as water has a specific gravity of 2. Value cannot be equal to or less than 0 @unit{\unitless}.
     * @param[in] flow_rate Volume of fluid flow through the valve. Best taken from immediately upstream of the valve assuming there are no
     * branches downstream of measurement location. Value cannot be equal to or less than 0. @unit{\gallons\minute}.
     * @param[in] upstream_pressure Gauge pressure after the valve @unit{\PSI}.
     * @param[in] upstream_gauge_elevation Height difference of the pressure gauge from the valve.
     * Can be negative, zero, or positive as the position is relative to the valve @unit{\feet}.
     * @param[in] downstream_pressure Gauge pressure before the valve @unit{\PSI}.
     * @param[in] downstream_gauge_elevation Height difference of the pressure gauge from the valve.
     * Can be negative, zero, or positive as the position is relative to the valve @unit{\feet}.
     *
     * @b Factors
     * * - @symbol{\text{kHeightToPressureConversion}; feet of fluid height to PSI, constant value 2.307249} @unit{\unitless}
     * * - @symbol{\text{kFluidPowerConversion}; flow rate to power lost, constant value 1714.231} @unit{\unitless}
     * * - @symbol{\text{kElectricalPowerConversion}; horsepower to kW, constant value 0.7457} @unit{\unitless}
     *
     * @formula
     * Pressure Drop         = (upstream_pressure - downstream_pressure) + specific_gravity * (upstream_gauge_elevation - downstream_gauge_elevation) / KHeightToPressureConversion @unit{\PSI}
     * Head Loss             = pressureDrop * KHeightToPressureConversion @unit{\feet}
     * Power Loss Frictional = pressureDrop * flow_rate / kFluidPowerConversion @unit{\hp}
     * Power Loss Electrical = (kElectricalPowerConversion   * powerLossFrictional / pump_efficiency) / motor_efficiency @unit{\kW}
     * Annual Energy Loss    = operating_hours * powerLossElectrical @unit{\kWHour}
     *
     * @return PumpValvePowerLoss::Output.
     */
    PumpValvePowerLoss::Output calculate(const double operating_hours, const double pump_efficiency, const double motor_efficiency,
                     const double specific_gravity, const double flow_rate,
                     const double upstream_pressure, const double upstream_gauge_elevation,
                     const double downstream_pressure, const double downstream_gauge_elevation) const;
};

