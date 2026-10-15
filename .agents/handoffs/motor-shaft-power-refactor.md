# MotorShaftPower Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: All five persona phases complete; native/types/fresh-WASM and rendered documentation verified; independent review next.
- Owner: Codex
- Created / last updated: 2026-10-15
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/212
- Branch / intended PR base: `issue-212` / `epic-pump-result-refactor`
- Base commit: `ba430c6f2518777f6839ec298282c1d83d16ad7e`
- Suite PR: pending; post-push CI/publication evidence belongs in the eventual PR description/comments.
- Desktop coordination: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Held Desktop PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964

## Target And Persona Sequence

- Logical module: `motorDriven/motor/motor_shaft_power`.
- Replace `MotorShaftPower.h/.cpp` with one matching snake_case pair; add dedicated binding, declaration,
  native test, typed `motors/wasm_motor_shaft_power.test.ts`, and teaching `.dox` page.
- No standalone legacy binding, declaration, native test, or WASM test exists to remove.
- Patterns: `compressedAir/dryer_operating_cost` and adjacent stateless motor modules.
- Sequence: Refactor Planner, C++ Namespace Refactorer, WebAssembly TypeScript Steward,
  Algorithm Docs Author, Verification Reviewer; record completion of each phase here.

## API And Compatibility Contract

| Surface | Before | After | Kind / units / defaults | Ownership / compatibility |
| --- | --- | --- | --- | --- |
| C++ calculator | Global class, eleven-argument constructor, `calculate()`, nested `Output` | `motor_shaft_power::calculate(const Input&) -> Result` | Required aggregate inputs; hp, kW, rpm, V, A, efficiency fraction, existing Motor enums; no defaults | Plain values; breaking, no wrappers |
| Standalone WASM | None | `calculateMotorShaftPower(MotorShaftPowerInput) -> MotorShaftPowerResult` | Function plus two value objects; same units | Plain objects, no cleanup; additive |
| FanResult dependency overload | Accepts `MotorShaftPower::Output` | Accepts `motor_shaft_power::Result` | Same output semantics | C++ dependency type migration; runtime API preserved |

- User explicitly approved class/header removal and the full stateless WASM/TypeScript API in planning and
  requested implementation on 2026-10-15. No calculation behavior change approved.
- Input order: `motor_rated_power`, `motor_measured_power`, `motor_rpm`, `line_frequency`, `efficiency_class`,
  `specified_efficiency`, `rated_voltage`, `full_load_amps`, `field_voltage`, `load_estimation_method`, `field_current`.
- Results: `shaft_power`, `current`, `power_factor`, `efficiency`, `power`, `estimated_fla`, `load_factor`.
- WASM names use camelCase, including `motorRpm` and `estimatedFLA`. Interfaces are type-only; module contributes
  only `calculateMotorShaftPower`. Reuse existing enum bindings.
- Migration: replace constructor/calculate calls with the function and complete aggregate input; update result
  member spelling. Remove old headers, class and nested output; no legacy standalone runtime surface existed.
- PumpResult and FanResult are the only calculator consumers. Preserve their exported fields and results;
  reuse the already-computed result in FanResult rather than evaluating twice.

## Formulas, Units And Documentation

- Engineering question: how much mechanical shaft power does a measured motor electrical operating point deliver?
- Final shaft power: electrical input kW times modeled efficiency fraction, divided by 0.746 kW/hp.
- POWER starts at load 0.01; CURRENT starts at 0.00. Retain repeated 0.01 additions, strict measurement comparisons
  and `load > 1.5`, both interpolation paths and voltage corrections, supplied-FLA normalization and estimated FLA.
- POWER ignores measured current; CURRENT ignores measured power. No validation, defaults, new clamping,
  fallback FLA, changed dependency errors, or altered nonfinite arithmetic.
- Legacy measured-power header incorrectly says hp; correct to electrical kW. Efficiency and load are fractions.
- Teaching sequence: final result/interpretation, measurement choice, model/bracketing, interpolation and voltage
  correction, worked examples for both modes, assumptions/limits, secondary API migration.
- Provenance: unchanged source and captured regression outputs; historical source of empirical interpolation
  and voltage adjustments is unverified. Verify external citations before adding them.

## Desktop And Release Boundaries

- Classification: breaking C++ API and additive WASM API; no intended numerical behavior change.
- Local Desktop source, installed declarations and process-flow source have no direct MotorShaftPower consumer;
  impact flows through pump/fan results. Preserve units, percentage conversions, saved data and runtime fields.
- Desktop wrappers/tests, both dependency pins, and held PR #8964 remain deferred to final epic integration.
- No package version changes or publication in this task; beta/final version pending verified publication.
- OptimalMotorPower, OptimalMotorShaftPower, MotorPerformance and other public refactors remain outside scope.

## Validation And Internal Review

- Legacy capture: 40 complete seven-output cases captured from unchanged base source after rebuilding native dependencies. Includes frequency/class/mode combinations and exact/adjacent search thresholds; durable goldens are in both test modules.
- C++ Namespace Refactorer: namespace/header/source/consumer migration and focused native tests complete.
- WebAssembly TypeScript Steward: dedicated binding, declaration, package export and typed browser tests complete.
- Algorithm Docs Author: final-result-first teaching page complete, with both worked examples and seven formulas
  with symbol tables; dependency links verified. No new external citations or provenance claims.
- Verification Reviewer: integrated API/ownership/units/formula/test consistency pass complete.
- Native configure/build passed. Focused shaft-power/pump/fan tests passed 446 assertions in 16 cases;
  full native suite passed 4,675 assertions in 332 cases. Existing pump/fan expected values are unchanged.
- `npm run verify:types` passed. After activating the installed SDK, `npm run verify:wasm` rebuilt and staged
  client.js/client.wasm and passed all 270 browser tests, including 40 captured seven-output operating points,
  plain-object typing/ownership, inactive inputs, immutability and state independence.
- Native tests also verify specified-efficiency dependency errors for both measurement modes.
- `npm run check:docs`, `git diff --check` and package dry-run inspection passed. Package contains both current
  runtime assets, the package declaration entrypoint and the new declaration module.
- Doxygen generated the new page without module-specific warnings. Localhost browser inspection confirmed
  rendered MathJax equations, symbol tables and both worked examples, with no browser errors.
- Final local cleanup changes only identifier spelling, comments and formatting in the calculation source;
  focused native tests were rerun afterward. Full-suite/fresh-WASM evidence predates that cosmetic cleanup.
- Pre-PR gate: independent review-only pass using `.github/skills/measur-code-review/` against the epic base;
  record exact reviewed base/head, findings, dispositions and readiness; no unresolved P0-P2 findings.
- Known environment limits: initial WASM command lacked SDK activation; activated rerun needed cache permission.
  Approved verification succeeded. npm package dry run also needed cache permission and passed on approved rerun.
  Doxygen's pre-existing missing-BibTeX error persists; this page has no bibliography dependency.
- Internal review: pending; reviewed base is the intended epic head at ba430c6, final implementation head to record.
- Local implementation only: no PR opened, push or package publication. CI/publication evidence is pending delivery.

## Open Questions Or Blockers

- No unresolved API or calculation-policy decisions.
