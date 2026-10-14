# MotorPowerFactor Refactor Handoff

## Workflow Metadata

- Lifecycle: active
- Status: All five persona phases complete; initial independent review's P2 documentation mismatch corrected;
  targeted review of the correction next.
- Owner: Codex
- Created / last updated: 2026-10-14
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/211
- Suite branch / intended PR base: `codex/motor-power-factor-refactor` / `epic-pump-result-refactor`
- Base commit: `271487373e5ee985ba61fdd2186c9d3a6bcd07c3`
- Suite PR: pending
- Desktop coordination: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Held Desktop PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964

## Target Module And Persona Sequence

- Domain / logical module: `motorDriven/motor` / `motor_power_factor`.
- Replace `MotorPowerFactor.h/.cpp` with one `motor_power_factor.h/.cpp` pair.
- Extract from mixed `motor.cpp` binding and `motor.d.ts` declaration into dedicated matching modules.
- Add `motor_power_factor.unit.cpp`, `motors/wasm_motor_power_factor.test.ts`, and
  `motor_power_factor_calculator.dox`; no direct legacy WASM test exists to migrate.
- Patterns: `compressedAir/dryer_operating_cost` value-object binding and adjacent motor namespace modules.
- Sequence: Refactor Planner, C++ Namespace Refactorer, WebAssembly TypeScript Steward,
  Algorithm Docs Author, Verification Reviewer; update this handoff after each phase.

## Runtime API Contract

| Surface | Before | After | Embind kind | Units / defaults | Ownership | Compatibility |
| --- | --- | --- | --- | --- | --- | --- |
| C++ power factor | Global class, two constructors, `calculate()` and nameplate accessors | `motor_power_factor::calculate(const Input&) -> double` | None | Nine required fields; hp, rpm, A, V, fractional load/efficiency; fractional PF | Plain input, scalar result | Breaking |
| WASM power factor | Five-argument `MotorPowerFactor` constructor and `calculate()` | `calculateMotorPowerFactor(MotorPowerFactorInput) -> number` | `class_` to `function` + `value_object` | Same fractions and units; all nine fields required, no defaults | No allocation or `delete()` | Breaking |

## API And Compatibility

- Namespace `motor_power_factor`; struct `Input`; scalar result with no output struct.
- Input order: line frequency, rpm, efficiency class, specified efficiency, rated hp, load fraction,
  current, operating efficiency, voltage. Snake_case C++ members; camelCase WASM fields.
- Reuse existing Motor enums; interfaces are type-only and excluded from runtime module properties.
- User approved the complete input, removal of legacy surfaces without wrappers, preservation of formulas,
  and deterministic MotorPerformance near-zero path during planning; implementation requested 2026-10-14.
- Migration: replace constructor/method calls with the function and complete plain input; remove cleanup.
- MotorShaftPower (three calls), OptimalMotorPower (one), and MotorPerformance (one) receive private updates only.
- MotorPerformance now supplies its existing nameplate data instead of leaving near-zero dependency fields
  uninitialized. No undefined legacy zero-load result is treated as a golden.

## Desktop Impact

- Direct consumer: `src/app/tools-suite-api/pumps-suite-api.service.ts::motorPowerFactor` currently converts
  percentage load/efficiency to fractions, invokes the legacy constructor, multiplies PF by 100, and deletes it.
- Final migration must supply all nine fields, preserve app-facing percent results, and remove cleanup.
- Callers include `psat.service.ts`, motor-inventory load-characteristic calculations and operations data.
- Pump/fan result fields and reports remain unchanged; no saved-data/default-data or asset-loading changes.
- Desktop source, tests, root/process-flow package pins, and held PR #8964 remain deferred to final integration.
- Local consumer and integration-guide inspection completed; no Desktop validation claimed for this child.

## Formulas And Units

- Engineering question: what fraction of a motor's apparent electrical power is real input power?
- Loaded result: `(load_factor * motor_rated_power * 0.746) /`
  `(motor_current * motor_efficiency * rated_voltage * sqrt(3) / 1000)`.
