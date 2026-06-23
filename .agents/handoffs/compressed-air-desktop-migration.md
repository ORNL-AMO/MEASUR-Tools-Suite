# Compressed Air Desktop Migration Handoff

## Target Module

- Domain/path: `compressedAir/assessment`
- Logical modules:
  - `compressor_performance_points`
  - `compressor_system_profile`
  - extended `compressor_eem`
- Desktop source path: `/Users/txr/dev/AMO-Tools-Desktop/src/app/compressed-air-assessment/calculations`
- Suite public API path:
  - C++: `include/compressedAir/assessment/`
  - WASM declarations: `ts_def/ts_def_modules/compressedAir/assessment/`
  - Docs: `docs/dox-content/calculators/compressedAir/assessment/`

## Migration Boundary

- Move reusable calculation kernels into Suite.
- Keep Desktop responsible for:
  - metric conversion before calling Suite and display-unit conversion after results
  - form validation and display flags
  - modification ordering, labels, notes, modal state, and UI-only flags
  - assessment persistence and report shaping
  - CO2 service integration and emission-factor calculations
  - mapping Desktop numeric IDs and string modes to Suite enums

## Old Desktop Files And Suite Replacements

- `calculations/performancePoints/CompressorPerformancePointsClass.ts`
  - Replace default point generation with `generatePerformancePoints`.
  - Replace sequencer adjustment with `adjustPerformancePointsForSequencer`.
  - Replace pressure reduction adjustment with `reduceSystemPressurePerformancePoints`.
  - Replace cascading set-point adjustment with `adjustCascadingSetPointPerformancePoints`.
- `calculations/performancePoints/*PerformancePoint.ts`
  - Replace formulas with `compressor_performance_points` helpers and `generatePerformancePoints`.
  - Keep only UI display metadata if still needed.
- `calculations/performancePoints/performancePointHelpers.ts`
  - Replace with:
    - `calculatePressureAdjustedAirflow`
    - `calculatePressureAdjustedPower`
    - `calculateNoLoadPower`
    - `calculateNoLoadPowerWithoutUnloading`
    - `calculateUnloadPointPower`
    - `calculateUnloadPointAirflow`
    - `calculateUnloadPointDischargePressure`
    - `calculateCentrifugalUnloadPointAirflow`
    - `calculateRatedSpecificPower`
    - `calculateRatedIsentropicEfficiency`
- `calculations/CompressorInventoryItemClass.ts`
  - Replace performance-point mutation methods with Suite point-generation functions.
  - Replace rated metrics with `calculateRatedSpecificPower` and `calculateRatedIsentropicEfficiency`.
  - Keep display flags, persistence conversion, inventory item identity, colors, descriptions, and connected-inventory behavior in Desktop.
- `calculations/CompressedAirBaselineDayTypeProfileSummary.ts`
  - Replace compressor profile row calculations with `calculateBaselineProfile`.
  - Keep aggregation into Desktop view models and report state in Desktop.
- `calculations/CompressedAirProfileSummary.ts`
  - Replace calculation logic with `CompressorProfileRow` mapping where possible.
  - Keep presentation structure if Angular components still consume it.
- `calculations/modifications/energyEfficiencyMeasures/FlowReallocationResults.ts`
  - Replace flow reallocation, load sharing, base trim, reduce-runtime, and zero-flow shutdown calculations with `reallocateProfileFlow`.
  - Replace total rows with `calculateProfileTotals`.
  - Keep modification ordering and adjusted profile view-model mapping in Desktop.
- `calculations/modifications/CompressedAirEemSavingsResult.ts`
  - Replace day-type energy/cost/payback math with `calculateProfileSavings`.
  - Keep CO2/emissions enrichment and report-specific result shape in Desktop.
- `calculations/modifications/energyEfficiencyMeasures/compressorsAdjustment.ts`
  - Replace `calculateReducedAirFlow` with `calculatePressureReducedAirflow` or `pressureReducedAirflow`.
  - Keep order reshaping if it is only a Desktop display concern.
- `ReduceAirLeaksResults.ts`, `ImproveEndUseEfficiencyResults.ts`, `ReduceSystemAirPressureResults.ts`, `AdjustCascadingSetPointsSavingsResults.ts`, `UseAutomaticSequencerResults.ts`, `ReplaceCompressorResults.ts`
  - Replace reusable scalar/profile transforms with Suite EEM and profile functions.
  - Keep UI labels, selected modifications, adjusted compressor copies, replacement mapping, and report shaping in Desktop.
- `ResultingSystemProfileValidation.ts`
  - Keep in Desktop unless it becomes a pure numerical validation rule with no form/report dependency.

## Suite Functions, Inputs, Outputs, And Units

### Performance Points

