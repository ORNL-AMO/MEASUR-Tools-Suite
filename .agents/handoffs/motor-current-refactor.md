# MotorCurrent Refactor Handoff

## Workflow Metadata

- Lifecycle: completed
- Status: Suite implementation, validation, and pre-PR review complete; PR #426 open for CI/human review
- Owner: Codex
- Created / last updated: 2026-10-13
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/206
- Suite branch / intended PR base: `issue-206` / `epic-pump-result-refactor`
- Base commit: `363c011d6014f817e937a0b451cf645f5a52f541` (EstimateFLA PR #425 merged)
- Suite PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/426
- Desktop coordination: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Held Desktop PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964

## Target Module And Persona Sequence

- Domain / module: `motorDriven/motor` / `motor_current`.
- Replace `MotorCurrent.h/.cpp` with `motor_current.h/.cpp`; rename the matching native test.
- Extract the mixed `motor.cpp` binding and `motor.d.ts` declaration into dedicated module files.
- Add `tests/wasm-mocha/motors/wasm_motor_current.test.ts` and a motor calculator `.dox` page.
- Canonical value-object example: `compressedAir/dryer_operating_cost`; adjacent dependency: `estimate_fla`.
- Sequence: Refactor Planner, C++ Namespace Refactorer, WebAssembly TypeScript Steward,
  Algorithm Docs Author, Verification Reviewer. Each phase updates this handoff.

## Runtime API Contract

| Surface | Before | After | Embind kind | Units / defaults | Ownership | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| Motor/load input | Seven constructor arguments | `motor_current::Input` / `MotorCurrentInput` | `value_object` | hp, rpm, existing enums, efficiency/load fractions, V; all required | Plain value; no cleanup | Breaking |
| Existing current | `MotorCurrent(...).calculateCurrent(fla)`; C++ getter for estimated FLA | `motor_current::calculate(input, fla)` / `calculateMotorCurrent(input, fullLoadAmps)` | Function + `MotorCurrentOutput` value object | `current`, `estimated_fla` / `estimatedFLA` in A | Plain result; no `delete()` | Breaking; estimated FLA newly available in WASM |
| Optimal current | C++ `calculateOptimalCurrent()` only | `motor_current::calculateOptimal(input)` / `calculateOptimalMotorCurrent(input)` | Function returning number | A | Scalar; no cleanup | Breaking C++; additive WASM |

## Proposed API And Compatibility

- Input order: `motor_rated_power`, `motor_rpm`, `line_frequency`, `efficiency_class`,
  `specified_efficiency`, `load_factor`, `rated_voltage`. Bind camelCase fields, including `motorRpm`.
- Existing-current result contains `current` and `estimated_fla`; optimal returns only a current scalar.
- User explicitly approved the breaking cleanup, exposure of both paths, and shared input plus separate FLA
  argument during planning on 2026-10-13, then requested implementation of the complete plan.
- Remove legacy class/header/source, getter, runtime constructor, declaration, and compatibility wrappers.
- No behavior change approved. Preserve parameter order, enums, formulas, solver, scaling order, and boundaries.
- Migration: replace constructor/method/getter with the namespace function and result fields; WASM callers use
  plain input/result objects and remove MotorCurrent `delete()` calls.
- Migrate MotorShaftPower, OptimalMotorPower, and MotorPerformance privately; retain their public APIs.

## Desktop Impact

- Known direct consumer: `PumpsSuiteApiService.motorCurrent`, which currently constructs MotorCurrent,
  calls `calculateCurrent`, deletes the instance, and returns A.
- Final migration: map the same motor fields into the plain input, pass FLA separately, return `.current`,
  and remove the class import and cleanup. Load percentage remains divided by 100; reuse enum helpers.
- The wrapper currently passes `specifiedEfficiencyPercent` unchanged, while EstimateFLA expects a fraction.
  Record this existing unit mismatch for final integration; do not silently change Suite behavior here.
- No direct process-flow MotorCurrent consumer was found. No saved-data or WASM loading change is planned.
- Desktop source, tests, both dependency pins, and held PR #8964 stay untouched until final integration.

## Formulas And Units

- Engineering question: estimate motor current at a specified fractional load, using supplied FLA or raw model anchors.
- Existing path: scale six EstimateFLA anchors by `460 / rated_voltage`, then by supplied FLA divided by
  the scaled 100% anchor. Return the dependency's independent estimated FLA, not the supplied FLA.
- Optimal path: interpolate raw anchors; field-voltage corrections remain in OptimalMotorPower.
- Interpolation: degree 2 at 0/0.25/0.5 for load < 0.251; degree 4 at 0.25/0.5/0.75/1/1.25 for
  load < 1.251; degree 2 at 0.75/1/1.25 otherwise, capping evaluation above 1.5. No lower clamp.
- Constants: 460 V is model-local; load thresholds and anchor loads are dimensionless.
- Worked example: 100 hp, 1500 rpm, 60 Hz, energy efficient, 460 V, 25% load, supplied FLA 113.8 A.
  Raw anchors: 33.3308239270, 42.7411726195, 63.7477989466, 87.4684109871,
  113.8342622305, 142.4066620504 A. Existing current 42.7283082334 A; optimal current 42.7411726195 A.
- Preconditions: meaningful motor inputs and positive rated voltage; SPECIFIED requires positive efficiency;
  PREMIUM supports 2/4/6 poles. No new validation, fallback, or domain correction.
- Provenance: legacy source at the base commit and native regression fixtures; original empirical source is unverified.
- Golden capture: 29 cases compiled against the freshly rebuilt legacy native library before removing the class.
  Capture includes negative load, every anchor, both strict threshold neighborhoods, cap/exceedance, zero/double
  supplied FLA, 230/400/460/2300 V, 50/60 Hz, both specified baselines, and all supported premium pole columns.
- SME decisions: none needed for behavior preservation.

## Package And Release Coordination

- Classification: breaking API plus newly exposed WASM results/optimal function; no intentional numerical change.
- Beta / final package: pending CI / integrated release; do not invent or change package versions locally.
- Verify rebuilt/staged `bin/client.js` and `bin/client.wasm`; retain existing package file/loading layout.
- Complete all Suite children and integrated review before publishing the approved final/RC package and
  performing one consolidated Desktop migration with aligned root/process-flow pins.

## Validation

- Baseline: native configure/build passed; `[MotorCurrent],[pump_result],[Fan results existing],[Fan results modified]`
  passed 156 assertions in 14 cases. Captured 29 legacy cases before implementation.
- After refactor: native configure/build passed; focused MotorCurrent plus pump/fan consumers passed 253 assertions
  in 16 cases; the full native suite passed 4,314 assertions in 324 cases; `npm run verify:types` passed.
- `npm run verify:wasm` rebuilt/staged current artifacts and passed all 260 browser tests; includes 29 legacy
  cases through both new functions, plain-object/no-constructor checks, and unchanged frozen-input checks.
- Final formatting/test-tolerance changes: native rebuild, focused checks (253 assertions), and full native suite
  (4,314 assertions / 324 cases) passed; focused `[motor_current]` passed 101 assertions in 3 cases.
  Freshly rebuilt/staged `npm run verify:wasm` again passed all 260 browser tests and typechecking.
- `npm run check:docs`, Doxygen generation, and `git diff --check` passed. Doxygen reported its existing
  BibTeX/tooling error and unrelated warnings; no MotorCurrent-specific warning.
- Inspected the generated page in the local browser: equations and units rendered, interpolation/example tables
  displayed, dependency/API links resolved, and worked-example text fit the narrow viewport after splitting the
  substituted polynomial into its linear/quadratic contributions. Corrected Doxygen alias comma escaping in units.
- `npm pack --dry-run --json` confirmed the staged runtime JS/WASM and new/public declarations are included.
- Remaining: child PR CI/human review and the final integrated Suite review after the remaining modules merge.
- Environment: Emscripten SDK located at `/Users/txr/dev/emsdk`; not initially active in the shell.
- Restricted WASM build could not create the SDK cache lock; rerun with approved access passed.
- Restricted package dry run could not write npm's cache; approved rerun passed. Local docs server required
  approved access to bind localhost. Local clang-format is unavailable; formatting matched adjacent modules.

## Internal Review

- Intended base: `epic-pump-result-refactor` at the commit above.
- Reviewed implementation head: `da8f42ac93552245ae3b446fb195718c85857ebe`.
- Reviewer: independent review-only agent `motor_current_review`, following `.github/skills/measur-code-review/`.
- Readiness: Ready. No actionable findings; no unresolved P0-P2 issues.
- Review scope: complete base...head diff; verified scaling order, anchor sets, strict thresholds, cap,
  extrapolation, consumer updates, bindings/types/exports, ownership, tests, and documentation.
- Reviewer independently reran focused `[motor_current]` (101 assertions), motor/pump/fan regressions
  (253 assertions), TypeScript checking, and whitespace checks; all passed.
- Reviewer inspected Suite #206, Desktop coordination #8957, held PR #8964, and the local wrapper.
  Its deferred migration and existing efficiency-unit mismatch agree with the approved delivery policy.
- Reviewer used the recorded full native/WASM/package/visual documentation evidence rather than repeating
  those checks. Existing BibTeX tooling limitation remains; no module-specific documentation defect was found.
- Checks rerun after review fixes: none needed; no code findings or fixes. Subsequent handoff-only changes
  record review evidence and delivery links without altering the reviewed calculation/API.

## Open Questions Or Blockers

- None for implementation. Desktop integration and final release remain intentionally deferred.
