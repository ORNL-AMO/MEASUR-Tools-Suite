# FluidPower Refactor Handoff

## Workflow Metadata

- Lifecycle: completed
- Status: Implemented, verified and independently reviewed; Ready at 9d5e46c.
- Owner: Codex
- Created / last updated: 2026-10-15
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/220
- Branch / intended PR base: `issue-220` / `epic-pump-result-refactor`
- Base commit: `1998e82434604ccf066cb4257e3db2dbc53f25e8` (OptimalMotorPower PR #433 merged).
- Suite PR: pending; no publication requested.
- Desktop coordination: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Held Desktop PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964

## Target And Persona Sequence

- Logical module: `motorDriven/pumpFan/fluid_power`.
- Replace header-only `FluidPower.h` and its native test with one snake_case header/source/test set.
  Add matching binding/declaration, typed `motorDriven/pumpFan/wasm_fluid_power.test.ts`, and teaching `.dox` page.
- No standalone legacy binding, declaration, WASM test or calculation `.dox` page exists to remove.
- Patterns: `compressedAir/dryer_operating_cost` and adjacent `motor/optimal_motor_power`.
- Refactor Planner: approved contract below; C++, runtime and documentation phases complete.
- C++ Namespace Refactorer: header/source, consumer migration, Doxygen API comments and tests implemented.
- WebAssembly TypeScript Steward: value-object bindings, declarations, entrypoint/module exports and typed tests implemented.
- Algorithm Docs Author: final-result-first teaching page, five formulas/symbol tables, both worked examples,
  retained pressure convention, units, provenance and interpretation limits implemented.
- Verification Reviewer: cross-layer API, units, ownership, formulas and integrated validation checked;
  independent pre-PR review complete, Ready with no actionable findings.

## API And Compatibility Contract

| Surface | Before | After | Kind / units / defaults | Ownership / compatibility |
| --- | --- | --- | --- | --- |
| C++ pump | `FluidPower(SG, Q, H).calculate()` | `fluid_power::calculatePump(const PumpInput&) -> double` | Required aggregate SG (dimensionless), Q (US gpm), H (ft); result kW | Plain values; breaking, no wrapper |
| C++ fan | `FluidPower(Q, pi, po, K, pv).calculate()` | `fluid_power::calculateFan(const FanInput&) -> double` | Required Q (cfm), pi/po (in. water gauge), K (dimensionless), pv (in. water); result kW | Plain values; breaking, no wrapper |
| Standalone WASM | None | `calculatePumpFluidPower(PumpFluidPowerInput)` and `calculateFanFluidPower(FanFluidPowerInput)` | Functions plus input value objects; numeric kW returns | Plain objects/scalars, no cleanup; additive |
| Direct C++ consumers | Constructor/calculate calls | Namespace calls in MoverEfficiency and OptimalPumpShaftPower | Retain their public APIs, conversion order and results | Existing consumer ownership preserved |

- User explicitly approved full stateless API, class/header removal and separate pump/fan functions in planning,
  then requested implementation on 2026-10-15. No calculation-behavior change approved.
- Pump fields in order: `specific_gravity`, `flow_rate`, `head`.
- Fan fields in order: `flow_rate`, `inlet_pressure`, `outlet_pressure`, `compressibility_factor`, `velocity_pressure`.
- WASM fields use camelCase. All fields required, including velocityPressure; no defaults or result objects.
- Module type exposes only two runtime functions; input interfaces are type-only.
- Remove the old class/header/test instead of retaining compatibility support.

## Formulas, Units And Documentation

- Engineering question: how much power is delivered to the fluid at the supplied pump or fan duty?
- Pump kW: `0.746 * Q * H * SG / 3961.38`.
- Fan kW: `0.746 * Q * (po - pi - pv) * K / 6362`.
- Preserve constants, multiplication/subtraction/division order and signed/nonfinite arithmetic.
  Use existing `physics::conversions::kBhpToKw` (exactly 0.746); divisors remain private named constants.
- No validation, clamping, defaulting, efficiency adjustment or unit conversion is added.
- Retain six original native goldens: pump 53.7836814443 and 64.5404177332 kW;
  fan 1.6416221314, 1.9699465577, 262.3349690747 and 198.5721824055 kW.
- Teach final fluid-power interpretation first, selection/units, supporting relationships and retained constants,
  pump and fan worked examples, velocity-pressure subtraction, signed results, assumptions and limits.
- Provenance: unchanged legacy header at the base commit and captured numerical results; historical provenance
  of the exact divisors is unverified. No SME decision is required for behavior preservation.

## Desktop And Release Boundaries

- Classification: breaking C++ API and additive WASM API; no intended numerical behavior change.
- Read-only planning inspection found no direct legacy FluidPower Suite consumer in Desktop wrappers,
  process-flow source or installed declarations. Desktop has independent curve fluid-power formulas;
  changing those is outside scope. Indirect assessment results must retain their goldens.
- No Desktop code/tests, dependency pins, loading paths or held PR updates in this child.
- Final Desktop migration and verification are deferred until the complete Suite epic is approved.
- Package versions: pending verified publication; no version bump or publication in this implementation.

## Validation

- Commands run: baseline native configure/build passed; original FluidPower test passed six assertions.
  Captured 23 finite results from the unchanged header compiled at -O3 before removing it.
- Refactored native configure/build passed. Focused fluid-power/mover/pump/fan tests passed 259 assertions
  in 19 cases; full native suite passed 5,061 assertions in 337 cases.
- Temporary -O3 differential harness compared 373,490 pump/fan combinations with the unchanged archived
  legacy header. All non-NaN values matched bit-for-bit, including signed zero/infinity; NaN classifications matched.
- `npm run verify:types` passed. `npm run verify:wasm` rebuilt/staged client.js and client.wasm,
  typechecked and passed all 276 browser tests, including the three new typed FluidPower tests.
- `npm run check:docs`, `git diff --check` and npm package dry-run content inspection passed.
  The package contains both runtime assets, the declaration entrypoint and new declaration module;
  the removed legacy header is absent.
- Doxygen generated the FluidPower page without module-specific warnings. Localhost browser inspection
  confirmed both worked examples, all five equations and their symbol/unit tables. All 65 MathJax containers
  rendered without math errors; the page console had no errors. Visual QA caught unformatted unit strings
  in symbol tables; these were replaced with existing unit macros and the generated page was rechecked.
- Header-comment and native-test layout updates were followed by a native rebuild and focused rerun:
  259 assertions in 19 cases passed again. No runtime implementation changed after full native/fresh-WASM validation.
- Environment limits: initial WASM verification hit Emscripten-cache sandbox restrictions; an approved rerun passed.
  npm package inspection and the local documentation server likewise required approved cache/socket access.
  Full Doxygen generation retains the pre-existing missing-BibTeX error despite emitting the inspected page.
- Still needed for this implementation: none. Final integrated Suite review and the consolidated Desktop
  verification/release cycle remain epic-level work.

## Internal Review

- Intended PR base / reviewed base: `epic-pump-result-refactor` at `1998e82434604ccf066cb4257e3db2dbc53f25e8`.
- Reviewed head: `9d5e46c77b8e9f18b8eae5b8d09ede672eb1bb30`.
- Independent reviewer: `fluid_power_review`, using `.github/skills/measur-code-review/` in a separate context.
- Readiness: Ready; no actionable findings and no unresolved P0-P2 findings. No review fixes required.
- Reviewer independently reran 239 focused native assertions in 18 cases, all 373,490 differential comparisons,
  declaration verification, documentation-link and diff-whitespace checks; all passed. The archived legacy header
  hash matches the base commit. Reviewer inspected recorded full-native/fresh-WASM evidence and package contents.
- No checks rerun for review fixes because none were required. Subsequent handoff-only evidence updates do not
  materially change the reviewed implementation.
- Remaining P3 findings, questions or module-specific validation gaps: none. The pre-existing full-documentation
  BibTeX limitation remains documented above.

## Open Questions Or Blockers

- No unresolved implementation or review blockers. Desktop verification remains deferred to final epic integration.
- No push, PR opening or package publication was performed. When PR delivery is requested, target the epic branch
  and record post-push CI/publication evidence in the PR without publication-evidence-only follow-up pushes.
