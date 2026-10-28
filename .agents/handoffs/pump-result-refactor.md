# Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: all 14 Suite calculators merged; develop reconciled; integrated validation/review complete with documented CI/publication follow-up; Desktop integration will use the integrated PR's exact beta
- Owner: Codex
- Created: 2026-10-07
- Last updated: 2026-10-28
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/203
- Suite feature branch: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/tree/epic-pump-result-refactor
- Integration readiness branch / PR base: `codex/pump-result-integration-readiness` / `epic-pump-result-refactor`.
  The user requested a child PR into the epic on 2026-10-28; the epic-to-develop PR and merges remain later work.
- Suite CI bootstrap PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/420
- Suite PumpResult PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/421
- Suite Poles issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/216 (closed)
- Suite Poles PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/423 (merged 2026-10-12)
- Desktop issue: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8951
- Desktop coordination issue: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Desktop feature branch: https://github.com/ORNL-AMO/AMO-Tools-Desktop/tree/epic-pump-result-refactor
- Desktop PumpResult PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8956 (merged)
- Prior Desktop MotorEfficiency PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964 (merged at `9b7ff3d7416ff8172ad3ab24fc01ab2ef29acbc9`, verified read-only on 2026-10-27)

## Target Module

- Domain/path: `motorDriven/pump`
- Logical module: pump result assessment
- Legacy files: `PumpResult.h/.cpp`, `pump.cpp`, `pump.d.ts`, one mixed C++ test, and two WASM tests
- Nearby examples: `motorDriven/pump/pump_head` and `compressedAir/dryer_operating_cost`

## Pre-Refactor Public API

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

## Implemented Namespace API

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
- WebAssembly bindings: replace class bindings with two functions and four value objects.
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
| 3 | #208 MotorEfficiency | Desktop PR #8964 is merged; its package records pin `1.2.6-beta.365.1`. Remaining Desktop work is deferred to final integration. | Suite PR #424 merged on 2026-10-13; issue #208 closed; latest published integrated beta `1.2.6-beta.365.1`; last beta with recorded review/validation evidence `1.2.6-beta.363.1`. |
| 4 | #205 EstimateFLA | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite PR [#425](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/425) merged on 2026-10-13 at `363c011`; Desktop migration deferred to final integration. |
| 5 | #206 MotorCurrent | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite PR [#426](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/426) merged on 2026-10-13 at `9b3b8da`. See [MotorCurrent handoff](motor-current-refactor.md). |
| 6 | #210 MotorPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite [PR #428](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/428) merged on 2026-10-14 at `2714873`; recorded validated child beta `1.2.6-beta.374.1`. See [MotorPower handoff](motor-power-refactor.md). |
| 7 | #211 MotorPowerFactor | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite PR [#430](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/430) merged at `9da4f19`; reviewed implementation head `873efc0`. See [MotorPowerFactor handoff](motor-power-factor-refactor.md). |
| 8 | #212 MotorShaftPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite [PR #432](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/432) merged on 2026-10-15 at `80c6475`. See [MotorShaftPower handoff](motor-shaft-power-refactor.md). |
| 9 | #213 OptimalMotorPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite [PR #433](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/433) merged at `1998e82`; reviewed implementation head `5cb2284`. See [OptimalMotorPower handoff](optimal-motor-power-refactor.md). |
| 10 | #220 FluidPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite [PR #434](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/434) merged on 2026-10-15 at `7b5b760`; reviewed implementation head `9d5e46c`. See [FluidPower handoff](fluid-power-refactor.md). |
| 11 | #221 MoverEfficiency | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite PR #441 merged at `8d34462`; implementation independently reviewed Ready at `27510c8`. See the [MoverEfficiency handoff](mover-efficiency-refactor.md). |
| 12 | #227 OptimalPumpShaftPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite PR #442 merged at `2a20eed`; review and delivery evidence linked from the [OptimalPumpShaftPower handoff](optimal-pump-shaft-power-refactor.md). |
| 13 | #222 MoverShaftPower | Defer all Desktop wrapper and package-pin work to the final integration pass. | Suite PR [#443](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/443) merged at `93427c3`. See the [MoverShaftPower handoff](mover-shaft-power-refactor.md). |
| 14 | #214 OptimalMotorShaftPower | Consolidate Desktop wrapper and package-pin work in the final integration pass. | Suite [PR #444](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/444) merged at `e7ceb58`; implemented, verified and independently reviewed Ready. See the [OptimalMotorShaftPower handoff](optimal-motor-shaft-power-refactor.md). |

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
- After integrated Suite validation and review pass, open the reviewed readiness child PR into the epic and use
  that PR's exact CI-published beta for consolidated Desktop implementation and verification. Keep the Suite
  PR open while Desktop integration proceeds. Update both Desktop pins together to that exact beta; never
  use the floating `beta` tag. Coordinate final version selection, publication and merges after both
  implementations are complete. Any changed Suite implementation requires a reviewed replacement beta and
  affected Desktop checks against it. This sequence was explicitly requested by the user on 2026-10-28.

