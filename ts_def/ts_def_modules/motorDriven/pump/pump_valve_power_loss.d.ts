/**
 * Output of pump valve power loss calculations.
 *
 * @property pressure_drop double, pressure drop in PSI.
 * @property head_loss double, head loss in feet.
 * @property power_loss_frictional double, frictional power loss in hp.
 * @property power_loss_electrical double, electrical power loss in kW.
 * @property annual_energy_loss double, annual energy loss in kWh.
 */
export interface PumpValvePowerLossOutput {
    pressure_drop: number;
    head_loss: number;
    power_loss_frictional: number;
    power_loss_electrical: number;
    annual_energy_loss: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates electrical power loss for a throttled pump valve compared to wide-open operation.
 */
export declare class PumpValvePowerLoss {
    /**
     * Constructor for PumpValvePowerLoss - parameter less default constructor
     */
    constructor();

    /**
     * @param operating_hours double, annual operating hours.
     * @param pump_efficiency double, pump hydraulic efficiency.
     * @param motor_efficiency double, motor efficiency.
     * @param specific_gravity double, specific gravity of the fluid.
     * @param flow_rate double, volumetric flow rate in gpm.
     * @param upstream_pressure double, upstream gauge pressure in PSI.
     * @param upstream_gauge_elevation double, upstream gauge elevation in feet.
     * @param downstream_pressure double, downstream gauge pressure in PSI.
     * @param downstream_gauge_elevation double, downstream gauge elevation in feet.
     * @returns PumpValvePowerLossOutput
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
    PumpValvePowerLossOutput: PumpValvePowerLossOutput;
};
