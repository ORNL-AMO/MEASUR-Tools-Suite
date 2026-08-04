/**
 * Steam System Modeler Tool (SSMT) - core calculators.
 *
 * Provides IAPWS-97 steam/water property calculators and components for
 * modeling steam systems: boiler, deaerator, flash tank, PRV, header,
 * turbine, and heat exchanger.
 *
 * Enumerations (`ThermodynamicQuantity`, `Solve`, `TurbineProperty`) are
 * imported from the `ssmtEnum` module.
 */

import type {
    ThermodynamicQuantity,
    Solve,
    TurbineProperty,
} from './ssmtEnum';
import type { InletVector } from '../binding/registered_vectors';

export type { ThermodynamicQuantity, Solve, TurbineProperty };

// ---------------------------------------------------------------------------
// Output property interfaces
// ---------------------------------------------------------------------------

/**
 * Saturated steam/water properties at a given pressure and temperature.
 *
 * All specific quantities are per unit mass (kJ/kg or m3/kg) for gas (steam)
 * and liquid (water) phases, plus evaporation (latent) values.
 */
export declare class SaturatedPropertiesOutput {
    private constructor();

    /** Saturated pressure, units MPa */
    saturatedPressure: number;
    /** Saturated temperature, units K */
    saturatedTemperature: number;
    /** Liquid specific enthalpy, units kJ/kg */
    liquidEnthalpy: number;
    /** Gas (steam) specific enthalpy, units kJ/kg */
    gasEnthalpy: number;
    /** Evaporation (latent) specific enthalpy, units kJ/kg */
    evaporationEnthalpy: number;
    /** Liquid specific entropy, units kJ/(kg.K) */
    liquidEntropy: number;
    /** Gas (steam) specific entropy, units kJ/(kg.K) */
    gasEntropy: number;
    /** Evaporation (latent) specific entropy, units kJ/(kg.K) */
    evaporationEntropy: number;
    /** Liquid specific volume, units m3/kg */
    liquidVolume: number;
    /** Gas (steam) specific volume, units m3/kg */
    gasVolume: number;
    /** Evaporation (latent) specific volume, units m3/kg */
    evaporationVolume: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Thermodynamic properties of steam/water at a given state.
 *
 */
export declare class SteamPropertiesOutput {
    /**
     * @param temperature Temperature, units K.
     * @param pressure Pressure, units MPa.
     * @param quality Quality, dimensionless fraction.
     * @param specificVolume Specific volume, units m3/kg.
     * @param density Density, units kg/m3.
     * @param specificEnthalpy Specific enthalpy, units kJ/kg.
     * @param specificEntropy Specific entropy, units kJ/(kg.K).
     * @param internalEnergy Internal energy, units MJ.
     */
    constructor(
        temperature: number,
        pressure: number,
        quality: number,
        specificVolume: number,
        density: number,
        specificEnthalpy: number,
        specificEntropy: number,
        internalEnergy: number
    );

    /** Temperature, units K */
    temperature: number;
    /** Pressure, units MPa */
    pressure: number;
    /** Quality, dimensionless fraction. */
    quality: number;
    /** Specific volume, units m3/kg */
    specificVolume: number;
    /** Density, units kg/m3 */
    density: number;
    /** Specific enthalpy, units kJ/kg */
    specificEnthalpy: number;
    /** Specific entropy, units kJ/(kg.K) */
    specificEntropy: number;
    /** Internal energy, units MJ */
    internalEnergy: number;
    /** Isobaric specific heat capacity Cp, units kJ/(kg.K) */
    specificIsobaricHeatCapacity_cp: number;
    /** Isochoric specific heat capacity Cv, units kJ/(kg.K) */
    specificIsochoricHeatCapacity_cv: number;
    /** Speed of sound, units m/s */
    speedOfSound_w: number;
    /** Isentropic exponent, dimensionless. */
    isentropicExponent: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Steam/fluid properties extended with mass flow and energy flow.
 *
 * Extends {@link SteamPropertiesOutput} with `massFlow` (kg/hr) and
 * `energyFlow` (units kJ/hr or MJ/hr depending on context).
 */
export declare class FluidProperties extends SteamPropertiesOutput {
    /**
     * @param massFlow Mass flow, units kg/hr.
     * @param energyFlow Energy flow, units kJ/hr or MJ/hr depending on context.
     * @param temperature Temperature, units K.
     * @param pressure Pressure, units MPa.
     * @param quality Quality, dimensionless fraction.
     * @param specificVolume Specific volume, units m3/kg.
     * @param density Density, units kg/m3.
     * @param specificEnthalpy Specific enthalpy, units kJ/kg.
     * @param specificEntropy Specific entropy, units kJ/(kg.K).
     * @param internalEnergy Internal energy, units MJ.
     */
    constructor(
        massFlow: number,
        energyFlow: number,
        temperature: number,
        pressure: number,
        quality: number,
        specificVolume: number,
        density: number,
        specificEnthalpy: number,
        specificEntropy: number,
        internalEnergy: number
    );

