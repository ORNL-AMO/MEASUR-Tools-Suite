export * from "./ts_def_modules/binding/registered_vectors";

export * from "./ts_def_modules/compressedAir/compressedAir";
export * from "./ts_def_modules/compressedAir/compressed_air_utils";
export * from "./ts_def_modules/compressedAir/dryer_operating_cost";
export * from "./ts_def_modules/compressedAir/operating_cost";
export * from "./ts_def_modules/compressedAir/pipe_sizing";
export * from "./ts_def_modules/compressedAir/pneumatic_air_requirement";
export * from "./ts_def_modules/compressedAir/pneumatic_valve";
export * from "./ts_def_modules/compressedAir/receiver_tank";

export * from "./ts_def_modules/compressedAir/assessment/compressor";
export * from "./ts_def_modules/compressedAir/assessment/compressor_catalog";
export * from "./ts_def_modules/compressedAir/assessment/compressor_eem";
export * from "./ts_def_modules/compressedAir/assessment/compressor_performance_points";
export * from "./ts_def_modules/compressedAir/assessment/compressor_system_profile";
export * from "./ts_def_modules/compressedAir/assessment/centrifugal_compressor";
export * from "./ts_def_modules/compressedAir/assessment/load_unload_compressor";
export * from "./ts_def_modules/compressedAir/assessment/modulation_without_unload_compressor";
export * from "./ts_def_modules/compressedAir/assessment/start_stop_compressor";
export * from "./ts_def_modules/compressedAir/assessment/vfd_compressor";

export * from "./ts_def_modules/compressedAir/leak_survey/bag_method";
export * from "./ts_def_modules/compressedAir/leak_survey/compressed_air_leak_survey";
export * from "./ts_def_modules/compressedAir/leak_survey/decibels_method";
export * from "./ts_def_modules/compressedAir/leak_survey/estimate_method";
export * from "./ts_def_modules/compressedAir/leak_survey/orifice_method";

export * from "./ts_def_modules/databases/default_data";

export * from "./ts_def_modules/motorDriven/fans/fan";
export * from "./ts_def_modules/motorDriven/fans/fanEnum";
export * from "./ts_def_modules/motorDriven/fans/fan_affinity_laws";

export * from "./ts_def_modules/motorDriven/motor/motor";
export * from "./ts_def_modules/motorDriven/motor/motorEnum";

export * from "./ts_def_modules/motorDriven/pump/pump";
export * from "./ts_def_modules/motorDriven/pump/pump_valve_power_loss";

export * from "./ts_def_modules/motorDriven/pumpFan/pumpFan";

export * from "./ts_def_modules/other/chp";
export * from "./ts_def_modules/other/lighting_data";
export * from "./ts_def_modules/other/powerFactor";

export * from "./ts_def_modules/physics/gas_compositions";

export * from "./ts_def_modules/processCooling/chillers";
export * from "./ts_def_modules/processCooling/process_cooling";

export * from "./ts_def_modules/processHeat/air_heating_using_exhaust";
export * from "./ts_def_modules/processHeat/cascade_heat_high_to_low";
export * from "./ts_def_modules/processHeat/energy_equivalency";
export * from "./ts_def_modules/processHeat/flow_calculations_energy_use";
export * from "./ts_def_modules/processHeat/o2_enrichment";
export * from "./ts_def_modules/processHeat/water_heating_using_exhaust";

