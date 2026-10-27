# Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: Suite implementation and local downstream validation complete; PR/package coordination in progress
- Owner: Codex
- Created: 2026-10-05
- Last updated: 2026-10-13
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
- Executable formula provenance: existing implementation and regression fixtures; the exact historical source of the
  two retained compatibility values is not recorded.
- Documentation provenance: the teaching-oriented algorithm narrative cites the DOE PSAT2008 user manual for the
  measurement configurations and loss-coefficient treatment, DOE's July/August 2000 Energy Matters newsletter for
  the conventional 2.31 ft/psi pressure-head derivation, and NBS Miscellaneous Publication 286 for U.S. customary
  volume relationships.
- Legacy-factor decision: preserve 448.8311693 gpm/cfs and 0.432750001 psi/ft in the Suite. The former is the
  established rounded form of the unit-derived 448.831168831... gpm/cfs conversion. The latter implies a reference
  water specific weight of 62.316000144 lb-force/ft^3; its exact historical source and precision remain unverified.
  No conversion responsibility moves to Desktop, so no Desktop issue update is required for this documentation work.
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
- PR review follow-up: added a shared `1e-9 ft` absolute tolerance to native golden assertions, clarified the flow-conversion factor as gpm per cfs, and rewrote pipe area as `pi * diameter^2 / 4`. Focused native, full native, fresh WASM, Doxygen, documentation-link, and whitespace checks passed after these changes.
- Teaching-document enhancement: reorganized the pump-head algorithm page around the physical energy balance,
  measurement selection, sign conventions, formula derivations, loss-coefficient normalization, a golden worked
  example, and typed WebAssembly usage. Focused native tests passed 42 assertions in two test cases;
  `npm run verify:types`, `npm run check:docs`, and `git diff --check` passed. Doxygen generated the updated page with
  no pump-head warnings and resolved the formulas, code block, and implementation references. Bibliography rendering
  remains locally unverified because the existing environment does not provide `bibtex`; Doxygen emitted its known
  missing-`bibtex` diagnostic along with unrelated pre-existing warnings.
- MathJax unit-rendering follow-up: replaced unsupported grouped siunitx expressions with the dimensionally equivalent
  `gal*s/(min*ft^3)` form and composed cubic inches as `in^3`. Regenerated Doxygen and loaded the pump-head page in
  headless Chrome; its post-MathJax DOM contained no `mjx-merror`, undefined-unit messages, or siunitx failures.
- Local Desktop package validation: packed this exact Suite working tree as `measur-tools-suite@1.2.6`, installed it into an isolated Desktop checkout without changing dependency pins, and passed the two focused wrapper tests, Angular application TypeScript checking, and the root application build.
- Known environment limits: `clang-format` is not installed; C++ formatting was checked manually. Doxygen cannot produce bibliography output without `bibtex`.
- Commands still needed: repeat Desktop validation against the exact published beta, then update both Desktop pins/lockfiles and repeat against the approved final package.

## Open Questions Or Blockers

- No implementation decisions remain. Package beta/final identifiers will be recorded when produced by the release workflow.

## Issue 200 Engineering Review 2026-10-13

Implemented the eight suggestions from the engineer's pump-head Doxygen review in Suite only.
This documentation update preserves the current public API, executable formulas, and all stored constants.

| Review item | Disposition | Implementation |
| --- | --- | --- |
| 1. Unit exponents | Accepted | Compose units from base foot/inch units with explicit squared or cubed powers; no shared renderer changes. |
| 2. Worked-example total | Accepted | Use HTML bold markup in all three total-row cells and bold mathematical notation for the pump-head symbol. |
| 3. Water density and specific weight | Adapted | Explain approximate mass density near 68 degrees Fahrenheit in lbm/ft^3 and cite NBS Circular 19, Table 34; retain gamma as specific weight in lbf/ft^3 and explain numerical equality under standard gravity. |
| 4. Negative elevation head | Accepted | Describe the lower discharge-gauge measurement correction and its offset of the pressure-head contribution. |
| 5. Gauge elevation reference | Adapted | Use the gauge center and a common datum; require the elevation to match the supplied pressure reading, including any corrected reference. PSAT is cited for the common datum, not for the added center-of-gauge clarification. |
| 6. Reference-water pressure factor | Adapted | Cite the Hydraulic Institute explanation of head and pressure and NBS water tables; distinguish the 2.31 ft/psi approximation from the exact stored factor and avoid unsupported historical attribution. Qualify centrifugal-pump density independence by flow, speed, impeller geometry, comparable viscosity, and absence of cavitation. |
| 7. Pipe size at measurement | Accepted | State that each gauge's entered inside diameter applies at the pressure-measurement location; preserve the tank fluid-surface reference and suction-loss reference diameter. |
| 8. Terminology | Accepted | Use pump head consistently in the algorithm narrative, C++ API comments, and TypeScript declaration comments; retain all identifiers. |

### Supporting Sources

- [PSAT2008 user manual](https://www.energy.gov/sites/default/files/2014/04/f15/psat_user_manual.pdf): common elevation datum, measurement pipe sizes, and normalized loss coefficients.
- [NBS Circular 19, Sixth Edition, Table 34](https://nvlpubs.nist.gov/nistpubs/Legacy/circ/nbscircular19e6.pdf): approximate water properties near 68 degrees Fahrenheit.
- [Hydraulic Institute System Curves](https://datatool.pumps.org/pump-fundamentals/sys-curves): head as energy per unit weight and pressure/specific-gravity relationship.

### Validation

- Configured and built the native cpp_tests target; focused [pump_head] tests passed 42 assertions in two cases, including all five worked-example components and the 100.3959322495 ft total.
- npm run verify:wasm rebuilt and staged the module, passed TypeScript checking, and passed all 251 browser tests. The initial sandbox attempt could not write an Emscripten cache lock; the authorized rerun passed.
- Doxygen regenerated successfully with a temporary TeX Live BibTeX executable downloaded into /private/tmp. Existing unrelated configuration and undocumented-parameter warnings remain; no warnings were emitted for the changed pump-head files or new citations.
- Headless Chrome inspection found no JavaScript errors, MathJax errors, nested unit powers, or unresolved citation keys. Inspected the pressure, velocity, reference-property, and worked-example sections visually; verified all three total-row cells are bold and bibliography URLs are clickable.
- Compared stripped C++ and TypeScript comments against HEAD: all non-comment content is unchanged. All ten labeled algorithm equations are unchanged.
- npm run check:docs and git diff --check passed.

### Desktop Follow-up

Align the Pump Head Tool help with the Suite gauge-center/common-datum definition, corrected pressure-reference qualification, and pipe-size-at-measurement assumption. Track this separately under Suite issue 200 and the existing [Desktop coordination issue 8941](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8941).
No Desktop changes or GitHub messages were made for this review update; no new API migration is needed.
