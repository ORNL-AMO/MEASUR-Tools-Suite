/**
 * Pump Valve Power Loss
 *
 * Calculates hydraulic and electrical losses caused by throttled valve
 * operation compared to wide-open flow.
 */

/**
 * Result object returned by {@link PumpValvePowerLoss.calculate}.
 *
 * @property pressure_drop double, pressure drop in psi
 * @property head_loss double, head loss in ft
 * @property power_loss_frictional double, frictional power loss in hp
 * @property power_loss_electrical double, electrical power loss in kW
 * @property annual_energy_loss double, annual energy loss in kWh
 */
export declare class PumpValvePowerLossOutput {
    private constructor();

    /** Pressure drop, units psi */
    pressure_drop: number;
    /** Head loss, units ft */
    head_loss: number;
    /** Frictional power loss, units hp */
    power_loss_frictional: number;
    /** Electrical power loss, units kW */
    power_loss_electrical: number;
    /** Annual energy loss, units kWh */
    annual_energy_loss: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates electrical power loss for a throttled pump valve compared to wide-open operation.
 */
export declare class PumpValvePowerLoss {
    /**
     * Default constructor - no arguments required.
     */
    constructor();

    /**
     * @param operating_hours double, annual operating hours, units hr/year.
     * @param pump_efficiency Pump hydraulic efficiency, dimensionless fraction.
     * @param motor_efficiency Motor efficiency, dimensionless fraction.
     * @param specific_gravity double, specific gravity, dimensionless of the fluid.
     * @param flow_rate double, volumetric flow rate in gpm.
     * @param upstream_pressure double, upstream gauge pressure in PSI.
     * @param upstream_gauge_elevation double, upstream gauge elevation in feet.
     * @param downstream_pressure double, downstream gauge pressure in PSI.
     * @param downstream_gauge_elevation double, downstream gauge elevation in feet.
     * @returns {@link PumpValvePowerLossOutput}
     */
    calculate(
        operating_hours: number,
        pump_efficiency: number,
        motor_efficiency: number,
        specific_gravity: number,
        flow_rate: number,
        upstream_pressure: number,
        upstream_gauge_elevation: number,
        downstream_pressure: number,
        downstream_gauge_elevation: number
    ): PumpValvePowerLossOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type PumpValvePowerLossModule = {
    PumpValvePowerLoss: typeof PumpValvePowerLoss;
    PumpValvePowerLossOutput: typeof PumpValvePowerLossOutput;
};
