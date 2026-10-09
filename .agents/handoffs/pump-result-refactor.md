# Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: Suite and Desktop implementations complete; feature branches established; Suite CI bootstrap and coordinated review pending
- Owner: Codex
- Created: 2026-10-07
- Last updated: 2026-10-09
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/203
- Suite feature branch: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/tree/epic-pump-result-refactor
- Suite CI bootstrap PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/420
- Suite PumpResult PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/421
- Desktop issue: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8951
- Desktop coordination issue: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Desktop feature branch: https://github.com/ORNL-AMO/AMO-Tools-Desktop/tree/epic-pump-result-refactor
- Desktop PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8956

## Target Module

- Domain/path: `motorDriven/pump`
- Logical module: pump result assessment
- Legacy files: `PumpResult.h/.cpp`, `pump.cpp`, `pump.d.ts`, one mixed C++ test, and two WASM tests
- Nearby examples: `motorDriven/pump/pump_head` and `compressedAir/dryer_operating_cost`

## Current Public API

- C++ symbols: global `PumpResult`, nested `PumpResult::Output`, and `Pump::Input`/`Pump::FieldData` constructor inputs
- Embind runtime names: `PumpResultInput`, `PumpFieldData`, `PumpResult`, and `PumpResults`
- TypeScript declarations: four runtime classes requiring `delete()`
- Test-visible behavior: separate existing and modified methods; savings and optimization getters always return zero

## Runtime API Contract

| Surface | Before | After | Embind kind | Units/defaults | Ownership and cleanup | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| Shared system input | Constructor arguments spread across `PumpResultInput`, `Motor`, `PumpFieldData`, and `PumpResult` | Nested `PumpResultSystemInput` plain object | `class_` inputs to `value_object` | Equipment, hydraulic duty, operating voltage, annual hours, and electricity rate | Plain nested object; no cleanup | Breaking |
| Existing result | `new PumpResult(...).calculateExisting()` | `calculateExistingPumpResult(ExistingPumpResultInput)` | `class_` to `function` + `value_object` | Efficiencies fractions; power hp/kW; energy MWh/year; cost thousand $/year | Before: four class instances require cleanup; after: plain input/result | Breaking |
| Modified result | `new PumpResult(...).calculateModified()` | `calculateModifiedPumpResult(ModifiedPumpResultInput)` | `class_` to `function` + `value_object` | Same result units; estimated full-load amps is zero | Before: four class instances require cleanup; after: plain input/result | Breaking |
| Savings metadata | Two getters that return zero | Removed | class methods removed | Desktop retains zero app-facing values | No Suite object | Breaking |

## Proposed Namespace API

- Namespace: `pump_result`
- Functions: `calculateExisting(const ExistingInput&)`, `calculateModified(const ModifiedInput&)`
- Structs/value objects: C++ `SystemInput`, `ExistingInput`, `ModifiedInput`, and `Result`; WASM/TypeScript `PumpResultSystemInput`, `ExistingPumpResultInput`, `ModifiedPumpResultInput`, and `PumpResultOutput`
- Enums: reuse existing `Pump::Style` and `Motor` enums
- Runtime names to preserve: `PumpStyle`, `SpecificSpeed`, and all Motor enum names

## Compatibility Decision

- Default: preserve public compatibility.
- Decision: intentionally breaking stateless cleanup approved by the user on 2026-10-07.
- Migration notes needed: replace constructors/method calls with plain-object functions and remove cleanup calls.
- User approval for breaking changes: explicit.
- Removed legacy surfaces: four PumpResult runtime classes and two zero-valued getters.
- Behavior change approved: none.

## Touched Layers

- Headers/source: replace global class with `pump_result.h/.cpp`; `Pump.h` remains unchanged.
- C++ tests: port all pump-result goldens; move `EstimateFLA` to its motor test.
- WebAssembly bindings: replace class bindings with two functions and three value objects.
- TypeScript declarations: replace runtime classes with interfaces and functions.
- WASM Mocha tests: consolidate into one typed plain-object test module.
- Algorithm docs: add a teaching-oriented `pump_result_calculator.dox`.