    /** Mass flow, units kg/hr */
    massFlow: number;
    /** Energy flow, units kJ/hr or MJ/hr depending on context. */
    energyFlow: number;
}

// ---------------------------------------------------------------------------
// Saturated property calculators
// ---------------------------------------------------------------------------

/**
 * Calculates saturated pressure from a given temperature.
 */
export declare class SaturatedPressure {
    /**
     * @param saturatedTemperature Saturated temperature, units K
     */
    constructor(saturatedTemperature: number);

    /**
     * Calculates saturated pressure.
     * @returns Saturated pressure, units MPa
     */
    calculate(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates saturated temperature from a given pressure.
 */
export declare class SaturatedTemperature {
    /**
     * @param saturatedPressure Saturated pressure, units MPa
     */
    constructor(saturatedPressure: number);

    /**
     * Calculates saturated temperature.
     * @returns Saturated temperature, units K
     */
    calculate(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates all saturated properties at a given pressure and temperature.
 */
export declare class SaturatedProperties {
    /**
     * @param saturatedPressure Saturated pressure, units MPa
     * @param saturatedTemperature Saturated temperature, units K
     */
    constructor(saturatedPressure: number, saturatedTemperature: number);

    /**
     * Calculates all saturated properties.
     * @returns {@link SaturatedPropertiesOutput}
     */
    calculate(): SaturatedPropertiesOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Steam properties calculator
// ---------------------------------------------------------------------------

/**
 * Calculates steam/water properties at a given pressure and thermodynamic quantity.
 */
export declare class SteamProperties {
    /**
     * @param pressure Pressure, units MPa
     * @param quantityType {@link ThermodynamicQuantity} - TEMPERATURE (K), ENTHALPY (kJ/kg), ENTROPY (kJ/(kg.K)), or QUALITY (unitless)
     * @param quantityValue Value of the specified thermodynamic quantity; units depend on quantityType (K, kJ/kg, kJ/(kg.K), or quality fraction).
     */
    constructor(
        pressure: number,
        quantityType: ThermodynamicQuantity,
        quantityValue: number
    );

    /**
     * Calculates steam properties for the given inlet conditions.
     * @returns {@link SteamPropertiesOutput}
     */
    calculate(): SteamPropertiesOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Boiler
// ---------------------------------------------------------------------------

/**
 * Determines fuel energy required to produce steam at specified conditions.
 *
 * Uses general boiler operational characteristics to compute steam, blowdown,
 * and feedwater properties.
 *
 */
export declare class Boiler {
    /**
     * @param deaeratorPressure Deaerator pressure, units MPa
     * @param combustionEfficiency Combustion efficiency, units %
     * @param blowdownRate Blowdown rate as percent of inlet mass flow, units %.
     * @param steamPressure Steam pressure, units MPa
     * @param quantityType {@link ThermodynamicQuantity} - TEMPERATURE (K), ENTHALPY (kJ/kg), ENTROPY (kJ/(kg.K)), or QUALITY
     * @param quantityValue Value of the specified thermodynamic quantity; units depend on quantityType (K, kJ/kg, kJ/(kg.K), or quality fraction).
     * @param steamMassFlow Steam mass flow, units kg/hr
     */
    constructor(
        deaeratorPressure: number,
        combustionEfficiency: number,
        blowdownRate: number,
        steamPressure: number,
        quantityType: ThermodynamicQuantity,
        quantityValue: number,
        steamMassFlow: number
    );

    /** @returns {@link FluidProperties} steam properties */
    getSteamProperties(): FluidProperties;
    /** @returns {@link FluidProperties} blowdown properties */
    getBlowdownProperties(): FluidProperties;
    /** @returns {@link FluidProperties} feedwater properties */
    getFeedwaterProperties(): FluidProperties;
    /** @returns Boiler energy, units MJ */
    getBoilerEnergy(): number;
    /** @returns Fuel energy, units MJ */
    getFuelEnergy(): number;
    /** @returns Blowdown rate as percent of inlet mass flow, units %. */
    getBlowdownRate(): number;
    /** @returns Combustion efficiency, units % */
    getCombustionEfficiency(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// HeatLoss
// ---------------------------------------------------------------------------

/**
 * Calculates heat energy loss and outlet steam properties given a % heat loss.
 */
export declare class HeatLoss {
    /**
     * @param inletPressure Inlet pressure, units MPa
     * @param quantityType {@link ThermodynamicQuantity}
     * @param quantityValue Value of the thermodynamic quantity; units depend on quantityType (K, kJ/kg, kJ/(kg.K), or quality fraction).
     * @param inletMassFlow Inlet mass flow, units kg/hr
     * @param percentHeatLoss Heat loss, units %
     */
    constructor(
        inletPressure: number,
        quantityType: ThermodynamicQuantity,
        quantityValue: number,
        inletMassFlow: number,
        percentHeatLoss: number
    );

    /** @returns {@link FluidProperties} inlet properties */
    getInletProperties(): FluidProperties;
    /** @returns {@link FluidProperties} outlet steam properties */
    getOutletProperties(): FluidProperties;
    /** @returns Heat loss, units MJ/hr */
    getHeatLoss(): number;
    /** @returns Inlet pressure, units MPa */
    getInletPressure(): number;
    /** @returns Thermodynamic quantity value; units depend on quantityType (K, kJ/kg, kJ/(kg.K), or quality fraction). */
    getQuantityValue(): number;
    /** @returns Inlet mass flow, units kg/hr */
    getInletMassFlow(): number;
    /** @returns Percent heat loss, units % */
    getPercentHeatLoss(): number;
    /** @returns {@link ThermodynamicQuantity} quantity type */
    getQuantityType(): ThermodynamicQuantity;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// FlashTank
// ---------------------------------------------------------------------------

/**
 * Calculates mass flows and properties of outlet gas and liquid from a flash tank.
 */
export declare class FlashTank {
    /**
     * @param inletWaterPressure Inlet water pressure, units MPa
     * @param quantityType {@link ThermodynamicQuantity}
     * @param quantityValue Value of the thermodynamic quantity; units depend on quantityType (K, kJ/kg, kJ/(kg.K), or quality fraction).
     * @param inletWaterMassFlow Inlet water mass flow, units kg/hr
     * @param tankPressure Tank pressure, units MPa
     */
    constructor(
        inletWaterPressure: number,
        quantityType: ThermodynamicQuantity,
        quantityValue: number,
        inletWaterMassFlow: number,
        tankPressure: number
    );

    /** @returns {@link FluidProperties} inlet water properties */
    getInletWaterProperties(): FluidProperties;
    /** @returns {@link FluidProperties} outlet gas saturated properties */
    getOutletGasSaturatedProperties(): FluidProperties;
    /** @returns {@link FluidProperties} outlet liquid saturated properties */
    getOutletLiquidSaturatedProperties(): FluidProperties;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// PRV (Pressure Reducing Valve)
// ---------------------------------------------------------------------------

/**
 * Calculates steam properties after a pressure drop (without desuperheating).
 */
export declare class PrvWithoutDesuperheating {
    /**
     * @param inletPressure Inlet pressure, units MPa
     * @param quantityType {@link ThermodynamicQuantity}
     * @param quantityValue Value of the thermodynamic quantity; units depend on quantityType (K, kJ/kg, kJ/(kg.K), or quality fraction).
     * @param inletMassFlow Inlet mass flow, units kg/hr
     * @param outletPressure Outlet pressure, units MPa
     */
    constructor(
        inletPressure: number,
        quantityType: ThermodynamicQuantity,
        quantityValue: number,
        inletMassFlow: number,
        outletPressure: number
    );

    /** @returns {@link SteamPropertiesOutput} inlet steam properties */
    getInletProperties(): SteamPropertiesOutput;
    /** @returns {@link SteamPropertiesOutput} outlet steam properties */
    getOutletProperties(): SteamPropertiesOutput;
    /** @returns Inlet mass flow, units kg/hr */
    getInletMassFlow(): number;
    /** @returns Inlet energy flow, units MJ/hr */
    getInletEnergyFlow(): number;
    /** @returns Outlet mass flow, units kg/hr */
    getOutletMassFlow(): number;
    /** @returns Outlet energy flow, units MJ/hr */
    getOutletEnergyFlow(): number;
    /** @returns Whether desuperheating is active */
    isWithDesuperheating(): boolean;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates steam properties after a pressure drop with desuperheating.
 *
 * Extends {@link PrvWithoutDesuperheating} with feedwater injection.
 *
 */
export declare class PrvWithDesuperheating {
    /**
     * @param inletPressure Inlet pressure, units MPa
     * @param quantityType {@link ThermodynamicQuantity}
     * @param quantityValue Value of the thermodynamic quantity; units depend on quantityType (K, kJ/kg, kJ/(kg.K), or quality fraction).
     * @param inletMassFlow Inlet mass flow, units kg/hr
     * @param outletPressure Outlet pressure, units MPa
     * @param feedwaterPressure Feedwater pressure, units MPa
     * @param feedwaterQuantityType {@link ThermodynamicQuantity} for feedwater
     * @param feedwaterQuantityValue Value of the feedwater thermodynamic quantity; units depend on feedwaterQuantityType (K, kJ/kg, kJ/(kg.K), or quality fraction).
     * @param desuperheatingTemp Desuperheating temperature, units K
     */
    constructor(
        inletPressure: number,
        quantityType: ThermodynamicQuantity,
        quantityValue: number,
        inletMassFlow: number,
        outletPressure: number,
        feedwaterPressure: number,
        feedwaterQuantityType: ThermodynamicQuantity,
        feedwaterQuantityValue: number,
        desuperheatingTemp: number
    );

    /** @returns {@link SteamPropertiesOutput} inlet steam properties */
    getInletProperties(): SteamPropertiesOutput;
    /** @returns {@link SteamPropertiesOutput} outlet steam properties */
    getOutletProperties(): SteamPropertiesOutput;
    /** @returns Inlet mass flow, units kg/hr */
    getInletMassFlow(): number;
    /** @returns Inlet energy flow, units MJ/hr */
    getInletEnergyFlow(): number;
    /** @returns Outlet mass flow, units kg/hr */
    getOutletMassFlow(): number;
    /** @returns Outlet energy flow, units MJ/hr */
    getOutletEnergyFlow(): number;
    /** @returns {@link SteamPropertiesOutput} feedwater steam properties */
    getFeedwaterProperties(): SteamPropertiesOutput;
    /** @returns Feedwater mass flow, units kg/hr */
    getFeedwaterMassFlow(): number;
    /** @returns Feedwater energy flow, units MJ/hr */
    getFeedwaterEnergyFlow(): number;
    /** @returns Whether desuperheating is active */
    isWithDesuperheating(): boolean;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Casts a {@link PrvWithoutDesuperheating} instance to {@link PrvWithDesuperheating}.
 */
export declare class PrvCastDesuperheating {
    constructor();
    /**
     * Casts a PRV-without-desuperheating shared pointer to PRV-with-desuperheating.
     * @param prvWithout The `PrvWithoutDesuperheating` instance to cast
     * @returns The same object as {@link PrvWithDesuperheating}
     */
    Cast(prvWithout: PrvWithoutDesuperheating): PrvWithDesuperheating;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Deaerator
// ---------------------------------------------------------------------------

/**
 * Calculates required water and steam flows for a target feedwater mass flow.
 */
export declare class Deaerator {
    /**
     * @param deaeratorPressure Deaerator pressure, units MPa
     * @param ventRate Vent rate, units %
     * @param feedwaterMassFlow Feedwater mass flow, units kg/hr
     * @param waterPressure Inlet water pressure, units MPa
     * @param waterQuantityType {@link ThermodynamicQuantity} for water
     * @param waterQuantityValue Value of the water thermodynamic quantity; units depend on waterQuantityType (K, kJ/kg, kJ/(kg.K), or quality fraction).
     * @param steamPressure Inlet steam pressure, units MPa
     * @param steamQuantityType {@link ThermodynamicQuantity} for steam
     * @param steamQuantityValue Value of the steam thermodynamic quantity; units depend on steamQuantityType (K, kJ/kg, kJ/(kg.K), or quality fraction).
     */
    constructor(
        deaeratorPressure: number,
        ventRate: number,
        feedwaterMassFlow: number,
        waterPressure: number,
        waterQuantityType: ThermodynamicQuantity,
        waterQuantityValue: number,
        steamPressure: number,
        steamQuantityType: ThermodynamicQuantity,
        steamQuantityValue: number
    );

    /** @returns {@link FluidProperties} feedwater properties */
    getFeedwaterProperties(): FluidProperties;
    /** @returns {@link FluidProperties} vented steam properties */
    getVentedSteamProperties(): FluidProperties;
    /** @returns {@link FluidProperties} inlet water properties */
    getInletWaterProperties(): FluidProperties;
    /** @returns {@link FluidProperties} inlet steam properties */
    getInletSteamProperties(): FluidProperties;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Header / Inlet
// ---------------------------------------------------------------------------

/**
 * A single steam inlet for use with the {@link Header} calculator.
 */
export declare class Inlet {
    /**
     * @param pressure Inlet pressure, units MPa
     * @param quantityType {@link ThermodynamicQuantity}
     * @param quantityValue Value of the thermodynamic quantity; units depend on quantityType (K, kJ/kg, kJ/(kg.K), or quality fraction).
     * @param massFlow Inlet mass flow, units kg/hr
     */
    constructor(
        pressure: number,
        quantityType: ThermodynamicQuantity,
        quantityValue: number,
        massFlow: number
    );

    /** @returns {@link SteamPropertiesOutput} inlet steam properties */
    getInletProperties(): SteamPropertiesOutput;
    /** @returns Inlet energy flow, units kJ/hr */
    getInletEnergyFlow(): number;
    /** @returns Inlet mass flow, units kg/hr */
    getMassFlow(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates combined steam header properties from a list of inlet streams.
 */
export declare class Header {
    /**
     * @param headerPressure Header pressure, units MPa
     * @param inletVec Registered WASM vector of {@link Inlet} objects. Call
     * `delete()` when finished with the vector.
     */
    constructor(headerPressure: number, inletVec: InletVector);

    /** @returns {@link SteamPropertiesOutput} combined header steam properties */
    getHeaderProperties(): SteamPropertiesOutput;
    /** @returns Header pressure, units MPa */
    getHeaderPressure(): number;
    /** @returns Total inlet energy flow, units kJ/hr */
    getInletEnergyFlow(): number;
    /** @returns Total inlet mass flow, units kg/hr */
    getInletMassFlow(): number;
    /**
     * @returns Registered WASM vector of {@link Inlet} objects. Call `delete()`
     * when finished with the vector.
     */
    getInlets(): InletVector;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Turbine
// ---------------------------------------------------------------------------

/**
 * Calculates turbine properties (outlet state or isentropic efficiency).
 *
 * Two constructor overloads:
 *  1. Solve for outlet properties (known isentropic efficiency)
 *  2. Solve for isentropic efficiency (known outlet conditions)
 *
 */
export declare class Turbine {
    /**
     * Solve for outlet properties given isentropic efficiency.
     *
     * @param solveFor {@link Solve} - must be `OutletProperties`
     * @param inletPressure Inlet pressure, units MPa
     * @param inletQuantity {@link ThermodynamicQuantity} for inlet
     * @param inletQuantityValue Inlet thermodynamic quantity value (K, kJ/kg, kJ/(kg.K), or unitless)
     * @param turbineProperty {@link TurbineProperty} - `MassFlow` (kg/hr) or `PowerOut` (kW)
     * @param isentropicEfficiency Isentropic efficiency, fraction
     * @param generatorEfficiency Generator (conversion) efficiency, fraction
     * @param massFlowOrPowerOut Known turbine property value (kg/hr or kW)
     * @param outletSteamPressure Outlet steam pressure, units MPa
     */
    constructor(
        solveFor: Solve,
        inletPressure: number,
        inletQuantity: ThermodynamicQuantity,
        inletQuantityValue: number,
        turbineProperty: TurbineProperty,
        isentropicEfficiency: number,
        generatorEfficiency: number,
        massFlowOrPowerOut: number,
        outletSteamPressure: number
    );

    /**
     * Solve for isentropic efficiency given known outlet conditions.
     *
     * @param solveFor {@link Solve} - must be `IsentropicEfficiency`
     * @param inletPressure Inlet pressure, units MPa
     * @param inletQuantity {@link ThermodynamicQuantity} for inlet
     * @param inletQuantityValue Inlet thermodynamic quantity value; units depend on inletQuantity (K, kJ/kg, kJ/(kg.K), or quality fraction).
     * @param turbineProperty {@link TurbineProperty} selector for mass flow or power output.
     * @param generatorEfficiency Generator efficiency, dimensionless fraction.
     * @param massFlowOrPowerOut Known turbine property value; units kg/hr when turbineProperty is MassFlow, units kW when turbineProperty is PowerOut.
     * @param outletSteamPressure Outlet steam pressure, units MPa
     * @param outletQuantity {@link ThermodynamicQuantity} for outlet
     * @param outletQuantityValue Outlet thermodynamic quantity value; units depend on outletQuantity (K, kJ/kg, kJ/(kg.K), or quality fraction).
     */
    constructor(
        solveFor: Solve,
        inletPressure: number,
        inletQuantity: ThermodynamicQuantity,
        inletQuantityValue: number,
        turbineProperty: TurbineProperty,
        generatorEfficiency: number,
        massFlowOrPowerOut: number,
        outletSteamPressure: number,
        outletQuantity: ThermodynamicQuantity,
        outletQuantityValue: number
    );

    /** @returns {@link SteamPropertiesOutput} inlet steam properties */
    getInletProperties(): SteamPropertiesOutput;
    /** @returns Inlet energy flow, units MJ/hr */
    getInletEnergyFlow(): number;
    /** @returns {@link SteamPropertiesOutput} outlet steam properties */
    getOutletProperties(): SteamPropertiesOutput;
    /** @returns Outlet energy flow, units MJ/hr */
    getOutletEnergyFlow(): number;
    /** @returns Mass flow, units kg/hr */
    getMassFlow(): number;
    /** @returns Isentropic efficiency, units % */
    getIsentropicEfficiency(): number;
    /** @returns Energy output, units MJ/hr */
    getEnergyOut(): number;
    /** @returns Power output, units kW */
    getPowerOut(): number;
    /** @returns Generator efficiency, units % */
    getGeneratorEfficiency(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// HeatExchanger
// ---------------------------------------------------------------------------

/**
 * Result object returned by {@link HeatExchanger.calculate}.
 *
 * @property hotOutlet Outlet properties of the hot-side fluid
 * @property coldOutlet Outlet properties of the cold-side fluid
 */
export declare class HeatExchangerOutput {
    private constructor();

    /** Outlet properties of the hot-side fluid */
    hotOutlet: FluidProperties;
    /** Outlet properties of the cold-side fluid */
    coldOutlet: FluidProperties;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates a steam-to-water (or steam-to-steam) heat exchanger.
 *
 * Both inlets must have `ThermodynamicQuantity.TEMPERATURE` as their
 * quantity type, otherwise an exception is thrown.
 */
export declare class HeatExchanger {
    /**
     * @param hotInlet {@link FluidProperties} of the hot-side inlet
     * @param coldInlet {@link FluidProperties} of the cold-side inlet
     * @param approachTemp Minimum temperature approach between hot outlet and cold inlet, units K (default: 20)
     */
    constructor(
        hotInlet: FluidProperties,
        coldInlet: FluidProperties,
        approachTemp: number
    );

    /**
     * Calculate heat exchanger output.
     *
     * @returns {@link HeatExchangerOutput}
     */
    calculate(): HeatExchangerOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type SsmtModule = {
    SaturatedPropertiesOutput: typeof SaturatedPropertiesOutput;
    SteamPropertiesOutput: typeof SteamPropertiesOutput;
    FluidProperties: typeof FluidProperties;
    SaturatedPressure: typeof SaturatedPressure;
    SaturatedTemperature: typeof SaturatedTemperature;
    SaturatedProperties: typeof SaturatedProperties;
    SteamProperties: typeof SteamProperties;
    Boiler: typeof Boiler;
    HeatLoss: typeof HeatLoss;
    FlashTank: typeof FlashTank;
    PrvWithoutDesuperheating: typeof PrvWithoutDesuperheating;
    PrvWithDesuperheating: typeof PrvWithDesuperheating;
    PrvCastDesuperheating: typeof PrvCastDesuperheating;
    Deaerator: typeof Deaerator;
    Inlet: typeof Inlet;
    Header: typeof Header;
    Turbine: typeof Turbine;
    HeatExchanger: typeof HeatExchanger;
    HeatExchangerOutput: typeof HeatExchangerOutput;
};
