# Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: Suite through MotorShaftPower merged; OptimalMotorPower implemented, verified and independently reviewed Ready at 5cb2284; all remaining Desktop migration is deferred to final integration
- Owner: Codex
- Created: 2026-10-07
- Last updated: 2026-10-15
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/203
- Suite feature branch: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/tree/epic-pump-result-refactor
- Suite CI bootstrap PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/420
- Suite PumpResult PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/421
- Suite Poles issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/216 (closed)
- Suite Poles PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/423 (merged 2026-10-12)
- Desktop issue: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8951
- Desktop coordination issue: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Desktop feature branch: https://github.com/ORNL-AMO/AMO-Tools-Desktop/tree/epic-pump-result-refactor
- Desktop PumpResult PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8956 (merged)
- Desktop held integration PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964 (open; intentionally held)

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

## Feature PR Sequence

The Suite and Desktop integration branches are both named `epic-pump-result-refactor`. Each child branch starts from
the latest corresponding feature-branch head and merges through a reviewed PR into that feature branch. Modules are
ordered so foundational calculators migrate before the composite calculators that consume them.

| Order | Suite issue/module | Desktop action | Status |
| ---: | --- | --- | --- |
| 1 | #203 PumpResult | Completed in Desktop PR #8956. | Suite PR #421 and Desktop PR #8956 merged. |
| 2 | #216 Poles | No new Desktop work; final integration will consume the final Suite package once. | Suite PR #423 merged; issue closed; beta `1.2.6-beta.358.1` published. |
| 3 | #208 MotorEfficiency | Desktop PR #8964 is open and intentionally held without further changes or merge until the full Suite sequence is approved; its existing package pins are `1.2.6-beta.365.1`. | Suite PR #424 merged on 2026-10-13; issue #208 closed; latest published integrated beta `1.2.6-beta.365.1`; last beta with recorded review/validation evidence `1.2.6-beta.363.1`. |
| 4 | #205 EstimateFLA | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite PR [#425](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/425) merged on 2026-10-13 at `363c011`; Desktop migration deferred to final integration. |
| 5 | #206 MotorCurrent | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite PR [#426](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/426) merged on 2026-10-13 at `9b3b8da`. See [MotorCurrent handoff](motor-current-refactor.md). |
| 6 | #210 MotorPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite [PR #428](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/428) merged on 2026-10-14 at `2714873`; recorded validated child beta `1.2.6-beta.374.1`. See [MotorPower handoff](motor-power-refactor.md). |
| 7 | #211 MotorPowerFactor | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite PR [#430](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/430) merged at `9da4f19`; reviewed implementation head `873efc0`. See [MotorPowerFactor handoff](motor-power-factor-refactor.md). |
| 8 | #212 MotorShaftPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite [PR #432](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/432) merged on 2026-10-15 at `80c6475`. See [MotorShaftPower handoff](motor-shaft-power-refactor.md). |
| 9 | #213 OptimalMotorPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Implemented, verified and independently reviewed Ready at `5cb2284`; child PR delivery pending. See [OptimalMotorPower handoff](optimal-motor-power-refactor.md). |
| 10 | #220 FluidPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Planned Suite-only work. |
| 11 | #221 MoverEfficiency | Defer all Desktop wrapper and package-pin work to the final integration pass. | Planned Suite-only work. |
| 12 | #227 OptimalPumpShaftPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Planned Suite-only work. |
| 13 | #222 MoverShaftPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Planned Suite-only work. |
| 14 | #214 OptimalMotorShaftPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Planned Suite-only work. |

For each module:

- Preserve formulas, empirical coefficients, branches, units, interpolation, limits, and golden outputs.
- Use the namespace/value-object pattern across C++, WASM, declarations, tests, and teaching documentation when the
  module is publicly exposed.
- Update PumpResult, FanResult, MotorPerformance, and database consumers only as required to compile against the new
  dependency API. Do not refactor their public APIs unless their own issue is included in this sequence.
- Keep a module-specific handoff with the old/new runtime contract and ownership rules.
- Before opening each child PR, run a review-only pass with `.github/skills/measur-code-review/` against the intended
  feature-branch base. Record the reviewed base/head commits, findings and dispositions, rerun affected checks, and
  require a `Ready` or `Ready with documented follow-up` result with no unresolved P0-P2 findings.
- Complete Suite implementation, cross-layer tests, documentation, package artifacts, and pre-PR review for every
  remaining module before changing Desktop again.
