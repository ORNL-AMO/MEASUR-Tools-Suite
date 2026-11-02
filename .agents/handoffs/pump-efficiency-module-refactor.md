# Pump Efficiency Module Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: implementation prepared; integrated validation and independent review pending
- Owner: Codex
- Created / last updated: 2026-11-02
- Suite issue / coordinating epic: [#230](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/230)
- Epic handoff: [pump-efficiency-refactor.md](pump-efficiency-refactor.md)
- Suite branch: `issue-230`; initial PR base: `issue-226`
- Suite PR: pending
- Fixed legacy source baseline: `23b58b07e04a16c61d18344a67930ca01d791f7c`
- Desktop issue: [#9059](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/9059)
- Desktop PR: follow-up after Suite stack integration

## Target Module And Touched Layers

Replace global `PumpEfficiency` in `motorDriven/pumpFan` with the stateless
`motorDriven/pump/pump_efficiency` module. The matching header, implementation, binding,
declaration, native tests, typed WASM tests and calculation `.dox` follow the one-module rule.
Canonical value-object pattern: `compressedAir/dryer_operating_cost`.

Migrate earlier deviation-factor and pre-efficiency native/WASM composite fixtures while retaining
their existing numeric literals and tolerance expressions. Remove the superseded header/source,
legacy WASM test, now-empty mixed `pumpFan` binding/declaration and package-root `PumpFanModule`
wiring. Keep all unrelated pump/fan modules and shared enum registrations unchanged.

Planner, C++ Namespace Refactorer, WASM TypeScript Steward and Algorithm Docs Author responsibilities
are prepared. Verification Reviewer and pre-PR review remain pending.

## Public API And Runtime Contract

| Surface | Before | After | Embind kind | Units/defaults | Ownership | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| Composite pump efficiency | `PumpEfficiency(style, pumpEfficiency, rpm, kinematicViscosity, stageCount, flowRate, head).calculate()` | `pump_efficiency::calculate(const Input&)`; `calculatePumpEfficiency({style, rpm, kinematicViscosity, stageCount, flowRate, head})` | Calculator class replaced by function + input value object | Pump style, rpm, cSt, dimensionless stages, US gpm, ft total head; no defaults | Plain input; no cleanup | Approved breaking C++ and WASM |
| Result | Runtime `PumpEfficiencyResults` with `average`, `max`, constructor and `delete()` | C++ `pump_efficiency::Result`; plain TypeScript `PumpEfficiencyResult {average, max}` | Result class replaced by value object | Both fields are dimensionless efficiency fractions | Plain result; no cleanup | Approved breaking C++ and WASM |

C++ `Input` fields are `style`, `rpm`, `kinematic_viscosity`, `stage_count`, `flow_rate` and `head`.
TypeScript has corresponding required readonly camelCase fields. `PumpEfficiencyModule` contains
only the runtime function; interfaces are exported types without runtime constructors.

## Compatibility Decision And Migration

The user approved the stateless breaking namespace relocation, deletion of legacy surfaces and this
stack's implementation. Replace constructor/`calculate()` pairs with the function and six-field input;
remove calculator/result cleanup. No compatibility wrapper remains.

Omit the old `pumpEfficiency` argument. Fixed legacy captures independently show it is unused:
360 comparisons across all 13 styles plus two native unknown values, eight old argument values
(including signed zero, infinities and NaN), and all three optimal/average/max fields are exactly equal.
This removal does not activate a supplied-efficiency override.

Behavior changes approved: **none**. Preserve call/evaluation order, full-precision intermediates,
coefficients, `double` stage count, boundaries, `fmin`/`fmax` handling and signed/nonfinite behavior.
No validation, default, clamp, flow-halving or engineering correction is introduced.

## Formulas, Units And Teaching Page

Engineering question: estimate corrected average and empirical maximum efficiency from pump style
and duty. The final results are efficiency fractions, not percentages:

`average = optimal_pump_efficiency::calculate(input)`

`max = average * optimal_deviation_factor::calculate(flow_rate)`.

The supporting corrected average is `(Epre / 100) * Cnu - Cns`. Pre-efficiency is a percentage;
viscosity is a multiplier and speed correction is a fractional decrement. Duty units are rpm,
cSt, dimensionless stages, US gpm and ft total head. No stored efficiency argument contributes.

The `.dox` page teaches the final estimates first, traces the supporting method, provides formula
symbol tables, works the ANSI/API example and explains fallbacks and inappropriate uses. Detailed
coefficients remain on the linked helper pages. No empirical calibration range or unverified external
reference is invented; original provenance remains unverified.

Example: ANSI/API, 2000 rpm, 1.107 cSt, one stage, 2000 US gpm, 137 ft. Fixed legacy values:
`average=0.83933686357794668`, `max=0.86957345321252744`, representing approximately 83.93% and 86.96%.
Specified-efficiency and positive-displacement pre-efficiency fallbacks still permit negative corrected
results. Zero/negative/nonfinite duties retain arithmetic outcomes and are not valid operating claims.

## Desktop And Release Coordination

Desktop implementation and dependency updates are deferred under #9059. Its two wrappers migrate
once against the exact integrated beta: `achievableEfficiency` keeps fraction-to-percent conversion;
`pumpEfficiency` keeps its app-facing arguments and returns fractions. Retain the unused adapter
argument to avoid caller churn, but do not pass it into the new Suite input. Remove only obsolete
Suite calculator/result cleanup.

Preserve enum mappings, gpm/ft conversions, production rounding, app models, reporting and saved data.
Recheck process-flow consumers; align both manifests and generated lockfiles in the follow-up. No
package filenames, asset paths, `locateFile` or default databases change here. Root/consumer tests,
immutable production-service baselines and final-package verification remain follow-up gates.

Exact integrated beta/final package versions remain pending. Child betas are not accepted as the
consolidated Desktop integration package. Keep publication evidence in the PR, without evidence-only
follow-up pushes. Reconcile current develop and prior PumpResult integration before final readiness.

## Legacy Capture And Validation

Full evidence: `/private/tmp/pump-efficiency-stack-baseline-seajyimb`, archived fixed source hashes,
identical binary inputs and 5,254 full-precision result fields on Apple clang 21/macOS, GCC 13.3/Ubuntu
24.04 amd64 and Emscripten 4.0.12. Stage 4 of the shared harness selects all migrated APIs.

- New native fixtures cover 184 duties; typed WASM fixtures cover 182, including all styles, boundary
  neighbors, fractional/multiple stages, viscosity-cap neighbors and invalid/nonfinite arithmetic.
- Native-only unknown enum cases remain separate from embind's accepted runtime enums.
- Existing fixture values/tolerances and the original representative WASM assertions are retained.
- Same-platform legacy/current comparison must be exact, including zero signs and nonfinite classifications.
- Existing cross-platform legacy variation is logged separately: GCC and WASM are numerically equal;
  each differs from macOS in 1,818 fields, with zero classification changes. Twelve newly captured
  unsupported-style five-stage fields exceed previous diagnostic bounds before any refactor.
  No existing golden or tolerance is changed; those cases stay in exact per-platform captures.
- Comparison self-checks reject sign/classification and one-ULP differences and accept identical NaN/-0.

Still required: focused/full native checks, Linux Valgrind, fresh `npm run verify:wasm`, declaration
checks, docs/link generation and affected-page inspection, package-content verification, full candidate
whitespace check and independent pre-PR review. No integrated checks are claimed by preparation alone.

## Internal Review

- Intended initial base: `issue-226`; freeze actual parent/head commits when the layer is applied.
- Reviewed commits, reviewer, findings/dispositions and readiness: pending.
- Review the incremental parent diff and the final integrated diff against the intended integration base.
- Repeat affected validation and review after material fixes or restacking. No actionable unresolved P0–P2
  finding may remain when opening the PR. Required human approval remains separate.

## Open Questions Or Blockers

No implementation design questions remain. Validation, review, publication and integrated readiness are pending.
