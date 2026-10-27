# OptimalPumpShaftPower Refactor Handoff

## Workflow Metadata

- Lifecycle: completed
- Status: implemented, verified and independently reviewed; Ready at isolated review snapshot `1046b25`.
- Owner: Codex
- Created / last updated: 2026-10-27.
- Suite issue: https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/227
- Branch / intended PR base: `issue-227` / `epic-pump-result-refactor`.
- Base commit: `8d34462eada5354dd6841db9f9f0cbc680d3c6c7` (MoverEfficiency PR #441 merged).
- Suite PR: [branch PR and CI/publication evidence](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/pulls?q=is%3Apr+head%3Aissue-227)
  will be maintained in the PR description and workflow comments.
- Desktop coordination: https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/8957
- Prior Desktop MotorEfficiency PR: https://github.com/ORNL-AMO/AMO-Tools-Desktop/pull/8964
  (merged at `9b7ff3d7416ff8172ad3ab24fc01ab2ef29acbc9`, verified read-only during review).

## Target And Persona Sequence

- Logical module: `motorDriven/pumpFan/optimal_pump_shaft_power`.
- Replace legacy header/source with one snake_case pair; add matching binding, declaration, native test,
  typed WASM test and teaching `.dox` page. No direct legacy test/binding/declaration/page exists to migrate.
- Patterns: `compressedAir/dryer_operating_cost` and adjacent `pumpFan/mover_efficiency`.
- Refactor Planner: complete; user approved the full stateless implementation plan on 2026-10-27.
- C++ Namespace Refactorer: complete; namespace/header/source, two private consumers and native tests migrated.
- WebAssembly TypeScript Steward: complete; functions/value objects, documented declarations, module/entrypoint
  exports and three typed browser tests implemented; fresh-WASM verification passed.
- Algorithm Docs Author: complete; result-first teaching page, five formulas with symbol/unit tables,
  pump/fan worked examples, pressure convention, limits, provenance and migration implemented.
- Verification Reviewer: complete; cross-layer contracts, formulas, units, consumer behavior and validation checked.
- Independent pre-PR review: complete; Ready with no unresolved actionable findings.

## API And Compatibility Contract

| Surface | Before | After | Kind / units / defaults | Ownership / compatibility |
| --- | --- | --- | --- | --- |
| C++ pump | `OptimalPumpShaftPower(Q, H, SG, efficiency).calculate()` | `optimal_pump_shaft_power::calculatePump(const PumpInput&) -> double` | Required aggregate; US gpm, ft, dimensionless SG and efficiency fraction; hp result | Plain values; breaking, no wrapper |
| C++ fan | `OptimalPumpShaftPower(Q, pi, po, K, efficiency, pv).calculate()` | `optimal_pump_shaft_power::calculateFan(const FanInput&) -> double` | Required aggregate; cfm, pressures in. water, dimensionless K and efficiency fraction; hp result | Plain values; breaking, no wrapper |
| Standalone WASM | None | `calculateOptimalPumpShaftPower(OptimalPumpShaftPowerInput)` and `calculateOptimalFanShaftPower(OptimalFanShaftPowerInput)` | Functions and input value objects; numeric hp returns | Plain objects/scalars; no cleanup; additive |
| Direct consumers | Constructor/calculate calls in PumpResult and FanResult | Namespace calls only | Existing public contracts and positive-displacement branch retained | Existing consumer ownership preserved |

- Explicit user approval: remove legacy C++ class/header/getters/setters without compatibility wrappers;
  add the two standalone WASM functions. No numerical behavior change approved.
- Pump fields in order: `flow_rate`, `head`, `specific_gravity`, `pump_efficiency`.
- Fan fields in order: `flow_rate`, `inlet_pressure`, `outlet_pressure`, `compressibility_factor`,
  `fan_efficiency`, `velocity_pressure`. WASM uses camelCase; every field is required.
- `OptimalPumpShaftPowerModule` contains only the two runtime functions. Interfaces are type-only;
  no result objects, enums or runtime constructors are added.

## Formulas, Units And Documentation

- Engineering question: what shaft input is required for this duty at the supplied efficiency?
- Final hp result: `(fluidPowerKw / efficiencyFraction) / 0.746`; preserve evaluation order using
  `physics::conversions::kBhpToKw` (exactly 0.746). Do not cancel conversions or regroup arithmetic.
- Supporting fluid power: pump `0.746 * Q * H * SG / 3961.38`; fan
  `0.746 * Q * (po - pi - pv) * K / 6362`, delegated to `fluid_power`.
- Correct legacy percent comments: efficiency is a fraction (0.80 means 80%), confirmed by both
  native consumers and Desktop percentage-to-fraction adaptations.
- Preserve signed values/zeros, infinities, NaN and out-of-range efficiencies; no validation/defaults/clamping.
- Teaching sequence: final power and meaning, pump/fan duty selection, supporting formulas/units,
  both worked examples, pressure convention, physical/arithmetic limits, provenance and migration.
- “Optimal” means power at a supplied efficiency; the method does not optimize efficiency or select equipment.
- Provenance: unchanged class/source at the base commit and direct captures. The exact historical
  provenance of FluidPower's divisors is unverified. No SME decision is required for behavior preservation.
- Golden examples captured at -O3: pump `(1840,174.85,1,0.8)` gives `101.51891512553706` hp;
  fan `(129691,-16.36,1.1,0.988,0.595398315,0)` gives `590.62218629848621` hp.

## Desktop And Package Boundaries

- Classification: breaking C++ API plus additive WASM API; no intended calculation behavior change.
- Read-only inspection found no direct legacy Desktop use in application/process-flow source or installed
  declarations. Pump/fan assessments consume it indirectly; retain their existing goldens and conventions.
- No Desktop source/tests, saved-data changes, package pins, loading-path changes or PR updates.
- Root/process-flow package updates and downstream validation remain deferred to final epic integration.
- Beta/final package versions: pending verified publication; no manual publication/version bump here.

## Validation

- Archived legacy header/source outside the repository at `/private/tmp/optimal-pump-shaft-power-bgbej6dg`.
  Captured 15 pump and 15 fan outputs at -O3 before removal, including modified-assessment duties,
  velocity pressure, signed/zero duties, efficiency scaling and finite extreme magnitudes.
- Baseline native configure/build and focused FluidPower/MoverEfficiency/PumpResult/FanResult checks
  passed 259 assertions in 19 cases.
- Refactored native configure/build and final focused checks passed 345 assertions in 22 cases;
  full native suite passed 5,174 assertions in 341 cases. Existing assessment expectations are unchanged.
- Temporary -O3 legacy differential harness passed all 11,520,946 pump/fan combinations, comparing
  non-NaN results bit-for-bit (including signed zero/infinity) and matching NaN classifications.
  Archived header/source bytes match the base commit. The comparison was rerun successfully.
- `npm run verify:types` passed. Fresh `npm run verify:wasm` rebuilt/staged client.js and client.wasm,
  typechecked and passed all 282 browser tests, including the three new typed calculator tests.
- Markdown links and `git diff --check` passed. npm package dry run contains 100 files, including
  both runtime assets, the entrypoint and new declaration; the legacy header is absent.
- Doxygen emitted the new page without module-specific warnings. Browser inspection over localhost
  confirmed readable formulas, symbol/unit tables and both examples; all 69 MathJax containers rendered
  without math errors. Existing MathJax configuration warnings do not prevent rendering.
- Environment limits: initial WASM link required approved Emscripten-cache access; rerun passed.
  Package inspection and localhost documentation serving required approved cache/socket access.
  Full Doxygen generation retains the pre-existing missing-BibTeX error despite emitting the page.
- Still needed for this implementation: none. Final integrated Suite review and consolidated Desktop
  verification remain epic-level work. No Desktop changes or validation were performed for this child.

## Internal Review

- Intended base: `epic-pump-result-refactor` at `8d34462eada5354dd6841db9f9f0cbc680d3c6c7`.
- Reviewed implementation snapshot: `72c032f97e11cf6a6cfd4ea6282a3975170a36ae`.
- Final reviewed snapshot, including the handoff-only correction: `1046b25f7b7441f7cfbbdd456337d31d21d17e06`.
  These are frozen commits in an isolated temporary clone at
  `/private/tmp/optimal-pump-shaft-power-bgbej6dg/review-snapshot`; at review time the user's branch/index
  were not committed or staged. The complete candidate diff was reviewed against the intended epic base.
- Independent reviewer: `optimal_shaft_power_review`, using `.github/skills/measur-code-review/` in a separate context.
- Readiness: Ready; no unresolved actionable findings or P0-P2 findings.
- Findings/dispositions: one P3 stale Desktop PR status was corrected in this handoff and the parent
  roadmap after read-only GitHub verification. PR #8964 is merged, not held. Remaining Desktop work
  stays deferred. The reviewer checked the correction and confirmed Ready at the final snapshot.
- Reviewer independently passed 345 focused native assertions in 22 cases, all 11,520,946 differential
  comparisons using a freshly compiled -O3 harness, type verification, Markdown links and complete-diff
  whitespace checks. Archived legacy bytes matched the base; frozen candidate contents and package
  assets were checked. Reviewer also inspected full-native/fresh-WASM logs (5,174 assertions/341 cases;
  282 browser tests); broad suites and browser rendering were not independently repeated.
- After the P3 correction, author and reviewer reran Markdown links and whitespace checks successfully.
  No implementation or test changes were needed. This final handoff/roadmap update records completed
  review evidence only and does not materially change the reviewed candidate.
- Remaining module-specific validation gaps: none. Existing BibTeX/MathJax configuration limitations
  and deferred Desktop validation remain documented above.

## Open Questions Or Blockers

- None for implementation. Final package selection and Desktop integration remain epic-level work.
- User requested commit, push and PR creation on 2026-10-27; target the epic branch. Keep subsequent
  CI/package evidence in the linked PR without publication-evidence-only follow-up pushes.
