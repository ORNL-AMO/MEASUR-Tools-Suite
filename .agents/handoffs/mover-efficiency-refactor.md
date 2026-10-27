# MoverEfficiency Refactor Handoff

## Workflow Metadata

- Lifecycle: completed
- Status: Implemented, verified and independently reviewed; Ready at 27510c8.
- Owner: Codex
- Created: 2026-10-26; last updated: 2026-10-27.
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/221
- Branch / intended PR base: `issue-221` / `epic-pump-result-refactor`.
- Base commit: `7b5b760d6183891d892a55eb132f57b472430a4f` (FluidPower PR #434 merged).
- Suite PR: none opened; future CI/publication evidence belongs in the child PR and workflow comments.
- Desktop coordination: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Held Desktop PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964

## Target And Persona Sequence

- Logical module: `motorDriven/pumpFan/mover_efficiency`.
- Replace `MoverEfficiency.h/.cpp` and its native test with one snake_case header/source/test set.
  Add matching binding/declaration, typed `wasm_mover_efficiency.test.ts`, and teaching `.dox` page.
- No standalone legacy binding, declaration, WASM test or algorithm page exists to remove.
- Patterns: `compressedAir/dryer_operating_cost` and adjacent `pumpFan/fluid_power`.
- Refactor Planner: complete; user approved the full implementation plan on 2026-10-26.
- C++ Namespace Refactorer: complete; namespace API, two private consumers, comments and native tests migrated.
- WebAssembly TypeScript Steward: complete; two functions, two value objects, documented interfaces,
  entrypoint/module exports and three typed browser tests implemented. Fresh-WASM verification passed.
- Algorithm Docs Author: complete; final-ratio-first teaching page, five formulas with symbol/unit tables,
  both worked examples, retained pressure convention, physical/arithmetic limits and migration notes implemented.
- Verification Reviewer: cross-layer API, units, ownership, consumer behavior, formulas and validation
  checked; independent review-only readiness pass complete, Ready with no actionable findings.

## API And Compatibility Contract

| Surface | Before | After | Kind / units / defaults | Ownership / compatibility |
| --- | --- | --- | --- | --- |
| C++ pump | `MoverEfficiency(SG, Q, H, shaftHp).calculate()` | `mover_efficiency::calculatePump(const PumpInput&) -> double` | Required aggregate; SG dimensionless, Q US gpm, H ft, shaft hp; fraction result | Plain values; breaking, no wrapper |
| C++ fan | `MoverEfficiency(Q, shaftHp, pi, po, K, pv).calculate()` | `mover_efficiency::calculateFan(const FanInput&) -> double` | Required aggregate; Q cfm, shaft hp, pressures in. water, K dimensionless; fraction result | Plain values; breaking, no wrapper |
| Standalone WASM | None | `calculatePumpMoverEfficiency(PumpMoverEfficiencyInput)` and `calculateFanMoverEfficiency(FanMoverEfficiencyInput)` | Functions plus input value objects; numeric fraction returns | Plain objects/scalars; no cleanup; additive |
| Direct consumers | Constructor/calculate calls in PumpResult and FanResult | Namespace calls only | Existing public contracts, positive-displacement branch and percentage conventions retained | Existing consumer ownership preserved |

- User explicitly approved breaking C++ class/header/getter/setter removal without compatibility wrappers,
  separate pump/fan functions and additive standalone WASM APIs. No numerical behavior change approved.
- Pump fields in order: `specific_gravity`, `flow_rate`, `head`, `mover_shaft_power`.
- Fan fields in order: `flow_rate`, `mover_shaft_power`, `inlet_pressure`, `outlet_pressure`,
  `compressibility_factor`, `velocity_pressure`.
- WASM fields use camelCase, including `moverShaftPower` in both interfaces; every field is required.
- Module type exposes only the two runtime functions; input interfaces are type-only. No result objects/enums.

## Formulas, Units And Documentation

- Engineering question: what fraction of supplied mover shaft power reaches the fluid at this operating duty?
- Final fraction: `(fluidPowerKw / 0.746) / moverShaftPowerHp`. Use `physics::conversions::kBhpToKw`
  (exactly 0.746) without cancelling conversions or changing evaluation order.
- Supporting fluid power: pump `0.746 * Q * H * SG / 3961.38`;
  fan `0.746 * Q * (po - pi - pv) * K / 6362`, delegated to `fluid_power`.
- Result is dimensionless, not percentage points: 0.75 means 75%. The legacy percent comment is incorrect.
- Preserve above-one/negative outputs, signed zero, infinities and NaN. No validation, clamping or defaults.
- Retain all 22 pump input/golden rows (the original two test cases duplicate the same table).
  Capture direct fan results, including the existing FanResult duty and nonzero velocity pressure, before removal.
- Teaching order: final ratio and interpretation, duty selection/units, supporting formulas and pressure
  convention, pump/fan worked examples, physical and arithmetic boundaries, provenance and migration.
- Provenance: unchanged legacy class/source at the base commit and its captured outputs. Exact historical
  provenance of FluidPower's divisors remains unverified. No module-specific SME decision is needed.

## Desktop And Package Boundaries

- Classification: breaking C++ API plus additive WASM API; no intended calculation behavior change.
- Planning inspected Desktop wrappers, process-flow source and installed declarations: no direct legacy
  MoverEfficiency use found. Pump/fan assessments consume it indirectly; preserve their existing goldens.
- No Desktop source/tests, dependency pins, saved-data changes, loading-path changes or held-PR updates.
- Root/process-flow package updates and downstream verification remain deferred to final epic integration.
- Beta/final versions: pending verified publication; no manual publication or version bump in this implementation.

## Validation

- Legacy header/source/test archived outside the repository before editing; 13 direct fan outputs captured at -O3.
- Baseline native configure/build passed; focused legacy/FluidPower/PumpResult/FanResult checks passed
  232 assertions in 18 cases. Refactored configure/build and focused checks passed 255 assertions in 19 cases.
- Temporary -O3 differential comparison passed all 2,598,977 pump/fan combinations, comparing the archived
  legacy class with the namespace implementation: all non-NaNs bit-for-bit (including signed zero/infinity),
  with matching NaN classifications.
- After tightening signed-zero assertions, the final native rebuild and focused rerun passed
  259 assertions in 19 cases; the full native suite passed 5,088 assertions in 338 cases.
  The differential harness was rerun successfully. Archived header/source/test bytes match the base commit.
- `npm run verify:types` passed. `npm run verify:wasm` rebuilt/staged client.js and client.wasm,
  typechecked and passed all 279 browser tests, including the three new typed MoverEfficiency tests.
- Markdown links and `git diff --check` passed. npm package dry run passed: both runtime assets,
  entrypoint and new declaration module present among 99 files; removed legacy header absent.
- Doxygen emitted the new page without module-specific warnings. Browser inspection over localhost confirmed
  readable ratio, pump/fan examples and symbol/unit tables; all 69 MathJax containers rendered without math
  errors, and the page console had no errors. Corrected the final digit of the pump example's intermediate
  hp value during numerical QA; regenerated page inspection confirmed the correction and zero math errors.
- Environment limits: initial WASM link required approved access to the Emscripten cache; the rerun passed.
  npm package inspection and the localhost documentation server also required approved cache/socket access.
  Full documentation generation retains the pre-existing missing-BibTeX error despite emitting the page.
- Still needed for this implementation: none. No runtime implementation changes after fresh-WASM validation;
  subsequent source layout, native assertion and documentation updates were checked as described above.
  Final integrated Suite review and consolidated Desktop validation remain epic-level work.

## Internal Review

- Intended base: `epic-pump-result-refactor` at `7b5b760d6183891d892a55eb132f57b472430a4f`.
- Reviewed implementation head: `27510c8f19ee2c98b73bc62d596bcea5d1cb364f`.
- Independent reviewer: `mover_efficiency_review`, using `.github/skills/measur-code-review/` in a separate context.
- Readiness: Ready; no actionable findings and no unresolved P0-P2 findings. No review fixes required.
- Reviewer independently passed 259 focused native assertions in 19 cases, all 2,598,977 differential
  comparisons, type verification, Markdown-link checks and complete-diff whitespace checks. Archived
  header/source/test bytes matched the base; package artifacts and both examples' arithmetic were checked.
- Reviewer inspected the recorded full-native and fresh-WASM logs (5,088 assertions / 338 cases;
  279 browser tests). Those broad checks and browser rendering were not repeated by the reviewer.
- Remaining module-specific findings or validation gaps: none. Existing BibTeX limitation and deferred
  Desktop validation remain documented above. This subsequent handoff-only evidence update does not
  materially change the reviewed implementation; no affected validation rerun was needed for review fixes.

## Open Questions Or Blockers

- None for implementation. Desktop integration and final package selection remain epic-level work.