- After the integrated Suite review passes, publish the approved final or release-candidate package. Rebase and
  consolidate Desktop PR #8964 against the final integration branch, update both Desktop package pins once, migrate
  every affected wrapper, and perform Desktop review and verification once.

Explicitly outside this feature are `Pump.h`/#202, MotorData/#207, MotorPerformance/#209, FanResult/#198, and the
pump-efficiency chain #223-#230. MotorPerformance and FanResult may receive private consumer updates required by a
dependency migration, but their public refactors remain separate.

## Desktop Impact

- Current state: Desktop PR #8964 remains open as retained validation history and is intentionally held with no new
  updates or merge until the complete Suite sequence reaches approved final integration.
- Final integration: consolidate all affected wrappers, root and process-flow package pins, and Desktop verification
  into one rebase/review cycle against the approved final or RC Suite package.
- Until then: no Desktop implementation, wrapper tests, Angular typecheck/build, regression run, or package-pin update
  is part of an individual Suite child delivery.

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
- PumpResult Desktop-validation beta: `1.2.6-beta.355.1`
- Recorded MotorEfficiency integrated Suite beta: `1.2.6-beta.365.1` from merged PR #424, confirmed by its
  [publication workflow](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/actions/runs/38400544559).
- Last MotorEfficiency beta with recorded review/validation evidence: `1.2.6-beta.363.1`. The `.365.1` package was
  published after that reviewed head; this record does not extend `.363.1` review/validation coverage to `.365.1`.
- Existing Desktop PR #8964 package pins: root and process-flow manifests both pin `1.2.6-beta.365.1` at Desktop head
  `2b48fc84ecc6834d83a3bf56318f266c28368caa`; its description still records `.363.1` as the tested beta. These are
  distinct package-publication, dependency-state, and validation facts; no Desktop update was made in this task.
- EstimateFLA PR #425 published child betas `.366.1` and `.367.1` and merged into the integrated branch on
  2026-10-13 at `363c011`. Subsequent package identifiers are recorded separately when verified.
