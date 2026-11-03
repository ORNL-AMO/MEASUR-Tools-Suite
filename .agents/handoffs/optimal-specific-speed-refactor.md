# Optimal Specific Speed Refactor Handoff

## Workflow Metadata

- Lifecycle: completed
- Status: implemented, verified and independently reviewed; CI/publication tracked in child PR
- Owner: Codex
- Created / last updated: 2026-11-02
- Suite issue: [#228](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/228)
- Epic: [#230](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/230),
  [epic handoff](pump-efficiency-refactor.md)
- Suite branch: `issue-228`; initial PR base: `issue-225`, the
  [#449 pre-pump efficiency PR](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/449)
- Suite PR: [child PR and CI/publication record](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pulls?q=is%3Apr+head%3Aissue-228+base%3Aissue-225)
- Fixed legacy baseline: `23b58b07e04a16c61d18344a67930ca01d791f7c`
- Desktop issue: [#9059](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/9059)
- Desktop PR: follow-up after Suite stack integration

## Target Module And Touched Layers

Move the pump-only `OptimalSpecificSpeed.h/.cpp` from `motorDriven/pumpFan` to
`motorDriven/pump/optimal_specific_speed.h/.cpp`; remove the legacy class and files.
Migrate its sole production C++ caller in the still-unmigrated `OptimalPumpEfficiency.cpp`.
One matching module now covers each layer:

- C++ header/source: `include/` and `src/motorDriven/pump/optimal_specific_speed`
- Binding: `bindings-wasm/motorDriven/pump/optimal_specific_speed.cpp`
- Declaration: `ts_def/ts_def_modules/motorDriven/pump/optimal_specific_speed.d.ts`, with package-root
  export and `MeasurToolsSuite` module intersection
- Native test: `tests/cpp/motorDriven/pump/optimal_specific_speed.unit.cpp`
- Typed package-root WASM test: `tests/wasm-mocha/motorDriven/pump/wasm_optimal_specific_speed.test.ts`
- Teaching page: `docs/dox-content/calculators/motorDriven/pump/optimal_specific_speed_calculator.dox`

Canonical value-object pattern: `compressedAir/dryer_operating_cost`. Planner, C++ Namespace Refactorer,
WASM TypeScript Steward, Algorithm Docs Author and Verification Reviewer phases are complete. The existing
composite preservation tests continue to cover the caller; independent pre-PR review is recorded below.

## Public API And Runtime Contract

| Surface | Before | After | Embind kind | Units/defaults | Ownership | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| Specific speed | `OptimalSpecificSpeed(rpm, flowRate, head, stageCount).calculate()`; no standalone WASM export | `optimal_specific_speed::calculate(const Input&)`; `calculateOptimalSpecificSpeed({rpm, flowRate, head, stageCount})` | New function + input value object | rpm, US gpm, ft total head, dimensionless stages; no defaults | Plain input and scalar result; no `delete()` | Approved breaking C++; additive WASM |

`Input` has `double rpm`, `flow_rate`, `head` and `stage_count`. The matching TypeScript
`OptimalSpecificSpeedInput` has four required readonly numeric properties: `rpm`, `flowRate`, `head`
and `stageCount`. `OptimalSpecificSpeedModule` exposes only the runtime function. Input/result names
are not runtime constructors. Shared enums and `Pump.h` are unchanged.

## Compatibility Decision

The epic records the user's approved breaking stateless relocation and deletion of the six obsolete
classes, without wrappers. This child removes `OptimalSpecificSpeed` and migrates its direct caller.
Behavior changes approved: **none**. Retain multiplication/division grouping, the square root and `pow`
expression, the stage-count `double`, and signed-zero/nonfinite arithmetic. No input conversion, validation,
flow-halving, integer restriction, default or clamp is introduced. The legacy unit comment is corrected;
the numerical unit convention is unchanged. Public C++ callers replace the constructor/`calculate()`
pair with the namespace function and a four-field input aggregate.

## Formulas And Units

The calculation answers which US customary specific speed represents the supplied duty for the
downstream efficiency correction. It does not optimize rotational speed or locate a best-efficiency point.
Preserve exactly:

`rpm * sqrt(flow_rate) / pow(head / stage_count, 0.75)`.

Flow is US gpm, total head is ft, speed is rpm and stage count is dimensionless. The result is
`rpm*sqrt(US gpm)/ft^(3/4)`, not a dimensionless specific speed. No coefficients or defaults are added.
The teaching page presents that result first, explains the head-per-stage and unit conventions,
works the three-stage example, and states arithmetic and applicability limits with formula symbol tables.

Representative immutable legacy values:

- `{2000, 2000, 137, 1}`: `2233.5957167946208`.
- `{1800, 1000, 100, 3}`: `4103.1127025185997`.
- `{1800, 1000, 100, 1.5}`: `2439.7254097465811`.

The source relationship is preserved from the fixed baseline; no new external calibration or validated
range is claimed. No SME formula decision is required for this behavior-preserving migration.

## Desktop Impact And Package Coordination

There was no standalone legacy Desktop specific-speed class wrapper to migrate in the epic inspection.
This helper's WASM export is additive; existing composite/correction runtime APIs and cleanup contracts
remain available in this child. Desktop implementation, dependency pins, saved data, enum mappings,
reporting and loading paths are unchanged. Desktop impact must still be verified at consolidated integration.
No child package-version changes or arbitrary beta selection belong here. The Suite stack's integrated
handoff will record its exact CI beta, source revision, migration and remaining Desktop follow-up under #9059.
Release readiness remains pending validation, review and integrated consumer acceptance.

## Legacy Capture And Validation

Before replacing the source, archived the header/implementation from `23b58b0` and compiled an isolated
capture harness with Apple clang 21, `-O3 -DNDEBUG -std=gnu++20`. Evidence root:
`/private/tmp/optimal-specific-speed-baseline-8r1tsd7e`, including source copies, harness,
`metadata.txt` and 32 decimal/hex values in `legacy-results.txt`.
The cases cover single/multiple/fractional stages, signed inputs and zero, NaN, infinity, overflow
and underflow. Portable native/WASM fixtures retain these values and classifications with relative
`1e-14` and absolute `1e-12` tolerance in specific-speed units; signed zeros are compared separately.

- Executed: isolated legacy capture and current comparison with identical flags: **zero raw decimal/hex
  differences across all 32 rows**; `./node_modules/.bin/tsc --noEmit` passed; tracked `git diff --check`
  passed. Full builds/tests have not yet run for this implementation.
- macOS/Apple clang Release build: focused **45 assertions / 3 cases**; full **6603 assertions / 358 cases**.
- Ubuntu 24.04 amd64/GCC 13: matching focused/full counts; full suite under Valgrind 3.22 with
  `--error-exitcode=99 --leak-check=full`: **zero errors, no leaks**.
- Fresh `npm run verify:wasm`: build/stage/typecheck and **298 ChromeHeadless tests passed**.
- Immutable complete stack matrix at `/private/tmp/pump-efficiency-stack-baseline-seajyimb`: **5254 fields**
  compare exactly against fixed legacy on each of macOS, GCC and WASM, with **zero numerical differences or
  classification changes**. Reports: `/private/tmp/pump-228-{macos,wasm}-comparison/comparison.json` and
  archive `gcc-stage-1/comparison.json`. The matrix includes all styles, numeric boundaries and ignored inputs.
- Separate cross-platform legacy ledgers record 1818 compiler/libm differences and zero classification changes,
  including 12 extreme/cancellation fields beyond prior portable diagnostic bounds. They precede this change;
  no existing fixture tolerance was changed. Same-platform preservation is exact on every platform.
- Types, Markdown links, package dry-run runtime/declaration contents, generated Doxygen formulas/tables and
  full diff whitespace passed. No affected-page Doxygen warnings; existing repository BibTeX failure and
  unrelated legacy warnings remain, and interactive MathJax rendering is unverified.
- Logs: `/private/tmp/pump-228-*.log`; Linux logs are archive `linux-228-*.log`.
- Reconfigure CMake so additions/deletions are discovered. Retain existing composite golden values and
  report every raw numerical difference; do not replace captures or loosen tolerances to pass.

## Internal Review

- Intended base: `issue-225` at `ebcedec94c0f7fd26ad6a40d1aa58376ff2beaa3`.
- Reviewed source head: `0ff7a37640a8057ca95fe8b9391d5acfad40798b`.
- Independent reviewer: `desktop_impact`, using `.github/skills/measur-code-review/`; no actionable findings.
- Readiness: ready with documented Doxygen/visual follow-up. Reviewer independently ran focused native,
  types, links and complete diff whitespace and checked exact scalar captures. Linux/full-matrix evidence
  subsequently completed without source changes. Report: `/private/tmp/specific-speed-review-3vpskkxn/review.md`.
- Only handoff/epic metadata changes follow the reviewed source head.
- Material changes after review require another review pass. Retargeting/restacking must use the current
  parent diff; the final epic also requires an integrated review against its intended integration base.

## Open Questions Or Blockers

No implementation design questions remain. Live CI/publication belongs in the linked PR; Desktop adoption,
stack merging after required approvals and final release remain follow-up gates.
