# MoverShaftPower Refactor Handoff

## Workflow Metadata

- Lifecycle: completed
- Status: Implemented, verified and independently reviewed Ready; no unresolved actionable findings.
- Owner: Codex; created / last updated: 2026-10-27.
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/222
- Branch / intended PR base: `issue-222` / `epic-pump-result-refactor`.
- Base commit: `2a20eed283fd4195c0b3af70ced8a2175c38bab7` (OptimalPumpShaftPower PR #442 merged).
- Suite PR: [#443 and CI/publication evidence](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pull/443); delivery and validation evidence are maintained in its description and CI comments.
- Delivery: user requested commit, push and PR creation on 2026-10-27; target the epic branch.
  Keep post-push CI/package evidence in the PR; avoid publication-evidence-only follow-up pushes.
- Desktop coordination: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957

## Target And Persona Sequence

- Logical module: `motorDriven/pumpFan/mover_shaft_power`.
- Replace `MoverShaftPower.h/.cpp` and native test with snake_case counterparts; extract the mixed
  PumpFan binding/declarations into matching dedicated modules and expand the existing typed WASM test.
- Patterns: `compressedAir/dryer_operating_cost` and adjacent stateless motor/pump-fan modules.
- Refactor Planner: complete; user approved this full implementation plan and breaking removal.
- C++ Namespace Refactorer: complete; legacy class removed and PumpResult/FanResult migrated.
- WebAssembly TypeScript Steward: complete; value-object binding, declarations, exports and typed tests updated.
- Algorithm Docs Author: complete; teaching page, worked examples, symbol/unit tables and PumpResult link added.
- Verification Reviewer: complete; independent pre-PR review confirms Ready with no actionable findings.

## API And Compatibility Contract

| Surface | Before | After | Kind / units / defaults | Ownership / compatibility |
| --- | --- | --- | --- | --- |
| C++ calculator | Global class, constructor/calculate, getters/setters, nested Output | `mover_shaft_power::calculate(const Input&) -> Result` | Required aggregate: motor shaft hp, existing Motor::Drive, specified efficiency fraction | Plain values; breaking, no wrappers |
| WASM calculator | `new MoverShaftPower(P, drive, efficiency).calculate()` | `calculateMoverShaftPower(MoverShaftPowerInput)` | Function plus input/result value objects; all fields required | Breaking; no cleanup |
| WASM result | Constructible MoverShaftPowerOutput class | MoverShaftPowerResult plain object | moverShaftPower in hp; driveEfficiency fraction | Breaking; remove both old constructors and delete() calls |
| PumpResult / FanResult | Private class calls and camelCase C++ result members | Private namespace calls and snake_case result members | Existing public results and units unchanged | Existing consumer ownership preserved |

- Explicit user approval: replace classes and obsolete surfaces, confirmed in planning and implementation
  request on 2026-10-27. No numerical behavior change approved.
- C++ Input order: `motor_shaft_power`, `drive`, `specified_efficiency`; Result:
  `mover_shaft_power`, `drive_efficiency`. WASM/TypeScript fields use camelCase.
- TypeScript exports `MoverShaftPowerInput`, `MoverShaftPowerResult` and the function;
  `MoverShaftPowerModule` contains only the function. Interfaces are type-only, not runtime constructors.
- Preserve the existing Motor::Drive/runtime Drive enum names and values.
- Remove old header/class, getter/setter surface, nested Output, class bindings/declarations,
  obsolete mixed-module exports, and compatibility-only tests. No shim API.

## Formulas, Units And Documentation

- Question: how much motor shaft output reaches the pump/fan after drive losses?
- Direct drive returns supplied hp and efficiency 1; SPECIFIED multiplies supplied hp by its fraction.
- Belt loss uses the unchanged exponential coefficients 0.68759, -0.019791, 3.7558, -0.21507,
  3.9963; notched and synchronous factors remain `(0.05 / 0.07)` and `(0.02 / 0.07)`.
  Preserve multiplication/division order; efficiency is `1 - loss / motor_shaft_power` and delivered
  power is `motor_shaft_power - loss`. Unknown C++ drives retain ordinary V-belt fallback.
- No defaults, clamping, validation or error translation. Preserve signed/nonfinite arithmetic;
  belt zero-power efficiency is NaN. Specified efficiency is ignored in other branches.
- Teaching page: final outputs, drive decision path, formulas/symbol units, 50 hp notched-belt example
  (48.4814329723 hp), direct/specified examples, limitations, provenance and migration.
- Historical code attributes the belt curve to AMCA 203-90 Appendix L and scaling to a Belt Drive
  Tip Sheet; exact coefficient derivation is unverified. Do not invent external provenance or a
  validated operating range. Distinguish this forward calculation from OptimalMotorShaftPower.
- Legacy source/header archived unchanged at `/private/tmp/mover-shaft-power-222-xff89oh5`;
  baseline captures compiled with `-O3`. Golden values and verification evidence are recorded below.

## Desktop And Package Boundaries

- Classification: breaking C++/WASM/TypeScript API, no intended numerical change.
- Read-only inspection of local Desktop app/process-flow source found no direct calculator calls;
  installed declarations expose the legacy classes. Pump/fan assessments consume it indirectly.
- Desktop wrappers/tests, saved data, root/process-flow dependency pins, web/Electron loading and
  package selection/validation remain deferred to final epic integration. No Desktop mutations.
- Beta/final version: pending final integration; no manual version bump or publication.

## Validation

- Archived legacy header/source bytes match base commit `2a20eed`; captures compiled at `-O3`.
  Durable native and WASM fixtures cover both fields for 48 finite duties and 53 arithmetic boundaries.
- Native baseline configure/build passed; focused baseline passed 179 assertions in 14 cases.
  Refactored focused checks passed 453 assertions in 17 cases. Initial refactored native build/full suite passed
  5,448 assertions in 344 cases, including unchanged PumpResult and FanResult expectations.
- Temporary `-O3` differential harness passed 1,607,396 comparisons over all five drives, two invalid
  C++ drives, dense -1000..1000 hp duties, binary exponents/adjacent values, efficiency fractions,
  signed zeros, subnormals, NaN and infinities. Both fields match bit-for-bit except NaN classifications.
- `npm run verify:types` passed. Fresh `npm run verify:wasm` rebuilt/staged runtime assets,
  typechecked and passed all 284 browser tests, including 101 captured calculator fixtures.
- `npm run check:docs` and `git diff --check` passed. npm package dry-run includes 101 files,
  both runtime assets, package entrypoint and the new declaration module; old class declarations removed.
- Doxygen emitted the new page without module-specific warnings. Local browser inspection confirms
  readable equations, symbol/unit tables and the worked example. All 52 MathJax containers rendered
  without math errors; browser logs contain only existing MathJax configuration/component warnings.
- Existing full-documentation BibTeX error persists despite successful page generation. Sandbox initially
  blocked the Emscripten cache lock, npm cache and localhost socket; approved reruns passed.
- Still needed for this module implementation: none. Desktop verification remains deferred to final epic
  integration; no Desktop checks or changes performed.

## Internal Review

- Intended base: `epic-pump-result-refactor` at `2a20eed283fd4195c0b3af70ced8a2175c38bab7`.
- Reviewed implementation snapshot: `5f8208126b72afd7c1d22747fd1db6079d47e42e` in an isolated
  temporary clone at `/private/tmp/mover-shaft-power-222-xff89oh5/review-snapshot`. At review time the user branch/index
  were uncommitted and unstaged; the snapshot freezes the entire candidate diff against the epic base.
- Independent reviewer: `mover_shaft_power_review`, using `.github/skills/measur-code-review/` in a
  separate context. Readiness: **Ready**; no actionable P0-P3 findings or unresolved module defects.
- Reviewer independently rebuilt the `-O3` differential against frozen source and passed all 1,607,396
  comparisons; legacy archived bytes matched the base. Frozen/live source and tests matched. Focused
  native checks passed 453 assertions in 17 cases; typecheck, Markdown links, complete-diff whitespace
  and package-evidence inspection passed. Linked Suite #222 and Desktop #8957 were inspected read-only.
- Reviewer inspected author logs for full native (5,448 assertions/344 cases) and fresh WASM
  (284 browser tests); those broad suites and browser rendering were not independently repeated.
- No review fixes were needed. Final handoff/roadmap changes record completed review and browser QA
  evidence only. Documentation links and whitespace checks were rerun after this evidence update.
- Remaining module-specific validation gaps: none. Existing BibTeX/MathJax configuration limitations
  and deferred final Desktop verification are recorded above.

## Open Questions Or Blockers

- None for implementation. Final package selection and consolidated Desktop verification are epic work.

## Named Constants Follow-Up — 2026-10-27

- User requested meaningful names for the magic numbers and clearer provenance. Replaced the raw
  curve coefficients with private constexpr slow/fast decay amplitudes, signed inverse-hp exponent
  coefficients and high-positive-power loss term. Named the 0.07/0.05/0.02 reference loss fractions,
  relative loss multipliers and percentage-point divisor. No public API change or arithmetic regrouping.
- Comments and the teaching page connect the reference fractions to legacy comments' nominal
  93%/95%/98% efficiencies, distinguish them from calculated efficiency, and retain the qualification
  that exact empirical coefficient derivation is unverified. Names describe mathematical roles.
- Final-source native focused checks passed 453 assertions in 17 cases; a freshly compiled `-O3`
  differential passed all 1,607,396 comparisons, both fields bit-for-bit except NaN classification.
  Fresh rebuilt/staged `npm run verify:wasm` passed all 284 browser tests and typechecking.
  Markdown links and whitespace checks passed. Doxygen emitted the updated page without module-specific
  warnings; the existing repository BibTeX error remains. The full native suite and browser visual QA
  above belong to the preceding revision; neither needed repeating for named constants/prose alone.
- Independent review of follow-up implementation snapshot `f797513ed5b7e6ffb9ebbd473f602c56dcb77efb`
  against the preceding reviewed snapshot `eddc68e7587bdd934e4d0efb430d3c0ffa0a6b24` confirmed Ready
  with no actionable findings. The complete candidate still targets epic base `2a20eed`.

## Engineering Documentation Sweep — 2026-10-27

- User requested removal of migration content from calculation `.dox` pages across the PumpResult epic.
  Swept all 13 completed pages: PumpResult, Poles, MotorEfficiency, EstimateFLA, MotorCurrent, MotorPower,
  MotorPowerFactor, MotorShaftPower, OptimalMotorPower, FluidPower, MoverEfficiency,
  OptimalPumpShaftPower and MoverShaftPower. PumpHead is outside this epic and was left unchanged.
- Removed old-to-new constructor/accessor/cleanup instructions, removed/additive API status, refactor
  narration and commit/test-capture history. Current interfaces/examples remain, along with engineering
  interpretation, provenance qualifications, boundary behavior and model-specific caveats. Migration
  contracts remain in development handoffs and PR records. Added this distinction to the documentation guide.
- All 81 formula blocks, 80 symbol/unit tables and 37 inline math expressions are byte-identical to
  PR head `32940f58b19ec4271149bb62e9211e0c2f8018e4`. Documentation links and whitespace checks pass.
  Doxygen emitted all 13 pages without migration headings or edited-page diagnostics. The existing
  repository-wide BibTeX error and unrelated warnings remain. No runtime code/API change or native/WASM
  rerun is involved in this prose-only follow-up; prior runtime validation remains applicable.
- Independent reviewer `mover_shaft_power_review` reviewed delta `32940f5...3295592c9b7c0c6b85508faf0bdc5c8497303b2b`
  in `/private/tmp/pump-docs-sweep-wwugj3ec/review-snapshot`: Ready, no actionable findings. Reviewer
  independently confirmed identical math/tables, links and whitespace and inspected Doxygen evidence.
- This update continues PR #443; no new PR or Desktop/package changes are required.
