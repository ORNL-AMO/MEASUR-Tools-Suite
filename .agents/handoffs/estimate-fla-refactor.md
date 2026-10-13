# Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: Suite PR #425 open for review; Desktop migration deferred to final integration
- Owner: Codex
- Created: 2026-10-13
- Last updated: 2026-10-13
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/205
- Suite PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/425
- Desktop issue: deferred to final integration
- Desktop PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964 (open and intentionally held)

## Target Module

- Domain/path: `motorDriven/motor`
- Logical module: EstimateFLA
- Current files: `estimate_fla.h/.cpp`, dedicated WASM binding/declaration/test, and calculator documentation
- Nearby examples: `motor_efficiency` and `compressedAir/dryer_operating_cost`

## Runtime API Contract

| Surface | Before | After | Embind kind | Ownership and cleanup | Compatibility |
| --- | --- | --- | --- | --- | --- |
| EstimateFLA | C++ `EstimateFLA(...).calculate()` returns an array; WASM `new EstimateFLA(...).getEstimatedFLA()` exposes only FLA | `estimate_fla::calculate(Input)` / `calculateEstimateFLA(input)` exposes both results | `class_` to `function` + `value_object` | Plain input/output and fixed value array; no `delete()` | Breaking |

## Proposed Namespace API

- Namespace: `estimate_fla`
- Function: `calculate(const Input&) -> Result`
- Value objects: C++ `Input`/`Result`; WASM/TypeScript `EstimateFLAInput`/`EstimateFLAOutput`
- Outputs: `estimated_fla` and a fixed 0/25/50/75/100/125-percent partial-load array
- Removed runtime name: `EstimateFLA`

## Compatibility Decision

- Decision: approved breaking stateless refactor; remove the legacy class, runtime constructor, and compatibility tests.
- User approval: explicit in this task on 2026-10-13.
- Behavioral preservation: retain all coefficients, class selection, pole selection, voltage adjustment, specified-efficiency behavior, partial-load semantics, and golden results.

## Desktop Impact

- Known consumer: `PumpsSuiteApiService.estimateFla` constructs the removed runtime class.
- Delivery decision: do not alter Desktop until every Suite child has completed review and the approved final/RC package is published.
- Held work: Desktop PR #8964 remains open as validation history and receives no updates or merge before final integration.

## Formulas And Units

- Curve: retained double-exponential basic, class-multiplier, and interval-multiplier curves.
- Full-load adjustment: the 100-percent anchor is corrected from the 460 V model reference; the specified class also applies its selected baseline-efficiency ratio.
- Partial-load behavior: six anchors remain unadjusted legacy curve values.
- Constants: 460 V is model-local. This calculator has no hp-to-kW conversion; its motor-efficiency dependency uses `physics::conversions::kBhpToKw` (0.746).
- Documentation: `docs/dox-content/calculators/motorDriven/motor/estimate_fla_calculator.dox`.

## Validation

- Commands run: focused native `[estimate_fla]` passed 64 assertions; focused `[MotorCurrent]` passed 4 assertions;
  the full native suite passed 4,196 assertions in 321 cases; `npm run verify:types` passed; `npm run verify:wasm`
  rebuilt/staged the module and passed all 255 browser tests; `npm run check:docs` passed; Doxygen generated the
  EstimateFLA page and its internal links; `git diff --check` passed.
- Commands still needed: PR CI and the final integrated Suite review after the remaining modules merge.
- Known environment limits: Doxygen reported the repository's existing missing-BibTeX/tooling issue and pre-existing
  documentation warnings, but no EstimateFLA-specific warning.

## Internal Review

- Intended PR base: `epic-pump-result-refactor` at `e6d6df776a9aa3546ab97f58bb0ee2e6ba6e13a5`.
- Reviewed head commit: `971015d1b2ae2541ae00a764cf21140f19b93496`.
- Review scope: complete `base...head` implementation diff; subsequent handoff-only commits record review evidence
  and the PR URL without changing the reviewed calculation or API.
- Reviewer: review-only pass following `.github/skills/measur-code-review/`.
- Readiness result: ready.
- Findings and dispositions: corrected the engineering documentation's basic-curve coefficient units to A/hp
  and clarified that the old WASM API exposed only FLA. C++ API, MotorCurrent migration, embind ownership,
  TypeScript declarations, typed WASM surface, algorithm documentation, and deferred Desktop impact are consistent.
- Checks rerun after documentation corrections: `npm run check:docs`, `doxygen Doxyfile`, and `git diff --check`;
  no EstimateFLA-specific Doxygen warnings or unresolved P0-P2 findings remain.
- Remaining P3 findings, questions, or validation gaps: no local `clang-format` executable is installed; formatting was
  checked manually against the nearby motor-efficiency pattern.

## Open Questions Or Blockers

- No implementation blocker. The only downstream gate is the intentionally deferred final Suite-to-Desktop integration.

## PR Review Follow-Up (2026-10-13)

- Review: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/425#pullrequestreview-5506501562
- Premium boundary: public C++, TypeScript, and calculator documentation now require 2-, 4-, or 6-pole premium
  selections. The pre-existing three-column table is unchanged; unsupported higher-pole inputs are not validated
  or clamped, preserving the approved behavior contract.
- Premium coverage: added a native golden for every supported premium pole column, checking estimated FLA and all
  six anchors (21 assertions), plus a typed WASM golden. Values were captured by compiling the legacy EstimateFLA
  header/source from base `e6d6df7`, with 200 hp, 230 V, 60 Hz, and speeds 3600/1780/1200 rpm.
- Specified efficiency: documented the > 0 precondition in all public surfaces; the retained calculation still does
  not validate it. Exact equal-distance baseline comparisons choose ENERGY_EFFICIENT, now documented explicitly.
- Package records: central handoff distinguishes last documented MotorEfficiency reviewed beta `.363.1`, latest
  published integrated beta `.365.1`, and Desktop #8964's existing `.365.1` pins; no new Desktop work was performed.
- Verification: focused native `[estimate_fla]` passed 85 assertions in 2 cases; full native suite passed 4,217
  assertions in 322 cases; `npm run verify:types`, freshly rebuilt/staged `npm run verify:wasm` (256 browser tests),
  `npm run check:docs`, and `git diff --check` passed. Doxygen generated the updated API/calculator pages without
  module-specific warnings; the pre-existing missing-BibTeX and unrelated warnings remain.
- Follow-up review: compared all five review findings with the revised public comments, fixtures, and verified
  remote package records; no unresolved finding remains from this review. No calculation or binding code changed.
