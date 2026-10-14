# MotorPower Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: C++, WebAssembly TypeScript, and Algorithm Docs Author phases complete; Verification Reviewer phase active
- Owner: Codex
- Created / last updated: 2026-10-14
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/210
- Suite branch / intended PR base: `codex/motor-power-refactor` / `epic-pump-result-refactor`
- Synced base commit: `4c573f3cd523f3c897aa6f9c87e565d5a271b61e`
- Suite PR: pending
- Desktop coordination: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Held Desktop PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964

## Target Module And Persona Sequence

- Domain / module: `motorDriven/motor` / `motor_power`.
- Replace `MotorPower.h/.cpp` with `motor_power.h/.cpp`; add a dedicated native test.
- Add matching binding/declaration modules and `tests/wasm-mocha/motors/wasm_motor_power.test.ts`.
- Add `docs/dox-content/calculators/motorDriven/motor/motor_power_calculator.dox`.
- Scalar patterns: `motorDriven/motor/poles` and `processHeat/energy_equivalency`.
- Sequence: Refactor Planner, C++ Namespace Refactorer, WebAssembly TypeScript Steward,
  Algorithm Docs Author, Verification Reviewer. Each phase updates this handoff.

## Runtime API Contract

| Surface | Before | After | Embind kind | Units / defaults | Ownership | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| C++ power | `MotorPower(voltage, current, pf).calculate()` | `motor_power::calculate(rated_voltage, motor_current, power_factor)` | None | V, A, fractional PF; returns kW; no defaults | Scalar | Breaking C++ |
| WASM power | No direct export | `calculateMotorPower(ratedVoltage, motorCurrent, powerFactor)` | Function | Same required inputs and kW result | Scalar; no cleanup | Additive |

## API And Compatibility

- C++ returns `double`; TypeScript returns `number`; no input/result structs or runtime constructors.
- User explicitly approved removal of the legacy C++ API and addition of the three-argument WASM function
  during planning and requested implementation on 2026-10-14.
- Remove the class/header/source without compatibility wrappers. No numerical change is approved.
- Migration: include `motorDriven/motor/motor_power.h` and replace constructor/method calls with
  `motor_power::calculate(voltage, current, power_factor)`.
- Update three MotorShaftPower calls and one OptimalMotorPower call privately; preserve consumer APIs.

## Desktop Impact

- No existing direct MotorPower runtime surface or consumer; local Suite adapter and process-flow searches
  found only related power fields and MotorPowerFactor usage.
- Indirect pump/fan consumers retain their numerical results and saved-data shapes.
- No wrapper, enum/percentage mapping, package-pin, model, default-data, or WASM-loading change here.
- Desktop source and held PR #8964 remain deferred to final integrated Suite migration.

## Formulas And Units

- Engineering question: calculate three-phase motor real electrical input power from voltage, current, and PF.
- Formula: `rated_voltage * motor_current * sqrt(3) * power_factor / 1000`, in the retained evaluation order.
- Voltage is RMS line-to-line V; current is RMS line A; PF is dimensionless fraction; output is kW, not hp.
- The historic header incorrectly stated hp; correcting that comment does not change the calculation.
- Use balanced sinusoidal three-phase conditions and a PF appropriate to the operating point; explain limits
  for phase imbalance, distorted waveforms, and nameplate values that differ from operating measurements.
- Physical input domain: nonnegative voltage/current and PF 0..1 for consuming motors. No validation,
  clamps, defaults, efficiency adjustment, or horsepower conversion is added; retain signed/out-of-range arithmetic.
- Constants: exact `sqrt(3)` for the three-phase relationship and 1000 W/kW.
- Provenance: legacy source at synced base; DOE sourcebook printed p. 42 (`doe2008motorSourcebook`) supports
  the three-phase relationship using rounded 1.732; retain exact square root and avoid copying its unit typos.
- Worked example: 460 V, 100 A, PF 0.85 -> 67.72318657594309 kW.
- Legacy capture: compiled unchanged MotorPower.cpp before removal; 12 fixtures cover 230/400/460/2300 V,
  representative currents, PF 0/0.75/0.85/0.9/0.92/1, zero voltage/current, each negative argument, and PF 1.2.
- No SME decision or unresolved formula/unit question.

## Package And Release Coordination

- Classification: breaking C++ source API; additive WASM/TypeScript API; behavior preserved.
- Beta: pending ready child PR CI; final package: integrated epic release. No local version bump.
- Keep runtime/package paths unchanged; verify freshly built/staged JS/WASM and packaged declarations.
- No individual MotorPower Desktop package-pin update or beta validation; final integration uses aligned pins.

## Validation

- Develop sync: native configure/build, focused pump-head/pump/fan tests (194 assertions / 15 cases),
  `npm run verify:types`, `npm run check:docs`, merge whitespace check passed. Bibliography entries preserved.
- Legacy native fixture capture passed before replacing MotorPower.
- C++ phase: replaced the class with the namespace API and migrated all four consumers. Initial native
  build found an incorrect Catch2 include; corrected it to the repository's bundled `catch.hpp`.
  Corrected native rebuild and focused/full verification results are recorded below.
- Focused power/pump/fan tests passed 164 assertions in 14 cases; full native suite passed
  4,326 assertions in 325 cases; `npm run verify:types` passed with the new module and typed browser test.
- WASM/TypeScript phase adds one scalar binding, dedicated declarations, package-root/module exports,
  and 12 legacy fixtures in a typed browser test. No legacy runtime constructor existed to remove.
- Algorithm Docs Author completed the engineering page, symbol tables, 460 V worked example,
  DOE citation, physical limits, fractional-PF interpretation, and C++/TypeScript examples.
- Fresh `npm run verify:wasm` rebuilt/staged the current JS/WASM, typechecked, and passed all 262
  browser tests. The restricted attempt hit an SDK cache-lock permission error; the approved rerun passed.
- `npm run check:docs`, Doxygen generation, package dry run, and whitespace checks passed.
  The package includes staged `bin/client.js`, `bin/client.wasm`, the entrypoint, and new declarations.
- Local Doxygen emits existing unrelated warnings. With doc-error warnings enabled, the DOE citation
  has no associated number on MotorPower and the pre-existing MotorEfficiency/Poles pages even with the
  temporary BibTeX binary available; the shared citation key and bibliography source are correct. The
  new page also links directly to the sourcebook page. Bibliography numbering remains a local tooling gap.
- Browser security review blocked the generated local `file:` URL. No workaround was attempted;
  visual/MathJax inspection is unavailable. Generated HTML sections, example, API, and local links are
  checked directly. Report this remaining visual-validation gap accurately.
- Remaining: focused/new and consumer native tests, full native suite, fresh `npm run verify:wasm`,
  declarations, docs links/Doxygen/rendered page, package dry run, whitespace, and independent pre-PR review.

## Internal Review

- Intended base: synced epic commit above.
- Reviewed head / reviewer / readiness / findings: pending implementation and verification.
- No PR opens with unresolved P0-P2 findings. Record dispositions and rerun affected checks after fixes.

## Open Questions Or Blockers

- None for implementation. Desktop integration and final release remain intentionally deferred.
