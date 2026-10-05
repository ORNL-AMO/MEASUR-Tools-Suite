# Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: Suite implementation and local downstream validation complete; PR/package coordination in progress
- Owner: Codex
- Created: 2026-10-05
- Last updated: 2026-10-05
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/200
- Suite PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/418
- Desktop issue: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8941
- Desktop PR: pending

## Target Module

- Domain/path: `motorDriven/pump`
- Logical module: pump head calculator
- Legacy files: `HeadTool.h/.cpp`, head-tool sections in `pump.cpp` and `pump.d.ts`, one C++ test, and two WASM tests
- Nearby examples: `compressedAir/dryer_operating_cost` stateless value-object calculator

## Current Public API

- C++ symbols: global `HeadToolBase`, `HeadTool`, `HeadToolSuctionTank`, and `HeadToolBase::Output`
- Embind runtime names: `HeadTool`, `HeadToolSuctionTank`, and `HeadToolOutput`
- TypeScript declarations: runtime classes in `motorDriven/pump/pump.d.ts`
- Test-visible behavior: constructor-based gauge and suction-tank calculations returning an embind class that requires `delete()`

## Runtime API Contract

| Surface | Before | After | Embind kind | Units/defaults | Ownership and cleanup | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| Suction-gauge calculation | `new HeadTool(...).calculate()` | `calculatePumpHeadFromSuctionGauge(input)` | `class_` to `function` + `value_object` | SG dimensionless; flow gpm; diameters in; pressures psig; elevations/head ft; loss coefficients dimensionless | Before: calculator and result require `delete()`; after: plain input/result, no cleanup | Breaking |
| Suction-tank calculation | `new HeadToolSuctionTank(...).calculate()` | `calculatePumpHeadFromSuctionTank(input)` | `class_` to `function` + `value_object` | SG dimensionless; flow gpm; diameters in; pressures psig; elevations/head ft; loss coefficients dimensionless | Before: calculator and result require `delete()`; after: plain input/result, no cleanup | Breaking |
| Shared result | `HeadToolOutput` runtime class | `PumpHeadResult` plain object | `class_` to `value_object` | All six properties are head in ft | No `delete()` after refactor | Breaking |

## Proposed Namespace API

- Namespace: `pump_head`
- Functions: `calculateFromSuctionGauge(const SuctionGaugeInput&)` and `calculateFromSuctionTank(const SuctionTankInput&)`
- Structs/value objects: `SuctionGaugeInput`, `SuctionTankInput`, and `Result`
- Enums: none
- Runtime names to preserve: existing result property names only

## Compatibility Decision

- Default: preserve public compatibility.
- Decision: intentionally breaking cleanup approved by the user on 2026-10-05.
- Migration notes needed: replace constructors and instance `calculate()` calls with typed plain-object function calls; remove all related `delete()` calls.
- User approval for breaking changes: explicit in the implementation request.
- Removed legacy surfaces: PascalCase header/source, three runtime classes, class declarations, constructor tests, and compatibility wrappers.
- Behavior change approved: none; formulas and results must remain unchanged.

## Touched Layers

- Headers/source: replace `HeadTool.h/.cpp` with `pump_head.h/.cpp`
- C++ tests: replace `HeadTool.unit.cpp` with `pump_head.unit.cpp`
- WebAssembly bindings: move pump-head bindings from `pump.cpp` to `pump_head.cpp`
- TypeScript declarations: move pump-head types from `pump.d.ts` to `pump_head.d.ts`; update `client.d.ts`
- WASM Mocha tests: replace two legacy constructor tests with one typed function test
- Algorithm docs: add `docs/dox-content/calculators/motorDriven/pump/pump_head_calculator.dox`

## Desktop Impact

- Wrapper or helper changes: migrate `PumpsSuiteApiService` internals; retain app-facing wrapper method names.
- Enum, unit, percentage, or nullable conversion changes: none.
- App models, reports, exports, or saved-data changes: none.
- Process-flow package changes: dependency pin only; no direct consumer.
- Web/Electron WASM loading changes: none planned.
- Downstream verification: focused wrapper test, Angular typecheck, and root app build against the exact beta/final packages.

## Formulas And Units

- Final result formula: `H_p = H_z + H_p,pressure + Delta H_v + H_f,s + H_f,d`, units ft.
- Supporting formulas: `Q = q/448.8311693`, `v = Q/(pi D^2/4)`, `H_v = v^2/(2g)`, pressure head from pressure difference divided by `0.432750001 * SG`, and friction head `K * H_v`.
- Constants: pi; `g = 32.174 ft/s^2`; `12 in/ft`; `448.8311693 gpm/(ft^3/s)`; and `0.432750001 psi/ft` at SG 1. All are referenced from `physics/constants.h`.
- Units: gpm, inches, psig, ft, ft/s, ft/s^2, and dimensionless coefficients/SG.
- Formula provenance: existing implementation and regression fixtures; no external reference is currently recorded.
- Golden inputs and expected results: gauge fixture `100.3959322495 ft`; suction-tank fixture `22.9728655518 ft`.
- SME decisions required: none for this behavior-preserving refactor.
- Unclear or unverified items: physical provenance of the two legacy conversion factors is not recorded; retain exact values.

## Package And Release Coordination

- Change classification: breaking API
- Beta package version: pending Suite PR workflow
- Final package version: pending release approval
- Desktop root dependency: currently `1.2.5`; update to exact beta/final version
- Desktop process-flow dependency: currently `1.2.5`; keep aligned with root
- Release readiness: Suite and local Desktop implementation validated; exact beta/final package validation remains pending
- Release blockers: beta/final publication requires the normal PR and release workflow

## Validation

- Baseline: pre-refactor focused C++ test passed, 41 assertions in one test case.
- Native validation: configured and built `build-cpp`; refactored `[pump_head]` tests passed 42 assertions in two test cases, including a new specific-gravity regression; full suite passed 4,148 assertions in 317 test cases.
- WebAssembly and declarations: `npm run verify:types` passed; `npm run verify:wasm` passed after activating the local Emscripten SDK, including all 251 browser tests and all three typed pump-head tests.
- Documentation and hygiene: Doxygen completed with pre-existing configuration/undocumented-parameter warnings and a missing local `bibtex` executable; the new pump-head files emitted no warnings. `npm run check:docs` and `git diff --check` passed.
- Local Desktop package validation: packed this exact Suite working tree as `measur-tools-suite@1.2.6`, installed it into an isolated Desktop checkout without changing dependency pins, and passed the two focused wrapper tests, Angular application TypeScript checking, and the root application build.
- Known environment limits: `clang-format` is not installed; C++ formatting was checked manually. Doxygen cannot produce bibliography output without `bibtex`.
- Commands still needed: repeat Desktop validation against the exact published beta, then update both Desktop pins/lockfiles and repeat against the approved final package.

## Open Questions Or Blockers

- No implementation decisions remain. Package beta/final identifiers will be recorded when produced by the release workflow.