- `generatePerformancePoints(input: CompressorPerformancePointInput): CompressorPerformancePoints`
  - Inputs: nameplate, controls, design details, centrifugal endpoints, existing point values/default flags, atmospheric pressure.
  - Outputs: full-load, max-full-flow, mid-turndown, turndown, unload, no-load, blowoff points.
  - Units: pressure psig/psia, airflow acfm, power kW, motor size hp, percentages as percent, flags dimensionless boolean.
- `adjustPerformancePointsForSequencer(input: SequencerSetPointInput): CompressorPerformancePoints`
  - Inputs: compressor point input, target pressure psig, variance psig.
  - Outputs: regenerated point bundle.
- `reduceSystemPressurePerformancePoints(input: PressureReductionPointInput): CompressorPerformancePoints`
  - Inputs: compressor point input, pressure reduction psig.
  - Outputs: regenerated point bundle.
- `adjustCascadingSetPointPerformancePoints(input: CascadingSetPointInput): CompressorPerformancePoints`
  - Inputs: compressor point input, adjusted full-load pressure psig, adjusted max-full-flow pressure psig.
  - Outputs: regenerated point bundle.
- Scalar helpers:
  - `calculatePressureAdjustedAirflow(capacityAcfm, pointPressurePsig, ratedPressurePsig, atmosphericPressurePsia): number` returns acfm.
  - `calculatePressureAdjustedPower(compressorType, inletPressurePsia, pointPressurePsig, ratedFullLoadPressurePsig, packagePowerKw, atmosphericPressurePsia): number` returns kW.
  - `calculateNoLoadPower(noLoadPowerULPercent, packagePowerKw, designEfficiencyPercent): number` returns kW.
  - `calculateNoLoadPowerWithoutUnloading(noLoadPowerFMPercent, fullLoadPowerKw): number` returns kW.
  - `calculateUnloadPointPower(noLoadPowerFMPercent, unloadPointCapacityPercent, exponent, maxFullFlowPowerKw): number` returns kW.
  - `calculateUnloadPointAirflow(fullLoadAirflowAcfm, unloadPointCapacityPercent): number` returns acfm.
  - `calculateUnloadPointDischargePressure(maxFullFlowPressurePsig, modulatingPressureRangePsig, fullLoadAirflowAcfm, unloadPointAirflowAcfm): number` returns psig.
  - `calculateCentrifugalUnloadPointAirflow(centrifugal, dischargePressurePsig): number` returns acfm.
  - `calculateRatedSpecificPower(totalPackageInputPowerKw, fullLoadRatedCapacityAcfm): number` returns kW/100 acfm.
  - `calculateRatedIsentropicEfficiency(ratedSpecificPower, fullLoadOperatingPressurePsig): number` returns percent.

### System Profile

- `calculateBaselineProfile(compressors, profileRows, options): CompressorProfileRowV`
  - Inputs: `CompressorProfileCompressorV`, `CompressorProfileRowV`, `CompressorProfileOptions`.
  - Outputs: registered vector of calculated compressor rows. Caller must call `delete()`.
- `calculateProfileTotals(compressors, profileRows): CompressorProfileTotalV`
  - Inputs: compressor vector, calculated row vector.
  - Outputs: registered vector of total rows. Caller must call `delete()`.
- `reallocateProfileFlow(compressors, previousProfileRows, demandRows, options, runtimeStates, trimSelections): CompressorProfileRowV`
  - Inputs: compressor vector, prior row vector, demand total vector, options, runtime state vector, trim selection vector.
  - Outputs: registered vector of adjusted compressor rows. Caller must call `delete()`.
- `calculateProfileSavings(baselineRows, adjustedRows, input): CompressorProfileSavingsResult`
  - Inputs: baseline row vector, adjusted row vector, electricity cost dollars/kWh, interval hours, operating days, auxiliary energy kWh/year, implementation cost dollars, salvage dollars.
  - Outputs: annual baseline/adjusted energy kWh, annual baseline/adjusted cost dollars, energy savings kWh, cost savings dollars, percent savings, payback months.
- `calculateCompressorProfileRow(compressor, inputBasis, inputValue, options, powerFactor, amps, volts): CompressorProfileRow`
  - Inputs: one compressor definition, input basis, numeric input value in basis units, options, electrical values.
  - Outputs: one calculated profile row.
- `calculatePressureReducedAirflow(useAirflowAcfm, adjustedFullLoadPressurePsig, altitudePressurePsia, originalFullLoadPressurePsig, atmosphericPressurePsia): number`
  - Output: pressure-reduced airflow acfm.

### EEM Helpers

- Existing Suite helpers:
  - `reduceAirLeaks`
  - `improveEndUseEfficiency`
  - `reduceSystemAirPressure`
  - `adjustCascadingSetPoint`
  - `pressureReductionSaving`
  - `adjustedPower`
