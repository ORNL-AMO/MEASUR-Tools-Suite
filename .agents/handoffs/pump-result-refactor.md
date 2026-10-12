# Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: Suite and Desktop PumpResult changes merged; Poles merged; MotorEfficiency Suite and Desktop child PRs open
- Owner: Codex
- Created: 2026-10-07
- Last updated: 2026-10-12
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/203
- Suite feature branch: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/tree/epic-pump-result-refactor
- Suite CI bootstrap PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/420
- Suite PumpResult PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/421
- Suite Poles issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/216 (open)
- Suite Poles PR: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/423 (merged 2026-10-12)
- Desktop issue: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8951
- Desktop coordination issue: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Desktop feature branch: https://github.com/ORNL-AMO/AMO-Tools-Desktop/tree/epic-pump-result-refactor
- Desktop PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8956

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
| 1 | #203 PumpResult | Use Desktop issue #8951 and PR #8956 for the wrapper migration. | Suite PR #421 and Desktop PR #8956 merged. |
| 2 | #216 Poles | No Desktop PR; update and test dependent Suite consumers. | Suite PR #423 merged; all quality checks passed; beta `1.2.6-beta.358.1` published. Issue #216 remains open. |
| 3 | #208 MotorEfficiency | Use Desktop issue #8961 and PR #8964 for the existing efficiency wrappers. | **In progress:** Suite PR #424 is green and published beta `1.2.6-beta.359.1`; Desktop PR #8964 passed local exact-beta validation and is open. |
| 4 | #205 EstimateFLA | Create a Desktop issue and PR for `estimateFla`. | Planned |
| 5 | #206 MotorCurrent | Create a Desktop issue and PR for `motorCurrent`. | Planned |
| 6 | #210 MotorPower | No Desktop PR; internal dependency migration. | Planned |
| 7 | #211 MotorPowerFactor | Create a Desktop issue and PR for `motorPowerFactor`. | Planned |
| 8 | #212 MotorShaftPower | No direct Desktop API; migrate PumpResult and FanResult consumers. | Planned |
| 9 | #213 OptimalMotorPower | No direct Desktop API; migrate PumpResult and FanResult consumers. | Planned |
| 10 | #220 FluidPower | No Desktop PR; foundational pump/fan hydraulic calculation. | Planned |
| 11 | #221 MoverEfficiency | No direct Desktop API; migrate PumpResult and FanResult consumers. | Planned |
| 12 | #227 OptimalPumpShaftPower | No direct Desktop API; migrate PumpResult and FanResult consumers. | Planned |
| 13 | #222 MoverShaftPower | No current Desktop caller; verify removal of the legacy runtime class. | Planned |
| 14 | #214 OptimalMotorShaftPower | No direct Desktop API; migrate PumpResult and FanResult consumers. | Planned |

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
- Keep the Suite PR draft until it is ready for a meaningful beta. For a public API migration, validate Desktop
  against that exact beta and keep the root and process-flow dependency pins aligned.
- Do not create an empty Desktop PR for an internal Suite change. Record the no-change consumer analysis and focused
  Desktop verification on the Suite PR and Desktop coordination issue instead.

Explicitly outside this feature are `Pump.h`/#202, MotorData/#207, MotorPerformance/#209, FanResult/#198, and the
pump-efficiency chain #223-#230. MotorPerformance and FanResult may receive private consumer updates required by a
dependency migration, but their public refactors remain separate.

## Desktop Impact

- Wrapper or helper changes: migrate `PumpsSuiteApiService` result methods to plain inputs/functions and build one shared `PumpResultSystemInput` for both paths.
- Enum, unit, percentage, or nullable conversion changes: none; keep current adapter conversions.
- App models, reports, exports, or saved-data changes: none.
- Process-flow package changes: dependency pin only; no direct consumer found.
- Web/Electron WASM loading changes: none planned.
- Downstream verification: focused wrapper tests, Angular typecheck, and root build against exact package.
- Desktop implementation branch: `issue-8951`; rebased onto `epic-pump-result-refactor` at `d1ba297a9`.
- Desktop prerequisite: pump-head PR #8945 merged into Desktop `develop` on 2026-10-08 and is included in the feature-branch base.

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
- Latest integrated Suite beta: `1.2.6-beta.358.1` from merged Poles PR #423
- MotorEfficiency Desktop-validation beta: `1.2.6-beta.359.1` from Suite PR #424
- Final package version: pending
- Desktop root dependency: update to exact beta/final package
- Desktop process-flow dependency: keep aligned with root
- Desktop PumpResult PR pins: both manifests and lockfiles are aligned at `1.2.6-beta.355.1`.
- Release readiness: Suite PR #421 and Desktop PR #8956 are merged; Poles PR #423 is merged; MotorEfficiency Suite PR #424 and Desktop PR #8964 are open with exact-beta validation complete.
- Release blockers: complete the dependency PR sequence, validate the integrated feature, and publish the approved final package.

## Validation

- Commands run: baseline `[PumpResults]` passed 129 assertions in 11 cases; refactored `[pump_result]` passed 129 assertions in 11 cases; moved `[EstimateFLA]` passed 64 assertions; the full native suite passed 4,148 assertions in 317 cases; `npm run verify:types` passed; `npm run verify:wasm` rebuilt and staged the composed-input module and passed all 251 browser tests; `npm run check:docs` passed; Doxygen generated the Pump Result page without module-specific warnings; `git diff --check` passed. Against `measur-tools-suite@1.2.6-beta.355.1`, Desktop passed five focused pump wrapper tests, Angular application typechecking, the root application build, and the full PR unit/regression workflow. Poles PR #423 subsequently passed native tests, rebuilt-WASM tests, and declarations/documentation checks before publishing `1.2.6-beta.358.1`.
- Commands still needed: final generated-document visual review; repeat integrated Suite and Desktop checks after each applicable dependency migration and against the approved final package.
- Known environment limits: Doxygen reports pre-existing repository warnings and cannot run BibTeX in this environment. Browser security policy prevented opening the generated local HTML page, so generated markup was inspected statically.

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

- The final package identifier remains pending. Suite issue #216 remains open although Poles PR #423 is merged; close or retain it according to project issue policy. The next planned Suite child issue is #208 MotorEfficiency.
