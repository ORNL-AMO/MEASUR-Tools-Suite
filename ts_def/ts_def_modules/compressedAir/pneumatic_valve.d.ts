/**
 * @brief Input parameters for the flow rate calculation (Cv = 1).
 *
 * @var inletPressure double, inlet (upstream) absolute pressure in psia.
 * @var outletPressure double, outlet (downstream) absolute pressure in psia.
 */
export interface PneumaticValveFlowRateInput {
    inletPressure: number;
    outletPressure: number;
}

/**
 * @brief Result of the flow rate calculation (Cv = 1).
 *
 * @var flowRate double, air flow rate through a valve with Cv = 1 in scfm.
 */
export interface PneumaticValveFlowRateResult {
    flowRate: number;
}

/**
 * @brief Input parameters for the valve flow coefficient (Cv) calculation.
 *
 * @var inletPressure double, inlet (upstream) absolute pressure in psia.
 * @var outletPressure double, outlet (downstream) absolute pressure in psia.
 * @var flowRate double, measured or required air flow rate in scfm.
 */
export interface PneumaticValveCvInput {
    inletPressure: number;
    outletPressure: number;
    flowRate: number;
}

/**
 * @brief Result of the valve flow coefficient (Cv) calculation.
 *
 * @var flowCoefficient double, dimensionless valve flow coefficient (Cv).
 */
export interface PneumaticValveCvResult {
    flowCoefficient: number;
}

/**
 * @brief Calculates the air flow rate through a pneumatic valve with unit flow coefficient (Cv = 1).
 * @param input PneumaticValveFlowRateInput
 * @return PneumaticValveFlowRateResult containing `flowRate` [scfm].
 */
export function calculatePneumaticValveFlowRate(
    input: PneumaticValveFlowRateInput
): PneumaticValveFlowRateResult;

/**
 * @brief Calculates the valve flow coefficient (Cv) for a pneumatic valve.
 * @param input PneumaticValveCvInput
 * @return PneumaticValveCvResult containing `flowCoefficient`.
 */
export function calculatePneumaticValveCv(
    input: PneumaticValveCvInput
): PneumaticValveCvResult;

/** Factory function to load the Pneumatic Valve. */
export default function PneumaticValveModule(): Promise<{
    calculatePneumaticValveFlowRate: typeof calculatePneumaticValveFlowRate;
    calculatePneumaticValveCv: typeof calculatePneumaticValveCv;
}>;