- New reusable transforms:
  - `pressureReducedAirflow(useAirflowAcfm, adjustedFullLoadPressurePsig, altitudePressurePsia, originalFullLoadPressurePsig, atmosphericPressurePsia): number`
  - `addReceiverVolume(currentReceiverVolumeFt3, addedReceiverVolumeFt3): ReceiverVolumeResult`
  - `automaticSequencerSetPoints(targetPressurePsig, variancePsig): AutomaticSequencerSetPointResult`

## Enum And ID Mapping

Desktop compressor type IDs from `inventoryOptions.ts`:

- `1` Single stage lubricant-injected rotary screw -> `CompressorType.Screw`, `CompressorStage.Single`, `CompressorLubricant.Injected`
- `2` Two stage lubricant-injected rotary screw -> `CompressorType.Screw`, `CompressorStage.Two`, `CompressorLubricant.Injected`
- `3` Two stage lubricant-free rotary screw -> `CompressorType.Screw`, `CompressorStage.Two`, `CompressorLubricant.Free`
- `4` Single stage reciprocating -> `CompressorType.Reciprocating`, `CompressorStage.Single`, `CompressorLubricant.None`
- `5` Two stage reciprocating -> `CompressorType.Reciprocating`, `CompressorStage.Two`, `CompressorLubricant.None`
- `6` Multiple stage centrifugal -> `CompressorType.Centrifugal`, `CompressorStage.Multiple`, `CompressorLubricant.None`

Desktop control IDs from `inventoryOptions.ts`:

- `1` Inlet modulation without unloading -> `CompressorControl.ModulationWithoutUnload`
- `2` Inlet modulation with unloading -> `CompressorControl.ModulationUnload`
- `3` Variable displacement with unloading -> `CompressorControl.VariableDisplacementUnload`
- `4` Load/unload -> `CompressorControl.LoadUnload`
- `5` Multi-step unloading -> `CompressorControl.MultiStepUnloading`
- `6` Start/Stop -> `CompressorControl.StartStop`
- `7` Inlet butterfly modulation with blowoff -> `CompressorControl.BlowOff`
- `8` Inlet butterfly modulation with unloading -> `CompressorControl.ModulationUnload`
- `9` Inlet guide vane modulation with blowoff -> `CompressorControl.BlowOff`
- `10` Inlet guide vane modulation with unloading -> `CompressorControl.ModulationUnload`
- `11` VFD -> `CompressorControl.Vfd`

Desktop profile input basis IDs from `SuiteApiHelperService.getComputeFromEnum`:

- `0` -> `CompressorInputBasis.PowerFraction`
- `1` -> `CompressorInputBasis.CapacityFraction`
- `2` -> `CompressorInputBasis.MeasuredPower`
- `3` -> `CompressorInputBasis.MeasuredCapacity`
- `4` -> `CompressorInputBasis.Electrical`

Desktop multi-compressor strings:

- `cascading` -> `CompressorSystemControlMode.Cascading`
- `targetPressureSequencer` -> `CompressorSystemControlMode.TargetPressureSequencer`
- `loadSharing` -> `CompressorSystemControlMode.LoadSharing`
- `baseTrim` -> `CompressorSystemControlMode.BaseTrim`
- Isentropic-efficiency ordering, when used as an explicit system strategy, maps to `CompressorSystemControlMode.IsentropicEfficiency`.

## Sample Before And After Call Patterns

### Performance Point Generation

Before:

```ts
const points = new CompressorPerformancePointsClass(item.performancePoints);
points.updatePerformancePoints(nameplateData, centrifugalSpecifics, designDetails, compressorControls, atmosphericPressure, settings);
```

After:

```ts
const points = suite.generatePerformancePoints({
  nameplate,
  controls,
  design,
  centrifugal,
  points: existingPointsWithDefaultFlags,
  atmosphericPressurePsia: atmosphericPressure,
});
```

### Baseline Profile Calculation

After:

```ts
const compressors = new suite.CompressorProfileCompressorV();
const profileRows = new suite.CompressorProfileRowV();

try {
  compressors.push_back(mappedCompressor);
  profileRows.push_back(mappedProfileRow);

  const rows = suite.calculateBaselineProfile(compressors, profileRows, options);
  try {
    const row = rows.get(0);
    // map row.powerKw, row.airflowAcfm, row.powerFraction, row.airflowFraction back to Desktop view model
  } finally {
    rows.delete();
  }
} finally {
  profileRows.delete();
  compressors.delete();
}
```

### Flow Reallocation

After:

```ts
const adjustedRows = suite.reallocateProfileFlow(
  compressors,
  previousRows,
  demandRows,
  options,
  runtimeStates,
  trimSelections
);

try {
  // read adjustedRows.get(i), then map back to ProfileSummaryData
} finally {
  adjustedRows.delete();
}
```