export * from "./ts_def_modules/processHeat/losses/atmosphere_heat_loss";
export * from "./ts_def_modules/processHeat/losses/auxiliary_power_used";
export * from "./ts_def_modules/processHeat/losses/energy_input_electric_arc_furnace";
export * from "./ts_def_modules/processHeat/losses/energy_input_exhaust_gas_heat_loss";
export * from "./ts_def_modules/processHeat/losses/exhaust_gas_heat_loss_electric_arc_furnace";
export * from "./ts_def_modules/processHeat/losses/fixture_heat_loss";
export * from "./ts_def_modules/processHeat/losses/gas_cooling_heat_loss";
export * from "./ts_def_modules/processHeat/losses/gas_flue_gas_material";
export * from "./ts_def_modules/processHeat/losses/gas_load_charge_material_heat_required";
export * from "./ts_def_modules/processHeat/losses/leakage_heat_loss";
export * from "./ts_def_modules/processHeat/losses/liquid_cooling_heat_loss";
export * from "./ts_def_modules/processHeat/losses/liquid_load_charge_material_heat_required";
export * from "./ts_def_modules/processHeat/losses/load_charge_material";
export * from "./ts_def_modules/processHeat/losses/opening_heat_loss";
export * from "./ts_def_modules/processHeat/losses/slag_other_material_heat_loss";
export * from "./ts_def_modules/processHeat/losses/solid_liquid_flue_gas_material";
export * from "./ts_def_modules/processHeat/losses/solid_load_charge_material_heat_required";
export * from "./ts_def_modules/processHeat/losses/wall_heat_loss";
export * from "./ts_def_modules/processHeat/losses/water_cooling_heat_loss";

export * from "./ts_def_modules/steam/air_water_cooling_using_flue";
export * from "./ts_def_modules/steam/steam_leak_survey";
export * from "./ts_def_modules/steam/water_heating_using_flue";
export * from "./ts_def_modules/steam/water_heating_using_steam";

export * from "./ts_def_modules/steamModeler/ssmt";
export * from "./ts_def_modules/steamModeler/ssmtEnum";
export * from "./ts_def_modules/steamModeler/ssmtModeler";

export * from "./ts_def_modules/treasureHunt/compressed_air_pressure_reduction";
export * from "./ts_def_modules/treasureHunt/compressed_air_reduction";
export * from "./ts_def_modules/treasureHunt/electricity_reduction";
export * from "./ts_def_modules/treasureHunt/insulated_pipe_reduction";
export * from "./ts_def_modules/treasureHunt/insulated_tank_reduction";
export * from "./ts_def_modules/treasureHunt/natural_gas_reduction";
export * from "./ts_def_modules/treasureHunt/steam_reduction";
export * from "./ts_def_modules/treasureHunt/water_reduction";

export * from "./ts_def_modules/wasteWater/svi";
export * from "./ts_def_modules/wasteWater/wasteWater";

export * from "./ts_def_modules/water/waterAssessment";

/**
 * Represents the fully-initialized MEASUR Tools Suite WebAssembly module instance.
 * This is the intersection of all sub-module types, giving full typed access to every
 * calculator, class, and enum exposed by the WASM bindings.
 *
 * Use this type to annotate the result of the module factory without any casting:
 * @example
 * ```ts
 * import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';
 * const m: MeasurToolsSuite = await createModule({ locateFile: (f) => `/wasm/${f}` });
 * ```
 */