Explicitly outside this feature are `Pump.h`/#202, MotorData/#207, MotorPerformance/#209, FanResult/#198, and the
pump-efficiency chain #223-#230. MotorPerformance and FanResult may receive private consumer updates required by a
dependency migration, but their public refactors remain separate.

## Desktop Impact

- Current state: Desktop MotorEfficiency PR #8964 is already merged at `9b7ff3d7416ff8172ad3ab24fc01ab2ef29acbc9`.
  GitHub status was verified read-only on 2026-10-27; earlier held-PR instructions were stale. Remaining Desktop
  implementation, package updates and verification stay deferred until approved final Suite integration.
- Final integration: consolidate affected wrappers, root and process-flow package pins, and Desktop verification
  against the exact beta published by the integrated Suite PR. Final version selection and merges follow
  completion of both implementations; an RC/final package is not a prerequisite for Desktop implementation.
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
- Integrated beta version: pending readiness PR CI; publication evidence belongs in the PR and Desktop #8957.
- Final package version: deferred until both implementations are complete.
- Desktop root dependency: update during Desktop integration to the integrated PR's exact beta.
- Desktop process-flow dependency: align with the root's exact beta during Desktop integration.
- Prior Desktop PR: #8964 is merged. No Desktop PR changes are part of the remaining Suite child deliveries.
- Release readiness: Suite PR #421 and Desktop PR #8956 are merged; Poles PR #423, MotorEfficiency PR #424,
  EstimateFLA PR #425, and MotorCurrent PR #426 are merged. The epic was synced with develop at `4c573f3`.
  MotorPower PR #428 merged on 2026-10-14 at `2714873`. MotorPowerFactor PR #430 merged at `9da4f19`.
  MotorShaftPower PR #432 merged on 2026-10-15 at `80c6475` after verification and independent review.
  OptimalMotorPower PR #433 merged at `1998e82`; independent pre-PR review is Ready at `5cb2284`.
  FluidPower PR #434 merged on 2026-10-15 at `7b5b760`; independent review was Ready at `9d5e46c`.
  MoverEfficiency implementation, verification and independent review are complete, Ready at `27510c8`;
  child PR/CI evidence is linked from its module handoff.
  Evidence is in the module handoffs.
- Desktop implementation gate: integrated Suite validation/review and the integrated PR's verified exact beta.
- Merge/release gate: complete Desktop implementation, review and verification; coordinate final versions,
  publication and Suite-first merge order afterward. Do not merge the Suite epic as part of beta preparation.

## Validation

- Commands run: baseline `[PumpResults]` passed 129 assertions in 11 cases; refactored `[pump_result]` passed 129 assertions in 11 cases; moved `[EstimateFLA]` passed 64 assertions; the full native suite passed 4,148 assertions in 317 cases; `npm run verify:types` passed; `npm run verify:wasm` rebuilt and staged the composed-input module and passed all 251 browser tests; `npm run check:docs` passed; Doxygen generated the Pump Result page without module-specific warnings; `git diff --check` passed. Against `measur-tools-suite@1.2.6-beta.355.1`, Desktop passed five focused pump wrapper tests, Angular application typechecking, the root application build, and the full PR unit/regression workflow. Poles PR #423 subsequently passed native tests, rebuilt-WASM tests, and declarations/documentation checks before publishing `1.2.6-beta.358.1`. The EstimateFLA Suite-only refactor subsequently passed focused EstimateFLA (64 assertions) and MotorCurrent (4 assertions) tests, 4,196 native assertions in 321 cases, declaration verification, a freshly rebuilt/staged WASM suite with 255 browser tests, documentation checks/Doxygen page generation, and whitespace checks; no Desktop changes were made.
- Historical child validation is retained below. Current integrated evidence is recorded in the
  2026-10-28 section; Desktop review and verification follow against the integrated PR's exact beta.
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