### EEM Savings

After:

```ts
const savings = suite.calculateProfileSavings(baselineRows, adjustedRows, {
  dayTypeId,
  electricityCostPerKwh: costKwh,
  intervalHours: summaryDataInterval,
  operatingDays,
  auxiliaryEnergyKwh,
  implementationCost,
  salvageValue,
});

// Desktop can add CO2 and report-only fields after this result returns.
```

## Characterization Fixtures And Expected Outputs

Suite characterization tests added for parity:

- `tests/cpp/compressedAir/assessment/compressor_performance_points.unit.cpp`
  - Screw modulation/unload default points:
    - full load: 100 psig, 1048 acfm, 166.5 kW
    - max full flow: 110 psig, 1040 acfm, 175.6 kW
    - unload: 110.5 psig, 943 acfm, 170.3 kW
    - no load: 15 psig, 0 acfm, 41.6 kW
  - VFD defaults:
    - mid turndown: 102.4 psig, 605 acfm, 115 kW
    - turndown: 104.8 psig, 202 acfm, 55.8 kW
- `tests/cpp/compressedAir/assessment/compressor_system_profile.unit.cpp`
  - Baseline measured capacity: 500 acfm -> 75 kW
  - Cascading reallocation: 1200 acfm -> 1000/100 kW and 200/42 kW
  - Load sharing: 750 acfm -> compressor A 750/87.5 kW and compressor B off
  - Savings: 1420 baseline kWh, 875 adjusted kWh, 545 kWh savings, $54.50 savings, 22.0183 months payback
- WASM tests:
  - `tests/wasm-mocha/compressedAir/assessment/wasm_compressor_performance_points.test.ts`
  - `tests/wasm-mocha/compressedAir/assessment/wasm_compressor_system_profile.test.ts`
  - `tests/wasm-mocha/compressedAir/assessment/wasm_compressor_eem.test.ts`

Desktop migration should add Angular-side fixtures around representative persisted assessments before deleting old calculation classes.

## Desktop Deletion And Replacement Checklist

- [ ] Add mapper helpers from Desktop compressor inventory/profile models to Suite passive objects.
- [ ] Add mapper helpers from Suite `CompressorProfileRow` and `CompressorProfileTotal` back to Desktop view models.
- [ ] Add vector helper constructors/deletion wrappers for profile vectors.
- [ ] Replace `CompressorPerformancePointsClass` update methods with Suite functions.
- [ ] Replace performance point class formulas with Suite calls or remove classes if only calculation wrappers remain.
- [ ] Replace `FlowReallocationResults.reallocateFlow`, `shareLoad`, `setBaseTrimOrdering`, and combination logic with `reallocateProfileFlow`.
- [ ] Replace baseline profile row calculation with `calculateBaselineProfile`.
- [ ] Replace day-type total calculation with `calculateProfileTotals`.
- [ ] Replace EEM savings rollup with `calculateProfileSavings`, then layer Desktop CO2/report fields.
- [ ] Replace reduced airflow, receiver-volume, sequencer set-point helpers with Suite EEM helpers.
- [ ] Keep Desktop validation/report tests green after each replacement step.
- [ ] Delete obsolete calculation files only after the mapped Suite path is covered by Desktop tests.

## Desktop Validation Commands

Run from `/Users/txr/dev/AMO-Tools-Desktop` after updating package output and Desktop adapters:

```bash
npm run lint
npm run build
npx ng test --watch=false --browsers=ChromeHeadless
```

Also run the targeted compressed-air specs added during migration. If the Desktop repo uses a different CI command set, run the same commands configured for the open PR.

## Suite Validation Status

- C++ validation passed during Suite implementation:
  - `cmake -S . -B build-cpp`
  - `cmake --build build-cpp`
  - `./build-cpp/bin/cpp_tests`
- TypeScript declaration validation passed:
  - `./node_modules/.bin/tsc --noEmit`
- Documentation validation was attempted:
  - `doxygen Doxyfile` exited 0, but reported existing CLANG option warnings, a BibTeX `bib*.bbl` error message, and unrelated undocumented-parameter warnings outside compressed air.
- Environment limit observed:
  - `emcmake` and `emmake` are not available in this shell, so Suite WASM rebuild still needs to run in an Emscripten-enabled environment.
  - `npm run tests` was attempted and failed because the local `bin/client.js` and WASM binary do not include the new assessment bindings. The failure mode was missing compressor assessment constructors/functions, including previously added compressor assessment bindings.

## Open Questions Or Blockers

- Desktop should decide whether any remaining calculations are purely UI/report shaping or should be proposed for a later Suite migration.
- CO2 emissions remain Desktop-owned until Suite APIs accept emission-factor inputs.