- MotorCurrent beta: `1.2.6-beta.370.1`, verified from [PR #426's CI comment](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/426#issuecomment-6151817084); Desktop will not consume an individual MotorCurrent beta.
- MotorPower recorded beta: `1.2.6-beta.374.1` at `b61a2af`, verified from [PR #428's CI comment](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/428#issuecomment-6172509451). CI passed; Desktop does not consume this individual beta. Later handoff-only heads may publish newer packages.
- MotorEfficiency Suite status: PR #424 merged on 2026-10-13; issue #208 closed.
- Final package version: pending
- Desktop root dependency: do not update until final integration; then update once to the approved final/RC package.
- Desktop process-flow dependency: do not update until final integration; then align it with the root once.
- Desktop held PR: #8964 remains open, unmodified, and unmerged until the final Suite package is available.
- Release readiness: Suite PR #421 and Desktop PR #8956 are merged; Poles PR #423, MotorEfficiency PR #424,
  EstimateFLA PR #425, and MotorCurrent PR #426 are merged. The epic was synced with develop at `4c573f3`.
  MotorPower PR #428 merged on 2026-10-14 at `2714873`. MotorPowerFactor PR #430 merged at `9da4f19`.
  MotorShaftPower PR #432 merged on 2026-10-15 at `80c6475` after verification and independent review.
  OptimalMotorPower implementation and verification are complete; independent pre-PR review is Ready at `5cb2284`.
- Release blockers: complete and review all remaining Suite modules, pass the integrated Suite review, publish the approved final/RC package, then perform the one Desktop integration/review cycle.

## Validation

- Commands run: baseline `[PumpResults]` passed 129 assertions in 11 cases; refactored `[pump_result]` passed 129 assertions in 11 cases; moved `[EstimateFLA]` passed 64 assertions; the full native suite passed 4,148 assertions in 317 cases; `npm run verify:types` passed; `npm run verify:wasm` rebuilt and staged the composed-input module and passed all 251 browser tests; `npm run check:docs` passed; Doxygen generated the Pump Result page without module-specific warnings; `git diff --check` passed. Against `measur-tools-suite@1.2.6-beta.355.1`, Desktop passed five focused pump wrapper tests, Angular application typechecking, the root application build, and the full PR unit/regression workflow. Poles PR #423 subsequently passed native tests, rebuilt-WASM tests, and declarations/documentation checks before publishing `1.2.6-beta.358.1`. The EstimateFLA Suite-only refactor subsequently passed focused EstimateFLA (64 assertions) and MotorCurrent (4 assertions) tests, 4,196 native assertions in 321 cases, declaration verification, a freshly rebuilt/staged WASM suite with 255 browser tests, documentation checks/Doxygen page generation, and whitespace checks; no Desktop changes were made.
- Commands still needed: final generated-document visual review; Suite checks for each remaining module; one integrated Suite review; then one consolidated Desktop review and verification against the approved final package.
- MotorCurrent validation: native build and 4,314 assertions in 324 cases passed; focused motor/pump/fan checks
  passed 253 assertions; typechecking and freshly rebuilt/staged WASM verification passed all 260 browser tests.
  Documentation links, whitespace checks, package dry run, and generated-page inspection passed; independent
  internal review is Ready with no actionable findings. Reviewed implementation head: `da8f42a`.
- Known environment limits: Doxygen reports pre-existing repository warnings and cannot run BibTeX in this environment. Browser security policy prevented opening the generated local HTML page, so generated markup was inspected statically.
- MotorPowerFactor validation: focused power-factor/pump/fan checks passed 207 assertions in 17 cases; full
  native tests passed 4,381 assertions in 329 cases; declarations and fresh-WASM verification passed all 267
  browser tests. Docs/whitespace/package checks and generated MathJax page inspection over localhost passed.
  The existing BibTeX limitation remains; the new page uses verified direct source links.

- MotorShaftPower validation: 40 complete seven-output legacy captures; focused native checks passed 446
  assertions in 16 cases; full native suite passed 4,675 assertions in 332 cases; declarations and freshly
  staged WASM passed all 270 browser tests. Docs/whitespace/package checks and rendered-page inspection passed.
  Existing Doxygen BibTeX limitation persists. Independent review of `ba430c6...17a30db` is Ready with
  no actionable findings; final native/fresh-WASM reruns passed. No Desktop changes or validation performed for this child.

## Internal Review

- Intended PR base and reviewed base commit: `epic-pump-result-refactor` at `ea65920089a11d426996f065b4a554bb046c7066`.
- Reviewed head commit: `38542a621bee5cd0ef880c80fb740ad361a17307`.
- Reviewer or review task: review-only Codex pass using `.github/skills/measur-code-review/`.
- Readiness result: ready.
- Findings and dispositions: one P2 documentation inconsistency was resolved. The coordinated Suite-to-Desktop workflow
  previously opened or readied a PR before the new internal-review gate; its canonical release sequence now requires
  the review in both repositories before their PRs open.
- Checks rerun after review fixes: `npm run check:docs` and `git diff --check` passed.
- Remaining P3 findings, questions, or validation gaps: none for this documentation change. This review-evidence entry
  is the only change after the reviewed head and does not materially alter the reviewed workflow.

## Open Questions Or Blockers

- The final package identifier remains pending. Desktop PR #8964 is intentionally held until all Suite modules are merged and the integrated Suite review approves a final/RC package.

## MotorShaftPower Readability Follow-Up

- POWER/CURRENT implementation paths are private functions with named operating points and shared evaluation,
  interpolation and voltage helpers. The conversion uses `physics::conversions::kBhpToKw` (unchanged 0.746).
- Full native validation passed 4,675 assertions in 332 cases; fresh WASM passed all 270 browser tests.
  A 1,152-case comparison with the preceding implementation matched all non-NaN fields bit-for-bit and
  retained NaN classifications. No goldens, public interfaces, Desktop code or package pins changed.
- Independent full-diff re-review of `ba430c6...02bf735` is Ready with no actionable findings.

## OptimalMotorPower Implementation

- Replaced the legacy C++ class with `optimal_motor_power::calculate(Input) -> Result` and added the standalone
  plain-object `calculateOptimalMotorPower` WASM/TypeScript API. Breaking C++ removal and additive runtime API
  explicitly approved; no numerical behavior changes. PumpResult and FanResult receive private updates only.
- Captured 69 complete five-output legacy fixtures; native tests and typed browser tests preserve them.
  A 9,504-case differential comparison matched every non-NaN output bit-for-bit and retained NaN classifications.
- Full native suite passed 5,031 assertions in 335 cases; fresh WASM verification passed all 273 browser tests.
  Declarations, docs/whitespace/package checks and rendered MathJax page/example inspection passed.
  Existing full-documentation BibTeX limitation persists. Independent full-diff review of `80c6475...5cb2284`
  is Ready with no actionable findings; reviewer independently reran 356 native assertions and declaration/whitespace checks.
- Desktop source, tests, package pins and held PR #8964 remain deferred to final integration.