## OptimalMotorShaftPower Implementation — 2026-10-27

- Suite #214 adds a stateless motor namespace and standalone plain-object WASM/TypeScript API;
  PumpResult and FanResult private consumers migrated without changing their expected results.
- Captured 121 legacy fixtures; focused native checks passed 540 assertions/17 cases; full native
  passed 5,836 assertions/348 cases; fresh rebuilt/staged WASM passed all 287 browser tests.
- Optimized differential passed 41,669,208 output comparisons. Typecheck, documentation links,
  complete-diff whitespace, package dry run and generated-page visual inspection passed.
- Independent review of epic base `93427c3` through snapshot `c38d4a39b932afd915f923749a918d216a94b0c2`
  is Ready, no actionable findings; reviewer rebuilt the differential and reran focused checks.
  See the [module handoff](optimal-motor-shaft-power-refactor.md) for the migration contract and evidence.
- User-requested worked-example precision sweep subsequently updated 14 calculation pages and the
  documentation guide. All 82 general formula blocks and 794 source/binding/declaration/test files
  remain unchanged; independent documentation review is Ready. Details are in the module handoff.
- Suite child [PR #444](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/444) delivers this work
  from `issue-214` into the epic; CI/publication evidence stays in that PR. No Desktop changes,
  package-pin updates, manual publication or automatic merge are part of this delivery.
  Existing Doxygen BibTeX failure remains; module-specific page has no warnings. Final epic integration
  review, release and consolidated Desktop verification remain separate work.

## Historical Workflow Documentation Review

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

- All planned Suite calculators are merged. Integrated review and exact-beta publication/consumer checks
  remain before Desktop implementation starts; prior Desktop PR #8964 is already merged. Final version
  selection, RC/final publication and merging are intentionally deferred until both implementations finish.

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
- Remaining Desktop source, tests and package-pin work stay deferred to final integration.

## FluidPower Implementation

- Replaced the header-only class with `fluid_power::calculatePump(PumpInput)` and
  `fluid_power::calculateFan(FanInput)`, returning numeric kW. Added standalone plain-input
  `calculatePumpFluidPower` and `calculateFanFluidPower` WASM/TypeScript APIs. Approved breaking C++ removal
  and additive runtime API; no numerical behavior changes. MoverEfficiency and OptimalPumpShaftPower receive
  private consumer updates only.
- Retained all six original goldens and captured 23 finite duty/boundary outputs. A 373,490-case differential
  comparison matched all non-NaN results bit-for-bit, including signed zero/infinity, and retained NaN classifications.
- Focused native checks passed 259 assertions in 19 cases; full native suite passed 5,061 assertions in 337 cases.
  Fresh rebuilt/staged WASM passed all 276 browser tests. Types, docs/whitespace/package checks and rendered-page
  inspection passed; all 65 MathJax containers rendered without errors. Existing full-documentation BibTeX limitation persists.
- Independent full-diff review of `1998e82...9d5e46c` is Ready with no actionable findings; reviewer independently
  reran focused native, differential, type, documentation-link and whitespace checks. See the module handoff.
- Remaining Desktop source, tests and dependency-pin work stay deferred to final integration. No package publication
  or PR delivery was performed in this implementation.
- Subsequent delivery: Suite [PR #434](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/434) merged into
  the epic on 2026-10-15 at `7b5b760`; the PR holds CI/publication evidence.

## MoverEfficiency Implementation

- Replaced the legacy class with `mover_efficiency::calculatePump(PumpInput)` and
  `mover_efficiency::calculateFan(FanInput)`, returning numeric efficiency fractions. Added standalone
  plain-input `calculatePumpMoverEfficiency` and `calculateFanMoverEfficiency` WASM/TypeScript APIs.
  Breaking C++ removal and additive runtime API explicitly approved; no numerical behavior changes.
- PumpResult and FanResult receive only private consumer updates. Original pump goldens, captured direct
  fan duties and arithmetic boundaries are covered; 2,598,977 legacy differential comparisons passed.
- Final focused native checks passed 259 assertions in 19 cases; full native tests passed 5,088 assertions
  in 338 cases. Fresh rebuilt/staged WASM passed all 279 browser tests. Types, docs/whitespace/package checks
  and rendered-page/example inspection passed; all 69 MathJax containers rendered without errors.
  Existing full-documentation BibTeX limitation persists.
- Independent full-diff review of `7b5b760...27510c8` is Ready with no actionable findings; reviewer
  independently reran focused native, differential, type, documentation-link and whitespace checks.
  See the module handoff for exact validation and review evidence.
- Remaining Desktop source, tests and dependency-pin work stay deferred to final integration.

## OptimalPumpShaftPower Implementation

- Replaced the legacy class with `optimal_pump_shaft_power::calculatePump(PumpInput)` and
  `calculateFan(FanInput)`, returning numeric hp. Added standalone plain-input
  `calculateOptimalPumpShaftPower` and `calculateOptimalFanShaftPower` WASM/TypeScript APIs.
  Breaking C++ removal and additive runtime APIs explicitly approved; no numerical behavior changes.
- PumpResult and FanResult receive only private consumer updates. Captured 30 direct legacy duties;
  native and typed WASM tests cover them plus arithmetic boundaries. All 11,520,946 legacy differential
  comparisons passed, with non-NaN outputs bit-for-bit and matching NaN classifications.
- Focused native checks passed 345 assertions in 22 cases; full native tests passed 5,174 assertions
  in 341 cases. Fresh rebuilt/staged WASM passed all 282 browser tests. Types, docs/whitespace/package
  checks and rendered pump/fan examples passed; all 69 MathJax containers rendered without math errors.
  Existing full-documentation BibTeX limitation and MathJax configuration warnings persist.
- Independent full-diff review against `8d34462`, finalized at isolated snapshot `1046b25`, is Ready.
  A P3 stale Desktop PR status was corrected and re-reviewed; no unresolved actionable findings remain.
  See its module handoff for exact snapshot details and the branch PR/CI evidence link.
- New Desktop source, tests, dependency pins and final package selection remain deferred to final integration.

## MoverShaftPower Implementation

- Replaced legacy calculator/output classes with `mover_shaft_power::calculate(Input) -> Result`
  and `calculateMoverShaftPower(MoverShaftPowerInput) -> MoverShaftPowerResult`, using plain objects.
  Breaking C++/WASM/TypeScript removal explicitly approved on 2026-10-27; no numerical change.
- PumpResult/FanResult receive private consumer migrations only; Drive enum values are unchanged.
- Preserved both output fields across 101 captured duties/boundaries and 1,607,396 exact legacy
  differential comparisons. Focused native checks passed 453 assertions/17 cases; full native passed
  5,448 assertions/344 cases. Fresh rebuilt/staged WASM passed all 284 browser tests.
- Types, links, whitespace and package checks passed. Added a rendered teaching page with formulas,
  symbol/unit tables and worked examples. Existing full-documentation BibTeX limitation persists.
- Independent complete-diff review against `2a20eed` at frozen snapshot `5f82081` is Ready, with no
  actionable findings. Exact commits and validation evidence are recorded in the module handoff.
  No Desktop changes, package-pin changes, publication or manual version bump included.

### MoverShaftPower Named Constants Follow-Up

- Named empirical curve terms, reference belt-loss fractions and conversion factor; documented
  historical attribution without claiming verified coefficient derivation. No API or numerical change.
- Refreshed focused native checks (453 assertions/17 cases), all 1,607,396 exact legacy comparisons,
  and fresh WASM verification (284 browser tests) passed. Follow-up snapshot `f797513` independently
  reviewed Ready; full evidence is in the module handoff.

## Calculation Documentation Cleanup

- Removed API migration/refactor history from all 13 completed epic calculator `.dox` pages;
  migration contracts remain in module handoffs and PRs. Current usage and engineering explanations,
  provenance, model caveats, 81 formulas, 80 symbol/unit tables and 37 inline math expressions remain.
- Added the calculation-versus-migration documentation rule to `contributing/documentation.md`.
  Links, whitespace and generated-page checks pass; existing full-documentation BibTeX error persists.
- Independent documentation review is Ready at frozen snapshot `3295592`, with no actionable findings.
  Delivered as a documentation follow-up in Suite PR [#443](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/443).

## Integrated Desktop Migration Contract — 2026-10-28

All 14 C++ modules intentionally replace their legacy classes with the namespace APIs documented
in the module handoffs. No compatibility wrappers remain. Formulas and defined legacy outputs are
preserved. The bounded exception is the user-approved MotorPerformance near-zero correction in
[MotorPowerFactor](motor-power-factor-refactor.md): pass existing nameplate fields that were previously
uninitialized. No undefined legacy result is a golden; native and WASM tests verify the deterministic
zero-load path. Classify the integrated release as breaking/additive API plus this bounded behavior
correction, and include it in Desktop motor-performance regression verification.
The table lists every changed public WASM calculation; Poles remains C++-only, with no WASM export.

| Surface / detailed contract | Previous WASM API | Integrated WASM API | Units and required data | Kind / ownership / compatibility |
| --- | --- | --- | --- | --- |
| Pump existing / contract above | PumpResult constructors and calculateExisting() | calculateExistingPumpResult(ExistingPumpResultInput) | Nested system, motor FLA and measured kW/A; hp, kW, A, fractions, MWh/year, thousand dollars/year | Function + plain input/result; remove class cleanup; breaking |
| Pump modified / contract above | PumpResult constructors and calculateModified() | calculateModifiedPumpResult(ModifiedPumpResultInput) | Nested system plus pump efficiency fraction; same output units; estimated FLA remains zero | Function + plain input/result; remove class cleanup; breaking |
| [MotorEfficiency](motor-efficiency-refactor.md) | MotorEfficiency(...).calculate(load, efficiency) | calculateMotorEfficiency(MotorEfficiencyInput) | hp, rpm, frequency/class enums, fractional load and specified efficiency; returns fraction | Function + value input, numeric output; remove delete(); breaking |
| [EstimateFLA](estimate-fla-refactor.md) | EstimateFLA(...).getEstimatedFLA() | calculateEstimateFLA(EstimateFLAInput) | hp, rpm, frequency/class enums, efficiency fraction, V; returns estimatedFLA and six partialLoadCurrents in A | Function + value input/output and fixed JS array; no cleanup; breaking |
| [MotorCurrent](motor-current-refactor.md) | MotorCurrent(...).calculateCurrent(fla) | calculateMotorCurrent(MotorCurrentInput, fullLoadAmps) | hp, rpm, frequency/class enums, fractional efficiency/load, V, separate FLA in A; current and independently estimated FLA in A | Function + value input/output; remove delete(); breaking |
| [Optimal current](motor-current-refactor.md) | Not exposed | calculateOptimalMotorCurrent(MotorCurrentInput) | Same required motor input; raw-model current in A, without supplied-FLA/voltage normalization | Function + value input, numeric output; no cleanup; additive |
| [MotorPower](motor-power-refactor.md) | Not exposed | calculateMotorPower(ratedVoltage, motorCurrent, powerFactor) | Required V, A and fractional PF; returns kW | Scalar function; no cleanup; additive |
| [MotorPowerFactor](motor-power-factor-refactor.md) | MotorPowerFactor(...).calculate() | calculateMotorPowerFactor(MotorPowerFactorInput) | Nine required nameplate/operating fields: hp, rpm, A, V, enums and fractions; returns fractional PF | Function + value input, numeric output; remove delete(); breaking |
| [MotorShaftPower](motor-shaft-power-refactor.md) | Not exposed | calculateMotorShaftPower(MotorShaftPowerInput) | Eleven required fields including inactive measurement; hp, kW, rpm, V, A, enums, fractions; seven result fields | Function + plain input/result; no cleanup; additive |
| [OptimalMotorPower](optimal-motor-power-refactor.md) | Not exposed | calculateOptimalMotorPower(OptimalMotorPowerInput) | Eight required nameplate/duty fields; shaft hp, V, rpm, enums/fractions; returns kW, A, efficiency/PF/load fractions | Function + plain input/result; no cleanup; additive |
| [Pump fluid power](fluid-power-refactor.md) | Not exposed | calculatePumpFluidPower(PumpFluidPowerInput) | Specific gravity fraction, gpm, ft; returns kW | Function + value input, numeric output; no cleanup; additive |
| [Fan fluid power](fluid-power-refactor.md) | Not exposed | calculateFanFluidPower(FanFluidPowerInput) | cfm, inlet/outlet/velocity pressure in in. water, compressibility fraction; returns kW | Function + value input, numeric output; no cleanup; additive |
| [Pump mover efficiency](mover-efficiency-refactor.md) | Not exposed | calculatePumpMoverEfficiency(PumpMoverEfficiencyInput) | Specific gravity, gpm, ft and shaft hp; returns efficiency fraction | Function + value input, numeric output; no cleanup; additive |
| [Fan mover efficiency](mover-efficiency-refactor.md) | Not exposed | calculateFanMoverEfficiency(FanMoverEfficiencyInput) | cfm, shaft hp, inlet/outlet/velocity pressure in in. water, compressibility fraction; returns efficiency fraction | Function + value input, numeric output; no cleanup; additive |
| [Optimal pump shaft power](optimal-pump-shaft-power-refactor.md) | Not exposed | calculateOptimalPumpShaftPower(OptimalPumpShaftPowerInput) | gpm, ft, specific gravity and supplied pump-efficiency fraction; returns hp | Function + value input, numeric output; no cleanup; additive |
| [Optimal fan shaft power](optimal-pump-shaft-power-refactor.md) | Not exposed | calculateOptimalFanShaftPower(OptimalFanShaftPowerInput) | cfm, inlet/outlet/velocity pressure in in. water, compressibility and supplied efficiency fractions; returns hp | Function + value input, numeric output; no cleanup; additive |
| [MoverShaftPower](mover-shaft-power-refactor.md) | MoverShaftPower(...).calculate(); MoverShaftPowerOutput | calculateMoverShaftPower(MoverShaftPowerInput) | Motor shaft hp, Drive enum, specified efficiency fraction; returns moverShaftPower hp and driveEfficiency fraction | Function + plain input/result; remove both constructors/cleanup; breaking |
| [OptimalMotorShaftPower](optimal-motor-shaft-power-refactor.md) | Not exposed | calculateOptimalMotorShaftPower(OptimalMotorShaftPowerInput) | Mover shaft hp, Drive enum, specified efficiency fraction; returns motorShaftPower hp and driveEfficiency fraction | Function + plain input/result; no cleanup; additive |

- Every value-object field is required; no new defaults, numerical validation or clamping is added.
  Existing limits, sentinels and nonfinite behavior remain as documented in each module's contract.
- Runtime Drive, LineFrequency, LoadEstimationMethod, MotorEfficiencyClass, PumpStyle and SpecificSpeed
  names/values are unchanged. Reuse Desktop's helper mappings; retain its percent/fraction conversions.
  Current normalized MotorCurrent calls must pass supplied FLA separately. EstimateFLA's six current
  anchors are plain array values, not a registered vector; they require no delete().
- Desktop epic read-only inspection at 9b7ff3d confirms PumpResult and MotorEfficiency are already
  migrated. PumpsSuiteApiService still constructs EstimateFLA, MotorCurrent and MotorPowerFactor;
  migrate those remaining wrappers, passing all newly required power-factor nameplate fields.
  The removed MoverShaftPower runtime surface must be searched again when Desktop work starts;
  no direct call was found in the inspected epic wrapper/process-flow sources.
- Standalone additive functions need no Desktop wrapper merely to complete this integration.
  Pump/fan assessments consume the calculations indirectly; verify fans and MotorPerformance
  behavior along with pumps. Public FanResult/MotorPerformance APIs remain outside the refactor.
- Preserve app-facing PsatOutputs, saved assessment shapes, reports/exports, zero-valued savings
  metadata, annual-energy units and annual-cost conversion. Default database semantics, WASM asset
  names and locateFile behavior are unchanged; check the packaged assets during Desktop verification.
- Both Desktop epic manifests currently pin 1.2.6-beta.365.1. Update both and their lockfiles together
  during Desktop implementation to the integrated PR's exact beta. No Desktop code/pin changes are
  included in this Suite preparation task.

## Integrated Suite Readiness — 2026-10-28

- All 14 child implementations are merged through PR #444 at e7ceb58c8613b403c733268549eb892d802d0638.
- Fetched origin and merged develop b0c46f1fc82a5069020f2b1cb7f466a187239e00 into the epic at
  98ed4d9118daeb026dccb574392f6c8796fec578, preserving history. Manifest/lockfile inherit 1.2.7.
  PumpHead keeps develop's engineering wording and the epic's rounded examples; no runtime change.
- Native Release configure/build and full cpp_tests passed: 5,836 assertions in 348 cases.
- Fresh npm run verify:wasm rebuilt/staged bin/client.js and bin/client.wasm, typechecked and passed
  all 287 browser tests. Restricted SDK-cache access failed first; the approved rerun passed.
- npm run check:docs, all nine beta-publication helper tests and complete-diff whitespace passed.
- npm pack --dry-run --json passed: 102 files, including both runtime assets, the declaration
  entrypoint and all 13 public calculation declaration modules. Poles has no public WASM surface.
- Local Doxygen generated affected pages, but still reports the pre-existing missing-BibTeX error
  and unrelated warnings. Require successful CI Doxygen generation before declaring delivery ready.
- Generated MotorPower page inspected over localhost: readable final equation, units and worked
  example; 38 MathJax containers and no math errors. This closes its prior visual-review gap.
- Full browser sweep checked 15 calculator pages including PumpHead. It found five broken unit
  entries in EstimateFLA and PumpResult: prose inside siunitx expressions was rejected by MathJax.
  Split those symbol rows by applicable units without changing formulas, coefficients or runtime
  code. Regenerated pages and refreshed-browser inspection pass: EstimateFLA 52 and PumpResult
  152 MathJax containers, no math errors; all other inspected pages also had no math errors.
  Documentation links and whitespace checks passed after the fix. No native/WASM rerun is needed
  for this documentation-only delta. Existing fixtures cover pump existing/modified and positive-
  displacement paths, fan consumers, motor calculations, drive branches and arithmetic boundaries.
- Desktop #8957 now records the user-approved exact-beta-first implementation sequence, with final
  versions and merging deferred until both implementations finish. No Desktop source/pins changed.
- Independent integrated review by integrated_suite_review used .github/skills/measur-code-review/
  on the complete 180-file diff, base develop b0c46f1fc82a5069020f2b1cb7f466a187239e00 through
  head 7f4c51f32581f530c0b85bbe916b87720c0a3fbb. Readiness: Ready with documented follow-up;
  no unresolved P0-P2 findings. Reviewer independently passed 1,985 native assertions in 50 cases,
  types, links, whitespace, nine beta helper tests and cross-layer checks of 24 value objects and
  18 runtime functions across 13 modules. Full native/fresh-WASM evidence was corroborated.
- One P3 finding corrected: the integrated migration summary now records the previously approved
  bounded MotorPerformance near-zero correction, with corresponding PR behavior classification.
  This changes handoff/review evidence only; implementation/docs remain identical to reviewed head.
  Rerun links/whitespace for these metadata edits. No unresolved actionable findings remain.
- Final rendered sweep: all 15 pages, 1,200 MathJax containers, zero math errors. Local BibTeX
  limitation remains documented; successful CI Doxygen and exact-beta consumer verification are
  delivery gates before the beta is declared ready. Post-push evidence stays in PR/issue records.
- Readiness delivery target changed at the user's request: branch codex/pump-result-integration-readiness
  targets epic-pump-result-refactor at e7ceb58c8613b403c733268549eb892d802d0638. The child diff
  includes develop reconciliation, the handoff and two unit-table documentation repairs; no runtime
  change. A separate review of this six-file child diff is required before opening its PR. The full
  epic-to-develop review above remains implementation evidence, not a substitute for the child review.
  The readiness PR's beta contains the combined implementation and can support Desktop validation;
  the epic-to-develop PR, final package version and merges remain subsequent coordinated work.
- Integrated PR/CI and post-push publication evidence will live in the
  [readiness PR conversation](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pulls?q=is%3Apr+head%3Acodex%2Fpump-result-integration-readiness+base%3Aepic-pump-result-refactor)
  and [Desktop coordination issue](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957).
  Do not push evidence-only commits after beta publication. Keep the PR open; final release versions
  and merging await completion of both implementations.