## Desktop Impact

- Wrapper or helper changes: migrate `PumpsSuiteApiService` result methods to plain inputs/functions and build one shared `PumpResultSystemInput` for both paths.
- Enum, unit, percentage, or nullable conversion changes: none; keep current adapter conversions.
- App models, reports, exports, or saved-data changes: none.
- Process-flow package changes: dependency pin only; no direct consumer found.
- Web/Electron WASM loading changes: none planned.
- Downstream verification: focused wrapper tests, Angular typecheck, and root build against exact package.
- Desktop implementation branch: `issue-8951`; rebased onto `epic-pump-result-refactor` at `d1ba297a9`.
- Desktop prerequisite: pump-head PR #8945 merged into Desktop `develop` on 2026-10-08 and is included in the feature-branch base.

## Formulas And Units

- Final result formula: electrical power passes through motor, drive, and pump efficiencies to hydraulic power.
- Supporting formulas: motor load interpolation; drive losses; rotodynamic and positive-displacement hydraulic power; annual energy and cost.
- Constants: 0.746 kW/hp; 3961.38 gpm-ft/hp; 1714.231 gpm-psi/hp; retained empirical motor and belt coefficients.
- Units: gpm, ft, psi, hp, kW, A, V, RPM, MWh/year, thousand dollars/year, and dimensionless fractions.
- Formula provenance: implementation and native/WASM regression fixtures; historical provenance of empirical motor and belt coefficients is unverified.
- Golden inputs and expected results: retained 11-case native suite plus rotodynamic and positive-displacement WASM fixtures.
- SME decisions required: none for behavior preservation.
- Unclear or unverified items: original empirical coefficient sources are not recorded.

## Package And Release Coordination

- Change classification: breaking API
- Beta package version: pending
- Final package version: pending
- Desktop root dependency: update to exact beta/final package
- Desktop process-flow dependency: keep aligned with root
- Current Desktop `develop` pins: both manifests are aligned at `1.2.6-rc.350.1`; no speculative PumpResult package version is committed.
- Release readiness: Suite PR #421 and Desktop PR #8956 are intentionally draft pending integrated beta validation
- Release blockers: approval and merge of Suite CI bootstrap PR #420, followed by PumpResult beta/final package publication

## Validation

- Commands run: baseline `[PumpResults]` passed 129 assertions in 11 cases; refactored `[pump_result]` passed 129 assertions in 11 cases; moved `[EstimateFLA]` passed 64 assertions; the full native suite passed 4,148 assertions in 317 cases; `npm run verify:types` passed; `npm run verify:wasm` rebuilt and staged the composed-input module and passed all 251 browser tests; `npm run check:docs` passed; Doxygen generated the Pump Result page without module-specific warnings; `git diff --check` passed. Against the exact locally packed Suite artifact, the develop-based Desktop branch passed its Angular application typecheck, all three focused PumpResult wrapper tests, and the root build.
- Commands still needed: final generated-document visual review; repeat Desktop checks against exact beta and final packages after Suite CI bootstrap PR #420 merges.
- Known environment limits: Doxygen reports pre-existing repository warnings and cannot run BibTeX in this environment. Browser security policy prevented opening the generated local HTML page, so generated markup was inspected statically. Because clean Desktop `develop` still references the pump-head runtime classes removed from Suite `develop`, local validation used declaration-only compatibility shims for those uncalled pump-head methods; the shims were confined to the temporary packed dependency and were not added to either branch.

## Open Questions Or Blockers

- Exact beta/final package identifiers remain pending. Merge Suite CI bootstrap PR #420 first, then publish and validate the PumpResult beta before either implementation PR is made ready for review.