export type MeasurToolsSuite =
    // binding
    import("./ts_def_modules/binding/registered_vectors").RegisteredVectorsModule &
    // compressedAir
    import("./ts_def_modules/compressedAir/compressedAir").CompressedAirModule &
    import("./ts_def_modules/compressedAir/compressed_air_utils").CompressedAirUtilsModule &
    import("./ts_def_modules/compressedAir/dryer_operating_cost").DryerOperatingCostModule &
    import("./ts_def_modules/compressedAir/operating_cost").OperatingCostModule &
    import("./ts_def_modules/compressedAir/pipe_sizing").PipeSizingModule &
    import("./ts_def_modules/compressedAir/pneumatic_air_requirement").PneumaticAirRequirementModule &
    import("./ts_def_modules/compressedAir/pneumatic_valve").PneumaticValveModule &
    import("./ts_def_modules/compressedAir/receiver_tank").ReceiverTankModule &
    import("./ts_def_modules/compressedAir/assessment/compressor").CompressorAssessmentSharedModule &
    import("./ts_def_modules/compressedAir/assessment/compressor_eem").CompressorEemModule &
    import("./ts_def_modules/compressedAir/assessment/compressor_performance_points").CompressorPerformancePointsModule &
    import("./ts_def_modules/compressedAir/assessment/compressor_system_profile").CompressorSystemProfileModule &
    import("./ts_def_modules/compressedAir/assessment/centrifugal_compressor").CentrifugalCompressorModule &
    import("./ts_def_modules/compressedAir/assessment/load_unload_compressor").LoadUnloadCompressorModule &
    import("./ts_def_modules/compressedAir/assessment/modulation_without_unload_compressor").ModulationWithoutUnloadCompressorModule &
    import("./ts_def_modules/compressedAir/assessment/start_stop_compressor").StartStopCompressorModule &
    import("./ts_def_modules/compressedAir/assessment/vfd_compressor").VfdCompressorModule &
    // compressedAir/leak_survey
    import("./ts_def_modules/compressedAir/leak_survey/bag_method").BagMethodModule &
    import("./ts_def_modules/compressedAir/leak_survey/compressed_air_leak_survey").CompressedAirLeakSurveyModule &
    import("./ts_def_modules/compressedAir/leak_survey/decibels_method").DecibelsMethodModule &
    import("./ts_def_modules/compressedAir/leak_survey/estimate_method").EstimateMethodModule &
    import("./ts_def_modules/compressedAir/leak_survey/orifice_method").OrificeMethodModule &
    // databases
    import("./ts_def_modules/databases/default_data").DefaultDataModule &
    // motorDriven/fans
    import("./ts_def_modules/motorDriven/fans/fan_affinity_laws").FanAffinityLawsModule &
    import("./ts_def_modules/motorDriven/fans/fanEnum").FanEnumModule &
    import("./ts_def_modules/motorDriven/fans/fan").FanModule &
    // motorDriven/motor
    import("./ts_def_modules/motorDriven/motor/motorEnum").MotorEnumModule &
    import("./ts_def_modules/motorDriven/motor/motor").MotorModule &
    // motorDriven/pump
    import("./ts_def_modules/motorDriven/pump/pump").PumpModule &
    import("./ts_def_modules/motorDriven/pump/pump_valve_power_loss").PumpValvePowerLossModule &
    // motorDriven/pumpFan
    import("./ts_def_modules/motorDriven/pumpFan/pumpFan").PumpFanModule &
    // other
    import("./ts_def_modules/other/chp").ChpModule &
    import("./ts_def_modules/other/lighting_data").LightingDataModule &
    import("./ts_def_modules/other/powerFactor").PowerFactorModule &
    // physics
    import("./ts_def_modules/physics/gas_compositions").GasCompositionsModule &
    // processCooling
    import("./ts_def_modules/processCooling/chillers").ChillersModule &
    import("./ts_def_modules/processCooling/process_cooling").ProcessCoolingModule &
    // processHeat
    import("./ts_def_modules/processHeat/air_heating_using_exhaust").AirHeatingUsingExhaustModule &
    import("./ts_def_modules/processHeat/cascade_heat_high_to_low").CascadeHeatHighToLowModule &
    import("./ts_def_modules/processHeat/energy_equivalency").EnergyEquivalencyModule &
    import("./ts_def_modules/processHeat/flow_calculations_energy_use").FlowCalculationsEnergyUseModule &
    import("./ts_def_modules/processHeat/o2_enrichment").O2EnrichmentModule &
    import("./ts_def_modules/processHeat/water_heating_using_exhaust").WaterHeatingUsingExhaustModule &
    // processHeat/losses
    import("./ts_def_modules/processHeat/losses/atmosphere_heat_loss").AtmosphereHeatLossModule &
    import("./ts_def_modules/processHeat/losses/auxiliary_power_used").AuxiliaryPowerUsedModule &
    import("./ts_def_modules/processHeat/losses/energy_input_electric_arc_furnace").EnergyInputElectricArcFurnaceModule &
    import("./ts_def_modules/processHeat/losses/energy_input_exhaust_gas_heat_loss").EnergyInputExhaustGasHeatLossModule &
    import("./ts_def_modules/processHeat/losses/exhaust_gas_heat_loss_electric_arc_furnace").ExhaustGasHeatLossElectricArcFurnaceModule &
    import("./ts_def_modules/processHeat/losses/fixture_heat_loss").FixtureHeatLossModule &
    import("./ts_def_modules/processHeat/losses/gas_cooling_heat_loss").GasCoolingHeatLossModule &
    import("./ts_def_modules/processHeat/losses/gas_flue_gas_material").GasFlueGasMaterialModule &
    import("./ts_def_modules/processHeat/losses/gas_load_charge_material_heat_required").GasLoadChargeMaterialHeatRequiredModule &
    import("./ts_def_modules/processHeat/losses/leakage_heat_loss").LeakageHeatLossModule &
    import("./ts_def_modules/processHeat/losses/liquid_cooling_heat_loss").LiquidCoolingHeatLossModule &
    import("./ts_def_modules/processHeat/losses/liquid_load_charge_material_heat_required").LiquidLoadChargeMaterialHeatRequiredModule &
    import("./ts_def_modules/processHeat/losses/load_charge_material").LoadChargeMaterialModule &
    import("./ts_def_modules/processHeat/losses/opening_heat_loss").OpeningHeatLossModule &
    import("./ts_def_modules/processHeat/losses/slag_other_material_heat_loss").SlagOtherMaterialHeatLossModule &
    import("./ts_def_modules/processHeat/losses/solid_liquid_flue_gas_material").SolidLiquidFlueGasMaterialModule &
    import("./ts_def_modules/processHeat/losses/solid_load_charge_material_heat_required").SolidLoadChargeMaterialHeatRequiredModule &
    import("./ts_def_modules/processHeat/losses/wall_heat_loss").WallHeatLossModule &
    import("./ts_def_modules/processHeat/losses/water_cooling_heat_loss").WaterCoolingHeatLossModule &
    // steam
    import("./ts_def_modules/steam/air_water_cooling_using_flue").AirWaterCoolingUsingFlueModule &
    import("./ts_def_modules/steam/steam_leak_survey").SteamLeakSurveyModule &
    import("./ts_def_modules/steam/water_heating_using_flue").WaterHeatingUsingFlueModule &
    import("./ts_def_modules/steam/water_heating_using_steam").WaterHeatingUsingSteamModule &
    // steamModeler
    import("./ts_def_modules/steamModeler/ssmtEnum").SsmtEnumModule &
    import("./ts_def_modules/steamModeler/ssmt").SsmtModule &
    import("./ts_def_modules/steamModeler/ssmtModeler").SsmtModelerModule &
    // treasureHunt
    import("./ts_def_modules/treasureHunt/compressed_air_pressure_reduction").CompressedAirPressureReductionModule &
    import("./ts_def_modules/treasureHunt/compressed_air_reduction").CompressedAirReductionModule &
    import("./ts_def_modules/treasureHunt/electricity_reduction").ElectricityReductionModule &
    import("./ts_def_modules/treasureHunt/insulated_pipe_reduction").InsulatedPipeReductionModule &
    import("./ts_def_modules/treasureHunt/insulated_tank_reduction").InsulatedTankReductionModule &
    import("./ts_def_modules/treasureHunt/natural_gas_reduction").NaturalGasReductionModule &
    import("./ts_def_modules/treasureHunt/steam_reduction").SteamReductionModule &
    import("./ts_def_modules/treasureHunt/water_reduction").WaterReductionModule &
    // wasteWater
    import("./ts_def_modules/wasteWater/svi").SviModule &
    import("./ts_def_modules/wasteWater/wasteWater").WasteWaterModule &
    // water
    import("./ts_def_modules/water/waterAssessment").WaterAssessmentModule;

declare const _default: (moduleArg?: Record<string, unknown>) => Promise<MeasurToolsSuite>;
export default _default;
