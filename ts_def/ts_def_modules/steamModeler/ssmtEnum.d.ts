/**
 * Steam System Modeler (SSMT) shared enumerations.
 *
 * Defines all enumerations shared across the Steam System Modeler tool:
 * thermodynamic quantity types, turbine solve modes, turbine property types,
 * and condensing/pressure turbine operation modes.
 */

/**
 * Thermodynamic quantity type used to specify steam inlet/outlet conditions.
 *
 * Selects which thermodynamic property is supplied as the known quantity:
 * - `TEMPERATURE` - temperature in K
 * - `ENTHALPY`    - specific enthalpy in kJ/kg
 * - `ENTROPY`     - specific entropy in kJ/(kg.K)
 * - `QUALITY`     - vapour quality, unitless (0-1)
 */
export enum ThermodynamicQuantity {
    TEMPERATURE = 0,
    ENTHALPY    = 1,
    ENTROPY     = 2,
    QUALITY     = 3,
}

/**
 * Turbine solve mode.
 *
 * - `OutletProperties`     - solve for outlet steam properties given isentropic efficiency
 * - `IsentropicEfficiency` - solve for isentropic efficiency given outlet steam properties
 */
export enum Solve {
    OutletProperties     = 0,
    IsentropicEfficiency = 1,
}

/**
 * Known turbine property type used as the driving input.
 *
 * - `MassFlow` - mass flow rate in kg/hr
 * - `PowerOut` - power output in kW
 */
export enum TurbineProperty {
    MassFlow = 0,
    PowerOut = 1,
}

/**
 * Condensing turbine operation mode.
 *
 * - `STEAM_FLOW`       - turbine is driven by a specified steam flow rate
 * - `POWER_GENERATION` - turbine is driven by a specified power generation target
 */
export enum CondensingTurbineOperation {
    STEAM_FLOW       = 0,
    POWER_GENERATION = 1,
}

/**
 * Pressure turbine operation mode.
 *
 * - `STEAM_FLOW`       - turbine is driven by a specified steam flow rate
 * - `POWER_GENERATION` - turbine is driven by a specified power generation target
 * - `BALANCE_HEADER`   - turbine output balances the connected steam header
 * - `POWER_RANGE`      - turbine operates within a specified power range
 * - `FLOW_RANGE`       - turbine operates within a specified steam flow range
 */
export enum PressureTurbineOperation {
    STEAM_FLOW       = 0,
    POWER_GENERATION = 1,
    BALANCE_HEADER   = 2,
    POWER_RANGE      = 3,
    FLOW_RANGE       = 4,
}

export type SsmtEnumModule = {
    ThermodynamicQuantity: typeof ThermodynamicQuantity;
    Solve: typeof Solve;
    TurbineProperty: typeof TurbineProperty;
    CondensingTurbineOperation: typeof CondensingTurbineOperation;
    PressureTurbineOperation: typeof PressureTurbineOperation;
};