- Strict near-zero condition: `abs(load_factor) < 0.001`; query motor efficiency at load 0.25 and use
  `zero_load_power_loss / (460 * sqrt(3) * motor_current / 1000)`.
- Inherited loss model: zero-load loss is 0.8 times quarter-load loss; quarter-load loss uses modeled efficiency.
- Preserve evaluation order, fixed 460 V, signed/unclamped arithmetic, nonfinite results and dependency errors.
- Loaded branch ignores the four nameplate/model fields; near-zero branch ignores supplied operating
  efficiency and voltage. No new validation or defaults.
- Formula provenance: unchanged source and regression capture; DOE's 2008 motor sourcebook printed pages
  15 and 42 verified for the PF ratio and three-phase electrical relationship. Direct page links are provided;
  provenance of the 0.8 loss ratio, 0.001 threshold and fixed-voltage assumption remains unverified.
- Captured 31 legacy results by compiling unchanged MotorPowerFactor.cpp and motor_efficiency.cpp at the base;
  fully initialized nine-argument inputs cover defined behavior only. Temporary capture JSON is outside the repo.
- Teaching examples: 100 hp, load 0.75, 100 A, efficiency 0.9, 460 V -> PF 0.7802596029265596;
  60 Hz, 1780 rpm, energy-efficient, 100 hp, zero load, 30 A -> PF 0.053160046055729181.
- SME decision: no formula changes; legacy model provenance remains explicitly unverified.

## Package And Release Coordination

- Classification: breaking C++ and WASM API; bounded behavior correction for previously undefined
  MotorPerformance near-zero inputs.
- Beta / final package versions: pending verified publication / final integrated release.
- Both Desktop dependency pins stay unchanged until the approved integrated final/RC package.
- Release blocker: remaining epic modules and integrated Suite review, then consolidated Desktop migration.

## Validation

- Run: refreshed epic; legacy source compilation and 31-output capture succeeded; native configure/build
  and focused power-factor/pump/fan tests passed (207 assertions in 17 cases).
- Full native suite passed 4,381 assertions in 329 cases; `npm run verify:types` passed.
- `npm run verify:wasm` rebuilt and staged current JS/WASM and passed all 267 browser tests.
- `npm run check:docs`, `git diff --check`, and package dry-run inspection passed; `bin/client.js`,
  `bin/client.wasm`, package entrypoint and new declarations are included.
- Doxygen generated the new page without module-specific warnings. Browser rendering over an approved
  localhost server confirmed MathJax equations, symbol tables and both worked examples; no browser errors.
- Browser tests cover 31 captured native goldens, typed scalar surface and legacy-constructor removal,
  immutable input/state independence, branch-specific ignored inputs and deterministic MotorPerformance zero load.
- Remaining: independent pre-PR review and PR CI/publication evidence.
- Known limits: sandbox attempts blocked Emscripten and npm caches and local port binding; approved reruns passed.
  Doxygen's existing BibTeX failure persists elsewhere in the repository. This page uses verified direct source
  links instead of adding an unresolved numbered bibliography reference.

## Internal Review

- Intended base: `epic-pump-result-refactor` at `271487373e5ee985ba61fdd2186c9d3a6bcd07c3`.
- Initial reviewed head: `a332e902f5c2b79ca85ba80ca4785b247478d479`.
- Reviewer: `motor_power_factor_review`; initial result Not ready for one P2 documentation finding.
- Finding/disposition: header, TS and engineering prose incorrectly restricted near-zero PREMIUM to 2/4/6 poles.
  Corrected all three to describe motor_efficiency's retained mapping of higher classified counts to the six-pole
  curve. Calculation unchanged. Reviewer independently confirmed existing pole tests pass (9 assertions).
- Final reviewed head / readiness: pending targeted review.
- Use `.github/skills/measur-code-review/`; no unresolved P0-P2 finding before PR opening.

## Open Questions Or Blockers

- No unresolved API or behavior decision. Package publication and validation evidence pending.
