# OptimalMotorPower Refactor Handoff

## Workflow Metadata

- Lifecycle: completed
- Status: Implemented, verified and independently reviewed; Ready at 5cb2284; PR delivery requested.
- Owner: Codex
- Created / last updated: 2026-10-15
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/213
- Branch / intended PR base: `issue-213` / `epic-pump-result-refactor`
- Base commit: `80c647502f2ad18f960f9208570d5c890ba58afd` (MotorShaftPower PR #432 merged).
- Suite PR: [branch PR and CI/publication evidence](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pulls?q=is%3Apr+head%3Aissue-213) will be maintained in the PR description and CI comments.
- Desktop coordination: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Held Desktop PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964

## Target And Persona Sequence

- Logical module: `motorDriven/motor/optimal_motor_power`.
- Replaced `OptimalMotorPower.h/.cpp` with one snake_case header/source pair. Added matching binding,
  declaration, native test, typed `motors/wasm_optimal_motor_power.test.ts`, and teaching `.dox` page.
- No legacy standalone binding, declaration or dedicated test existed to remove.
- Patterns: `compressedAir/dryer_operating_cost` and adjacent `motor_shaft_power`.
- Refactor Planner: approved full stateless contract and behavior-preservation scope.
- C++ Namespace Refactorer: namespace implementation, public API comments, consumer migration and native tests complete.
- WebAssembly TypeScript Steward: value-object binding, declarations, package exports and typed browser tests complete.
- Algorithm Docs Author: final-result-first teaching page, seven formulas/symbol tables, worked example and limits complete.
- Verification Reviewer: cross-layer API, ownership, units, formulas and validation evidence checked; independent review complete.

## API And Compatibility Contract

| Surface | Before | After | Kind / units / defaults | Ownership / compatibility |
| --- | --- | --- | --- | --- |
| C++ calculator | Global class, eight-argument constructor, calculate(), getter/setter, nested Output | `optimal_motor_power::calculate(const Input&) -> Result` | Required aggregate inputs; hp, rpm, V, efficiency fraction and existing Motor enums; no defaults | Plain values; breaking, no wrappers |
| Standalone WASM | None | `calculateOptimalMotorPower(OptimalMotorPowerInput) -> OptimalMotorPowerResult` | Function plus input/result value objects; electrical kW, current A, fractional efficiency/PF/load | Plain objects, no cleanup; additive |
| PumpResult and FanResult | Private constructor/calculate calls | Private namespace function calls | Public runtime fields, units and numerical outputs preserved | Existing consumer ownership preserved |

- User explicitly approved class/header removal and the full stateless WASM/TypeScript API in planning,
  then requested implementation on 2026-10-15. No calculation-behavior change approved.
- Input order: `motor_rated_power`, `motor_rpm`, `line_frequency`, `efficiency_class`, `specified_efficiency`,
  `rated_voltage`, `field_voltage`, `optimal_motor_shaft_power`.
- Results: `power`, `efficiency`, `current`, `power_factor`, `load_factor`.
- WASM fields are camelCase, including `motorRpm`. Interfaces are type-only; the module contributes only the function.
- Migration: replace constructor/calculate with a complete aggregate input on each call. Replace result
  powerFactor/loadFactor with power_factor/load_factor. Getter/setter, old headers/class and nested Output are removed.
- PumpResult and FanResult are the only direct consumers. Their exported fields and existing goldens are unchanged.

## Formulas, Units And Documentation

- Engineering question: what electrical demand corresponds to a supplied motor shaft-power requirement?
  This does not choose motor size or optimize equipment; drive/mover losses inform the requirement upstream.
- Target shaft kW: supplied hp times `physics::conversions::kBhpToKw` (exactly 0.746).
- At trial load, evaluate raw optimal current, field-voltage current correction, efficiency, power factor,
  electrical kW and shaft kW in the legacy order. Start at zero; retain accumulated 0.01 additions,
  strict shaft-power exceedance and load > 1.5 termination, initial zero anchors and extrapolation.
- Interpolate load and electrical quantities with retained arithmetic; scale final current by 460/rated V
  and recompute power factor. No new validation, defaults, clamping or error translation.
- Private named OperatingPoint, trial evaluation and interpolation helpers keep algorithm steps explicit.
- Units: shaft/nameplate hp, electrical kW, rpm, V, A and dimensionless efficiency/PF/load fractions.
- Worked example: 100 hp, 1780 rpm, 60 Hz, ENERGY_EFFICIENT, specified 0.93 (inactive), 460 V rated/field,
  target 75 hp: 58.8307085111 kW, efficiency 0.95103393136, current 87.4684109871 A,
  power factor 0.84417868597, load 0.7500000000000001. Target mechanical output is 55.95 kW.
- Provenance: unchanged source at base commit plus native captures; historical empirical curve/voltage
  provenance remains unverified. No engineering-policy or SME decision is needed for preservation.
- Boundary documentation includes no-load demand, negative target/zero-voltage nonfinite arithmetic,
  SPECIFIED dependency exceptions, PREMIUM pole limits and search-limit versus operating-rating distinction.

## Desktop And Release Boundaries

- Classification: breaking C++ API and additive WASM API; no intended numerical behavior change.
- Read-only search of local Desktop source, installed declarations and process-flow found no direct
  OptimalMotorPower consumer. Impact remains indirect through modified pump/fan results.
- Desktop coordination issue #8957 inspected. Desktop wrappers/tests, root/process-flow pins and held PR #8964
  remain deferred to final epic integration. No Desktop code, package pins or loading paths changed.
- Beta and final versions: pending verified publication; no package version bump or publication performed here.
- Public refactors of OptimalMotorShaftPower, MotorPerformance, FanResult and other calculators are outside scope.

## Validation And Internal Review

- Reconfigured/rebuilt native dependencies before captures. A temporary harness compiled an unchanged copy
  of the legacy calculator at base with -O3, preserving its original class behavior under a renamed private symbol.
- Captured 69 complete five-output cases, now durable in both native and typed browser test files.
  Covers 50/60 Hz, four efficiency classes, 2/4/6 poles, 5-600 hp, equal/unequal voltages,
  light/full/overload and beyond-limit targets, exact/adjacent trial thresholds, zero/negative targets and zero voltages.
- Native tests also check all input fields, repeated/interleaved calls, inactive specified efficiency and dependency errors.
- Temporary differential harness compared 9,504 cases against the unchanged -O3 legacy calculator:
  every non-NaN field matched bit-for-bit, including signed zero/infinity; NaN classifications matched.
- `cmake -S . -B build-cpp` and `cmake --build build-cpp -j 4` passed.
- Focused optimal/pump/fan tests passed 508 assertions in 16 cases. Full native suite passed 5,031 assertions in 335 cases.
- `npm run verify:types` passed. `npm run verify:wasm` rebuilt/staged client.js and client.wasm,
  typechecked and passed all 273 browser tests, including plain-object runtime ownership and 69 legacy fixtures.
- `npm run check:docs`, `git diff --check` and npm package dry-run content inspection passed.
  Package includes both runtime assets, declaration entrypoint and new declaration module.
- Doxygen generated the new page without module-specific warnings; localhost browser inspection confirmed
  rendered equations, units/symbol tables and worked example. All 85 MathJax containers rendered without math errors;
  page console contained no errors. Full generation retains the pre-existing missing-BibTeX error.
- Environment limits: initial optimized temporary-harness compile/run attempts exited 137; compiling the harness
  without optimization and the legacy calculation separately at -O3 succeeded. Initial WASM/cache, npm cache and local
  server port attempts hit sandbox restrictions; approved reruns succeeded.
- Intended base / reviewed base: `epic-pump-result-refactor` at `80c647502f2ad18f960f9208570d5c890ba58afd`.
- Reviewed head: `5cb2284bbaaaaade32a6048bf7d2ff3ba50846fa`.
- Independent reviewer: `optimal_motor_review`, using `.github/skills/measur-code-review/` in a separate context.
- Readiness: Ready; no actionable findings and no unresolved P0-P2 findings. No review fixes required.
- Reviewer independently reran focused native tests (356 assertions in 3 cases), declaration verification
  and full-diff whitespace checks; all passed. Reviewed recorded full-native/fresh-WASM/differential/package/rendered-doc
  evidence and reinspected Suite #213 and Desktop #8957. Subsequent handoff-only evidence changes do not alter implementation.

## Open Questions Or Blockers

- No unresolved implementation or review blockers. Desktop verification is intentionally deferred to final integration.
- User requested PR delivery on 2026-10-15. Push the reviewed branch and open against the epic; record
  post-push CI and any exact published beta in the linked PR, without publication-evidence-only follow-up pushes.
  No beta or final package publication is claimed by local validation.
